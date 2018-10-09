#include "photomaker.h"
#include <QtGui/qsplitter.h>
#include <QtGui/qtextedit.h>
#include <QtGui/qfiledialog.h>
#include <QtGui/qtreeview.h>
#include <QtGui/QFileSystemModel.h>
#include <QtGui/qtreewidget.h>
#include <QtGui/qlayout.h>
#include "pmleftpane.h"
#include <QtGui/qpushbutton.h>
#include "pmbottomctrlpane.h"
#include "pmcentralpane.h"
#include "pmprintprojcfgdlg.h"
#include <QtGui/qcheckbox.h>
#include <QFileDialog>
#include "PmUndoActionStack.h"
#include <QPrinter>
#include <QPrintDialog>
#include "PhotoEditViewscene.h"
#include <QMessageBox>
#include <QPrinterInfo>
#include <QPageSetupDialog>
#include <QToolButton>
#include <QMouseEvent>
#include <QShortcut>
#include <QMessageBox>

#include "PrintCfgDlg.h"
#include "pmaboutdlg.h"
#include "PhotoCalViewItem.h"
#include <QDesktopWidget>

#define BUILDIN_IMG_RES_PREFIX	":/PhotoMaker/Resources/images/buildinui/"
QString gbires = QString(BUILDIN_IMG_RES_PREFIX);
extern QApplication *g_app ;


void PhotoMaker::_createActions()
{
    _newAct = new QAction(QIcon("Resources/images/new.png"), tr("New..."),
                               this);
    _newAct->setShortcuts(QKeySequence::New);
    _newAct->setStatusTip(tr("Create a new print project"));
    connect(_newAct, SIGNAL(triggered()), this, SLOT(OnNewProj()));


    _openAct = new QAction(QIcon("Resources/images/open.png"), tr("Open..."),this);
    _openAct->setShortcuts(QKeySequence::Open);
    _openAct->setStatusTip(tr("Open a  print project"));
    connect(_openAct, SIGNAL(triggered()), this, SLOT(OnOpenProj()));


    _saveAct = new QAction(QIcon("Resources/images/save.png"), tr("Save..."), this);
    _saveAct->setShortcuts(QKeySequence::Save);
    _saveAct->setStatusTip(tr("Save the current project"));
    connect(_saveAct, SIGNAL(triggered()), this, SLOT(OnSaveProj()));

    _saveAsAct = new QAction(QIcon("Resources/images/save.png"), tr("Save as..."), this);
   // _saveAsAct->setShortcuts(QKeySequence::Save);
    _saveAsAct->setStatusTip(tr("Save the current project"));
    connect(_saveAsAct, SIGNAL(triggered()), this, SLOT(OnSaveAs()));


    _undoAct = new QAction(QIcon("Resources/images/undo.png"), tr("Undo"), this);
    _undoAct->setShortcuts(QKeySequence::Undo);
    _undoAct->setStatusTip(tr("Undo the last editing action"));
    connect(_undoAct, SIGNAL(triggered()), this, SLOT(OnUndo()));

    _quitCurPrjAct = new QAction(QIcon("Resources/images/exit.png"), tr("Close"), this);
    //_exitAppAct->setShortcuts(QKeySequence::Quit);
    _quitCurPrjAct->setStatusTip(tr("Quit current project"));
    connect(_quitCurPrjAct, SIGNAL(triggered()), this, SLOT(OnQuitProj()));

    _exitAppAct = new QAction(QIcon("Resources/images/exit.png"), tr("Close"), this);
    _exitAppAct->setShortcuts(QKeySequence::Quit);
    _exitAppAct->setStatusTip(tr("Quit the application"));
    connect(_exitAppAct, SIGNAL(triggered()), this, SLOT(close()));

    _aboutAct = new QAction(tr("About"), this);
    _aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(_aboutAct, SIGNAL(triggered()), this, SLOT(OnAbout()));


	_cutAct = new QAction(tr("Cut"), this);
	_cutAct->setStatusTip(tr("Cut"));
    _cutAct->setShortcuts(QKeySequence::Cut);
	connect(_cutAct, SIGNAL(triggered()), this, SLOT(OnCut()));

	_copyAct = new QAction(tr("Copy"), this);
	_copyAct->setStatusTip(tr("Copy"));
    _copyAct->setShortcuts(QKeySequence::Copy);
	connect(_copyAct, SIGNAL(triggered()), this, SLOT(OnCopy()));

	_pasteAct = new QAction(tr("Paste"), this);
	_pasteAct->setStatusTip(tr("Paste"));
    _pasteAct->setShortcuts(QKeySequence::Paste);
	connect(_pasteAct, SIGNAL(triggered()), this, SLOT(OnPaste()));

	_delAct = new QAction(tr("Delete"), this);
	_delAct->setStatusTip(tr("Delete"));
	_delAct->setShortcut(Qt::Key_Delete);
	connect(_delAct, SIGNAL(triggered()), this, SLOT(OnDelSelection()));

	_printAct = new QAction(tr("Print"), this);
	_printAct->setStatusTip(tr("Print current project"));
    _printAct->setShortcut(QKeySequence("Ctrl+P"));
	connect(_printAct, SIGNAL(triggered()), this, SLOT(OnPrint()));


	// global shortcuts
	/*
	QShortcut  *ctrlxshortcut= new QShortcut(QKeySequence::Cut, this);
	connect( ctrlxshortcut, SIGNAL( activated () ), this, SLOT( OnCut() ) );

	QShortcut  *ctrlcshortcut= new QShortcut(QKeySequence::Copy, this);
	connect( ctrlcshortcut, SIGNAL( activated () ), this, SLOT( OnCopy() ) );

	QShortcut  *ctrlvshortcut= new QShortcut(QKeySequence::Paste, this);
	connect( ctrlvshortcut, SIGNAL( activated () ), this, SLOT( OnPaste() ) );
	*/
	// load language files in language folder 
	{
		_createLangItms();
	}
}



#define TOOL_BAR_HEIGHT 58
#define TOOL_BAR_WIDTH  70
#define TOP_LABEL_HEIGHT 80

void PhotoMaker::_createToolBarButton()
{
	QRect rect = this->geometry();
	_toolBarBane = new QLabel(_pCentralWidget);
	_toolBarBane->setGeometry(0,TOP_LABEL_HEIGHT, rect.width(), TOP_LABEL_HEIGHT);
	_toolBarBane->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	_toolBarBane->show();

	QRect btnRect = QRect(1, 1,TOOL_BAR_WIDTH, TOOL_BAR_HEIGHT - 2);
	_newBtn = new QToolButton(this->_toolBarBane);
	_newBtn->setText(tr("New"));
	_newBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_newBtn->setGeometry(btnRect);
	_newBtn->setIcon(QPixmap::fromImage(QImage("Resources/images/new.png")));
	_newBtn->setIconSize(QSize(TOOL_BAR_WIDTH,TOOL_BAR_HEIGHT - 25));


	btnRect.adjust(TOOL_BAR_WIDTH+5, 0, TOOL_BAR_WIDTH+5, 0);
	_opnBtn = new QToolButton(this->_toolBarBane);
	_opnBtn->setText(tr("Open"));
	_opnBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_opnBtn->setGeometry(btnRect);
	_opnBtn->setIcon(QPixmap::fromImage(QImage("Resources/images/open.png")));
	_opnBtn->setIconSize(QSize(TOOL_BAR_WIDTH,TOOL_BAR_HEIGHT - 25));




	btnRect.adjust(TOOL_BAR_WIDTH+5, 0, TOOL_BAR_WIDTH+5, 0);
	_savBtn = new QToolButton(this->_toolBarBane);
	_savBtn->setText(tr("Save"));
	_savBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	_savBtn->setGeometry(btnRect);
	_savBtn->setIcon(QPixmap::fromImage(QImage("Resources/images/save.png")));
	_savBtn->setIconSize(QSize(TOOL_BAR_WIDTH,TOOL_BAR_HEIGHT - 25));

	btnRect.adjust(TOOL_BAR_WIDTH+5, 0, TOOL_BAR_WIDTH+5, 0);
	_prntBtn = new QToolButton(this->_toolBarBane);
	_prntBtn->setText(tr("Print"));
	_prntBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_prntBtn->setGeometry(btnRect);
	_prntBtn->setIcon(QPixmap::fromImage(QImage("Resources/images/print.png")));
	_prntBtn->setIconSize(QSize(TOOL_BAR_WIDTH,TOOL_BAR_HEIGHT - 25));

	btnRect.adjust(TOOL_BAR_WIDTH+5, 0, TOOL_BAR_WIDTH+5, 0);
	_undoBtn = new QToolButton(this->_toolBarBane);
	_undoBtn->setText(tr("Undo"));
	_undoBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_undoBtn->setGeometry(btnRect);
	_undoBtn->setIcon(QPixmap::fromImage(QImage("Resources/images/undo.png")));
	_undoBtn->setIconSize(QSize(TOOL_BAR_WIDTH,TOOL_BAR_HEIGHT- 25));

	btnRect.adjust(TOOL_BAR_WIDTH+5, 0, TOOL_BAR_WIDTH+5, 0);
	_delBtn = new QToolButton(this->_toolBarBane);
	_delBtn->setText(tr("Delete"));
	_delBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_delBtn->setGeometry(btnRect);
	_delBtn->setIcon(QPixmap::fromImage(QImage("Resources/images/delete.png")));
	_delBtn->setIconSize(QSize(TOOL_BAR_WIDTH,TOOL_BAR_HEIGHT - 25));

	btnRect.adjust(TOOL_BAR_WIDTH+5, 0, TOOL_BAR_WIDTH*1.5+5, 0);
	_orientationBtn = new QToolButton(this->_toolBarBane);
	_orientationBtn->setText(tr("Orientation"));
	_orientationBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_orientationBtn->setGeometry(btnRect);
	_orientationBtn->setIcon(QPixmap::fromImage(QImage("Resources/images/Orientation.png")));
	_orientationBtn->setIconSize(QSize(TOOL_BAR_WIDTH*1.5,TOOL_BAR_HEIGHT - 25));


	btnRect.adjust(TOOL_BAR_WIDTH*1.5+5, 0, TOOL_BAR_WIDTH+5, 0);
	_addtxtBtn = new QToolButton(this->_toolBarBane);
	_addtxtBtn->setText(tr("Text"));
	_addtxtBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_addtxtBtn->setGeometry(btnRect);
	_addtxtBtn->setIcon(QPixmap::fromImage(QImage("Resources/images/addtxt.png")));
	_addtxtBtn->setIconSize(QSize(TOOL_BAR_WIDTH,TOOL_BAR_HEIGHT - 25));

	btnRect.adjust(TOOL_BAR_WIDTH+5, 0, TOOL_BAR_WIDTH*1.5+5, 0);
	_shadowBtn = new QToolButton(this->_toolBarBane);
	_shadowBtn->setText(tr("Picure Shadow"));
	_shadowBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_shadowBtn->setGeometry(btnRect);
	_shadowBtn->setIcon(QPixmap::fromImage(QImage("Resources/images/shadow.png")));
	_shadowBtn->setIconSize(QSize(TOOL_BAR_WIDTH*1.5,TOOL_BAR_HEIGHT - 25));
	_shadowBtn->setCheckable(true);
	_shadowBtn->setEnabled(false);


	btnRect.adjust(TOOL_BAR_WIDTH+5, 0, TOOL_BAR_WIDTH*1.5+5, 0);
	_quitBtn = new QToolButton(this->_toolBarBane);
	_quitBtn->setText(tr("Quit"));
	_quitBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_quitBtn->setGeometry(btnRect);
	_quitBtn->setIcon(QPixmap::fromImage(QImage("Resources/images/exit.png")));
	_quitBtn->setIconSize(QSize(TOOL_BAR_WIDTH*1.5,TOOL_BAR_HEIGHT - 25));

	
	connect(_newBtn, SIGNAL(clicked()), this, SLOT(OnNewProj()));
	connect(_opnBtn, SIGNAL(clicked()), this, SLOT(OnOpenProj()));
    connect(_savBtn, SIGNAL(clicked()), this, SLOT(OnSaveProj()));
    connect(_prntBtn, SIGNAL(clicked()), this, SLOT(OnPrint()));
    connect(_undoBtn, SIGNAL(clicked()), this, SLOT(OnUndo()));
    connect(_delBtn, SIGNAL(clicked()), this, SLOT(OnDelSelection()));
    connect(_addtxtBtn, SIGNAL(clicked()), this, SLOT(OnAddTxt()));
    connect(_shadowBtn, SIGNAL(clicked()), this, SLOT(OnChgShadow()));
    connect(_quitBtn, SIGNAL(clicked()), this, SLOT(OnQuitProj()));
	connect(_orientationBtn, SIGNAL(clicked()), this, SLOT(OnOrentation()));

}



//! [8]
void PhotoMaker::_createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
	statusBar()->setStyleSheet("background-image:url(" + gbires + "TitleBarBackGround.png)");

}


