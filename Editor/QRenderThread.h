#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>


class RenderThread : public QThread
{
	Q_OBJECT

public:
	RenderThread(QObject *parent = 0);
	~RenderThread();

	void stop();

signals:
	void UpdateTick();

protected:
	void run();

private:
	QMutex mutex;
	bool abort;
};

#endif