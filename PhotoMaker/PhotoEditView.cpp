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

#include <QtGui>

#include "photoeditview.h"
#include "photoeditviewscene.h"
#include "photoeditviewitem.h"
#include "PmPaperPage.h"


PmPhotoView::PmPhotoView(QWidget * parent ):QGraphicsView(parent)
{
    scale_lvl = 1.0;
	//connect(this, SIGNAL(setcursor(PageViewItm*,int)),  SLOT(_updateViewItmCursor(PageViewItm*, int)));
	connect(this, SIGNAL(sigreloadviewitm(PageViewItm*)),  SLOT(_reloadViewItm(PageViewItm*)));
}

#if 0
void PmPhotoView::updatecurosr(PageViewItm* pViewItm, int cursor)
{
	emit setcursor(pViewItm, cursor);
}
#endif

void PmPhotoView::reloadviewitm(PageViewItm* pViewItm) 
{
	emit sigreloadviewitm(pViewItm);

}
#if 0
void PmPhotoView::_updateViewItmCursor(PageViewItm* pViewItm, int cursor1)
{
	QCursor cursor((Qt::CursorShape)cursor1);
	pViewItm->updateCursor(cursor);
	//this->setCursor(cursor);
}
#endif


void PmPhotoView::_reloadViewItm(PageViewItm* pViewItm)
{
	pViewItm->setContent("");
}



bool PmPhotoView::rmPaperPage(const PmPrintPaperPage *pPaperPage, int &index)
{
	return _scene->rmPaperPage(pPaperPage, index);
}

bool PmPhotoView::addPaperPage(PmPrintPaperPage *pPaperPage, int index)
{
	return _scene->addPaperPage(pPaperPage, index);
}

void PmPhotoView::reloadPaperPage(const PmPrintPaperPage *pPaperPage)
{
	_scene->reloadPaperPage(pPaperPage);
}

void PmPhotoView::reloadPhotoPage(const PmPhotoPage *pPhotoPage)
{
	if ( !pPhotoPage  )
	{
		return ;
	}
	_scene->reloadPhotoPage(pPhotoPage);


}

PhotoEditView::PhotoEditView(PhotoMaker *pMainFrame, QWidget *parent)
    :PmPhotoView(parent), _pMainFrame(pMainFrame), _pdoc(NULL),
	_sceneSizeInView(0.99), _horizonView(true),_angel(0), _centered(false)

