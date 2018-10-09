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

#include "photoeditviewscene.h"
#include "photoeditviewitem.h"
#include "photomaker.h"
#include "PhotoEditView.h"
#include "PhotoEditViewItem.h"
#include "PhotoCalViewItem.h"
#include "PhotoTextViewItem.h"
#include "pmundoactionstack.h"

#ifdef _WIN32
//#include <Windows.h>
#endif

#define _DEBUG_FALLSON
#undef _DEBUG_FALLSON

#define DEFAULT_BOUNDSIZE 10
#define PRINT_PREFERED_HEIGHT	800

PhotoEditViewScene::PhotoEditViewScene(const QRectF& rect,  PhotoMaker *pMainFrame, QObject *parent)
    : PmViewScnen(parent),_pPaperPage(NULL), _pPaperPageBackGround(NULL),
	_pMainFrame(pMainFrame), _selctedtxtviewitm(NULL),_selectedphotoitm(NULL), _firstPageWnd(NULL)
{
    //setBoundSize(DEFAULT_BOUNDSIZE);
    setSceneRect(rect);
    setBackgroundBrush(Qt::white);
}

void PhotoEditViewScene::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
	//
	QGraphicsScene::mousePressEvent(mouseEvent);
	if (this->selectedItems().size() == 0)
	{
		selectItm(NULL, NULL);
	}
}


void PhotoEditViewScene::saveSelection()
{
	_seltxtindex = -1;
	_txtcnt = 0;
	_selpageindex = -1;
	_pagecnt = 0;
	_selitmindex = -1;
	_itmcnt = 0;

	PmTextItm *selctedtxtitm = NULL;
	if( _selctedtxtviewitm )
	{
		selctedtxtitm = _selctedtxtviewitm->getTextItm();
		QList<PmTextItm *> txtlst;
		selctedtxtitm->getPrintPage()->getTextbox(txtlst);
		_txtcnt = txtlst.size();
		int index = -1;
		QList<PmTextItm *>::iterator it;
		index = 0;
		for(it=txtlst.begin(); it!=txtlst.end(); it++, index++ )
		{
			if ( *it == selctedtxtitm )
			{
				break;
			}
		}
		if ( it == txtlst.end() )
		{
			index = -1;
		}
		_seltxtindex = index;
	}

	PmPageItm *selectedphotoitm = NULL;
	if ( _selectedphotoitm )
	{
		selectedphotoitm = _selectedphotoitm->getPmPageItm();
		PmPhotoPage *page = selectedphotoitm->getPage();
		QList<PmPhotoPage *> pagelst;
		page->getPaperPage()->getPhotoPages(pagelst);
		_pagecnt = pagelst.size();
		QList<PmPhotoPage *>::iterator it;
		_selpageindex = 0;
		for ( it=pagelst.begin(); it!=pagelst.end(); it++, _selpageindex++ )
		{
			PmPhotoPage *chkpage = *it;
			if ( chkpage == page )
			{
				break;
			}

		}
		if ( it == pagelst.end() )
		{
			_selpageindex = -1;
		}
		if ( _selpageindex >= 0 )
		{
			QList<PmPageItm *>  pageitmlst;
			page->getPicItms(pageitmlst);
			_itmcnt = pageitmlst.size();
			QList<PmPageItm *>::iterator pageitmit;
			_selitmindex = 0;
			for ( pageitmit=pageitmlst.begin(); pageitmit!=pageitmlst.end(); pageitmit++, _selitmindex++ )
			{
				if ( *pageitmit == selectedphotoitm )
				{
					break;
				}

			}	
			if ( pageitmit == pageitmlst.end() )
			{
				_selitmindex = -1;
			}
		}
	}
}

void PhotoEditViewScene::restoreSelection()
{
			
	if(  _seltxtindex >= 0 && _txtcnt > 0  )
	{
		QList<PmTextItm *> txtlst;
		_pPaperPage->getTextbox(txtlst);
		QList<PmTextItm *>::iterator it;

		if ( _txtcnt == txtlst.size() )
		{
			int i=0; 
			for ( it=txtlst.begin(); it!=txtlst.end(); it++, i++ )
			{
				//
				if( i== _seltxtindex )
				{
					break;
				}
			}
			if ( it!=txtlst.end() )
			{
				_selctedtxtviewitm = (TextViewItem*)(*it)->getViewItm();
			}
		}
	}



	if ( _selpageindex>=0 && _selitmindex>=0 )
	{
		QList<PmPhotoPage *> pagelst;
		_pPaperPage->getPhotoPages(pagelst);
		if ( _pagecnt == pagelst.size() )
		{
			QList<PmPhotoPage *>::iterator it;
			int i=0;
			for ( it=pagelst.begin(); it!=pagelst.end(); it++, i++ )
			{
				if ( i == _selpageindex )
				{
					break;
				}

			}
			if ( it != pagelst.end() )
			{
				QList<PmPageItm *>  pageitmlst;
				(*it)->getPicItms(pageitmlst);
				if ( _itmcnt == pageitmlst.size() )
				{
					QList<PmPageItm *>::iterator pageitmit;
					int itmi = 0;
					for ( pageitmit=pageitmlst.begin(); pageitmit!=pageitmlst.end(); pageitmit++, itmi++ )
					{
						if ( itmi == _selitmindex )
						{
							break;
						}

					}
					if ( pageitmit != pageitmlst.end() )
					{
						_selectedphotoitm  = (PageViewItm *)(*pageitmit)->getPageViewItm();
					}
				}
			}
		}
	}
	this->selectItm(_selectedphotoitm, _selctedtxtviewitm);
}

bool PhotoEditViewScene::getSelection(PmPageItm *&pageitm, PmTextItm *&txtitm)
{
	txtitm = NULL;
	pageitm = NULL;
	if  (_selctedtxtviewitm )
	{
		txtitm = _selctedtxtviewitm->getTextItm();
	}

	if ( _selectedphotoitm )
	{
		pageitm = _selectedphotoitm->getPmPageItm();
	}

	return true;
}
bool PhotoEditViewScene::getSelectionType(SELECTION_ITM_TYPE &type)
{
	if ( !_selctedtxtviewitm && !_selectedphotoitm)
	{
		type = SELECTION_NULL;
		return true;
	}
	if ( _selectedphotoitm )
	{
		PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm*>(_selectedphotoitm);
		if ( photoviewitm )
		{
			PmPageItm *pageitm = photoviewitm->getPmPageItm();
			if ( !pageitm )
			{
				// should not be
				type = SELECTIION_IMG;
				return true;
			}
			QString imgpath;
			pageitm->getContent(imgpath);
			if ( imgpath.length() )
			{
				type = SELECTIION_IMG;
				return true;
			}
			QColor color;
			pageitm->getBgColor(color);
			if ( color != Qt::white )
			{
				// has filled color
				type = SELECTION_COLOR;
				return true;
			}
			type = SELECTIION_NULL_IMG;
			return true;
		}
		if ( dynamic_cast<CalViewItm*>(_selectedphotoitm) )
		{
			type = SELECTION_CALENDAR;
			return true;
		}
	}

	if ( _selctedtxtviewitm )
	{
		type = SELECTION_TEXT;
		return true;
	}

	return false;
}

void PhotoEditViewScene::selectItm(PageViewItm *pViewItm,  TextViewItem* txtviewitm)
{
	 if ( pViewItm )
	 {
		 // select photo item
		 if ( this->_selctedtxtviewitm )
		 {
			 _selctedtxtviewitm->setSelected(false);
			 _selctedtxtviewitm->update();
			 _selctedtxtviewitm= NULL;
		 }
		 if ( _selectedphotoitm )
		 {
			 _selectedphotoitm->setZValue(2);
			 _selectedphotoitm->setSelected(false);
			 _selectedphotoitm->update();
			 PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm *>(_selectedphotoitm);
			 if ( photoviewitm )
			 {
				photoviewitm->selectPanoramaPair(false);
			 }
			 _selectedphotoitm = NULL;
		 }
		 this->_selectedphotoitm = pViewItm;
		 _selectedphotoitm->setSelected(true);
		  _selectedphotoitm->setZValue(3);
		 _selectedphotoitm->update();

		 PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm *>(_selectedphotoitm);
		 if ( photoviewitm )
		 {
			 photoviewitm->selectPanoramaPair(true);
		 }
		 if ( dynamic_cast<PhotoViewItm*>(pViewItm) )
		 {
			 this->_pMainFrame->showEditPane(PmBottomCtrlPane::PHOTO_EDIT);
		 }
		 else if ( dynamic_cast<CalViewItm*>(pViewItm) )
		 {
			 this->_pMainFrame->showEditPane(PmBottomCtrlPane::CALENDAR_EDIT);
		 }

	 }
	 else if ( txtviewitm )
	 {
		 // seletect text item
		 if ( this->_selectedphotoitm )
		 {
			 _selectedphotoitm->setSelected(false);
			 _selectedphotoitm->update();

			 PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm *>(_selectedphotoitm);
			 if ( photoviewitm )
			 {
				 photoviewitm->selectPanoramaPair(false);
			 }
			 _selectedphotoitm = NULL;
		 }
		 this->_selctedtxtviewitm = txtviewitm;
		 _selctedtxtviewitm->setSelected(true);
		 _selctedtxtviewitm->update();

		 //text item is slected, show text edit bottom pane
		 QString cnt;
		 _selctedtxtviewitm->getTextItm()->getContent(cnt);
		 this->_pMainFrame->showEditPane(PmBottomCtrlPane::TEXT_EDIT, cnt);
	 }
	 else
	 {
		 if ( this->_selectedphotoitm )
		 {
			 _selectedphotoitm->setSelected(false);
			 _selectedphotoitm->setZValue(2);
			 _selectedphotoitm->update();
			 PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm *>(_selectedphotoitm);
			 if ( photoviewitm )
			 {
				 photoviewitm->selectPanoramaPair(false);
			 }
			 _selectedphotoitm = NULL;
		 }
		 if ( this->_selctedtxtviewitm )
		 {
			 _selctedtxtviewitm->setSelected(false);
			 _selctedtxtviewitm->update();
			 _selctedtxtviewitm = NULL;
		 }
		 this->_pMainFrame->showEditPane(PmBottomCtrlPane::HIDE_EDIT);

	 }
	 update();
}
	
void PhotoEditViewScene::updateTextItm(PmTextItm *txtitm, const QRectF rect)
{
	if ( !txtitm )
	{
		return ;
	}
	LayoutBoxMargin marginInEditView;
	txtitm->getPrintPage()->getMarginInEditView(marginInEditView);

	LayoutBoxPos pos;
	txtitm->getRectInPrintPage(pos);
	QRectF rcInScene ;
	
	pos.width = rect.width();
	pos.height = rect.height();
	pos.y = (rect.top()-_paperpageframe.top())/(_paperpageframe.height()*(1-marginInEditView.top-marginInEditView.bottom));
	//pos.height = rect.height()/(_paperpageframe.height()*(1-marginInEditView.top-marginInEditView.bottom));
	//pos.width = rect.width()/(_paperpageframe.width()*(1-marginInEditView.left-marginInEditView.right-marginInEditView.mid));
	if ( rect.left() < (_paperpageframe.left()+_paperpageframe.right())/2 )
	{
		// left page
		pos.x = (rect.left()-_paperpageframe.left())/(_paperpageframe.width()*(1-marginInEditView.left-marginInEditView.right-marginInEditView.mid));
	}
	else
	{
		// right page
		pos.x = (rect.left()-_paperpageframe.left()-_paperpageframe.width()*(marginInEditView.left+marginInEditView.mid))/(_paperpageframe.width()*(1-marginInEditView.left-marginInEditView.right-marginInEditView.mid));
	}

	txtitm->setRectInPrintPage(pos);

	// update last index
	PmPrintPaperPage *paper = txtitm->getPrintPage();
	if ( !paper )
	{
		return ;
	}
	QList<PmPhotoPage *> photopages;
	paper->getPhotoPages(photopages);
	if ( photopages.size() == 2 )
	{
		if ( pos.x < 0.5 )
		{
			_pMainFrame->updateLastPhotoPage(photopages.first());
		}
		else
		{
			_pMainFrame->updateLastPhotoPage(photopages.last());
		}
	}
	else if ( photopages.size() == 1 )
	{
		_pMainFrame->updateLastPhotoPage(photopages.first());
	}
}

void PhotoEditViewScene::_rmAllViewItms()
{
	 QList<QGraphicsItem *> gpitmlst = this->items();
	 QList<QGraphicsItem *>::iterator it;
	 for ( it=gpitmlst.begin(); it!=gpitmlst.end(); it++ )
	 {
		 QGraphicsItem *gpitm = *it;
		 PageViewItm *pgviewitm = dynamic_cast<PageViewItm *>(gpitm);
		 if ( pgviewitm )
		 {
			 PmPageItm *pageitm = pgviewitm->getPmPageItm();
			 if ( pageitm )
			 {
				 pageitm->setPageViewItm(NULL);
			 }
		 }
		 TextViewItem *txtviweitm = dynamic_cast<TextViewItem *>(gpitm);
		 if ( txtviweitm )
		 {
			 PmTextItm *txtitm = txtviweitm->getTextItm();
			 txtitm->setViewItm(NULL);
		 }
	 }

	 clear();
}

void PhotoEditViewScene::updateScene(bool bReload)
{
	//
	if ( bReload )
	{

		// set all pageitem's view item to null


		_selctedtxtviewitm = NULL;
		_selectedphotoitm = NULL;
		_rmAllViewItms();


		PmPrintPaperPage *pcurpaper = NULL;
		int index = 0;
		_pMainFrame->getDoc()->getCurPrintPaperPage(pcurpaper, index);

		this->rmPaperPage(_pPaperPage, index, false);
		_pPaperPage = pcurpaper;
		this->addPaperPage(_pPaperPage, index);		

	}
	else
	{
		//
		this->_updateItems();
	}

	return ;

}

void PhotoEditViewScene::setPaperPage(PmPrintPaperPage *pPaperPage)
{
	_pPaperPage = pPaperPage;
}
	

