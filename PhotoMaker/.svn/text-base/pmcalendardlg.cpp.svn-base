#include "pmcalendardlg.h"
#include "calendarpropsheet.h"
#include "calweekdaysheet.h"
#include "calmonthyearsheet.h"
#include "photomaker.h"

PmCalendarDlg::PmCalendarDlg(const CALENDAR_CFG &calcfg,PhotoMaker *pMainFrame, QWidget *parent)
	: QDialog(parent), _forall(false), _pMainFrame(pMainFrame)
{
	ui.setupUi(this);
    setWindowIcon(QIcon("Resources\\images\\AppIcon.ico"));

	_calpage = new CalendarPropSheet(calcfg.calcfg);
	_calpage->setObjectName(QString::fromUtf8("Calendar"));
	ui.tabCalendar->addTab(_calpage, QString(tr("Calendar")));

	_wdpage = new CalWeekDaySheet(calcfg.wdcfg);
	_wdpage->setObjectName(QString::fromUtf8("WeekDays"));
	ui.tabCalendar->addTab(_wdpage, QString(tr("Week Days")));

	_mypage = new CalMonthYearSheet(calcfg.monthyearcfg);
	_mypage->setObjectName(QString::fromUtf8("MonthYear"));
	ui.tabCalendar->addTab(_mypage, QString(tr("Month & Year")));


	//tab_2 = new QWidget();
	//tab_2->setObjectName(QString::fromUtf8("tab_2"));
	//tabCalendar->addTab(tab_2, QString());

	connect(ui.btnApply, SIGNAL(clicked()), SLOT(onApply()));
	connect(ui.btnOkAll, SIGNAL(clicked()), SLOT(onOkAll()));
	connect(ui.btnOk, SIGNAL(clicked()), SLOT(onOk()));
	connect(ui.btnCancel, SIGNAL(clicked()), SLOT(onCancel()));

}

PmCalendarDlg::~PmCalendarDlg()
{

}

bool PmCalendarDlg::getCalendarCfg(CALENDAR_CFG &calendarcfg)
{
	calendarcfg.forall = _forall;
	if ( ! _calpage->getCalProps(calendarcfg.calcfg) )
	{
		return false;
	}
	if ( ! _wdpage->getWeekdaysPorps(calendarcfg.wdcfg) )
	{
		return false;
	}
	if ( ! _mypage->getMonthYearProps(calendarcfg.monthyearcfg) )
	{
		return false;
	}

	return true;
}


void PmCalendarDlg::onOkAll()
{
	accept();

	_forall = true;
	
	emit close();

   //Todo list
}

void PmCalendarDlg::onOk()
{
	accept();

	_forall = false;

	emit close();
}

void PmCalendarDlg::onApply()
{
    //emit finished(QDialog::Accepted);
    //Todo list

	// accpt is same as onok, except it does not close the dialog
	_forall = false;

	if ( _pMainFrame )
	{
		CALENDAR_CFG calendaritmscfg;

		bool ret = getCalendarCfg(calendaritmscfg);
		if ( !ret )
		{
			return ;
		}

		// 
		_pMainFrame->updateCalCfg(calendaritmscfg);
	}
}

void PmCalendarDlg::onCancel()
{
	reject();
	emit close();
}
