#include "pmleftpane.h"
#include <QtGui/qtextedit.h>
#include <QtGui/qfiledialog.h>
#include <QtGui/QFileSystemModel.h>
#include <QtGui/qtreewidget.h>
#include <QtGui/qlayout.h>
#include <QtGui/qsplitter.h>
#include "PmPicView.h"
#include <QtConcurrentRun> 
#include <qtimer.h>
#include "qmeta/jpeg.h"
#include "pmpaperpage.h"
#include <QTimer>

#define MAX_PATH 260

//QString gbires = "Resources/images/color/";


void PmLeftPane::reTranslate()
{
	pTabContainer->setTabText(0, tr("Browse"));
	if ( _showlypreview )
	{
		pTabContainer->setTabText(1, tr("Layout"));
		pTabContainer->setTabText(2, tr("Color"));
	}
	else
	{
		pTabContainer->setTabText(1, tr("Color"));
	}
	if ( this->_dirbrowser )
	{
		_dirbrowser->reTranslate();
	}
}

PmLeftPane::PmLeftPane(QWidget *parent)
	: QLabel(parent), _curIndex(0),_pCurDir(NULL),_curPicIndex(0), _dirbrowser(NULL),
	_finished(true),_pListThread(NULL),_lypreviewselector(NULL), _showlypreview(false)
{

	setStyleSheet("background-image:url(" + gbires + "leftpane.png)");

	pTabContainer = new QTabWidget(this);

	QPalette palette;
	palette.setBrush(pTabContainer->backgroundRole(), QBrush(QColor(qRgb(255,255,255))));
	pTabContainer->setPalette(palette);

	pvsplitter = new QSplitter(Qt::Vertical, this);

	QList<int> sizes;


	_dirbrowser = new PmDirBrowseTree(pvsplitter);
	_dirbrowser->header()->hide();
	_dirbrowser->setStyleSheet("background-image:url(" + gbires + "white.png)");


	pvsplitter->addWidget(_dirbrowser);

	//pEdit1 = new QTextEdit(this);

	pPhotoPreviewView = new PictureView(this);
	pPhotoPreviewView->setShowItmFrame(true);
	pvsplitter->addWidget(pPhotoPreviewView);
	pPhotoPreviewView->updatePath("");
	pPhotoPreviewView->setStyleSheet("background-image:url(" + gbires + "white.png)");


	sizes.push_back(200);
	sizes.push_back(400);
	pvsplitter->setSizes(sizes);
	pvsplitter->setStretchFactor(2,1);


	pLayoutSelView = new PictureView(this);
	pLayoutSelView->hide();
	_constructLayoutPane(pLayoutSelView);
	pLayoutSelView->setStyleSheet("background-image:url(" + gbires + "white.png)");

	pColorSelView= new PictureView(this);
	pColorSelView->setImgSize(80, 90);
	pColorSelView->setImgMargin(20,20);
	_constructColorPane(pColorSelView);
	pColorSelView->setStyleSheet("background-image:url(" + gbires + "white.png)");


	pvsplitter->addWidget(pPhotoPreviewView);
	pPhotoPreviewView->updatePath("");

	pTabContainer->addTab(pvsplitter,QIcon("Resources/images/browse.png"),tr("Browse"));
	pTabContainer->addTab(pColorSelView, QIcon("Resources/images/coloricon.png"),tr("Color"));


	_lypreviewselector = new LayoutPreviewSelector(pLayoutSelView);
	//
	_dirbrowser->subscribeSelectionChanged(SelPathChangedNf, this);



}



void PmLeftPane::_constructLayoutPane(PictureView *pLayoutView)
{
	pLayoutView->enableItmScale(false);

	// full size
}


void PmLeftPane::_constructColorPane(PictureView *pColorView)
{
	pColorView->enableItmScale(false);

	pColorView->addItem(gbires + "color/Lightgrey.png", tr("Light Grey"), COLOR_PREFIX  COLOR_LIGHT_GREY_NAME);
	pColorView->addItem(gbires + "color/Grey.png", tr("Grey"),COLOR_PREFIX  COLOR_GREY_NAME);
	pColorView->addItem(gbires + "color/DarkGrey.png", tr("Dark Grey"),COLOR_PREFIX  COLOR_DARK_GREY_NAME);
	pColorView->addItem(gbires + "color/Black.png", tr("Black"), COLOR_PREFIX  COLOR_BLACK_NAME);
	pColorView->addItem(gbires + "color/BrightYellow.png", tr("Bright yellow"), COLOR_PREFIX  COLOR_BRIGHT_YELLOW_NAME);
	pColorView->addItem(gbires + "color/Yellow.png", tr("Yellow"),COLOR_PREFIX   COLOR_YELLOW_NAME);
	pColorView->addItem(gbires + "color/Orange.png", tr("Orange"), COLOR_PREFIX  COLOR_ORANGE_NAME);
	pColorView->addItem(gbires + "color/Pink.png", tr("Pink"),COLOR_PREFIX   COLOR_PINK_NAME);
	pColorView->addItem(gbires + "color/LightPink.png", tr("Light Pink"),COLOR_PREFIX   COLOR_LIGHT_PINK_NAME);

	pColorView->addItem(gbires + "color/Blue.png", tr("Blue"),COLOR_PREFIX  COLOR_BLUE_NAME);
	pColorView->addItem(gbires + "color/Lightblue.png", tr("Light Blue"),COLOR_PREFIX   COLOR_LIGHT_BLUE_NAME);
	pColorView->addItem(gbires + "color/lightgreen.png", tr("Light Green"), COLOR_PREFIX  COLOR_LIGHT_GREEN_NAME);
	pColorView->addItem(gbires + "color/Green.png", tr("Green"), COLOR_PREFIX  COLOR_GREEN_NAME);
	pColorView->addItem(gbires + "color/Customer.png", tr("Customer Color"), COLOR_PREFIX COLOR_CUSTOMER_NAME);
}

