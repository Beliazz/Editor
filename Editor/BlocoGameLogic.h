#include "main.h"

struct ExecutedScript
{
	string filename;
	struct stat status;
};

typedef std::vector<ExecutedScript> ScriptList;

class BlocoGameLogic : public BaseGameLogic
{
friend class BlocoGameLogicListener;

public:
	BlocoGameLogic(GameOptions const &optionss);
	~BlocoGameLogic()
	{
		while (!m_ActorList.empty())
		{
			ActorMap::iterator i = m_ActorList.begin();
			ActorId aid = (*i).first;
			VRemoveActor(aid);
		}
	}

	void VRemoveActor(ActorId id);
	virtual void GetCameraNode() { }

	//Allows access for script calls.
	LuaObject m_MetaTable;

	//Script accessible functions.
	void SetCameraOffset( LuaObject gameViewIndex, LuaObject offsetTable );

	// Logic Update
	virtual void VOnUpdate(float time, float elapsedTime);

private:
	EventListenerPtr m_pListener;
	ScriptList m_ExecutedScripts;
	shared_ptr<CScriptInput> m_scriptInput;
};


class BlocoGameLogicListener : public IEventListener
{
	BlocoGameLogic *m_pGame;

public:
	explicit BlocoGameLogicListener( BlocoGameLogic *pGame) : m_pGame(pGame){};
	virtual char const * GetName(void) { return "BlocoGameLogicListener"; }
	virtual bool HandleEvent( IEventData const & event );
};
