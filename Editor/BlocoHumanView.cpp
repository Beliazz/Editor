#include "main.h"

void ListenForBlocoGameViewEvents(EventListenerPtr listener)
{
	safeAddListener( listener, EvtData_New_Actor::sk_EventType );
	safeAddListener( listener, EvtData_EneableMovementController::sk_EventType );
	safeAddListener( listener, EvtData_SetMovementController::sk_EventType );
	safeAddListener( listener, EvtData_Wireframe::sk_EventType );
	safeAddListener( listener, EvtData_SetTexture::sk_EventType );
 	safeAddListener( listener, EvtData_Destroy_Actor::sk_EventType );
 	safeAddListener( listener, EvtData_Transform_Actor::sk_EventType );
 	safeAddListener( listener, EvtData_Request_New_Actor::sk_EventType );
	safeAddListener( listener, EvtData_SetActorTransform::sk_EventType );
	safeAddListener( listener, EvtData_PerformePick::sk_EventType );
	safeAddListener( listener, EvtData_Picked_Actor::sk_EventType );
	safeAddListener( listener, EvtData_EnableActor::sk_EventType );
	safeAddListener( listener, EvtData_SetStaticActor::sk_EventType );
	safeAddListener( listener, EvtData_RayCast_Result::sk_EventType );
}

void ListenForBlocoEditorViewEvents(EventListenerPtr listener)
{
	safeAddListener( listener, EvtData_FileDrop::sk_EventType );
	safeAddListener( listener, EvtData_DragMove::sk_EventType );
}

BlocoHumanView::BlocoHumanView() : HumanView()
{
	m_pListener =  EventListenerPtr( DEBUG_CLIENTBLOCK BlocoGameViewListener( this ) );
	ListenForBlocoGameViewEvents(m_pListener);
	ListenForBlocoEditorViewEvents(m_pListener);

	m_pScene.reset(DEBUG_CLIENTBLOCK ScreenElementScene());

	Frustum frustum;
	frustum.Init(D3DX_PI/4.0f, 1.0f, 0.1f, 10000.0f);

	Vec Eye( 0.0f, 100.0f, -300.0f, 1.0f );
	Vec At( 0.0f, 50.0f, 0.0f, 1.0f );
	Vec Up( 0.0f, 1.0f, 0.0f, 1.0f );
	m_pCamera.reset(DEBUG_CLIENTBLOCK CameraNode( optional_empty(), "Camera001" , MatTranslation(Eye),frustum ));
	m_controller.reset(DEBUG_CLIENTBLOCK MovementController(m_pCamera,0.0f,0.0f,true));

	assert(m_pScene && m_pCamera && _T("Out of memory"));

	m_pScene->VAddChild(optional_empty(), m_pCamera);
	m_pScene->SetCamera(m_pCamera);
}

void BlocoHumanView::VOnAttach(GameViewId vid, optional<ActorId> aid)
{
	HumanView::VOnAttach(vid, aid);
	BuildInitialScene();
}

void BlocoHumanView::BuildInitialScene()
{
	VPushElement(m_pScene);
}

void BlocoHumanView::VOnUpdate( int deltaMilliseconds )
{
	HumanView::VOnUpdate( deltaMilliseconds );

	//Send out a tick to script listeners.
	const EvtData_Update_Tick tickEvent( deltaMilliseconds );
	safeTriggerEvent( tickEvent );

	m_controller->OnUpdate(deltaMilliseconds);
}

void BlocoHumanView::VRenderText()
{
	stringstream ss;

	ss << "FPS:            " << (int) g_pApp->GetFPS()<< "\n";

	ss << "DrawTime:   " << (float) g_pApp->GetDrawTime()  * 1000 << "\n";
	ss << "UpdateTime: " << (float) g_pApp->GetUpdateTime()* 1000 << "\n";
	ss << "IdleTime:       " << (float) g_pApp->GetIdleTime()* 1000 << "\r";

	m_pFont->VRender(m_pRenderer->GetContext(), ss.str(), 18, Vec(g_pApp->GetScreenWidth() - 400, 15), Col(1, 1, 1, 1));
}