PmLeftPane::~PmLeftPane()
{

}


void PmLeftPane::resizeEvent(QResizeEvent *)
{
	QRect rect = this->geometry();
	pTabContainer->setGeometry(0, 5, rect.width(), rect.height()-5);
}


void PmLeftPane::_ctrlPageChanged(int index)
{
}

unsigned int ShowPicPreview( void * context )
{
	PmLeftPane *pThis = (PmLeftPane*)context;
	pThis->showcurrentpath();

	return 0;
}
void PmLeftPane::showcurrentpath()
{
	this->pPhotoPreviewView->clear();


	QDir dir(_curpath);

	dir.setFilter(QDir::Files);
	dir.setSorting(QDir::Name);
	QStringList filters;
	filters << "*.jpg" << "*.gif" ;
	dir.setNameFilters(filters);

	QFileInfoList list = dir.entryInfoList();
	for (int subindex=0;subindex<list.size(); subindex++ )
	{
		QFileInfo fileInfo = list.at(subindex);
		QString check = fileInfo.absoluteFilePath();
		QString dirpath = check;
		if ( dirpath.at(dirpath.length()-1) == '/' )
		{
			dirpath = dirpath.left(dirpath.length()-1);
		}
		int lastslashpos = dirpath.lastIndexOf("\\");
		if ( lastslashpos == -1 )
		{
			lastslashpos = dirpath.lastIndexOf("/");
		}
		QString dirname;
		if ( lastslashpos > 0 & dirpath.length()-lastslashpos-1 >0 )
		{
			dirname = dirpath.right(dirpath.length()-lastslashpos-1);
		}
		else
		{
			dirname = dirpath;
		}
		if ( '/' == dirname.at(dirname.length()-1) )
		{
			dirname = dirname.left(dirname.length()-1);
		}

		//
		this->pPhotoPreviewView->addItem(dirpath, dirname, dirpath);
		this->update();
		//Sleep(5000);

		QRect rect = this->geometry();
		this->repaint(rect);
	}
	
}

void test()
{
}


void  ShowPicPreview1( void * context )
{
	PmLeftPane *pThis = (PmLeftPane*)context;
	pThis->ListAllImgFiles();
}

void AddImg(void *context, const QString &name, const QString &path)
{
	PmLeftPane *pThis = (PmLeftPane*)context;

	pThis->AddImgItm(name, path);
}

void PmLeftPane::AddImgItm(const QString &name, const QString &path)
{
	QImage img(path);
	QImage smallimg = img.scaled(50, 50, Qt::KeepAspectRatio);
	IMG_ITM imgItm;
	imgItm.name = name;
	imgItm._img = new QImage(smallimg);
	imgItm.path = path;
	_imglock.lock();
	imglst.push_back(imgItm);
	_imglock.unlock();
}


#define IMG_SIZE_X	160
#define IMG_SIZE_Y	160



void PmLeftPane::ListAllImgFiles()
{
	//
	QDir dir(_curpath);

	dir.setFilter(QDir::Files);
	dir.setSorting(QDir::Name);
	QStringList filters;
	filters << "*.jpg" << "*.gif" << "*.bmp" << "*.png" << "*.jpeg";
	dir.setNameFilters(filters);

	QFileInfoList list = dir.entryInfoList();
	for (int subindex=0;subindex<list.size(); subindex++ )
	{
		if ( _curpath.length() <= 0 )
		{
			break;
		}
		QFileInfo fileInfo = list.at(subindex);
		QString check = fileInfo.absoluteFilePath();
		QString dirpath = check;
		if ( dirpath.at(dirpath.length()-1) == '/' )
		{
			dirpath = dirpath.left(dirpath.length()-1);
		}
		int lastslashpos = dirpath.lastIndexOf("\\");
		if ( lastslashpos == -1 )
		{
			lastslashpos = dirpath.lastIndexOf("/");
		}
		QString dirname;
		if ( lastslashpos > 0 & dirpath.length()-lastslashpos-1 >0 )
		{
			dirname = dirpath.right(dirpath.length()-lastslashpos-1);
		}
		else
		{
			dirname = dirpath;
		}
		if ( '/' == dirname.at(dirname.length()-1) )
		{
			dirname = dirname.left(dirname.length()-1);
		}

		//QFuture<void> future = QtConcurrent::run(AddImg, this, dirname, dirpath);
		QImage smallimg;
		if ( dirname.lastIndexOf("jpg") > 0  || dirname.lastIndexOf("JPG") > 0)
		{
			qmeta::Jpeg jpgfile(dirpath);
			QByteArray data = jpgfile.Thumbnail();
			if ( data.size() )
			{
				QString thumbnailpath;
				thumbnailpath += ".\\";
				thumbnailpath += dirname;
				thumbnailpath += ".thumb";

				QFile file(thumbnailpath);
				file.open(QIODevice::WriteOnly);
				file.write(data);
				file.close();
				
				//QPixmap pixmap(thumbnailpath);

				//QRect pixrect = pixmap.rect();
				QImage img(thumbnailpath);
				QRect imgrect = img.rect();
				int width = img.width();
				int height = img.height();
				if ( height > width )
				{
					width = (IMG_SIZE_X*1.0)/height * width;
					height = IMG_SIZE_Y;
				}
				else
				{
					height = (IMG_SIZE_Y*1.0)/width * height;
					width = IMG_SIZE_X;
				}
				smallimg = img.scaled(IMG_SIZE_X, IMG_SIZE_Y, Qt::KeepAspectRatio);

				bool ret =  QFile::remove(thumbnailpath);

				if ( ret)
				{
				}

				
			}
			else
			{
				QImage img(dirpath);
				int width = img.width();
				int height = img.height();
				if ( height > width )
				{
					width = (IMG_SIZE_X*1.0)/height * width;
					height = IMG_SIZE_Y;
				}
				else
				{
					height = (IMG_SIZE_Y*1.0)/width * height;
					width = IMG_SIZE_X;
				}
				smallimg = img.scaled(width, height, Qt::KeepAspectRatio);
				//smallimg = img;
	
			}
		}
		else
		{
			QImage img(dirpath);
			int width = img.width();
			int height = img.height();
			if ( height > width )
			{
				width = (IMG_SIZE_X*1.0)/height * width;
				height = IMG_SIZE_Y;
			}
			else
			{
				height = (IMG_SIZE_Y*1.0)/width * height;
				width = IMG_SIZE_X;
			}
			smallimg = img.scaled(width, height, Qt::KeepAspectRatio);
			//smallimg = img;

		}

		IMG_ITM imgItm;
		imgItm.name = dirname;
		imgItm._img = new QImage(smallimg);
		imgItm.path = dirpath;
		_imglock.lock();
		imglst.push_back(imgItm);
		_imglock.unlock();
	}
	this->_finished = true;
}

