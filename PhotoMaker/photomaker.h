#ifndef PHOTOMAKER_H
#define PHOTOMAKER_H

#include <QtGui/QMainWindow>
#include "ui_photomaker.h"
#include <QtGui/qtoolbar.h>
#include <QtGui/qlabel.h>
#include <QtGui/qpushbutton.h>
#include <QtGui/qsplitter.h>
#include "pmbottomctrlpane.h"
#include "pmphotomakerdoc.h"
#include <QToolButton>
#include <QCursor>

class PmCentralPane;
class PmLeftPane;
class FrameBar;


class PhotoAppCfg
{
public:
	PhotoAppCfg();
	~PhotoAppCfg();

public:
	bool getPicViewDir(QString &dir);
	bool setPicViewDir(const QString &dir);
	bool getLang(QString &langname, QString &langfile);
	bool setLang(const QString &langname, const QString &langfile);
	bool getPrintSeam(int &printseam);
	bool setPrintSeam(const int &printseam);
	bool isMaximized();
	bool setMaximized(bool maxmized);

	bool loadCfg(const QString &cfgfile);
	bool saveCfg(const QString &cfgfile);
private:
	bool _saveStr(QDomDocument &doc,QDomElement &parent, const QString &name, const QString & value);
	bool _loadStr(QDomElement &elem, QString &value);
	bool _saveFloat(QDomDocument &doc,QDomElement &parent, const QString &name, const qreal value);
	bool _loadFloat(QDomElement &elem, qreal &value);
	bool _saveInt(QDomDocument &doc,QDomElement &parent, const QString &name, const int value);
	bool _loadInt(QDomElement &elem, int &value);

private:
	QString _picviewdir;
	QString _langname;
	QString _langfile;
	int _printseam;
	bool _mainwndmaximized;
};

class PrintPagesPreviewView;
class PhotoEditView;
class TopInfoLabel;


class PhotoMaker : public QMainWindow
{
	Q_OBJECT

	friend class TopInfoLabel;
public:

public:
	PhotoMaker(PmPhotoMakerDoc *pdoc, QWidget *parent = 0, Qt::WFlags flags = 0);
	~PhotoMaker();

public:
	PmPhotoMakerDoc *getDoc(){return _pdoc;}
	bool updateLastPhotoPage(PmPhotoPage *photopage);

public:
	void updateViews(bool reload = true);

	void updateEditView(bool reload = true);
	PrintPagesPreviewView *getPreviewView();
	PhotoEditView *getEditView();
	bool showEditPane(PmBottomCtrlPane::EDIT_PANE_TYPE editpane,const QString &cnt=QString(""));
	void updateEditPaneInfo();

public:
	// paper add/remove/move assist function
	void addPaperAtIndex(int index);
	void delPaper(PmPrintPaperPage *paper);
	void mvPaper(PmPrintPaperPage *paper, PmPrintPaperPage *topaper);


protected:
    virtual void resizeEvent(QResizeEvent *);
	virtual void closeEvent(QCloseEvent *e);
public:
	void updateUIStatus();
	// calendar edit
	void updateCalCfg(const CALENDAR_CFG &calcfg);
	bool getSelCalCfg(CALENDAR_CFG &calcfg);
	void updateFirstCalMonth(int firstmonth);
	void updateCalYear(int year);

	void OpenProj(const QString &projfile);


	bool isWndMaxmized();

public slots:
	// system button
	void OnClose();
	void OnMaxmize();
	void OnMinimize();
	void OnRestore();
	void OnAbout();

	//
	void OnNewProj();
	void OnOpenProj();
	void OnQuitProj();
	void OnSaveProj();
	void OnSaveAs();
	void OnPrint();
	void OnUndo();
	void OnDelSelection();
	void OnAddTxt();
	void OnChgShadow();
	//void onShadow();
	void OnNextPage();
	void OnPrePage();

	void OnInsPageBefore();
	void OnInsPageAfter();
	void OnDelCurPage();

	void OnZoomEditView(qreal scale);

	//
	void OnCut();
	void OnCopy();
	void OnPaste();

	//
	void OnLangchg();


	// photoedit
	void OnRotatePhotoleft();
	void OnRotatePhotoright();
	void OnSetPhotoHSL();
	void OnSetPhotoBWC();
	void OnSetPhotoLCIG();
	void OnSetPhotoRE();
	void OnZoomPhoto(qreal scale);
	void OnSetBgColor(const QColor &color);