#define TOP_LABEL_HEIGHT 80
PhotoMaker::PhotoMaker(PmPhotoMakerDoc *pdoc, QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), _pdoc(pdoc), _langactGroup(NULL),
	_newBtn(NULL),_opnBtn(NULL), _savBtn(NULL),_prntBtn(NULL),_undoBtn(NULL),
	_delBtn(NULL),_orientationBtn(NULL),_addtxtBtn(NULL),_shadowBtn(NULL),_quitBtn(NULL),
	_toplabel(NULL),_pCentralWidget(NULL),_pOpWidget(NULL),_phsplitter(NULL),
	_pLeftPane(NULL),_pBottomCtrlPane(NULL),_pCentralPane(NULL),
	_leftBar(NULL), _rightBar(NULL), _undoonprocessing(false)

{
	ui.setupUi(this);
	
	setWindowFlags(Qt::FramelessWindowHint);
   // w.setWindowFlags(Qt::FramelessWindowHint);

	this->resize(1024, 768);
	this->setMinimumSize(800, 600);

	

	_createActions();
	_createStatusBar();



	_pCentralWidget = new QWidget(this);
	QPalette palette;
	palette.setBrush(_pCentralWidget->backgroundRole(), QBrush(QImage(gbires + "BarLayout.png")));
	_pCentralWidget->setPalette(palette);

	_pOpWidget = new QWidget(_pCentralWidget);


	QRect rect = this->geometry();
	_toplabel = new TopInfoLabel(_pCentralWidget,this);
	_toplabel->setGeometry(0,0, rect.width(), TOP_LABEL_HEIGHT);
	//_toplabel->setText("<h2><i>This  bar will show some</i><font color=red>  message!</font></h2>");
	_toplabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	//QPalette palette;
	//palette.setBrush(_toplabel->backgroundRole(), QBrush(QImage(":/PhotoMaker/Resources/images/undo.png")));
	_toplabel->setStyleSheet(QString("background-image:url(") + gbires + "TitleBarBackGround.png)");
	//_toplabel->setPalette(palette);
	_toplabel->show();

	_createToolBarButton();


	_pOpWidget->setGeometry(0, TOP_LABEL_HEIGHT+TOP_LABEL_HEIGHT, rect.width(),rect.height()-TOP_LABEL_HEIGHT*2);
	QRect checkrect = _pOpWidget->geometry();


	_phsplitter = new QSplitter(Qt::Horizontal, _pOpWidget);
	//_phsplitter->setStyleSheet("QSplitter{background-color:RGB(46,63,93)}");
	_phsplitter->setOpaqueResize(false);
	_phsplitter->setChildrenCollapsible(false); 

	QList<int> sizes;

	_pLeftPane = new PmLeftPane(_pOpWidget);
	_phsplitter->addWidget(_pLeftPane);
	_phsplitter->setMinimumWidth(100);
	_pLeftPane->setMinimumWidth(180);

	QSplitter *pRightvsplitter = new QSplitter(Qt::Vertical, _pOpWidget);
	pRightvsplitter->setOpaqueResize(false);
	pRightvsplitter->setChildrenCollapsible(false); 

	QPalette palette1;
	palette1.setBrush(_pCentralWidget->backgroundRole(), QBrush(QImage(gbires + "HBarLayout.png")));
	pRightvsplitter->setPalette(palette1);

	_pCentralPane = new PmCentralPane(this, _pOpWidget);
	pRightvsplitter->addWidget(_pCentralPane);
	_pCentralPane->setMinimumHeight(300);

	_pBottomCtrlPane = new PmBottomCtrlPane(this, _pOpWidget);
	pRightvsplitter->addWidget(_pBottomCtrlPane);
	_pBottomCtrlPane->setMinimumHeight(160);
	
	sizes.clear();
	sizes.push_back(400);
	sizes.push_back(160);
	pRightvsplitter->setSizes(sizes);
	pRightvsplitter->setStretchFactor(1,0);
	pRightvsplitter->setStretchFactor(0,1);


	_phsplitter->addWidget(pRightvsplitter);
	pRightvsplitter->setMinimumWidth(160);

	sizes.clear();
	sizes.push_back(280);
	sizes.push_back(450);
	_phsplitter->setSizes(sizes);
	_phsplitter->setStretchFactor(0,0);
	_phsplitter->setStretchFactor(1,1);
	//pRightvsplitter->setMinimumHeight
	//_phsplitter->setMinimumWidth(


	setCentralWidget(_pCentralWidget);
	QRect centralrect = _pCentralWidget->geometry();

	rect = _pOpWidget->geometry();
	_phsplitter->setGeometry(0, 0, rect.width(), rect.height());


	_pCentralWidget->show();
	_pOpWidget->show();

	_leftBar = new FrameBar(true, this, this);
	_rightBar = new FrameBar(false, this, this);


	this->_appcfg.loadCfg("appcfg.xml");
	QString langname, langfile;
	_appcfg.getLang(langname, langfile);
	if ( !langname.length() )
	{
		langname = tr("English");
	}
	this->_chgLang(langname, langfile);
	_selLangMenu(langname);


    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - width())/2, (desktop->height() - height())/2);

	if ( _appcfg.isMaximized() )
	{
		this->OnMaxmize();
	}

	QString lastshowpath;
	_appcfg.getPicViewDir(lastshowpath);
	if ( lastshowpath.length() )
	{
		_pLeftPane->selectCurFolder(lastshowpath);
	}
	
	updateUIStatus();
	show();
}

PhotoMaker::~PhotoMaker()
{

}

void PhotoMaker::updateViews(bool reload)
{
	//
	PmPhotoView *photoEditView = _pCentralPane->getEditView();
	photoEditView->updateView(reload);
	PmPhotoView *previewView = this->_pBottomCtrlPane->getPreviewView();
 	previewView->updateView(reload);
}

void PhotoMaker::updateEditView(bool reload )
{
	PmPhotoView *photoEditView = _pCentralPane->getEditView();
	photoEditView->updateView(reload);

	// update page info
	this->_showPageIndexInfo();

	//
	PROJ_PROPS prj;
	_pdoc->getProjProps(prj);
	switch( prj.type )
	{
	case PROJ_PROPS::CALENDARA4:
	case PROJ_PROPS::CALENDARA5:
	case PROJ_PROPS::CALENDAR4X6:
		{
			PmPrintPaperPage *pcurpaper;
			int index = 0;
			_pdoc->getCurPrintPaperPage(pcurpaper, index);
			if ( index == 12 )
			{
				// front page
				this->_pLeftPane->showLayoutPreview(prj.type, !prj.hasborder, PROJ_PROPS::LYCALFRONTPG);
			}
			else
			{
				this->_pLeftPane->showLayoutPreview(prj.type, !prj.hasborder, prj.lytype);
			}
		}
		break;
	default:
		;
	}
}
	
bool PhotoMaker::updateLastPhotoPage(PmPhotoPage *photopage)
{
	PmPhotoMakerDoc *pdoc = getDoc();
	PmPrintPaperPage *oldnextpaper = NULL;
	pdoc->getNextEditPaper(oldnextpaper);
	bool ret = pdoc->updateLastPhotoPage(photopage);
	if ( !ret )
	{
		return false;
	}
	PmPrintPaperPage *nextpaper = NULL;
	pdoc->getNextEditPaper(nextpaper);

	if ( oldnextpaper != nextpaper )
	{
		//updateNextEditPaper
		getPreviewView()->updateNextEditPaper(oldnextpaper, nextpaper);
	}

	return true;
}
PrintPagesPreviewView *PhotoMaker::getPreviewView()
{
	return this->_pBottomCtrlPane->getPreviewView();
}

PhotoEditView *PhotoMaker::getEditView()
{
	return _pCentralPane->getEditView();
}

void PhotoMaker::updateEditPaneInfo()
{
	_pBottomCtrlPane->updateEditPaneInfo();
}


bool PhotoMaker::showEditPane(PmBottomCtrlPane::EDIT_PANE_TYPE editpane, const QString &cnt)
{
	bool ret =  _pBottomCtrlPane->showEditPane(editpane, cnt);

	if ( ret )
	{
		PmPhotoView *previewView = this->_pBottomCtrlPane->getPreviewView();
		previewView->updateView(false);
	}
	return true;
}

#define TITLE_BAR_HEIGHT		20
#define MENUE_BAR_HEIGHT		26
#define STATUS_BAR_HEIGHT		26

#define INFO_BANE_HEIGHT	58

#define FRAME_WIDTH		2

void PhotoMaker::resizeEvent(QResizeEvent *)
{
	//
     QPainterPath path;
 
     QRectF rect1 = this->geometry();
	 rect1.adjust(-rect1.left(),-rect1.top(), -rect1.left(), -rect1.top());
 
     path.addRoundRect(rect1,1,1);
 
        
 
    QPolygon polygon= path.toFillPolygon().toPolygon();//获得这个路径上的所有的点
 
	QRegion region(polygon);//根据这个点构造这个区域
 
	setMask(region);

	//
	QRect rect = this->geometry();
	_pCentralWidget->setGeometry(0,0/*TITLE_BAR_HEIGHT+MENUE_BAR_HEIGHT+TOOLBAR_BTN_HEIGHT*/, rect.width(), rect.height()/*-(TITLE_BAR_HEIGHT+MENUE_BAR_HEIGHT+TOOLBAR_BTN_HEIGHT)*//* - STATUS_BAR_HEIGHT*/);
	QRect centralrect = _pCentralWidget->geometry();


	_toplabel->setGeometry(FRAME_WIDTH,0, centralrect.width()-FRAME_WIDTH*2, INFO_BANE_HEIGHT);
	_toolBarBane->setGeometry(FRAME_WIDTH, INFO_BANE_HEIGHT, centralrect.width()-FRAME_WIDTH*2, INFO_BANE_HEIGHT);

	// ajust tool bar
	//	btnRect.adjust(TOOL_BAR_WIDTH+5, 0, TOOL_BAR_WIDTH*1.5+5, 0);
	QRect btnRect = QRect(rect.width()-1, 1,TOOL_BAR_WIDTH, TOOL_BAR_HEIGHT - 2);
	btnRect.adjust(-TOOL_BAR_WIDTH-5, 0, -TOOL_BAR_WIDTH-5, 0);
	_quitBtn->setGeometry(btnRect);


	QRect statusRect = statusBar()->geometry();
	_pOpWidget->setGeometry(FRAME_WIDTH, INFO_BANE_HEIGHT*2, centralrect.width()-FRAME_WIDTH*2, centralrect.height()-INFO_BANE_HEIGHT*2-statusRect.height());

	rect = _pOpWidget->geometry();
	_phsplitter->setGeometry(0, 0, rect.width(), rect.height());

	this->_leftBar->setGeometry(0, 0, FRAME_WIDTH,centralrect.height());
	this->_rightBar->setGeometry(centralrect.width()-FRAME_WIDTH, 0, FRAME_WIDTH,centralrect.height());

}


void PhotoMaker::_showProjInfo(PROJ_PROPS prjprops)
{
	QString projinfo;
	switch(prjprops.type )
	{
	case PROJ_PROPS::POCKETBOOK4X3:
		{
			projinfo = tr("PocketBooklet");
		}
		break;
	case PROJ_PROPS::PHOTOBOOK10X15:
		{
			projinfo = tr("Photobook 10:15");
		}
		break;
	case PROJ_PROPS::SINGLE4X6:
		{
			projinfo = tr("4x6 Singles");
		}
		break;
	case PROJ_PROPS::PHOTOBOOK8X5:
		{
			projinfo = tr("Photobook 8:5 - ");
			switch(prjprops.lytype)
			{
			case PROJ_PROPS::LY8X5FULL:
				{
					projinfo += tr("Fullpage");
				}
				break;
			case PROJ_PROPS::LY8X5TRADITION:
				{
					projinfo += tr("Tradition");
				}
				break;
			case PROJ_PROPS::LY8X5VERTICON:
				{
					projinfo += tr("Verticon");
				}
				break;
			case PROJ_PROPS::LY8X5HORIZON:
				{
					projinfo += tr("Horizon");
				}
				break;
			}
		}
		break;
	case PROJ_PROPS::CALENDARA4:
	case PROJ_PROPS::CALENDARA5:
	case PROJ_PROPS::CALENDAR4X6:
		{
			projinfo = tr("Calendar");
		}
		break;
	case PROJ_PROPS::DEFDEMO:
	default:
		;
	}
	projinfo = "<h2> <font  color=white>" + projinfo +  "</font></h2>";
	_toplabel->setText(projinfo);
	_toplabel->update();
}