void PmLeftPane::_ShowPicPreview()
{
	//
	if ( !this->_pCurDir )
	{
		return;
	}

	//
	QFileInfoList list = _pCurDir->entryInfoList();
	if ( _curPicIndex == list.size() )
	{
		//
		delete _pCurDir;
		_pCurDir = NULL;
		_curPicIndex = 0;
		return ;
	}

	QFileInfo fileInfo = list.at(_curPicIndex);
	QString check = fileInfo.absoluteFilePath();
	QString dirpath = check;
	if ( dirpath.at(dirpath.length()-1) == '/' )
	{
		dirpath = dirpath.left(dirpath.length()-1);
	}
	int lastslashpos = dirpath.lastIndexOf("\\");
	if ( lastslashpos == -1 )
	{
		lastslashpos = dirpath.lastIndexOf("/");
	}
	QString dirname;
	if ( lastslashpos > 0 & dirpath.length()-lastslashpos-1 >0 )
	{
		dirname = dirpath.right(dirpath.length()-lastslashpos-1);
	}
	else
	{
		dirname = dirpath;
	}
	if ( '/' == dirname.at(dirname.length()-1) )
	{
		dirname = dirname.left(dirname.length()-1);
	}

	//
	pPhotoPreviewView->addItem(dirpath, dirname,dirpath);
	this->update();

	QRect rect = this->geometry();
	this->repaint(rect);

	_curPicIndex++;
	pPhotoPreviewView->updateView();


	//QTimer *timer = new QTimer;
	connect(_timer, SIGNAL(timeout()), this, SLOT(_ShowPicPreview()));
	_timer->start(0);

	//QTimer::singleShot(0, this, SLOT(_ShowPicPreview()));

}



void PmLeftPane::_ShowPicPreview2()
{
	bool gotone = false;
	IMG_ITM imgItm;
	list<IMG_ITM> tmpimglst;

	_imglock.lock();
	tmpimglst=imglst;
	imglst.clear();
	_imglock.unlock();

	while(!tmpimglst.empty() )
	{
		gotone = true;
		imgItm = tmpimglst.front();
		tmpimglst.pop_front();
		pPhotoPreviewView->addItem( QPixmap::fromImage(*imgItm._img) ,imgItm.name,imgItm.path);
		delete imgItm._img;
	}

	if ( !gotone )
	{
		if ( !this->_finished )
		{
			//QTimer::singleShot(0, this, SLOT(_ShowPicPreview2()));
			//connect(_timer, SIGNAL(timeout()), this, SLOT(_ShowPicPreview2()));
			//timer->start(1);
			return ;

		}
		_timer->stop();

		return ;
	}

	//connect(_timer, SIGNAL(timeout()), this, SLOT(_ShowPicPreview2()));
	//_timer->start(1);

}


void PmLeftPane::cleanup()
{

	if (_pListThread )
	{
		_curpath.clear();
		_pListThread->waitForFinished();
		delete _pListThread;
		_pListThread = NULL;
	}
}

void PmLeftPane::selectCurFolder(const QString &path)
{
	if ( !path.length() )
	{
		return ;
	}
	this->_dirbrowser->selectCurFolder(path);
	showFolder(path);
	return ;
}

void PmLeftPane::showFolder(const QString &path)
{
	//this->_dirbrowser->expen
	if ( _pListThread )
	{
		_curpath.clear();
		_pListThread->waitForFinished();
		delete _pListThread;
		_pListThread = NULL;
	}
	_curpath = path;

	_imglock.lock();
	imglst.clear();
	_imglock.unlock();
	pPhotoPreviewView->clear();

	_finished = false;

	QFuture<void> future = QtConcurrent::run(ShowPicPreview1, this);
	_pListThread = new QFuture<void>(future);

	_timer = new QTimer;
	connect(_timer, SIGNAL(timeout()), this, SLOT(_ShowPicPreview2()));
	_timer->start(1);
}


void PmLeftPane::SelPathChangedNf( void *context,const QString &path )
{
	//
	PmLeftPane *pThis = (PmLeftPane*)context;

	if ( !pThis )
	{
		return ;
	}
	if ( !path.length() )
	{
		return ;
	}
	pThis->showFolder(path);

}



