#ifndef PmPhotoPage_H
#define PmPhotoPage_H

#include <QObject>
#include <QRect>
#include <QImage>
#include <QRGB>
#include <QMargins>
#include <QPixmap>
#include <QPrinter>
#include <QDateTime>



typedef struct _ProjProps
{
	typedef enum{DEFDEMO, POCKETBOOK4X3, PHOTOBOOK10X15, SINGLE4X6, PHOTOBOOK8X5,
	CALENDARA4, CALENDARA5,CALENDAR4X6}PROJ_TYPE;
	typedef enum{DEFLYTYPE, LY8X5FULL, LY8X5TRADITION, LY8X5VERTICON, LY8X5HORIZON,
	LYCALA4L1, LYCALA4L2, LYCALA4L3, LYCALA4L4, LYCALA5L1, LYCALA5L2,LYCALA5L3,
	LYCAL4X6L1, LYCAL4X6L2, LYCAL4X6L3, LYCAL4X6L4, LYCALFRONTPG}LAYOUT_TYPE;
	PROJ_TYPE type;
	bool hasborder;
	LAYOUT_TYPE lytype;
	unsigned int year; // for calendar
	unsigned int firstmonth;
	bool shadow;
	bool txtshadow;
	unsigned int lastphotopage;
	_ProjProps():type(DEFDEMO), hasborder(false), 
		lytype(DEFLYTYPE), year(2012),firstmonth(1), shadow(false),txtshadow(true),lastphotopage(0){}
}PROJ_PROPS;



typedef struct _PrintTaskInfo
{
	//
	QString information;
	QPrinter::PaperSize pagesize; // in mm
	QSize custompagesize;
	bool landscape;


	//
	int beginpage;
	int endpage;
	_PrintTaskInfo():pagesize(QPrinter::A4), landscape(false),beginpage(0), endpage(0)
	{
	}
}PRINT_TASK_INFO, *PPRINT_TASK_INFO;


typedef struct _FontProps
{
	QString name;
	QColor color;
	bool bold;
	bool iatic;
	bool underLine;
	int align; //Qt::AlignmentFlag
	qreal heightInCell;

	_FontProps(): bold(false), iatic(false),
		underLine(false), align(Qt::AlignLeft|Qt::AlignVCenter)
	{
	}

}FONT_PROPS, *PFONT_PROPS;

typedef struct _SpaceProps
{
	qreal left, top, right, bottom;
	qreal leftpad, toppad, rightpad, bottompad;
	_SpaceProps():left(0), top(0), right(0),bottom(0),
		leftpad(0), toppad(0), rightpad(0), bottompad(0)
	{
	}
}SPACE_PROPS, *PSPACE_PROPS;

typedef struct _CalProps
{
	// calendar 

	//   font
	FONT_PROPS fontcfg;


	// color
	QColor bgcolor;
	QColor rowcolor;
	QColor cellcolor;
	QList<QColor> wdcolors;

	// line spacing
	SPACE_PROPS linespace;
	SPACE_PROPS cellspace;
}CAL_PROPS, *PCAL_PROPS;

typedef struct _WeekDaysProps
{
	bool showwds;
	qreal regionsize;
	FONT_PROPS fontcfg;
	QColor rowcolor;
	QColor cellcolor;

	// line spacing
	SPACE_PROPS linespace;
	SPACE_PROPS cellspace;
	_WeekDaysProps():showwds(true), regionsize(0)
	{
	}
}WEEKDAY_PROPS, *PWEEKDAY_PROPS;

typedef struct _MonthYearProps
{
	bool showmonthyear;
	qreal regionsize;
	bool showonbottom;
	bool showmonthyeardouble;

	FONT_PROPS fontcfg;

	QColor rowcolor;

	// line spacing
	SPACE_PROPS linespace;

	_MonthYearProps():showmonthyear(true),regionsize(0), 
		showonbottom(false),showmonthyeardouble(true)
	{
	}
}MONTHYEAR_PROPS, *PMONTHYEAR_PROPS;


typedef struct _CalendarCfg
{
	bool forall;
	CAL_PROPS calcfg;
	WEEKDAY_PROPS wdcfg;
	MONTHYEAR_PROPS monthyearcfg;
	_CalendarCfg():forall(false)
	{
	}
}CALENDAR_CFG, *PCALENDAR_CFG;