void PhotoEditViewScene::_updateBackgroundItm()
{
	QString backgroundimg;
	_pPaperPage->getBackGroundImgInEditView(backgroundimg);

	if ( dynamic_cast<QGraphicsPixmapItem *>(_pPaperPageBackGround) )
	{
		_pPaperPageBackGround->setX(_paperpageframe.left());
		_pPaperPageBackGround->setY(_paperpageframe.top());

		QImage img(backgroundimg);
		QImage newsizeimg = img.scaled(_paperpageframe.width(), _paperpageframe.height());

		QPixmap tempPixmap(_paperpageframe.width(), _paperpageframe.height());
		QPainter painter;
		painter.begin(&tempPixmap);
		QRect bgrc = QRect(_paperpageframe.left(),_paperpageframe.top(), _paperpageframe.width(), _paperpageframe.height() );
		bgrc.adjust(-bgrc.left(), -bgrc.top(), -bgrc.left(), -bgrc.top());
		painter.drawPixmap(bgrc,QPixmap::fromImage(newsizeimg));

        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(1);
        pen.setBrush(Qt::lightGray);
		painter.setPen(pen);
		painter.drawRect(bgrc);
		painter.end();

		((QGraphicsPixmapItem *)_pPaperPageBackGround)->setPixmap(tempPixmap);
	}
	else if ( dynamic_cast<QGraphicsRectItem*>(_pPaperPageBackGround) )
	{
		//_pPaperPageBackGround->setX(_paperpageframe.left());
		//_pPaperPageBackGround->setY(_paperpageframe.top());

		((QGraphicsRectItem*)_pPaperPageBackGround)->setRect(
			_paperpageframe.adjusted(0,0,
			0,0));
	}
}

void PhotoEditViewScene::_addFirstPageWnd()
{
	if ( this->_pPaperPage->getPagePos() == FIRST_PAGE )
	{
		_firstPageWnd = new QGraphicsRectItem(NULL);
		QPen pen;
		pen.setColor(Qt::gray);
		pen.setStyle(Qt::DashLine);
		_firstPageWnd->setPen(pen);
		_firstPageWnd->setZValue(4);
		this->addItem(_firstPageWnd);
	}
	else
	{
		this->_firstPageWnd = NULL;
	}
}
void PhotoEditViewScene::_updateFirstPageWnd()
{
	if ( !_firstPageWnd )
	{
		return ;
	}

	QList<PmPhotoPage *> photoPages;
	_pPaperPage->getPhotoPages(photoPages);
	if ( photoPages.size() == 1)
	{
		// rightpage
	}

	PmPhotoPage *pPhotoPage = photoPages.first();
	LayoutBoxPos pagepos;
	pPhotoPage->getPagePosInPaper(pagepos);

	QRectF paperpagerect = _paperpageframe;
	qreal papaerpagexoff = paperpagerect.left() ;
	qreal papaerpageyoff = paperpagerect.top();

	qreal height = paperpagerect.height();
	qreal width = paperpagerect.width();


	LayoutBoxMargin marginInEditView;
	this->_pPaperPage->getMarginInEditView(marginInEditView);

	papaerpagexoff += width * marginInEditView.left;
	papaerpageyoff += height * marginInEditView.top;
	qreal paperwidthinview = width * ( 1-marginInEditView.left-marginInEditView.right-marginInEditView.mid);
	qreal paperheightinview = height * ( 1-marginInEditView.top-marginInEditView.bottom);

	qreal pagex, pagey, pagewidth, pageheight;
	if ( pagepos.x >= 0.5 )
	{
		// right page
		pagex = papaerpagexoff + paperwidthinview*pagepos.x + marginInEditView.mid*width;
	}
	else
	{
		// left page
		pagex = papaerpagexoff + paperwidthinview*(pagepos.x );
	}
	if ( marginInEditView.mid )
	{
		pagewidth = paperwidthinview/2;
	}
	else
	{
		pagewidth = paperwidthinview;
	}
	pagey = papaerpageyoff + height*pagepos.y/*+pagepos.margin.top*height*/;
	pageheight = paperheightinview;

	// adjust page area
	pagex += pagewidth * pagepos.margin.left;
	pagewidth = pagewidth * ( 1-pagepos.margin.left - pagepos.margin.right);
	pagey += pageheight * pagepos.margin.top;
	pageheight = pageheight * ( 1 - pagepos.margin.top - pagepos.margin.bottom);
	QRectF pagerect = QRectF(pagex,pagey,pagewidth, pageheight );


	QRectF firstpagewndrc = pagerect;
	firstpagewndrc.adjust(pagerect.width()*75.0/234,pagerect.height()*108.0/330, 
		-pagerect.width()*48.0/234, -pagerect.height()*133.0/330);
	_firstPageWnd->setRect(firstpagewndrc);


}


void PhotoEditViewScene::_addBackgroundItm()
{
	if ( _pPaperPageBackGround )
	{
		return ;
	}

	QString backgroundimg;
	if (  _pPaperPage->getBackGroundImgInEditView(backgroundimg) && backgroundimg.size() )
	{
		// draw a rect
		_pPaperPageBackGround = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(backgroundimg)));
		QLinearGradient linearGrad(QPointF(0, 0), QPointF(1024, 768));
		//gradient.setStops(
		//linearGrad.setColorAt(0, QColor(qRgb(240,240,240)));
		//linearGrad.setColorAt(1, QColor(qRgb(240,240,200)));
		//_pPaperPageLayout->setBrush(QBrush(linearGrad));
		//_pPaperPageLayout->setBrush(QBrush(QColor(qRgb(240,240,240))));
		//_pPaperPageBackGround->setFlag(QGraphicsItem::ItemIsSelectable, true);

		this->addItem(_pPaperPageBackGround);
		_pPaperPageBackGround->setZValue(0);

		_pPaperPageBackGround->setX(_paperpageframe.left());
		_pPaperPageBackGround->setY(_paperpageframe.top());

		QImage img(backgroundimg);
		QImage newsizeimg = img.scaled(_paperpageframe.width(), _paperpageframe.height());
		((QGraphicsPixmapItem *)_pPaperPageBackGround)->setPixmap(QPixmap::fromImage(newsizeimg));

		QGraphicsDropShadowEffect* gdse =  (QGraphicsDropShadowEffect*)_pPaperPageBackGround->graphicsEffect();
		if( gdse == 0 )
		{
#define NORM_LINE 1
#define SHADOW_OFFSET 2
#define SHADOW_BLUR   10.0
#define MOUSEMV_THRES 5

			gdse = new QGraphicsDropShadowEffect(this);
			gdse->setOffset(SHADOW_OFFSET, SHADOW_OFFSET);
			gdse->setBlurRadius(SHADOW_BLUR);
			_pPaperPageBackGround->setGraphicsEffect(gdse);
		}
	}
	else
	{
		// draw a rect
		_pPaperPageBackGround = new QGraphicsRectItem();

		this->addItem(_pPaperPageBackGround);
		_pPaperPageBackGround->setZValue(0);


		((QGraphicsRectItem*)_pPaperPageBackGround)->setRect(
			_paperpageframe.adjusted(0, 0,
			0, 0));
		QPen pen;
		pen.setColor(Qt::lightGray);
		pen.setStyle(Qt::SolidLine);
		pen.setCapStyle(Qt::RoundCap);
		pen.setJoinStyle(Qt::RoundJoin);

		((QGraphicsRectItem*)_pPaperPageBackGround)->setBrush(QBrush(Qt::white));
		((QGraphicsRectItem*)_pPaperPageBackGround)->setPen(pen);
		QGraphicsDropShadowEffect* gdse =  (QGraphicsDropShadowEffect*)_pPaperPageBackGround->graphicsEffect();
		if( gdse == 0 )
		{
#define EDITVIEW_SHADOW_OFFSET 3.5
#define EDITVIEW_SHADOW_BLUR   10.0

			gdse = new QGraphicsDropShadowEffect(this);
			gdse->setOffset(EDITVIEW_SHADOW_OFFSET, EDITVIEW_SHADOW_OFFSET);
			gdse->setBlurRadius(EDITVIEW_SHADOW_BLUR);
			_pPaperPageBackGround->setGraphicsEffect(gdse);
		}
	}

}

void PhotoEditViewScene::_updateItems()
{
	if ( !this->_pPaperPage )
	{
		return ;
	}

	//
	// update the scene rect 
	//
	QSize size;
	_pPaperPage->getSize(size);
	QRectF rect = sceneRect();

	qreal height, width;
	if ( rect.height() < rect.width()  )
	{
		height = rect.height()-40;
		width = height*size.width()/size.height();
	}
	else
	{
		width = rect.width()-40;
		height = width*size.height()/size.width();
		//width = (rect.height()-40)*size.width()/size.height();
		//height = rect.height()-40;
	}

	if ( width <= 0 ) width = 10;
	if ( height <= 0 ) height = 10;

	_paperpageframe.setLeft((rect.width()- width)/2);
	_paperpageframe.setTop((rect.height()-height)/2);
	_paperpageframe.setWidth(width);
	_paperpageframe.setHeight(height);

	_updateBackgroundItm();
	this->_updateFirstPageWnd();

	PmPhotoPage *pPhotoPage = NULL;
	QList<PmPhotoPage *> photoPages;
	_pPaperPage->getPhotoPages(photoPages);

	QList<PmPhotoPage *>::iterator it;
	for(it=photoPages.begin(); it!=photoPages.end(); it++ )
	{
		//
		this->_updatePhotoPage(*it);
	}
	this->_updateTextBox();

    //this->update();
	this->update();

}

void PhotoEditViewScene::_updatePhotoPage(PmPhotoPage *pPhotoPage)
{
	if ( !pPhotoPage )
	{
		return ;
	}


	LayoutBoxPos pagepos;
	pPhotoPage->getPagePosInPaper(pagepos);

	QRectF paperpagerect = _paperpageframe;
	qreal papaerpagexoff = paperpagerect.left() ;
	qreal papaerpageyoff = paperpagerect.top();

	qreal height = paperpagerect.height();
	qreal width = paperpagerect.width();


	LayoutBoxMargin marginInEditView;
	this->_pPaperPage->getMarginInEditView(marginInEditView);

	papaerpagexoff += width * marginInEditView.left;
	papaerpageyoff += height * marginInEditView.top;
	qreal paperwidthinview = width * ( 1-marginInEditView.left-marginInEditView.right-marginInEditView.mid);
	qreal paperheightinview = height * ( 1-marginInEditView.top-marginInEditView.bottom);

	qreal pagex, pagey, pagewidth, pageheight;
	if ( pagepos.x >= 0.5 )
	{
		// right page
		pagex = papaerpagexoff + paperwidthinview*pagepos.x + marginInEditView.mid*width;
	}
	else
	{
		// left page
		pagex = papaerpagexoff + paperwidthinview*(pagepos.x );
	}
	if ( marginInEditView.mid )
	{
		pagewidth = paperwidthinview/2;
	}
	else
	{
		pagewidth = paperwidthinview;
	}
	pagey = papaerpageyoff + height*pagepos.y/*+pagepos.margin.top*height*/;
	pageheight = paperheightinview;

	// first create a page back ground
	PageBkgrndViewItm *pgbkviewitm = (PageBkgrndViewItm*)pPhotoPage->getPageBkViewItm();
	if ( !pgbkviewitm )
	{
		pgbkviewitm = new PageBkgrndViewItm(this,pPhotoPage);
		QPen pen;
		pen.setWidth(0);
		pen.setColor(QColor(qRgb(255,255,255)));

		pgbkviewitm->setPen(pen);
		QBrush brush(QColor(qRgb(255,255,255)));
		pgbkviewitm->setBrush(brush);

		this->addItem(pgbkviewitm);
		pgbkviewitm->setRect(pagex+2, pagey+2, pagewidth-4, pageheight-4);
		pgbkviewitm->setZValue(1);
		pPhotoPage->setPageBkViewItm(pgbkviewitm);
	}
	else
	{
		pgbkviewitm->setRect(pagex+2, pagey+2, pagewidth-4, pageheight-4);
	}


	// adjust page area
	pagex += pagewidth * pagepos.margin.left;
	pagewidth = pagewidth * ( 1-pagepos.margin.left - pagepos.margin.right);
	pagey += pageheight * pagepos.margin.top;
	pageheight = pageheight * ( 1 - pagepos.margin.top - pagepos.margin.bottom);

	QRectF pagerect = QRectF(pagex,pagey,pagewidth, pageheight );

	QList<PmPageItm *> picitmlst;
	pPhotoPage->getPicItms(picitmlst);

	// create new items
	QList<PmPageItm *>::iterator it;
	for(it=picitmlst.begin(); it!=picitmlst.end(); it++ )
	{
		//

		/*1. Adjust the image size according the scene's size*/
		/*2. Set the position according the scene's size*/
		//start = ::GetTickCount();

		PmPageItm *pPicItm = *it;
		LayoutBoxPos itmPos;
		pPicItm->getRectInPage(itmPos);

		// first add photo page offset
		qreal xoff,yoff;
		xoff = pagerect.left() + pagerect.width()* itmPos.x;
		yoff = pagerect.top() + pagerect.height()*itmPos.y;

		qreal itmwidth, itmheight;
		itmwidth = itmPos.width*pagerect.width();
		itmheight = itmPos.height * pagerect.height();

		PageViewItm* item = (PageViewItm* )pPicItm->getPageViewItm();

		if ( pPicItm->getPhotoItmType() == PmPageItm::CALENDAR_ITM )
		{
			CalViewItm *calitm = (CalViewItm*)item;
		}
		else
		{
			PhotoViewItm* item1 = (PhotoViewItm* )item;
			if ( !item1 )
			{
				continue;
			}
			QString imgpath;
			pPicItm->getContent(imgpath);
			if ( imgpath.length())
			{
				QPixmap savedpixmap;
				QPixmap *pixmap = pPicItm->getPixmap();
				if ( pixmap )
				{
					savedpixmap = *pixmap;
				}

				item1->setImg(imgpath, savedpixmap);
				pPicItm->setPixmap(savedpixmap);
			}
			else
			{
				QPixmap savedpixmap;
				item1->setImg(imgpath, savedpixmap);
				pPicItm->setPixmap(savedpixmap);
			}
		}

		QMargins margin = QMargins(itmwidth*itmPos.margin.left,
			itmheight*itmPos.margin.top,
			itmwidth*itmPos.margin.right,
			itmheight*itmPos.margin.bottom);

		item->setItemMargin(margin);
		item->setItemSize(QSize((int)itmwidth,(int)itmheight));
		item->setPos(int(xoff),(int)(yoff));

		item->resize();
	}
}

