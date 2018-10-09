#include "printinfobar.h"

PrintInfoBar::PrintInfoBar(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(onCancel()));

	this->setWindowFlags( Qt::WindowStaysOnTopHint/*|Qt::FramelessWindowHint*/);
	ui.lbInfo->setAlignment(Qt::AlignHCenter);
}

PrintInfoBar::~PrintInfoBar()
{

}


void PrintInfoBar::showInfo(const QString &info)
{
	QString lbtxt;
	//lbtxt += QString("<h2><font color=red>");
	lbtxt += info;
	//lbtxt +=  "</font></h2>";

	ui.lbInfo->setText(lbtxt);
}

void PrintInfoBar::onCancel()
{
	emit cancel();
}