void PhotoMaker::OnNewProj()
{
	_prjfile = "";

	PmPrintProjCfgDlg dlg(this);
	if ( QDialog::Accepted != dlg.exec() )
	{

		return ;
	}
	PROJ_PROPS projprops;
	dlg.getProjProps(projprops);

	if ( this->_pdoc->newDoc(projprops) )
	{
		_showProjInfo(projprops);
		this->updateViews(true);
		this->_pLeftPane->showLayoutPreview(projprops.type, !projprops.hasborder, projprops.lytype);

		PhotoEditView *photoEditView = _pCentralPane->getEditView();
		photoEditView->enableShadow(projprops.shadow);
	}

	PmUndoActionStack::getInst().clearUpdated();
	PmUndoActionStack::getInst().clearUndoStack();
	this->updateUIStatus();

}
void PhotoMaker::OnQuitProj()
{
	if ( PmUndoActionStack::getInst().isUpdated() )
	{
		//
		QMessageBox confirmdlg(QMessageBox::Question, tr("Confirmation"),
			tr("The current project is not saved.\n Do you want to save it now?"),
			QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel ,this);
		
		int ret = confirmdlg.exec();	
		if ( ret == QMessageBox::Yes )
		{
			this->OnSaveProj();
		}
		else if ( ret == QMessageBox::Cancel )
		{
			//return ;
		}
	}
	this->_prjfile = "";
	this->OnNewProj();
}

void PhotoMaker::OpenProj(const QString &projfile)
{
	QString filepath = projfile;
	_prjfile = filepath;

	QDir prjfolder("prj/");
	//file.delte
	QFileInfoList list = prjfolder.entryInfoList();
	for (int subindex=0;subindex<list.size(); subindex++ )
	{
		QFileInfo fileinfo = list[subindex];
		QString path = fileinfo.fileName();
		prjfolder.remove(path);
	}

	QFile file;
	file.copy(filepath,"./prj/prj.save.tar" );


	// compress all the prj folder
	QProcess::execute("./bsdtar.exe -xf ./prj/prj.save.tar");
	prjfolder.remove("./prj.save.tar");


	QString prjfile = "prj/prjfile.xml";

	this->_pdoc->loadDoc(prjfile);
	_pdoc->updateLastEditPage();



	// reload
	//this->getPhotoEditView()->setpap
	PROJ_PROPS projprops;
	_pdoc->getProjProps(projprops);
	this->_showProjInfo(projprops);

	this->updateViews(true);
	_pdoc->getProjProps(projprops);

	this->_pLeftPane->showLayoutPreview(projprops.type, !projprops.hasborder, projprops.lytype);
	_pdoc->getProjProps(projprops);

	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	photoEditView->enableShadow(projprops.shadow);
	photoEditView->enableTxtShadow(projprops.txtshadow);

	updateUIStatus();
}

void PhotoMaker::OnOpenProj()
{
	QFileDialog filedlg;
	filedlg.setNameFilter("Photo Maker File(*.pm)");
	filedlg.setAcceptMode(QFileDialog::AcceptOpen);
	//filedlg.exec();
	QString filepath = filedlg.getOpenFileName(this, tr("Open the project file"), QString(), "Photo Maker File(*.pm)");
	if ( filepath.length() <= 0 )
	{
		return ;
	}
	_prjfile = filepath;
	OpenProj(filepath);

	PmUndoActionStack::getInst().clearUpdated();

	PmUndoActionStack::getInst().clearUndoStack();
	this->updateUIStatus();

}
void PhotoMaker::OnSaveAs()
{
	QFileDialog filedlg;
	filedlg.setNameFilter("Photo Maker File(*.pm)");
	filedlg.setAcceptMode(QFileDialog::AcceptSave);
	//filedlg.exec();
	QString filepath = filedlg.getSaveFileName(this, tr("Save the project file"), QString(), "Photo Maker File(*.pm)");
	if ( filepath.length() <= 0 )
	{
		return ;
	}

	_prjfile = filepath;

	// first save xml in proj folder
	QDir prjfolder("prj/");

	QString xmlsvefile = "prj/prjfile.xml";
	this->_pdoc->saveDoc(xmlsvefile);

	// compress all the prj folder
	QProcess::execute("./bsdtar.exe -cf prj.save.tar ./prj/*.*");
	QFile file;
	QDir dir;
	if ( file.exists(_prjfile) )
	{
		dir.remove(_prjfile);
	}
	bool ret = file.copy("./prj.save.tar", _prjfile);
	dir.remove("./prj.save.tar");

	PmUndoActionStack::getInst().clearUpdated();
}

void PhotoMaker::OnSaveProj()
{
	if ( 0 == _prjfile.length() )
	{
		QFileDialog filedlg;
		filedlg.setAcceptMode(QFileDialog::AcceptSave);
		//filedlg.exec();
		QString filepath = filedlg.getSaveFileName(this, tr("Save the project file"), QString(), "Photo Maker File(*.pm)");
		if ( filepath.length() <= 0 )
		{
			return ;
		}

		_prjfile = filepath;
	}
	// first save xml in proj folder
	QDir prjfolder("prj/");

	QString xmlsvefile = "prj/prjfile.xml";
	this->_pdoc->saveDoc(xmlsvefile);

	// compress all the prj folder
	QProcess::execute("./bsdtar.exe -cf prj.save.tar ./prj/*.*");
	QFile file;
	QDir dir;
	if ( file.exists(_prjfile) )
	{
		dir.remove(_prjfile);
	}
	bool ret = file.copy("./prj.save.tar", _prjfile);
	dir.remove("./prj.save.tar");
	PmUndoActionStack::getInst().clearUpdated();
}

void PhotoMaker::OnPrint()
{
	PmPrinterCfgDlg dlg(this->_appcfg);

	if ( !this->_pdoc )
	{
		return ;
	}

	PRINT_TASK_INFO printTaskInfo;
	PROJ_PROPS proj;
	_pdoc->getProjProps(proj);
	bool showseamadjust = !proj.hasborder;
	switch(proj.type)
	{
	case PROJ_PROPS::CALENDARA4:
	case PROJ_PROPS::CALENDARA5:
	case PROJ_PROPS::CALENDAR4X6:
		showseamadjust = false;
		break;
	case PROJ_PROPS::POCKETBOOK4X3:
		showseamadjust = true;
		break;
	default:
		;
	}
	dlg.showSrintSeamBtn(showseamadjust);

	PrintTaskMgr::getPrintTaskInfo(proj, printTaskInfo);

	QList<PmPrintPaperPage*>  paperpages;
	_pdoc->getPrintPaperPages(paperpages);

	int lasteditpageidx = 0;
	_pdoc->getLastEditPhotoPage(lasteditpageidx);
	dlg.setMaxPages(lasteditpageidx);
	dlg.setInformation(printTaskInfo.information);

	if (dlg.exec() == QDialog::Accepted)
	{
		dlg.getPageRange(printTaskInfo.beginpage, printTaskInfo.endpage);
		if (printTaskInfo.beginpage == 0 &&  printTaskInfo.endpage == -1 )
		{
			// all pages
			printTaskInfo.beginpage = 1;
			printTaskInfo.endpage = lasteditpageidx;

		}
		QPrinterInfo printerInfo;
		bool gotprinter = dlg.getPrinter(printerInfo);
		 QList<QPrinter::PaperSize> paperszlst = printerInfo.supportedPaperSizes();
		QPrinter *printer = new QPrinter(printerInfo);
		if ( !gotprinter )
		{
			printer->setOutputFormat(QPrinter::PdfFormat);
			printer->setOutputFileName("C:/Users/penner/desktop/fallson.pdf");
		}
		printer->setPageMargins(0,0,0,0, QPrinter::Point);


		QRectF pageRect ;
		pageRect = printer->pageRect(/*QPrinter::Point*/);

		QPrinter::PaperSize papersize = printer->paperSize();
		if ( printTaskInfo.pagesize == QPrinter::Custom )
		{
			printer->setPaperSize(QPrinter::Custom );
			printer->setPaperSize(QSizeF(printTaskInfo.custompagesize),QPrinter::Inch);
		}
		else
		{
			printer->setPaperSize(printTaskInfo.pagesize);
		}
		if ( printTaskInfo.landscape )
		{
            printer->setOrientation(QPrinter::Landscape);
		}
		else
		{
            printer->setOrientation(QPrinter::Portrait);
		}
		printer->setColorMode(QPrinter::Color);
        QPainter  *painter = new QPainter(printer);

		qreal printoff = 0; 
		dlg.getPrintOff(printoff);
		pageRect = printer->pageRect(/*QPrinter::Point*/);
		if ( fabs(printoff) >= 0.0001 )
		{
			pageRect.adjust(pageRect.width()*printoff, 0, pageRect.width()*printoff, 0);
		}
		qDebug()<< "pageRect " << pageRect;
		QRectF paperRect ;
		paperRect = printer->paperRect();
		qDebug()<< "paperRect " << paperRect;

		PhotoPrintScene *printscene = new PhotoPrintScene(pageRect,this,this);
		printscene->print(printer, painter, &printTaskInfo);

	}
}
PmPageItm *_getCalItm(PmPrintPaperPage* paper);

void PhotoMaker::OnUndo()
{
	//
	this->getEditView()->saveSelection();

	PE_UNDOACT_ITEM _undoActitm;
	if ( !PmUndoActionStack::getInst().popAction(_undoActitm) )
	{
		return ;
	}
	updateUIStatus();

	_undoonprocessing = true;
	switch(_undoActitm.action)
	{
	case PE_UNDOACT_ITEM::ACTION_PG_SETIMG:
	case PE_UNDOACT_ITEM::ACTION_PG_SETLAYOUT:
	case PE_UNDOACT_ITEM::ACTION_IMG_ZOOMIMG:
	case PE_UNDOACT_ITEM::ACTION_IMG_MOVEIMG:
	case PE_UNDOACT_ITEM::ACTION_PG_RMIMG:
	case PE_UNDOACT_ITEM::ACTION_PG_SWITCHIMG:
		{
			// all these are edit a paper
			_undoActitm.saved.pageedit.peditpaper->copy(*_undoActitm.saved.pageedit.psavepaper);
			delete _undoActitm.saved.pageedit.psavepaper; // has item has no parent, must be destroied
			// check if there's 2nd edit paper
			if ( _undoActitm.saved.pageedit.p2ndeditpaper )
			{
				_undoActitm.saved.pageedit.p2ndeditpaper->copy(*_undoActitm.saved.pageedit.p2ndsavepaper);
				delete _undoActitm.saved.pageedit.p2ndsavepaper;
			}
		}
		break;
	case PE_UNDOACT_ITEM::ACTION_PG_EDITIMG:
		{
			// should delete the edit copy file
			if ( _undoActitm.saved.imgedit.pupdatedphotopath )
			{
				QDir dir;
				dir.remove( *_undoActitm.saved.imgedit.pupdatedphotopath);
				delete _undoActitm.saved.imgedit.pupdatedphotopath;
				_undoActitm.saved.imgedit.pupdatedphotopath = NULL;
			}

			// all these are edit a paper
			_undoActitm.saved.imgedit.pphotoeditpaper->copy(*_undoActitm.saved.imgedit.pphotoeditsavepaper);
			delete _undoActitm.saved.imgedit.pphotoeditsavepaper; // has item has no parent, must be destroied

		}
		break;
	case PE_UNDOACT_ITEM::ACTION_PG_ADD_PAPER:
		{
			// the added page should be delted
			PmPrintPaperPage *paddedpaper = _undoActitm.saved.addpaper.paddedpaper;

			int index = 0;
			this->getPreviewView()->rmPaperPage(paddedpaper, index);

			// remove from doc
			_pdoc->rmPrintPaper(paddedpaper, index);

			// this paper should be deleted
			delete paddedpaper;
		}
		break;
	case PE_UNDOACT_ITEM::ACTION_PG_DEL_PAPER:
		{
			// the delete paper should be restored
			PmPrintPaperPage *pdeletedpaper = _undoActitm.saved.rmpaper.pdeletedpaper;
			PmPrintPaperPage * porgbeforepaper = _undoActitm.saved.rmpaper.porgbeforepaper;
			int index = 0;
			this->_pdoc->getPaperIndex(porgbeforepaper, index);

			PmPrintPaperPage *pcurpaper = NULL;
			_pdoc->insertPrintPaper(pdeletedpaper, false, index);
				 
			this->getPreviewView()->addPaperPage(pdeletedpaper, index+1);
		}
		break;
	case PE_UNDOACT_ITEM::ACTION_PG_MV_PAPER:
		{
			// the paper should be moved back to original position

			PmPrintPaperPage *pmvingpaper = _undoActitm.saved.mvpaper.pmvingpaper;
			PmPrintPaperPage * porgbeforepaper = _undoActitm.saved.mvpaper.porgbeforepaper;

			int index = 0;
			this->getPreviewView()->rmPaperPage(pmvingpaper, index);

			_pdoc->rmPrintPaper(pmvingpaper, index);
			_pdoc->getPaperIndex(porgbeforepaper, index);
			_pdoc->insertPrintPaper(pmvingpaper, false, index);
			_pdoc->getPaperIndex(porgbeforepaper, index);
			this->getPreviewView()->addPaperPage(pmvingpaper, index+1);
		}
		break;
	case PE_UNDOACT_ITEM::ACTION_CAL_CFG_EDIT:
		{
			int cnt = _undoActitm.saved.caledit.cnt;
			for ( int i=0; i<cnt; i++ )
			{
				PmPrintPaperPage *paper = _undoActitm.saved.caledit.edtpaper[i];
				PCALENDAR_CFG psavedcalcfg = _undoActitm.saved.caledit.savedcalcfgs[i];
				PmPageItm *calitm = _getCalItm(paper);
				if ( !calitm || !psavedcalcfg )
				{
					continue;
				}
				calitm->setCalProps(psavedcalcfg->calcfg);
				calitm->setWdsProps(psavedcalcfg->wdcfg);
				calitm->setMonthYearProps(psavedcalcfg->monthyearcfg);

				CalViewItm *calviewitm = (CalViewItm *)(calitm->getPageViewItm());
				if ( calviewitm )
				{
					calviewitm->reload();
					calviewitm->getScene()->update();
				}

				CalViewItm *previewitm = (CalViewItm*)calitm->getPreviewPageViewItm();
				if ( previewitm )
				{
					previewitm->update();
					previewitm->getScene()->update();
				}
			}
		}
		break;
	case PE_UNDOACT_ITEM::ACTION_CAL_FIRSTMONTH:
		{
			int firstmonth =  _undoActitm.saved.calfirstmon.firstmonth;
			PmPhotoMakerDoc *pDoc = getDoc();
			PROJ_PROPS proj;
			pDoc->getProjProps(proj);
			proj.firstmonth = firstmonth;
			pDoc->updateProjProps(proj);
		}
		break;
	case PE_UNDOACT_ITEM::ACTION_CAL_YEAR:
		{
			int year =  _undoActitm.saved.calyear.year;
			PmPhotoMakerDoc *pDoc = getDoc();
			PROJ_PROPS proj;
			pDoc->getProjProps(proj);
			proj.year = year;
			pDoc->updateProjProps(proj);
		}
		break;
	case PE_UNDOACT_ITEM::ACTION_PRJ_CHG_SHADOW:
		{
			PROJ_PROPS proj;
			getDoc()->getProjProps(proj);

			bool shadow = _undoActitm.saved.prjprop.shadow;
			_shadowBtn->setChecked(shadow);


			proj.shadow = shadow;
			getDoc()->updateProjProps(proj);

			PhotoEditView *photoEditView = _pCentralPane->getEditView();
			photoEditView->enableShadow(shadow);
		}
		break;
	}
	this->updateViews(true);
	this->getEditView()->restoreSelection();

	this->_pBottomCtrlPane->updateEditPaneInfo();

	_undoonprocessing = false;

}