void PhotoEditViewScene::_updateTextBox()
{
	QList<PmTextItm *> txtitmlst;
	_pPaperPage->getTextbox(txtitmlst);
	if ( !txtitmlst.size() )
	{
		return ;
	}

	QRectF scrc = this->sceneRect();
	LayoutBoxMargin marginInEditView;
	this->_pPaperPage->getMarginInEditView(marginInEditView);


	QList<PmTextItm *>::iterator it;
	for ( it=txtitmlst.begin(); it!=txtitmlst.end(); it++ )
	{
		PmTextItm *pTextItm = *it;

		LayoutBoxPos itmpos;
		pTextItm->getRectInPrintPage(itmpos);

		QRectF paperpagerect = _paperpageframe;
		qreal papaerpagexoff = paperpagerect.left();
		qreal papaerpageyoff = paperpagerect.top();
		qreal height = paperpagerect.height();
		qreal width = paperpagerect.width();

		papaerpagexoff += width*marginInEditView.left;
		papaerpageyoff += height * marginInEditView.top;
		width = width * ( 1-marginInEditView.left-marginInEditView.right - marginInEditView.mid);
		height = height * ( 1-marginInEditView.top-marginInEditView.bottom);

		QRectF textrect;
		if ( itmpos.x < 0.5 )
		{
			// left page
			textrect = QRectF(papaerpagexoff + width*itmpos.x, 
				papaerpageyoff + height*itmpos.y, 
				itmpos.width,
				itmpos.height);

		}
		else
		{
			// right page
			textrect = QRectF(papaerpagexoff + width*itmpos.x +  marginInEditView.mid*_paperpageframe.width(), 
				papaerpageyoff + height*itmpos.y, 
				itmpos.width,
				itmpos.height);
		}
		TextViewItem* txtviewitm = (TextViewItem*)pTextItm->getViewItm();
		txtviewitm->setFontViewRatio(_paperpageframe.height()/PRINT_PREFERED_HEIGHT);
		txtviewitm->setPos(int(textrect.left()),(int)(textrect.top()));
		txtviewitm->setWidthHeight(textrect.width(), textrect.height());
	}

}


void PhotoEditViewScene::_loadTextBoxs()
{
	QList<PmTextItm *> txtitmlst;
	_pPaperPage->getTextbox(txtitmlst);
	if ( !txtitmlst.size() )
	{
		return ;
	}


	QList<PmTextItm *>::iterator it;
	for ( it=txtitmlst.begin(); it!=txtitmlst.end(); it++ )
	{
		PmTextItm *pTxtItm = *it;
		TextViewItem* txtviewitm = NULL;

		txtviewitm = (TextViewItem*) pTxtItm->getViewItm();
		
		if ( txtviewitm)
		{
			//this->removeItem(txtviewitm); // this may be removed when reload paper
			delete txtviewitm;
			txtviewitm = NULL;
			pTxtItm->setViewItm(txtviewitm);
		}

                txtviewitm = new TextViewItem(false, QPointF(0,0),NULL);
		txtviewitm->setTextItm(pTxtItm);
		QString cnt;
		//pTextItm->setContent("<h2><i>Text Box</i><font color=red> Item!</font></h2>");
		if ( pTxtItm )
		{
			pTxtItm->getContent(cnt);
		}
		pTxtItm->getContent(cnt);
		txtviewitm->setText(cnt);
		txtviewitm->setShadow(pTxtItm->isShadowEnable());
		this->addItem(txtviewitm);
		//txtviewitm->setPos(int(textrect.left()),(int)(textrect.top()));
		txtviewitm->setZValue(3);
		pTxtItm->setViewItm(txtviewitm);
	}
	_updateTextBox();
}



void PhotoEditViewScene::_syncCalCfg(const CalendarInfo &ci, const WeekdaysInfo &wi, const MonthYearInfo &mi, CALENDAR_CFG &calcfg)
{
    /*Font part*/
	calcfg.calcfg.fontcfg.name = ci.font.family();
	calcfg.calcfg.fontcfg.color = ci.color;

	calcfg.calcfg.fontcfg.align = 0;
	if ( HorLeftAlig == ci.hor  )
	{
		calcfg.calcfg.fontcfg.align |= Qt::AlignLeft;
	}
	else if ( HorCenterAlig == ci.hor )
	{
		calcfg.calcfg.fontcfg.align |= Qt::AlignHCenter;
	}
	else
	{
		calcfg.calcfg.fontcfg.align |= Qt::AlignRight;
	}

	if ( VerTopAlig == ci.ver  )
	{
		calcfg.calcfg.fontcfg.align |= Qt::AlignTop;
	}
	else if ( VerCenterAlig == ci.ver )
	{
		calcfg.calcfg.fontcfg.align |= Qt::AlignVCenter;
	}
	else
	{
		calcfg.calcfg.fontcfg.align |= Qt::AlignBottom;
	}
	calcfg.calcfg.fontcfg.heightInCell = ci.height_in_cell * 1.0 / 100;
        calcfg.calcfg.fontcfg.bold = ci.font.bold();
        calcfg.calcfg.fontcfg.iatic = ci.font.italic();
        calcfg.calcfg.fontcfg.underLine = ci.font.underline();

    /*Colors part*/
	calcfg.calcfg.bgcolor = ci.bg_color;
	calcfg.calcfg.rowcolor = ci.row_color;
	calcfg.calcfg.cellcolor = ci.cell_color;
	for ( int i=0; i<7; i++ )
	{
		calcfg.calcfg.wdcolors.push_back(ci.everyday_color[i]);
	}

	// space
	calcfg.calcfg.linespace.left = ci.line_space[0];
	calcfg.calcfg.linespace.top = ci.line_space[1];
	calcfg.calcfg.linespace.right = ci.line_space[2];
	calcfg.calcfg.linespace.bottom = ci.line_space[3];

	calcfg.calcfg.linespace.leftpad = ci.line_padding[0];
	calcfg.calcfg.linespace.toppad = ci.line_padding[1];
	calcfg.calcfg.linespace.rightpad = ci.line_padding[2];
	calcfg.calcfg.linespace.bottompad = ci.line_padding[3];


	calcfg.calcfg.cellspace.left = ci.cell_space[0];
	calcfg.calcfg.cellspace.top = ci.cell_space[1];
	calcfg.calcfg.cellspace.right = ci.cell_space[2];
	calcfg.calcfg.cellspace.bottom = ci.cell_space[3];

	calcfg.calcfg.cellspace.leftpad = ci.cell_padding[0];
	calcfg.calcfg.cellspace.toppad = ci.cell_padding[1];
	calcfg.calcfg.cellspace.rightpad = ci.cell_padding[2];
	calcfg.calcfg.cellspace.bottompad = ci.cell_padding[3];


	// week days
	calcfg.wdcfg.showwds = wi.show;
	calcfg.wdcfg.regionsize = wi.size_of_region;

	// wd font
	calcfg.wdcfg.fontcfg.name = wi.font.family();
	calcfg.wdcfg.fontcfg.color = wi.color;

	calcfg.wdcfg.fontcfg.align = 0;
	if ( HorLeftAlig == wi.hor  )
	{
		calcfg.wdcfg.fontcfg.align |= Qt::AlignLeft;
	}
	else if ( HorCenterAlig == wi.hor )
	{
		calcfg.wdcfg.fontcfg.align |= Qt::AlignHCenter;
	}
	else
	{
		calcfg.wdcfg.fontcfg.align |= Qt::AlignRight;
	}

	if ( VerTopAlig == wi.ver  )
	{
		calcfg.wdcfg.fontcfg.align |= Qt::AlignTop;
	}
	else if ( VerCenterAlig == wi.ver )
	{
		calcfg.wdcfg.fontcfg.align |= Qt::AlignVCenter;
	}
	else
	{
		calcfg.wdcfg.fontcfg.align |= Qt::AlignBottom;
	}
	calcfg.wdcfg.fontcfg.heightInCell = wi.height_in_cell * 1.0 / 100;
        calcfg.wdcfg.fontcfg.bold = wi.font.bold();
        calcfg.wdcfg.fontcfg.iatic = wi.font.italic();
        calcfg.wdcfg.fontcfg.underLine = wi.font.underline();
	
	// wd color
	calcfg.wdcfg.rowcolor = wi.row_color;
	calcfg.wdcfg.cellcolor = wi.cell_color;

	calcfg.wdcfg.linespace.left = wi.line_space[0];
	calcfg.wdcfg.linespace.top = wi.line_space[1];
	calcfg.wdcfg.linespace.right = wi.line_space[2];
	calcfg.wdcfg.linespace.bottom = wi.line_space[3];

	calcfg.wdcfg.linespace.leftpad = wi.line_padding[0];
	calcfg.wdcfg.linespace.toppad = wi.line_padding[1];
	calcfg.wdcfg.linespace.rightpad = wi.line_padding[2];
	calcfg.wdcfg.linespace.bottompad = wi.line_padding[3];


	calcfg.wdcfg.cellspace.left = wi.cell_space[0];
	calcfg.wdcfg.cellspace.top = wi.cell_space[1];
	calcfg.wdcfg.cellspace.right = wi.cell_space[2];
	calcfg.wdcfg.cellspace.bottom = wi.cell_space[3];

	calcfg.wdcfg.cellspace.leftpad = wi.cell_padding[0];
	calcfg.wdcfg.cellspace.toppad = wi.cell_padding[1];
	calcfg.wdcfg.cellspace.rightpad = wi.cell_padding[2];
	calcfg.wdcfg.cellspace.bottompad = wi.cell_padding[3];

	// month year
	calcfg.monthyearcfg.showmonthyear = mi.show;
	calcfg.monthyearcfg.regionsize = mi.size_of_region ;
	calcfg.monthyearcfg.showonbottom = mi.bottom;
	calcfg.monthyearcfg.showmonthyeardouble = mi.doublespace;

    /*month year Font part*/
	calcfg.monthyearcfg.fontcfg.name = mi.font.family();
	calcfg.monthyearcfg.fontcfg.color = mi.color;

	calcfg.monthyearcfg.fontcfg.align = 0;
	if ( HorLeftAlig == mi.hor  )
	{
		calcfg.monthyearcfg.fontcfg.align |= Qt::AlignLeft;
	}
	else if ( HorCenterAlig == mi.hor )
	{
		calcfg.monthyearcfg.fontcfg.align |= Qt::AlignHCenter;
	}
	else
	{
		calcfg.monthyearcfg.fontcfg.align |= Qt::AlignRight;
	}

	if ( VerTopAlig == mi.ver  )
	{
		calcfg.monthyearcfg.fontcfg.align |= Qt::AlignTop;
	}
	else if ( VerCenterAlig == mi.ver )
	{
		calcfg.monthyearcfg.fontcfg.align |= Qt::AlignVCenter;
	}
	else
	{
		calcfg.monthyearcfg.fontcfg.align |= Qt::AlignBottom;
	}
	calcfg.monthyearcfg.fontcfg.heightInCell = mi.height_in_cell * 1.0 / 100;
        calcfg.monthyearcfg.fontcfg.bold = mi.font.bold();
        calcfg.monthyearcfg.fontcfg.iatic = mi.font.italic();
        calcfg.monthyearcfg.fontcfg.underLine = mi.font.underline();

	
	// wd color
	calcfg.monthyearcfg.rowcolor = mi.row_color;

	calcfg.monthyearcfg.linespace.left = mi.line_space[0];
	calcfg.monthyearcfg.linespace.top = mi.line_space[1];
	calcfg.monthyearcfg.linespace.right = mi.line_space[2];
	calcfg.monthyearcfg.linespace.bottom = mi.line_space[3];

	calcfg.monthyearcfg.linespace.leftpad = mi.line_padding[0];
	calcfg.monthyearcfg.linespace.toppad = mi.line_padding[1];
	calcfg.monthyearcfg.linespace.rightpad = mi.line_padding[2];
	calcfg.monthyearcfg.linespace.bottompad = mi.line_padding[3];

}

bool _isPanoramaLayout(PHOTO_LAYOUT layout)
{
	switch(layout)
	{
	case PP_LAYOUT_FULLSIZE_PANOR:
	case PP_LAYOUT_BORDER_PANOR:
	case PP_LAYOUT_PB8X5_FULLSIZE_PANOR:
	case PP_LAYOUT_PB8X5_TRADITION_PANOR:
	case PP_LAYOUT_PB8X5_HORIZON_PANOR:
	case PP_LAYOUT_PB8X5_VERTICON_PANOR:
		return true;
		break;
	default:
		return false;
	}

	return false;
}

void PhotoEditViewScene::_addPhotoPage(PmPhotoPage *pPhotoPage)
{
	if ( !pPhotoPage )
	{
		return ;
	}


	QList<PmPageItm *> picitmlst;
	pPhotoPage->getPicItms(picitmlst);


	// create new items
	QList<PmPageItm *>::iterator it;
	for(it=picitmlst.begin(); it!=picitmlst.end(); it++ )
	{
		//

		/*1. Adjust the image size according the scene's size*/
		/*2. Set the position according the scene's size*/
		PmPageItm *pPicItm = *it;
		PageViewItm *viewitm = NULL;

		QMargins margin;

		if ( pPicItm->getPhotoItmType() == PmPageItm::CALENDAR_ITM )
		{
			//
			PROJ_PROPS proj;
			this->_pMainFrame->getDoc()->getProjProps(proj);

			CalViewItm *calviewitm = CalViewItmFactory::getViewItm(proj.lytype, QPointF(0,0),
						QSize((int)0,(int)0),margin,this);
			viewitm = calviewitm;


			CALENDAR_CFG calcfg;
			pPicItm->getCalProps(calcfg.calcfg);
			if ( !calcfg.calcfg.fontcfg.name.length()  )
			{
				CalendarInfo ci;
				WeekdaysInfo wi;
				MonthYearInfo mi;

				calviewitm->getInfo(&ci, &wi, &mi);
				_syncCalCfg(ci, wi, mi, calcfg);
				pPicItm->setCalProps(calcfg.calcfg);
				pPicItm->setWdsProps(calcfg.wdcfg);
				pPicItm->setMonthYearProps(calcfg.monthyearcfg);
			}
		}
		else
		{
			if (_isPanoramaLayout(pPhotoPage->getLayout() ) )
			{
				viewitm = new PhotoPanoViewItm(QPointF(0,0),
					QSize((int)0,(int)0),margin,
					pPhotoPage->isLeft()?PhotoPanoViewItm::Left_Pano:PhotoPanoViewItm::Right_Pano,
					this);
			}
			else
			{
				viewitm = new PhotoViewItm(QPointF(0,0),
					QSize((int)0,(int)0),margin,this);
			}
			


		}
		viewitm->setPmPageItm(pPicItm);
		viewitm->reload();

		PROJ_PROPS proj;
		this->_pMainFrame->getDoc()->getProjProps(proj);
		bool shadow =proj.shadow;
		viewitm->setShadow(shadow);
		this->addItem(viewitm);
		viewitm->setZValue(2);
		pPicItm->setPageViewItm(viewitm);

	}
	this->_updatePhotoPage(pPhotoPage);

	// calulate the image off
	for(it=picitmlst.begin(); it!=picitmlst.end(); it++ )
	{
		//

		/*1. Adjust the image size according the scene's size*/
		/*2. Set the position according the scene's size*/
		PmPageItm *pPicItm = *it;
		PageViewItm *viewitm = NULL;

		if ( pPicItm->getPhotoItmType() == PmPageItm::CALENDAR_ITM )
		{
			//
			continue;
		}
		else
		{
			PhotoViewItm *photoviewitm = (PhotoViewItm *)pPicItm->getPageViewItm();
			if ( photoviewitm )
			{
				//photoviewitm->recalImgOff();
			}

		}

	}


}


