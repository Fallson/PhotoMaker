#include "pmpaperpagectrlpane.h"
#include <QtDebug>
#include <QtGui/qlayout.h>
#include <QtGui/qpushbutton.h>
#include <QtGui/qdial.h>
#include "borderlayout.h"


#define PAGE_CTRLER_HEIGHT	26
#define PAGE_CTRLER_Y_POS	10
#define PAGE_INFO_CTRLER_WIDTH	160
#define PAGE_GO_BTN_WIDTH	30
#define PAGE_ZOOM_ICON_WIDTH	31
#define PAGE_ZOOM_ICON_HEIGHT	22
#define PAGE_ZOOM_SLIDER_WIDTH	100
#define PAGE_ZOOM_SLIDER_HEIGHT	14
#define PAGE_ZOOM_SLIDER_SPAN_2_FRAME	10

#define VIEW_ZOOM_SPAN_RANGE	500

PmPaperPageCtrlPane::PmPaperPageCtrlPane(PhotoMaker *pMainFrame, QWidget *parent)
	: QLabel(parent), _pMainFrame(pMainFrame)
{
	setStyleSheet("background-image:url(" + gbires + "pagectrlbk.png)");
		//"QPushButton:hover {background: qradialgradient(cx: 0.3, cy: -0.4,fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #ccc, stop: 1 #222);}");


	pZoomIcon = new QLabel(this);
    pZoomIcon->setPixmap(QPixmap::fromImage(QImage("Resources/images/ZoomInOut.png").scaled(PAGE_ZOOM_ICON_WIDTH,PAGE_ZOOM_ICON_HEIGHT)));


	pSlider = new QSlider(this);
	pSlider->setOrientation(Qt::Horizontal);


	pSlider->setRange(0, VIEW_ZOOM_SPAN_RANGE);
	pSlider->setSingleStep(1);
	pSlider->setPageStep(2);

	
	pPreButn = new QPushButton(
		QIcon(QPixmap::fromImage(QImage("Resources/images/pre.png").scaled(PAGE_GO_BTN_WIDTH,PAGE_CTRLER_HEIGHT))), 
		"", this);
	pPreButn->setFlat(true);
	pPreButn->setStyleSheet("QPushButton{background: transparent}");
	pPreButn->setIconSize(QSize(PAGE_GO_BTN_WIDTH,PAGE_CTRLER_HEIGHT));

	//pPreButn->setMaximumWidth(25);

	ppageShow = new QLabel(this);
	ppageShow->setText("No 1 Page");
	ppageShow->setAlignment(Qt::AlignCenter);
	ppageShow->setStyleSheet("QLabel{background: transparent}");

	pNextButn =  new QPushButton(
		QIcon(QPixmap::fromImage(QImage("Resources/images/next.png").scaled(PAGE_GO_BTN_WIDTH,PAGE_CTRLER_HEIGHT))), 
		"", this);
	pNextButn->setFlat(true);
	pNextButn->setStyleSheet("QPushButton{background: transparent}");
	pNextButn->setIconSize(QSize(PAGE_GO_BTN_WIDTH,PAGE_CTRLER_HEIGHT));


	connect(pSlider, SIGNAL(valueChanged ( int  )), this, SLOT(Zoom(int)));
	connect(pNextButn, SIGNAL(clicked ( bool )),_pMainFrame, SLOT(OnNextPage()));
	connect(pPreButn, SIGNAL(clicked ( bool )),_pMainFrame, SLOT(OnPrePage()));

}

PmPaperPageCtrlPane::~PmPaperPageCtrlPane()
{

}

// 

void PmPaperPageCtrlPane::resizeEvent(QResizeEvent *)
{
	QRect rect = this->geometry();
	int midpos = rect.width()/2;

	pPreButn->setGeometry(midpos-PAGE_INFO_CTRLER_WIDTH/2 - PAGE_GO_BTN_WIDTH, PAGE_CTRLER_Y_POS-1,
		PAGE_GO_BTN_WIDTH, PAGE_CTRLER_HEIGHT+2);
	pNextButn->setGeometry(midpos +PAGE_INFO_CTRLER_WIDTH/2, PAGE_CTRLER_Y_POS-1, 
		PAGE_GO_BTN_WIDTH, PAGE_CTRLER_HEIGHT+2);
	ppageShow->setGeometry(midpos-PAGE_INFO_CTRLER_WIDTH/2, PAGE_CTRLER_Y_POS, 
		PAGE_INFO_CTRLER_WIDTH, PAGE_CTRLER_HEIGHT);

	pZoomIcon->setGeometry(rect.width()-PAGE_ZOOM_SLIDER_WIDTH-PAGE_ZOOM_ICON_WIDTH-PAGE_ZOOM_SLIDER_SPAN_2_FRAME*1.5,
		PAGE_CTRLER_Y_POS,
		PAGE_ZOOM_ICON_WIDTH,PAGE_ZOOM_ICON_HEIGHT);
	pSlider->setGeometry(rect.width()-PAGE_ZOOM_SLIDER_WIDTH-PAGE_ZOOM_SLIDER_SPAN_2_FRAME, PAGE_CTRLER_Y_POS*1.2, 
		PAGE_ZOOM_SLIDER_WIDTH, PAGE_ZOOM_SLIDER_HEIGHT);

}

void PmPaperPageCtrlPane::ZoomIn()
{
	int pos = pSlider->sliderPosition();
	pos++;
	if ( pos > VIEW_ZOOM_SPAN_RANGE )
	{
		pos = VIEW_ZOOM_SPAN_RANGE;
	}
	pSlider->setSliderPosition(pos);

	qreal scale = 1 + pos*1.0/VIEW_ZOOM_SPAN_RANGE;

	_pMainFrame->OnZoomEditView(scale);
}

void PmPaperPageCtrlPane::ZoomOut()
{
	int pos = pSlider->sliderPosition();
	pos --;
	if ( pos < 0 )
	{
		pos = 0;
	}
	pSlider->setSliderPosition(pos);

	qreal scale = 1 + pos*1.0/VIEW_ZOOM_SPAN_RANGE;

	_pMainFrame->OnZoomEditView(scale);
}

void PmPaperPageCtrlPane::Zoom(int value)
{
	int pos = value;
	if ( pos < 0 )
	{
		pos = 0;
	}
	if ( pos > VIEW_ZOOM_SPAN_RANGE )
	{
		pos = VIEW_ZOOM_SPAN_RANGE;
	}


	qreal scale = 1 + pos*1.0/VIEW_ZOOM_SPAN_RANGE;

	_pMainFrame->OnZoomEditView(scale);
}


void PmPaperPageCtrlPane::showPageInfo(const QString &pageInfo)
{

	ppageShow->setText(pageInfo);
}
