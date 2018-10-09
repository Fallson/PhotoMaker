#ifndef PMPRINTSEAMDLG_H
#define PMPRINTSEAMDLG_H

#include <QDialog>
#include "ui_pmprintseamdlg.h"
#include <QPrinterInfo>

class PmPrintSeamDlg : public QDialog
{
	Q_OBJECT

public:
	PmPrintSeamDlg(const QPrinterInfo &printerinfo, const QString &printername, QWidget *parent = 0);
	~PmPrintSeamDlg();

public:
	bool getCalibrationNo(int &calibrationNo);
	bool setCalibrationNo(int calibrationNo);

protected slots:
	void OnAutoAdjust();
	void OnDesc();
	void OnInc();
	void OnOK();
	void OnCancel();

private:
	void _adjustCalibrationLabel();

private:
	Ui::PmPrintSeamDlg ui;
	QString _printername;
	QPrinterInfo _printerinfo;
	int _calibrationNo;
};

#endif // PMPRINTSEAMDLG_H
