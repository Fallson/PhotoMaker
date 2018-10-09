#ifndef PMCALENDAREDIT_H
#define PMCALENDAREDIT_H

#include <QWidget>
#include "ui_pmcalendaredit.h"

class PhotoMaker;
class PmCalendarEdit : public QWidget
{
	Q_OBJECT

public:
	PmCalendarEdit(PhotoMaker *pMainFrame, QWidget *parent = 0);
	~PmCalendarEdit();

protected slots:
	void firstMonthChanged(int value);
	void increaseYear();
	void decreaseYear();
	void calendarPropSet();

private:
	Ui::PmCalendarEdit ui;

	PhotoMaker *_pMainFrame;
	
	int _year;

};

#endif // PMCALENDAREDIT_H