{
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   // setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	//this->ensureVisible(QRectF(0,0,0,0));
	QRect rect = this->geometry();
    _scene = new PhotoEditViewScene(rect,_pMainFrame,this);
    this->setScene(_scene);

	if (_pMainFrame )
	{
		//
		_pdoc = _pMainFrame->getDoc();
	}
	int index = 0;
	PmPrintPaperPage *pPaperPage = NULL;
	_pdoc->getCurPrintPaperPage(pPaperPage, index);
	pPaperPage->setEditView(this);
	((PhotoEditViewScene*)_scene)->setPaperPage(pPaperPage);

	// QRect rect = this->geometry();
	 QRect scenerect;
	 scenerect.setRect(0, 0, rect.width(), rect.height());
	 _scene->setSceneRect(scenerect);
	_scene->updateScene();


	_changePageOrientationAct = new QAction(QIcon(""), tr("change page orientation"),this);


	_insertPrevPageAct = new QAction(QIcon(""), tr("inert page before"),this);
	_insertNextPageAct = new QAction(QIcon(""), tr("insert page behind"),this);
	_deletePageAct = new QAction(QIcon(""), tr("delete page"),this);
	connect(_insertPrevPageAct,SIGNAL(triggered()), this->_pMainFrame, SLOT(insertbefore()));
	connect(_insertNextPageAct,SIGNAL(triggered()), this->_pMainFrame, SLOT(insertafter()));
	connect(_deletePageAct,SIGNAL(triggered()), this->_pMainFrame, SLOT(delcur()));


	_nextPageAct = new QAction(QIcon(""), tr("previous page"),this);;
	_prevPageAct = new QAction(QIcon(""), tr("next page"),this);
	connect(_nextPageAct,SIGNAL(triggered()), this->_pMainFrame, SLOT(nextPage()));
	connect(_prevPageAct,SIGNAL(triggered()), this->_pMainFrame, SLOT(prePage()));


	// common for calendar & image
	_cutAct = new QAction(QIcon(""), tr("Cut"),this);
	_pasteAct = new QAction(QIcon(""), tr("Paste"),this);
	_copyAct = new QAction(QIcon(""), tr("Copy"),this);
	_delAct = new QAction(QIcon(""), tr("Delete"),this);
	connect(_cutAct, SIGNAL(triggered()), this->_pMainFrame, SLOT(OnCut()));
	connect(_copyAct, SIGNAL(triggered()), this->_pMainFrame, SLOT(OnCopy()));
	connect(_pasteAct, SIGNAL(triggered()), this->_pMainFrame, SLOT(OnPaste()));
	connect(_delAct, SIGNAL(triggered()), this->_pMainFrame, SLOT(OnDelSelection()));

	// image
	_rotateLeftAct = new QAction(QIcon(""), tr("Rotate Picture Left"),this);
	_rotateRightAct = new QAction(QIcon(""), tr("Rotate Picture Right"),this);
	_lightEditAct = new QAction(QIcon(""), tr("Lightness, contrast, intensity,gamma..."),this);
	_colorEditAct = new QAction(QIcon(""), tr("Hue, saturation, lightness..."),this);
	_blackwhiteEditAct = new QAction(QIcon(""), tr("Black and white, colorize..."),this);
	_remRedEyeEditAct = new QAction(QIcon(""), tr("Remove red-eyes..."),this);
	_chgBkGrndColorAct = new QAction(QIcon(""), tr("Change olor"),this);
	connect(_rotateLeftAct,SIGNAL(triggered()), this->_pMainFrame, SLOT(rotatePhotoleft()));
	connect(_rotateRightAct,SIGNAL(triggered()), this->_pMainFrame, SLOT(rotatePhotoright()));
	connect(_lightEditAct,SIGNAL(triggered()), this->_pMainFrame, SLOT(setPhotoLCIG()));
	connect(_colorEditAct,SIGNAL(triggered()), this->_pMainFrame, SLOT(setPhotoHSL()));
	connect(_blackwhiteEditAct,SIGNAL(triggered()), this->_pMainFrame, SLOT(setPhotoBWC()));
	//connect(_remRedEyeEditAct,SIGNAL(triggered()), this->_pMainFrame, SLOT(setPhotoBWC()));
}

void PhotoEditView::reTranslate()
{
	_changePageOrientationAct->setText( tr("change page orientation"));
	_insertPrevPageAct->setText(tr("inert page before"));
	_insertNextPageAct->setText(tr("insert page behind"));
	_deletePageAct->setText(tr("delete page"));
	_nextPageAct->setText(tr("previous page"));
	_prevPageAct->setText(tr("next page"));


	// common for calendar & image
	_cutAct->setText( tr("Cut"));
	_pasteAct->setText( tr("Paste"));
	_copyAct->setText(tr("Copy"));
	_delAct->setText(tr("Delete"));

	// image
	_rotateLeftAct->setText(tr("Rotate Picture Left"));
	_rotateRightAct->setText(tr("Rotate Picture Right"));
	_lightEditAct->setText(tr("Lightness, contrast, intensity,gamma..."));
	_colorEditAct->setText(tr("Hue, saturation, lightness..."));
	_blackwhiteEditAct->setText( tr("Black and white, colorize..."));
	_remRedEyeEditAct->setText(tr("Remove red-eyes..."));
	_chgBkGrndColorAct->setText(tr("Change olor"));
}

 void PhotoEditView::resizeEvent(QResizeEvent *)
 {
	 //
	 QRect rect = this->geometry();
	 static QRect lastrect;
	 if ( abs(rect.width()-lastrect.width()) < 3 && abs(rect.height()-lastrect.height())<3)
	 {
		 return ;
	 }
	if ( _centered )
	{
		if ( fabs(scale_lvl - 1) < 0.0001 )
		{
			_centered = false;
		}
	}
	 lastrect = rect;
	 QRect scenerect;
	 if ( this->_horizonView )
	 {
		 scenerect.setRect(0, 0, rect.width()*_sceneSizeInView, rect.height()*_sceneSizeInView);
	 }
	 else
	 {
		 scenerect.setRect(0, 0, rect.height()*_sceneSizeInView, rect.width()*_sceneSizeInView);
	 }
	 _scene->setSceneRect(scenerect);
	scaleView(this->scale_lvl);
	 _scene->updateScene(false);
	 //_scene->update();
 }

