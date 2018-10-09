#pragma once

#include <QList>
#include <QString>
#include "pmphotomakerdoc.h"



typedef enum{PP_FORMAT_PB4X3, PP_FORMAT_PB10X15,PP_FORMAT_SINGLE4X6,PP_FORMAT_PB8X5,
	PP_FORMAT_CALENDAR_A4,PP_FORMAT_CALENDAR_A5,PP_FORMAT_CALENDAR_4X6,
	PP_LAYOUT_FULLSIZE, PP_LAYOUT_BORDER, 
	PP_LAYOUT_PB8X5, PP_LAYOUT_PB8X5_BORDERLESS,
	PP_LAYOUT_PB8X5_FULLSIZE, PP_LAYOUT_PB8X5_TRADITION, PP_LAYOUT_PB8X5_HORIZON, PP_LAYOUT_PB8X5_VERTICON,
	PP_LAYOUT_CALENDAR_A4_L1_NAME, PP_LAYOUT_CALENDAR_A4_L2_NAME,PP_LAYOUT_CALENDAR_A4_L3_NAME, PP_LAYOUT_CALENDAR_A4_L4_NAME,
	PP_LAYOUT_CALENDAR_A5_L1_NAME, PP_LAYOUT_CALENDAR_A5_L2_NAME,PP_LAYOUT_CALENDAR_A5_L3_NAME,
	PP_LAYOUT_CALENDAR_4X6_L1_NAME, PP_LAYOUT_CALENDAR_4X6_L2_NAME,PP_LAYOUT_CALENDAR_4X6_L3_NAME, PP_LAYOUT_CALENDAR_4X6_L4_NAME,
	PP_CALENDAR_YEAR
}PHOTO_PRINT_DIR_NAME;

class PpPrjWizardPage;
typedef struct _PRJ_DIR_ITM
{
	QString name;
	QString iconPath;
	QString showPicPath;
	PHOTO_PRINT_DIR_NAME dirtype;
	PpPrjWizardPage *nextPage;
	int index;
}PRJ_DIR_ITM, *PPRJ_DIR_ITM;

class PhotoPrintPrjModel;
class PpPrjWizardPage
{
public:
	PpPrjWizardPage(){}
	virtual ~PpPrjWizardPage(){}

public:
	virtual bool HasPrePage() = 0;
	virtual bool HasNextPage() = 0;
	virtual bool getDirItm(QList<PRJ_DIR_ITM> &diritms) = 0;
	virtual bool getSelectedItm(PRJ_DIR_ITM &selctedItm) = 0;
	virtual bool setSelectedIndex(const int index) = 0;
	virtual bool getTitle(QString &title) = 0;
	virtual PpPrjWizardPage* getPrePage() = 0;
	virtual PpPrjWizardPage* getNextPage() = 0;
	virtual void setPrePage(PpPrjWizardPage* prePage) = 0;
};


class PpBaseSelectPage: public QObject, public PpPrjWizardPage
{
	Q_OBJECT
public:
	PpBaseSelectPage(PhotoPrintPrjModel*);
	~PpBaseSelectPage();

public:
	virtual bool getDirItm(QList<PRJ_DIR_ITM> &diritms);
	virtual bool getSelectedItm(PRJ_DIR_ITM &selctedItm);
	virtual bool setSelectedIndex(const int index);
	virtual PpPrjWizardPage* getNextPage();
	virtual void setPrePage(PpPrjWizardPage* prePage){_pPrePage = prePage;}
	virtual PpPrjWizardPage* getPrePage() {return _pPrePage;}

protected:
	bool _getSelectItm(const int index, PRJ_DIR_ITM &selecteditm);
	bool _fillProjProps(const PRJ_DIR_ITM &selecteditm, PROJ_PROPS &projprops);
protected:
	QList<PRJ_DIR_ITM> _diritmslst;
	int _selectedindex;
	PpPrjWizardPage *_pPrePage;
	PhotoPrintPrjModel* _model;
};

class PpFormatSelectPage:  public PpBaseSelectPage
{
	Q_OBJECT
public:
	PpFormatSelectPage(PhotoPrintPrjModel*);
	~PpFormatSelectPage();
public:
	virtual bool HasPrePage();
	virtual bool HasNextPage();

