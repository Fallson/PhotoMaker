#ifndef PMCALENDARDLG_H
#define PMCALENDARDLG_H

#include <QDialog>
#include "ui_pmcalendardlg.h"
#include "pmpaperpage.h"

class CalendarPropSheet;
class CalWeekDaySheet;
class CalMonthYearSheet;

class PhotoMaker;
class PmCalendarDlg : public QDialog
{
	Q_OBJECT

public:
	PmCalendarDlg(const CALENDAR_CFG &calcfg,PhotoMaker *pMainFrame=NULL, QWidget *parent = 0);
	~PmCalendarDlg();

public:
	bool getCalendarCfg(CALENDAR_CFG &calendarcfg);

protected slots:
	void onOkAll();
	void onOk();
	void onApply();
	void onCancel();
private:
	Ui::PmCalendarDlg ui;

	CalendarPropSheet *_calpage;
	CalWeekDaySheet *_wdpage;
	CalMonthYearSheet *_mypage;

	bool _forall;

	PhotoMaker *_pMainFrame; 
};

#endif // PMCALENDARDLG_H