void PhotoEditView::contextMenuEvent ( QContextMenuEvent * event )
{
	QGraphicsView::contextMenuEvent(event);
	//
	// check which is select
		// right click

	QMenu *menu = new QMenu();

	SELECTION_ITM_TYPE itmtype;
	bool ret = _scene->getSelectionType(itmtype);


	// image
	if ( !ret || SELECTION_NULL == itmtype || SELECTION_CAL_MONTH == itmtype )
	{
		// no item is selected, 
		menu->addAction(_changePageOrientationAct);
		menu->addSeparator();

		menu->addAction(_insertPrevPageAct);
		menu->addAction(_insertNextPageAct);
		menu->addSeparator();

		menu->addAction(_deletePageAct);
		menu->addSeparator();

		menu->addAction(_nextPageAct);
		menu->addAction(_prevPageAct);
	}
	else if ( SELECTIION_IMG == itmtype || SELECTIION_NULL_IMG==itmtype || SELECTION_COLOR==itmtype )
	{
		// no item is selected, 
		bool enabled = false;

		menu->addAction(_rotateLeftAct);
		menu->addAction(_rotateRightAct);
		menu->addSeparator();

		menu->addAction(_lightEditAct);
		menu->addAction(_colorEditAct);
		menu->addAction(_blackwhiteEditAct);
		menu->addAction(_remRedEyeEditAct);
		menu->addSeparator();
		menu->addAction(_chgBkGrndColorAct);
		menu->addSeparator();

		menu->addAction(_cutAct);
		menu->addAction(_copyAct);
		menu->addAction(_pasteAct);
		menu->addSeparator();

		menu->addAction(_delAct);

		// update status
		_rotateLeftAct->setEnabled(false);
		_rotateRightAct->setEnabled(false);
		_lightEditAct->setEnabled(false);
		_colorEditAct->setEnabled(false);
		_blackwhiteEditAct->setEnabled(false);
		_remRedEyeEditAct->setEnabled(false);
		_chgBkGrndColorAct->setEnabled(false);
		_cutAct->setEnabled(false);
		_copyAct->setEnabled(false);
		_pasteAct->setEnabled(false);
		_delAct->setEnabled(false);

		if ( SELECTIION_IMG == itmtype )
		{
			//
			_rotateLeftAct->setEnabled(true);
			_rotateRightAct->setEnabled(true);
			_lightEditAct->setEnabled(true);
			_colorEditAct->setEnabled(true);
			_blackwhiteEditAct->setEnabled(true);
			_remRedEyeEditAct->setEnabled(true);
			//_chgBkGrndColorAct->setEnabled(false);
			_cutAct->setEnabled(true);
			_copyAct->setEnabled(true);

			QClipboard *cb = QApplication::clipboard();
			const QMimeData *mimedata = cb->mimeData();
			QByteArray type ;
			QByteArray srcapp;
			if ( mimedata )
			{
				srcapp = mimedata->data("srcapp");
				type = mimedata->data("type");	 // img, text
			}

			if ( srcapp == "photomaker" && QString(type.data()).length() )
			{
				_pasteAct->setEnabled(true); // check if there's antying in clipboard
			}
			else
			{
				_pasteAct->setEnabled(false); // check if there's antying in clipboard
			}
			_delAct->setEnabled(true);
		}
		else if ( SELECTION_COLOR == itmtype )
		{
			_chgBkGrndColorAct->setEnabled(true);
			_cutAct->setEnabled(true);
			_copyAct->setEnabled(true);
			QClipboard *cb = QApplication::clipboard();
			const QMimeData *mimedata = cb->mimeData();
			QByteArray type ;
			QByteArray srcapp;
			if ( mimedata )
			{
				srcapp = mimedata->data("srcapp");
				type = mimedata->data("type");	 // img, text
			}

			if ( srcapp == "photomaker" && QString(type.data()).length() )
			{
				_pasteAct->setEnabled(true); // check if there's antying in clipboard
			}
			else
			{
				_pasteAct->setEnabled(false); // check if there's antying in clipboard
			}
			_delAct->setEnabled(true);
		}
		else
		{
			QClipboard *cb = QApplication::clipboard();
			const QMimeData *mimedata = cb->mimeData();
			QByteArray type ;
			QByteArray srcapp;
			if ( mimedata )
			{
				srcapp = mimedata->data("srcapp");
				type = mimedata->data("type");	 // img, text
			}

			if ( srcapp == "photomaker" && QString(type.data()).length() )
			{
				_pasteAct->setEnabled(true); // check if there's antying in clipboard
			}
			else
			{
				//_pasteAct->setEnabled(false); // check if there's antying in clipboard
			}

		}
	}
	else if ( SELECTION_CALENDAR == itmtype )
	{
		_cutAct->setEnabled (false);
		_copyAct->setEnabled (false);
		_pasteAct->setEnabled (false);
		_delAct->setEnabled (false);

		menu->addAction(_cutAct);
		menu->addAction(_copyAct);
		menu->addAction(_pasteAct);
		menu->addSeparator();

		menu->addAction(_delAct);
	}
	else if ( SELECTION_TEXT == itmtype )
	{
		_cutAct->setEnabled (true);
		_copyAct->setEnabled (true);
		QClipboard *cb = QApplication::clipboard();
		const QMimeData *mimedata = cb->mimeData();
		QByteArray type ;
		QByteArray srcapp;
		if ( mimedata )
		{
			srcapp = mimedata->data("srcapp");
			type = mimedata->data("type");	 // img, text
		}

		if ( srcapp == "photomaker" && QString(type.data()).length() )
		{
			_pasteAct->setEnabled(true); // check if there's antying in clipboard
		}
		else
		{
			_pasteAct->setEnabled(false); // check if there's antying in clipboard
		}
		_delAct->setEnabled (true);

		menu->addAction(_cutAct);
		menu->addAction(_copyAct);
		menu->addAction(_pasteAct);
		menu->addSeparator();

		menu->addAction(_delAct);
	}



	menu->exec(event->globalPos());
	delete menu;
}