	// text edit
	void OnAlignText(int align);
	void OnValignText(int valign);
    void OnSetTextCnt(QString &txt, qreal font_ratio);
    void OnSetTextShadow(bool shadow);

	void OnMvTxtBox(QRectF itmrct,int state = 1);
	void OnRotateTxtBox(QRectF itmrct, int angel, int state=1);
	void OnResizeTxtBox( QRectF itmrct,int state=1);

	// edit view orentation
	void OnOrentation();

private:
	void _showProjInfo(PROJ_PROPS prjprops);
	bool _isSinglePageProj();
	bool _isCalendarPrj();
	void _showPageIndexInfo();

	void _translateLang();
	void _createLangItms();
	void _updateLangMenuItmsLang();
	bool _getLangName(const QString &langfilename, QString &langname);
	bool _getLangFile(const QString &langname, QString &langfilename);
	void _chgLang(const QString &langname, QString &langfile);
	void _selLangMenu(const QString &langname);

    void _createActions();
	void _createToolBarButton();
    void _createStatusBar();


private:
	Ui::PhotoMakerClass ui;


	QRect _normalRc;

	TopInfoLabel *_toplabel;
	QLabel *_toolBarBane;


    QAction *_newAct;
	QAction *_openAct;
    QAction *_saveAct;
    QAction *_saveAsAct;


	QAction *_cutAct;
    QAction *_copyAct;
    QAction *_pasteAct;
    QAction *_undoAct;
	QAction *_delAct;

    QAction *_printAct;


    QAction *_aboutAct;
    QAction *_exitAppAct;
    QAction *_quitCurPrjAct;

	QList<QAction *> _langActs;
	QList<QString> _langshortnames;
	QActionGroup *_langactGroup;


	QToolButton *_newBtn;
	QToolButton *_opnBtn;
	QToolButton *_savBtn;	
	QToolButton *_prntBtn;
	QToolButton *_undoBtn;
	QToolButton *_delBtn;
	QToolButton *_orientationBtn;
	QToolButton *_addtxtBtn;
	QToolButton *_shadowBtn;
	QToolButton *_quitBtn;

	QWidget *_pCentralWidget;
	QWidget *_pOpWidget;
	QSplitter *_phsplitter;
	PmLeftPane *_pLeftPane;
	PmBottomCtrlPane *_pBottomCtrlPane;
	PmCentralPane *_pCentralPane;


	FrameBar *_leftBar, *_rightBar;

	bool _undoonprocessing;
private:
	PmPhotoMakerDoc *_pdoc;
	PhotoAppCfg _appcfg;
	QString _prjfile;


};



class TopInfoLabel: public QLabel
{
	Q_OBJECT

public:
	TopInfoLabel(QWidget *parent,  PhotoMaker *pframe);
	~TopInfoLabel();

public:
	void reTranslateLang();

protected:

	virtual void  mouseMoveEvent ( QMouseEvent * ev );
	virtual void  mousePressEvent ( QMouseEvent * ev );
	virtual void mouseReleaseEvent ( QMouseEvent * ev );
	virtual void mouseDoubleClickEvent ( QMouseEvent * ev );

    virtual void resizeEvent(QResizeEvent *);

protected slots:
	void OnMaxmize();
	void OnRestore();


private:
	PhotoMaker *_frame;
	bool _pressed;
	QPoint _oldPos;
	bool _maxized;

	QPushButton *pMinWin;
	QPushButton *pMaxWin;
	QPushButton *pRestoreWin;
	QPushButton *pCloseWin;

	QPushButton *pFile;
	QPushButton *pEdit;
	QPushButton *pLanguage;
	QPushButton *pHelp;
};


class FrameBar: public QLabel
{
	Q_OBJECT
public:
public:
	FrameBar(bool left, QWidget *parent, const QWidget *pframe);
	~FrameBar();

protected:

	virtual void  mouseMoveEvent ( QMouseEvent * ev );
	virtual void  mousePressEvent ( QMouseEvent * ev );
	virtual void mouseReleaseEvent ( QMouseEvent * ev );
	virtual void enterEvent ( QEvent * event );
	virtual void leaveEvent ( QEvent * event );
private:
	QWidget *_frame;
	bool _pressed;
	QPoint _oldPos;
	bool _left;

	QCursor _cursor;
};

extern QString gbires;

#endif // PHOTOMAKER_H