void BlocoHumanView::VRenderDiagnostic()
{
	g_pApp->m_pGame->VGetGamePhysics()->VRenderDiagnostics(m_pScene.get());
}

void BlocoHumanView::SetActorTransform( ActorId id, Mat mat )
{
	shared_ptr<ISceneNode> node = m_pScene->FindActor(id);
	if (node)
	{
		node->VSetTransform(mat);
	}
}

void BlocoHumanView::TransformActor( ActorId id, Mat mat )
{
	shared_ptr<ISceneNode> node = m_pScene->FindActor(id);
	if (node)
	{
		Mat res = node->VGet()->ToWorld() * mat;
		node->VSetTransform(res);
	}
}

bool BlocoGameViewListener::HandleEvent( IEventData const & event )
{
	//New Actor
	if ( EvtData_New_Actor::sk_EventType == event.VGetEventType() )
		{
			const EvtData_New_Actor & ed = static_cast< const EvtData_New_Actor & >( event );

			shared_ptr<SceneNode> node = ed.m_pActorParams->VCreateSceneNode(m_pView->m_pScene);
			if (node)
			{
				m_pView->m_pScene->VAddChild(ed.m_pActorParams->m_Id, node);
				node->VOnRestore(&(*(m_pView->m_pScene)));
			}
		}

	//Set Actor Transform
	else if ( EvtData_SetActorTransform::sk_EventType == event.VGetEventType() )
	{
		const EvtData_SetActorTransform & ed = static_cast< const EvtData_SetActorTransform & >( event );
		m_pView->SetActorTransform(ed.m_Id, ed.m_Mat);
	}

	//Actor Transform
	else if ( EvtData_Transform_Actor::sk_EventType == event.VGetEventType() )
	{
// 		const EvtData_Transform_Actor & ed = static_cast< const EvtData_Transform_Actor & >( event );
// 		m_pView->TransformActor(ed.m_Id, ed.m_Mat);
	}

	//Destroy Actor
	else if ( EvtData_Destroy_Actor::sk_EventType == event.VGetEventType() )
	{
		const EvtData_Destroy_Actor & castEvent = static_cast< const EvtData_Destroy_Actor & >( event );
		ActorId aid = castEvent.m_id;
		m_pView->m_pScene->RemoveChild(aid);
	}


	//Enable MovementController
	else if (EvtData_EneableMovementController::sk_EventType == event.VGetEventType())
		{
			const EvtData_EneableMovementController & ed = static_cast< const EvtData_EneableMovementController & >( event );

			m_pView->m_pScene->EneableMovementController( ed.m_enable );
		}

	//Set MovementController to a Actor
	else if (EvtData_SetMovementController::sk_EventType == event.VGetEventType())
		{
			const EvtData_SetMovementController & ed = static_cast< const EvtData_SetMovementController & >( event );

			m_pView->m_pScene->SetMovementController( ed.m_id );
		}

	//Render Scene in Wireframe Mode
	else if (EvtData_Wireframe::sk_EventType == event.VGetEventType())
		{
				const EvtData_Wireframe & ed = static_cast< const EvtData_Wireframe & >( event );

				m_pView->m_pRenderer->SetWireframe( ed.m_enable );
		}





	HandleEditorEvent( event );

	return false;
}