void PhotoMaker::OnDelSelection()
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();

	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;
	photoEditView->getSelection(pageitm, txtitm);
	PmPrintPaperPage *pcurpaper = NULL;
	int paperindex = 0;
	getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);
	if ( (pageitm || txtitm) && pcurpaper )
	{
		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;
		undoactitm.saved.pageedit.peditpaper =pcurpaper;
		undoactitm.saved.pageedit.psavepaper =getDoc()->createNewPaper();
		if ( undoactitm.saved.pageedit.psavepaper )
		{
			undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
			undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
			//undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
			PmUndoActionStack::getInst().pushAction(undoactitm);
			updateUIStatus();
		}
	}


	photoEditView->delSelection();
}

void PhotoMaker::OnAddTxt()
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();

	// need undo
	PmPrintPaperPage *pcurpaper = NULL;
	int paperindex = 0;
	getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);
	if ( pcurpaper )
	{
		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;
		undoactitm.saved.pageedit.peditpaper = pcurpaper;
		undoactitm.saved.pageedit.psavepaper = getDoc()->createNewPaper();
		if ( undoactitm.saved.pageedit.psavepaper )
		{
			undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
			undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
			//undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
			PmUndoActionStack::getInst().pushAction(undoactitm);
			updateUIStatus();
		}
	}
	photoEditView->addText();
}

void PhotoMaker::OnChgShadow()
{
	PROJ_PROPS proj;
	getDoc()->getProjProps(proj);
	// add later
	PE_UNDOACT_ITEM undoactitm;
	undoactitm.action = PE_UNDOACT_ITEM::ACTION_PRJ_CHG_SHADOW;
	undoactitm.saved.prjprop.shadow = proj.shadow;
	PmUndoActionStack::getInst().pushAction(undoactitm);
	updateUIStatus();


	bool shadow = _shadowBtn->isChecked();
	shadow = !shadow;
	_shadowBtn->setChecked(shadow);


	proj.shadow = shadow;
	getDoc()->updateProjProps(proj);

	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	photoEditView->enableShadow(shadow);
}

void PhotoMaker::OnNextPage()
{
	_pdoc->moveNextPaperPage();

	PmPhotoView *photoEditView = _pCentralPane->getEditView();
	this->updateEditView(true);
	PrintPagesPreviewView *preview = getPreviewView();
	if ( preview )
	{
		int index = 0;
		PmPrintPaperPage *curpaper = NULL;
		_pdoc->getCurPrintPaperPage(curpaper, index);
		preview->updateSelection(index);
	}
}

void PhotoMaker::OnPrePage()
{
	_pdoc->movePrePaperPage();
	PmPhotoView *photoEditView = _pCentralPane->getEditView();
	this->updateEditView(true);
	PrintPagesPreviewView *preview = getPreviewView();
	if ( preview )
	{
		int index = 0;
		PmPrintPaperPage *curpaper = NULL;
		_pdoc->getCurPrintPaperPage(curpaper, index);
		preview->updateSelection(index);
	}
}

void PhotoMaker::OnZoomEditView(qreal scale)
{
    PhotoEditView *photoEditView = _pCentralPane->getEditView();
    if( scale > 3.0 )
        scale = 3.0;
	photoEditView->scaleView(scale);

    //photoEditView->scale(photoEditView->scale_lvl, photoEditView->scale_lvl);
}

void PhotoMaker::OnOrentation()
{
    PhotoEditView *photoEditView = _pCentralPane->getEditView();
	photoEditView->chgOrentation();

}

void PhotoMaker::addPaperAtIndex(int index)
{
	PmPrintPaperPage *oldnextpaper = NULL;
	_pdoc->getNextEditPaper(oldnextpaper);


	 PmPrintPaperPage *newpaper = NULL;
	  PmPrintPaperPage *pcurpaper = NULL;
	 _pdoc->getPaperFromIndex(pcurpaper, index);
	 _pdoc->addPrintPaper(pcurpaper, true, newpaper, index);

	 this->getPreviewView()->addPaperPage(newpaper, index);

	PmPrintPaperPage *nextpaper = NULL;
	_pdoc->getNextEditPaper(nextpaper);

	if ( oldnextpaper != nextpaper )
	{
		//updateNextEditPaper
		getPreviewView()->updateNextEditPaper(oldnextpaper, nextpaper);
	}


	PE_UNDOACT_ITEM undoitm;
	undoitm.action = PE_UNDOACT_ITEM::ACTION_PG_ADD_PAPER;
	undoitm.saved.addpaper.paddedpaper = newpaper;

	PmUndoActionStack &undostack = PmUndoActionStack::getInst();

	undostack.pushAction(undoitm);
	this->updateUIStatus();
}

void PhotoMaker::delPaper(PmPrintPaperPage *paper)
{
	PmPrintPaperPage *oldnextpaper = NULL;
	_pdoc->getNextEditPaper(oldnextpaper);


	PmPrintPaperPage *curpaper = NULL;
	int index = 0;
	_pdoc->getCurPrintPaperPage(curpaper, index);
	if ( curpaper == paper )
	{
		// curent paper will be changed
	}
	// remove from doc
	_pdoc->rmPrintPaper(paper, index);

	this->getPreviewView()->rmPaperPage(paper, index);


	PmPrintPaperPage *nextpaper = NULL;
	_pdoc->getNextEditPaper(nextpaper);

	if ( oldnextpaper != nextpaper )
	{
		//updateNextEditPaper
		getPreviewView()->updateNextEditPaper(oldnextpaper, nextpaper);
	}


	this->updateEditView();

	// save the paper in undo action stack
	PE_UNDOACT_ITEM undoitm;
	undoitm.action = PE_UNDOACT_ITEM::ACTION_PG_DEL_PAPER;
	undoitm.saved.rmpaper.pdeletedpaper = paper;
	PmPrintPaperPage *porgbeforepaper = NULL;
	if ( index > 0 )
	{
		 _pdoc->getPaperFromIndex(porgbeforepaper,index-1);
	}
	undoitm.saved.rmpaper.porgbeforepaper =porgbeforepaper;

	PmUndoActionStack &undostack = PmUndoActionStack::getInst();

	undostack.pushAction(undoitm);
	this->updateUIStatus();

}

void PhotoMaker::mvPaper(PmPrintPaperPage *paper, PmPrintPaperPage *topaper)
{
	int index = 0;

	PmPrintPaperPage *oldnextpaper = NULL;
	_pdoc->getNextEditPaper(oldnextpaper);


	this->getPreviewView()->rmPaperPage(paper, index);

	// remove from doc
	_pdoc->rmPrintPaper(paper, index);
	PmPrintPaperPage * porgbeforepage = NULL;
	if ( index > 0 )
	{
		_pdoc->getPaperFromIndex(porgbeforepage, index-1);
	}

	// inser it
	_pdoc->getPaperIndex(topaper, index);
	_pdoc->insertPrintPaper(paper, true, index);
	_pdoc->getPaperIndex(paper, index);
	this->getPreviewView()->addPaperPage(paper, index);

	PmPrintPaperPage *nextpaper = NULL;
	_pdoc->getNextEditPaper(nextpaper);

	if ( oldnextpaper != nextpaper )
	{
		//updateNextEditPaper
		getPreviewView()->updateNextEditPaper(oldnextpaper, nextpaper);
	}


	// save the paper in undo action stack
	PE_UNDOACT_ITEM undoitm;
	undoitm.action = PE_UNDOACT_ITEM::ACTION_PG_MV_PAPER;

	undoitm.saved.mvpaper.pmvingpaper = paper;
	undoitm.saved.mvpaper.porgbeforepaper =porgbeforepage;

	PmUndoActionStack &undostack = PmUndoActionStack::getInst();

	undostack.pushAction(undoitm);	
	this->updateUIStatus();

}

void PhotoMaker::OnInsPageBefore()
{
	// get current page
	PmPrintPaperPage *pcurpaper = NULL;
	int index = 0;
	_pdoc->getCurPrintPaperPage(pcurpaper, index);
	
	this->addPaperAtIndex(index);
}

void PhotoMaker::OnInsPageAfter()
{
	PmPrintPaperPage *pcurpaper = NULL;
	int index = 0;
	_pdoc->getCurPrintPaperPage(pcurpaper, index);
	
	this->addPaperAtIndex(index+1);
}

void PhotoMaker::OnDelCurPage()
{
	PmPrintPaperPage *pcurpaper = NULL;
	int index = 0;
	_pdoc->getCurPrintPaperPage(pcurpaper,index );

	this->delPaper(pcurpaper);
}


void PhotoMaker::OnRotatePhotoleft()
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	if ( !photoEditView )
	{
		return ;
	}

	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;
	photoEditView->getSelection(pageitm, txtitm);
	PmPrintPaperPage *pcurpaper = NULL;
	int paperindex = 0;
	getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);
	if ( pageitm && pcurpaper )
	{
		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_EDITIMG;
		undoactitm.saved.imgedit.pphotoeditpaper = pcurpaper;
		undoactitm.saved.imgedit.pphotoeditsavepaper = getDoc()->createNewPaper();
		if ( undoactitm.saved.imgedit.pphotoeditsavepaper )
		{
			undoactitm.saved.imgedit.pphotoeditsavepaper->copy(*undoactitm.saved.imgedit.pphotoeditpaper);
			undoactitm.saved.imgedit.pphotoeditsavepaper->setborder(undoactitm.saved.imgedit.pphotoeditpaper->getborder());

			PmUndoActionStack::getInst().pushAction(undoactitm);
			updateUIStatus();
		}
	}
	photoEditView->rotateSelectionleft();
	//this->updateEditView(true);
}

void PhotoMaker::OnRotatePhotoright()
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	if ( !photoEditView )
	{
		return ;
	}

	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;
	photoEditView->getSelection(pageitm, txtitm);
	PmPrintPaperPage *pcurpaper = NULL;
	int paperindex = 0;
	getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);
	if ( pageitm && pcurpaper )
	{
		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_EDITIMG;
		undoactitm.saved.imgedit.pphotoeditpaper = pcurpaper;
		undoactitm.saved.imgedit.pphotoeditsavepaper = getDoc()->createNewPaper();
		if ( undoactitm.saved.imgedit.pphotoeditsavepaper )
		{
			undoactitm.saved.imgedit.pphotoeditsavepaper->copy(*undoactitm.saved.imgedit.pphotoeditpaper);
			undoactitm.saved.imgedit.pphotoeditsavepaper->setborder(undoactitm.saved.imgedit.pphotoeditpaper->getborder());

			PmUndoActionStack::getInst().pushAction(undoactitm);
			updateUIStatus();
		}
	}
	photoEditView->rotateSelectionright();
}

void PhotoMaker::OnSetPhotoHSL()
{
	// spcial, done in photoviewitem
    PhotoEditView *photoEditView = _pCentralPane->getEditView();
    if ( !photoEditView )
    {
            return ;
    }

    photoEditView->setSelectionHSL();
}

