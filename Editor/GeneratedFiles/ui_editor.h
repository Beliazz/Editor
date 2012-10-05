/********************************************************************************
** Form generated from reading UI file 'editor.ui'
**
** Created: Fri 5. Oct 21:47:13 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITOR_H
#define UI_EDITOR_H

#include <FileBrowser.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <dxwidget.h>

QT_BEGIN_NAMESPACE

class Ui_EditorClass
{
public:
    QAction *actionPause;
    QAction *actionRun;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuPhysic;
    QMenu *menuScript;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout;
    FileBrowser *treeView_2;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents_2;
    QHBoxLayout *horizontalLayout_2;
    DXWidget *RenderWindow1;

    void setupUi(QMainWindow *EditorClass)
    {
        if (EditorClass->objectName().isEmpty())
            EditorClass->setObjectName(QString::fromUtf8("EditorClass"));
        EditorClass->resize(1158, 704);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(EditorClass->sizePolicy().hasHeightForWidth());
        EditorClass->setSizePolicy(sizePolicy);
        EditorClass->setBaseSize(QSize(0, 0));
        EditorClass->setAcceptDrops(true);
        actionPause = new QAction(EditorClass);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        actionPause->setCheckable(true);
        actionPause->setChecked(true);
        actionRun = new QAction(EditorClass);
        actionRun->setObjectName(QString::fromUtf8("actionRun"));
        centralWidget = new QWidget(EditorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        EditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EditorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1158, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuPhysic = new QMenu(menuBar);
        menuPhysic->setObjectName(QString::fromUtf8("menuPhysic"));
        menuScript = new QMenu(menuBar);
        menuScript->setObjectName(QString::fromUtf8("menuScript"));
        EditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EditorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        EditorClass->addToolBar(Qt::LeftToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EditorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        EditorClass->setStatusBar(statusBar);
        toolBar = new QToolBar(EditorClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        EditorClass->addToolBar(Qt::TopToolBarArea, toolBar);
        dockWidget_3 = new QDockWidget(EditorClass);
        dockWidget_3->setObjectName(QString::fromUtf8("dockWidget_3"));
        dockWidget_3->setMinimumSize(QSize(200, 111));
        dockWidget_3->setAcceptDrops(true);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        treeView_2 = new FileBrowser(dockWidgetContents);
        treeView_2->setObjectName(QString::fromUtf8("treeView_2"));
        treeView_2->setAcceptDrops(true);
        treeView_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(treeView_2);

        dockWidget_3->setWidget(dockWidgetContents);
        EditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_3);
        dockWidget = new QDockWidget(EditorClass);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        horizontalLayout_2 = new QHBoxLayout(dockWidgetContents_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        RenderWindow1 = new DXWidget(dockWidgetContents_2);
        RenderWindow1->setObjectName(QString::fromUtf8("RenderWindow1"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(RenderWindow1->sizePolicy().hasHeightForWidth());
        RenderWindow1->setSizePolicy(sizePolicy1);
        RenderWindow1->setMinimumSize(QSize(800, 600));
        RenderWindow1->setMaximumSize(QSize(9999999, 9999999));
        RenderWindow1->setCursor(QCursor(Qt::CrossCursor));

        horizontalLayout_2->addWidget(RenderWindow1);

        dockWidget->setWidget(dockWidgetContents_2);
        EditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuPhysic->menuAction());
        menuBar->addAction(menuScript->menuAction());
        menuPhysic->addAction(actionPause);
        menuScript->addAction(actionRun);
        toolBar->addAction(actionPause);
        toolBar->addAction(actionRun);

        retranslateUi(EditorClass);
        QObject::connect(actionPause, SIGNAL(toggled(bool)), EditorClass, SLOT(PausePhysics()));
        QObject::connect(actionRun, SIGNAL(triggered()), EditorClass, SLOT(RunScript()));

        QMetaObject::connectSlotsByName(EditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *EditorClass)
    {
        EditorClass->setWindowTitle(QApplication::translate("EditorClass", "Editor", 0, QApplication::UnicodeUTF8));
        actionPause->setText(QApplication::translate("EditorClass", "Pause", 0, QApplication::UnicodeUTF8));
        actionRun->setText(QApplication::translate("EditorClass", "Run", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("EditorClass", "File", 0, QApplication::UnicodeUTF8));
        menuPhysic->setTitle(QApplication::translate("EditorClass", "Physic", 0, QApplication::UnicodeUTF8));
        menuScript->setTitle(QApplication::translate("EditorClass", "Script", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("EditorClass", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EditorClass: public Ui_EditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITOR_H
