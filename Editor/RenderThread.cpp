#include <QtGui>
#include <math.h>
#include "QRenderThread.h"
#include "main.h"

RenderThread::RenderThread(QObject *parent) : QThread(parent)
{
	abort = false;
}

RenderThread::~RenderThread()
{

}

void RenderThread::run()
{
	while(!abort) 
	{
		g_pApp->Update();
	}
}

void RenderThread::stop()
{
	mutex.lock();
	abort = true;
	mutex.unlock();
}