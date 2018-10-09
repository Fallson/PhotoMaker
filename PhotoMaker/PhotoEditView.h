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

#ifndef PhotoEditView_H
#define PhotoEditView_H

#include <QGraphicsView>
#include "photoeditviewscene.h"
#include "photomaker.h"

QT_BEGIN_NAMESPACE

QT_END_NAMESPACE


class PageViewItm;


class PmPhotoView : public QGraphicsView
{
    Q_OBJECT

public:
	PmPhotoView(QWidget * parent = 0 );
	virtual ~PmPhotoView() {}

public:
	virtual void updateView(bool reload) = 0;
	virtual void reloadPhotoPage(const PmPhotoPage *pPhotoPage);
	virtual bool addPaperPage(PmPrintPaperPage *pPaperPage, int index) ;
	virtual bool rmPaperPage(const PmPrintPaperPage *pPaperPage, int &index) ;
	virtual void reloadPaperPage(const PmPrintPaperPage *pPhotoPage) ;

	//virtual void updatecurosr(PageViewItm* pViewItm, int cursor) ;
	virtual void reloadviewitm(PageViewItm* pViewItm) ;

public slots:
	 //void _updateViewItmCursor(PageViewItm* , int );
	 void _reloadViewItm(PageViewItm*);

signals:
	void setcursor(PageViewItm* , int );
	void sigreloadviewitm(PageViewItm*);

protected:
	PhotoEditViewScene* _scene;
public:
        qreal scale_lvl;
};



class PhotoEditView : public PmPhotoView
{
    Q_OBJECT

public:
   PhotoEditView(PhotoMaker *pMainFrame, QWidget * parent = 0 );

public:
	virtual void updateView(bool reload);


public:
	void scaleView(qreal scale);
	void chgOrentation();

	void cutSelection();
	void copySelection();
	void pasteSelection();

	void setBgColor(const QColor &color);
	void rotateSelectionleft();
	void rotateSelectionright();
    void setSelectionHSL();
    void setSelectionBWC();
    void setSelectionLCIG();
    void setSelectionRE();
	void zoomSelection(qreal scale);
	void delSelection();
	bool getSelection(PmPageItm *&pageitm, PmTextItm *&txtitm);
	void saveSelection();
	void restoreSelection();

	void updateSelCalCfg(const CALENDAR_CFG &calcfg);
	bool getSelCalCfg(CALENDAR_CFG &calcfg);


	void addText();
	void alignText(int align);
	void valignText(int align);
    void setTextCnt(QString &txt, qreal font_ratio);


	bool enableShadow(bool shadow);
	bool enableTxtShadow(bool shadow);
	//
	void reTranslate();


protected:
   virtual void resizeEvent(QResizeEvent *);
   	void contextMenuEvent ( QContextMenuEvent * event );

private:
	void _setViewMatrix();

private:
	PhotoMaker *_pMainFrame;
	PmPhotoMakerDoc *_pdoc;

	// menu action
	// page menu item
	QAction *_changePageOrientationAct;
	QAction *_insertPrevPageAct;
	QAction *_insertNextPageAct;
	QAction *_deletePageAct;
	QAction *_nextPageAct;
	QAction *_prevPageAct;

	// common for calendar & image
	QAction *_cutAct;
	QAction *_pasteAct;
	QAction *_copyAct;
	QAction *_delAct;


	// image
	QAction *_rotateLeftAct;
	QAction *_rotateRightAct;
	QAction *_lightEditAct;
	QAction *_colorEditAct;
	QAction *_blackwhiteEditAct;
	QAction *_remRedEyeEditAct;
	QAction *_chgBkGrndColorAct;

	qreal _sceneSizeInView;

	bool _horizonView;
	int _angel;
	bool _centered;

};



class PrintPagesPreviewView : public PmPhotoView
{
    Q_OBJECT

public:
   PrintPagesPreviewView(PhotoMaker *pMainFrame, QWidget * parent = 0 );

public:
	virtual void updateView(bool reload);
	void reloadPhotoPage(const PmPhotoPage *pPhotoPage);
	void reloadPaperPage(const PmPrintPaperPage *pPhotoPage);
	bool addPaperPage(PmPrintPaperPage *pPaperPage, int index);
	bool rmPaperPage(const PmPrintPaperPage *pPaperPage, int &index); // remove from the view

	//void rmPaperPage(PmPrintPaperPage *pPaperPage); // delete the paper
	//void insertPaperPage(PmPrintPaperPage *curpaper, bool before);


	void updateSelection(int curindex);
	void updateNextEditPaper(PmPrintPaperPage *pOldNextPaper, PmPrintPaperPage *pNextPaper);

	//
	void reTranslate();

protected:
	virtual void resizeEvent(QResizeEvent *);
	virtual void contextMenuEvent ( QContextMenuEvent * event );

public slots:
	void insertbefore();
	void insertafter();
	void delcur();

private:
	PhotoPreviewScene* _scene;
	PhotoMaker *_pMainFrame;
	PmPhotoMakerDoc *_pdoc;

	QAction *_InsBeforeAct;
	QAction *_InsAfterAct;
	QAction *_delAct;

};

#endif