bool PmLeftPane::showLayoutPreview(const PROJ_PROPS::PROJ_TYPE proj, bool boderless, PROJ_PROPS::LAYOUT_TYPE layoutname)
{
	if ( !_lypreviewselector )
	{
		return false;
	}

	LayoutPrviewDisplayer &displayer = _lypreviewselector->getLyPreviewDisplayer(proj);
	bool showlayoutpreview = true;
	displayer.show(boderless, layoutname, showlayoutpreview);

	if ( showlayoutpreview == this->_showlypreview )
	{
		return true;
	}
	_showlypreview = showlayoutpreview;
	if ( _showlypreview )
	{
		pTabContainer->insertTab(1,pLayoutSelView, QIcon("Resources/images/layouticon.png"),tr("Layout"));
	}
	else
	{
		pTabContainer->removeTab(1);
		pLayoutSelView->hide();
	}

	return true;
}



Ly4x3PrviewDisplayer::Ly4x3PrviewDisplayer(PictureView *layoutview):_layoutview(layoutview)
{
}
Ly4x3PrviewDisplayer::~Ly4x3PrviewDisplayer()
{
}

void Ly4x3PrviewDisplayer::show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview)
{
	// fill later
	PictureView *pLayoutView = _layoutview;

	if ( !pLayoutView )
	{
		return ;
	}

	pLayoutView->clear();

	// full size
	pLayoutView->addItem(QPixmap(gbires + "layout/pocketbook4x3/Fullsizesingle.png"), "Fullsize Single",QString(LY_PREFIX)+LY_4X3_FULLSIZE_SINGLE);
	pLayoutView->addItem(gbires+ "layout/pocketbook4x3/FullsizePanorama.png", "Fullsize Panor",QString(LY_PREFIX)+LY_4X3_FULLSIZE_PANORAMA);
	pLayoutView->addItem(gbires+ "layout/pocketbook4x3/bordersingle.png","Border Single",QString(LY_PREFIX)+LY_4X3_BORDER_SINGLE);
	pLayoutView->addItem(gbires+ "layout/pocketbook4x3/BorderPanorama.png", "Border Panor",QString(LY_PREFIX)+LY_4X3_BORDER_PANORAMA);

	pLayoutView->updateView(true);
}

Ly4x6PrviewDisplayer::Ly4x6PrviewDisplayer(PictureView *layoutview):_layoutview(layoutview)
{
}

Ly4x6PrviewDisplayer::~Ly4x6PrviewDisplayer()
{
}

void Ly4x6PrviewDisplayer::show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview)
{
	if ( _layoutview )
	{
		_layoutview->clear();
	}
	showview = false;

}


Ly10x5PrviewDisplayer::Ly10x5PrviewDisplayer(PictureView *layoutview):_layoutview(layoutview)
{
}
Ly10x5PrviewDisplayer::~Ly10x5PrviewDisplayer()
{
}

void Ly10x5PrviewDisplayer::show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview)
{
	if ( _layoutview )
	{
		_layoutview->clear();
	}
	showview = false;
}


Ly8x5PrviewDisplayer::Ly8x5PrviewDisplayer(PictureView *layoutview):_layoutview(layoutview)
{
}

Ly8x5PrviewDisplayer::~Ly8x5PrviewDisplayer()
{
}

