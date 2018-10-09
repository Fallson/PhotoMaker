#ifndef CALENDARPROPSHEET_H
#define CALENDARPROPSHEET_H

#include <QWidget>
#include "ui_calendarpropsheet.h"
#include "pmpaperpage.h"

class CalendarPropSheet : public QWidget
{
	Q_OBJECT

public:
	CalendarPropSheet(const CAL_PROPS &calprops, QWidget *parent = 0);
	~CalendarPropSheet();

public:
	bool getCalProps(CAL_PROPS &calprops);


protected slots:
	void _leftBtnClicked();
	void _hcenterBtnClicked();
	void _rightBtnClicked();
	void _topBtnClicked();
	void _vcenterBtnClicked();
	void _bottomBtnClicked();
	void _wdcolorSelChanged(int curindex);
	void _wdcolorChanged(int curindex);

private:
	void _init();
	void _initFont();
	void _initSpace();
	void _initColor();

	void _getFont();
	void _getSpace();
	void _getColor();

private:
	Ui::CalendarPropSheet ui;

	CAL_PROPS _calprops;
};

#endif // CALENDARPROPSHEET_H
