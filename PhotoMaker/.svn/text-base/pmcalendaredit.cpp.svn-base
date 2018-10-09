#include "pmcalendaredit.h"
#include "photomaker.h"
#include "pmpaperpage.h"
#include "PmCalendarDlg.h"

PmCalendarEdit::PmCalendarEdit(PhotoMaker *pMainFrame, QWidget *parent)
	: QWidget(parent),_pMainFrame(pMainFrame), _year(2012)
{
	ui.setupUi(this);
	ui.cbFirstMonth->addItem(tr("January"));
	ui.cbFirstMonth->addItem(tr("February"));
	ui.cbFirstMonth->addItem(tr("March"));
	ui.cbFirstMonth->addItem(tr("April"));
	ui.cbFirstMonth->addItem(tr("May"));
	ui.cbFirstMonth->addItem(tr("June"));
	ui.cbFirstMonth->addItem(tr("July"));
	ui.cbFirstMonth->addItem(tr("August"));
	ui.cbFirstMonth->addItem(tr("September"));
	ui.cbFirstMonth->addItem(tr("October"));
	ui.cbFirstMonth->addItem(tr("November"));
	ui.cbFirstMonth->addItem(tr("December"));

	if ( _pMainFrame )
	{
		PROJ_PROPS proj;
		_pMainFrame->getDoc()->getProjProps(proj);
		this->_year = proj.year;
		QString yearlb = QString(tr("Year <b>%1</b>")).arg(_year);
		ui.lbYear->setText(yearlb);
	}

	connect(ui.cbFirstMonth, SIGNAL(currentIndexChanged (int )), this, SLOT(firstMonthChanged(int)));
	connect(ui.btnIncress, SIGNAL(clicked()), this, SLOT(increaseYear()));
	connect(ui.btnDecrease, SIGNAL(clicked()), this, SLOT(decreaseYear()));
	connect(ui.btnCalendarPorps, SIGNAL(clicked()), this, SLOT(calendarPropSet()));
}

PmCalendarEdit::~PmCalendarEdit()
{

}

void PmCalendarEdit::firstMonthChanged(int value)
{
	//
	if ( !_pMainFrame )
	{
		return ;
	}
	PmPhotoMakerDoc *pDoc = _pMainFrame->getDoc();
	PROJ_PROPS proj;
	pDoc->getProjProps(proj);
	if ( proj.type != PROJ_PROPS::CALENDARA4 && 
		proj.type != PROJ_PROPS::CALENDARA5 && 
		proj.type != PROJ_PROPS::CALENDAR4X6 )
	{
		//
		return ;
	}

	_pMainFrame->updateFirstCalMonth(value+1);
}


void PmCalendarEdit::increaseYear()
{

	//updateProjProps
	PmPhotoMakerDoc *pDoc = _pMainFrame->getDoc();

	PROJ_PROPS proj;
	pDoc->getProjProps(proj);
	if ( proj.type != PROJ_PROPS::CALENDARA4 && 
		proj.type != PROJ_PROPS::CALENDARA5 && 
		proj.type != PROJ_PROPS::CALENDAR4X6 )
	{
		//
		return ;
	}
	_year++;

	_pMainFrame->updateCalYear(_year);

	QString yearLabel =  QString(tr("Year <b>%1</b>")).arg(_year);
	ui.lbYear->setText(yearLabel);

}

void PmCalendarEdit::decreaseYear()
{
	PmPhotoMakerDoc *pDoc = _pMainFrame->getDoc();

	PROJ_PROPS proj;
	pDoc->getProjProps(proj);
	if ( proj.type != PROJ_PROPS::CALENDARA4 && 
		proj.type != PROJ_PROPS::CALENDARA5 && 
		proj.type != PROJ_PROPS::CALENDAR4X6 )
	{
		//
		return ;
	}
	_year--;
	_pMainFrame->updateCalYear(_year);

	QString yearLabel =  QString(tr("Year <b>%1</b>")).arg(_year);
	ui.lbYear->setText(yearLabel);
}

void PmCalendarEdit::calendarPropSet()
{
	CALENDAR_CFG calendaritmscfg;
	if ( !_pMainFrame->getSelCalCfg(calendaritmscfg) )
	{
		return ;
	}

	PmCalendarDlg dlg(calendaritmscfg, _pMainFrame);
	if ( QDialog::Accepted != dlg.exec() )
	{
		return ;
	}
	// update calendar property
	bool ret = dlg.getCalendarCfg(calendaritmscfg);
	if ( !ret )
	{
		return ;
	}

	// 
	this->_pMainFrame->updateCalCfg(calendaritmscfg);

}