struct LayoutBoxMargin
{
	qreal left;
    qreal top;
    qreal right;
    qreal bottom; 
	qreal mid; // for margin of horizal mid area in edit view, 
	LayoutBoxMargin():left(0), top(0), right(0), bottom(0), mid(0){}
};

typedef enum {NullType, TextType, ImgType, CalType, CalMonthType}ITEM_TYPE;

struct LayoutBoxPos
{
	ITEM_TYPE type;
	qreal x,y,width,height; 
	LayoutBoxMargin margin;
	LayoutBoxPos():type(ImgType), x(0), y(0), width(0), height(0){}
};



//
// layout  supports
//

#define LY_PREFIX			"Layout/"

#define LY_8X5_FULLSIZE_A	"8x5FullSizeA"
#define LY_8X5_FULLSIZE_B	"8x5FullSizeB"
#define LY_8X5_FULLSIZE_C	"8x5FullSizeC"
#define LY_8X5_FULLSIZE_D	"8x5FullSizeD"
#define LY_8X5_FULLSIZE_PANOR	"8x5FullSizePanor"
#define LY_8X5_TRADITION_A	"8x5TraditionA"
#define LY_8X5_TRADITION_B	"8x5TraditionB"
#define LY_8X5_TRADITION_C	"8x5TraditionC"
#define LY_8X5_TRADITION_D	"8x5TraditionD"
#define LY_8X5_TRADITION_PANOR	"8x5TraditionPanor"

#define LY_8X5_HORIZON_A	"8x5HorizonA"
#define LY_8X5_HORIZON_B	"8x5HorizonB"
#define LY_8X5_HORIZON_C	"8x5HorizonC"
#define LY_8X5_HORIZON_D	"8x5HorizonD"
#define LY_8X5_HORIZON_E	"8x5HorizonE"
#define LY_8X5_HORIZON_PANOR	"8x5HorizonPanor"

#define LY_8X5_VERTICON_A	"8x5VerticonA"
#define LY_8X5_VERTICON_B	"8x5VerticonB"
#define LY_8X5_VERTICON_C	"8x5VerticonC"
#define LY_8X5_VERTICON_D	"8x5VerticonD"
#define LY_8X5_VERTICON_PANOR	"8x5VerticonPanor"


// 4x3

#define LY_4X3_FULLSIZE_SINGLE		"4x3FullSizeSingle"
#define LY_4X3_FULLSIZE_PANORAMA	"4x3FullSizePanorama"
#define LY_4X3_BORDER_SINGLE		"4x3BorderSingle"
#define LY_4X3_BORDER_PANORAMA		"4x3BorderPanorama"


///
#define LY_CALA4_FP_1	"CalA4FrontPgL1"
#define LY_CALA4_FP_2	"CalA4FrontPgL2"

#define LY_CALA4_L1_1	"CalA4L1L1"
#define LY_CALA4_L1_2	"CalA4L1L2"
#define LY_CALA4_L1_3	"CalA4L1L3"
#define LY_CALA4_L1_4	"CalA4L1L4"

#define LY_CALA4_L2_1	"CalA4L2L1"
#define LY_CALA4_L2_2	"CalA4L2L2"
#define LY_CALA4_L2_3	"CalA4L2L3"
#define LY_CALA4_L2_4	"CalA4L2L4"
#define LY_CALA4_L2_5	"CalA4L2L5"
#define LY_CALA4_L2_6	"CalA4L2L6"

#define LY_CALA4_L3_1	"CalA4L3L1"
#define LY_CALA4_L3_2	"CalA4L3L2"
#define LY_CALA4_L3_3	"CalA4L3L3"
#define LY_CALA4_L3_4	"CalA4L3L4"

#define LY_CALA4_L4_1	"CalA4L4L1"
#define LY_CALA4_L4_2	"CalA4L4L2"
#define LY_CALA4_L4_3	"CalA4L4L3"
#define LY_CALA4_L4_4	"CalA4L4L4"

//A5
#define LY_CALA5_FP_1	"CalA5FrontPgL1"
#define LY_CALA5_FP_2	"CalA5FrontPgL2"


#define LY_CALA5_L1_1	"CalA5L1L1"
#define LY_CALA5_L1_2	"CalA5L1L2"
#define LY_CALA5_L1_3	"CalA5L1L3"
#define LY_CALA5_L1_4	"CalA5L1L4"
#define LY_CALA5_L1_5	"CalA5L1L5"
#define LY_CALA5_L1_6	"CalA5L1L6"