void PhotoMaker::OnSetPhotoBWC()
{
	// spcial, done in photoviewitem
    PhotoEditView *photoEditView = _pCentralPane->getEditView();
    if ( !photoEditView )
    {
            return ;
    }

    photoEditView->setSelectionBWC();
}

void PhotoMaker::OnSetPhotoLCIG()
{
	// spcial, done in photoviewitem
    PhotoEditView *photoEditView = _pCentralPane->getEditView();
    if ( !photoEditView )
    {
            return ;
    }

    photoEditView->setSelectionLCIG();
}

void PhotoMaker::OnSetPhotoRE()
{
 	// spcial, done in photoviewitem
   PhotoEditView *photoEditView = _pCentralPane->getEditView();
    if ( !photoEditView )
    {
            return ;
    }

    photoEditView->setSelectionRE();
}

void PhotoMaker::OnZoomPhoto(qreal scale)
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	if ( !photoEditView )
	{
		return ;
	}

	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;
	photoEditView->getSelection(pageitm, txtitm);
	PmPrintPaperPage *pcurpaper = NULL;
	int paperindex = 0;
	getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);
	if ( pageitm && pcurpaper )
	{
		qreal oldratio = 0;
		pageitm->getZoom(oldratio);
		if ( oldratio == scale )
		{
			return;
		}
		static QDateTime lastupdate;
		QDateTime ct;

		ct = QDateTime::currentDateTime();
		if ( abs((int)(ct.toTime_t()- lastupdate.toTime_t())) > 1 )
		{
			lastupdate = ct;
			// save the action for undo
			PE_UNDOACT_ITEM undoactitm;
			undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_EDITIMG;
			undoactitm.saved.imgedit.pphotoeditpaper = pcurpaper;
			undoactitm.saved.imgedit.pphotoeditsavepaper = getDoc()->createNewPaper();
			if ( undoactitm.saved.imgedit.pphotoeditsavepaper )
			{
				undoactitm.saved.imgedit.pphotoeditsavepaper->copy(*undoactitm.saved.imgedit.pphotoeditpaper);
				undoactitm.saved.imgedit.pphotoeditsavepaper->setborder(undoactitm.saved.imgedit.pphotoeditpaper->getborder());

				PmUndoActionStack::getInst().pushAction(undoactitm);
				updateUIStatus();
			}

		}
	}
		
	photoEditView->zoomSelection(scale);
}

void PhotoMaker::OnSetBgColor(const QColor &color)
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	if ( !photoEditView )
	{
		return ;
	}
	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;
	photoEditView->getSelection(pageitm, txtitm);
	PmPrintPaperPage *pcurpaper = NULL;
	int paperindex = 0;
	getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);
	if ( pageitm && pcurpaper )
	{
		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_EDITIMG;
		undoactitm.saved.imgedit.pphotoeditpaper = pcurpaper;
		undoactitm.saved.imgedit.pphotoeditsavepaper = getDoc()->createNewPaper();
		if ( undoactitm.saved.imgedit.pphotoeditsavepaper )
		{
			undoactitm.saved.imgedit.pphotoeditsavepaper->copy(*undoactitm.saved.imgedit.pphotoeditpaper);
			undoactitm.saved.imgedit.pphotoeditsavepaper->setborder(undoactitm.saved.imgedit.pphotoeditpaper->getborder());

			PmUndoActionStack::getInst().pushAction(undoactitm);
			updateUIStatus();
		}
	}
	photoEditView->setBgColor(color);
}


void PhotoMaker::updateCalCfg(const CALENDAR_CFG &calcfg)
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	if ( !photoEditView )
	{
		return ;
	}

	if ( calcfg.forall )
	{
		QList<PmPrintPaperPage*> paperpages;
		getDoc()->getPrintPaperPages(paperpages);
		QList<PmPrintPaperPage*>::iterator it;

		// parepare undo

		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_CAL_CFG_EDIT;
		undoactitm.saved.caledit.cnt = 12;
		int i=0;
		for (it=paperpages.begin(),i=0; it!=paperpages.end(); it++, i++ )
		{
			undoactitm.saved.caledit.edtpaper[i] = *it;
			PmPageItm *calitm = _getCalItm(*it);
			if ( !calitm )
			{
				// must not be
				continue;
			}
			PCALENDAR_CFG psavcalcfg = new CALENDAR_CFG;
			if ( !psavcalcfg )
			{
				// not enough memory
				continue;
			}
			calitm->getCalProps(psavcalcfg->calcfg);
			calitm->getWdsProps(psavcalcfg->wdcfg);
			calitm->getMonthYearProps(psavcalcfg->monthyearcfg);
			undoactitm.saved.caledit.savedcalcfgs[i] = psavcalcfg;
		}
		PmUndoActionStack::getInst().pushAction(undoactitm);
		updateUIStatus();
	}
	else
	{
		// get selection
		PmPageItm *pageitm = NULL;
		PmTextItm *txtitm = NULL;
		photoEditView->getSelection(pageitm, txtitm);
		if ( pageitm && pageitm->getPhotoItmType()==PmPageItm::CALENDAR_ITM)
		{
			// parepare undo
			PE_UNDOACT_ITEM undoactitm;
			undoactitm.action = PE_UNDOACT_ITEM::ACTION_CAL_CFG_EDIT;
			undoactitm.saved.caledit.cnt = 1;
			undoactitm.saved.caledit.edtpaper[0] =pageitm->getPage()->getPaperPage();

			PCALENDAR_CFG psavcalcfg = new CALENDAR_CFG;
			if ( !psavcalcfg )
			{
				// not enough memory
				return ;
			}
			pageitm->getCalProps(psavcalcfg->calcfg);
			pageitm->getWdsProps(psavcalcfg->wdcfg);
			pageitm->getMonthYearProps(psavcalcfg->monthyearcfg);
			undoactitm.saved.caledit.savedcalcfgs[0] = psavcalcfg;
			PmUndoActionStack::getInst().pushAction(undoactitm);
			updateUIStatus();

		}


	}
	photoEditView->updateSelCalCfg(calcfg);

}

bool PhotoMaker::getSelCalCfg(CALENDAR_CFG &calcfg)
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	if ( !photoEditView )
	{
		return false;
	}
	return photoEditView->getSelCalCfg(calcfg);
}

void PhotoMaker::updateFirstCalMonth(int firstmonth)
{
	//
	PmPhotoMakerDoc *pDoc = getDoc();
	PROJ_PROPS proj;
	pDoc->getProjProps(proj);
	if ( proj.type != PROJ_PROPS::CALENDARA4 && 
		proj.type != PROJ_PROPS::CALENDARA5 && 
		proj.type != PROJ_PROPS::CALENDAR4X6 )
	{
		//
		return ;
	}
	// save for undo first
	PE_UNDOACT_ITEM undoactitm;
	undoactitm.action = PE_UNDOACT_ITEM::ACTION_CAL_FIRSTMONTH;
	undoactitm.saved.calfirstmon.firstmonth = proj.firstmonth;
	PmUndoActionStack::getInst().pushAction(undoactitm);
	updateUIStatus();

	proj.firstmonth = firstmonth;
	pDoc->updateProjProps(proj);

	updateViews(true);
}

void PhotoMaker::updateCalYear(int year)
{
//updateProjProps
	PmPhotoMakerDoc *pDoc = getDoc();

	PROJ_PROPS proj;
	pDoc->getProjProps(proj);
	if ( proj.type != PROJ_PROPS::CALENDARA4 && 
		proj.type != PROJ_PROPS::CALENDARA5 && 
		proj.type != PROJ_PROPS::CALENDAR4X6 )
	{
		//
		return ;
	}
	// save for undo first
	PE_UNDOACT_ITEM undoactitm;
	undoactitm.action = PE_UNDOACT_ITEM::ACTION_CAL_YEAR;
	undoactitm.saved.calyear.year = proj.year;
	PmUndoActionStack::getInst().pushAction(undoactitm);
	updateUIStatus();


	proj.year = year;

	pDoc->updateProjProps(proj);
	updateViews(true);
}


void PhotoMaker::OnAlignText(int align)
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	if ( !photoEditView )
	{
		return ;
	}

	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;
	photoEditView->getSelection(pageitm, txtitm);
	PmPrintPaperPage *pcurpaper = NULL;
	int paperindex = 0;
	getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);

	if ( txtitm && pcurpaper)
	{

		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;
		undoactitm.saved.pageedit.peditpaper = pcurpaper;
		undoactitm.saved.pageedit.psavepaper = getDoc()->createNewPaper();
		if ( undoactitm.saved.pageedit.psavepaper )
		{
			undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
			undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
			//undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
			PmUndoActionStack::getInst().pushAction(undoactitm);
			updateUIStatus();
		}
	}


	return photoEditView->alignText(align);

}

void PhotoMaker::OnValignText(int valign)
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	if ( !photoEditView )
	{
		return ;
	}

	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;
	photoEditView->getSelection(pageitm, txtitm);
	PmPrintPaperPage *pcurpaper = NULL;
	int paperindex = 0;
	getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);

	if ( txtitm && pcurpaper)
	{

		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;
		undoactitm.saved.pageedit.peditpaper = pcurpaper;
		undoactitm.saved.pageedit.psavepaper = getDoc()->createNewPaper();
		if ( undoactitm.saved.pageedit.psavepaper )
		{
			undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
			undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
			//undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
			PmUndoActionStack::getInst().pushAction(undoactitm);
			updateUIStatus();
		}
	}


	return photoEditView->valignText(valign);


}

void PhotoMaker::OnSetTextShadow(bool shadow)
{
	PROJ_PROPS proj;
	_pdoc->getProjProps(proj);
	if ( proj.shadow == shadow )
	{
		return ;
	}
	proj.shadow = shadow;
	_pdoc->updateProjProps(proj);

	//
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	if ( !photoEditView )
	{
		return ;
	}
	photoEditView->enableTxtShadow(shadow);
}

void PhotoMaker::OnSetTextCnt(QString &txt, qreal font_ratio)
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	if ( !photoEditView )
	{
		return ;
	}
	if ( _undoonprocessing )
	{
		return ;
	}


	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;
	photoEditView->getSelection(pageitm, txtitm);
	PmPrintPaperPage *pcurpaper = NULL;
	int paperindex = 0;
	getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);

	if ( txtitm && pcurpaper)
	{
		QString oldcnt;
		txtitm->getContent(oldcnt);
		if ( oldcnt == txt )
		{
			return;
		}

		QDateTime ct = QDateTime::currentDateTime();
		int losttime = ct.toTime_t()-txtitm->getLastBackTime().toTime_t();
		if ( abs(losttime) > 5)
		{
			txtitm->setLastBackTime(ct);
			PE_UNDOACT_ITEM undoactitm;
			undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;
			undoactitm.saved.pageedit.peditpaper = pcurpaper;
			undoactitm.saved.pageedit.psavepaper = getDoc()->createNewPaper();
			if ( undoactitm.saved.pageedit.psavepaper )
			{
				undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
				undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
				//undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
				PmUndoActionStack::getInst().pushAction(undoactitm);
				updateUIStatus();
			}
		}
	}

    
	return photoEditView->setTextCnt(txt, font_ratio);
}


void PhotoMaker::OnMvTxtBox(QRectF itmrct,int state)
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	if ( !photoEditView )
	{
		return ;
	}

	PhotoEditViewScene *editscene = dynamic_cast<PhotoEditViewScene *>(photoEditView->scene());
	if ( !editscene )
	{
		return ;
	}
	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;
	photoEditView->getSelection(pageitm, txtitm);
	if ( !txtitm )
	{
		return ;
	}

	if ( state == 0 )
	{
		PmPrintPaperPage *pcurpaper = NULL;
		int paperindex = 0;
		getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);
		if ( pcurpaper )
		{
			// begin
			PE_UNDOACT_ITEM undoactitm;
			undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;
			undoactitm.saved.pageedit.peditpaper = pcurpaper;
			undoactitm.saved.pageedit.psavepaper = getDoc()->createNewPaper();
			if ( undoactitm.saved.pageedit.psavepaper )
			{
				undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
				undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
				//undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
				PmUndoActionStack::getInst().pushAction(undoactitm);
				updateUIStatus();
			}
		}
	}

	editscene->updateTextItm(txtitm, itmrct);
	editscene->update();
}

void PhotoMaker::OnRotateTxtBox(QRectF itmrct, int angel,int state)
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	if ( !photoEditView )
	{
		return ;
	}

	PhotoEditViewScene *editscene = dynamic_cast<PhotoEditViewScene *>(photoEditView->scene());
	if ( !editscene )
	{
		return ;
	}
	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;
	photoEditView->getSelection(pageitm, txtitm);
	if ( !txtitm )
	{
		return ;
	}

	if ( state == 0 )
	{
		PmPrintPaperPage *pcurpaper = NULL;
		int paperindex = 0;
		getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);
		if ( pcurpaper )
		{
			// begin
			PE_UNDOACT_ITEM undoactitm;
			undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;
			undoactitm.saved.pageedit.peditpaper = pcurpaper;
			undoactitm.saved.pageedit.psavepaper = getDoc()->createNewPaper();
			if ( undoactitm.saved.pageedit.psavepaper )
			{
				undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
				undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
				//undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
				PmUndoActionStack::getInst().pushAction(undoactitm);
				updateUIStatus();
			}
		}
	}

	editscene->updateTextItm(txtitm, itmrct);
	editscene->update();
}