void PhotoEditViewScene::reloadPhotoPage(const PmPhotoPage *pPhotoPage)
{
	//
	// first remove all items below this paperpage
	//
	QList<QGraphicsItem *>  itmlst;
	itmlst = items();
	PmPageItm *pageitm = NULL;

	QList<QGraphicsItem *>::iterator it;
	for(it=itmlst.begin(); it!=itmlst.end(); it++ )
	{
		//
		pageitm = NULL;
		PageViewItm *viewitm = dynamic_cast<PageViewItm *>(*it);
		if ( viewitm )
		{
			pageitm  = viewitm->getPmPageItm();
		}
		if ( pageitm )
		{
			PmPhotoPage *checkphotopage = pageitm->getPage();
			if ( !checkphotopage )
			{
				continue;
			}

			if ( checkphotopage != pPhotoPage )
			{
				continue;
			}

			// remove this item
			removeItem(*it);

			continue;
		}
	}


	this->_updatePhotoPage((PmPhotoPage*)pPhotoPage);
	/*
	if ( updatescene )
	{
		this->update();
	}
	*/
	this->updateScene();
}

bool PhotoEditViewScene::addPaperPage(PmPrintPaperPage *pPaperPage, int index, bool updatescene)
{

	//
	_pPaperPage = (PmPrintPaperPage *)pPaperPage;


	//
	// update the scene rect 
	//
	QSize size;
	_pPaperPage->getSize(size);
	QRectF rect = sceneRect();

	qreal height, width;
	width = (rect.height()-40)*size.width()/size.height();
	height = rect.height()-40;

	if ( width <= 0 ) width = 10;
	if ( height <= 0 ) height = 10;

	_paperpageframe.setLeft((rect.width()- width)/2);
	_paperpageframe.setTop((rect.height()-height)/2);
	_paperpageframe.setWidth(width);
	_paperpageframe.setHeight(height);





	this->_addBackgroundItm();
	if ( _pPaperPageBackGround )
		_pPaperPageBackGround->update();

	_addFirstPageWnd();
	_updateFirstPageWnd();

	PmPhotoPage *pPhotoPage = NULL;
	QList<PmPhotoPage *> photoPages;
	_pPaperPage->getPhotoPages(photoPages);

	QList<PmPhotoPage *>::iterator it2;
	for(it2=photoPages.begin(); it2!=photoPages.end(); it2++ )
	{
		//
		this->_addPhotoPage(*it2);
	}
	this->_loadTextBoxs();

	// update scenen, all items need to be updated will be updated
	if ( updatescene )
	{
		this->update();
	}

	return true;

}
bool PhotoEditViewScene::rmPaperPage(const PmPrintPaperPage *pPaperPage, int &index, bool updatescene)
{
	//
	// first remove all items below this paperpage
	//
	this->clear();
	QList<PmPhotoPage *> photopages;
	_pPaperPage->getPhotoPages(photopages);
	QList<PmPhotoPage *>::iterator it;
	for ( it=photopages.begin(); it!=photopages.end(); it++ )
	{
		// clear pagebckground view item
		(*it)->setPageBkViewItm(NULL);
	}

	_pPaperPageBackGround = NULL;
	_pPaperPage = NULL;

	_selctedtxtviewitm = NULL;
	_selectedphotoitm = NULL;

	if ( updatescene )
	{
		this->update();
	}
	return true;
}

void PhotoEditViewScene::reloadPaperPage(const PmPrintPaperPage *pPaperPage, bool updatescene)
{
	int index = 0;
	_selctedtxtviewitm = NULL;
	_selectedphotoitm = NULL;

	this->rmPaperPage(pPaperPage, index, false);
	this->addPaperPage((PmPrintPaperPage*)pPaperPage,index,  false);


	// update scenen, all items need to be updated will be updated
	this->update();

}



void PhotoEditViewScene::setBgColor(const QColor &color)
{
	PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm*>(_selectedphotoitm);
	if ( !photoviewitm )
	{
		return ;
	}

	PmPageItm *selection = photoviewitm->getPmPageItm();
	selection->setBgColor(color);
	photoviewitm->updatePanoramaPair();

	photoviewitm->reload();

	PhotoPreviewItm *previewitm = (PhotoPreviewItm *)selection->getPreviewPageViewItm();
	if ( previewitm )
	{
		previewitm->reload();
	}

}

void PhotoEditViewScene::rotateSelectionleft()
{
	PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm*>(_selectedphotoitm);
	if ( !photoviewitm )
	{
		return ;
	}

	photoviewitm->rotate(-90);
	PmPageItm *selection = photoviewitm->getPmPageItm();
	selection->clearImgLeftTop();
	
	PmPrintPaperPage *paper = photoviewitm->getPmPageItm()->getPage()->getPaperPage();
	this->reloadPaperPage(paper, true);
	PmPhotoView *pPreviewView = (PmPhotoView*)(paper->getPreviewView());
	if ( pPreviewView )
	{
		pPreviewView->reloadPaperPage(paper);
	}


	// restore selection item
	photoviewitm = (PhotoViewItm *)selection->getPageViewItm();
	this->selectItm(photoviewitm, NULL);
	
	
}

void PhotoEditViewScene::rotateSelectionright()
{
	PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm*>(_selectedphotoitm);
	if ( !photoviewitm )
	{
		return ;
	}
	photoviewitm->rotate(90);
	PmPageItm *selection = photoviewitm->getPmPageItm();
	selection->clearImgLeftTop();

	PmPrintPaperPage *paper = photoviewitm->getPmPageItm()->getPage()->getPaperPage();
	this->reloadPaperPage(paper, true);

	PmPhotoView *pPreviewView = (PmPhotoView*)(paper->getPreviewView());
	if ( pPreviewView )
	{
		pPreviewView->reloadPaperPage(paper);
	}

	// restore selection item
	photoviewitm = (PhotoViewItm *)selection->getPageViewItm();
	this->selectItm(photoviewitm, NULL);
	
	// save the img
	//this->update();
}

void PhotoEditViewScene::setSelectionHSL()
{
    PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm*>(_selectedphotoitm);
    if ( photoviewitm )
    {
            photoviewitm->setHSL();
            update();
    }
}

void PhotoEditViewScene::setSelectionBWC()
{
    PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm*>(_selectedphotoitm);
    if ( photoviewitm )
    {
            photoviewitm->setBWC();
            update();
    }
}


void PhotoEditViewScene::cutSelection()
{
	PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm*>(_selectedphotoitm);
	if ( photoviewitm )
	{
		// photo item
		PmPageItm *pageitm = photoviewitm->getPmPageItm();
		QString path;
		QColor color;
		pageitm->getContent(path);
		pageitm->getBgColor(color);

		// save the information in clipboard
		QClipboard *cb = QApplication::clipboard();
		QMimeData *mimedata =  new QMimeData();
		mimedata->setData("srcapp","photomaker");
		mimedata->setData("type","img");
		mimedata->setData("imgpath",path.toAscii());
		QString colorval = QString("%1").arg(color.rgba());
		mimedata->setData("imgcolor", colorval.toAscii());


		qreal scale;
		int angel = 0;
		pageitm->getZoom(scale);
		pageitm->getRotate(angel);
		QString value;
		value = QString("%1").arg(scale);
		mimedata->setData("imgscale",value.toAscii());
		value = QString("%1").arg(angel);
		mimedata->setData("imgrotate",value.toAscii());

		QPointF imglefttop;
		pageitm->getImgLeftTop(imglefttop);
		value = QString("%1").arg(imglefttop.rx());
		mimedata->setData("imgleft",value.toAscii());
		value = QString("%1").arg(imglefttop.ry());
		mimedata->setData("imgtop",value.toAscii());


		cb->setMimeData(mimedata);
		


		pageitm->setContent("");
		pageitm->setBgColor(Qt::white);
		photoviewitm->reload();
		update();
		return ;
	}

	if ( _selctedtxtviewitm )
	{
		//
		PmTextItm *ptxtitm = _selctedtxtviewitm->getTextItm();

		// save the information in clipboard
		QString cnt;
		int align;
		qreal scale;
		int angel;

		ptxtitm->getContent(cnt);
		align = ptxtitm->getAlign();
		scale = ptxtitm->getScale();
		angel = ptxtitm->getRotate();

		// save the information in clipboard
		QClipboard *cb = QApplication::clipboard();
		QMimeData *mimedata =  new QMimeData();
		mimedata->setData("srcapp","photomaker");
		mimedata->setData("type" , "text");
		mimedata->setData("textcnt" ,cnt.toAscii());

		QString value;
		value = QString("%1").arg(scale);
		mimedata->setData("textscale",value.toAscii());
		value = QString("%1").arg(angel);
		mimedata->setData("textrotate",  value.toAscii());
		value = QString("%1").arg(align);
		mimedata->setData("textalign",value.toAscii());

		LayoutBoxPos rect;
		ptxtitm->getRectInPrintPage(rect);
		value = QString("%1").arg(rect.x);
		mimedata->setData("textrcx", value.toAscii());
		value = QString("%1").arg(rect.y);
		mimedata->setData("textrcy",value.toAscii());
		value = QString("%1").arg(rect.width);
		mimedata->setData("textrcwidth" ,value.toAscii());
		value = QString("%1").arg(rect.height);
		mimedata->setData("textrcheight",value.toAscii());


		cb->setMimeData(mimedata);


		PmPrintPaperPage *printpaper = ptxtitm->getPrintPage();
		printpaper->delTextbox(ptxtitm);
		this->removeItem(_selctedtxtviewitm);
		delete _selctedtxtviewitm;
		_selctedtxtviewitm = NULL;

		update();
		return ;
	}
}

void PhotoEditViewScene::copySelection()
{
	PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm*>(_selectedphotoitm);
	if ( photoviewitm )
	{
		// photo item
		PmPageItm *pageitm = photoviewitm->getPmPageItm();
		QString path;
		QColor color;
		pageitm->getContent(path);
		pageitm->getBgColor(color);

		// save the information in clipboard
		QClipboard *cb = QApplication::clipboard();
		QMimeData *mimedata =  new QMimeData();
		mimedata->setData("srcapp","photomaker");
		mimedata->setData("type","img");
		mimedata->setData("imgpath",path.toAscii());
		QString colorval = QString("%1").arg(color.rgba());
		mimedata->setData("imgcolor",colorval.toAscii());


		qreal scale;
		int angel = 0;
		pageitm->getZoom(scale);
		pageitm->getRotate(angel);
		QString value;
		value = QString("%1").arg(scale);
		mimedata->setData("imgscale",value.toAscii());
		value = QString("%1").arg(angel);
		mimedata->setData("imgrotate",value.toAscii());

		QPointF imglefttop;
		pageitm->getImgLeftTop(imglefttop);
		value = QString("%1").arg(imglefttop.rx());
		mimedata->setData("imgleft",value.toAscii());
		value = QString("%1").arg(imglefttop.ry());
		mimedata->setData("imgtop",value.toAscii());


		cb->setMimeData(mimedata);
		
 		return ;
	}

	if ( _selctedtxtviewitm )
	{
		//
		PmTextItm *ptxtitm = _selctedtxtviewitm->getTextItm();

		// save the information in clipboard
		QString cnt;
		int align;
		qreal scale;
		int angel;

		ptxtitm->getContent(cnt);
		align = ptxtitm->getAlign();
		scale = ptxtitm->getScale();
		angel = ptxtitm->getRotate();

		// save the information in clipboard
		QClipboard *cb = QApplication::clipboard();
		QMimeData *mimedata =  new QMimeData();
		mimedata->setData("srcapp","photomaker");
		mimedata->setData("type" , "text");
		mimedata->setData("textcnt" ,cnt.toAscii());

		QString value;
		value = QString("%1").arg(scale);
		mimedata->setData("textscale",value.toAscii());
		value = QString("%1").arg(angel);
		mimedata->setData("textrotate",  value.toAscii());
		value = QString("%1").arg(align);
		mimedata->setData("textalign",value.toAscii());

		LayoutBoxPos rect;
		ptxtitm->getRectInPrintPage(rect);
		value = QString("%1").arg(rect.x);
		mimedata->setData("textrcx", value.toAscii());
		value = QString("%1").arg(rect.y);
		mimedata->setData("textrcy",value.toAscii());
		value = QString("%1").arg(rect.width);
		mimedata->setData("textrcwidth" ,value.toAscii());
		value = QString("%1").arg(rect.height);
		mimedata->setData("textrcheight",value.toAscii());


		cb->setMimeData(mimedata);

 		return ;
	}
}

