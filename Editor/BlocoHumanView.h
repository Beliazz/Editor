#include "main.h"


class BlocoHumanView : public HumanView
{
	friend class BlocoGameViewListener;

private:
	EventListenerPtr m_pListener;
	shared_ptr<ScreenElementScene> m_pScene;		
	shared_ptr<CameraNode> m_pCamera;
	shared_ptr<MovementController> m_controller;

	Label* m_pInfoLabel;

	void VOnAttach(GameViewId vid, optional<ActorId> aid);
	virtual void VRenderText();



public:
	BlocoHumanView();

	virtual void VRenderDiagnostic();

	void SetActorTransform( ActorId id, Mat mat );
	void TransformActor( ActorId id, Mat mat );
	void BuildInitialScene();
	shared_ptr<ICamera> GetAssignedCamera() { return m_pScene->GetCamera(); }
	virtual void VOnUpdate(int deltaMilliseconds);
	
};


class BlocoGameViewListener : public IEventListener
{
	BlocoHumanView *m_pView;

public:
	explicit BlocoGameViewListener( BlocoHumanView *pView) : m_pView(pView){};
	virtual char const * GetName(void) { return "BlocoGameViewListener"; }
	virtual bool HandleEvent( IEventData const & event );
	virtual bool HandleEditorEvent( IEventData const & event );
};

