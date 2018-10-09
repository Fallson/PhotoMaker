#ifndef PMLEFTPANE_H
#define PMLEFTPANE_H

#include <QWidget>
#include <QtGui/QMainWindow>
#include "ui_photomaker.h"
#include <QtGui/qtoolbar.h>
#include <QtGui/qlabel.h>
#include <QtGui/qtreeView.h>
#include <QtGui/qsplitter.h>
#include <QtGui/qtextedit.h>
#include "pmdirbrowsetree.h"
#include "PmPicView.h"
#include <QDir>
#include <QMutex>
#include <list>
#include <QtConcurrentRun> 
#include "photomaker.h"

using namespace std;


typedef struct _ImgItm
{
	QString name;
	QImage *_img;
	QString path;
}IMG_ITM, *PIMG_ITM;

class QTimer;


class LayoutPrviewDisplayer
{
public:
	virtual void show(const bool borderless, const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview) = 0;
};

class PictureView;
class Ly4x3PrviewDisplayer: public QObject, public LayoutPrviewDisplayer
{
	Q_OBJECT
public:
	Ly4x3PrviewDisplayer(PictureView *layoutview);
	~Ly4x3PrviewDisplayer();
public:
	virtual void show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview);

private:
	PictureView *_layoutview;
};

class Ly4x6PrviewDisplayer: public QObject,public LayoutPrviewDisplayer
{
	Q_OBJECT
public:
	Ly4x6PrviewDisplayer(PictureView *layoutview);
	~Ly4x6PrviewDisplayer();
public:
	virtual void show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview);

private:
	PictureView *_layoutview;
};

class Ly10x5PrviewDisplayer: public QObject,public LayoutPrviewDisplayer
{
	Q_OBJECT
public:
	Ly10x5PrviewDisplayer(PictureView *layoutview);
	~Ly10x5PrviewDisplayer();
public:
	virtual void show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview);

private:
	PictureView *_layoutview;
};

class Ly8x5PrviewDisplayer:public QObject, public LayoutPrviewDisplayer
{
	Q_OBJECT
public:
	Ly8x5PrviewDisplayer(PictureView *layoutview);
	~Ly8x5PrviewDisplayer();
public:
	virtual void show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview);
private:
	PictureView *_layoutview;
};

class LyCalA4PrviewDisplayer: public QObject,public LayoutPrviewDisplayer
{
	Q_OBJECT
public:
	LyCalA4PrviewDisplayer(PictureView *layoutview);
	~LyCalA4PrviewDisplayer();
public:
	virtual void show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview);
private:
	PictureView *_layoutview;
};

class LyCalA5PrviewDisplayer: public QObject,public LayoutPrviewDisplayer
{
	Q_OBJECT
public:
	LyCalA5PrviewDisplayer(PictureView *layoutview);
	~LyCalA5PrviewDisplayer();
public:
	virtual void show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview);

private:
	PictureView *_layoutview;
};

class LyCal4x6PrviewDisplayer:public QObject, public LayoutPrviewDisplayer
{
	Q_OBJECT
public:
	LyCal4x6PrviewDisplayer(PictureView *layoutview);
	~LyCal4x6PrviewDisplayer();
public:
	virtual void show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview);

private:
	PictureView *_layoutview;
};

class LyDefPrviewDisplayer: public QObject,public LayoutPrviewDisplayer
{
	Q_OBJECT
public:
	LyDefPrviewDisplayer();
	~LyDefPrviewDisplayer();
public:
	virtual void show(const bool borderless,const PROJ_PROPS::LAYOUT_TYPE layoutname, bool &showview);
};



class LayoutPreviewSelector
{
public:
	LayoutPreviewSelector(PictureView *layoutview);
	~LayoutPreviewSelector();

public:
	LayoutPrviewDisplayer &getLyPreviewDisplayer(const PROJ_PROPS::PROJ_TYPE );

private:
	PictureView *_layoutview;
};


class PmLeftPane : public QLabel
{
	Q_OBJECT

public:
	PmLeftPane(QWidget *parent);
	~PmLeftPane();

protected:
    virtual void resizeEvent(QResizeEvent *);

public slots:
	void _ctrlPageChanged(int index);
	void _ShowPicPreview();
	void _ShowPicPreview2();

private:
	static void SelPathChangedNf( void *context,const QString &path );

	void _constructLayoutPane(PictureView *pLayoutPictureView);
	void _constructColorPane(PictureView *pColorPictureView);


	void _show4x3(bool borderless, bool panorama);
	void _show4x6single();
	void _show10x5();
	void _show8x5(bool borderless, const QString &layoutname);
	void _showCalendarA4(const QString &layoutname);
	void _showCalendarA5(const QString &layoutname);
	void _showCalendar4x6(const QString &layoutname);

public:
	void selectCurFolder(const QString &path);
	void showFolder(const QString &path);
	void getCurShowFolder(QString &path){path = _curpath;}

	void showcurrentpath();
	void ListAllImgFiles();
	void AddImgItm(const QString &name, const QString &path);

	bool showLayoutPreview(const PROJ_PROPS::PROJ_TYPE proj, bool boderless, PROJ_PROPS::LAYOUT_TYPE layoutname);

	void cleanup();
	void reTranslate();

private:
	QString _curpath;
	QFuture<void>  *_pListThread;

	QDir  *_pCurDir;
	int _curPicIndex;
	QMutex _imglock;
	list<IMG_ITM> imglst;
	bool _finished;


private:
	PmDirBrowseTree *_dirbrowser;
	QSplitter *pvsplitter;
	QTextEdit *pEdit1;
	QTabBar *pTabBar;
	QTabWidget *pTabContainer;

	PictureView *pPhotoPreviewView;
	PictureView *pLayoutSelView;
	PictureView *pColorSelView;

	QTimer *_timer;
	int _curIndex;

	LayoutPreviewSelector *_lypreviewselector;
	bool _showlypreview;
};

#endif // PMLEFTPANE_H
