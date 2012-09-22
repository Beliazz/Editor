#include "main.h"

QFileBrowser::QFileBrowser( QWidget *parent /*= NULL */ ):
	QTreeView(parent)
{
// 	m_pDirModel = new QDirModel(parent);
// 	m_pDirModel->setReadOnly(false);
// 	m_pDirModel->setSorting(QDir::DirsFirst);
// 	
// 	setModel(m_pDirModel);
}

QFileBrowser::~QFileBrowser()
{

}

// void QFileBrowser::SetDirectory( QString path )
// {
// 	m_index =  m_pDirModel->index(path);
// 	setRootIndex(m_index);
// 	expand(m_index);
// 	resizeColumnToContents(0);
// }
// 
// void QFileBrowser::dragEnterEvent( QDragEnterEvent *event )
// {
// 	event->accept();
// }
// 
// 
// void QFileBrowser::dropEvent( QDropEvent *event )
// {
// 		//Simulate Mouse Click to select the row
// 		QMouseEvent* mouseEvent = new QMouseEvent((QEvent::MouseButtonPress),event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
// 		this->mousePressEvent(mouseEvent);
// 
// 		//Get the selectet Index
// 		QModelIndex index	 = this->selectionModel()->selectedIndexes()[0];
// 		QString		filepath = m_pDirModel->filePath(index);
// 
// 
// 		//Check if its a file or a directory
// 		if(  m_pDirModel->fileInfo(index).isFile() )
// 		{
// 			//Its a file! Get the upper dir.
// 			int i;
// 			for (i = filepath.size() - 1; i >= 0 ; i--)
// 			{
// 				if ( filepath[i] == '/' )
// 					break;
// 			}
// 
// 			filepath.resize(i+1);
// 		}
// 		else
// 		{
// 			//Its a direcetory Add the'/' to the filepath
// 			if ( filepath[filepath.size()-1] != '/' )
// 				filepath.append('/');
// 		}	
// 
// 
// 	foreach(QUrl url, event->mimeData()->urls())
// 	{
// 		QString filename = url.toLocalFile();
// 		QString newFileName = filepath;
// 
// 		int i;
// 		for (i = filename.size() - 1; i >= 0 ; i--)
// 		{
// 			if ( filename[i] == '/' )
// 				break;
// 
// 			newFileName.insert(filepath.length(),filename[i]);
// 		}
// 
// 		if(!QFile(filename).copy(newFileName))
// 		{
// 			qDebug() << "Error oping the file";
// 		}
// 	}
// 
// 	m_pDirModel->refresh();
// 	this->setModel(m_pDirModel);
// }
// 
// void QFileBrowser::keyPressEvent( QKeyEvent* event )
// {
// 	if(event->key() & Qt::Key_Delete)
// 	{
// 		QModelIndex index = currentIndex();
// 		if(!index.isValid()) return;
// 
// 		//Check if its a file or a directory
// 		if(  m_pDirModel->fileInfo(index).isDir() )
// 		{
// 			//Dir
// 			m_pDirModel->rmdir(index);
// 		}
// 		else
// 		{
// 			//File
// 			m_pDirModel->remove(index);
// 		}
// 
// 	}
// 
// 	QTreeView::keyPressEvent(event);
// }