#define LY_CALA5_L2_1	"CalA5L2L1"
#define LY_CALA5_L2_2	"CalA5L2L2"
#define LY_CALA5_L2_3	"CalA5L2L3"
#define LY_CALA5_L2_4	"CalA5L2L4"
#define LY_CALA5_L2_5	"CalA5L2L5"


#define LY_CALA5_L3_1	"CalA5L3L1"
#define LY_CALA5_L3_2	"CalA5L3L2"
#define LY_CALA5_L3_3	"CalA5L3L3"
#define LY_CALA5_L3_4	"CalA5L3L4"

//CAL 4X6
#define LY_CALA4x6_FP_1	"CalA4x6FrontPgL1"
#define LY_CALA4x6_FP_2	"CalA4x6FrontPgL2"


#define LY_CAL4X6_L1_1	"Cal4X6L1L1"
#define LY_CAL4X6_L1_2	"Cal4X6L1L2"
#define LY_CAL4X6_L1_3	"Cal4X6L1L3"
#define LY_CAL4X6_L1_4	"Cal4X6L1L4"


#define LY_CAL4X6_L2_1	"Cal4X6L2L1"
#define LY_CAL4X6_L2_2	"Cal4X6L2L2"
#define LY_CAL4X6_L2_3	"Cal4X6L2L3"
#define LY_CAL4X6_L2_4	"Cal4X6L2L4"



#define LY_CAL4X6_L3_1	"Cal4X6L3L1"
#define LY_CAL4X6_L3_2	"Cal4X6L3L2"
#define LY_CAL4X6_L3_3	"Cal4X6L3L3"
#define LY_CAL4X6_L3_4	"Cal4X6L3L4"

#define LY_CAL4X6_L4_1	"Cal4X6L4L1"
#define LY_CAL4X6_L4_2	"Cal4X6L4L2"
#define LY_CAL4X6_L4_3	"Cal4X6L4L3"
#define LY_CAL4X6_L4_4	"Cal4X6L4L4"




