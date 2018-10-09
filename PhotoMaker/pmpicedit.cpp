#include "pmpicedit.h"
#include "photomaker.h"

PmPicEdit::PmPicEdit(PhotoMaker *pMainFrame, QWidget *parent)
	: QWidget(parent), _pMainFrame(pMainFrame)
{
	ui.setupUi(this);

    QAction *lsigeditAct = new QAction(QIcon(""), tr("lightness, contrast, intensity, gamma..."),ui.btnFlter);
    //openAct->setShortcuts(QKeySequence::New);
    lsigeditAct->setStatusTip(tr("edit lightness, contrast, intensity, gamma"));
    connect(lsigeditAct, SIGNAL(triggered()), _pMainFrame, SLOT(OnSetPhotoLCIG()));


    QAction *hhleditAct = new QAction(QIcon(""), tr("hue, haturation, lightness..."),ui.btnFlter);
    //openAct->setShortcuts(QKeySequence::New);
    hhleditAct->setStatusTip(tr("edit hue, haturation, lightness"));
    connect(hhleditAct, SIGNAL(triggered()), _pMainFrame, SLOT(OnSetPhotoHSL()));

    QAction *coloreditAct = new QAction(QIcon(""), tr("black and white, colorize..."),ui.btnFlter);
    //openAct->setShortcuts(QKeySequence::New);
    coloreditAct->setStatusTip(tr("editblack and white, colorize"));
    connect(coloreditAct, SIGNAL(triggered()), _pMainFrame, SLOT(OnSetPhotoBWC()));

    QAction *rmredeyeAct = new QAction(QIcon(""), tr("remove red-eyes..."),ui.btnFlter);
    //openAct->setShortcuts(QKeySequence::New);
    rmredeyeAct->setStatusTip(tr("editblack and white, colorize"));
    connect(rmredeyeAct, SIGNAL(triggered()), _pMainFrame, SLOT(OnSetPhotoRE()));

	QMenu *fltrmenu = new QMenu(ui.btnFlter);
	fltrmenu->addAction(lsigeditAct);
	fltrmenu->addAction(hhleditAct);
	fltrmenu->addAction(coloreditAct);
	fltrmenu->addAction(rmredeyeAct);

	ui.btnFlter->setMenu(fltrmenu);
	ui.btnFlter->setPopupMode(QToolButton::InstantPopup);
	ui.btnFlter->setAutoRaise(true);
	ui.btnFlter->setIconSize(QSize(48,48));
	ui.btnFlter->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	ui.btnFlter->setIcon(QIcon("Resources\\images\\imgfilter.png"));



	ui.btnRotateLeft->setAutoRaise(true);
	ui.btnRotateLeft->setIconSize(QSize(48,48));
	ui.btnRotateLeft->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	ui.btnRotateLeft->setIcon(QIcon("Resources\\images\\rotateleft.png"));

	ui.btnRotateRight->setAutoRaise(true);
	ui.btnRotateRight->setIconSize(QSize(48,48));
	ui.btnRotateRight->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	ui.btnRotateRight->setIcon(QIcon("Resources\\images\\rotateright.png"));

	ui.lbDPIIcon->setPixmap(QPixmap("Resources\\images\\dpi.png"));
	ui.lbDPI->setAlignment(Qt::AlignHCenter);
	ui.lbDPI->setText("dpi");
	



	connect(ui.btnRotateLeft, SIGNAL(clicked()), _pMainFrame, SLOT(OnRotatePhotoleft()));
	connect(ui.btnRotateRight, SIGNAL(clicked()), _pMainFrame, SLOT(OnRotatePhotoright()));
	connect(ui.photoZoomSplitter, SIGNAL(valueChanged ( int ) ), this, SLOT(OnZoomPhoto(int)));


	ui.lbZoomIcon->setPixmap(QPixmap::fromImage(QImage("Resources\\images\\zoom.png").scaled(QSize(15,15))));
	ui.photoZoomSplitter->setRange(1, 100);
	ui.photoZoomSplitter->setSingleStep(1);
	ui.photoZoomSplitter->setPageStep(10);

}

PmPicEdit::~PmPicEdit()
{

}


void PmPicEdit::OnZoomPhoto(int value)
{
	if ( _pMainFrame )
	{
		_pMainFrame->OnZoomPhoto((value -1)*1.0/100 + 1);
	}
}

void PmPicEdit::setScaleRatio(qreal ratio)
{
	if ( ratio < 1 )
	{
		ratio = 1;
	}
	ui.photoZoomSplitter->setSliderPosition((ratio - 1) * 100 + 1);
}


void PmPicEdit::setDpi(int dpi)
{
	QString dpistr = QString("%1").arg(dpi);
	ui.lbDPI->setText(dpistr);
}

