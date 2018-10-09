#ifndef CALWEEKDAYSHEET_H
#define CALWEEKDAYSHEET_H

#include <QWidget>
#include "ui_calweekdaysheet.h"
#include "pmpaperpage.h"

class CalWeekDaySheet : public QWidget
{
	Q_OBJECT

public:
	CalWeekDaySheet(const WEEKDAY_PROPS &wdprops,QWidget *parent = 0);
	~CalWeekDaySheet();

public:
	bool getWeekdaysPorps(WEEKDAY_PROPS &wdprops);

protected slots:
	void _leftBtnClicked();
	void _hcenterBtnClicked();
	void _rightBtnClicked();
	void _topBtnClicked();
	void _vcenterBtnClicked();
	void _bottomBtnClicked();

private:
	void _setupUI();
	void _initFont();
	void _initColor();
	void _initSpace();
	void _init();

	void _getFont();
	void _getColor();
	void _getSpace();

private:
	Ui::CalWeekDaySheet ui;

	WEEKDAY_PROPS _wdprops;
};

#endif // CALWEEKDAYSHEET_H