void PhotoEditView::updateView(bool reload)
{
	//
	if ( reload )
	{
		PmPrintPaperPage *pcurpaper = NULL;
		int index = 0;
		if ( _pdoc->getCurPrintPaperPage(pcurpaper, index)  && pcurpaper)
		{
			pcurpaper->setEditView(this);
			((PhotoEditViewScene*)_scene)->setPaperPage(pcurpaper);
			_scene->updateScene(reload);
		}
		 //_setViewMatrix();

		this->update();


		if ( !_horizonView  )
		{
			_setViewMatrix();
			_scene->updateScene(false);
		}



	}
	else
	{
		_scene->update();
		this->update();

	}
	return ;

}

void PhotoEditView::chgOrentation()
{
	_horizonView = !_horizonView;
	_centered = false;
	if ( !_horizonView )
	{
	}
	else
	{
		if ( _angel == 90 )
		{
		}
	}

	if ( !_horizonView  )
	{
		_angel = 90;
	}

	 //lastrect = rect;
	QRect rect = this->geometry();
	 QRect scenerect;

	 _scene->setSceneRect(scenerect);
	 _setViewMatrix();
	 _scene->updateScene(false);

}
void PhotoEditView::_setViewMatrix()
{
	QMatrix matrix;
	matrix.scale(scale_lvl, scale_lvl);

	if ( !_horizonView )
	{
		matrix.rotate(90);
	}
	else
	{
		matrix.rotate(0);
	}

	QRect rect = this->geometry();
	 QRect scenerect;
	 if ( this->_horizonView )
	 {
		 scenerect.setRect(0, 0, rect.width()*_sceneSizeInView, rect.height()*_sceneSizeInView);
	 }
	 else
	 {
		 scenerect.setRect(0, 0, rect.height()*_sceneSizeInView, rect.width()*_sceneSizeInView);
	 }
	 _scene->setSceneRect(scenerect);

	this->setMatrix(matrix);

	static bool first = true;
	if ( first )
	{
		if ( !_horizonView )
		{
			first = false;
			QRectF scrc = this->sceneRect();
			this->centerOn(scrc.width()*0.5, scrc.height()*0.5);

		}
	}
	this->_scene->update();
}

