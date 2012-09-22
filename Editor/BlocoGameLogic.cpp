#include "main.h"

//
// ListenForBlocoGameLogicEvents
//
void ListenForBlocoGameLogicEvents(EventListenerPtr listener)
{
 	safeAddListener( listener, EvtData_New_Actor::sk_EventType );
 	safeAddListener( listener, EvtData_Destroy_Actor::sk_EventType );
 	safeAddListener( listener, EvtData_Transform_Actor::sk_EventType );
 	safeAddListener( listener, EvtData_Request_New_Actor::sk_EventType );
	safeAddListener( listener, EvtData_SetActorTransform::sk_EventType );
	safeAddListener( listener, EvtData_RunScript::sk_EventType );
	safeAddListener( listener, EvtData_Move_Actor::sk_EventType );
	safeAddListener(listener, EvtData_PhysCollision::sk_EventType);
	safeAddListener(listener, EvtData_RayCast::sk_EventType);
}


/************************************************************************/
/* BlocoGameLogic                                                       */
/************************************************************************/
BlocoGameLogic::BlocoGameLogic( GameOptions const &optionss ) : BaseGameLogic(optionss)
{
	m_pPhysics.reset(CreateGamePhysics());
	
	m_pListener =  EventListenerPtr( DEBUG_CLIENTBLOCK BlocoGameLogicListener( this ) );
	ListenForBlocoGameLogicEvents(m_pListener);

	{
		//Create our metatable...
		m_MetaTable = g_pApp->m_pLuaStateManager->GetGlobalState()->GetGlobals().CreateTable("BlocoGameLogic");
		m_MetaTable.SetObject("__index", m_MetaTable);

		m_MetaTable.RegisterObjectDirect< BlocoGameLogic > ( "SetCameraOffset", NULL, &BlocoGameLogic::SetCameraOffset); 

		LuaObject luaStateManObj = g_pApp->m_pLuaStateManager->GetGlobalState()->BoxPointer(this);
		luaStateManObj.SetMetaTable(m_MetaTable);
		g_pApp->m_pLuaStateManager->GetGlobalState()->GetGlobals().SetObject("BlocoGameLogic", luaStateManObj);
	}

	m_scriptInput.reset(DEBUG_CLIENTBLOCK CScriptInput(g_pApp->m_pLuaStateManager->GetGlobalState()));

	shared_ptr<PhysicObjectParams> param = shared_ptr<PhysicObjectParams>(DEBUG_CLIENTBLOCK PhysicObjectParams(GetNewActorID()));
	shared_ptr<IActor> actor = param->VCreate(this);

	m_pPhysics->VAddPlane(Vec(0.0f,1.0f,0.0f),0.0f,actor.get(),0.0,PhysMat_Playdough);
}

void BlocoGameLogic::VRemoveActor( ActorId id )
{
	shared_ptr<IActor> actor = VGetActor( id );
	assert(actor && "No such actor!");
	if (!actor)
	{
		return;
	}

	//Call any script-related destructor.
	LuaState * pState = g_pApp->m_pLuaStateManager->GetGlobalState().Get();
	LuaObject globalActorTable = g_pApp->m_pLuaStateManager->GetGlobalActorTable();
	assert( globalActorTable.IsTable() && "Global actor table is NOT a table!" );
	LuaObject actorData = globalActorTable[ id ];

	shared_ptr<ActorParams> actorParams = actor->VGetParams();
	if ( 0 != strlen( actorParams->m_OnDestroyLuaFunctionName ) )
	{
		//First attempt to FIND the function specified.
		LuaObject foundObj = g_pApp->m_pLuaStateManager->GetGlobalState()->GetGlobal( actorParams->m_OnDestroyLuaFunctionName );
		if ( foundObj.IsNil() )
		{
			assert( 0 && "Unable to find specified OnDestroyFunc function!" );
		}
		else
		{
			//Make sure it actually *IS* a function.
			if ( false == foundObj.IsFunction() )
			{
				assert( 0 && "Specified OnDestroyFunc doesn't exist!" );
			}
			else
			{
				//Attempt to call the function.
				LuaFunction< void > onDestroyFunc( foundObj );
				onDestroyFunc( id, actorData );	//Pass in the actor ID and this actor's user-owned data table.
			}
		}
	}

	//Remove the actor from script's grubby little hands.
	actorData.AssignNil( pState );

	BaseGameLogic::VRemoveActor(id); 


	const EvtData_Destroy_Actor event( id );
	safeTriggerEvent( event );
}

void BlocoGameLogic::SetCameraOffset( LuaObject gameViewIndex, LuaObject offsetTable )
{
	//Ensure we have some non-garbage data.
	if ( false == gameViewIndex.IsNumber() )
	{
		assert( 0 && "Called SetCameraOffset() and first param wasn't a number for gameview index!" );
		return;
	}
	if ( false == offsetTable.IsTable() )
	{
		assert( 0 && "Called SetCameraOffset() and second param wasn't a table for camera offset!" );
		return;
	}

	//Make sure we've got a good camera offset table.
	Vec camOffset( 0.0f, 0.0f, 0.0f, 0.0f );
	const int tableCount = offsetTable.GetTableCount();
	if ( 3 != tableCount )
	{
		assert( 0 && "Called SetCameraOffset() and second param didn't have exactly 3 entries!" );
		return;
	}
	camOffset.SetX( offsetTable[ 1 ].GetFloat());
	camOffset.SetY( offsetTable[ 2 ].GetFloat());
	camOffset.SetZ(offsetTable[ 3 ].GetFloat());

	//Now ensure we have a valid value for game view.
	bool bFound = false;
	const GameViewId gameViewID = gameViewIndex.GetInteger();
	for ( GameViewList::iterator iter = m_gameViews.begin(), end = m_gameViews.end(); iter != end; ++iter )
	{
		shared_ptr<IGameView> pGameView = *iter;
		const GameViewId testID = pGameView->VGetId();
		if ( testID == gameViewID )
		{
			//Got our man, now ensure it's of the proper type.
			const GameViewType testType = pGameView->VGetType();
			if ( GameView_Human == testType )
			{
				bFound = true;
				//Cast it, then give it the message.
				HumanView * pHumanView = static_cast< HumanView * >( &*pGameView );
				pHumanView->VSetCameraOffset( camOffset );
			}
			break;
		}
	}

	assert( bFound && "Called SetCameraOffset() for an invalid game view ID." );
}