void PhotoEditViewScene::pasteSelection()
{
	QClipboard *cb = QApplication::clipboard();
	const QMimeData *mimedata =  cb->mimeData();

	if ( mimedata->data("srcapp") != "photomaker" )
	{
		return ;
	}
	if ( mimedata->data("type") == "text" )
	{
		//PmTextItm *ptxtitm = _selctedtxtviewitm->getTextItm();

		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;
		undoactitm.saved.pageedit.peditpaper =_pPaperPage;
		undoactitm.saved.pageedit.psavepaper = getMainFrame()->getDoc()->createNewPaper();
		if ( undoactitm.saved.pageedit.psavepaper )
		{
			undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
			undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
			//undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
			PmUndoActionStack::getInst().pushAction(undoactitm);
			getMainFrame()->updateUIStatus();
		}
		// save the information in clipboard
		QString cnt;
		int align;
		qreal scale;
		int angel;


		// save the information in clipboard

		cnt = mimedata->data("textcnt");

		QString value;
		value = mimedata->data("textscale");
		scale = value.toFloat();
		value = mimedata->data("textrotate");
		angel = value.toInt();
		value = mimedata->data("textalign");
		align = value.toInt();

		LayoutBoxPos rect;
		//ptxtitm->getRectInPrintPage(rect);
		value = mimedata->data("textrcx");
		rect.x = value.toFloat();
		value = mimedata->data("textrcy");
		rect.y = value.toFloat();
		value = mimedata->data("textrcwidth");
		rect.width = value.toFloat();
		value = mimedata->data("textrcheight");
		rect.height = value.toFloat();

		PmTextItm *ptxtitm = new PmTextItm(this);
		ptxtitm->setContent(cnt);
		ptxtitm->setAlign(align);
		ptxtitm->setScale(scale);
		ptxtitm->setRotate(angel);
		ptxtitm->setRectInPrintPage(rect);

		this->_pPaperPage->addTextbox(ptxtitm);

		this->_addTextBox(ptxtitm);

		update();
		//_updateTextBox();

		return ;

	}
	else if ( mimedata->data("type") == "img"   )
	{
		PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm*>(_selectedphotoitm);
		if ( !photoviewitm )
		{
			return ;
		}
		QString path;
		QString colorval;
		path = mimedata->data("imgpath");
		colorval = mimedata->data("imgcolor");
		QColor color;
		ulong val = colorval.toULong();
		color.setRgba(QRgb(val));

		QString value = mimedata->data("imgscale");
		qreal scale = value.toFloat();
		
		value = mimedata->data("imgrotate");
		int angel = value.toInt();

		QPointF imglefttop;
		value = mimedata->data("imgleft");
		imglefttop.setX(value.toFloat());
		value = mimedata->data("imgtop");
		imglefttop.setY(value.toFloat());


		PmPageItm *pageitm = photoviewitm->getPmPageItm();

		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;
		undoactitm.saved.pageedit.peditpaper = pageitm->getPage()->getPaperPage();
		undoactitm.saved.pageedit.psavepaper = getMainFrame()->getDoc()->createNewPaper();
		if ( undoactitm.saved.pageedit.psavepaper )
		{
			undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
			undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
			//undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
			PmUndoActionStack::getInst().pushAction(undoactitm);
			getMainFrame()->updateUIStatus();
		}


		pageitm->setContent(path);
		pageitm->setBgColor(color);
		pageitm->setRotate(angel);
		pageitm->setZoom(scale);
		pageitm->setImgLeftTop(imglefttop);

		photoviewitm->reload();
		PhotoPreviewItm *previewitm = (PhotoPreviewItm *)pageitm->getPreviewPageViewItm();
		if ( previewitm )
		{
			previewitm->reload();
		}
		update();
		return ;
	}
}

void PhotoEditViewScene::setSelectionLCIG()
{
    PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm*>(_selectedphotoitm);
    if ( photoviewitm )
    {
            photoviewitm->setLCIG();
            update();
    }
}

void PhotoEditViewScene::setSelectionRE()
{
    PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm*>(_selectedphotoitm);
    if ( photoviewitm )
    {
            photoviewitm->setRE();
            update();
    }
}


void PhotoEditViewScene::zoomSelection(qreal scale)
{
	PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm*>(_selectedphotoitm);
	if ( photoviewitm )
	{
		photoviewitm->scale(scale);
		update();
	}
}

void PhotoEditViewScene::delSelction()
{
	PhotoViewItm *photoviewitm = dynamic_cast<PhotoViewItm*>(_selectedphotoitm);
	if ( photoviewitm )
	{
		PmPageItm *pageitm = photoviewitm->getPmPageItm();

		// photo item
		pageitm->setContent("");
		pageitm->setBgColor(Qt::white);
		photoviewitm->reload();
		PhotoViewItm *previewitm = (PhotoViewItm *)pageitm->getPreviewPageViewItm();
		if ( previewitm )
		{
			previewitm->reload();
		}
		update();
		return ;
	}

	if ( _selctedtxtviewitm )
	{
		//
		PmTextItm *ptxtitm = _selctedtxtviewitm->getTextItm();
		PmPrintPaperPage *printpaper = ptxtitm->getPrintPage();
		printpaper->delTextbox(ptxtitm);
		this->removeItem(_selctedtxtviewitm);
		delete _selctedtxtviewitm;
		_selctedtxtviewitm = NULL;

		update();
		return ;
	}

}

/*
void PhotoEditViewScene::_updateCalCfg2Itm(const CALENDAR_CFG &calcfg, PmPageItm &calitm, bool &updated)
{
	updated = false;

	calitm.setCalProps(calcfg.calcfg);
	calitm.setWdsProps(calcfg.wdcfg);
	calitm.setMonthYearProps(calcfg.monthyearcfg);
	

	// later add check different logic

	updated = true;
}
*/

bool PhotoEditViewScene::getSelCalCfg(CALENDAR_CFG &calcfg)
{
	CalViewItm *calviewitm = dynamic_cast<CalViewItm*>(_selectedphotoitm);
	if ( !calviewitm )
	{
		return false;
	}
	
	PmPageItm *calitm = calviewitm->getPmPageItm();
	if ( !calitm )
	{
		return false;
	}
	calitm->getCalProps(calcfg.calcfg);
	calitm->getWdsProps(calcfg.wdcfg);
	calitm->getMonthYearProps(calcfg.monthyearcfg);


	return true;
}
PmPageItm *_getCalItm(PmPrintPaperPage* paper)
{
	QList<PmPhotoPage *> photopages;
	paper->getPhotoPages(photopages);
	if ( photopages.size() != 1 )
	{
		return NULL;
	}
	PmPhotoPage *photopage = photopages.first();
	if ( !photopage )
	{
		return NULL;
	}
	QList<PmPageItm *> picitmlst;
	photopage->getPicItms(picitmlst);
	QList<PmPageItm *>::iterator pageitmit;
	for ( pageitmit=picitmlst.begin(); pageitmit!=picitmlst.end(); pageitmit++ )
	{
		PmPageItm *pageitm = *pageitmit;
		if ( PmPageItm::CALENDAR_ITM == pageitm->getPhotoItmType() )
		{
			break;
		}
	}
	if ( pageitmit == picitmlst.end() )
	{
		return NULL;
	}

	PmPageItm *calitm = *pageitmit;
	return calitm;
}

void PhotoEditViewScene::updateSelCalCfg(const CALENDAR_CFG &calcfg)
{
	if ( calcfg.forall )
	{
		QList<PmPrintPaperPage*> paperpages;
		_pMainFrame->getDoc()->getPrintPaperPages(paperpages);
		QList<PmPrintPaperPage*>::iterator it;

	
		// update all
		// update selection
		for ( it=paperpages.begin(); it!=paperpages.end(); it++ )
		{
			PmPrintPaperPage *paper = *it;
			QList<PmPhotoPage *> photopages;
			paper->getPhotoPages(photopages);
			if ( photopages.size() != 1 )
			{
				continue;
			}
			PmPhotoPage *photopage = photopages.first();
			if ( !photopage )
			{
				continue;
			}
			QList<PmPageItm *> picitmlst;
			photopage->getPicItms(picitmlst);
			QList<PmPageItm *>::iterator pageitmit;
			for ( pageitmit=picitmlst.begin(); pageitmit!=picitmlst.end(); pageitmit++ )
			{
				PmPageItm *pageitm = *pageitmit;
				if ( PmPageItm::CALENDAR_ITM == pageitm->getPhotoItmType() )
				{
					break;
				}
			}
			if ( pageitmit == picitmlst.end() )
			{
				continue;
			}

			PmPageItm *calitm = *pageitmit;
			//
			bool updated = false;
			// update property

			updated = calitm->setCalProps(calcfg.calcfg);
			updated = calitm->setWdsProps(calcfg.wdcfg);
			updated = calitm->setMonthYearProps(calcfg.monthyearcfg);


			CalViewItm *calviewitm = (CalViewItm *)(calitm->getPageViewItm());
			if ( calviewitm )
			{
				calviewitm->reload();
				this->update();
			}

			CalViewItm *previewitm = (CalViewItm*)calitm->getPreviewPageViewItm();
			if ( previewitm )
			{
				previewitm->reload();
				previewitm->getScene()->update();
			}
		}		
	}
	else
	{
		// update selection
		CalViewItm *calviewitm = dynamic_cast<CalViewItm*>(_selectedphotoitm);
		if ( !calviewitm )
		{
			return ;
		}

		PmPageItm *calitm = calviewitm->getPmPageItm();
		if ( !calitm )
		{
			return ;
		}

		//
		bool updated = false;
		// update property

		updated = calitm->setCalProps(calcfg.calcfg);
		updated = calitm->setWdsProps(calcfg.wdcfg);
		updated = calitm->setMonthYearProps(calcfg.monthyearcfg);

		updated = true;
		if ( updated )
		{
			calviewitm->reload();

			CalViewItm *previewitm = (CalViewItm*)calitm->getPreviewPageViewItm();
			if ( previewitm )
			{
				previewitm->reload();
				previewitm->getScene()->update();
			}
		}
	}
}

void PhotoEditViewScene::_addTextBox(PmTextItm *pTextItm)
{
	LayoutBoxPos itmpos;
	pTextItm->getRectInPrintPage(itmpos);

	QRectF paperpagerect = _paperpageframe;
	qreal papaerpagexoff = paperpagerect.left();
	qreal papaerpageyoff = paperpagerect.top();
	qreal height = paperpagerect.height();
	qreal width = paperpagerect.width();


	QRectF textrect = QRectF(papaerpagexoff + width*itmpos.x+itmpos.margin.left, 
		papaerpageyoff + height*itmpos.y+itmpos.margin.top, 
		width*itmpos.width-itmpos.margin.left-itmpos.margin.right,
		height*itmpos.height-itmpos.margin.top-itmpos.margin.bottom);

        TextViewItem* txtviewitm = new TextViewItem(false, QPointF(textrect.left(),textrect.top()),NULL);
	txtviewitm->setTextItm(pTextItm);
	pTextItm->setViewItm(txtviewitm);
	QString cnt;
	pTextItm->getContent(cnt);
	txtviewitm->setText(cnt);
	txtviewitm->setShadow(pTextItm->isShadowEnable());
	this->addItem(txtviewitm);
	QRectF scrc = this->sceneRect();
	txtviewitm->setFontViewRatio(_paperpageframe.height()/PRINT_PREFERED_HEIGHT);
	txtviewitm->setPos(int(textrect.left()),(int)(textrect.top()));
	txtviewitm->setZValue(3);

	this->selectItm(NULL, txtviewitm);

}

void PhotoEditViewScene::addText()
{
	PmPrintPaperPage *pPringPaperPage = NULL;
	int index = 0;
	pPringPaperPage = this->_pPaperPage;

	pPringPaperPage->addTextbox();
	// update last edit photopage
	QList<PmPhotoPage *> photopages;
	pPringPaperPage->getPhotoPages(photopages);
	if ( photopages.size() )
	{
		_pMainFrame->updateLastPhotoPage(photopages.first());
	}
	//this->_updateTextBox();

	QList<PmTextItm *> txtitmlst;
	_pPaperPage->getTextbox(txtitmlst);
	if ( !txtitmlst.size() )
	{
		return ;
	}


	PmTextItm *pTextItm = txtitmlst.last();
	_addTextBox(pTextItm);

	this->update();

	this->_pMainFrame->updateViews(false);
	//PmPhotoView *photoEditView = _pCentralPane->getEditView();
	//photoEditView->updateView(true);
}


void PhotoEditViewScene::alignText(int align)
{
	PmTextItm *pTxtItm = NULL;
	
	pTxtItm = this->_selctedtxtviewitm->getTextItm();

	if ( pTxtItm )
	{

		int oldalign = pTxtItm->getAlign();
		oldalign &= PmTextItm::ALIGN_VMASK;
		oldalign |= align;
		align = oldalign;
		pTxtItm->setAlign(align);

		TextViewItem *txtviewitm = (TextViewItem*)pTxtItm->getViewItm();
                HorAlignment haligninview;
		switch ( align & PmTextItm::ALIGN_HMASK )
		{
		case PmTextItm::ALIGN_CENTER:
                        haligninview = HorCenterAlig;
			break;
		case PmTextItm::ALIGN_RIGHT:
                        haligninview = HorRightAlig;
			break;
		case PmTextItm::ALIGN_LEFT:
		default:
                        haligninview = HorLeftAlig;

		}
		txtviewitm->setHorAlignment(haligninview);
		txtviewitm->update();
		txtviewitm->scene()->update();
	}
}

void PhotoEditViewScene::valignText(int align)
{
	PmTextItm *pTxtItm = NULL;
	pTxtItm = this->_selctedtxtviewitm->getTextItm();

	if ( pTxtItm )
	{
		int oldalign = pTxtItm->getAlign();
		oldalign &= PmTextItm::ALIGN_HMASK;
		align |= oldalign;
		pTxtItm->setAlign(align);

		TextViewItem *txtviewitm = (TextViewItem*)pTxtItm->getViewItm();
                VerAlignment verigninview;
		switch ( align & PmTextItm::ALIGN_VMASK )
		{
		case PmTextItm::ALIGN_TOP:
                        verigninview = VerTopAlig;
			break;
		case PmTextItm::ALIGN_VCENTER:
                        verigninview = VerCenterAlig;
			break;
		case PmTextItm::ALIGN_BOTTOM:
		default:
                        verigninview = VerBottomAlig;

		}
		txtviewitm->setVerAlignment(verigninview);
		txtviewitm->update();
		txtviewitm->scene()->update();
	}
}


void PhotoEditViewScene::setTextCnt(QString &txt, qreal font_ratio)
{


	PmTextItm *pTxtItm = NULL;
	pTxtItm = this->_selctedtxtviewitm->getTextItm();

	if ( pTxtItm->setContent(txt) )
	{
		TextViewItem *txtviewitm = (TextViewItem*)pTxtItm->getViewItm();
                txtviewitm->setText(txt);
		txtviewitm->update();
		txtviewitm->scene()->update();
	}
}


bool PhotoEditViewScene::enableTxtShadow(bool shadow)
{
	QList<PmTextItm *> txtlst;
	this->_pPaperPage->getTextbox(txtlst);
	QList<PmTextItm *>::iterator txtit;
	for ( txtit = txtlst.begin(); txtit!=txtlst.end(); txtit++ )
	{

		PmTextItm *txtitm = *txtit;
		TextViewItem * txtviewitm = (TextViewItem*)(txtitm->getViewItm());
		txtviewitm->setShadow(shadow);
	}
	return true;
}