	virtual bool setSelectedIndex(const int index);
	virtual bool getTitle(QString &title);

	virtual PpPrjWizardPage* getPrePage();

	virtual void setPrePage(PpPrjWizardPage* prePage){}

private:
	bool _isFinal;
};


class Pp4X3LayoutSelectPage: public PpBaseSelectPage
{
	Q_OBJECT
public:
	Pp4X3LayoutSelectPage(PhotoPrintPrjModel*);
	~Pp4X3LayoutSelectPage();

public:

public:
	virtual bool HasPrePage();
	virtual bool HasNextPage();

	virtual bool getTitle(QString &title);

	virtual PpPrjWizardPage* getNextPage();



private:
	bool _isFinal;

};


class Pp8x5BorderSelectPage:  public PpBaseSelectPage
{
	Q_OBJECT
public:
	Pp8x5BorderSelectPage(PhotoPrintPrjModel*);
	~Pp8x5BorderSelectPage();

public:

public:
	virtual bool HasPrePage();
	virtual bool HasNextPage();

	virtual bool getTitle(QString &title);



private:
	bool _isFinal;

};


class Pp8x5LayoutSelectPage: public PpBaseSelectPage
{
	Q_OBJECT
public:
	Pp8x5LayoutSelectPage(PhotoPrintPrjModel*);
	~Pp8x5LayoutSelectPage();

public:

public:
	virtual bool HasPrePage();
	virtual bool HasNextPage();

	virtual bool getTitle(QString &title);

private:
	bool _isFinal;

};


class Pp8x5NoBorderLayoutSelectPage:public PpBaseSelectPage
{
	Q_OBJECT
public:
	Pp8x5NoBorderLayoutSelectPage(PhotoPrintPrjModel*);
	~Pp8x5NoBorderLayoutSelectPage();

public:

public:
	virtual bool HasPrePage();
	virtual bool HasNextPage();

	virtual bool getTitle(QString &title);


private:
	bool _isFinal;
};



class PpCalendarA4LayoutSelectPage:public PpBaseSelectPage
{
	Q_OBJECT
public:
	PpCalendarA4LayoutSelectPage(PhotoPrintPrjModel*);
	~PpCalendarA4LayoutSelectPage();

public:

public:
	virtual bool HasPrePage();
	virtual bool HasNextPage();

	virtual bool getTitle(QString &title);

private:
	bool _isFinal;
};



class PpCalendarA5LayoutSelectPage: public PpBaseSelectPage
{
	Q_OBJECT
public:
	PpCalendarA5LayoutSelectPage(PhotoPrintPrjModel*);
	~PpCalendarA5LayoutSelectPage();

public:

public:
	virtual bool HasPrePage();
	virtual bool HasNextPage();

	virtual bool getTitle(QString &title);

private:
	bool _isFinal;
};



class PpCalendar4x6LayoutSelectPage: public PpBaseSelectPage
{
	Q_OBJECT
public:
	PpCalendar4x6LayoutSelectPage(PhotoPrintPrjModel*);
	~PpCalendar4x6LayoutSelectPage();

public:

public:
	virtual bool HasPrePage();
	virtual bool HasNextPage();

	virtual bool getTitle(QString &title);

private:
	bool _isFinal;
};


class PpCalendarYearSelectPage: public PpBaseSelectPage
{
	Q_OBJECT
public:
	PpCalendarYearSelectPage(PhotoPrintPrjModel*);
	~PpCalendarYearSelectPage();

public:

public:
	virtual bool HasPrePage();
	virtual bool HasNextPage();

	virtual bool getTitle(QString &title);

private:
	bool _isFinal;
};

class PhotoPrintPrjModel
{
public:
	PhotoPrintPrjModel();
	~PhotoPrintPrjModel();

public:
	PROJ_PROPS &getPrjProps(){return _projprops;}

public:
	PpPrjWizardPage *Init();
	PpPrjWizardPage *goNext();
	PpPrjWizardPage *goPre();
	PpPrjWizardPage *getCurPage();

	void onCancel();
	void onOk();

private:
	bool _fillProjProps(const PRJ_DIR_ITM &selecteditm, PROJ_PROPS &projprops);

private:
	PpPrjWizardPage *_pCurPage;
	PROJ_PROPS _projprops;
};