void Ly8x5PrviewDisplayer::show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview)
{
	PictureView *pLayoutView = _layoutview;

	if ( !pLayoutView )
	{
		return ;
	}

	pLayoutView->clear();

	// full size
	switch(layoutname)
	{
	case PROJ_PROPS::LY8X5FULL:
		{
			// full size
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeA.png", tr("Fullsize A"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_A);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeB.png", tr("Fullsize B"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_B);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeC.png",tr("Fullsize C"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_C);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeD.png", tr("Fullsize D"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_D);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizePanorama.png", tr("Fullsize Panor"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_PANOR);

			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionA.png", tr("Tradition A"),QString(LY_PREFIX)+LY_8X5_TRADITION_A);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionB.png", tr("Tradition B"),QString(LY_PREFIX)+LY_8X5_TRADITION_B);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionC.png",tr("Tradition C"),QString(LY_PREFIX)+LY_8X5_TRADITION_C);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionD.png", tr("Tradition D"),QString(LY_PREFIX)+LY_8X5_TRADITION_D);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionPanorama.png", tr("Tradition Panor"),QString(LY_PREFIX)+LY_8X5_TRADITION_PANOR);

			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonA.png", tr("Horizon A"),QString(LY_PREFIX)+LY_8X5_HORIZON_A);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonB.png", tr("Horizon B"),QString(LY_PREFIX)+LY_8X5_HORIZON_B);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonC.png",tr("Horizon C"),QString(LY_PREFIX)+LY_8X5_HORIZON_C);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonD.png", tr("Horizon D"),QString(LY_PREFIX)+LY_8X5_HORIZON_D);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonE.png", tr("Horizon E"),QString(LY_PREFIX)+LY_8X5_HORIZON_E);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonPanorama.png", tr("Horizon Panor"),QString(LY_PREFIX)+LY_8X5_HORIZON_PANOR);

			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonA.png", tr("Verticon A"),QString(LY_PREFIX)+LY_8X5_VERTICON_A);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonB.png", tr("Verticon B"),QString(LY_PREFIX)+LY_8X5_VERTICON_B);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonC.png",tr("Verticon C"),QString(LY_PREFIX)+LY_8X5_VERTICON_C);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonD.png", tr("Verticon D"),QString(LY_PREFIX)+LY_8X5_VERTICON_D);
			pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonPanorama.png", tr("Verticon Panor"),QString(LY_PREFIX)+LY_8X5_VERTICON_PANOR);

		}
		break;
	case PROJ_PROPS::LY8X5TRADITION:
		{
			if ( borderless )
			{
				// include fullsize

				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionA.png", tr("Tradition A"),QString(LY_PREFIX)+LY_8X5_TRADITION_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionB.png", tr("Tradition B"),QString(LY_PREFIX)+LY_8X5_TRADITION_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionC.png",tr("Tradition C"),QString(LY_PREFIX)+LY_8X5_TRADITION_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionD.png", tr("Tradition D"),QString(LY_PREFIX)+LY_8X5_TRADITION_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionPanorama.png", tr("Tradition Panor"),QString(LY_PREFIX)+LY_8X5_TRADITION_PANOR);

				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonA.png", tr("Horizon A"),QString(LY_PREFIX)+LY_8X5_HORIZON_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonB.png", tr("Horizon B"),QString(LY_PREFIX)+LY_8X5_HORIZON_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonC.png",tr("Horizon C"),QString(LY_PREFIX)+LY_8X5_HORIZON_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonD.png", tr("Horizon D"),QString(LY_PREFIX)+LY_8X5_HORIZON_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonE.png", tr("Horizon E"),QString(LY_PREFIX)+LY_8X5_HORIZON_E);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonPanorama.png", tr("Horizon Panor"),QString(LY_PREFIX)+LY_8X5_HORIZON_PANOR);

				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonA.png", tr("Verticon A"),QString(LY_PREFIX)+LY_8X5_VERTICON_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonB.png", tr("Verticon B"),QString(LY_PREFIX)+LY_8X5_VERTICON_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonC.png",tr("Verticon C"),QString(LY_PREFIX)+LY_8X5_VERTICON_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonD.png", tr("Verticon D"),QString(LY_PREFIX)+LY_8X5_VERTICON_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonPanorama.png", tr("Verticon Panor"),QString(LY_PREFIX)+LY_8X5_VERTICON_PANOR);

				// full size
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeA.png", tr("Fullsize A"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeB.png", tr("Fullsize B"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeC.png",tr("Fullsize C"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeD.png", tr("Fullsize D"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizePanorama.png", tr("Fullsize Panor"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_PANOR);

			}
			else
			{

				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionA.png", tr("Tradition A"),QString(LY_PREFIX)+LY_8X5_TRADITION_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionB.png", tr("Tradition B"),QString(LY_PREFIX)+LY_8X5_TRADITION_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionC.png",tr("Tradition C"),QString(LY_PREFIX)+LY_8X5_TRADITION_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionD.png", tr("Tradition D"),QString(LY_PREFIX)+LY_8X5_TRADITION_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionPanorama.png", tr("Tradition Panor"),QString(LY_PREFIX)+LY_8X5_TRADITION_PANOR);

				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonA.png", tr("Horizon A"),QString(LY_PREFIX)+LY_8X5_HORIZON_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonB.png", tr("Horizon B"),QString(LY_PREFIX)+LY_8X5_HORIZON_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonC.png",tr("Horizon C"),QString(LY_PREFIX)+LY_8X5_HORIZON_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonD.png", tr("Horizon D"),QString(LY_PREFIX)+LY_8X5_HORIZON_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonE.png", tr("Horizon E"),QString(LY_PREFIX)+LY_8X5_HORIZON_E);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonPanorama.png", tr("Horizon Panor"),QString(LY_PREFIX)+LY_8X5_HORIZON_PANOR);

				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonA.png", tr("Verticon A"),QString(LY_PREFIX)+LY_8X5_VERTICON_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonB.png", tr("Verticon B"),QString(LY_PREFIX)+LY_8X5_VERTICON_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonC.png",tr("Verticon C"),QString(LY_PREFIX)+LY_8X5_VERTICON_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonD.png", tr("Verticon D"),QString(LY_PREFIX)+LY_8X5_VERTICON_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonPanorama.png", tr("Verticon Panor"),QString(LY_PREFIX)+LY_8X5_VERTICON_PANOR);

			}
		}
		break;
	case PROJ_PROPS::LY8X5VERTICON:
		{
			if ( borderless )
			{
				// include fullsize

				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonA.png", tr("Verticon A"),QString(LY_PREFIX)+LY_8X5_VERTICON_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/boderless/VerticonB.png", tr("Verticon B"),QString(LY_PREFIX)+LY_8X5_VERTICON_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/boderless/VerticonC.png",tr("Verticon C"),QString(LY_PREFIX)+LY_8X5_VERTICON_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/boderless/VerticonD.png", tr("Verticon D"),QString(LY_PREFIX)+LY_8X5_VERTICON_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/boderless/VerticonPanorama.png", tr("Verticon Panor"),QString(LY_PREFIX)+LY_8X5_VERTICON_PANOR);

				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionA.png", tr("Tradition A"),QString(LY_PREFIX)+LY_8X5_TRADITION_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionB.png", tr("Tradition B"),QString(LY_PREFIX)+LY_8X5_TRADITION_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionC.png",tr("Tradition C"),QString(LY_PREFIX)+LY_8X5_TRADITION_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionD.png", tr("Tradition D"),QString(LY_PREFIX)+LY_8X5_TRADITION_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionPanorama.png", tr("Tradition Panor"),QString(LY_PREFIX)+LY_8X5_TRADITION_PANOR);


				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonA.png", tr("Horizon A"),QString(LY_PREFIX)+LY_8X5_HORIZON_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonB.png", tr("Horizon B"),QString(LY_PREFIX)+LY_8X5_HORIZON_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonC.png",tr("Horizon C"),QString(LY_PREFIX)+LY_8X5_HORIZON_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonD.png", tr("Horizon D"),QString(LY_PREFIX)+LY_8X5_HORIZON_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonE.png", tr("Horizon E"),QString(LY_PREFIX)+LY_8X5_HORIZON_E);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonPanorama.png", tr("Horizon Panor"),QString(LY_PREFIX)+LY_8X5_HORIZON_PANOR);

				// full size
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeA.png", tr("Fullsize A"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeB.png", tr("Fullsize B"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeC.png",tr("Fullsize C"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeD.png", tr("Fullsize D"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizePanorama.png", tr("Fullsize Panor"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_PANOR);
			}
			else
			{
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonA.png", tr("Verticon A"),QString(LY_PREFIX)+LY_8X5_VERTICON_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonB.png", tr("Verticon B"),QString(LY_PREFIX)+LY_8X5_VERTICON_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonC.png",tr("Verticon C"),QString(LY_PREFIX)+LY_8X5_VERTICON_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonD.png", tr("Verticon D"),QString(LY_PREFIX)+LY_8X5_VERTICON_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonPanorama.png", tr("Verticon Panor"),QString(LY_PREFIX)+LY_8X5_VERTICON_PANOR);

				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionA.png", tr("Tradition A"),QString(LY_PREFIX)+LY_8X5_TRADITION_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionB.png", tr("Tradition B"),QString(LY_PREFIX)+LY_8X5_TRADITION_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionC.png",tr("Tradition C"),QString(LY_PREFIX)+LY_8X5_TRADITION_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionD.png", tr("Tradition D"),QString(LY_PREFIX)+LY_8X5_TRADITION_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionPanorama.png", tr("Tradition Panor"),QString(LY_PREFIX)+LY_8X5_TRADITION_PANOR);

				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonA.png", tr("Horizon A"),QString(LY_PREFIX)+LY_8X5_HORIZON_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonB.png", tr("Horizon B"),QString(LY_PREFIX)+LY_8X5_HORIZON_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonC.png",tr("Horizon C"),QString(LY_PREFIX)+LY_8X5_HORIZON_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonD.png", tr("Horizon D"),QString(LY_PREFIX)+LY_8X5_HORIZON_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonE.png", tr("Horizon E"),QString(LY_PREFIX)+LY_8X5_HORIZON_E);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonPanorama.png", tr("Horizon Panor"),QString(LY_PREFIX)+LY_8X5_HORIZON_PANOR);


				// full size
				/*
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/FullsizeA.png", tr("Fullsize A"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/FullsizeB.png", tr("Fullsize B"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/FullsizeC.png",tr("Fullsize C"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/FullsizeD.png", tr("Fullsize D"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/FullsizePanorama.png", tr("Fullsize Panor"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_PANOR);
				*/
			}
		}
		break;
	case PROJ_PROPS::LY8X5HORIZON:
		{

			if ( borderless )
			{
				// include fullsize
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonA.png", tr("Horizon A"),QString(LY_PREFIX)+LY_8X5_HORIZON_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonB.png", tr("Horizon B"),QString(LY_PREFIX)+LY_8X5_HORIZON_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonC.png",tr("Horizon C"),QString(LY_PREFIX)+LY_8X5_HORIZON_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonD.png", tr("Horizon D"),QString(LY_PREFIX)+LY_8X5_HORIZON_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonE.png", tr("Horizon E"),QString(LY_PREFIX)+LY_8X5_HORIZON_E);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/HorizonPanorama.png", tr("Horizon Panor"),QString(LY_PREFIX)+LY_8X5_HORIZON_PANOR);

				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionA.png", tr("Tradition A"),QString(LY_PREFIX)+LY_8X5_TRADITION_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionB.png", tr("Tradition B"),QString(LY_PREFIX)+LY_8X5_TRADITION_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionC.png",tr("Tradition C"),QString(LY_PREFIX)+LY_8X5_TRADITION_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionD.png", tr("Tradition D"),QString(LY_PREFIX)+LY_8X5_TRADITION_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/TraditionPanorama.png", tr("Tradition Panor"),QString(LY_PREFIX)+LY_8X5_TRADITION_PANOR);


				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonA.png", tr("Verticon A"),QString(LY_PREFIX)+LY_8X5_VERTICON_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonB.png", tr("Verticon B"),QString(LY_PREFIX)+LY_8X5_VERTICON_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonC.png",tr("Verticon C"),QString(LY_PREFIX)+LY_8X5_VERTICON_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonD.png", tr("Verticon D"),QString(LY_PREFIX)+LY_8X5_VERTICON_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/VerticonPanorama.png", tr("Verticon Panor"),QString(LY_PREFIX)+LY_8X5_VERTICON_PANOR);

				// full size
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeA.png", tr("Fullsize A"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeB.png", tr("Fullsize B"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeC.png",tr("Fullsize C"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizeD.png", tr("Fullsize D"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/borderless/FullsizePanorama.png", tr("Fullsize Panor"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_PANOR);
			}
			else
			{
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonA.png", tr("Horizon A"),QString(LY_PREFIX)+LY_8X5_HORIZON_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonB.png", tr("Horizon B"),QString(LY_PREFIX)+LY_8X5_HORIZON_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonC.png",tr("Horizon C"),QString(LY_PREFIX)+LY_8X5_HORIZON_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonD.png", tr("Horizon D"),QString(LY_PREFIX)+LY_8X5_HORIZON_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonE.png", tr("Horizon E"),QString(LY_PREFIX)+LY_8X5_HORIZON_E);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/HorizonPanorama.png", tr("Horizon Panor"),QString(LY_PREFIX)+LY_8X5_HORIZON_PANOR);

				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionA.png", tr("Tradition A"),QString(LY_PREFIX)+LY_8X5_TRADITION_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionB.png", tr("Tradition B"),QString(LY_PREFIX)+LY_8X5_TRADITION_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionC.png",tr("Tradition C"),QString(LY_PREFIX)+LY_8X5_TRADITION_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionD.png", tr("Tradition D"),QString(LY_PREFIX)+LY_8X5_TRADITION_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/TraditionPanorama.png", tr("Tradition Panor"),QString(LY_PREFIX)+LY_8X5_TRADITION_PANOR);


				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonA.png", tr("Verticon A"),QString(LY_PREFIX)+LY_8X5_VERTICON_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonB.png", tr("Verticon B"),QString(LY_PREFIX)+LY_8X5_VERTICON_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonC.png",tr("Verticon C"),QString(LY_PREFIX)+LY_8X5_VERTICON_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonD.png", tr("Verticon D"),QString(LY_PREFIX)+LY_8X5_VERTICON_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/VerticonPanorama.png", tr("Verticon Panor"),QString(LY_PREFIX)+LY_8X5_VERTICON_PANOR);

				// full size
				/*
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/FullsizeA.png", tr("Fullsize A"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_A);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/FullsizeB.png", tr("Fullsize B"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_B);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/FullsizeC.png",tr("Fullsize C"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_C);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/FullsizeD.png", tr("Fullsize D"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_D);
				pLayoutView->addItem(gbires+ "layout/Photobook8x5/border/FullsizePanorama.png", tr("Fullsize Panor"),QString(LY_PREFIX)+LY_8X5_FULLSIZE_PANOR);
				*/
			}
		}
		break;
	}
	pLayoutView->updateView(true);
}


