#include "main.h"

int main(int argc, char *argv[])
{
	EditorApp	 app(&g_pApp);
	QApplication a(argc,argv);
	Editor		 w;
		
	if (!g_pApp->Init("Editor", 1600, 900, true,w.GetRenderWindow()))
	{
		system("PAUSE");
		g_pApp->Exit();
		return 1;
	}

	w.show();
	g_pApp->Run();
	g_pApp->Exit();

	return 0;
}
