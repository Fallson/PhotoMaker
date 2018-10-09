#ifndef RESPUBLISHER_H
#define RESPUBLISHER_H

#include <QtGui/QMainWindow>
#include "ui_respublisher.h"

class ResPublisher : public QMainWindow
{
	Q_OBJECT

public:
	ResPublisher(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ResPublisher();

protected slots:
	void OnGenerateResData();
	void OnBrowse();

private:
	Ui::ResPublisherClass ui;
};

#endif // RESPUBLISHER_H
