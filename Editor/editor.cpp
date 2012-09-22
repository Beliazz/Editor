#include "main.h"
#include "QtGui/QFileDialog"

Editor::Editor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	QString dataDir = QString(getenv("BLOCO_HOME")) + "\\Editor\\Win32\\Debug\\data";

	ui.treeView_2->SetDirectory(dataDir);
}

Editor::~Editor()
{
}

void Editor::StartEngine()
{
// 	g_pApp->Run();
// 	m_renderThread.start();
}

void Editor::PausePhysics()
{
	IEventDataPtr pauseEvent = IEventDataPtr(DEBUG_CLIENTBLOCK EvtData_Phys_TogglePause());
	safeQueEvent(pauseEvent);
}

void Editor::RunScript()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"C:\\Users\\Mathias\\Documents\\GitHub\\Editor\\Win32\\Debug\\data\\script",tr("Files (*.*)"));

	for (int i = 0; i < fileName.length() ; i++)
	{
		if (fileName[i] == '/')
			fileName[i] = '\\';
	}

	g_pApp->RunScript(fileName.toStdString().c_str());
}

void Editor::closeEvent( QCloseEvent * closeEvt)
{
	g_pApp->AbortGame();

	QMainWindow::closeEvent(closeEvt);
}

HWND Editor::GetRenderWindow()
{
	return ui.RenderWindow1->winId();
}