void PhotoEditView::scaleView(qreal scale)
{
	scale_lvl = scale;
	_setViewMatrix();

	if ( !_centered )
	{
		if ( scale_lvl > 1 )
		{
			_centered = true;
			QRectF scrc = this->sceneRect();
			this->centerOn(scrc.width()*0.5, scrc.height()*0.5);

		}
	}
}


void PhotoEditView::cutSelection()
{
	PhotoEditViewScene *editscene = _scene;
	editscene->cutSelection();
}

void PhotoEditView::copySelection()
{
	PhotoEditViewScene *editscene = _scene;
	editscene->copySelection();
}

void PhotoEditView::pasteSelection()
{
	PhotoEditViewScene *editscene = _scene;
	editscene->pasteSelection();
}


void PhotoEditView::rotateSelectionleft()
{
	PhotoEditViewScene *editscene = _scene;
	editscene->rotateSelectionleft();
}

void PhotoEditView::setBgColor(const QColor &color)
{
	PhotoEditViewScene *editscene = _scene;
	editscene->setBgColor(color);
}

void PhotoEditView::rotateSelectionright()
{
	PhotoEditViewScene *editscene = _scene;
	editscene->rotateSelectionright();
}

void PhotoEditView::setSelectionHSL()
{
    PhotoEditViewScene *editscene = _scene;
    editscene->setSelectionHSL();
}

void PhotoEditView::setSelectionBWC()
{
    PhotoEditViewScene *editscene = _scene;
    editscene->setSelectionBWC();
}

void PhotoEditView::setSelectionLCIG()
{
    PhotoEditViewScene *editscene = _scene;
    editscene->setSelectionLCIG();
}

void PhotoEditView::setSelectionRE()
{
    PhotoEditViewScene *editscene = _scene;
    editscene->setSelectionRE();
}

void PhotoEditView::zoomSelection(qreal scale)
{
	PhotoEditViewScene *editscene = _scene;
	editscene->zoomSelection(scale);
}

void PhotoEditView::delSelection()
{
	PhotoEditViewScene *editscene = _scene;
	editscene->delSelction();
}

bool PhotoEditView::getSelection(PmPageItm *&pageitm, PmTextItm *&txtitm)
{
	return this->_scene->getSelection(pageitm, txtitm);
}
void PhotoEditView::saveSelection()
{
	_scene->saveSelection();
}

void PhotoEditView::restoreSelection()
{
	_scene->restoreSelection();
}


void PhotoEditView::updateSelCalCfg(const CALENDAR_CFG &calcfg)
{
	PhotoEditViewScene *editscene = _scene;
	editscene->updateSelCalCfg(calcfg);
}
	
bool PhotoEditView::getSelCalCfg(CALENDAR_CFG &calcfg)
{
	PhotoEditViewScene *editscene = _scene;
	return editscene->getSelCalCfg(calcfg);
}

void PhotoEditView::addText()
{
	PhotoEditViewScene *editscene = _scene;
	return editscene->addText();
}

void PhotoEditView::alignText(int align)
{
	PhotoEditViewScene *editscene = _scene;
	return editscene->alignText(align);

}
void PhotoEditView::valignText(int align)
{
	PhotoEditViewScene *editscene = _scene;
	return editscene->valignText(align);
}

void PhotoEditView::setTextCnt(QString &txt, qreal font_ratio)
{
	PhotoEditViewScene *editscene = _scene;
    return editscene->setTextCnt(txt, font_ratio);

}


bool PhotoEditView::enableTxtShadow(bool shadow)
{
	return this->_scene->enableTxtShadow(shadow);
}

