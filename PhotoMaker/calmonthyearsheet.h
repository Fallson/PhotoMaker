#ifndef CALMONTHYEARSHEET_H
#define CALMONTHYEARSHEET_H

#include <QWidget>
#include "ui_calmonthyearsheet.h"
#include "pmpaperpage.h"

class CalMonthYearSheet : public QWidget
{
	Q_OBJECT

public:
	CalMonthYearSheet(const MONTHYEAR_PROPS &myprops,QWidget *parent = 0);
	~CalMonthYearSheet();

public:
	bool getMonthYearProps(MONTHYEAR_PROPS &monthyearprops);

protected slots:
	void _leftBtnClicked();
	void _hcenterBtnClicked();
	void _rightBtnClicked();
	void _topBtnClicked();
	void _vcenterBtnClicked();
	void _bottomBtnClicked();

private:
	void _init();
	void _initFont();
	void _initSpace();
	void _initColor();

	void _getFont();
	void _getColor();
	void _getSpace();

private:
	Ui::CalMonthYearSheet ui;
	MONTHYEAR_PROPS _myprops;
};

#endif // CALMONTHYEARSHEET_H
