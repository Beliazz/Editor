#ifndef __QTFileBrowser_H
#define __QTFileBrowser_H

#include <main.h>
#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QTreeView>
#include <QtGui/QDirModel>
#include <QtCore/QDebug>
#include <QtGui/QDrag>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDragMoveEvent>
#include <QtGui/QDragLeaveEvent>

class xx : public QTreeView
{
	Q_OBJECT

public:
	xx( QWidget *parent = NULL ){}
	~xx(){}
};

class QFileBrowser : public QTreeView
{
	Q_OBJECT

public:
	QFileBrowser( QWidget *parent = NULL );
	~QFileBrowser();

// 	void SetDirectory( QString path);
// 
// protected:
// 	void keyPressEvent(QKeyEvent* event);
// 
// 	void dragEnterEvent(QDragEnterEvent *event);
// 	void dropEvent(QDropEvent *event);  
// 
// private:
// 	QDirModel* m_pDirModel;
// 	QModelIndex m_index;
// 
// 	QString m_dropedFilename;
// 	bool m_droped;
};

#endif