typedef enum{PP_LAYOUT_FULLSIZE_SINGLE,PP_LAYOUT_FULLSIZE_PANOR , 
	PP_LAYOUT_BORDER_SINGLE,PP_LAYOUT_BORDER_PANOR,
	PP_LAYOUT_PB8X5_FULLSIZE_A, PP_LAYOUT_PB8X5_FULLSIZE_B,PP_LAYOUT_PB8X5_FULLSIZE_C,PP_LAYOUT_PB8X5_FULLSIZE_D, PP_LAYOUT_PB8X5_FULLSIZE_PANOR,
	PP_LAYOUT_PB8X5_TRADITION_A, PP_LAYOUT_PB8X5_TRADITION_B, PP_LAYOUT_PB8X5_TRADITION_C, PP_LAYOUT_PB8X5_TRADITION_D, PP_LAYOUT_PB8X5_TRADITION_PANOR, 
	PP_LAYOUT_PB8X5_HORIZON_A, PP_LAYOUT_PB8X5_HORIZON_B,PP_LAYOUT_PB8X5_HORIZON_C, PP_LAYOUT_PB8X5_HORIZON_D,PP_LAYOUT_PB8X5_HORIZON_E, PP_LAYOUT_PB8X5_HORIZON_PANOR,
	PP_LAYOUT_PB8X5_VERTICON_A,PP_LAYOUT_PB8X5_VERTICON_B,PP_LAYOUT_PB8X5_VERTICON_C, PP_LAYOUT_PB8X5_VERTICON_D, PP_LAYOUT_PB8X5_VERTICON_PANOR,
	PP_LAYOUT_CALENDAR_A4_L1_L1,PP_LAYOUT_CALENDAR_A4_L1_L2,PP_LAYOUT_CALENDAR_A4_L1_L3,PP_LAYOUT_CALENDAR_A4_L1_L4,
	PP_LAYOUT_CALENDAR_A4_L2_L1,PP_LAYOUT_CALENDAR_A4_L2_L2,PP_LAYOUT_CALENDAR_A4_L2_L3, PP_LAYOUT_CALENDAR_A4_L2_L4, PP_LAYOUT_CALENDAR_A4_L2_L5, PP_LAYOUT_CALENDAR_A4_L2_L6,
	PP_LAYOUT_CALENDAR_A4_L3_L1, PP_LAYOUT_CALENDAR_A4_L3_L2, PP_LAYOUT_CALENDAR_A4_L3_L3, PP_LAYOUT_CALENDAR_A4_L3_L4,
	PP_LAYOUT_CALENDAR_A4_L4_L1,PP_LAYOUT_CALENDAR_A4_L4_L2, PP_LAYOUT_CALENDAR_A4_L4_L3, PP_LAYOUT_CALENDAR_A4_L4_L4,
	PP_LAYOUT_CALENDAR_A5_L1_L1, PP_LAYOUT_CALENDAR_A5_L1_L2, PP_LAYOUT_CALENDAR_A5_L1_L3, PP_LAYOUT_CALENDAR_A5_L1_L4, PP_LAYOUT_CALENDAR_A5_L1_L5, PP_LAYOUT_CALENDAR_A5_L1_L6,
	PP_LAYOUT_CALENDAR_A5_L2_L1,PP_LAYOUT_CALENDAR_A5_L2_L2, PP_LAYOUT_CALENDAR_A5_L2_L3, PP_LAYOUT_CALENDAR_A5_L2_L4, PP_LAYOUT_CALENDAR_A5_L2_L5,
	PP_LAYOUT_CALENDAR_A5_L3_L1,PP_LAYOUT_CALENDAR_A5_L3_L2, PP_LAYOUT_CALENDAR_A5_L3_L3, PP_LAYOUT_CALENDAR_A5_L3_L4,
	PP_LAYOUT_CALENDAR_4X6_L1_L1, PP_LAYOUT_CALENDAR_4X6_L1_L2, PP_LAYOUT_CALENDAR_4X6_L1_L3, PP_LAYOUT_CALENDAR_4X6_L1_L4,
	PP_LAYOUT_CALENDAR_4X6_L2_L1,PP_LAYOUT_CALENDAR_4X6_L2_L2, PP_LAYOUT_CALENDAR_4X6_L2_L3, PP_LAYOUT_CALENDAR_4X6_L2_L4,
	PP_LAYOUT_CALENDAR_4X6_L3_L1,PP_LAYOUT_CALENDAR_4X6_L3_L2, PP_LAYOUT_CALENDAR_4X6_L3_L3, PP_LAYOUT_CALENDAR_4X6_L3_L4,
	PP_LAYOUT_CALENDAR_4X6_L4_L1, PP_LAYOUT_CALENDAR_4X6_L4_L2,PP_LAYOUT_CALENDAR_4X6_L4_L3,PP_LAYOUT_CALENDAR_4X6_L4_L4,
	PP_LAYOUT_CALENDARA4_FONTPG,
	PP_LAYOUT_CALENDARA4_BORDER_FONTPG,
	PP_LAYOUT_CALENDARA5_FONTPG,
	PP_LAYOUT_CALENDARA5_BORDER_FONTPG,
	PP_LAYOUT_CALENDAR4x6_FONTPG,
	PP_LAYOUT_CALENDAR4x6_BORDER_FONTPG

}PHOTO_LAYOUT;


class PPLayout
{
public:
	virtual ~PPLayout(){}
public:
	virtual bool getLayout(QList<LayoutBoxPos> &layoutboxes,bool hasborder, bool left) = 0;
};


class PPLayoutMgr
{
private:
	PPLayoutMgr(){}
	~PPLayoutMgr(){}

public:
	static PPLayoutMgr& getInst(){ static PPLayoutMgr inst; return inst;}
	PPLayout &getLayout(PHOTO_LAYOUT layout);
	PPLayout &getLayout(const PROJ_PROPS &projprops,const QString &layoutname);

	PHOTO_LAYOUT getLayoutFromName(const PROJ_PROPS &projprops,const QString &name);
	QString  getLayoutName(const PHOTO_LAYOUT layout);

};



//
// pages support
//

class PmPhotoPage;

class PmPageItm: public QObject
{
	Q_OBJECT

public:
		typedef enum{IMG_ITM, IMG_PANOR_ITM, TXT_ITM, CALENDAR_ITM, COLOR_ITM}PHOTO_ITM_TYPE;
public:
	PmPageItm(QObject *parent);
	PmPageItm(PmPageItm &pageitm);
	~PmPageItm();

public:
	bool getRectInPage(LayoutBoxPos &rect);
	bool setRectInPage(const LayoutBoxPos &rect);

	void setPhotoItmType(PHOTO_ITM_TYPE type){_itmType = type;}
	PHOTO_ITM_TYPE getPhotoItmType(){ return _itmType;}

	bool setContent(const QString &cnt);
	bool getContent(QString &cnt);