void PhotoMaker::OnResizeTxtBox(QRectF itmrct,int state)
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	if ( !photoEditView )
	{
		return ;
	}

	PhotoEditViewScene *editscene = dynamic_cast<PhotoEditViewScene *>(photoEditView->scene());
	if ( !editscene )
	{
		return ;
	}
	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;
	photoEditView->getSelection(pageitm, txtitm);
	if ( !txtitm )
	{
		return ;
	}

	if ( state == 0 )
	{
		PmPrintPaperPage *pcurpaper = NULL;
		int paperindex = 0;
		getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);
		if ( pcurpaper )
		{
			// begin
			PE_UNDOACT_ITEM undoactitm;
			undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;
			undoactitm.saved.pageedit.peditpaper = pcurpaper;
			undoactitm.saved.pageedit.psavepaper = getDoc()->createNewPaper();
			if ( undoactitm.saved.pageedit.psavepaper )
			{
				undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
				undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
				//undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
				PmUndoActionStack::getInst().pushAction(undoactitm);
				updateUIStatus();
			}
		}
	}

	editscene->updateTextItm(txtitm, itmrct);
	editscene->update();
}



void PhotoMaker::updateUIStatus()
{
	if ( !PmUndoActionStack::getInst().hasActionStored() )
	{
		// disable undo button
		_undoAct->setEnabled(false);
		_undoBtn->setEnabled(false);
	}
	else
	{
		// enable undo button
		_undoAct->setEnabled(true);
		_undoBtn->setEnabled(true);

	}

	//
	PROJ_PROPS proj;
	this->_pdoc->getProjProps(proj);
	switch ( proj.type )
	{
	case PROJ_PROPS::CALENDARA4:
	case PROJ_PROPS::CALENDARA5:
	case PROJ_PROPS::CALENDAR4X6:
	case PROJ_PROPS::SINGLE4X6:
	case PROJ_PROPS::PHOTOBOOK10X15:
		{
			this->_shadowBtn->setEnabled(false);
		}
		break;
	default:
		{
			if ( proj.hasborder )
			{
				this->_shadowBtn->setEnabled(true);
				this->_shadowBtn->setChecked(proj.shadow);

			}
			else
			{
				this->_shadowBtn->setEnabled(false);
			}
		}

	}

	//this->_pBottomCtrlPane->updateEditPaneInfo();
}

void PhotoMaker::closeEvent(QCloseEvent *e)
{
	// first shutdown work threads
	QString curshowpath;
	_pLeftPane->getCurShowFolder(curshowpath);
	this->_appcfg.setPicViewDir(curshowpath);
	this->_pLeftPane->cleanup();

	_appcfg.saveCfg("appcfg.xml");

	QMainWindow::closeEvent(e);

}

// system button command
void PhotoMaker::OnClose()
{
	//
	if ( PmUndoActionStack::getInst().isUpdated() )
	{
		//
		QMessageBox confirmdlg(QMessageBox::Question, tr("Confirmation"),
			tr("The current project is not saved.\n Do you want to save it now?"),
			QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel ,this);
		
		int ret = confirmdlg.exec();	
		if ( ret == QMessageBox::Yes )
		{
			this->OnSaveProj();
		}
		else if ( ret == QMessageBox::Cancel )
		{
			return ;
		}
	}


	this->close();
}


bool PhotoMaker::isWndMaxmized()
{
	QDesktopWidget* desktop = QApplication::desktop();
	QRect desktoprc = desktop->availableGeometry (); 

	QRect currc = this->geometry();

	return currc == desktoprc;

}
void PhotoMaker::OnMaxmize()
{
	_appcfg.setMaximized(true);
	_normalRc = this->geometry();

	QDesktopWidget* desktop = QApplication::desktop();
	QRect rc = desktop->availableGeometry (); 
	this->move(rc.left(), rc.top());
	this->resize(rc.width(), rc.height());
	//this->showMaximized();
}
void PhotoMaker::OnMinimize()
{
	this->showMinimized();
}
void PhotoMaker::OnRestore()
{
	_appcfg.setMaximized(false);
	//this->showNormal();
	move(_normalRc.left(), _normalRc.top());
	resize(_normalRc.width(), _normalRc.height());
}

void PhotoMaker::OnAbout()
{
	PmAboutDlg dlg;
	dlg.exec();
}

	//
void PhotoMaker::OnCut()
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();

	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;
	photoEditView->getSelection(pageitm, txtitm);
	PmPrintPaperPage *pcurpaper = NULL;
	int paperindex = 0;
	getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);

	if ( pcurpaper && (pageitm ||  txtitm) )
	{

		// parepare undo
		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;
		undoactitm.saved.pageedit.peditpaper = pcurpaper;
		undoactitm.saved.pageedit.psavepaper = getDoc()->createNewPaper();
		if ( undoactitm.saved.pageedit.psavepaper )
		{
			undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
			undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
			//undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
			PmUndoActionStack::getInst().pushAction(undoactitm);
			updateUIStatus();	
		}
	}

	photoEditView->cutSelection();

}

void PhotoMaker::OnCopy()
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	photoEditView->copySelection();
}

void PhotoMaker::OnPaste()
{
	PhotoEditView *photoEditView = _pCentralPane->getEditView();
	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;
	photoEditView->getSelection(pageitm, txtitm);
	PmPrintPaperPage *pcurpaper = NULL;
	int paperindex = 0;
	getDoc()->getCurPrintPaperPage(pcurpaper, paperindex);

	if ( pcurpaper && (pageitm ||  txtitm) )
	{

		// parepare undo
		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;
		undoactitm.saved.pageedit.peditpaper = pcurpaper;
		undoactitm.saved.pageedit.psavepaper = getDoc()->createNewPaper();
		if ( undoactitm.saved.pageedit.psavepaper )
		{
			undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
			undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
			//undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
			PmUndoActionStack::getInst().pushAction(undoactitm);
			updateUIStatus();	
		}
	}
	photoEditView->pasteSelection();
}

void PhotoMaker::OnLangchg()
{

	QList<QAction *>::iterator it;
	QList<QString>::iterator itshortname;
	for ( it=this->_langActs.begin(), itshortname = this->_langshortnames.begin(); 
		it!=_langActs.end() && itshortname!=_langshortnames.end(); it++,itshortname++ )
	{
		if ( (*it)->isChecked() )
		{
			//
			break;
		}
	}
	if ( it == _langActs.end() || itshortname == _langshortnames.end() )
	{
		return ;
	}
	QAction *langact = *it;
	QString shortlangname = *itshortname;
	QString langname , langfile;
	this->_getLangName(shortlangname, langname);
	_chgLang(langname, langfile);

	this->_appcfg.setLang(langname, langfile);
}

void PhotoMaker::_selLangMenu(const QString &langname)
{
	QList<QAction *>::iterator it;
	QList<QString>::iterator itshortname;
	for ( it=this->_langActs.begin(), itshortname = this->_langshortnames.begin(); 
		it!=_langActs.end() && itshortname!=_langshortnames.end(); it++,itshortname++ )
	{
		QAction *langact = *it;
		QString shortlangname = *itshortname;
		QString chklangname ;
		this->_getLangName(shortlangname, chklangname);
		if ( chklangname == langname )
		{
			(*it)->setChecked(true);
			break;
		}

	}
}


void PhotoMaker::_chgLang(const QString &langname,  QString &langfile1)
{
	QString langfile = langfile1;
	if ( !langfile.length()  )
	{
		if (  !this->_getLangFile(langname, langfile) )
		{
			return ;
		}
		langfile = "./lang/" + langfile;
		langfile1 = langfile;
	}

	static QTranslator *translator = NULL;
	if ( translator )
	{
		g_app->removeTranslator(translator);
		delete translator;
		translator = NULL;
	}
	translator = new QTranslator(this);
	translator->load(langfile);
	
    g_app->installTranslator(translator);
	//QCoreApplication::instance()->installTranslator(&translator);

	_translateLang();
}


bool PhotoMaker::_getLangName(const QString &langshortname, QString &langname)
{
	QString sn = langshortname;
	if ( sn == "zh-cn" )
	{
		langname = tr("Simple Chinese");
	}
	else if ( sn == "zh-tw" )
	{
		langname = tr("Traditional Chinese");
	}
	else if ( sn == "zh-hk" )
	{
		langname = tr("Traditional Chinese");
	}
	else if ( sn == "en" )
	{
		langname = tr("English");
	}
	else if ( sn == "fi" || sn == "fi-fi" )
	{
		langname = tr("Finnish");
	}
	else if ( sn == "da" || sn== "da-dk" )
	{
		langname = tr("Danish");
	}
	else if ( sn == "ko" || sn == "ko-kr" )
	{
		langname = tr("Korean");
	}
	else if ( sn== "ja" || sn == "ja-jp" )
	{
		langname = tr("Japanese");
	}
	else if ( sn == "nl" || sn == "nl-nl" )
	{
		langname = tr("Dutch");
	}
	else if ( sn == "pt" )
	{
		langname = tr("Portuguese");
	}
	else if ( sn == "fr" )
	{
		langname = tr("French");
	}
	else if ( sn == "es" )
	{
		langname = tr("Spanish");
	}
	else if ( sn == "de" )
	{
		langname = tr("German");
	}
	else if ( sn == "ru" )
	{
		langname = tr("Russian");
	}
	else if ( sn == "it" )
	{
		langname = tr("Italian");
	}
	else if ( sn == "no" )
	{
		langname = tr("Norwegian");
	}
	else if ( sn == "hu" )
	{
		langname = tr("Hungarian");
	}
	else if ( sn == "tr" )
	{
		langname = tr("Turkish");
	}
	else if ( sn == "cs" )
	{
		langname = tr("Czech");
	}
	else if ( sn == "sl" )
	{
		langname = tr("Slovenian");
	}
	else if ( sn == "ar" )
	{
		langname = tr("Arabic");
	}
	else if ( sn == "hi" )
	{
		langname = tr("Hindi");
	}
	else if ( sn == "iw" )
	{
		langname = tr("Hebrew");
	}
	else if ( sn == "vi" )
	{
		langname = tr("Vietnamese");
	}


	return true;
}
bool PhotoMaker::_getLangFile(const QString &langname, QString &langfilename)
{
	QString str = tr("Simple Chinese");
	if ( langname == tr("Simple Chinese") )
	{
		langfilename = "photomaker_zh-cn.qm";
	}
	else if ( langname == tr("Traditional Chinese") )
	{
		langfilename = "photomaker_zh-tw.qm";
	}
	else if ( langname == tr("Traditional Chinese") )
	{
		langfilename = "photomaker_zh-hk.qm";
	}
	else if ( langname == tr("English") )
	{
		langfilename = "photomaker_en.qm";
	}
	else if ( langname == tr("Finnish") )
	{
		langfilename = "photomaker_fi.qm";
	}
	else if ( langname == tr("Danish") )
	{
		langfilename = "photomaker_da.qm";
	}
	else if ( langname == tr("Korean") )
	{
		langfilename = "photomaker_ko.qm";
	}
	else if ( langname == tr("Japanese") )
	{
		langfilename = "photomaker_ja.qm";
	}
	else if ( langname == tr("Dutch") )
	{
		langfilename = "photomaker_nl.qm";
	}
	else if ( langname == tr("Portuguese") )
	{
		langfilename = "photomaker_pt.qm";
	}
	else if ( langname == tr("French") )
	{
		langfilename = "photomaker_fr.qm";
	}
	else if ( langname == tr("Spanish") )
	{
		langfilename = "photomaker_es.qm";
	}
	else if ( langname == tr("German") )
	{
		langfilename = "photomaker_de.qm";
	}
	else if ( langname == tr("Russian") )
	{
		langfilename = "photomaker_ru.qm";
	}
	else if ( langname == tr("Italian") )
	{
		langfilename = "photomaker_it.qm";
	}
	else if ( langname == tr("Norwegian") )
	{
		langfilename = "photomaker_no.qm";
	}
	else if ( langname == tr("Hungarian") )
	{		
		langfilename = "photomaker_hu.qm";
	}
	else if ( langname == tr("Turkish") )
	{
		langfilename = "photomaker_tr.qm";
	}
	else if ( langname == tr("Czech") )
	{
		langfilename = "photomaker_cs.qm";
	}
	else if ( langname == tr("Slovenian") )
	{
		langfilename = "photomaker_sl.qm";
	}
	else if ( langname == tr("Arabic") )
	{
		langfilename = "photomaker_ar.qm";
	}
	else if ( langname == tr("Hindi") )
	{
		langfilename = "photomaker_hi.qm";
	}
	else if ( langname == tr("Hebrew") )
	{
		langfilename = "photomaker_iw.qm";
	}
	else if (langname == tr("Vietnamese") )
	{
		langfilename = "photomaker_vi.qm";
	}

	return true;
}