LyCalA4PrviewDisplayer::LyCalA4PrviewDisplayer(PictureView *layoutview):_layoutview(layoutview)
{
}

LyCalA4PrviewDisplayer::~LyCalA4PrviewDisplayer()
{
}
void LyCalA4PrviewDisplayer::show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview)
{
	PictureView *pLayoutView = _layoutview;

	if ( !pLayoutView )
	{
		return ;
	}

	pLayoutView->clear();
	showview = true;


	switch(layoutname)
	{
	case PROJ_PROPS::LYCALA4L1:
		{
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout1/Layout1.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CALA4_L1_1);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout1/Layout2.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CALA4_L1_2);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout1/Layout3.png",tr("Layout 3"),QString(LY_PREFIX)+LY_CALA4_L1_3);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout1/Layout4.png", tr("Layout 4"),QString(LY_PREFIX)+LY_CALA4_L1_4);
		}
		break;
	case PROJ_PROPS::LYCALA4L2:
		{
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout2/Layout1.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CALA4_L2_1);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout2/Layout2.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CALA4_L2_2);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout2/Layout3.png",tr("Layout 3"),QString(LY_PREFIX)+LY_CALA4_L2_3);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout2/Layout4.png", tr("Layout 4"),QString(LY_PREFIX)+LY_CALA4_L2_4);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout2/Layout5.png",tr("Layout 5"),QString(LY_PREFIX)+LY_CALA4_L2_5);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout2/Layout6.png", tr("Layout 6"),QString(LY_PREFIX)+LY_CALA4_L2_6);
		}
		break;
	case PROJ_PROPS::LYCALA4L3:
		{
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout3/Layout1.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CALA4_L3_1);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout3/Layout2.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CALA4_L3_2);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout3/Layout3.png",tr("Layout 3"),QString(LY_PREFIX)+LY_CALA4_L3_3);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout3/Layout4.png", tr("Layout 4"),QString(LY_PREFIX)+LY_CALA4_L3_4);
		}
		break;
	case PROJ_PROPS::LYCALA4L4:
		{
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout4/Layout1.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CALA4_L4_1);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout4/Layout2.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CALA4_L4_2);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout4/Layout3.png",tr("Layout 3"),QString(LY_PREFIX)+LY_CALA4_L4_3);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/Layout4/Layout4.png", tr("Layout 4"),QString(LY_PREFIX)+LY_CALA4_L4_4);
		}
		break;
	case PROJ_PROPS::LYCALFRONTPG:
		{
			pLayoutView->addItem(gbires+ "layout/CalendarA4/CalA4FrontPgBorder.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CALA4_FP_1);
			pLayoutView->addItem(gbires+ "layout/CalendarA4/CalA4FrontPg.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CALA4_FP_2);
		}
		break;
	}
}