void BlocoGameLogic::VOnUpdate( float time, float elapsedTime )
{
	BaseGameLogic::VOnUpdate(time,elapsedTime);

	m_scriptInput->OnUpdate(elapsedTime);
}



/************************************************************************/
/* Game Logic Listener                                                  */
/************************************************************************/

bool BlocoGameLogicListener::HandleEvent( IEventData const & event )
{
	//Request_New_Actor
	if ( EvtData_Request_New_Actor::sk_EventType == event.VGetEventType() )
	{
		const EvtData_Request_New_Actor & castEvent = static_cast< const EvtData_Request_New_Actor & >( event );

		ActorParams * pActorParams = NULL;

		ActorId actorID = m_pGame->GetNewActorID();

		const bool bCreateEventData = castEvent.VHasLuaEventData();
		if ( false == bCreateEventData )
		{
			//Actor params were created FOR us, so we won't need to allocate it.
			pActorParams = castEvent.m_pActorParams;
		}
		else
		{
			//Create actor params from the Lua object.
			LuaObject actorDef = castEvent.VGetLuaEventData();

			pActorParams = ActorParams::CreateFromLuaObj( actorDef );

			actorDef.SetInteger("actorID",actorID);
		}

		//Did we get valid actor params?
		if ( NULL == pActorParams )
		{
			assert( 0 && "Invalid parameters specified for actor!" );
			return false;
		}


		pActorParams->m_Id =  actorID;
		const EvtData_New_Actor actorEvent(actorID , pActorParams );
		const bool bSuccess = safeTriggerEvent( actorEvent );
		if ( bCreateEventData )
		{
			SAFE_DELETE( pActorParams );
		}


		LuaObject objects = g_pApp->m_pLuaStateManager->GetGlobalState().Get()->GetGlobal("Objects");
		bool res = objects.IsTable();

		LuaObject model	  = objects[actorID];
		res = model.IsTable();

		LuaObject func	  = model["Init"];
		res = func.IsFunction();

		LuaFunction<void> Init = func;	
		Init(model);

		return bSuccess;
	}

	//New Actor
	else if ( EvtData_New_Actor::sk_EventType == event.VGetEventType() )
	{
		const EvtData_New_Actor & castEvent = static_cast< const EvtData_New_Actor & >( event );
		ActorParams * pActorParams = castEvent.m_pActorParams;

		if ( NULL == pActorParams )
		{
			assert( 0 && "Received a DEBUG_CLIENTBLOCK actor event with NULL actor parameters!" );
			return false;
		}

		pActorParams->VCreate(m_pGame);


		if ( false == castEvent.m_id )
		{
			assert( 0 && "Unable to construct desired actor type!" );
			return false;
		}
		else
		{
			return false;
		}
	}

	//Move Actor
	else if ( EvtData_Move_Actor::sk_EventType == event.VGetEventType() )
	{
		const EvtData_Move_Actor & ed = static_cast< const EvtData_Move_Actor & >( event );
		m_pGame->VMoveActor( ed.m_Id, ed.m_Mat );
	}



	else if ( EvtData_PhysCollision::sk_EventType == event.VGetEventType() )
	{
		const EvtData_PhysCollision & ed = static_cast< const EvtData_PhysCollision & >( event );

		printf("Collision between %i %i\n",ed.m_ActorA,ed.m_ActorB);
	}


	//Set Actor Transform
	else if ( EvtData_SetActorTransform::sk_EventType == event.VGetEventType() )
	{
		const EvtData_SetActorTransform & castEvent = static_cast< const EvtData_SetActorTransform & >( event );
		m_pGame->VSetActorTransform(castEvent.m_Id, castEvent.m_Mat);
	}

	//Set Actor Transform
	else if ( EvtData_Transform_Actor::sk_EventType == event.VGetEventType() )
	{
		const EvtData_Transform_Actor & ed = static_cast< const EvtData_Transform_Actor & >( event );

		shared_ptr<IActor> actor = m_pGame->VGetActor(ed.m_Id);

		if (actor)
			m_pGame->VGetGamePhysics()->VKinematicMove(Mat(ed.m_Mat)*(*actor->VGetMat()),ed.m_Id);
		


/*		m_pGame->VTransformActor(castEvent.m_Id, castEvent.m_Mat);*/
	}

	//OnActorExecution
	else if ( EvtData_RunScript::sk_EventType == event.VGetEventType() )
	{
		const EvtData_RunScript & castEvent = static_cast< const EvtData_RunScript & >( event );
		
		ExecutedScript exeScript;

		exeScript.filename = castEvent.m_filename;

		//stat(exeScript.filename.c_str(), &exeScript.status);

		//m_pGame->m_ExecutedScripts.push_back(exeScript);
	}

	return false;
}