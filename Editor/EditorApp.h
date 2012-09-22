#ifndef EditorApp_h__
#define EditorApp_h__

#include "main.h"

class EditorApp : public Application
{
public:
	EditorApp(Application** ppApp) : Application(ppApp) { }

	virtual LPWSTR			VGetGameTitle()		     { return L"Editor"; }
	virtual HICON			VGetIcon()				 { return NULL; }
	virtual LPWSTR			VGetGameAppDirectory()	 { return L"Editor";}
	virtual void			VCreateGameAndView();
	virtual bool			VLoadGame();
	virtual void			VRegisterEvents();
	virtual void			VRegisterScriptFunctions();
};

#endif // BlocoApp_h__