bool PhotoEditView::enableShadow(bool shadow)
{
	return this->_scene->enableShadow(shadow);
}


PrintPagesPreviewView::PrintPagesPreviewView(PhotoMaker *pMainFrame, QWidget *parent)
    :PmPhotoView(parent), _pMainFrame(pMainFrame), _pdoc(NULL)
{
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QRect rect = this->geometry();
    _scene = new PhotoPreviewScene(rect,_pMainFrame, this);
    this->setScene(_scene);

	if (_pMainFrame )
	{
		//
		_pdoc = _pMainFrame->getDoc();
	}

	QRect scenerect;
	 scenerect.setRect(0, 0, rect.width(), rect.height());
	 _scene->setSceneRect(scenerect);
	_scene->updateScene();


	_InsBeforeAct = new QAction(QIcon(""), tr("Insert before"),this);
	_InsAfterAct = new QAction(QIcon(""), tr("Insert after"),this);
	_delAct = new QAction(QIcon(""), tr("delete"),this);

	connect(_InsBeforeAct, SIGNAL(triggered()), this, SLOT(insertbefore()));
	connect(_InsAfterAct, SIGNAL(triggered()), this, SLOT(insertafter()));
	connect(_delAct, SIGNAL(triggered()), this, SLOT(delcur()));

}

void PrintPagesPreviewView::reTranslate()
{
	_InsBeforeAct->setText(tr("Insert before"));
	_InsAfterAct->setText(tr("Insert after"));
	_delAct->setText(tr("delete"));
}

 void PrintPagesPreviewView::resizeEvent(QResizeEvent *)
 {
	 //
	 QRect rect = this->geometry();
	 QRectF scenerect = _scene->sceneRect();
	 
	 int xoff = (int)scenerect.height()-rect.height();
	 int yoff = (int)scenerect.width()-rect.width();
	 if (  abs(xoff) < 1 && abs(yoff) < 1 )
	 {
		 return ;
	 }
	 scenerect.setRect(0, 0, rect.width(), rect.height()-20);
	 _scene->setSceneRect(scenerect);
	 _scene->updateScene(false);
 }

 
 void PrintPagesPreviewView::contextMenuEvent ( QContextMenuEvent * event )
 {
	QGraphicsView::contextMenuEvent(event);
	//
	// check which is select
		// right click

	QMenu *menu = new QMenu();

	// no item is selected, 
	menu->addAction(_InsBeforeAct);
	menu->addAction(_InsAfterAct);
	menu->addAction(_delAct);

	_InsBeforeAct->setEnabled(false);
	_InsAfterAct->setEnabled(false);
	_delAct->setEnabled(false);

	 // if calendar project, not allow to add/remove papers


	 PmPrintPaperPage *paper = NULL;
	 _scene->getRightSelection(paper);
	 if ( paper )
	 {
		 int selpaperindex = 0;
		 _pdoc->getPaperIndex(paper, selpaperindex);
		 QList<PmPrintPaperPage *> papers;
		 _pdoc->getPrintPaperPages(papers);
		 if ( selpaperindex == 0 )
		 {
			 // if first paper, only allow insert after
			 _InsAfterAct->setEnabled(true);

		 }
		 else if ( selpaperindex == papers.size() -1 )
		 {
			 // if last paper, only allow insert before
			 _InsBeforeAct->setEnabled(true);
		 }
		 else
		 {
			  _InsAfterAct->setEnabled(true);
			  _InsBeforeAct->setEnabled(true);
			  _delAct->setEnabled(true);
			 // other pages, allow insert before, after, delete

		 }
	 }

	menu->exec(event->globalPos());
	delete menu;	 


 }

 void PrintPagesPreviewView::insertbefore()
 {
	 PmPrintPaperPage *paper = NULL;
	 _scene->getRightSelection(paper);
	 if ( !paper )
	 {
		 return ;
	 }

	int index = 0;
	_pdoc->getPaperIndex(paper, index);
	
	_pMainFrame->addPaperAtIndex(index);

 }

 void PrintPagesPreviewView::insertafter()
 {
	 PmPrintPaperPage *paper = NULL;
	 _scene->getRightSelection(paper);
	 if ( !paper )
	 {
		 return ;
	 }
	int index = 0;
	_pdoc->getPaperIndex(paper, index);
	
	_pMainFrame->addPaperAtIndex(index+1);

 }

