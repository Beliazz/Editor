#ifndef EDITOR_H
#define EDITOR_H

#include "main.h"

class Editor : public QMainWindow
{
	Q_OBJECT

public:
	HWND GetRenderWindow();
	Editor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Editor();

	void StartEngine();

public slots:
	void PausePhysics();
	void RunScript();

private:
	void closeEvent(QCloseEvent *);

	Ui::EditorClass ui;

	RenderThread m_renderThread;
};

#endif // EDITOR_H
