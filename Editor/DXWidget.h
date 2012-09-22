#ifndef DXWidget_H__
#define DXWidget_H__

#include <QtGui/QDockWidget>
#include <QPaintEngine>
#include <QtCore/QUrl>
#include <QtCore/QFileInfo>
#include "QRenderThread.h"

#include <QtGui/QDragEnterEvent>
#include <QtGui/QDragMoveEvent>
#include <QtGui/QDragLeaveEvent>

class DXWidget : public QWidget
{
	Q_OBJECT
public:
	 DXWidget(QWidget * parent = NULL) : QWidget(parent)
	{     
 		setAttribute(Qt::WA_NativeWindow, true); 
 		setAttribute(Qt::WA_PaintOnScreen, true);

		setAcceptDrops(TRUE);

		oldMousPosX = 0;
		oldMousPosY = 0;

	}
	~DXWidget()
	{
	}


protected:
	QPaintEngine *paintEngine() const { return 0; }

	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent *event);

	void mousePressEvent( QMouseEvent * event );
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent( QMouseEvent * event );	

	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);

	void OnLButtonDown(QMouseEvent * event);
	void OnRButtonDown(QMouseEvent * event);
	void OnMButtonDown(QMouseEvent * event);

	void OnLButtonUp(QMouseEvent * event);
	void OnRButtonUp(QMouseEvent * event);
	void OnMButtonUp(QMouseEvent * event);


	//bool winEvent(MSG* message, long* result);

	unsigned int oldMousPosX;
	unsigned int oldMousPosY;

	unsigned int ClickedMousPosX;
	unsigned int ClickedMousPosY;
};
#endif //DXWidget_H__