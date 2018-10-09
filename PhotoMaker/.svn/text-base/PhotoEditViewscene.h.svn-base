/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef PhotoEditViewScene_H
#define PhotoEditViewScene_H

#include <QGraphicsScene>
#include "PmPaperPage.h"
#include <QGraphicsItemGroup>
#include "photomaker.h"
#include <QTimer>
#include <QMutex>
#include "printinfobar.h"
//#include "PhotoCalViewItem.h"

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE


class PhotoMaker;

class PmViewScnen: public QGraphicsScene
{
	Q_OBJECT
public:
	PmViewScnen(QObject *parent = 0):QGraphicsScene(parent){}
	virtual ~PmViewScnen(){}

public:
	virtual void updateScene(bool bReload = true) = 0;
	virtual PhotoMaker*getMainFrame() = 0;

	virtual void reloadPhotoPage(const PmPhotoPage *pPhotoPage) = 0;
	virtual bool addPaperPage(PmPrintPaperPage *pPaperPage, int index, bool updtescene = true) = 0;
	virtual bool rmPaperPage(const PmPrintPaperPage *pPaperPage, int &index, bool updtescene = true) = 0;
	virtual void reloadPaperPage(const PmPrintPaperPage *pPaperPage, bool updtescene = true) = 0;


};

class TextViewItem;
class PhotoViewItm;
class PageViewItm;

class CalendarInfo;
class WeekdaysInfo;
class MonthYearInfo;

typedef enum{SELECTIION_IMG,SELECTIION_NULL_IMG, SELECTION_COLOR, SELECTION_TEXT, 
	SELECTION_CALENDAR, SELECTION_CAL_MONTH,SELECTION_NULL}SELECTION_ITM_TYPE;

class PhotoEditViewScene : public PmViewScnen
{
    Q_OBJECT

public:
    PhotoEditViewScene(const QRectF& rect, PhotoMaker *pMainFrame,QObject *parent = 0);

public:
	virtual void updateScene(bool bReload = true);
	virtual PhotoMaker*getMainFrame(){return _pMainFrame;}

	void reloadPhotoPage(const PmPhotoPage *pPhotoPage);
	bool addPaperPage(PmPrintPaperPage *pPaperPage, int index, bool updtescene = true);
	bool rmPaperPage(const PmPrintPaperPage *pPaperPage, int &index, bool updtescene = true);
	void reloadPaperPage(const PmPrintPaperPage *pPaperPage, bool updtescene = true);


public:
	void setPaperPage(PmPrintPaperPage *pPaperPage);
	void selectItm(PageViewItm *pViewItm, TextViewItem* txtviewitm );
	bool getSelectionType(SELECTION_ITM_TYPE &type);
	bool getSelection(PmPageItm *&pageitm, PmTextItm *&txtitm);
	void saveSelection();
	void restoreSelection();

	// aux for text pos update
	void updateTextItm(PmTextItm *txtitm, const QRectF rect);

public:
	//
	void cutSelection();
	void copySelection();
	void pasteSelection();

	// photo edit
	void setBgColor(const QColor &color);
	void rotateSelectionleft();
	void rotateSelectionright();
	void setSelectionHSL();
	void setSelectionBWC();
	void setSelectionLCIG();
	void setSelectionRE();
	void zoomSelection(qreal scale);
	void delSelction();

	// calendar edit
	void updateSelCalCfg(const CALENDAR_CFG &calcfg);
	bool getSelCalCfg(CALENDAR_CFG &calcfg);

	//
	void addText();
	void alignText(int align);
	void valignText(int align);
    void setTextCnt(QString &txt, qreal font_ratio);

	//
	bool enableShadow(bool shadow);
	bool enableTxtShadow(bool shadow);

	//


protected:
	virtual void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );

private:
	void _rmAllViewItms();
	
	//
	void _addFirstPageWnd();
	void _updateFirstPageWnd();

	//void _reloadItems();
	void _addBackgroundItm();
	void _addPhotoPage(PmPhotoPage *pPhotoPage);
	void _loadTextBoxs();
	void _addTextBox(PmTextItm *ptxtitm);

	void _updateItems();
	void _updatePhotoPage(PmPhotoPage *pPhotoPage);
	void _updateTextBox();
	void _updateBackgroundItm();

	//void _updateCalCfg2Itm(const CALENDAR_CFG &calcfg, PmPageItm &calitm, bool &updated);

	void _syncCalCfg(const CalendarInfo &ci, const WeekdaysInfo &wi, const MonthYearInfo &mi, CALENDAR_CFG &calcfg);
