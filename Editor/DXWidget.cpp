#include "main.h"
#include <QMouseEvent>


void DXWidget::keyPressEvent(QKeyEvent* event)
{
	g_pInput->QTKeyDown(event->key());
}

void DXWidget::keyReleaseEvent( QKeyEvent *event )
{
	g_pInput->QTKeyUP(event->key());
}

void DXWidget::mousePressEvent( QMouseEvent * event )
{
	switch(event->button())
	{
	case Qt::MouseButton::LeftButton:
		{
			POINT cursor;
			cursor.x = event->globalX();
			cursor.y = event->globalY();
			oldMousPosX = event->globalX();
			oldMousPosY = event->globalY();
			g_pInput->QtLButton(cursor,true);
			this->setCursor(Qt::BlankCursor);
			break;
		}

	case Qt::MouseButton::RightButton:
		{
			POINT cursor;
			cursor.x = event->globalX();
			cursor.y = event->globalY();
			oldMousPosX = event->globalX();
			oldMousPosY = event->globalY();
			g_pInput->QtRButton(cursor,true);
		}

	case Qt::MouseButton::MiddleButton:
		{
			POINT cursor;
			cursor.x = event->x();
			cursor.y = event->y();
			ClickedMousPosX = event->globalX();
			ClickedMousPosY = event->globalY();
			g_pInput->QtMiddleButton(cursor,true);
		}
	}
	setFocus();	
}

void DXWidget::mouseReleaseEvent( QMouseEvent *event )
{
	switch(event->button())
	{
	case Qt::MouseButton::LeftButton:
		{
			POINT cursor;
			cursor.x = event->x();
			cursor.y = event->y();
			g_pInput->QtLButton(cursor,false);

			//Movment is over. Set the Cursor to the Center of the Widget ( Also set oldMousPos)
			//mapToGlobal gets the absolut coord from a relativ coord in a child widget
			QPoint miPos = this->mapToGlobal( QPoint(0,0) );
			miPos.setX(miPos.x() + this->size().width() / 2);
			miPos.setY(miPos.y() + this->size().height() / 2);

			//Set Cursor Position
			QCursor qcursor;
			qcursor.setPos(miPos);
			qcursor.setShape(Qt::CrossCursor);
			this->setCursor(qcursor);

			//Update OldMousePos
			oldMousPosX = miPos.x();
			oldMousPosY = miPos.y();
			break;
		}

	case Qt::MouseButton::RightButton:
		{
			POINT cursor;
			cursor.x = event->x();
			cursor.y = event->y();
			g_pInput->QtRButton(cursor,false);
			break;
		}

	case Qt::MouseButton::MiddleButton:
		{
			POINT cursor;
			cursor.x = event->x();
			cursor.y = event->y();
			g_pInput->QtMiddleButton(cursor,false);
			OnMButtonUp(event);
		}
	}
	setFocus();	
}

void DXWidget::mouseMoveEvent( QMouseEvent * event )
{
	POINT cursor;
	POINT delta;

	cursor.x = event->globalX();
	cursor.y= event->globalY();

	delta.x = event->globalX() - oldMousPosX;
	delta.y = event->globalY() - oldMousPosY;

	g_pInput->QtMouseMove(cursor, delta);

	oldMousPosX = event->globalX();
	oldMousPosY = event->globalY();	
}

void DXWidget::dragEnterEvent( QDragEnterEvent *event )
{
	char* ValidFileFormats[2] = {"BLOC","bloc"};

	foreach(QUrl url, event->mimeData()->urls())
	{
		QString filename =url.toLocalFile();
		QString suffix = QFileInfo(filename).suffix().toUpper();

		for (unsigned int i = 0; i < 2 ; i++)
		{
			if (suffix == ValidFileFormats[i])
			{
				return event->accept();
			}
		}

	}

	return event->accept();
}

void DXWidget::dropEvent( QDropEvent *event )
{
	foreach(QUrl url, event->mimeData()->urls())
	{
		QString filename =url.toLocalFile();
		QString suffix = QFileInfo(filename).suffix().toUpper();

		if(suffix == "bcx" || suffix == "bcb" || suffix == "BCX" || suffix == "BCB" )
		{
			string file = filename.toStdString();

			for (int i = 0; i < file.length() ; i++)
			{
				if (file[i]=='/')
				{
					file[i] = '\\';
				}
			}

			IEventDataPtr pEvtData = IEventDataPtr(DEBUG_CLIENTBLOCK EvtData_FileDrop( file, event->pos().x(), event->pos().y() ));
			safeQueEvent(pEvtData);
		}
	}
}

void DXWidget::OnLButtonDown( QMouseEvent * event )
{
}

void DXWidget::OnRButtonDown( QMouseEvent * event )
{
}

void DXWidget::OnMButtonDown( QMouseEvent * event )
{
}

void DXWidget::OnLButtonUp( QMouseEvent * event )
{
	IEventDataPtr pEvtData = IEventDataPtr(DEBUG_CLIENTBLOCK EvtData_PerformePick( event->x(),event->y() ));
	safeQueEvent(pEvtData);
}

void DXWidget::OnRButtonUp( QMouseEvent * event )
{

}

void DXWidget::OnMButtonUp( QMouseEvent * event )
{

}

void DXWidget::dragMoveEvent( QDragMoveEvent *event )
{
	string filenames = "";

	foreach(QUrl url, event->mimeData()->urls())
	{
		filenames += url.toLocalFile().toStdString() + "\n";
	}

	IEventDataPtr pEvtData = IEventDataPtr(DEBUG_CLIENTBLOCK EvtData_DragMove( filenames, event->pos().x(),event->pos().y() ));
	safeQueEvent(pEvtData);
}