bool PhotoEditViewScene::enableShadow(bool shadow)
{
	QList<PmPhotoPage *> photopages;
	this->_pPaperPage->getPhotoPages(photopages);
	QList<PmPhotoPage *>::iterator pageit;
	for ( pageit = photopages.begin(); pageit!=photopages.end(); pageit++ )
	{
		QList<PmPageItm*> photoitmlst;
		(*pageit)->getPicItms(photoitmlst);
		QList<PmPageItm*>::iterator photoitmit;
		for ( photoitmit=photoitmlst.begin(); photoitmit!=photoitmlst.end(); photoitmit++ )
		{
			PmPageItm *pageitm = *photoitmit;
			PhotoViewItm * photoviewitm = (PhotoViewItm*)(pageitm->getPageViewItm());
			photoviewitm->setShadow(shadow);
		}
	}
	return true;
}

bool PhotoPreviewScene::getAround2Papers(int checkpos, PmPrintPaperPage *&beforepaper, PmPrintPaperPage *&nextpaper)
{
	// 
	int midoff = 0;
	QList<PaperPagePreviewItmSet *>::iterator it, next;
	for ( it=_paperpageviewlst.begin(); it!=_paperpageviewlst.end(); it++ )
	{
		PaperPagePreviewItmSet *paperset = *it;
		QRectF rc = paperset->getRect();
		next = it+1;
		if ( next == _paperpageviewlst.end() )
		{
			if ( checkpos < rc.right() )
			{
				return false;
			}
			// should be the last
			beforepaper = paperset->getPaperpage();
			nextpaper = NULL;

			return true;
		}
		QRectF nxtrc = (*next)->getRect();
		if ( (rc.right()-5) < checkpos && checkpos < (nxtrc.left()+5) ) 
		{
			beforepaper = paperset->getPaperpage();
			nextpaper = (*next)->getPaperpage();;
			return true;
		}
	}

	return false;
}

bool  PhotoPreviewScene::getMidPosIn2Paper(int checkpos, int &pos)
{
	// 
	int midoff = 0;
	QList<PaperPagePreviewItmSet *>::iterator it, next;
	for ( it=_paperpageviewlst.begin(); it!=_paperpageviewlst.end(); it++ )
	{
		PaperPagePreviewItmSet *paperset = *it;
		QRectF rc = paperset->getRect();
		next = it+1;
		if ( next == _paperpageviewlst.end() )
		{
			if ( checkpos < rc.right() )
			{
				return false;
			}
			// should be the last
			if ( midoff = 0 )
			{
				midoff = 5;
			}
			pos = rc.left() + rc.width() + midoff;
			return true;
		}

		QRectF nxtrc = (*next)->getRect();
		if ( (rc.right()-5) < checkpos && checkpos < (nxtrc.left()+5) )
		{
			pos = (rc.right() + nxtrc.left())/2;
			return  true;
		}
	}

	return false;
}

/// preview scenen

PhotoPreviewScene::PhotoPreviewScene(const QRectF& rect,PhotoMaker *pMainFrame, QObject *parent)
    : PmViewScnen(parent),_pPaperPage(NULL), _pPaperPageBackGround(NULL), 
	_pMainFrame(pMainFrame), _currentPaper(NULL), _rightBtnPaper(NULL), _bgviweitm(NULL)
{
    //setBoundSize(DEFAULT_BOUNDSIZE);
    setSceneRect(rect);
    setBackgroundBrush(Qt::white);


	QList<PmPrintPaperPage*> paperpages;
	if ( _pMainFrame )
	{
		PmPhotoMakerDoc *pDoc = _pMainFrame->getDoc();
		if ( pDoc )
		{
			pDoc->getPrintPaperPages(paperpages);
		}
	}
	PrintPagesPreviewView *previewview = (PrintPagesPreviewView*)parent;

	// add a background item (for receive drop event)
	_bgviweitm = new PreviewBkgrndViewItm(this,this->_pMainFrame);
	this->addItem(_bgviweitm);
}

bool PhotoPreviewScene::updateNextEditPaper(PmPrintPaperPage *pOldNextPaper, PmPrintPaperPage *pNextPaper)
{
	//
	QList<PaperPagePreviewItmSet *>::iterator it;
	for ( it=_paperpageviewlst.begin(); it!=_paperpageviewlst.end(); it++ )
	{
		PmPrintPaperPage *checkpaper =  (*it)->getPaperpage();
		if ( checkpaper == pOldNextPaper )
		{
			//
			(*it)->setNextEditPaper(false);
			(*it)->update();
		}
		if (  checkpaper == pNextPaper )
		{
			(*it)->setNextEditPaper(true);
			(*it)->update();
		}
	}
	return true;
}



void PhotoPreviewScene::_rmAllPreViewItms()
{
	 QList<QGraphicsItem *> gpitmlst = this->items();
	 QList<QGraphicsItem *>::iterator it;
	 for ( it=gpitmlst.begin(); it!=gpitmlst.end(); it++ )
	 {
		 QGraphicsItem *gpitm = *it;
		 PageViewItm *pgviewitm = dynamic_cast<PageViewItm *>(gpitm);
		 if ( pgviewitm )
		 {
			 PmPageItm *pageitm = pgviewitm->getPmPageItm();
			 if ( pageitm )
			 {
				 pageitm->setPreviewPageViewItm(NULL);
			 }
		 }
		 TextViewItem *txtviweitm = dynamic_cast<TextViewItem *>(gpitm);
		 if ( txtviweitm )
		 {
			 PmTextItm *txtitm = txtviweitm->getTextItm();
			 //txtitm->se(NULL);
		 }
	 }

	 clear();
}


#define PREVIEW_NARROW_ITM_WIDTH	100
#define PREVIEW_ITM_WIDTH	140
#define PREVIEW_ITM_SPAN	16

void PhotoPreviewScene::updateScene(bool bReload)
{
	//

	QRectF rect = this->sceneRect();
	_bgviweitm->setRect(0, 0, rect.width(), rect.height());
	_bgviweitm->setZValue(0);
	if ( bReload )
	{
		_rmAllPreViewItms();

		this->_currentPaper = NULL;
		_bgviweitm = NULL;

		_bgviweitm = new PreviewBkgrndViewItm(this, this->_pMainFrame);
		this->addItem(_bgviweitm);
		_bgviweitm->setZValue(0);

		_paperpageviewlst.clear();
		PmPrintPaperPage *currentpaperpage = NULL;
		QList<PmPrintPaperPage*> paperpages;
		if ( _pMainFrame )
		{
			PmPhotoMakerDoc *pDoc = _pMainFrame->getDoc();
			if ( pDoc )
			{
				pDoc->getPrintPaperPages(paperpages);

				PmPrintPaperPage *pcurpaper = NULL;
				int index = 0;
				_pMainFrame->getDoc()->getCurPrintPaperPage(pcurpaper, index);

				currentpaperpage = pcurpaper;

			}
		}

		PROJ_PROPS proj;
		this->_pMainFrame->getDoc()->getProjProps(proj);
		PrintPagesPreviewView *previewview = (PrintPagesPreviewView*)parent();

		bool calendar = false;
		if ( proj.type == PROJ_PROPS::CALENDARA4 ||
				proj.type == PROJ_PROPS::CALENDARA5 || 
				proj.type == PROJ_PROPS::CALENDAR4X6 )
		{
			calendar = true;
		}

		int index = 0;
		QList<PmPrintPaperPage*>::iterator it;
		bool multiplepage = false;
		for ( it=paperpages.begin(); it!=paperpages.end(); it++, index++ )
		{
			PaperPagePreviewItmSet *paperpageprevieitm = new PaperPagePreviewItmSet(this, *it, this->sceneRect(),this->_pMainFrame);
			if( calendar ||it == paperpages.begin() || it == paperpages.end() )
			{
				paperpageprevieitm->enableMvPaper(false);
			}
			
			(*it)->setPreviewView((PmPhotoView*)previewview);
			_paperpageviewlst.push_back(paperpageprevieitm);
			QString labeltxt;

			this->_getBottomLable(*it, index, labeltxt);

			paperpageprevieitm->setBottomLabel(labeltxt);
			//paperpageprevieitm->update(true);
			if ( currentpaperpage == *it )
			{
				select(paperpageprevieitm);
			}
		}
	
		
	}

	int itmcount = _paperpageviewlst.size();
	if ( !itmcount )
	{
		itmcount = 1;
	}




	QRectF pagerect = rect;

	int paperwidth = 196;
	int paperheight = rect.height();
	if ( paperheight > 220 )
	{
		// width is same
		paperwidth = 196;

	}
	else
	{
		// width is scaled with height
		paperwidth = 196*1.0/220 * paperheight;
	}
	pagerect.setWidth(paperwidth);
	pagerect.adjust(10, 2, 10,-2);

	int width = paperwidth + PREVIEW_ITM_SPAN;
	rect.setWidth((50+width*itmcount>rect.width())?(50+width*itmcount):rect.width());
	this->setSceneRect(rect);
	_bgviweitm->setRect(0, 0, rect.width(), rect.height());
	_bgviweitm->setZValue(0);


	//
	QList<PaperPagePreviewItmSet *>::iterator it;
	int index = 0;
	for ( it=_paperpageviewlst.begin(); it!=_paperpageviewlst.end(); it++, index++ )
	{
		PaperPagePreviewItmSet *paperpageprevieitm = *it;
		paperpageprevieitm->setRect(pagerect);
		if ( index == 1 )
		{
			int i = 0;
		}
		paperpageprevieitm->update(bReload);
		
		/*
		if ( onenarrowpage )
		{
			pagerect.adjust(PREVIEW_NARROW_ITM_WIDTH + PREVIEW_ITM_SPAN, 0, PREVIEW_NARROW_ITM_WIDTH + PREVIEW_ITM_SPAN , 0);
		}
		else
		{
			//
			int previewheight = rect.height();
			if ( previewheight > 220 )
			{
				// width is same
			}
			else
			{
				// width is scaled with height
			}
			if ( itmheight > 140 )
			{
				qreal topmargin = (photoframe.height()-20-120) * 0.5;
				paperpagerect.setTop(photoframe.top() + topmargin);
				qreal bottommargin = (photoframe.height()-20-120) * 0.5;
				paperpagerect.setBottom(photoframe.bottom() - 20 -bottommargin);
			}
			else
			{
				//
				qreal topmargin = (photoframe.height()-20) * 10.0/120.0;
				paperpagerect.setTop(photoframe.top() + topmargin);
				qreal bottommargin = (photoframe.height()-20) * 10.0/120.0;
				paperpagerect.setBottom(photoframe.bottom() - 20 -bottommargin);
			}
			pagerect.adjust(PREVIEW_ITM_WIDTH + PREVIEW_ITM_SPAN, 0, PREVIEW_ITM_WIDTH + PREVIEW_ITM_SPAN , 0);
		}
		*/
		pagerect.adjust(paperwidth + PREVIEW_ITM_SPAN, 0, paperwidth + PREVIEW_ITM_SPAN , 0);

	}

	this->update();

	return ;

}


void PhotoPreviewScene::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
	//
	QGraphicsScene::mousePressEvent(mouseEvent);
	if (this->selectedItems().size() == 0)
	{
		select(NULL);
	}
}

void PhotoPreviewScene::select(int curindex)
{
	PaperPagePreviewItmSet *paperpage = _paperpageviewlst.at(curindex);
	select(paperpage);
}


void PhotoPreviewScene::selectRightBtnPaper(PaperPagePreviewItmSet *pNewPaper)
{

	_rightBtnPaper = pNewPaper;
}


bool PhotoPreviewScene::getRightSelection(PmPrintPaperPage *&paper)
{
	paper = NULL;
	if ( _rightBtnPaper )
	{
		paper = _rightBtnPaper->getPaperpage();
	}

	return true;
}

void PhotoPreviewScene::select(PaperPagePreviewItmSet *pNewPaper)
{
	if ( this->_currentPaper == pNewPaper )
	{
		return ;
	}
	if ( _currentPaper )
	{
		_currentPaper->select(false);
	}
	_currentPaper = pNewPaper;
	if ( !_currentPaper )
	{
		return ;
	}
	_currentPaper->select(true);

	PmPrintPaperPage *paperpage = _currentPaper->getPaperpage();
	if ( paperpage )
	{
		if ( _pMainFrame->getDoc()->setCurPaperPage(paperpage) )
		{
			_pMainFrame->updateEditView(true);
		}
		//paperpage->getEditView(
	}
}



void PhotoPreviewScene::reloadPhotoPage(const PmPhotoPage *pPhotoPage)
{
	return ;

}

