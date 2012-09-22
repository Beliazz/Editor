#ifndef FileBrowser_H__
#define FileBrowser_H__

#include <QtGui/QDockWidget>
#include <QtCore/QUrl>
#include <QtCore/QFileInfo>
#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QTreeView>
#include <QtGui/QDirModel>
#include <QtCore/QDebug>
#include <QtGui/QDrag>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDragMoveEvent>
#include <QtGui/QDragLeaveEvent>


class FileBrowser : public QTreeView
{
	Q_OBJECT
public:
	 FileBrowser(QWidget * parent = NULL);
	~FileBrowser();


	void SetDirectory( QString path);

protected:
	void keyPressEvent(QKeyEvent* event);

	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);  

private:
	QDirModel* m_pDirModel;
	QModelIndex m_index;

	QString m_dropedFilename;
	bool m_droped;
};

#endif //DXWidget_H__