LyCalA5PrviewDisplayer::LyCalA5PrviewDisplayer(PictureView *layoutview):_layoutview(layoutview)
{
}
LyCalA5PrviewDisplayer::~LyCalA5PrviewDisplayer()
{
}
void LyCalA5PrviewDisplayer::show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview)
{
	PictureView *pLayoutView = _layoutview;

	if ( !pLayoutView )
	{
		return ;
	}

	pLayoutView->clear();
	showview = true;


	switch(layoutname)
	{
	case PROJ_PROPS::LYCALA5L1:
		{
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout1/Layout1.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CALA5_L1_1);
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout1/Layout2.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CALA5_L1_2);
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout1/Layout3.png",tr("Layout 3"),QString(LY_PREFIX)+LY_CALA5_L1_3);
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout1/Layout4.png", tr("Layout 4"),QString(LY_PREFIX)+LY_CALA5_L1_4);
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout1/Layout5.png",tr("Layout 5"),QString(LY_PREFIX)+LY_CALA5_L1_5);
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout1/Layout6.png", tr("Layout 6"),QString(LY_PREFIX)+LY_CALA5_L1_6);
		}
		break;
	case PROJ_PROPS::LYCALA5L2:
		{
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout2/Layout1.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CALA5_L2_1);
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout2/Layout2.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CALA5_L2_2);
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout2/Layout3.png",tr("Layout 3"),QString(LY_PREFIX)+LY_CALA5_L2_3);
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout2/Layout4.png", tr("Layout 4"),QString(LY_PREFIX)+LY_CALA5_L2_4);
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout2/Layout5.png",tr("Layout 5"),QString(LY_PREFIX)+LY_CALA5_L2_5);
		}
		break;
	case PROJ_PROPS::LYCALA5L3:
		{
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout3/Layout1.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CALA5_L3_1);
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout3/Layout2.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CALA5_L3_2);
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout3/Layout3.png",tr("Layout 3"),QString(LY_PREFIX)+LY_CALA5_L3_3);
			pLayoutView->addItem(gbires+ "layout/CalendarA5/Layout3/Layout4.png", tr("Layout 4"),QString(LY_PREFIX)+LY_CALA5_L3_4);
		}
		break;
	case PROJ_PROPS::LYCALFRONTPG:
		{
			pLayoutView->addItem(gbires+ "layout/CalendarA5/CalA5FrontPgBorder.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CALA5_FP_1);
			pLayoutView->addItem(gbires+ "layout/CalendarA5/CalA5FrontPg.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CALA5_FP_2);
		}
	}
}


