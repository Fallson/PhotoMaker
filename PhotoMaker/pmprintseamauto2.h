#ifndef PMPRINTSEAMAUTO2_H
#define PMPRINTSEAMAUTO2_H

#include <QDialog>
#include "ui_pmprintseamauto2.h"
#include <QPrinterInfo>

class PmPrintSeamAuto2 : public QDialog
{
	Q_OBJECT

public:
	PmPrintSeamAuto2(const QPrinterInfo &printerinfo,const QString &printername,QWidget *parent = 0);
	~PmPrintSeamAuto2();

protected slots:
	void OnPrint();
	void OnPrintProps();

private:
	void _print();

private:
	Ui::PmPrintSeamAuto2 ui;

private:
	QString _printername;
	QPrinterInfo _printerinfo;
};

#endif // PMPRINTSEAMAUTO2_H