#if 0
void PrintPagesPreviewView::insertPaperPage(PmPrintPaperPage *curpaper, bool before)
{
	 PmPrintPaperPage *newpaper = NULL;
	 int index = 0;

	 _pdoc->addPrintPaper(curpaper, before, newpaper, index);
	 this->_scene->addPaperPage(newpaper, index);
}

void PrintPagesPreviewView::rmPaperPage(PmPrintPaperPage *paper)
{

	 int index = 0;

	 
	 this->_scene->rmPaperPage(paper,index);

	 PmPrintPaperPage * curpaper = NULL;
	 int curselidx = 0;
	 _pMainFrame->getDoc()->getCurPrintPaperPage(curpaper,curselidx );
	 if ( paper == curpaper)
	{
		// curent page is delted, select the next page 
		this->_pMainFrame->getDoc()->moveNextPaperPage();
		 _pdoc->rmPrintPaper(paper,  index);

		_scene->select(index);
	}
	 else
	 {
		 _pdoc->rmPrintPaper(paper,  index);
	 }

	 // paper is not deleted, later it can be added to undo action stack

	 // set the last edit page
	 PmPrintPaperPage *nextpaper = NULL;
	 _pdoc->getNextEditPaper(nextpaper);
	 updateNextEditPaper(NULL, nextpaper);
	 _scene->updateScene(false);
}
#endif

 void PrintPagesPreviewView::delcur()
 {
	 PmPrintPaperPage *paper = NULL;
	 _scene->getRightSelection(paper);
	 if ( !paper )
	 {
		 return ;
	 }
	 
	 _pMainFrame->delPaper(paper);
	// rmPaperPage(paper);

	 // insert to undao action stack
 }

void PrintPagesPreviewView::updateView(bool reload)
{
	//
	if ( reload )
	{
		PmPrintPaperPage *pcurpaper = NULL;
		int index = 0;
		if ( _pdoc->getCurPrintPaperPage(pcurpaper, index)  && pcurpaper)
		{
			//((PhotoPreviewScene*)_scene)->setPaperPage(pcurpaper);
			_scene->updateScene(reload);
		}
		this->update();
	}
	else
	{
		QRect rect = this->geometry();
		QRectF oldscenerect = _scene->sceneRect();

		// rect =  rect.adjusted(0,0,0,-10);
		// get

		QScrollBar *vscrollbar = verticalScrollBar();
		QScrollBar *hscrollbar = horizontalScrollBar();

		int vpos = vscrollbar->value();
		int hpos = hscrollbar->value();


		//scenerect.setRect(0, 0, rect.width(), rect.height());
		//_scene->setSceneRect(scenerect);
		_scene->updateScene(false);

		QRectF scenerect = _scene->sceneRect();
		if ( scenerect != oldscenerect )
		{
			vscrollbar->setValue(vpos);
			hscrollbar->setValue(hpos);
		}
	}
	return ;

}

void PrintPagesPreviewView::reloadPhotoPage(const PmPhotoPage *pPhotoPage)
{
	_scene->reloadPhotoPage(pPhotoPage);
}

bool PrintPagesPreviewView::addPaperPage(PmPrintPaperPage *pPaperPage, int index)
{
	return _scene->addPaperPage(pPaperPage,index);
}

bool PrintPagesPreviewView::rmPaperPage(const PmPrintPaperPage *pPaperPage, int &index)
{
	return _scene->rmPaperPage(pPaperPage, index);
}
void PrintPagesPreviewView::reloadPaperPage(const PmPrintPaperPage *pPaperPage)
{
	_scene->reloadPaperPage(pPaperPage);
}


void PrintPagesPreviewView::updateSelection(int curindex)
{
	_scene->select(curindex);
}

void PrintPagesPreviewView::updateNextEditPaper(PmPrintPaperPage *pOldNextPaper, PmPrintPaperPage *pNextPaper)
{
	_scene->updateNextEditPaper(pOldNextPaper,pNextPaper);
}