private:
    //int bound_size;

	QRectF _paperpageframe;
	PmPrintPaperPage *_pPaperPage;
	QGraphicsItem  *_pPaperPageBackGround;
	QGraphicsRectItem *_firstPageWnd;

	PhotoMaker *_pMainFrame;

	TextViewItem *_selctedtxtviewitm;
	PageViewItm *_selectedphotoitm;
	int _seltxtindex;
	int _txtcnt;
	int _selpageindex;
	int _pagecnt;
	int _selitmindex;
	int _itmcnt;

};


class PreviewBkgrndViewItm;
class PaperPagePreviewItmSet;
class PhotoPreviewScene : public PmViewScnen
{
    Q_OBJECT

public:
    PhotoPreviewScene(const QRectF& rect,PhotoMaker *pMainFrame, QObject *parent = 0);

public:
	bool updateNextEditPaper(PmPrintPaperPage *pOldNextPaper, PmPrintPaperPage *pNextPaper);

	virtual void updateScene(bool bReload = true);
	virtual PhotoMaker*getMainFrame(){return _pMainFrame;}

	void reloadPhotoPage(const PmPhotoPage *pPhotoPage);
	bool addPaperPage(PmPrintPaperPage *pPaperPage, int index, bool updtescene = true);
	bool rmPaperPage(const PmPrintPaperPage *pPaperPage, int &index, bool updtescene = true);
	void reloadPaperPage(const PmPrintPaperPage *pPaperPage, bool updtescene = true);


public:

	//void setPaperPage(PmPrintPaperPage *pPaperPage);
	bool getRightSelection(PmPrintPaperPage *&paper);
	void selectRightBtnPaper(PaperPagePreviewItmSet *pNewPaper);
	void select(PaperPagePreviewItmSet *pNewPaper);
	void select(int curindex);

	bool getMidPosIn2Paper(int checkpos, int &pos);
	bool getAround2Papers(int checkpos, PmPrintPaperPage *&beforepaper, PmPrintPaperPage *&nextpaper);

protected:
	void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );


private:
	bool _isSinglePageProj();
	bool _isCalendarPrj();
	bool _getBottomLable(PmPrintPaperPage *pPaperPage, int index, QString &txt);


	void _rmAllPreViewItms();

private:
    //int bound_size;

	QList<PaperPagePreviewItmSet *> _paperpageviewlst;

	QRectF _paperpageframe;
	PmPrintPaperPage *_pPaperPage;
	QGraphicsPixmapItem  *_pPaperPageBackGround;
	PhotoMaker *_pMainFrame;

	PaperPagePreviewItmSet *_currentPaper;
	PaperPagePreviewItmSet *_rightBtnPaper;

	PreviewBkgrndViewItm *_bgviweitm;
};


//class PRINT_TASK_INFO;

class PhotoPrintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    PhotoPrintScene(const QRectF& rect, PhotoMaker *pMainFrame,QObject *parent = 0);

public:
	virtual PhotoMaker*getMainFrame(){return _pMainFrame;}
	virtual void updateScene(bool bReload = true){}

	bool addPaperPage(PmPrintPaperPage *pPaperPage, int index, bool updtescene = true);


public:
	void loadPaperPage(PmPrintPaperPage *pPaperPage);
	void print(QPrinter *printer, QPainter *painter, PRINT_TASK_INFO *printInfo);
	void setprintoff(qreal xoff, qreal yoff);

public:

protected slots:
	void _printerTimerFunc();
	void _onCancelPrint();

private:
	//void _addBackgroundItm();
	void _addPhotoPage(PmPhotoPage *pPhotoPage);
	void _addTextBox();

	//void _updateItems();
	//void _updatePhotoPage(PmPhotoPage *pPhotoPage);
	void _updateTextBox();
	void _updateBackgroundItm();

	// 
	void _go2NextPrintPaper();

private:
    //int bound_size;

	QRectF _paperpageframe;
	PmPrintPaperPage *_pPaperPage;
	QGraphicsPixmapItem  *_pPaperPageBackGround;
	PhotoMaker *_pMainFrame;

	TextViewItem *_selctedtxtviewitm;
	PhotoViewItm *_selectedphotoitm;



	//QTimer *_timer;

	int _curpageno;
	int _endprintpageno;
	PmPrintPaperPage *_printerpaper;
	QPrinter *_printer;
	QPainter *_painter;
	PRINT_TASK_INFO _printInfo;
	QList<PmPrintPaperPage*> _papers;

	PmPhotoPage *_leftpage;
	QList<PmTextItm *> _printtxtlst;

	bool _cancel;
	PrintInfoBar *_printInfoBar;
	bool _twopagesinpaper;

	qreal _xoff, _yoff;

};




#endif