void PhotoMaker::_createLangItms()
{
	//
	// enum lang folder to find all languages
	//
	QDir langdir(".\\lang");
	QFileInfoList list = langdir.entryInfoList();
	if ( list.size() <= 0 )
	{
		// no language packages
		return ;
	}

	if ( _langactGroup )
	{
		delete _langactGroup;
		_langactGroup = NULL;
	}
	_langactGroup = new QActionGroup(this);
	_langshortnames.clear();
	_langActs.clear();
	for ( int i=0; i<list.size(); i++ )
	{
		QFileInfo fileInfo = list.at(i);
		if ( fileInfo.isDir() )
		{
			continue;
		}
		QString filename = fileInfo.baseName();
		QString ext = fileInfo.completeSuffix();
		if ( ext != "qm" )
		{
			continue;
		}
		QString langpart;
		langpart = filename;
		int pos = langpart.indexOf("_");
		if ( pos == -1 )
		{
			continue;
		}
		langpart = langpart.right(langpart.length()-(pos+1));
		QString langname;
		if ( !_getLangName(langpart, langname) )
		{
			continue;
		}

		QAction *pLangAct = NULL;
		pLangAct = new QAction(langname, this);
		pLangAct->setStatusTip(langname);
		pLangAct->setCheckable(true);
		this->_langActs.push_back(pLangAct);
		_langshortnames.push_back(langpart);
		_langactGroup->addAction(pLangAct);
		if ( langname == tr("English") )
		{
			pLangAct->setChecked(true);
		}
		connect(pLangAct, SIGNAL(triggered()), this, SLOT(OnLangchg()));
	}

}

void PhotoMaker::_updateLangMenuItmsLang()
{
	QList<QAction *>::iterator it;
	QList<QString>::iterator itsname;
	for ( it=_langActs.begin(), itsname=this->_langshortnames.begin(); 
		it!=_langActs.end() && itsname!=_langshortnames.end(); it++,itsname++ )
	{

		QAction *pLangAct = *it;
		QString langshortname = *itsname;
		if ( !pLangAct )
		{
			continue;
		}
		QString langname;
		this->_getLangName(langshortname, langname);
		pLangAct->setText(langname);
		pLangAct->setStatusTip(langname);
	}
}

void PhotoMaker::_translateLang()
{
	_updateLangMenuItmsLang();

	_newAct->setText(tr("New..."));
	_newAct->setStatusTip(tr("Create a new print project"));
	_openAct->setText(tr("Open..."));
	_openAct->setStatusTip(tr("Open a  print project"));
	_saveAct->setText(tr("Save..."));
	_saveAct->setStatusTip(tr("Save the current project"));
	_saveAsAct->setText(tr("Save as..."));
	_saveAsAct->setStatusTip(tr("Save the current project"));

	_undoAct->setText( tr("Undo"));
	_undoAct->setStatusTip(tr("Undo the last editing action"));

	_quitCurPrjAct->setText(tr("Quit"));
	_quitCurPrjAct->setStatusTip(tr("Quit the application"));


	_aboutAct->setText(tr("About"));
	_aboutAct->setStatusTip(tr("Show the application's About box"));

	_cutAct->setText(tr("Cut"));
	_cutAct->setStatusTip(tr("Cut"));
	_copyAct ->setText(tr("Copy"));
	_copyAct->setStatusTip(tr("Copy"));
	_pasteAct ->setText(tr("Paste"));
	_pasteAct->setStatusTip(tr("Paste"));


	if ( _newBtn )
	{
		_newBtn->setText(tr("New"));
	}
	if ( _opnBtn )
	{
		_opnBtn->setText(tr("Open"));
	}
	if ( _savBtn )
	{
		_savBtn->setText(tr("Save"));
	}
	if ( _prntBtn )
	{
		_prntBtn->setText(tr("Print"));
	}
	if ( _undoBtn )
	{
		_undoBtn->setText(tr("Undo"));
	}
	if ( _delBtn )
	{
		_delBtn->setText(tr("Delete"));
	}
	if ( _orientationBtn )
	{
		_orientationBtn->setText(tr("Orientation"));
	}
	if ( _addtxtBtn )
	{
		_addtxtBtn->setText(tr("Text"));
	}
	if ( _shadowBtn )
	{
		_shadowBtn->setText(tr("Picure Shadow"));
	}
	if ( _quitBtn )
	{
		_quitBtn->setText(tr("Quit"));
	}
	statusBar()->showMessage(tr("Ready"));


	if ( _toplabel )
	{
		_toplabel->reTranslateLang();
	}
	if ( _pLeftPane )
	{
		_pLeftPane->reTranslate();
	}
	if ( _pBottomCtrlPane )
	{
		this->_pBottomCtrlPane->reTranslate();
	}

	if ( _pCentralPane )
	{
		_showPageIndexInfo();
		this->_pCentralPane->getEditView()->reTranslate();
	}
	if ( _pBottomCtrlPane )
	{
		this->_pBottomCtrlPane->getPreviewView()->reTranslate();
	}
}


bool PhotoMaker::_isSinglePageProj()
{
	PROJ_PROPS proj;
	this->getDoc()->getProjProps(proj);
	switch(proj.type)
	{
	case PROJ_PROPS::PHOTOBOOK10X15:
	case PROJ_PROPS::SINGLE4X6:
		return true;
		break;
	default:
		;
	}

	return false;

}

bool PhotoMaker::_isCalendarPrj()
{
	PROJ_PROPS proj;
	this->getDoc()->getProjProps(proj);
	switch(proj.type)
	{
	case PROJ_PROPS::CALENDARA4:
	case PROJ_PROPS::CALENDARA5:
	case PROJ_PROPS::CALENDAR4X6:
		return true;
		break;
	default:
		;
	}

	return false;

}



void PhotoMaker::_showPageIndexInfo()
{

	PmPrintPaperPage *pcurpaper = NULL;
	int index;
	if ( !_pdoc->getCurPrintPaperPage(pcurpaper, index) )
	{
		return ;
	}


	QString labeltxt;
	if ( _isCalendarPrj() )
	{
		QString monlst[] = {tr("January"), tr("February"), tr("March"), tr("April"),
			tr("May"), tr("June"), tr("July"), tr("August"), tr("September"),tr("October"),
			tr("Novermber"), tr("December")};
		
		if ( index >= 0 && index < 12)
		{
			int year = 1;
			int month = 1;
			PmPageItm *calitm = this->getDoc()->getCalItm(pcurpaper);
			if ( calitm )
			{
				calitm->getMonth(year, month);
			}

			labeltxt = monlst[month-1];
		}
	}
	else if ( _isSinglePageProj())
	{
		labeltxt = QString(tr("Page %1")).arg(index+1);
	}
	else
	{
		QList<PmPhotoPage *> photopages;
		pcurpaper->getPhotoPages(photopages);
		QList<PmPrintPaperPage*> paperpages;
		getDoc()->getPrintPaperPages(paperpages);


		if ( index == 0  )
		{
			labeltxt = QString(tr("Page %1")).arg(2*index+1);
		}
		else if ( index == paperpages.size() - 1 )
		{
			labeltxt = QString(tr("Page %1")).arg(2*index);
		}
		else 
		{
			labeltxt = QString(tr("Page %1-%2")).arg(2*index).arg(2*index+1);
		}
	}
	_pCentralPane->showPageInfo(labeltxt);


}


#define TITLE_BTN_X		10
#define TITLE_BTN_Y		20
#define TITLE_BTN_HEIGHT	22
#define TITLE_BTN_WIDTH	72
#define TITLE_BTN_SPAN	10

TopInfoLabel::TopInfoLabel(QWidget *parent, PhotoMaker *pframe):
_frame(pframe), QLabel(parent),_pressed(false), _maxized(false)
{
	PhotoMaker *pFrame = dynamic_cast<PhotoMaker *>(_frame);
	if ( !pFrame )
	{
		return ;
	}
	
	pFile = new QPushButton(tr("File"),this);
	pFile->setFlat(true);
	pFile->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton:hover{background-image:url(" + gbires + "titlebtnbg.png)}"
		"QPushButton:pressed{background: qradialgradient(cx: 0.3, cy: -0.4,fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);}");
	pFile->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gbires + "menu_long_btn.png)}"
		"QPushButton:hover{background-image:url(" + gbires + "menu_long_btn_hover.png)}");


	QMenu  *menu = new QMenu(pFrame);
	menu->addAction(pFrame->_newAct);
	menu->addAction(pFrame->_openAct);
	menu->addAction(pFrame->_saveAct);
	menu->addAction(pFrame->_saveAsAct);
	menu->addSeparator();
	menu->addAction(pFrame->_printAct);

	menu->addSeparator();
	menu->addAction(pFrame->_exitAppAct);
	pFile->setMenu(menu);
	
	pEdit = new QPushButton(tr("Edit"), this);
	pEdit->setFlat(true);
	//pEdit->setStyleSheet("background-image:url(" + gbires + "titlebtnbg.png)");
	pEdit->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton:hover{background-image:url(" + gbires + "titlebtnbg.png)}"
		"QPushButton:pressed{background: qradialgradient(cx: 0.3, cy: -0.4,fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);}");
	pEdit->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gbires + "menu_long_btn.png)}"
		"QPushButton:hover{background-image:url(" + gbires + "menu_long_btn_hover.png)}");


	QMenu  *editmenu = new QMenu(pFrame);
	editmenu->addAction(pFrame->_undoAct);
	editmenu->addSeparator();
	editmenu->addAction(pFrame->_cutAct);
	editmenu->addAction(pFrame->_copyAct);
	editmenu->addAction(pFrame->_pasteAct);
	//menu->addAction(pFrame->save
	pEdit->setMenu(editmenu);

	pLanguage = new QPushButton(tr("Language"), this);
	pLanguage->setFlat(true);
	pLanguage->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton:hover{background-image:url(" + gbires + "titlebtnbg.png)}"
		"QPushButton:pressed{background: qradialgradient(cx: 0.3, cy: -0.4,fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);}");
	pLanguage->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gbires + "menu_long_btn.png)}"
		"QPushButton:hover{background-image:url(" + gbires + "menu_long_btn_hover.png)}");

	QMenu  *langmenu = new QMenu(pFrame);
	QList<QAction *> &langactlst = pFrame->_langActs;

	QList<QAction *>::iterator it;
	for ( it=langactlst.begin(); it!=langactlst.end(); it++ )
	{
		//
		langmenu->addAction(*it);
	}
	pLanguage->setMenu(langmenu);

	pHelp = new QPushButton(tr("Help"), this);
	pHelp->setFlat(true);
	pHelp->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton:hover{background-image:url(" + gbires + "titlebtnbg.png)}"
		"QPushButton:pressed{background: qradialgradient(cx: 0.3, cy: -0.4,fx: 0.3, fy: -0.4,radius: 1.35, stop: 0 #fff, stop: 1 #888);}");
	pHelp->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gbires + "menu_long_btn.png)}"
		"QPushButton:hover{background-image:url(" + gbires + "menu_long_btn_hover.png)}");

	QMenu  *helpmenu = new QMenu(pFrame);
	helpmenu->addAction(pFrame->_aboutAct);
	//menu->addAction(pFrame->save
	pHelp->setMenu(helpmenu);

	//
	pMinWin = new QPushButton( this);
	pMinWin->setFlat(true);
	pMinWin->setStyleSheet("background-image:url(" + gbires + "min_wind_btn.png)");
	pMinWin->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gbires + "min_btn.png)}"
		"QPushButton:hover{background-image:url(" + gbires + "min_btn_hover.png)}");

	pMaxWin = new QPushButton( this);
	pMaxWin->setFlat(true);
	pMaxWin->setStyleSheet("background-image:url(" + gbires + "max_wind_btn.png)");
	pMaxWin->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gbires + "max_btn.png)}"
		"QPushButton:hover{background-image:url(" + gbires + "max_btn_hover.png)}");
	pRestoreWin = new QPushButton( this);
	pRestoreWin->setFlat(true);
	pRestoreWin->setStyleSheet("background-image:url(" + gbires + "restor_wind_btn.png)");
	pRestoreWin->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gbires + "max_btn.png)}"
		"QPushButton:hover{background-image:url(" + gbires + "max_btn_hover.png)}");


	pCloseWin = new QPushButton( this);
	pCloseWin->setFlat(true);
	pCloseWin->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gbires + "close_btn.png)}"
		"QPushButton:hover{background-image:url(" + gbires + "close_btn_hover.png)}");
 


	QRect rect(TITLE_BTN_X, TITLE_BTN_Y, TITLE_BTN_WIDTH, TITLE_BTN_HEIGHT);
	pFile->setGeometry(rect);
	rect.adjust(TITLE_BTN_WIDTH+TITLE_BTN_SPAN, 0, TITLE_BTN_WIDTH+TITLE_BTN_SPAN, 0);
	pEdit->setGeometry(rect);
	rect.adjust(TITLE_BTN_WIDTH+TITLE_BTN_SPAN, 0, TITLE_BTN_WIDTH+TITLE_BTN_SPAN, 0);
	pLanguage->setGeometry(rect);
	rect.adjust(TITLE_BTN_WIDTH+TITLE_BTN_SPAN, 0, TITLE_BTN_WIDTH+TITLE_BTN_SPAN, 0);
	pHelp->setGeometry(rect);

	if ( pframe->isMaximized() )
	{
		pRestoreWin->show();
		pMaxWin->hide();
	}
	else
	{
		pRestoreWin->hide();
		pMaxWin->show();
	}


	connect(pCloseWin,SIGNAL(clicked()), this->_frame, SLOT(OnClose()));
	connect(pMinWin,SIGNAL(clicked()), this->_frame, SLOT(OnMinimize()));
	connect(pMaxWin,SIGNAL(clicked()), this->_frame, SLOT(OnMaxmize()));
	connect(pRestoreWin,SIGNAL(clicked()), this->_frame, SLOT(OnRestore()));

	connect(pMaxWin,SIGNAL(clicked()), this, SLOT(OnMaxmize()));
	connect(pRestoreWin,SIGNAL(clicked()), this, SLOT(OnRestore()));



}