	// for image
	bool getRotate(int &angel);
	bool setRotate(int angel);
	bool getZoom(qreal &ratio);
	bool setZoom(qreal ratio);

	bool setImgLeftTop(const QPointF &lefttop){_imglefttop = lefttop; return true;}
	bool getImgLeftTop(QPointF &lefttop){lefttop = _imglefttop; return true;}
	void clearImgLeftTop(){_imglefttop = QPointF(-1, -1);}

	bool setBgColor(const QColor &color){_bkcolor = color; return true;}
	bool getBgColor(QColor &color){color = _bkcolor; return true;}

	//for calendar
	bool setMonth(const int year, const int month){_year = year; _month = month; return true;}
	bool getMonth(int &year, int &month){year = _year; month = _month;return true;}

	// calendar view style
	bool setCalProps(const CAL_PROPS &calprops){_calcfg = calprops;return true;}
	bool getCalProps(CAL_PROPS &calprops){calprops = _calcfg; return true;}

	// week days
	bool setWdsProps(const WEEKDAY_PROPS &wdsprops){_wdcfg = wdsprops; return true;}
	bool getWdsProps(WEEKDAY_PROPS &wdsprops){wdsprops = _wdcfg; return true;}

	// month&year
	bool setMonthYearProps(const MONTHYEAR_PROPS &monthyearprops){_monthyearcfg = monthyearprops; return true;}
	bool getMonthYearProps(MONTHYEAR_PROPS &monthyearprops){monthyearprops = _monthyearcfg; return true;}


	// common
	bool setPage(PmPhotoPage *page);
	PmPhotoPage * getPage();

	void *getPageViewItm(){return _photoitm;}
	void setPageViewItm(void *itm){_photoitm = itm;}

	void *getPreviewPageViewItm(){return _previewphotoitm;}
	void setPreviewPageViewItm(void *itm){_previewphotoitm = itm;}

	// for enhance performance
	void setPixmap(const QPixmap &pixmap){_pixmap = pixmap;}
	QPixmap *getPixmap(){return &_pixmap;}

	// edit support
	bool zoom(int value);


private:
	LayoutBoxPos _layoutbox;
	PmPhotoPage *_pPage;

	PHOTO_ITM_TYPE _itmType;

	// image
	QString _cnt;
	int _angel;
	qreal _ratio;
	QPointF _imglefttop;
	QColor _bkcolor;


	// calendar 
	int _year, _month;

	//  calendar view cfg

	// common
	CAL_PROPS _calcfg;

	// week days
	WEEKDAY_PROPS _wdcfg;

	// month & year
	MONTHYEAR_PROPS _monthyearcfg;




	// ui assist
	void * _photoitm;
	void * _previewphotoitm;

	QPixmap _pixmap;
};


class PmPrintPaperPage;

class PmTextItm: public QObject
{
	Q_OBJECT

public:
		typedef enum{ALIGN_HMASK=0xffff0000, ALIGN_VMASK=0x0000ffff, ALIGN_TOP=0x01, ALIGN_VCENTER=0x02, ALIGN_BOTTOM=0x03,ALIGN_VJUSTIFY=0x4, ALIGN_LEFT=0x10000, ALIGN_CENTER=0x20000, ALIGN_RIGHT=0x30000, ALIGN_JUSTIFY=0x40000}ALIGN_TYPE;
public:
	PmTextItm(QObject *parent);
	PmTextItm(PmTextItm &txtitm);
	~PmTextItm(){}

public:
	// height and width is the absolute pt
	bool getRectInPrintPage(LayoutBoxPos &rect){rect = _layoutbox; return true;}
	bool setRectInPrintPage(const LayoutBoxPos &rect){_layoutbox = rect; return true;}

	bool setContent(const QString &cnt){_cnt = cnt; return true;}
	bool getContent(QString &cnt){cnt = _cnt; return true;}



	int getAlign() {return _aligntype;}
	void setAlign(int align){_aligntype = align;}

	void setScale(qreal scale){_scale = scale;}
	qreal getScale(){return _scale;}
	void setRotate(qreal rotate){_rotate = rotate;}
	qreal getRotate(){return _rotate;}
	void enableShadow(bool bEnableShadow){_shadow = bEnableShadow;}
	bool isShadowEnable(){return _shadow;}

	bool setPrintPage(PmPrintPaperPage *page){_pPage=page; return true;}
	PmPrintPaperPage * getPrintPage(){return _pPage;}