LyCal4x6PrviewDisplayer::LyCal4x6PrviewDisplayer(PictureView *layoutview):_layoutview(layoutview)
{
}


LyCal4x6PrviewDisplayer::~LyCal4x6PrviewDisplayer()
{
}

void LyCal4x6PrviewDisplayer::show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview)
{
	PictureView *pLayoutView = _layoutview;

	if ( !pLayoutView )
	{
		return ;
	}

	pLayoutView->clear();
	showview = true;


	switch(layoutname)
	{
	case PROJ_PROPS::LYCAL4X6L1:
		{
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout1/Layout1.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CAL4X6_L1_1);
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout1/Layout2.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CAL4X6_L1_2);
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout1/Layout3.png",tr("Layout 3"),QString(LY_PREFIX)+LY_CAL4X6_L1_3);
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout1/Layout4.png", tr("Layout 4"),QString(LY_PREFIX)+LY_CAL4X6_L1_4);
		}
		break;
	case PROJ_PROPS::LYCAL4X6L2:
		{
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout2/Layout1.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CAL4X6_L2_1);
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout2/Layout2.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CAL4X6_L2_2);
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout2/Layout3.png",tr("Layout 3"),QString(LY_PREFIX)+LY_CAL4X6_L2_3);
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout2/Layout4.png", tr("Layout 4"),QString(LY_PREFIX)+LY_CAL4X6_L2_4);
		}
		break;
	case PROJ_PROPS::LYCAL4X6L3:
		{
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout3/Layout1.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CAL4X6_L3_1);
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout3/Layout2.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CAL4X6_L3_2);
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout3/Layout3.png",tr("Layout 3"),QString(LY_PREFIX)+LY_CAL4X6_L3_3);
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout3/Layout4.png", tr("Layout 4"),QString(LY_PREFIX)+LY_CAL4X6_L3_4);
		}
		break;
	case PROJ_PROPS::LYCAL4X6L4:
		{
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout4/Layout1.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CAL4X6_L4_1);
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout4/Layout2.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CAL4X6_L4_2);
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout4/Layout3.png",tr("Layout 3"),QString(LY_PREFIX)+LY_CAL4X6_L4_3);
			pLayoutView->addItem(gbires+ "layout/Calendar4x6/Layout4/Layout4.png", tr("Layout 4"),QString(LY_PREFIX)+LY_CAL4X6_L4_4);
		}
		break;
	case PROJ_PROPS::LYCALFRONTPG:
		{
			pLayoutView->addItem(gbires+ "layout/CalendarA4x6/CalA4x6FrontPgBorder.png", tr("Layout 1"),QString(LY_PREFIX)+LY_CALA4x6_FP_1);
			pLayoutView->addItem(gbires+ "layout/CalendarA4x6/CalA4x6FrontPg.png", tr("Layout 2"),QString(LY_PREFIX)+LY_CALA4x6_FP_2);
		}

	}
}


LyDefPrviewDisplayer::LyDefPrviewDisplayer()
{
}

LyDefPrviewDisplayer::~LyDefPrviewDisplayer()
{
}

void LyDefPrviewDisplayer::show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview)
{
}


LayoutPreviewSelector::LayoutPreviewSelector(PictureView *layoutview):_layoutview(layoutview)
{
}

LayoutPreviewSelector::~LayoutPreviewSelector()
{
}


LayoutPrviewDisplayer &LayoutPreviewSelector::getLyPreviewDisplayer(const PROJ_PROPS::PROJ_TYPE proj )
{
	switch(proj)
	{
	case PROJ_PROPS::POCKETBOOK4X3:
		{
			static Ly4x3PrviewDisplayer dispalyer(_layoutview);
			return dispalyer;
		}
		break;
	case PROJ_PROPS::PHOTOBOOK10X15:
		{
			static Ly10x5PrviewDisplayer displayer(_layoutview);
			return displayer;
		}
		break;
	case PROJ_PROPS::SINGLE4X6:
		{
			static Ly4x6PrviewDisplayer displayer(_layoutview);
			return displayer;
		}
		break;
	case PROJ_PROPS::PHOTOBOOK8X5:
		{
			static Ly8x5PrviewDisplayer displayer(_layoutview);
			return displayer;
		}
		break;
	case PROJ_PROPS::CALENDARA4:
		{
			static LyCalA4PrviewDisplayer displayer(_layoutview);
			return displayer;
		}
		break;
	case PROJ_PROPS::CALENDARA5:
		{
			static LyCalA5PrviewDisplayer displayer(_layoutview);
			return displayer;
		}
		break;
	case PROJ_PROPS::CALENDAR4X6:
		{
			static LyCal4x6PrviewDisplayer displayer(_layoutview);
			return displayer;
		}
		break;
	case PROJ_PROPS::DEFDEMO:
	default:
		{
			static LyDefPrviewDisplayer defdisplayer;
			return defdisplayer;
		}
	}
}
