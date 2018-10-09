#ifndef PMPRINTSEAMAUTO1_H
#define PMPRINTSEAMAUTO1_H

#include <QDialog>
#include "ui_pmprintseamauto1.h"
#include <QPrinterInfo>

class PmPrintSeamAuto1 : public QDialog
{
	Q_OBJECT

public:
	PmPrintSeamAuto1(const QPrinterInfo &printerinfo,const QString &printername, QWidget *parent = 0);
	~PmPrintSeamAuto1();

protected slots:
	void OnPrint();
	void OnPrintProps();

private:
	void _print();


private:
	Ui::PmPrintSeamAuto1 ui;

	QString _printername;
	QPrinterInfo _printerinfo;
};

#endif // PMPRINTSEAMAUTO1_H