	void *getViewItm(){return _viewitm;}
	void setViewItm(void *itm){_viewitm = itm;}
	QDateTime getLastBackTime(){return _lastbacktime;}
	void setLastBackTime(QDateTime lastbacktime){_lastbacktime=lastbacktime;}

private:
	LayoutBoxPos _layoutbox;
	PmPrintPaperPage *_pPage;

	QString _cnt;
	qreal _scale;
	qreal _rotate;
	bool _shadow;
	void * _viewitm;
	int _aligntype;

	QDateTime _lastbacktime; // asist memeber, no need to save
};


class PmPhotoPage : public QObject
{
	Q_OBJECT

public:
	PmPhotoPage(QObject *parent);
	~PmPhotoPage();

	PmPhotoPage(PmPhotoPage &srcpage);

public:
	int getType(){return 0;}
	void setType(int type){}
	
	bool hasBorder(){return _hasborder;}
	void setBorder(bool hasborder){_hasborder = hasborder;}
	bool isLeft(){return _isleft;}
	void setIsLeft(bool left){_isleft = left;}

	PHOTO_LAYOUT getLayout(){return _layout;}
	bool setLayout(PHOTO_LAYOUT layout, bool hasborder, bool left, bool adjustlayout = true);

	bool getPagePosInPaper(LayoutBoxPos &pagepos);
	bool setPagePosInPaper(LayoutBoxPos &pagepos);
	void reversePagePos();

	qreal getScaleRatio(){return _scaleratio;}
	qreal setScaleRatio(qreal ratio){return _scaleratio=ratio;}

	bool getImgOff();
	bool setImgOff();

	//
	// when a new layout is set, it create a new PmPageItm list.
	// then check if old items can be copied into the new one
	// at last, it delete the old items.
	//
	bool getPicItms(QList<PmPageItm *> &picitmlst);
	bool setPicItms(const QList<PmPageItm *> &picitmlst);

	PmPrintPaperPage *getPaperPage(){return _pPaperPage;}
	void setPaperPage(PmPrintPaperPage *pPaperPage){_pPaperPage = pPaperPage;}

	// eidt view assit
	void *getPageBkViewItm(){return _pBkViewItm;}
	void setPageBkViewItm(void *bkViewItm){_pBkViewItm = bkViewItm;}


private:
	PHOTO_LAYOUT _layout;
	QList<PmPageItm *> _pagepicitmlst;

	PmPrintPaperPage *_pPaperPage;
	LayoutBoxPos _pos;
	qreal _scaleratio;

	bool _isleft;
	bool _hasborder;

	void * _pBkViewItm;
};

class PmPhotoView;

typedef enum {FIRST_PAGE, LAST_PAGE, NORMAL_PAGE}PAGE_POS_INBOOK;

class PmPrintPaperPage : public QObject
{
	Q_OBJECT
public:
	typedef enum{LF_PG_LAYOUT, RT_PG_LAYOUT, WH_PG_LAYOUT}LAYOUT_POS;
public:
	PmPrintPaperPage(QObject *parent, PAGE_POS_INBOOK pagepos );
	virtual ~PmPrintPaperPage();

public:
	bool copy(PmPrintPaperPage &srcpaper);
	// help functions for edit
	PmPhotoView *getPreviewView(){return _pPapaerPreviewView;}
	void setPreviewView(PmPhotoView *view){_pPapaerPreviewView = view;}
	PmPhotoView *getEditView(){return _pPhotoEditView;}
	void setEditView(PmPhotoView *view){_pPhotoEditView = view;}

	// help functions for panorama
	bool updatePanoramaPages(PmPhotoPage *srcpage, PmPhotoPage *&dstpage);

	PAGE_POS_INBOOK getPagePos(){return _paperpos;}
public:
	// property
	virtual void getSize(QSize &size){}
	virtual bool getMarginInEditView(LayoutBoxMargin &marginInEditView){return false;}
	virtual bool getBackGroundImgInEditView(QString &imgpath){return false;}
	virtual void setborder(bool hasborder){} 
	virtual bool getborder(){return true;} 


	// functions used when layout changes
	//virtual bool splitPhotoPage();
	//virtual bool mergePhotoPage();

	virtual void rotate(){;}


	virtual bool setLayout(PmPhotoPage *pPhotoPage,PHOTO_LAYOUT layout, LAYOUT_POS layoutpos=WH_PG_LAYOUT);
	virtual bool getPhotoPages(QList<PmPhotoPage *> &photopages);
	virtual bool setPhotoPages(const QList<PmPhotoPage *> &photopages);