bool BlocoGameViewListener::HandleEditorEvent( IEventData const & event )
{
	//Drop File
	if ( EvtData_FileDrop::sk_EventType == event.VGetEventType() )
	{
		const EvtData_FileDrop & ed = static_cast< const EvtData_FileDrop & >( event );



		D3DXMATRIX matProj  = D3DXMATRIX((float*)m_pView->GetAssignedCamera()->GetProjection().GetArray());
		D3DXMATRIX matView  = D3DXMATRIX((float*)m_pView->GetAssignedCamera()->GetView().GetArray());


		// Compute the vector of the pick ray in screen space
		D3DXVECTOR3 v;
		v.x =  ( ( ( 2.0f * ed.m_posX ) / g_pApp->GetWindowWidth()  ) - 1 ) / matProj._11;
		v.y = -( ( ( 2.0f * ed.m_posY ) / g_pApp->GetWindowHeight() ) - 1 ) / matProj._22;
		v.z = 1.0f;

		D3DXMATRIX m;
		D3DXMatrixInverse( &m, NULL, &matView );

		float x,y,z;

		// Transform the screen space pick ray into 3D space
		x = v.x * m._11 + v.y * m._21 + v.z * m._31;
		y = v.x * m._12 + v.y * m._22 + v.z * m._32;
		z = v.x * m._13 + v.y * m._23 + v.z * m._33;

		Vec rayDir = Vec(x,y,z);

		x = m._41;
		y = m._42;
		z = m._43;


		Vec rayOrg = Vec(x,y,z);
		Vec rayEnd = rayOrg+rayDir*m_pView->GetAssignedCamera()->GetFrustum().m_Far;


		bool bHit=false;
		Vec hitpoint = g_pApp->m_pGame->VGetGamePhysics()->VRayCast( rayOrg, rayEnd, bHit);

		if (!bHit)
			hitpoint = Vec(0.0f,0.0f,0.0f);

#ifdef RAYCAST_ON_DRAGMOVE
		m_pView->SetActorTransform(4, MatTranslation(0.0f,0.0f,0.0f));
#endif

		ModelObjectParams* params = DEBUG_CLIENTBLOCK ModelObjectParams(ed.m_filename.c_str(),"simple.fxc","");
		params->m_bHasScript = true;

		string sScriptFileName = ed.m_filename;
		sScriptFileName.erase(sScriptFileName.end()-3,sScriptFileName.end());
		sScriptFileName += "lua";
		strcpy(params->m_sScriptFilename,sScriptFileName.c_str());
		params->m_Mat = MatTranslation(hitpoint);
		
		IEventDataPtr pEvtData = IEventDataPtr(DEBUG_CLIENTBLOCK EvtData_Request_New_Actor(params));
		safeQueEvent(pEvtData);
	}

#ifdef RAYCAST_ON_DRAGMOVE

	//Drop File
	if ( EvtData_DragMove::sk_EventType == event.VGetEventType() )
	{
		const EvtData_DragMove & ed = static_cast< const EvtData_DragMove & >( event );


		D3DXMATRIX matProj  = D3DXMATRIX((float*)m_pView->GetAssignedCamera()->GetProjection().GetArray());
		D3DXMATRIX matView  = D3DXMATRIX((float*)m_pView->GetAssignedCamera()->GetView().GetArray());


		// Compute the vector of the pick ray in screen space
		D3DXVECTOR3 v;
		v.x =  ( ( ( 2.0f * ed.m_posX ) / g_pApp->GetWindowWidth()  ) - 1 ) / matProj._11;
		v.y = -( ( ( 2.0f * ed.m_posY ) / g_pApp->GetWindowHeight() ) - 1 ) / matProj._22;
		v.z = 1.0f;

		D3DXMATRIX m;
		D3DXMatrixInverse( &m, NULL, &matView );

		float x,y,z;

		// Transform the screen space pick ray into 3D space
		x = v.x * m._11 + v.y * m._21 + v.z * m._31;
		y = v.x * m._12 + v.y * m._22 + v.z * m._32;
		z = v.x * m._13 + v.y * m._23 + v.z * m._33;

		Vec rayDir = Vec(x,y,z);

		x = m._41;
		y = m._42;
		z = m._43;


		Vec rayOrg = Vec(x,y,z);
		Vec rayEnd = rayOrg+rayDir*m_pView->GetAssignedCamera()->GetFrustum().m_Far;


		bool bHit=false;
		Vec hitpoint = g_pApp->m_pGame->VGetGamePhysics()->VRayCast( rayOrg, rayEnd, bHit);

		if (!bHit)
			hitpoint = Vec(0.0f,0.0f,0.0f);

		m_pView->SetActorTransform(4, MatTranslation(hitpoint));
	}

#endif

	return true;
}

