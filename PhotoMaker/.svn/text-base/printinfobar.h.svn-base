#ifndef PRINTINFOBAR_H
#define PRINTINFOBAR_H

#include <QWidget>
#include "ui_printinfobar.h"

class PrintInfoBar : public QWidget
{
	Q_OBJECT

public:
	PrintInfoBar(QWidget *parent = 0);
	~PrintInfoBar();

public:
	void showInfo(const QString &info);

Q_SIGNALS:
	void cancel();

private slots:
	void onCancel();

private:
	Ui::PrintInfoBar ui;
};

#endif // PRINTINFOBAR_H
