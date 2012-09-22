#ifndef Main_h__
#define Main_h__


//#define RAYCAST_ON_DRAGMOVE


#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QTreeView>
#include <QtGui/QDirModel>
#include <QtCore/QDebug>
#include <QtGui/QDrag>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDragMoveEvent>
#include <QtGui/QDragLeaveEvent>
#include "ui_editor.h"
#include "QRenderThread.h"

#include "editor.h"
#include "DXWidget.h"


#include <Bloco.h>
#pragma comment(lib, "Bloco.lib")

#include "BlocoHumanView.h"
#include "BlocoGameLogic.h"
#include "EditorApp.h"

#endif