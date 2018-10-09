#ifndef PMPRINTSEAMAUTO3_H
#define PMPRINTSEAMAUTO3_H

#include <QDialog>
#include "ui_pmprintseamauto3.h"

class PmPrintSeamAuto3 : public QDialog
{
	Q_OBJECT

public:
	PmPrintSeamAuto3(QWidget *parent = 0);
	~PmPrintSeamAuto3();

public:
	bool getCalibrationNo(int &no);

protected slots:
	void OnFinish();


private:
	Ui::PmPrintSeamAuto3 ui;

	QString _calibrationNo;
};

#endif // PMPRINTSEAMAUTO3_H