bool PhotoPreviewScene::_getBottomLable(PmPrintPaperPage *pPaperPage, int index, QString &labeltxt)
{	
	if ( !pPaperPage )
	{
		return false;
	}

	if ( _isCalendarPrj() )
	{
		QString monlst[] = {tr("January"), tr("February"), tr("March"), tr("April"),
			tr("May"), tr("June"), tr("July"), tr("August"), tr("September"),tr("October"),
			tr("Novermber"), tr("December"),tr("Front page")};
		
		if ( index >= 0 && index < 13)
		{
			int year = 1;
			int month = 1;
			PmPageItm *calitm = this->_pMainFrame->getDoc()->getCalItm(pPaperPage);
			if ( calitm )
			{
				calitm->getMonth(year, month);
				labeltxt = monlst[month-1];
			}
			else
			{
				// front page
				labeltxt = monlst[12];
			}

		}
	}
	else if ( _isSinglePageProj())
	{
		labeltxt = QString(tr("Page %1")).arg(index+1);
	}
	else
	{
		QList<PmPhotoPage *> photopages;
		pPaperPage->getPhotoPages(photopages);
		QList<PmPrintPaperPage*> paperpages;
		this->_pMainFrame->getDoc()->getPrintPaperPages(paperpages);

		//if ( photopages.size() == 1)
		//{
		//	labeltxt = QString(tr("Page %1")).arg(index+1);
		//}
		//else
		{
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
	}

	return true;
}

bool PhotoPreviewScene::_isSinglePageProj()
{
	PROJ_PROPS proj;
	this->_pMainFrame->getDoc()->getProjProps(proj);
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

bool PhotoPreviewScene::_isCalendarPrj()
{
	PROJ_PROPS proj;
	this->_pMainFrame->getDoc()->getProjProps(proj);
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


bool PhotoPreviewScene::addPaperPage(PmPrintPaperPage *pPaperPage,int index, bool updatescene)
{
	PaperPagePreviewItmSet *paperpageprevieitm = new PaperPagePreviewItmSet(this, pPaperPage, this->sceneRect(), this->_pMainFrame);
	pPaperPage->setPreviewView(_pMainFrame->getPreviewView());


	QList<PaperPagePreviewItmSet *>::iterator paperpageit;
	int checkindex = 0;
	for(paperpageit=_paperpageviewlst.begin(); paperpageit!=_paperpageviewlst.end(); paperpageit++, checkindex++ )
	{
		//
		if ( checkindex >= index)
		{
			break;
		}
	}
	if ( paperpageit != _paperpageviewlst.end() )
	{
		_paperpageviewlst.insert(paperpageit, paperpageprevieitm);
	}
	else
	{
		_paperpageviewlst.push_back(paperpageprevieitm);
	}


	QString labeltxt;
	this->_getBottomLable(pPaperPage, index, labeltxt);
	paperpageprevieitm->setBottomLabel(labeltxt);
	paperpageprevieitm->update(true);

	// update all other's index
	if ( updatescene )
	{
		checkindex=0;
		bool multiplepage = false;
		for(paperpageit=_paperpageviewlst.begin(); paperpageit!=_paperpageviewlst.end(); paperpageit++, checkindex++ )
		{
			//
			if ( checkindex <= index )
			{
				continue;
			}
			if ( *paperpageit )
			{
				PaperPagePreviewItmSet *updatepaperpageprevieitm = *paperpageit;
				QString labeltxt;
				this->_getBottomLable(updatepaperpageprevieitm->getPaperpage(),checkindex,labeltxt);
				updatepaperpageprevieitm->setBottomLabel(labeltxt);
			}
		}


		QRectF rect = this->sceneRect();
		int itmcount = _paperpageviewlst.size();
		if ( !itmcount )
		{
			itmcount = 1;
		}

		qreal width = 160;
		rect.setWidth((100+width*itmcount)>rect.width()?(100+width*itmcount):rect.width());
		this->setSceneRect(rect);

		this->updateScene(false);
	}

	return true;
}
bool PhotoPreviewScene::rmPaperPage(const PmPrintPaperPage *pPaperPage, int &index, bool updatescene)
{
	//
	// first remove all items below this paperpage
	//

	index = 0;
	QList<PaperPagePreviewItmSet *>::iterator paperpageit;
	PaperPagePreviewItmSet* pPaperPageViewItm = NULL;
	for(paperpageit=_paperpageviewlst.begin(); paperpageit!=_paperpageviewlst.end(); paperpageit++, index++)
	{
		if ( (*paperpageit)->getPaperpage() == pPaperPage )
		{
			pPaperPageViewItm = *paperpageit;
			break;
		}
	}
	if ( !pPaperPageViewItm )
	{
		// preview scene has no such paperpage
		return false;
	}

	pPaperPageViewItm->remove();
	_paperpageviewlst.erase(paperpageit);
	// update all other's index
	if ( updatescene )
	{
		int checkindex=0;
		bool multiplepage = false;
		for(paperpageit=_paperpageviewlst.begin(); paperpageit!=_paperpageviewlst.end(); paperpageit++, checkindex++ )
		{
			//
			if ( checkindex <= index-1 )
			{
				continue;
			}
			if ( *paperpageit )
			{
				PaperPagePreviewItmSet *updatepaperpageprevieitm = *paperpageit;
				QString labeltxt;
				this->_getBottomLable(updatepaperpageprevieitm->getPaperpage(),checkindex,labeltxt);
				updatepaperpageprevieitm->setBottomLabel(labeltxt);
				if ( paperpageit + 1 == _paperpageviewlst.end() )
				{
					updatepaperpageprevieitm->enableMvPaper(false);
				}
			}
		}


		QRectF rect = this->sceneRect();
		int itmcount = _paperpageviewlst.size();
		if ( !itmcount )
		{
			itmcount = 1;
		}

		qreal width = 160;
		rect.setWidth((100+width*itmcount)>rect.width()?(100+width*itmcount):rect.width());
		this->setSceneRect(rect);

		this->updateScene(false);
	}


	return true;
}

void PhotoPreviewScene::reloadPaperPage(const PmPrintPaperPage *pPaperPage, bool updatescene)
{
	int index = 0;
	if ( !rmPaperPage(pPaperPage, index, false) )
	{
		return ;
	}
	
	if ( !addPaperPage((PmPrintPaperPage *)pPaperPage,index, false) )
	{
		return ;
	}

	// update scenen, all items need to be updated will be updated
	this->update();

}


/////////////////////////////////////////////////////////////////////////////////////////////////////
// print scene
/////////////////////////////////////////////////////////////////////////////////////////////////////////

PhotoPrintScene::PhotoPrintScene(const QRectF& rect,  PhotoMaker *pMainFrame, QObject *parent)
    : QGraphicsScene(parent),_pPaperPage(NULL), _pPaperPageBackGround(NULL),
	_pMainFrame(pMainFrame), _selctedtxtviewitm(NULL),_selectedphotoitm(NULL),
	_printerpaper(NULL), _endprintpageno(0), _cancel(false), _xoff(0), _yoff(0)
{
    setSceneRect(rect);
    //setBackgroundBrush(Qt::white);
	
	// i am not sure why we should set this
	// but if we do not set, nothing will be printed
	setBackgroundBrush(Qt::transparent);

	//_timer = new QTimer(this);

	//connect(_timer, SIGNAL(timeout()), this, SLOT(_printerTimerFunc()));
}


void PhotoPrintScene::loadPaperPage(PmPrintPaperPage *pPaperPage)
{
	this->clear();
	_pPaperPage = pPaperPage;
	addPaperPage(_pPaperPage, 0, false);
	update();
}

void PhotoPrintScene::_onCancelPrint()
{
	//
	_cancel = true;
}

void PhotoPrintScene::setprintoff(qreal xoff, qreal yoff)
{
	_xoff = xoff; _yoff = yoff;
}

void PhotoPrintScene::print(QPrinter *printer, QPainter *painter, PRINT_TASK_INFO* printInfo)	
{
	if ( !printInfo || !printer || !painter )
	{
		return ;
	}

	this->_printer =  printer;
	this->_painter = painter;
	this->_curpageno = printInfo->beginpage;
	this->_endprintpageno = printInfo->endpage;

	_twopagesinpaper = false;
	PROJ_PROPS proj;
	_pMainFrame->getDoc()->getProjProps(proj);
	switch(proj.type)
	{
	case  PROJ_PROPS::POCKETBOOK4X3:
	case PROJ_PROPS::PHOTOBOOK8X5:
		_twopagesinpaper = true;
		break;
	}
	if ( _twopagesinpaper )
	{

		if ( printInfo->beginpage%2 == 0 )
		{
			//
			this->_curpageno  = printInfo->beginpage-1;
		}

		if ( printInfo->endpage%2 != 0 )
		{
			//
			this->_endprintpageno  = printInfo->endpage+1;
		}
	}

	_printerpaper = new PmPrintPaperPage(NULL, NORMAL_PAGE);

	_leftpage = NULL; 
	_printtxtlst.clear();
	_papers.clear();
	_pMainFrame->getDoc()->getPrintPaperPages(_papers);
	

	_printInfoBar = new PrintInfoBar();
	_cancel = false;
	connect(_printInfoBar, SIGNAL(cancel()), this, SLOT(_onCancelPrint()));

	//_labelInfo = new QLabel(NULL, Qt::WindowStaysOnTopHint/*|Qt::FramelessWindowHint*/);
	//_labelInfo->setAlignment(Qt::AlignHCenter);
	QRect rect = _pMainFrame->geometry();
	QRect infobarrc = _printInfoBar->geometry();
	_printInfoBar->setGeometry(rect.width()/2-infobarrc.width()/2, rect.height()/2-40, infobarrc.width(), infobarrc.height());
	_printInfoBar->show();
	this->_go2NextPrintPaper();
}

#define PAPER_PRINTER_TIMER	500

void PhotoPrintScene::_go2NextPrintPaper()
{
	//
	if ( _curpageno >  _endprintpageno || _cancel )
	{
		// no next page

		//_labelInfo->close();
		//_printInfoBar
		delete _printInfoBar;
		_printInfoBar = NULL;
		delete this->_printerpaper;
		_printerpaper = NULL;
		delete this->_painter;
		_painter = NULL;
		delete this->_printer;
		_printer = NULL;

		return ;
	}

	PROJ_PROPS proj;
	this->_pMainFrame->getDoc()->getProjProps(proj);

	int paperindex = 0;
	if ( this->_twopagesinpaper )
	{
		paperindex = this->_curpageno/2;
	}
	else
	{
		paperindex = _curpageno - 1;
	}
	QList<PmPhotoPage *> photopages;
	_papers[paperindex]->getPhotoPages(photopages);


	if ( proj.type == PROJ_PROPS::CALENDARA4 || 
		proj.type == PROJ_PROPS::CALENDARA5 ||
		proj.type == PROJ_PROPS::CALENDAR4X6 ||
		 proj.type == PROJ_PROPS::PHOTOBOOK10X15 || proj.type == PROJ_PROPS::SINGLE4X6 )
	{
		// first page should be asigned, now get the right page
		QList<PmPhotoPage*> printerpages;
		PmPhotoPage *printpage = new PmPhotoPage(*photopages[0]);

		printerpages.push_back(printpage);
		_printerpaper->setPhotoPages(printerpages);

		QString info;


		if ( proj.type == PROJ_PROPS::PHOTOBOOK10X15 || proj.type == PROJ_PROPS::SINGLE4X6 )
		{
			info += QString(tr("Page No %1")).arg(_curpageno);
		}
		else
		{
			QString monlst[] = {tr("January"), tr("February"), tr("March"), tr("April"),
				tr("May"), tr("June"), tr("July"), tr("August"), tr("September"),tr("October"),
				tr("Novermber"), tr("December")};	

			int year = 1;
			int month = 1;
			PmPageItm *calitm = this->_pMainFrame->getDoc()->getCalItm(_printerpaper);
			if ( calitm )
			{
				calitm->getMonth(year, month);
			}

			info += monlst[month-1];

		}

		_printInfoBar->showInfo(info);
		//_labelInfo->setText(info);
		//_labelInfo->update();
		_curpageno++;
		//_timer->start(0); 
		QTimer::singleShot(PAPER_PRINTER_TIMER, this, SLOT(_printerTimerFunc()));

		// paint the paper

	}
	else
	{
		if ( photopages.size() == 1 )
		{
			// first
			_leftpage = photopages[0];

			QList<PmTextItm *> txtlst;
			_papers[paperindex]->getTextbox(txtlst);

			QList<PmTextItm *>::iterator it;
			for ( it=txtlst.begin(); it!=txtlst.end(); it++ )
			{
				PmTextItm *ptxtitm = new PmTextItm(**it);
				LayoutBoxPos pos;
				ptxtitm->getRectInPrintPage(pos);
				if ( pos.x <= 0.5 )
				{
					// not currect
					continue;
				}
				pos.x -= 0.5;
				ptxtitm->setRectInPrintPage(pos);
				_printtxtlst.push_back(ptxtitm);
			}

			_curpageno++;
			// go next paper
			_go2NextPrintPaper();
		}
		else
		{
			// first page should be asigned, now get the right page
			PmPhotoPage *rightpage = NULL;
			rightpage = photopages[0];
			QList<PmPhotoPage*> printerpages;


			if ( _leftpage )
			{
				// if no left page, the previous page is not printed
				PmPhotoPage *printleftpage = new PmPhotoPage(*_leftpage);
				printleftpage->reversePagePos();
				PmPhotoPage *printrightpage = new PmPhotoPage(*rightpage);
				printrightpage->reversePagePos();
				printerpages.push_back(printleftpage);
				printerpages.push_back(printrightpage);
				_printerpaper->setPhotoPages(printerpages);

				// get text item list
				QList<PmTextItm *> nexttxtlst, txtlst;
				_papers[paperindex]->getTextbox(txtlst);
				QList<PmTextItm *>::iterator txtitmit;
				for ( txtitmit=txtlst.begin(); txtitmit!=txtlst.end(); txtitmit++ )
				{
					//
					PmTextItm *txtitm = *txtitmit;
					if ( !txtitm)
					{
						continue;
					}
					LayoutBoxPos pos;
					txtitm->getRectInPrintPage(pos);
					if ( pos.x <= 0.5 )
					{
						// in this page, 
						PmTextItm *txtitmcpy = new PmTextItm(*txtitm);
						pos.x += 0.5;
						txtitmcpy->setRectInPrintPage(pos);
						_printtxtlst.push_back(txtitmcpy);
					}
					else
					{
						PmTextItm *txtitmcpy = new PmTextItm(*txtitm);
						pos.x -= 0.5;
						txtitmcpy->setRectInPrintPage(pos);
						nexttxtlst.push_back(txtitmcpy);
					}
				}
				for ( txtitmit = _printtxtlst.begin(); txtitmit != _printtxtlst.end(); txtitmit++ )
				{
					(*txtitmit)->setPrintPage(_printerpaper);
					_printerpaper->addTextbox(*txtitmit);
				}
				_printtxtlst = nexttxtlst;
				_leftpage = photopages[1];

				// do in timer
				QString info;
				info += QString(tr("Page No %1 - %2")).arg(_curpageno-1).arg(_curpageno);
				_printInfoBar->showInfo(info);
				//_labelInfo->setText(info);
				//_labelInfo->update();
				_curpageno+=2;
				//_timer->start(0);
				QTimer::singleShot(PAPER_PRINTER_TIMER, this, SLOT(_printerTimerFunc()));
			}
			else
			{
				QList<PmTextItm *> txtlst;
				_papers[paperindex]->getTextbox(txtlst);

				QList<PmTextItm *>::iterator it;
				for ( it=txtlst.begin(); it!=txtlst.end(); it++ )
				{
					PmTextItm *ptxtitm = new PmTextItm(**it);
					LayoutBoxPos pos;
					ptxtitm->getRectInPrintPage(pos);
					if ( pos.x <= 0.5 )
					{
						// not currect
						continue;
					}
					pos.x -= 0.5;
					ptxtitm->setRectInPrintPage(pos);
					_printtxtlst.push_back(ptxtitm);
				}

				_leftpage = photopages[1];
				_curpageno+=1;
				_go2NextPrintPaper();

			}

			// 
		}
	}

}

void PhotoPrintScene::_printerTimerFunc()
{
	if ( !_printerpaper )
	{
		return ;
	}
	loadPaperPage(_printerpaper);
	this->render(_painter);

	QList<PmPhotoPage *> pages;
	_printerpaper->getPhotoPages(pages);
	QList<PmPhotoPage *>::iterator it;
	for ( it=pages.begin(); it!=pages.end(); it++ )
	{
		delete *it;
	}

	if ( _curpageno <=  _endprintpageno )
	{
		this->_printer->newPage();
	}

	this->_go2NextPrintPaper();
}


void PhotoPrintScene::_updateBackgroundItm()
{
	return ;
}
#if 0
void PhotoPrintScene::_addBackgroundItm()
{
	if ( _pPaperPageBackGround )
	{
		return ;
	}


	QString backgroundimg;
	if (  _pPaperPage->getBackGroundImgInEditView(backgroundimg) )
	{
		_pPaperPageBackGround = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(backgroundimg)));
		QLinearGradient linearGrad(QPointF(0, 0), QPointF(1024, 768));

		this->addItem(_pPaperPageBackGround);
		_pPaperPageBackGround->setZValue(0);

		_pPaperPageBackGround->setX(_paperpageframe.left());
		_pPaperPageBackGround->setY(_paperpageframe.top());

		QImage img(backgroundimg);
		QImage newsizeimg = img.scaled(_paperpageframe.width(), _paperpageframe.height());
		_pPaperPageBackGround->setPixmap(QPixmap::fromImage(newsizeimg));

		QGraphicsDropShadowEffect* gdse =  (QGraphicsDropShadowEffect*)_pPaperPageBackGround->graphicsEffect();
		if( gdse == 0 )
		{
#define NORM_LINE 1
#define SHADOW_OFFSET 3.5
#define SHADOW_BLUR   10.0
#define MOUSEMV_THRES 5

			gdse = new QGraphicsDropShadowEffect(this);
			gdse->setOffset(1, 1);
			gdse->setBlurRadius(1);

			// strage, the following must be called, otherwise, the scene will not be pritned
			_pPaperPageBackGround->setGraphicsEffect(gdse);
		}
	}

}
#endif

void PhotoPrintScene::_updateTextBox()
{
	QList<PmTextItm *> txtitmlst;
	_pPaperPage->getTextbox(txtitmlst);
	if ( !txtitmlst.size() )
	{
		return ;
	}

	QRectF scrc = this->sceneRect();
	LayoutBoxMargin marginInEditView;
	this->_pPaperPage->getMarginInEditView(marginInEditView);
	marginInEditView.left = marginInEditView.mid = marginInEditView.right = 0;
	marginInEditView.top = marginInEditView.bottom = 0;


	QList<PmTextItm *>::iterator it;
	for ( it=txtitmlst.begin(); it!=txtitmlst.end(); it++ )
	{
		PmTextItm *pTextItm = *it;

		LayoutBoxPos itmpos;
		pTextItm->getRectInPrintPage(itmpos);

		QRectF paperpagerect = _paperpageframe;
		qreal papaerpagexoff = paperpagerect.left();
		qreal papaerpageyoff = paperpagerect.top();
		qreal height = paperpagerect.height();
		qreal width = paperpagerect.width();

		papaerpagexoff += width*marginInEditView.left;
		papaerpageyoff += height * marginInEditView.top;
		width = width * ( 1-marginInEditView.left-marginInEditView.right - marginInEditView.mid);
		height = height * ( 1-marginInEditView.top-marginInEditView.bottom);

		QRectF textrect;
		if ( itmpos.x < 0.5 )
		{
			// left page
			textrect = QRectF(papaerpagexoff + width*itmpos.x, 
				papaerpageyoff + height*itmpos.y, 
				itmpos.width,
				itmpos.height);

		}
		else
		{
			// right page
			textrect = QRectF(papaerpagexoff + width*itmpos.x +  marginInEditView.mid*_paperpageframe.width(), 
				papaerpageyoff + height*itmpos.y, 
				itmpos.width,
				itmpos.height);
		}
		TextViewItem* txtviewitm = (TextViewItem*)pTextItm->getViewItm();
		txtviewitm->setPos(int(textrect.left()),(int)(textrect.top()));
		txtviewitm->setWidthHeight(textrect.width()/*600/scrc.height()*/, textrect.height()/**600/scrc.height()*/);
		txtviewitm->setFontViewRatio(_paperpageframe.height()/PRINT_PREFERED_HEIGHT);
	}

}

void PhotoPrintScene::_addTextBox()
{
	QList<PmTextItm *> txtitmlst;
	_pPaperPage->getTextbox(txtitmlst);
	if ( !txtitmlst.size() )
	{
		return ;
	}

	QList<PmTextItm *>::iterator it;
	for ( it=txtitmlst.begin(); it!=txtitmlst.end(); it++ )
	{
		PmTextItm *pTextItm = *it;

		LayoutBoxPos itmpos;
		pTextItm->getRectInPrintPage(itmpos);

		QRectF paperpagerect = _paperpageframe;
		qreal papaerpagexoff = paperpagerect.left();
		qreal papaerpageyoff = paperpagerect.top();
		qreal height = paperpagerect.height();
		qreal width = paperpagerect.width();


		QRectF textrect = QRectF(papaerpagexoff + width*itmpos.x+itmpos.margin.left, 
			papaerpageyoff + height*itmpos.y+itmpos.margin.top, 
			width*itmpos.width-itmpos.margin.left-itmpos.margin.right,
			height*itmpos.height-itmpos.margin.top-itmpos.margin.bottom);

        TextViewItem* txtviewitm = new TextViewItem(true, QPointF(textrect.left(),textrect.top()),NULL);
		txtviewitm->setTextItm(pTextItm);
		pTextItm->setViewItm(txtviewitm);
		QString cnt;
		pTextItm->getContent(cnt);
		txtviewitm->setText(cnt);
		txtviewitm->setShadow(pTextItm->isShadowEnable());
		this->addItem(txtviewitm);
		txtviewitm->setPos(int(textrect.left()),(int)(textrect.top()));
		txtviewitm->setZValue(3);
		//pTextItm->setViewItm(txtviewitm);
	}
	this->_updateTextBox();
}




void PhotoPrintScene::_addPhotoPage(PmPhotoPage *pPhotoPage)
{
	if ( !pPhotoPage )
	{
		return ;
	}

	LayoutBoxPos pagepos;
	pPhotoPage->getPagePosInPaper(pagepos);

	QRectF paperpagerect = _paperpageframe;
	qreal papaerpagexoff = paperpagerect.left() ;
	qreal papaerpageyoff = paperpagerect.top();

	qreal height = paperpagerect.height();
	qreal width = paperpagerect.width();


	LayoutBoxMargin marginInEditView;
	this->_pPaperPage->getMarginInEditView(marginInEditView);
	marginInEditView.left = marginInEditView.right = marginInEditView.top = marginInEditView.bottom = 0;

	papaerpagexoff += width*marginInEditView.left;
	papaerpageyoff += height * marginInEditView.top;
	width = width * ( 1-marginInEditView.left-marginInEditView.right);
	height = height * ( 1-marginInEditView.top-marginInEditView.bottom);


	///
	qreal pagex, pagey, pagewidth, pageheight;
		// right page
	pagex = papaerpagexoff + width*pagepos.x;
	pagewidth = width * pagepos.width;

	pagey = papaerpageyoff + height*pagepos.y/*+pagepos.margin.top*height*/;
	pageheight = height * pagepos.height;

	
	// adjust page area
	pagex += pagewidth * pagepos.margin.left;
	pagewidth = pagewidth * ( 1-pagepos.margin.left - pagepos.margin.right);
	pagey += pageheight * pagepos.margin.top;
	pageheight = pageheight * ( 1 - pagepos.margin.top - pagepos.margin.bottom);

	QRectF pagerect = QRectF(pagex,pagey,pagewidth, pageheight );

	///

	QList<PmPageItm *> picitmlst;
	pPhotoPage->getPicItms(picitmlst);


	// create new items
	QList<PmPageItm *>::iterator it;
	for(it=picitmlst.begin(); it!=picitmlst.end(); it++ )
	{
		//

		/*1. Adjust the image size according the scene's size*/
		/*2. Set the position according the scene's size*/
		PmPageItm *pPicItm = *it;
		LayoutBoxPos itmrect;
		pPicItm->getRectInPage(itmrect);

		// first add photo page offset

		qreal xoff,yoff;
		xoff = pagerect.left() + pagerect.width()* itmrect.x;
		yoff = pagerect.top() + pagerect.height()*itmrect.y;

		qreal itmwidth, itmheight;
		itmwidth = itmrect.width*pagerect.width();
		itmheight = itmrect.height * pagerect.height();

		QMargins margin = QMargins(pagerect.width()*itmrect.margin.left,
			pagerect.height()*itmrect.margin.top,
			pagerect.width()*itmrect.margin.right,
			pagerect.height()*itmrect.margin.bottom);

		PageViewItm *viewitem = NULL;
		if ( pPicItm->getPhotoItmType() != PmPageItm::CALENDAR_ITM )
		{
			PhotoViewItm* item1 = NULL;

			if (_isPanoramaLayout(pPhotoPage->getLayout() ) )
			{
				item1 = new PhotoPanoViewItm(QPointF(xoff,yoff),
					QSize((int)itmwidth,(int)itmheight),margin,
					(!pPhotoPage->isLeft())?PhotoPanoViewItm::Left_Pano:PhotoPanoViewItm::Right_Pano,
					NULL);
			}
			else
			{
				item1 = new PhotoViewItm(QPointF(xoff,yoff),
				QSize((int)itmwidth,(int)itmheight),margin,NULL);
			}

			viewitem = item1;
			QString imgpath;
			pPicItm->getContent(imgpath);
			if ( imgpath.length())
			{
				QPixmap savedpixmap;
				QPixmap *pixmap = pPicItm->getPixmap();
				if ( pixmap )
				{
					savedpixmap = *pixmap;
				}

				item1->setImg(imgpath, savedpixmap);
			}
			else
			{
				QPixmap savedpixmap;

				item1->setImg(imgpath,savedpixmap);
			}

			QColor color;
			pPicItm->getBgColor(color);
			item1->setItemBGColor(color);
		}
		else
		{

			//
			PROJ_PROPS proj;
			this->_pMainFrame->getDoc()->getProjProps(proj);

			CalViewItm *calviewitm = CalViewItmFactory::getViewItm(proj.lytype, QPointF(0,0),
						QSize((int)itmwidth,(int)itmheight),margin,NULL);
			viewitem = calviewitm;

			CALENDAR_CFG calcfg;
			pPicItm->getCalProps(calcfg.calcfg);
			pPicItm->setCalProps(calcfg.calcfg);
			pPicItm->getWdsProps(calcfg.wdcfg);
			pPicItm->setWdsProps(calcfg.wdcfg);
			pPicItm->getMonthYearProps(calcfg.monthyearcfg);
			pPicItm->setMonthYearProps(calcfg.monthyearcfg);
			int year = 0, mon = 0;
			pPicItm->getMonth(year, mon);
			calviewitm->setYearMonth(year, mon);

			// calendar

		}

		PROJ_PROPS proj;
		this->_pMainFrame->getDoc()->getProjProps(proj);
		bool shadow = proj.shadow;
		this->addItem(viewitem);
		viewitem->setZValue(2);
		//pPicItm->setPageViewItm(viewitem);
		viewitem->setPmPageItm(pPicItm);

		//shadow = true;
		viewitem->setShadow(shadow);
		if ( shadow )
		{
			QGraphicsDropShadowEffect* gdse =  (QGraphicsDropShadowEffect*)viewitem->graphicsEffect();
			if( gdse == 0 )
			{
//#define NORM_LINE 1
#define SHADOW_OFFSET 2
#define SHADOW_BLUR   10.0
//#define MOUSEMV_THRES 5

				gdse = new QGraphicsDropShadowEffect(NULL);
				gdse->setOffset(SHADOW_OFFSET, SHADOW_OFFSET);
				gdse->setBlurRadius(SHADOW_BLUR);
				viewitem->setGraphicsEffect(gdse);
			}
		}
		viewitem->setPos(int(xoff),(int)(yoff));
		//viewitem->setZValue(1);
		viewitem->resize();
	}
}


bool PhotoPrintScene::addPaperPage(PmPrintPaperPage *pPaperPage, int index, bool updatescene)
{

	//
	_pPaperPage = (PmPrintPaperPage *)pPaperPage;


	//
	// update the scene rect 
	//
	QSize size;
	_pPaperPage->getSize(size);
	QRectF rect = sceneRect();

	qreal height, width;
	width = rect.width();
	height = rect.height();

	if ( width <= 0 ) width = 10;
	if ( height <= 0 ) height = 10;

	_paperpageframe.setLeft(0);
	_paperpageframe.setTop(0);
	_paperpageframe.setWidth(width);
	_paperpageframe.setHeight(height);

	_paperpageframe.adjust(_xoff, _yoff, _xoff, _yoff);


	PmPhotoPage *pPhotoPage = NULL;
	QList<PmPhotoPage *> photoPages;
	_pPaperPage->getPhotoPages(photoPages);

	QList<PmPhotoPage *>::iterator it2;
	for(it2=photoPages.begin(); it2!=photoPages.end(); it2++ )
	{
		//
		this->_addPhotoPage(*it2);
	}
	this->_addTextBox();

	return true;

}


#if 0
class InfoProducer : public QThread
{
public:
	InfoProducer(QWidget * frame);
public:
    int run(int argc, char *argv[], unsigned long ms);
	void stop();

private:
	bool _stop;
	QLabel *_infoBar;
	QWidget *_frame;

};

InfoProducer::InfoProducer(QWidget * frame):_stop(false), _frame(frame)
{
	_infoBar = new QLabel(NULL ,Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
	QRect rect = _frame->geometry();
	rect.adjust(rect.left(), rect.top(), rect.left(), rect.top());
	_infoBar->setGeometry(rect.width()/2-100, rect.height()/2-25, 200, 50);
	_infoBar->show();

}

void InfoProducer::stop()
{
	_stop = true;
}

int InfoProducer::run(int argc, char *argv[], unsigned long ms)
{

	while(_stop)
	{
		usleep(1000);
	}

	return 0;
}
#endif