TopInfoLabel::~TopInfoLabel()
{
}

void TopInfoLabel::reTranslateLang()
{
	pFile->setText(tr("File"));
	pEdit->setText(tr("Edit"));
	pLanguage->setText(tr("Language"));
	pHelp->setText(tr("Help"));
}

#define WIN_OP_BTN_SIZE_X	32
#define WIN_OP_BTN_SIZE_Y	17
#define WIN_OP_BTN_SPAN	5

void TopInfoLabel::resizeEvent(QResizeEvent *)
{
	/*
    QPainterPath path;
 
     QRectF rect1 = this->geometry();
	 rect1.adjust(-rect1.left(),-rect1.top(), -rect1.left(), -rect1.top());
 
     path.addRoundRect(rect1,1,1);
 
        
 
    QPolygon polygon= path.toFillPolygon().toPolygon();//获得这个路径上的所有的点
 
	QRegion region(polygon);//根据这个点构造这个区域
 
	setMask(region);
	*/


	if ( _frame->isWndMaxmized() )
	{
		pRestoreWin->show();
		pMaxWin->hide();
	}
	else
	{
		pRestoreWin->hide();
		pMaxWin->show();
	}


	//
	QRect rect = this->geometry();

	int btn_xstart_pos = rect.width()-(WIN_OP_BTN_SIZE_X+WIN_OP_BTN_SPAN)*3 - WIN_OP_BTN_SPAN;
	int btn_y_pos = WIN_OP_BTN_SPAN;

	QRect btnrect = QRect(btn_xstart_pos,btn_y_pos, WIN_OP_BTN_SIZE_X,WIN_OP_BTN_SIZE_Y);
	pMinWin->setGeometry(btnrect);

	btnrect.adjust(WIN_OP_BTN_SIZE_X+WIN_OP_BTN_SPAN,0, WIN_OP_BTN_SIZE_X+WIN_OP_BTN_SPAN,0);
	pMaxWin->setGeometry(btnrect);

	//btnrect.adjust(WIN_OP_BTN_SIZE+WIN_OP_BTN_SPAN,0, WIN_OP_BTN_SIZE+WIN_OP_BTN_SPAN,0);
	pRestoreWin->setGeometry(btnrect);

	btnrect.adjust(WIN_OP_BTN_SIZE_X+WIN_OP_BTN_SPAN,0, WIN_OP_BTN_SIZE_X+WIN_OP_BTN_SPAN,0);
	pCloseWin->setGeometry(btnrect);

	// default is not maxizable window
	//pMaxWin->show();
	//pRestoreWin->hide();
}
void TopInfoLabel::mousePressEvent( QMouseEvent * ev )
{
    if( ev->button() != Qt::LeftButton)
    {
        return;
    }
	if ( _pressed )
	{
		return ;
	}
	_oldPos = ev->globalPos();
	_pressed = true;
}

void TopInfoLabel::mouseReleaseEvent( QMouseEvent * ev )
{
	_pressed = false;
}

void TopInfoLabel::mouseDoubleClickEvent ( QMouseEvent * ev )
{
	if ( this->_frame->isWndMaxmized() )
	{
		this->_frame->OnRestore();

		pMaxWin->show();
		pRestoreWin->hide();
	}
	else
	{
		this->_frame->OnMaxmize();

		pMaxWin->hide();
		pRestoreWin->show();
	}
}


void TopInfoLabel::OnMaxmize()
{
		pMaxWin->hide();
		pRestoreWin->show();
}

void TopInfoLabel::OnRestore()
{
		pMaxWin->show();
		pRestoreWin->hide();
}


#define MOUSEMV_THRES 2

void TopInfoLabel::mouseMoveEvent( QMouseEvent * event )
{

    if( !_pressed )
        return;

	QPoint curpos = event->globalPos();

	if( qAbs(curpos.x()-_oldPos.x()) >= MOUSEMV_THRES || qAbs(curpos.y()-_oldPos.y()) >= MOUSEMV_THRES )
    {
		QRect rect = this->_frame->geometry();
		rect.adjust(curpos.x()-_oldPos.x(),curpos.y()-_oldPos.y(),
			curpos.x()-_oldPos.x(),curpos.y()-_oldPos.y());
		_frame->setGeometry(rect);
        _oldPos = curpos;
    }
}





FrameBar::FrameBar(bool left,QWidget *parent, const QWidget *pframe):
_frame(( QWidget *)pframe), QLabel(parent),_pressed(false), _left(left)
{
	setStyleSheet("background-image:url(" + gbires + "BarLayout.png)");
}

FrameBar::~FrameBar()
{
}

void FrameBar::mousePressEvent( QMouseEvent * ev )
{
    if( ev->button() != Qt::LeftButton)
    {
        return;
    }
	if ( _pressed )
	{
		return ;
	}
	_oldPos = ev->globalPos();
	_pressed = true;
}

void FrameBar::mouseReleaseEvent( QMouseEvent * ev )
{
	_pressed = false;
}

#define MOUSEMV_THRES 2

void FrameBar::mouseMoveEvent( QMouseEvent * event )
{

    if( !_pressed )
        return;

	QPoint curpos = event->globalPos();

	if( qAbs(curpos.x()-_oldPos.x()) >= MOUSEMV_THRES || qAbs(curpos.y()-_oldPos.y()) >= MOUSEMV_THRES )
    {
		QRect rect = this->_frame->geometry();
		if ( this->_left )
		{
			rect.adjust(curpos.x()-_oldPos.x(),0,
				0,0);
		}
		else
		{

			rect.adjust(0,0,
				curpos.x()-_oldPos.x(),0);
		}

		_frame->setGeometry(rect);
        _oldPos = curpos;
    }
}

void FrameBar::enterEvent ( QEvent * event )
{
	_cursor = this->cursor();
	this->setCursor(Qt::SizeHorCursor);
}
void FrameBar::leaveEvent ( QEvent * event )
{
	this->setCursor(_cursor);
}


PhotoAppCfg::PhotoAppCfg():_printseam(0)
{
}

PhotoAppCfg::~PhotoAppCfg()
{
}

bool PhotoAppCfg::getPicViewDir(QString &dir)
{
	dir = this->_picviewdir;
	return true;
}
	
bool PhotoAppCfg::setPicViewDir(const QString &dir)
{
	_picviewdir = dir;
	return true;
}

bool PhotoAppCfg::getLang(QString &langname, QString &langfile)
{
	langname = this->_langname;
	langfile = _langfile;
	return true;
}

bool PhotoAppCfg::setLang(const QString &langname, const QString &langfile)
{
	this->_langname = langname;
	_langfile = langfile;
	return true;
}

bool PhotoAppCfg::getPrintSeam(int &printseam)
{
	if ( _printseam == 0 )
	{
		_printseam = 13;
	}
	printseam = _printseam;
	return true;
}

bool PhotoAppCfg::setPrintSeam(const int &printseam)
{
	_printseam = printseam;
	return true;
}

bool PhotoAppCfg::isMaximized()
{
	return this->_mainwndmaximized;
}

bool PhotoAppCfg::setMaximized(bool maxmized)
{
	this->_mainwndmaximized = maxmized;
	return true;
}



bool PhotoAppCfg::_saveStr(QDomDocument &doc,QDomElement &parent, const QString &name, const QString & value)
{
	QDomElement elem = doc.createElement(name);
	parent.appendChild(elem);

	QDomText txtnode = doc.createTextNode(value);
	elem.appendChild(txtnode);

	return true;
}

bool PhotoAppCfg::_loadStr(QDomElement &elem, QString &value)
{
	if ( elem.isNull() )
	{
		return false;
	}
	/*
	if ( QDomNode::TextNode !=  elem.nodeType() )
	{
		return false;
	}
	*/
	value = elem.text();
	return true;
}


bool PhotoAppCfg::_saveFloat(QDomDocument &doc,QDomElement &parent, const QString &name, const qreal value)
{
    QString tmpbuf = QString("%1").arg(value);
    return this->_saveStr(doc, parent, name, tmpbuf);
}
bool PhotoAppCfg::_loadFloat(QDomElement &elem, qreal &value)
{
	QString strval;
	if ( !_loadStr(elem, strval) )
	{
		return false;
	}
	float tmp;
	QByteArray ba = strval.toAscii();
	char *data = ba.data();
	sscanf(data, "%f", &tmp);
	value = tmp;
	return true;
}

bool PhotoAppCfg::_loadInt(QDomElement &elem, int &value)
{
	QString strval;
	if ( !_loadStr(elem, strval) )
	{
		return false;
	}
	sscanf(strval.toAscii().data(), "%d", &value);
	return true;
}
bool PhotoAppCfg::_saveInt(QDomDocument &doc,QDomElement &parent, const QString &name, const int value)
{
    QString tmpbuf = QString("%1").arg(value);
    return this->_saveStr(doc, parent, name, tmpbuf);
}


bool PhotoAppCfg::loadCfg(const QString &cfgfile)
{
	 QFile file(cfgfile);
     if (!file.open(QFile::ReadOnly | QFile::Text)) 
	 {
		 return false;
	 }

	 QDomDocument appcfgdoc;

	 QString errorStr;
     int errorLine;
     int errorColumn;
	 if ( !appcfgdoc.setContent(&file, true,  &errorStr, &errorLine,
                                 &errorColumn) )
	 {
		 return false;
	 }

     QDomElement root = appcfgdoc.documentElement();
     if (root.tagName() != "PmAppCfg") 
	 {
         return false;
     } 

	 QDomElement lastpicviewfolderelem = root.firstChildElement("LastPictureViewFolder");
	 if ( !lastpicviewfolderelem.isNull() )
	 {
		 this->_loadStr(lastpicviewfolderelem, this->_picviewdir);
	 }


	 QDomElement lstlangnameelem = root.firstChildElement("LastLangName");
	 if ( !lstlangnameelem.isNull() )
	 {
		 this->_loadStr(lstlangnameelem, this->_langname);
	 }
	 QDomElement lstlangfileelem = root.firstChildElement("LastLangFilePath");
	 if ( !lstlangfileelem.isNull() )
	 {
		 this->_loadStr(lstlangfileelem, this->_langfile);
	 }


	 QDomElement printseamelem = root.firstChildElement("PrintSeam");
	 if ( !printseamelem.isNull() )
	 {
		 this->_loadInt(printseamelem, this->_printseam);
	 }



	 QDomElement wndmaxelem = root.firstChildElement("MainwndMaximized");
	 if ( !wndmaxelem.isNull() )
	 {
		 int val  =0;
		 this->_loadInt(wndmaxelem,val);
		 this->_mainwndmaximized = val!=0;
	 }

	 this->_saveInt(appcfgdoc, root, "MainwndMaximized", this->_mainwndmaximized?1:0);

	 return true;
}

bool PhotoAppCfg::saveCfg(const QString &cfgfile)
{
	 QFile file(cfgfile);
     if (!file.open(QFile::ReadWrite | QFile::Text | QFile::Truncate)) 
	 {
		 return false;
	 }

	 QDomDocument appcfgdoc("photomakerdoc");

	 QString errorStr;
     int errorLine;
     int errorColumn;

	 QDomElement root = appcfgdoc.createElement("PmAppCfg");
	 appcfgdoc.appendChild(root);

	 // save app configures
	 this->_saveStr(appcfgdoc, root, "LastPictureViewFolder", this->_picviewdir);

	 this->_saveStr(appcfgdoc, root, "LastLangName", this->_langname);
	 this->_saveStr(appcfgdoc, root, "LastLangFilePath", this->_langfile);

	 this->_saveInt(appcfgdoc, root, "PrintSeam", this->_printseam);

	 this->_saveInt(appcfgdoc, root, "MainwndMaximized", this->_mainwndmaximized?1:0);

	 //this->_savePaperPage(domDocument, paperpageselem,  *this->_printpaperpage);

	 QString xml = appcfgdoc.toString();
	 
	 file.write(xml.toUtf8());

	 return true;
}