	virtual bool getTextbox(QList<PmTextItm *> &txtlst);
	virtual bool addTextbox(PmTextItm *pTextItm = NULL);
	virtual bool delTextbox(PmTextItm *pTextItm);
	//virtual bool getPhotoPagesPos(QList<LayoutBoxPos> &pagespos) = 0;

private:
	PHOTO_LAYOUT _getLayoutMatch2Panor(PHOTO_LAYOUT panorlayout);
	bool _need2BindPage(PmPhotoPage *pPhotoPage, PHOTO_LAYOUT newlayout);
	bool _switch2AnotherPanorama(PmPhotoPage *pPhotoPage, PHOTO_LAYOUT newlayout);
	bool _need2SplitPage(PmPhotoPage *pPhotoPage, PHOTO_LAYOUT newlayout);
	bool _isPanoramaLayout(PHOTO_LAYOUT layout);
	PHOTO_LAYOUT _getLayoutBind2PanoramaLayout(PHOTO_LAYOUT panoramalayout);
	void _clearImgOff();

protected:
	QList<PmPhotoPage *> _photoPages;
	QList<PmTextItm *> _txtlst;

	PmPhotoView *_pPhotoEditView;
	PmPhotoView *_pPapaerPreviewView;
	PAGE_POS_INBOOK _paperpos;
};




class Pm8x5PrintPaper: public PmPrintPaperPage
{
	Q_OBJECT
public:
	Pm8x5PrintPaper(bool hasborder, QObject *parent, PAGE_POS_INBOOK pos=NORMAL_PAGE );
	virtual ~Pm8x5PrintPaper();

public:
	virtual void setborder(bool hasborder){_borderless = !hasborder;} 
	virtual bool getborder(){return !_borderless;} 

	virtual void getSize(QSize &size);
	virtual void rotate();
	virtual bool getMarginInEditView(LayoutBoxMargin &marginInEditView);
	virtual bool getBackGroundImgInEditView(QString &imgpath);

	//virtual bool getPhotoPagesPos(QList<LayoutBoxPos> &pagespos);

private:
	QSize _size;
	bool _borderless;
};


class Pm10x15PrintPaper: public PmPrintPaperPage
{
	Q_OBJECT
public:
	Pm10x15PrintPaper(bool hasborder, QObject *parent, PAGE_POS_INBOOK pos=NORMAL_PAGE );
	virtual ~Pm10x15PrintPaper();

public:
	virtual void setborder(bool hasborder){_borderless = !hasborder;} 
	virtual bool getborder(){return !_borderless;} 

	virtual void getSize(QSize &size);
	virtual void rotate();
	virtual bool getMarginInEditView(LayoutBoxMargin &marginInEditView);
	virtual bool getBackGroundImgInEditView(QString &imgpath);

	//virtual bool getPhotoPagesPos(QList<LayoutBoxPos> &pagespos);

private:
	QSize _size;
	bool _borderless;
};



class Pm4x3PrintPaper: public PmPrintPaperPage
{
	Q_OBJECT
public:
	Pm4x3PrintPaper(bool hasborder, QObject *parent, PAGE_POS_INBOOK pos=NORMAL_PAGE );
	virtual ~Pm4x3PrintPaper();

public:
	virtual void setborder(bool hasborder){_borderless = !hasborder;} 
	virtual bool getborder(){return !_borderless;} 

	virtual void getSize(QSize &size);
	virtual void rotate();
	virtual bool getMarginInEditView(LayoutBoxMargin &marginInEditView);
	virtual bool getBackGroundImgInEditView(QString &imgpath);

	//virtual bool getPhotoPagesPos(QList<LayoutBoxPos> &pagespos);

private:
	QSize _size;
	bool _borderless;
};




class PmA4CalPrintPaper: public PmPrintPaperPage
{
	Q_OBJECT
public:
	PmA4CalPrintPaper(bool hasborder, PROJ_PROPS::LAYOUT_TYPE lytype, QObject *parent, PAGE_POS_INBOOK pos=NORMAL_PAGE );
	virtual ~PmA4CalPrintPaper();

public:
	virtual void setborder(bool hasborder){_borderless = !hasborder;} 
	virtual bool getborder(){return !_borderless;} 

