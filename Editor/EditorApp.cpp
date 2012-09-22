#include "main.h"

void EditorApp::VCreateGameAndView()
{
	GameOptions optionss;
	m_pGame = DEBUG_CLIENTBLOCK BlocoGameLogic(optionss);

	shared_ptr<BlocoHumanView> pHumanView = shared_ptr<BlocoHumanView>(DEBUG_CLIENTBLOCK BlocoHumanView());
	
	m_pGame->VAddView(pHumanView);
}
bool EditorApp::VLoadGame()
{
	return m_pGame->VLoadGame("NewGame");
}
void EditorApp::VRegisterEvents()
{

}
void EditorApp::VRegisterScriptFunctions()
{

}