	virtual void getSize(QSize &size);
	virtual void rotate();
	virtual bool getMarginInEditView(LayoutBoxMargin &marginInEditView);
	virtual bool getBackGroundImgInEditView(QString &imgpath);

	//virtual bool getPhotoPagesPos(QList<LayoutBoxPos> &pagespos);

private:
	QSize _size;
	bool _borderless;
};

class PmA5CalPrintPaper: public PmPrintPaperPage
{
	Q_OBJECT
public:
	PmA5CalPrintPaper(bool hasborder, PROJ_PROPS::LAYOUT_TYPE lytype, QObject *parent, PAGE_POS_INBOOK pos=NORMAL_PAGE );
	virtual ~PmA5CalPrintPaper();

public:
	virtual void setborder(bool hasborder){_borderless = !hasborder;} 
	virtual bool getborder(){return !_borderless;} 

	virtual void getSize(QSize &size);
	virtual void rotate();
	virtual bool getMarginInEditView(LayoutBoxMargin &marginInEditView);
	virtual bool getBackGroundImgInEditView(QString &imgpath);

	//virtual bool getPhotoPagesPos(QList<LayoutBoxPos> &pagespos);

private:
	QSize _size;
	bool _borderless;
};


class Pm4x6CalPrintPaper: public PmPrintPaperPage
{
	Q_OBJECT
public:
	Pm4x6CalPrintPaper(bool hasborder, PROJ_PROPS::LAYOUT_TYPE lytype,QObject *parent, PAGE_POS_INBOOK pos=NORMAL_PAGE );
	virtual ~Pm4x6CalPrintPaper();

public:
	virtual void setborder(bool hasborder){_borderless = !hasborder;} 
	virtual bool getborder(){return !_borderless;} 

	virtual void getSize(QSize &size);
	virtual void rotate();
	virtual bool getMarginInEditView(LayoutBoxMargin &marginInEditView);
	virtual bool getBackGroundImgInEditView(QString &imgpath);

	//virtual bool getPhotoPagesPos(QList<LayoutBoxPos> &pagespos);

private:
	QSize _size;
	bool _borderless;
};

#define COLOR_PREFIX		"Color/"


#define COLOR_LIGHT_GREY_NAME		"light_grey"
#define COLOR_GREY_NAME				"grey"
#define COLOR_DARK_GREY_NAME		"dark_grey"
#define COLOR_BLACK_NAME			"black"
#define COLOR_BRIGHT_YELLOW_NAME	"bright_yellow"
#define COLOR_YELLOW_NAME			"yellow"
#define COLOR_ORANGE_NAME			"orange"
#define COLOR_PINK_NAME				"pink"
#define COLOR_LIGHT_PINK_NAME		"light_pink"
#define COLOR_BLUE_NAME				"blue"
#define COLOR_LIGHT_BLUE_NAME		"light_blue"
#define COLOR_LIGHT_GREEN_NAME		"light_green"
#define COLOR_GREEN_NAME			"green"
#define COLOR_CUSTOMER_NAME			"Customer Color"

#define COLOR_LIGHT_GREY_VALUE		qRgb(233,233,233)
#define COLOR_GREY_VALUE			qRgb(177,177,177)
#define COLOR_DARK_GREY_VALUE		qRgb(93,93,93)
#define COLOR_BLACK_VALUE			qRgb(0,0,0)
#define COLOR_BRIGHT_YELLOW_VALUE	qRgb(255,240,184)
#define COLOR_YELLOW_VALUE			qRgb(255,231,121)
#define COLOR_ORANGE_VALUE			qRgb(255,190,104)
#define COLOR_PINK_VALUE			qRgb(255,199,203)
#define COLOR_LIGHT_PINK_VALUE		qRgb(231,201,255)
#define COLOR_BLUE_VALUE			qRgb(208,220,255)
#define COLOR_LIGHT_BLUE_VALUE		qRgb(231,251,255)
#define COLOR_LIGHT_GREEN_VALUE		qRgb(231,244,216)
#define COLOR_GREEN_VALUE			qRgb(231,244,153)

class ColorMgr
{
public:
	ColorMgr(){}
	~ColorMgr(){}

public:
	static bool getColor(const QString &name, QColor &color);
	static bool getColorName(const QColor &color,QString &name);
};
//
// for photo edit view, it only consist graphic view item, which represent one PmPhotoPage
// for photo page privew view, it has many grahpic view items, each will first 
//		1. show a PmPhotoPage,
//		2. show a page no
// 
//


#endif // PmPhotoPage_H
