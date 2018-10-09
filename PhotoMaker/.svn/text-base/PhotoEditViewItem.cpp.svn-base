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
#include "PhotoEditViewItem.h"
#include "photomaker.h"
#include "PhotoEditView.h"
#include "qmeta/jpeg.h"
#include <QPushbutton>
#include "pmundoactionstack.h"
#include "PhotoCalViewItem.h"
#include "PhotoHSLEditWidget.h"
#include "PhotoBWCEditWidget.h"
#include "PhotoLCIGEditWidget.h"
#include "PhotoRedeyeEditWidget.h"
/*********************************************************/
//PageViewItm related
/*********************************************************/
PageViewItm::PageViewItm(const QPointF &pos,
                         const QSize &size,
                         const QMargins& margin,
                         PmViewScnen *scene,
                         QGraphicsItem *parent)
    :QGraphicsObject(parent), _pPageItm(NULL)
{
    item_pos = pos;
    item_size = size;
    item_margin = margin;

    item_shadow = false;
    setShadow(false);

    item_bgcolor = Qt::white;

    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptDrops(true);
    //setCursor(Qt::BusyCursor);

}

PageViewItm::~PageViewItm()
{
    //do nth
}

QRectF PageViewItm::boundingRect() const
{
    qreal adjust = SHADOW_OFFSET;
    return QRectF(0, 0, item_size.width() + adjust, item_size.height() + adjust);
}


void PageViewItm::setShadow(bool s)
{
    static int first = 1;
    if( !first && item_shadow == s )
        return;

    first = 0;
    item_shadow = s;

    QGraphicsDropShadowEffect* gdse =  (QGraphicsDropShadowEffect*)this->graphicsEffect();
    if( gdse == 0 )
    {
        gdse = new QGraphicsDropShadowEffect(NULL);
        gdse->setOffset(SHADOW_OFFSET, SHADOW_OFFSET);
        gdse->setBlurRadius(SHADOW_BLUR);
        this->setGraphicsEffect(gdse);
    }
	QString imgpath;
	QColor bgcolor = Qt::white;
	if ( _pPageItm )
	{
		this->_pPageItm->getContent(imgpath);
		_pPageItm->getBgColor(bgcolor);
	}
	if( item_shadow && (imgpath.length() || bgcolor!=Qt::white))
    {
		PmPhotoPage *page = this->_pPageItm->getPage();
		PHOTO_LAYOUT ly = page->getLayout();
		bool panorama = false;
		switch(ly)
		{
		case PP_LAYOUT_FULLSIZE_PANOR:
		case PP_LAYOUT_BORDER_PANOR:
		case PP_LAYOUT_PB8X5_FULLSIZE_PANOR:
		case PP_LAYOUT_PB8X5_TRADITION_PANOR:
		case PP_LAYOUT_PB8X5_HORIZON_PANOR:
		case PP_LAYOUT_PB8X5_VERTICON_PANOR:
			panorama = true;
			break;
		default:
			;
		}
		bool leftpage = page->isLeft();
		if ( panorama && leftpage )
		{
			gdse->setOffset(0, SHADOW_OFFSET);
		}
		else
		{
			gdse->setOffset(SHADOW_OFFSET, SHADOW_OFFSET);
		}
        gdse->setBlurRadius(SHADOW_BLUR);
    }
    else
    {
        gdse->setOffset(0, 0);
        gdse->setBlurRadius(0);
    }
    this->update();
}

static void blur(QImage* image, const QRect& rect, int radius, bool alphaOnly = false)
{
    int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
    int alpha = (radius < 1)  ? 16 : (radius > 17) ? 1 : tab[radius-1];

    int r1 = rect.top();
    int r2 = rect.bottom();
    int c1 = rect.left();
    int c2 = rect.right();

    int bpl = image->bytesPerLine();
    int rgba[4];
    unsigned char* p;

    int i1 = 0;
    int i2 = 3;

    if (alphaOnly)
        i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);

    for (int col = c1; col <= c2; col++) {
        p = image->scanLine(r1) + col * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p += bpl;
        for (int j = r1; j < r2; j++, p += bpl)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int row = r1; row <= r2; row++) {
        p = image->scanLine(row) + c1 * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p += 4;
        for (int j = c1; j < c2; j++, p += 4)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int col = c1; col <= c2; col++) {
        p = image->scanLine(r2) + col * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p -= bpl;
        for (int j = r1; j < r2; j++, p -= bpl)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }

    for (int row = r1; row <= r2; row++) {
        p = image->scanLine(row) + c2 * 4;
        for (int i = i1; i <= i2; i++)
            rgba[i] = p[i] << 4;

        p -= 4;
        for (int j = c1; j < c2; j++, p -= 4)
            for (int i = i1; i <= i2; i++)
                p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
    }
}



void PageViewItm::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //draw the backgroud
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(QRect(0,0,item_size.width(),item_size.height()));



    //draw the boundary and main part
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(NORM_LINE);
	if ( item_bgcolor != Qt::white && !isSelected())
	{
		pen.setStyle(Qt::NoPen);
	}

	if( this->isSelected() )
	{
	    pen.setWidth(2*NORM_LINE);
		pen.setBrush(Qt::blue);
	}
    else
        pen.setBrush(Qt::lightGray);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    painter->setPen(pen);
    painter->setBrush(QBrush(item_bgcolor));

    QRect rect(item_margin.left(), item_margin.top(),
               (item_size.width()-item_margin.left()-item_margin.right()),
               (item_size.height()-item_margin.top()-item_margin.bottom()));
	painter->drawRect(rect);
}

void PageViewItm::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
}
void PageViewItm::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
}


#if 0
void PageViewItm::updateCursor(QCursor cursor)
{
    //
    setCursor(cursor);
    _eventforcursorupdate.release();
}

class PmViewItmUpdateRunner: public QThread
{
public:
    PmViewItmUpdateRunner(PageViewItm* pViewItm);
public:
    int run(unsigned long ms);

private:
    PageViewItm  *_pViewItm;
};

PmViewItmUpdateRunner::PmViewItmUpdateRunner(PageViewItm* pViewItm):_pViewItm(pViewItm)
{
}

int PmViewItmUpdateRunner::run(unsigned long ms)
{
    if ( !this->_pViewItm )
    {
        return -1;
    }

    QObject *parent = _pViewItm->getScene()->parent();
    PmPhotoView *pEditView = (PmPhotoView *)parent;
    pEditView->reloadviewitm(_pViewItm);
    return 0;
}

void PageViewItm::setContentFunc(void *context)
{
    PageViewItm *pThis = (PageViewItm *)context;
    if ( !pThis )
    {
        return ;
    }
    PmViewItmUpdateRunner runner(pThis);

    runner.run(2);
}
#endif

void PageViewItm::_updateCntTimerFunc()
{
	PhotoEditViewScene *peditscene = dynamic_cast<PhotoEditViewScene*>(this->getScene());
	if ( peditscene )
	{
		//peditscene->saveSelection();
	}
	this->setContent(_cnt);
	if ( peditscene )
	{
		//peditscene->restoreSelection();
	}
}

void PageViewItm::dropEvent(QGraphicsSceneDragDropEvent *event)
{

	/// update path
	if ( !_pPageItm )
	{
		return ;
	}

	QString info;
	if (event->mimeData()->hasText())
		info = event->mimeData()->text();

	QString srcloc = event->mimeData()->data("srcloc");
	if ( srcloc == "filelistview" )
	{
		this->_cnt = info;
		//QFuture<void> future = QtConcurrent::run(setContentFunc, this);

		// update page left/right property
		// copy the photo to project folder
		if ( !(_cnt.length()>8 && _cnt.left(7) == LY_PREFIX) )
		{
			QString path = _cnt;
			QString savedpath ;
			QFile file(path);
			if ( file.size() > 2*1024*1024 ) 
			{
				savedpath = "prj/";
				int index = path.lastIndexOf("/");
				if ( index > 0 )
				{
					QString name = path.right(path.length()-index-1);
					savedpath += name;

					QFile savedfile(savedpath);
					if ( savedfile.open(QIODevice::ReadOnly) )
					{
						savedfile.close();
						path = savedpath;
					}
					else
					{
						if ( file.copy(savedpath) )
						{
							path = savedpath;

						}
					}
				}
			}
			else
			{
				savedpath = "prj/";
				int index = path.lastIndexOf("/");
				if ( index > 0 )
				{
					QString name = path.right(path.length()-index-1);
					savedpath += name;
					if ( file.copy(savedpath) )
					{
						path = savedpath;
					}
					else
					{
						// check if exit
						QFile savefile;
						if ( savefile.exists(savedpath) )
						{
							path = savedpath;
						}
					}
				}
			}

			_cnt = path;

			this->setCursor(Qt::BusyCursor);
			QTimer::singleShot(500, this, SLOT(_updateCntTimerFunc()));

			//this->setContent(path);
		}
		else
		{
			//this->setContent(_cnt);
			this->setCursor(Qt::BusyCursor);

			QTimer::singleShot(500, this, SLOT(_updateCntTimerFunc()));
		}
		

	}
	else if ( srcloc == "preview" )
	{
		PmPageItm *pOldPageitm = NULL;
		QByteArray orgpageitm;
		QString tmp;
		if ( event->mimeData()->hasFormat("orginalpageitm") )
		{
			orgpageitm = event->mimeData()->data("orginalpageitm");
			tmp = orgpageitm.data();
			pOldPageitm = (PmPageItm *)tmp.toInt();
		}
		if ( pOldPageitm )
		{
			QString imgInThisItm;
			_pPageItm->getContent(imgInThisItm);
			pOldPageitm->setContent(imgInThisItm);

			PageViewItm *srcpreviewitm = (PageViewItm *)pOldPageitm->getPreviewPageViewItm();
			PageViewItm *srceditviewitm = (PageViewItm *)pOldPageitm->getPageViewItm();
			
			if ( srcpreviewitm )
			{
				srcpreviewitm->reload();
			}
			if ( srceditviewitm )
			{
				srceditviewitm->reload();
			}
		}
		_pPageItm->setContent(info);

		PageViewItm *dstpreviewviewitm = (PageViewItm *)_pPageItm->getPreviewPageViewItm();
		PageViewItm *dsteditviewitm = (PageViewItm *)_pPageItm->getPageViewItm();
		dstpreviewviewitm->reload();
		dsteditviewitm->reload();


		PmViewScnen *pScene = this->getScene();
		if ( pScene && pScene->getMainFrame())
		{
			pScene->getMainFrame()->updateLastPhotoPage(_pPageItm->getPage());
		}


		PhotoMaker *pMainFrame = pScene->getMainFrame();
		pMainFrame->updateViews(false);

	}
}

void PageViewItm::setItemBGColor(const QColor& clr)
{
    if( item_bgcolor == clr )
        return;

    item_bgcolor = clr;
    this->update();
}

void PageViewItm::clearItmBgColor()
{
	item_bgcolor = Qt::white;
}

PageBkgrndViewItm::PageBkgrndViewItm(PhotoEditViewScene *scene, PmPhotoPage *photopage):
_editsecne(scene),_photopage(photopage)
{
	this->setAcceptDrops(true);
}

void PageBkgrndViewItm::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
	QString info;
	if (event->mimeData()->hasText())
		info = event->mimeData()->text();

	QString srcloc = event->mimeData()->data("srcloc");
	if ( srcloc != "filelistview" )
	{
		event->ignore();
		//this->setAcceptDrops(false);
	}
	
	if ( info.length()>8 && info.left(7) == LY_PREFIX )
	{
		//this->setAcceptDrops(true);
		event->accept();
	}
	else
	{
		event->ignore();

		//this->setAcceptDrops(false);
	}
}

void PageBkgrndViewItm::dropEvent(QGraphicsSceneDragDropEvent *event)
{
	if ( !this->_photopage )
	{
		return ;
	}

	QString info;
	if (event->mimeData()->hasText())
		info = event->mimeData()->text();

	if ( info.length()>8 && info.left(7) == LY_PREFIX )

	if ( !(info.length()>8 && info.left(7) == LY_PREFIX) )
	{
		return ;
	}
	// layout
	QString layoutname = info.right(info.length()-7);
	this->_updateLayout(layoutname);

}
void PageBkgrndViewItm::_updateLayout(const QString &layoutname)
{
	if ( !_photopage  )
	{
		return ;
	}
	PmPrintPaperPage *paperpage = _photopage->getPaperPage();
	if ( !paperpage )
	{
		return ;
	}

	PhotoMaker *pMainFrame = this->_editsecne->getMainFrame();
	PROJ_PROPS projprops;
	pMainFrame->getDoc()->getProjProps(projprops);

	PHOTO_LAYOUT layout = PPLayoutMgr::getInst().getLayoutFromName(projprops, layoutname);



	// before action, save old state
	PE_UNDOACT_ITEM undoactitm;
	undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETLAYOUT;

	undoactitm.saved.pageedit.peditpaper = paperpage;
	undoactitm.saved.pageedit.psavepaper = pMainFrame->getDoc()->createNewPaper();
	if ( undoactitm.saved.pageedit.psavepaper )
	{
		undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
		undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());

		PmUndoActionStack::getInst().pushAction(undoactitm);
		_editsecne->getMainFrame()->updateUIStatus();
	}

	paperpage->setLayout(_photopage, layout,
		_photopage->isLeft()?PmPrintPaperPage::LF_PG_LAYOUT:PmPrintPaperPage::RT_PG_LAYOUT);

	PmPhotoView *pEditView = paperpage->getEditView();
	if ( pEditView )
	{
		pEditView->reloadPaperPage(paperpage);
	}
	PmPhotoView *pPreviewView = (PmPhotoView*)paperpage->getPreviewView();
	if ( pPreviewView )
	{
		pPreviewView->reloadPaperPage(paperpage);
	}

	// update scene
	pMainFrame->updateViews(false);
}


PreviewBkgrndViewItm::PreviewBkgrndViewItm(PhotoPreviewScene *scene, PhotoMaker *pMainFrame):
_dropping(false), _droppos(0),_previescene(scene), _pMainFrame(pMainFrame)
{
	this->setAcceptDrops(true);
}
PreviewBkgrndViewItm::~PreviewBkgrndViewItm()
{
}

void PreviewBkgrndViewItm::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
	//QGraphicsRectItem::paint(painter, option, widget);
	painter->setBackground(QBrush(QColor(Qt::blue)));
	QRectF rc = this->rect();
	//painter->drawRect(rc);
	//painter->fillRect(rc, Qt::SolidPattern);
	if ( this->_dropping )
	{
		//
		QRectF scrc = this->_previescene->sceneRect();
		QPen pen;
		pen.setColor(Qt::blue);
		pen.setWidth(2);
		painter->setPen(pen);
		painter->drawLine(QPointF(this->_droppos, 0), QPointF(this->_droppos, scrc.height()));
	}
}

void PreviewBkgrndViewItm::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	this->setAcceptDrops(false);
	this->setAcceptDrops(true);
}

void PreviewBkgrndViewItm::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	//this->setAcceptDrops(false);
	//this->setAcceptDrops(true);
}

void PreviewBkgrndViewItm::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
	QPointF pos = event->pos();
	
	QByteArray type = event->mimeData()->data("type");	
	if ( type != "previewpage" )
	{
		event->ignore();
		return ;
	}
	bool ret = false;

	PmPrintPaperPage *beforepaper= NULL, *nextpaper = NULL;
	ret = _previescene->getAround2Papers(event->pos().rx()+1, beforepaper, nextpaper);
	if ( !ret )
	{
		event->ignore();
		return ;
	}
	if ( beforepaper== NULL || nextpaper == NULL )
	{
		event->ignore();
		return ;

	}
	ret = _previescene->getMidPosIn2Paper(event->pos().rx()+1, this->_droppos);
	if ( ret )
	{
		event->accept();
		this->_dropping = true;
		this->update();
		this->_previescene->update();
	}
	else
	{
		event->ignore();
	}



}

void PreviewBkgrndViewItm::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
	this->_droppos = 0;
	this->_dropping = false;
	this->update();
	this->_previescene->update();
}

void PreviewBkgrndViewItm::dropEvent(QGraphicsSceneDragDropEvent *event)
{
	this->_droppos = 0;
	this->_dropping = false;
	//
	PaperPagePreviewItmSet *paperset = (PaperPagePreviewItmSet *)event->mimeData()->data("paper").toLongLong();
	if ( !paperset )
	{
	}
	else
	{
		// get the page which will be the new next
		PmPrintPaperPage *beforepaper=NULL,*nextpaper=NULL; 
		bool ret =  _previescene->getAround2Papers(event->pos().rx(), beforepaper, nextpaper);
		if ( !ret || (!beforepaper && !nextpaper) )
		{
			return ;
		}

		if ( nextpaper )
		{
			PmPrintPaperPage *pmvingpaper = paperset->getPaperpage();
			//PmPrintPaperPage *newpaper = NULL;
			//int index = 0;
			//_pMainFrame->getDoc()->addPrintPaper( nextpaper, true, newpaper, index);

			//PrintPagesPreviewView *preview = _pMainFrame->getPreviewView();
			// remove old page
			//preview->rmPaperPage(pmvingpaper);
			//this->_pMainFrame->getDoc()->getPaperIndex(nextpaper, index);
			//preview->addPaperPage(pmvingpaper, index);

			_pMainFrame->mvPaper(pmvingpaper, nextpaper);

			//_previescene->addPaperPage(newpaper, index, false);

		}

	}
}

//

PreviewPaperLabelViewItm::PreviewPaperLabelViewItm(PaperPagePreviewItmSet *paperpageset, PhotoPreviewScene *scene):
_previescene(scene), _drag(false), _paperpageset(paperpageset),_enableDrag(true)
{
	_orgcursor = cursor();
	QPointF hp = _orgcursor.hotSpot();

	//QBitmap curbitmap = QBitmap::fromImage(QImage(gbires + "curs/switchimg.png"));
	//QBitmap bitMap = curbitmap.createMaskFromColor(QColor(Qt::darkGreen));
	//curbitmap.setMask(bitMap); 
	this->setCursor(QCursor(QPixmap(gbires + "curs/switchpage.png"), 0, 0));
}
PreviewPaperLabelViewItm::~PreviewPaperLabelViewItm()
{
}

void PreviewPaperLabelViewItm::enableDrag(bool enable)
{
	_enableDrag = enable;
	if ( !_enableDrag )
	{
		setCursor(_orgcursor);

	}
	else
	{
		_orgcursor = cursor();
		//QBitmap curbitmap = QBitmap::fromImage(QImage(gbires + "curs/switchimg.png"));
		//QBitmap bitMap = curbitmap.createMaskFromColor(QColor(Qt::darkGreen));
		//curbitmap.setMask(bitMap); 
		this->setCursor(QCursor(QPixmap(gbires + "curs/switchpage.png"), 0, 0));
	}
}

void PreviewPaperLabelViewItm::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
	QPen oldpen = painter->pen();
	QPen pen;
	pen.setColor(Qt::gray);
	painter->setPen(pen);
	//QGraphicsRectItem::paint(painter, option, widget);
	QRectF rect = this->rect();
	painter->drawRect(rect);

	rect.adjust(2,2,-2,-2);
	painter->setPen(oldpen);
	painter->drawText(rect,Qt::AlignHCenter, _cnt);
}

void PreviewPaperLabelViewItm::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
	if ( !_enableDrag )
	{
		return ;
	}
	_drag = true;
}

//! [4]
void PreviewPaperLabelViewItm::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    //setCursor(Qt::OpenHandCursor);
	_drag = false;
}


void PreviewPaperLabelViewItm::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsRectItem::mouseMoveEvent(event);
	
	if ( !_drag )
	{
		return ;
	}


	if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }


    QDrag *drag = new QDrag(event->widget());

	//drag->setPixmap(this->pixmap().scaled(30, 40));
	//drag->setHotSpot(QPoint(15, 30));


    QMimeData *mime = new QMimeData;

	mime->setData("type", "previewpage");	
	QString paperpoint = QString("%1").arg((qlonglong)this->_paperpageset);
	mime->setData("paper", paperpoint.toAscii());
    drag->setMimeData(mime);

	drag->exec();

	//setCursor(Qt::OpenHandCursor);
}


void PreviewPaperLabelViewItm::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{

}

void PreviewPaperLabelViewItm::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{

}

void PreviewPaperLabelViewItm::dropEvent(QGraphicsSceneDragDropEvent *event)
{
}


/*********************************************************/
//PhotoViewItm related
/*********************************************************/
PhotoViewItm::PhotoViewItm(const QPointF &pos,
                           const QSize &size,
                           const QMargins &margin,
                           PhotoEditViewScene *scene,
                           QGraphicsItem *parent)
    :PageViewItm(pos, size, margin, scene,parent),
	_pScene(scene)
{
    img_filepath = QString("");
    pixmap = QPixmap();
    img_lefttop = QPoint();

    b_drag = false;
    setItemType(ImgType);
}

PhotoViewItm::~PhotoViewItm()
{
    //do nth
}

void PhotoViewItm::setImg(const QString &filepath,  QPixmap &savedpixmap)
{
    if( img_filepath == filepath )
        return;


    img_filepath = filepath;

    if(img_filepath.isEmpty())
    {
        //orgpixmap = QPixmap();
        pixmap =  QPixmap();
        return;
    }
    else
    {
        if ( !savedpixmap.isNull() )
        {
            pixmap = savedpixmap;
        }
        else
        {
            pixmap.load(img_filepath);
        }
		int width = pixmap.width();
		// if pictures too big, it will consume too much memory
		if ( width > 1000 )
		{
			pixmap = pixmap.scaledToWidth(1000);
		}
       //pixmap = orgpixmap;
        savedpixmap = pixmap;
    }
}

void PhotoViewItm::reload()
{
    QString imgpath;
    QPixmap *pixmap = NULL;
    QPixmap savedpixmap;


    if ( _pPageItm )
    {
        this->_pPageItm->getContent(imgpath);
        if ( imgpath.length())
        {
            pixmap = _pPageItm->getPixmap();
            if ( pixmap )
            {
                savedpixmap = *pixmap;
            }

        }
    }

    this->setImg(imgpath, savedpixmap);
    _pPageItm->setPixmap(savedpixmap);

	QColor color;
	_pPageItm->getBgColor(color);
	
	if ( color == Qt::white )
	{
		this->clearItmBgColor();
	}
	else
	{
		this->setItemBGColor(color);
	}


	//recalImgOff();

	// update shadow
	if ( !imgpath.length() && color==Qt::white)
	{
		QGraphicsDropShadowEffect* gdse =  (QGraphicsDropShadowEffect*)this->graphicsEffect();
		if( gdse  )
		{
			gdse->setOffset(0, 0);
			gdse->setBlurRadius(0);
		}
	}
	else
	{
		bool shadow = this->getItemShadow();
		if ( shadow )
		{
			this->setShadow(false);
			this->setShadow(true);
		}
	}


    this->resize();

	if ( imgpath.length() )
	{
		_orgcur = cursor();
		setCursor(Qt::OpenHandCursor);
	}
	else
	{
		setCursor(_orgcur);
	}
}


void PhotoViewItm::_updateLayout(const QString &layoutname)
{
	PmPhotoPage *pPage = _pPageItm->getPage();
	PmPrintPaperPage *pPaperPage = pPage->getPaperPage();

	PmViewScnen *pScene = this->getScene();
	if ( !pScene )
	{
		return ;
	}
	if ( pPage  && pPaperPage )
	{
		PhotoMaker *pMainFrame = pScene->getMainFrame();
		PROJ_PROPS projprops;
		pMainFrame->getDoc()->getProjProps(projprops);

		PHOTO_LAYOUT layout = PPLayoutMgr::getInst().getLayoutFromName(projprops, layoutname);



		// before action, save old state
		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETLAYOUT;

		undoactitm.saved.pageedit.peditpaper = this->getPmPageItm()->getPage()->getPaperPage();
		undoactitm.saved.pageedit.psavepaper = pScene->getMainFrame()->getDoc()->createNewPaper();
		if ( undoactitm.saved.pageedit.psavepaper )
		{
			undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
			undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());

			PmUndoActionStack::getInst().pushAction(undoactitm);
			pScene->getMainFrame()->updateUIStatus();
		}


		pPaperPage->setLayout(pPage, layout,
			pPage->isLeft()?PmPrintPaperPage::LF_PG_LAYOUT:PmPrintPaperPage::RT_PG_LAYOUT);

		PmPhotoView *pEditView = pPaperPage->getEditView();
		if ( pEditView )
		{
			pEditView->reloadPaperPage(pPaperPage);
		}
		PmPhotoView *pPreviewView = (PmPhotoView*)pPaperPage->getPreviewView();
		if ( pPreviewView )
		{
			pPreviewView->reloadPaperPage(pPaperPage);
		}

		// update scene
		pMainFrame->updateViews(false);
	}	
}
  
bool PhotoViewItm::_getScale(qreal &scale)
{
	QSize viewSize = this->getItemSize();

	const QPixmap &orgpixmap = *_pPageItm->getPixmap();

	QSize imgSize = QSize(orgpixmap.width(), orgpixmap.height());

    int win_w = viewSize.width();
    int win_h = viewSize.height();


    int imgwidth = imgSize.width();
    int imgheight = imgSize.height();

    if ( !(imgwidth && imgheight) )
    {
            scale = 1;
            return false;
    }

    if ( imgheight*1.0/imgwidth > win_h*1.0/win_w)
    {
            // full fill the width
            scale = win_w*1.0/imgwidth;
    }
    else
    {
            // full fill the height
            scale = win_h*1.0/imgheight;
    }

    return true;
}


void PhotoViewItm::_getImgDefOff(qreal &xoff,qreal &yoff)
{

	int win_w = getItemSize().width()-getItemMargin().left()-getItemMargin().right();
	int win_h = getItemSize().height()-getItemMargin().top()-getItemMargin().bottom();

	qreal defscale = 0;
	_getScale(defscale);

	xoff = yoff = 0;
	const QPixmap &orgpixmap = *_pPageItm->getPixmap();

	if ( defscale * orgpixmap.height() > win_h )
	{
		// height is longer than window
		qreal imgheight = orgpixmap.height();
		qreal yoffinwin = (orgpixmap.height()*defscale-win_h)/2;
		qreal yoffinpixmap = 0;
		yoffinpixmap  = yoffinwin/defscale ;
		yoff = yoffinpixmap;

	}
	else
	{
		// width is longer than window
		qreal xoffinwin = (orgpixmap.width()*defscale-win_w)/2;
		qreal xoffinpixmap = 0;
		xoffinpixmap  = xoffinwin/defscale ;
		xoff = xoffinpixmap;
	}
}

void PhotoViewItm::_getPixmapOffInViewItm(int &xoff,int &yoff)
{
		QPointF lefttop;
		_pPageItm->getImgLeftTop(lefttop);

		qreal defscale, scaleratio;
		this->_getScale(defscale);
		_pPageItm->getZoom(scaleratio);

		const QPixmap &orgpixmap = *_pPageItm->getPixmap();
		xoff = lefttop.x()*orgpixmap.width() * defscale * scaleratio;
		yoff = lefttop.y() * orgpixmap.height() * defscale * scaleratio;

}


void PhotoViewItm::_updateImg(const QString &imgpath)
{
	QString currentimgpath;
	_pPageItm->getContent(currentimgpath);

	// 
	if ( currentimgpath.contains("prj") )
	{
		//
	}

    PmViewScnen *pScene = getScene();
	if ( !pScene )
	{
		return ;
	}

	PE_UNDOACT_ITEM undoactitm;
	undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;
	undoactitm.saved.pageedit.peditpaper = this->getPmPageItm()->getPage()->getPaperPage();
	undoactitm.saved.pageedit.psavepaper = pScene->getMainFrame()->getDoc()->createNewPaper();
	if ( undoactitm.saved.pageedit.psavepaper )
	{
		undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
		undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());

		PmUndoActionStack::getInst().pushAction(undoactitm);

		pScene->getMainFrame()->updateUIStatus();

	}


	QString path = imgpath;
	QString savedpath;

	//_cursor = Qt::BusyCursor;


	QObject *parent = pScene->parent();
	PmPhotoView *pEditView = (PmPhotoView *)parent;
	//this->setCursor(Qt::BusyCursor);

	_pPageItm->setBgColor(Qt::white); // clear background
	_pPageItm->setContent(path);


	//_cursor = Qt::ArrowCursor;
	//this->setCursor(_cursor);

	QPixmap savepixmap;
	this->setImg(path, savepixmap);
	_pPageItm->setPixmap(savepixmap);

	// calculate the scale 

	QPointF pos = this->pos();

	PageViewItm *editviewitm = (PageViewItm *)_pPageItm->getPageViewItm();
	if ( editviewitm )
	{
		editviewitm->reload();
		PmViewScnen *editviewscene = editviewitm->getScene();
		if ( editviewscene )
		{
			editviewscene->update();
		}
	}

	PageViewItm *previewitm = (PageViewItm *)_pPageItm->getPreviewPageViewItm();
	//previewitm->recalImgOff();
	if ( previewitm )
	{
		previewitm->reload();
		PmViewScnen *previewscene = previewitm->getScene();
		if ( previewscene )
		{
			previewscene->update();
		}
	}

}

bool PhotoViewItm::getDpi(int &dpi)
{
	//
	QSize viewSize = this->getItemSize();
	QString imgfilepath ;
	_pPageItm->getContent(imgfilepath);
	QImage img(imgfilepath);
	const QPixmap &orgpixmap = *_pPageItm->getPixmap();

	QSize imgSize = QSize(orgpixmap.width(), orgpixmap.height());

    int win_w = viewSize.width();
    int win_h = viewSize.height();

	qreal defscale = 0;
	this->_getScale(defscale);
	int dpiy = 0;
	int dpix =0;
	if ( fabs(imgSize.height() - defscale * win_h) < 0.01 )
	{
		//scale according height


		int dotsinmeter = img.dotsPerMeterX();
		dpi = dotsinmeter *  0.0254;


		//dpi = img.physicalDpiY();
		dpix = img.physicalDpiX();
	}
	else
	{
		int dotsinmeter = img.dotsPerMeterX();
		dpi = dotsinmeter *  0.0254;

		dpiy = img.logicalDpiY();
	}
	return true;
}


void PhotoViewItm::_updateColor(const QString &colorname)
{


    PmViewScnen *pScene = getScene();
	if ( !pScene )
	{
		return ;
	}

	// before action, save old state
	PE_UNDOACT_ITEM undoactitm;
	undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SETIMG;

	undoactitm.saved.pageedit.peditpaper = this->getPmPageItm()->getPage()->getPaperPage();
	undoactitm.saved.pageedit.psavepaper = pScene->getMainFrame()->getDoc()->createNewPaper();
	if ( undoactitm.saved.pageedit.psavepaper )
	{
		undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
		undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());

		PmUndoActionStack::getInst().pushAction(undoactitm);
		pScene->getMainFrame()->updateUIStatus();
	}

	QColor color;
	if ( ColorMgr::getColor(colorname, color) )
	{
		this->setItemBGColor(color);
	}
	_pPageItm->setContent(""); // clear img path
	this->_pPageItm->setBgColor(color);

	PhotoViewItm *editviewitm = (PhotoViewItm *)_pPageItm->getPageViewItm();
	PhotoViewItm *previewitm = (PhotoViewItm *)_pPageItm->getPreviewPageViewItm();
	if ( editviewitm )
	{
		editviewitm->reload();
		if ( editviewitm->getScene() )
		{
			editviewitm->getScene()->update();
			editviewitm->getScene()->getMainFrame()->updateEditPaneInfo();
		}
	}
	if ( previewitm )
	{
		previewitm->reload();
		if ( previewitm->getScene() )
		{
			previewitm->getScene()->update();
		}
	}


	//this->_pBottomCtrlPane->updateEditPaneInfo();

	//PmViewScnen *pscene = getScene();
	//if ( pscene
	//PhotoMaker *pMainFrame = _pScene->getMainFrame();
	//pMainFrame->updateViews(false);

	//previewitm->getScene()->update();
}
extern QApplication *g_app ;

void PhotoViewItm::setContent(const QString &cnt)
{
	//
	QString info = cnt;
	if ( info.length() <= 0 )
	{
		info = this->_cnt;
	}
	

	PmViewScnen *pscene = this->getScene();
	// check if
	// "layout/"
	if ( info.length()>8 && info.left(7) == LY_PREFIX )
	{
		// layout
		QString layoutname = info.right(info.length()-7);

		// layout update will reload all items, this view will will be destroied, first restore the cursor
		this->setCursor(Qt::OpenHandCursor);
		//g_app->processEvents();
		// update latest index
		PmPhotoPage *photopage = _pPageItm->getPage();
		this->_updateLayout(layoutname);

		if ( pscene )
		{
			pscene->getMainFrame()->updateLastPhotoPage(photopage);
		}

	}
	else if ( info.length()>strlen(COLOR_PREFIX) && info.left(strlen(COLOR_PREFIX)) == COLOR_PREFIX )  
	{
		// set color
		QString colorname = info.right(info.length()-strlen(COLOR_PREFIX));
		_updateColor(colorname);

		// check if this is panorama item, 
		_updatePanoramaPair();

		// update latest index
		if ( pscene )
		{
			pscene->getMainFrame()->updateLastPhotoPage(_pPageItm->getPage());
			//_pScene->updateLastPhotoPage(this->_pPageItm->getPage());
		}
	}
	else
	{
		// update image
		_updateImg(info);

		// check if this is panorama item, 
		_updatePanoramaPair();

		// update latest index
		if ( pscene )
		{
			pscene->getMainFrame()->updateLastPhotoPage(_pPageItm->getPage());
		}
	}

}


void PhotoViewItm::scale(qreal ratio)
{
    if( ratio <= 1.0 )
        return;


    this->_pPageItm->setZoom(ratio);

    this->resize();

    _updatePanoramaPair();
}

bool PhotoViewItm::_isPanoramaLayout()
{
	PHOTO_LAYOUT layout = this->_pPageItm->getPage()->getLayout();
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

bool PhotoViewItm::selectPanoramaPair(bool selected)
{
	if ( !_isPanoramaLayout() )
	{
		return false;
	}

	PmPrintPaperPage *paper = this->getPmPageItm()->getPage()->getPaperPage();
	if ( !paper )
	{
		return false;
	}
	QList<PmPhotoPage *>  photopages;
	paper->getPhotoPages(photopages);
	if ( photopages.size() != 2 )
	{
		return false;
	}
	PmPhotoPage *leftpage, *rightpage;
	leftpage = photopages.first();
	rightpage = photopages.last();

	PmPhotoPage *dstpage = NULL;
	if ( getPmPageItm()->getPage() == leftpage )
	{
		dstpage = rightpage;
	}
	else
	{
		dstpage = leftpage;
	}

	QList<PmPageItm *> dstitmlst;
	PmPageItm *dstitm;
	dstpage->getPicItms(dstitmlst);
	if ( dstitmlst.size() != 1)
	{
		return false;
	}
	dstitm = dstitmlst[0];
	PhotoViewItm *dstviewitm = (PhotoViewItm *)dstitm->getPageViewItm();
	dstviewitm->setSelected(selected);
	if ( selected )
	{
		dstviewitm->setZValue(3);
	}
	else
	{
		dstviewitm->setZValue(2);
	}
	dstviewitm->update();
	return true;
}

bool PhotoViewItm::_updatePanoramaPair()
{
	if ( !_isPanoramaLayout() )
	{
		return false;
	}

	PmPhotoPage *dstpage = NULL;
	this->_pPageItm->getPage()->getPaperPage()->updatePanoramaPages(_pPageItm->getPage(), dstpage);
	if ( dstpage )
	{
		//
		QList<PmPageItm *> itmlst;
		dstpage->getPicItms(itmlst);
		if ( itmlst.size() > 0 && itmlst[0] )
		{
			PageViewItm *dstviewitm = (PageViewItm*)itmlst[0]->getPageViewItm();
			if ( dstviewitm )
			{
				dstviewitm->reload();
			}
			PageViewItm *dstpreviewitm = (PageViewItm*)itmlst[0]->getPreviewPageViewItm();
			if ( dstpreviewitm )
			{
				dstpreviewitm->reload();
			}
			//dstviewitm->update();
		}
	}

	return true;

}


void PhotoViewItm::rotate(int  angel)
{
	QMatrix matrix;

	matrix.rotate(angel);


	int oldangel = 0;
	_pPageItm->getRotate(oldangel);
	angel += oldangel;
	this->_pPageItm->setRotate(angel);

	QString imgpath;
	if ( _pPageItm && _pPageItm->getPixmap())
	{
		const QPixmap &orgpixmap = *_pPageItm->getPixmap();
		pixmap = orgpixmap.transformed(matrix);
	}
	//this->setImg(imgpath, pixmap);
	//orgpixmap = pixmap;

	_pPageItm->setPixmap(pixmap);

	PhotoViewItm *previewitm = (PhotoViewItm *) _pPageItm->getPreviewPageViewItm();
	previewitm->reload();

	this->resize();

	_updatePanoramaPair();
    //this->update();
}

bool PhotoViewItm::_saveNewImgFile(const QImage &img, QString &path)
{
	// find a file name
	QString newfilepath = path.left(path.length()-4);
	QString ext = path.right(4);
	int i=0; 
	QString checkfile;
	for ( ; i<100; i++ )
	{
		checkfile = QString("%1_%2").arg(newfilepath).arg(i);
		checkfile += ext;
		QFile file;
		if ( !file.exists(checkfile) )
		{
			break;
		}
	}
	if ( i < 100 )
	{
		newfilepath = checkfile;
	}
	else
	{
		// fail to save the file
		return false;
	}

	bool ret = img.save(newfilepath);
	if ( ret )
	{
		path = newfilepath;
	}

	return ret;
}

void PhotoViewItm::setHSL()
{
	if ( !_pPageItm->getPixmap() )
	{
		return ;
	}
	const QPixmap &orgpixmap = *_pPageItm->getPixmap();

    PhotoHSLEditWidget hsl_widget(orgpixmap);
    hsl_widget.exec();

    if( !hsl_widget.isOKClick() )
        return;

    QImage tmp_img = pixmap.toImage();
    HSL hsl = hsl_widget.getHSL();
    bool ret = PhotoHSLEditWidget::changeImageHSL(&tmp_img, hsl);
    if(ret == false)
        return;

	QString filepath;
	_pPageItm->getContent(filepath);
	if ( _saveNewImgFile(tmp_img, filepath) )
	{
		_pPageItm->setContent(filepath);
	}
	else
	{
		filepath = "";
	}

	PE_UNDOACT_ITEM undoactitm;
	undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_EDITIMG;
	undoactitm.saved.imgedit.pphotoeditpaper = this->getPmPageItm()->getPage()->getPaperPage();
	undoactitm.saved.imgedit.pphotoeditsavepaper = this->_pScene->getMainFrame()->getDoc()->createNewPaper();
	if ( undoactitm.saved.imgedit.pphotoeditsavepaper )
	{
		undoactitm.saved.imgedit.pphotoeditsavepaper->copy(*undoactitm.saved.imgedit.pphotoeditpaper);
		undoactitm.saved.imgedit.pphotoeditsavepaper->setborder(undoactitm.saved.imgedit.pphotoeditpaper->getborder());
		undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
		PmUndoActionStack::getInst().pushAction(undoactitm);
		this->_pScene->getMainFrame()->updateUIStatus();

	}
	//

    pixmap = QPixmap::fromImage(tmp_img);
    //orgpixmap = pixmap;
    _pPageItm->setPixmap(pixmap);


    this->update();
    _updatePanoramaPair();

	PageViewItm *previewitm = (PageViewItm*)_pPageItm->getPreviewPageViewItm();
	if ( previewitm )
	{
		previewitm->reload();
	}
}

void PhotoViewItm::setBWC()
{
	if ( !_pPageItm->getPixmap() )
	{
		return ;
	}
	const QPixmap &orgpixmap = *_pPageItm->getPixmap();
    PhotoBWCEditWidget bwc_widget(orgpixmap);
    bwc_widget.exec();

    if( !bwc_widget.isOKClick() )
        return;

    QImage tmp_img = pixmap.toImage();
    BWC bwc = bwc_widget.getBWC();
    bool ret = PhotoBWCEditWidget::changeImageBWC(&tmp_img, bwc);
    if(ret == false)
        return;

	QString filepath;
	_pPageItm->getContent(filepath);
	if ( _saveNewImgFile(tmp_img, filepath) )
	{
		_pPageItm->setContent(filepath);
	}
	else
	{
		filepath = "";
	}

	// save the action for undo
	PE_UNDOACT_ITEM undoactitm;
	undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_EDITIMG;
	undoactitm.saved.imgedit.pphotoeditpaper = this->getPmPageItm()->getPage()->getPaperPage();
	undoactitm.saved.imgedit.pphotoeditsavepaper = this->_pScene->getMainFrame()->getDoc()->createNewPaper();
	if ( undoactitm.saved.imgedit.pphotoeditsavepaper )
	{
		undoactitm.saved.imgedit.pphotoeditsavepaper->copy(*undoactitm.saved.imgedit.pphotoeditpaper);
		undoactitm.saved.imgedit.pphotoeditsavepaper->setborder(undoactitm.saved.imgedit.pphotoeditpaper->getborder());
		undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
		PmUndoActionStack::getInst().pushAction(undoactitm);
		this->_pScene->getMainFrame()->updateUIStatus();
	}


    pixmap = QPixmap::fromImage(tmp_img);
    //orgpixmap = pixmap;
    _pPageItm->setPixmap(pixmap);

    this->update();
    _updatePanoramaPair();

	PageViewItm *previewitm = (PageViewItm*)_pPageItm->getPreviewPageViewItm();
	if ( previewitm )
	{
		previewitm->reload();
	}
}

void PhotoViewItm::setLCIG()
{
	if ( !_pPageItm->getPixmap() )
	{
		return ;
	}
	const QPixmap &orgpixmap = *_pPageItm->getPixmap();

    PhotoLCIGEditWidget lcig_widget(orgpixmap);
    lcig_widget.exec();

    if( !lcig_widget.isOKClick() )
        return;

    QImage tmp_img = pixmap.toImage();
    LCIG lcig = lcig_widget.getLCIG();
    bool ret = PhotoLCIGEditWidget::changeImageLCIG(&tmp_img, lcig);
    if(ret == false)
        return;

	QString filepath;
	_pPageItm->getContent(filepath);
	if ( _saveNewImgFile(tmp_img, filepath) )
	{
		_pPageItm->setContent(filepath);
	}
	else
	{
		filepath = "";
	}


	PE_UNDOACT_ITEM undoactitm;
	undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_EDITIMG;
	undoactitm.saved.imgedit.pphotoeditpaper = this->getPmPageItm()->getPage()->getPaperPage();
	undoactitm.saved.imgedit.pphotoeditsavepaper = this->_pScene->getMainFrame()->getDoc()->createNewPaper();
	if ( undoactitm.saved.imgedit.pphotoeditsavepaper )
	{
		undoactitm.saved.imgedit.pphotoeditsavepaper->copy(*undoactitm.saved.imgedit.pphotoeditpaper);
		undoactitm.saved.imgedit.pphotoeditsavepaper->setborder(undoactitm.saved.imgedit.pphotoeditpaper->getborder());

		PmUndoActionStack::getInst().pushAction(undoactitm);
		this->_pScene->getMainFrame()->updateUIStatus();

	}

    pixmap = QPixmap::fromImage(tmp_img);
    //orgpixmap = pixmap;
    _pPageItm->setPixmap(pixmap);

    this->update();
    _updatePanoramaPair();

	PageViewItm *previewitm = (PageViewItm*)_pPageItm->getPreviewPageViewItm();
	if ( previewitm )
	{
		previewitm->reload();
	}

}

void PhotoViewItm::setRE()
{
	if ( !_pPageItm->getPixmap() )
	{
		return ;
	}

    PhotoRedeyeEditWidget re_widget(pixmap);
    re_widget.exec();

    if( !re_widget.isOKClick() )
        return;

	QImage tmp_img = re_widget.getImage();

	QString filepath;
	_pPageItm->getContent(filepath);
	if ( _saveNewImgFile(tmp_img, filepath) )
	{
		_pPageItm->setContent(filepath);
	}
	else
	{
		filepath = "";
	}

	PE_UNDOACT_ITEM undoactitm;
	undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_EDITIMG;
	undoactitm.saved.imgedit.pphotoeditpaper = this->getPmPageItm()->getPage()->getPaperPage();
	undoactitm.saved.imgedit.pphotoeditsavepaper = this->_pScene->getMainFrame()->getDoc()->createNewPaper();
	if ( undoactitm.saved.imgedit.pphotoeditsavepaper )
	{
		undoactitm.saved.imgedit.pphotoeditsavepaper->copy(*undoactitm.saved.imgedit.pphotoeditpaper);
		undoactitm.saved.imgedit.pphotoeditsavepaper->setborder(undoactitm.saved.imgedit.pphotoeditpaper->getborder());
		undoactitm.saved.imgedit.pupdatedphotopath = new QString(filepath);
		PmUndoActionStack::getInst().pushAction(undoactitm);
		this->_pScene->getMainFrame()->updateUIStatus();
	}
	//

	pixmap = QPixmap::fromImage(tmp_img);
	//orgpixmap = pixmap;
	_pPageItm->setPixmap(pixmap);


	this->update();
	_updatePanoramaPair();

	PageViewItm *previewitm = (PageViewItm*)_pPageItm->getPreviewPageViewItm();
	if ( previewitm )
	{
		previewitm->reload();
	}
}

void PhotoViewItm::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


    if( pixmap.isNull() )
    {
        PageViewItm::paint(painter, option, widget);
    }
    else
    {
        //draw the background
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(Qt::white));
        painter->drawRect(QRect(0,0,getItemSize().width(),getItemSize().height()));


        //draw the boundary
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(2*NORM_LINE);
        if( this->isSelected() )
            pen.setBrush(Qt::blue);
        else
            pen.setBrush(Qt::lightGray);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);

        int win_w = getItemSize().width()-getItemMargin().left()-getItemMargin().right();
        int win_h = getItemSize().height()-getItemMargin().top()-getItemMargin().bottom();
        QRect rect(getItemMargin().left(), getItemMargin().top(), win_w, win_h);
        

         //draw the image
        int img_w = pixmap.width();
        int img_h = pixmap.height();
        if ( img_w < win_w )
        {
            img_w = win_w;
        }
        if ( img_h < win_h )
        {
            img_h = win_h;
        }

		qreal scaleratio;
		_pPageItm->getZoom(scaleratio);

		qreal defscale = 0;
		_getScale(defscale);

		QPointF lefttop;
		_pPageItm->getImgLeftTop(lefttop);

		const QPixmap &orgpixmap = *_pPageItm->getPixmap();

		if ( fabs(lefttop.rx() - (-1)) < 0.0001 && fabs(lefttop.ry() - (-1)) < 0.0001 )
		{
			qreal xoffinpixmap, yoffinpixmap;
			_getImgDefOff(xoffinpixmap, yoffinpixmap);
			_pPageItm->setImgLeftTop(QPointF(xoffinpixmap/orgpixmap.width(), yoffinpixmap/orgpixmap.height()));
			//img_lefttop.setX(xoffinpixmap);
			//img_lefttop.setY(yoffinpixmap);
			//_pPageItm->setImgLeftTop(img_lefttop);
			_pPageItm->getImgLeftTop(lefttop);

			// calculate current off in view
			img_lefttop.setX(xoffinpixmap*defscale*scaleratio);
			img_lefttop.setY(yoffinpixmap*defscale*scaleratio);	
		}

		int imgxoff; // = lefttop.x()*orgpixmap.width() * defscale * scaleratio;
		int imgyoff; // = lefttop.y() * orgpixmap.height() * defscale * scaleratio;
		_getPixmapOffInViewItm(imgxoff, imgyoff);


        QRect rect2(imgxoff, imgyoff, win_w, win_h);
        painter->drawPixmap( rect, pixmap, rect2 );
        if ( isSelected() )
        {
            painter->drawRect(rect);
        }

    }
}

void PhotoViewItm::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //this->setSelected(!this->isSelected());
    PhotoEditViewScene *pEditScene = dynamic_cast<PhotoEditViewScene *>(getScene());
	if ( !pEditScene )
	{
		return ;
	}
    pEditScene->selectItm(this, NULL);

    if(event->button() != Qt::LeftButton)
    {
        b_drag = false;
        return;
    }
    //this->setSelected(!this->isSelected());
    setCursor(Qt::ClosedHandCursor);


    this->scene()->update();
    b_drag = true;
}

void PhotoViewItm::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    static QPointF d;

    if( !b_drag )
        return;

    QPointF dd = event->pos() - event->lastPos();
    d += dd;

	const QPixmap &orgpixmap = *_pPageItm->getPixmap();

    if( qAbs(d.x()) >= MOUSEMV_THRES || qAbs(d.y()) >= MOUSEMV_THRES )
    {
        int img_w = pixmap.width();
        int img_h = pixmap.height();
        int win_w = getItemSize().width()/*-getItemMargin().left()-getItemMargin().right()*/;
        int win_h = getItemSize().height()/*-getItemMargin().top()-getItemMargin().bottom()*/;

        /*img_w and img_h must be >= win_w and win_h, because of scaleImage function we called early*/
		qreal defscale, scaleratio;
		this->_getScale(defscale);
		this->_pPageItm->getZoom(scaleratio);
		QPointF lefttop;
		_pPageItm->getImgLeftTop(lefttop);

		// height is exceed view item
		// do not move x
		qreal maxy = (orgpixmap.height() * defscale * scaleratio - win_h)/(orgpixmap.height() * defscale * scaleratio);
		qreal miny = 0;
		qreal newy = lefttop.ry() - d.y() * 1.0 /defscale/scaleratio  / orgpixmap.height();
		if ( newy<miny)
		{
			newy = miny;
		}
		if ( newy>maxy )
		{
			newy = maxy;
		}
		lefttop.setY(newy);


		qreal viewwidth = win_w;
		if ( _isPanoramaLayout() )
		{
			viewwidth *= 2;
		}

		qreal maxx = (orgpixmap.width() * defscale * scaleratio - viewwidth)/(orgpixmap.width() * defscale * scaleratio);
		qreal minx = 0;
		qreal newx = lefttop.rx() - d.x() * 1.0 /defscale/scaleratio  / orgpixmap.width();
		if ( newx<minx)
		{
			newx = 0.001;
		}
		if ( newx>maxx )
		{
			newx = maxx;
		}
		lefttop.setX(newx);



		_pPageItm->setImgLeftTop(lefttop);
		/*
        int new_x = img_lefttop.x() - d.x();
        if( new_x < 0 )
            img_lefttop.setX(0);
        else if( new_x > (img_w-win_w))
            img_lefttop.setX(img_w-win_w);
        else
            img_lefttop.setX(new_x);

        int new_y = img_lefttop.y() - d.y();
        if( new_y < 0 )
            img_lefttop.setY(0);
        else if( new_y > (img_h-win_h))
            img_lefttop.setY(img_h-win_h);
        else
            img_lefttop.setY(new_y);

		//
		// update pageitm
		// save the position
		int x = img_lefttop.x();
		int y = img_lefttop.y();

		// calculate the scale
		qreal defscale = 0;
		_getScale( defscale);
		qreal scaleratio = 1;
		_pPageItm->getZoom(scaleratio);

		int xInOrgPixmap = x*1.0/(defscale*scaleratio);
		int yInOrgPixmap = y*1.0/(defscale*scaleratio);
		qreal xoff = 0, yoff = 0;
		xoff = xInOrgPixmap*1.0/orgpixmap.width();
		yoff = yInOrgPixmap * 1.0 /orgpixmap.height();

		this->_pPageItm->setImgLeftTop(QPointF(xoff, yoff));
		*/

        d = QPointF();
        this->update();
        _updatePanoramaPair();
		scene()->update();
    }
}

void PhotoViewItm::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    b_drag = false;

    QString imgpath;

	if ( _pPageItm )
    {
        this->_pPageItm->getContent(imgpath);
    }

	if ( imgpath.length() )
	{
		_orgcur = cursor();
		setCursor(Qt::OpenHandCursor);
	}
	else
	{
		setCursor(_orgcur);
	}
}


void PhotoViewItm::resize(bool update)
{
    QPointF lefttop;
    if ( !_pPageItm )
    {
        return ;
    }
    _pPageItm->getImgLeftTop(lefttop);

	const QPixmap &orgpixmap = *_pPageItm->getPixmap();

    // get current scale
    int win_w = getItemSize().width()-getItemMargin().left()-getItemMargin().right();
    int win_h = getItemSize().height()-getItemMargin().top()-getItemMargin().bottom();

    qreal defscale;
    _getScale( defscale);
    qreal scaleratio = 1;
    _pPageItm->getZoom(scaleratio);

    int imgxoff = lefttop.x()*orgpixmap.width() * defscale * scaleratio;
    int imgyoff = lefttop.y() * orgpixmap.height() * defscale * scaleratio;

    this->img_lefttop = QPoint(imgxoff,imgyoff);

    int showimgwidth = orgpixmap.width()*defscale*scaleratio;
    int showimgheight = orgpixmap.height()*defscale*scaleratio;
    pixmap = orgpixmap.scaled(QSize(showimgwidth, showimgheight));


    if ( update )
        this->update();
}

/*************************PhotoPanoViewItm*************************/
PhotoPanoViewItm::PhotoPanoViewItm(const QPointF& pos,
               const QSize& size,
               const QMargins& margin,
               PanoType type,
               PhotoEditViewScene *scene,
               QGraphicsItem * parent)
    :PhotoViewItm(pos,size,margin,scene,parent)
{
    panotype = type;
}

PhotoPanoViewItm::~PhotoPanoViewItm()
{

}

void PhotoPanoViewItm::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    PhotoViewItm::paint(painter, option, widget);
}


bool PhotoPanoViewItm::_getScale(qreal &scale)
{
	if ( !_pPageItm->getPixmap() )
	{
		return false;
	}
	const QPixmap &orgpixmap = *_pPageItm->getPixmap();

	QSize viewSize = this->getItemSize();
	QSize imgSize = QSize(orgpixmap.width(), orgpixmap.height());

    int win_w = viewSize.width();
    win_w *= 2;
    int win_h = viewSize.height();

    int imgwidth = imgSize.width();
    int imgheight = imgSize.height();

    if ( !(imgwidth && imgheight) )
    {
            scale = 1;
            return false;
    }

    if ( imgheight*1.0/imgwidth > win_h*1.0/win_w)
    {
            // full fill the width
            scale = win_w*1.0/imgwidth;
    }
    else
    {
            // full fill the height
            scale = win_h*1.0/imgheight;
    }

    return true;
}

void PhotoPanoViewItm::_getImgDefOff(qreal &xoff,qreal &yoff)
{
    int win_w = getItemSize().width()/*-getItemMargin().left()-getItemMargin().right()*/;
    int win_h = getItemSize().height()/*-getItemMargin().top()-getItemMargin().bottom()*/;

    qreal defscale = 0;
    _getScale( defscale);

	if ( !_pPageItm->getPixmap() )
	{
		return ;
	}
	const QPixmap &orgpixmap = *_pPageItm->getPixmap();

	int orgimgheight = orgpixmap.height();
	int orgimgwidth = orgpixmap.width();

    if ( fabs(defscale * orgimgheight - win_h)<1 )
    {
        // height is longer than window
        qreal yoffinwin = (orgimgheight*defscale-win_h)/2;
        qreal yoffinpixmap = 0;
        yoffinpixmap  = yoffinwin/defscale ;
        yoff = yoffinpixmap;

		//if( panotype == Left_Pano )
		{
			xoff  = 0;
		}
		//else if( panotype == Right_Pano )
		//{
		//	xoff = win_w*1.0/defscale;
		//}

    }
    else
    {
            // width is longer than window
            qreal xoffinwin = (orgimgwidth*defscale-win_w*2)/2;
			xoffinwin /= defscale;
			//if( panotype == Left_Pano )
			{
				xoff  = xoffinwin;
			}
			//else if( panotype == Right_Pano )
			//{
			//	xoff = win_w*1.0/defscale+xoffinwin;
			//}

            yoff = 0;
    }
}


void PhotoPanoViewItm::_getPixmapOffInViewItm(int &xoff,int &yoff)
{
	PhotoViewItm::_getPixmapOffInViewItm(xoff, yoff);
	if ( panotype == Left_Pano )
	{
		//
		//PhotoViewItm::_getPixmapOffInViewItm(xoff, yoff);
	}
	else
	{
		QSize viewitmsize = this->getItemSize();
		xoff+=viewitmsize.width();
	}
}


/*************************PhotoPreviewItm*************************/

PhotoPreviewItm::PhotoPreviewItm(const QPointF& pos,
                   const QSize& size,
                   const QMargins& margin,
                   PhotoPreviewScene *scene,
                   QGraphicsItem * parent): 
PhotoViewItm(pos, size, margin, NULL, parent),
	_pPaperPagePreviwItm(NULL), _pScene(scene)
{
	    img_filepath = QString("");
    pixmap = QPixmap();
    img_lefttop = QPoint();

    b_drag = false;
    setItemType(ImgType);
}

PhotoPreviewItm::~PhotoPreviewItm()
{
}

void PhotoPreviewItm::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	//PhotoViewItm::mouseReleaseEvent(event);
	if ( event->button() == Qt::LeftButton )
	{
		if ( _pPaperPagePreviwItm )
		{
			//
			_pScene->select(_pPaperPagePreviwItm);
		}
	}
}

void PhotoPreviewItm::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

	if ( event->button() == Qt::RightButton )
	{
		//
		if ( _pPaperPagePreviwItm )
		{
			//
			_pScene->selectRightBtnPaper(_pPaperPagePreviwItm);
		}
	}
	//QGraphicsItem::mousePressEvent(event);
}
void PhotoPreviewItm::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	//QGraphicsPixmapItem::mouseMoveEvent(event);

	if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }

	PmPageItm *_pPageItm = this->_pPageItm;
	QString imgpath;
	_pPageItm->getContent(imgpath);
	QColor color;
	_pPageItm->getBgColor(color);
	if ( imgpath.length() <= 0 && (!color.isValid()||color==Qt::white))
	{
		return ;
	}


    QDrag *drag = new QDrag(event->widget());
	drag->setPixmap(this->pixmap.scaled(30, 40));
	drag->setHotSpot(QPoint(15, 30));
	   

    QMimeData *mime = new QMimeData;
	mime->setText(imgpath);
	QByteArray orgpageitm;
	QString tmp;
	tmp = QString("%1").arg((ulong)_pPageItm);
	orgpageitm.append(tmp);

	mime->setData("orginalpageitm", orgpageitm);
	mime->setData("srcloc", "preview");

    drag->setMimeData(mime);

	drag->exec();

	//setCursor(Qt::OpenHandCursor);
}

void PhotoPreviewItm::dropEvent(QGraphicsSceneDragDropEvent *event)
{
	PhotoMaker *pMainFrame = _pScene->getMainFrame();

	/// update path
	QString info;
	if (event->mimeData()->hasText())
		info = event->mimeData()->text();
	//img_filepath = path;

	if ( !_pPageItm )
	{
		return ;
	}
	QString srcloc = event->mimeData()->data("srcloc");
	if ( srcloc == "filelistview" )
	{
		PhotoViewItm::dropEvent(event);
	}
	else if ( srcloc == "preview" )
	{
		PmPageItm *pSrcPageitm = NULL;
		QByteArray orgpageitm;
		QString tmp;
		if ( event->mimeData()->hasFormat("orginalpageitm") )
		{
			orgpageitm = event->mimeData()->data("orginalpageitm");
			tmp = orgpageitm.data();
			pSrcPageitm = (PmPageItm *)tmp.toInt();
		}
		PmPageItm *dstPageItm = this->_pPageItm;
		if ( dstPageItm == pSrcPageitm ||  dstPageItm == NULL || pSrcPageitm == NULL )
		{
			return ;
		}


		PmViewScnen *pScene = getScene();
		if ( !pScene )
		{
			return ;
		}
		// save for undo actions
		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SWITCHIMG;
		undoactitm.saved.pageedit.peditpaper = dstPageItm->getPage()->getPaperPage();
		undoactitm.saved.pageedit.psavepaper = pScene->getMainFrame()->getDoc()->createNewPaper();
		if ( undoactitm.saved.pageedit.psavepaper )
		{
			undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
			undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
			if ( pSrcPageitm->getPage()->getPaperPage() != dstPageItm->getPage()->getPaperPage() )
			{
				undoactitm.saved.pageedit.p2ndeditpaper = pSrcPageitm->getPage()->getPaperPage();
				undoactitm.saved.pageedit.p2ndsavepaper = pScene->getMainFrame()->getDoc()->createNewPaper();
				undoactitm.saved.pageedit.p2ndsavepaper->copy(*undoactitm.saved.pageedit.p2ndeditpaper);
				undoactitm.saved.pageedit.p2ndsavepaper->setborder(undoactitm.saved.pageedit.p2ndeditpaper->getborder());
			}

			PmUndoActionStack::getInst().pushAction(undoactitm);

			pScene->getMainFrame()->updateUIStatus();
		}


		QPointF srclefttop(-1,-1);
		QPixmap pixmap;
		QString srcpath;
		QColor srccolor;
		if ( pSrcPageitm )
		{
			//pSrcPageitm->getImgLeftTop(srclefttop);
			pSrcPageitm->getContent(srcpath);
			if ( pSrcPageitm->getPixmap() )
			{
				pixmap = *pSrcPageitm->getPixmap();
			}
			pSrcPageitm->getBgColor(srccolor);
			QString imgInThisItm;
			dstPageItm->getContent(imgInThisItm);
			pSrcPageitm->setContent(imgInThisItm);
			QPointF lefttop(-1,-1);
			//dstPageItm->getImgLeftTop(lefttop);
			pSrcPageitm->setImgLeftTop(lefttop);
			if ( dstPageItm->getPixmap() )
			{
				pSrcPageitm->setPixmap(*dstPageItm->getPixmap());
			}
			else
			{
				pSrcPageitm->setPixmap(QPixmap());
			}
			QColor color;
			dstPageItm->getBgColor(color);
			pSrcPageitm->setBgColor(color);

		}		
		if ( dstPageItm )
		{
			dstPageItm->setContent(srcpath);
			dstPageItm->setImgLeftTop(srclefttop);
			dstPageItm->setPixmap(pixmap);
			dstPageItm->setBgColor(srccolor);
		}

		PhotoViewItm *srcpreviewitm = NULL;
		PhotoViewItm *srcEditViewItm = NULL;

		if ( pSrcPageitm )
		{
			srcpreviewitm = (PhotoViewItm *)pSrcPageitm->getPreviewPageViewItm();
			srcEditViewItm = (PhotoViewItm *)pSrcPageitm->getPageViewItm();
		}

		PhotoViewItm *dstEditViewItm = NULL;
		PhotoViewItm *dstPreViewItm = NULL;
		if ( dstPageItm )
		{
			dstPreViewItm = (PhotoViewItm *)dstPageItm->getPreviewPageViewItm();
			dstEditViewItm = (PhotoViewItm *)dstPageItm->getPageViewItm();
		}

		if ( pScene )
		{
			pScene->getMainFrame()->updateLastPhotoPage(dstPageItm->getPage());
		}

		if  ( dstEditViewItm )
		{
			dstEditViewItm->reload();
			dstEditViewItm->updatePanoramaPair();
		}
		if ( dstPreViewItm )
		{
			dstPreViewItm->reload();
			dstPreViewItm->updatePanoramaPair();
		}
		if ( srcpreviewitm )
		{
			srcpreviewitm->reload();
			srcpreviewitm->updatePanoramaPair();
		}
		if ( srcEditViewItm )
		{
			srcEditViewItm->reload();
			srcEditViewItm->updatePanoramaPair();
		}
		//this->reload();
	}

	// update all views
	pMainFrame->updateViews(false);

}

void PhotoPreviewItm::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
	PhotoViewItm::paint(painter, option, widget);
}




void PhotoPreviewItm::reload()
{
	QString imgpath;
	QPixmap *pixmap = NULL;
	if ( _pPageItm )
	{
		this->_pPageItm->getContent(imgpath);
		//pixmap = _pPageItm->getPixmap();
	}

	QPixmap savepixmap;
	if ( pixmap )
	{
		savepixmap = *pixmap;
	}
	this->setImg(imgpath,savepixmap);
	
	//_pPageItm->setPixmap(savepixmap);
	QColor color;
	if ( _pPageItm )
	{
		_pPageItm->getBgColor(color);
		if ( !color.isValid() )
		{
			color = Qt::white;
		}
		this->setItemBGColor(color);
	}

	if ( imgpath.length() || color!=Qt::white )
	{
		_orgcur = cursor();
		setCursor(QCursor(QPixmap(gbires + "curs/switchimg.png"), 0, 0));
	}
	else
	{
		setCursor(Qt::ArrowCursor);
	}

	this->resize();
}


// panorama view item

PanorPhotoPreviewItm::PanorPhotoPreviewItm(const QPointF& pos,
                   const QSize& size,
                   const QMargins& margin,bool left,
                   PhotoPreviewScene *scene,
                   QGraphicsItem * parent): 
PhotoPanoViewItm(pos, size, margin,left?PhotoPanoViewItm::Left_Pano:PhotoPanoViewItm::Right_Pano, NULL, parent),
	_pPaperPagePreviwItm(NULL), _pScene(scene)
{
	img_filepath = QString("");
    pixmap = QPixmap();
    img_lefttop = QPoint();

    b_drag = false;
    setItemType(ImgType);
}

PanorPhotoPreviewItm::~PanorPhotoPreviewItm()
{
}



void PanorPhotoPreviewItm::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	//PhotoViewItm::mouseReleaseEvent(event);
	if ( event->button() == Qt::LeftButton )
	{
		if ( _pPaperPagePreviwItm )
		{
			//
			_pScene->select(_pPaperPagePreviwItm);
		}
	}
}

void PanorPhotoPreviewItm::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

	if ( event->button() == Qt::RightButton )
	{
		//
		if ( _pPaperPagePreviwItm )
		{
			//
			_pScene->selectRightBtnPaper(_pPaperPagePreviwItm);
		}
	}
	//QGraphicsItem::mousePressEvent(event);
}


void PanorPhotoPreviewItm::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	//QGraphicsPixmapItem::mouseMoveEvent(event);

	if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }

	PmPageItm *_pPageItm = this->_pPageItm;
	QString imgpath;
	_pPageItm->getContent(imgpath);
	if ( imgpath.length() <= 0 )
	{
		return ;
	}


    QDrag *drag = new QDrag(event->widget());
	drag->setPixmap(this->pixmap.scaled(30, 40));
	drag->setHotSpot(QPoint(15, 30));
	   

    QMimeData *mime = new QMimeData;
	mime->setText(imgpath);
	QByteArray orgpageitm;
	QString tmp;
	tmp = QString("%1").arg((ulong)_pPageItm);
	orgpageitm.append(tmp);

	mime->setData("orginalpageitm", orgpageitm);
	mime->setData("srcloc", "preview");

    drag->setMimeData(mime);

	drag->exec();

	//setCursor(Qt::OpenHandCursor);
}

void PanorPhotoPreviewItm::dropEvent(QGraphicsSceneDragDropEvent *event)
{
	PhotoMaker *pMainFrame = _pScene->getMainFrame();

	/// update path
	QString info;
	if (event->mimeData()->hasText())
		info = event->mimeData()->text();
	//img_filepath = path;

	if ( !_pPageItm )
	{
		return ;
	}
	QString srcloc = event->mimeData()->data("srcloc");
	if ( srcloc == "filelistview" )
	{
		PhotoViewItm::dropEvent(event);
	}
	else if ( srcloc == "preview" )
	{
		PmPageItm *pSrcPageitm = NULL;
		QByteArray orgpageitm;
		QString tmp;
		if ( event->mimeData()->hasFormat("orginalpageitm") )
		{
			orgpageitm = event->mimeData()->data("orginalpageitm");
			tmp = orgpageitm.data();
			pSrcPageitm = (PmPageItm *)tmp.toInt();
		}
		PmPageItm *dstPageItm = this->_pPageItm;
		if ( dstPageItm == pSrcPageitm ||  dstPageItm == NULL || pSrcPageitm == NULL )
		{
			return ;
		}


		PmViewScnen *pScene = getScene();
		if ( !pScene )
		{
			return ;
		}
		// save for undo actions
		PE_UNDOACT_ITEM undoactitm;
		undoactitm.action = PE_UNDOACT_ITEM::ACTION_PG_SWITCHIMG;
		undoactitm.saved.pageedit.peditpaper = dstPageItm->getPage()->getPaperPage();
		undoactitm.saved.pageedit.psavepaper = pScene->getMainFrame()->getDoc()->createNewPaper();
		if ( undoactitm.saved.pageedit.psavepaper )
		{
			undoactitm.saved.pageedit.psavepaper->copy(*undoactitm.saved.pageedit.peditpaper);
			undoactitm.saved.pageedit.psavepaper->setborder(undoactitm.saved.pageedit.peditpaper->getborder());
			if ( pSrcPageitm->getPage()->getPaperPage() != dstPageItm->getPage()->getPaperPage() )
			{
				undoactitm.saved.pageedit.p2ndeditpaper = pSrcPageitm->getPage()->getPaperPage();
				undoactitm.saved.pageedit.p2ndsavepaper = pScene->getMainFrame()->getDoc()->createNewPaper();
				undoactitm.saved.pageedit.p2ndsavepaper->copy(*undoactitm.saved.pageedit.p2ndeditpaper);
				undoactitm.saved.pageedit.p2ndsavepaper->setborder(undoactitm.saved.pageedit.p2ndeditpaper->getborder());
			}

			PmUndoActionStack::getInst().pushAction(undoactitm);

			pScene->getMainFrame()->updateUIStatus();

		}


		QPointF srclefttop(-1,-1);
		QPixmap pixmap;
		QString srcpath;
		QColor srccolor;
		if ( pSrcPageitm )
		{
			//pSrcPageitm->getImgLeftTop(srclefttop);
			pSrcPageitm->getContent(srcpath);
			if ( pSrcPageitm->getPixmap() )
			{
				pixmap = *pSrcPageitm->getPixmap();
			}
			pSrcPageitm->getBgColor(srccolor);
			QString imgInThisItm;
			dstPageItm->getContent(imgInThisItm);
			pSrcPageitm->setContent(imgInThisItm);
			QPointF lefttop(-1,-1);
			//dstPageItm->getImgLeftTop(lefttop);
			pSrcPageitm->setImgLeftTop(lefttop);
			if ( dstPageItm->getPixmap() )
			{
				pSrcPageitm->setPixmap(*dstPageItm->getPixmap());
			}
			else
			{
				pSrcPageitm->setPixmap(QPixmap());
			}
			QColor color;
			dstPageItm->getBgColor(color);
			pSrcPageitm->setBgColor(color);

		}		
		if ( dstPageItm )
		{
			dstPageItm->setContent(srcpath);
			dstPageItm->setImgLeftTop(srclefttop);
			dstPageItm->setPixmap(pixmap);
			dstPageItm->setBgColor(srccolor);
		}

		PhotoViewItm *srcpreviewitm = NULL;
		PhotoViewItm *srcEditViewItm = NULL;

		if ( pSrcPageitm )
		{
			srcpreviewitm = (PhotoViewItm *)pSrcPageitm->getPreviewPageViewItm();
			srcEditViewItm = (PhotoViewItm *)pSrcPageitm->getPageViewItm();
		}

		PhotoViewItm *dstEditViewItm = NULL;
		PhotoViewItm *dstPreViewItm = NULL;
		if ( dstPageItm )
		{
			dstPreViewItm = (PhotoViewItm *)dstPageItm->getPreviewPageViewItm();
			dstEditViewItm = (PhotoViewItm *)dstPageItm->getPageViewItm();
		}

		if  ( dstEditViewItm )
		{
			dstEditViewItm->reload();
			dstEditViewItm->updatePanoramaPair();
		}
		if ( dstPreViewItm )
		{
			dstPreViewItm->reload();
			dstPreViewItm->updatePanoramaPair();
		}
		if ( srcpreviewitm )
		{
			srcpreviewitm->reload();
			srcpreviewitm->updatePanoramaPair();
		}
		if ( srcEditViewItm )
		{
			srcEditViewItm->reload();
			srcEditViewItm->updatePanoramaPair();
		}
		//this->reload();

	}

	// update all views
	pMainFrame->updateViews(false);
}

void PanorPhotoPreviewItm::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
	PhotoPanoViewItm::paint(painter, option, widget);
}


void PanorPhotoPreviewItm::reload()
{
	QString imgpath;
	QPixmap *pixmap = NULL;
	if ( _pPageItm )
	{
		this->_pPageItm->getContent(imgpath);
		//pixmap = _pPageItm->getPixmap();
	}

	QPixmap savepixmap;
	if ( pixmap )
	{
		savepixmap = *pixmap;
	}
	this->setImg(imgpath,savepixmap);
	
	//_pPageItm->setPixmap(savepixmap);
	QColor color;
	if ( _pPageItm )
	{
		_pPageItm->getBgColor(color);
		if ( !color.isValid() )
		{
			color = Qt::white;
		}
		this->setItemBGColor(color);
	}

	if ( imgpath.length() || color != Qt::white )
	{
		_orgcur = cursor();
		setCursor(QCursor(QPixmap(gbires + "curs/switchimg.png"), 0, 0));
	}
	else
	{
		setCursor(Qt::ArrowCursor);
	}

	this->resize();
}


//
PaperPagePreviewItmSet::PaperPagePreviewItmSet(PhotoPreviewScene *pscene,
	PmPrintPaperPage *pPaperPage, const QRectF &rect, PhotoMaker* pMainFrame):
_pscene(pscene), _pPaperPage(pPaperPage), _rect(rect),
	_pPaperPageBackGround(NULL), _pMainFrame(pMainFrame), _isnext(false),_enableMv(true)
{
	//_bottomLabel = new QPushButton(/*(QWidget*)(_pscene->parent())*/);
	//_bottomLabel->setText("Page No 2");
	//_bottomLabel->hide();
	//_bottomLabel->setFlat(true);

	_updateRegions();


	_pBottomLabel = new PreviewPaperLabelViewItm(this, _pscene);
	_pBottomLabel->setContent("Page No 2");
	//_pBottomLabel->sethei

	_pBottomLabel->setZValue(2);
	if ( _pscene )
	{
		_pscene->addItem(_pBottomLabel);
	}

	this->_addBackgroundItm();

}

PaperPagePreviewItmSet::~PaperPagePreviewItmSet()
{
	delete _pBottomLabel; // this item has no parent, must be destroied;
	delete _pPaperPageBackGround;
}

void PaperPagePreviewItmSet::enableMvPaper(bool enable)
{
	_enableMv = enable;
	_pBottomLabel->enableDrag(_enableMv);
}


void PaperPagePreviewItmSet::setBottomLabel(const QString &labeltxt)
{
	this->_bottomLabelTxt = labeltxt;
	_pBottomLabel->setContent(_bottomLabelTxt);
}
void PaperPagePreviewItmSet::_removeViewItems()
{
	QList<PageViewItm*>::iterator it;
	for ( it=_viewitmlst.begin(); it!= _viewitmlst.end(); it++ )
	{
		//
		if ( *it )
		{
			_pscene->removeItem(*it);
		}
	}

	_viewitmlst.clear();
}



void PaperPagePreviewItmSet::remove()
{
	_removeViewItems();

	if (_pPaperPageBackGround )
	{
		this->_pscene->removeItem(_pPaperPageBackGround);
	}
	_pPaperPageBackGround = NULL;

	if ( this->_pBottomLabel )
	{
		this->_pscene->removeItem(_pBottomLabel);
		delete _pBottomLabel;
		_pBottomLabel = NULL;
	}
	_pPaperPageBackGround = NULL;

}

#define PREVIEW_ITM_HEIGHT_DELTA	3
#define BOTTOM_LABEL_HEIGHT	20
#define BOTTOM_LABEL_OFF_2_BOTTOM	5
#define PREVIEW_ITM_WIDTH_DELTA	5
void PaperPagePreviewItmSet::_updateRegions()
{
	_previewframe = _rect;
	_previewframe.adjust(0,PREVIEW_ITM_HEIGHT_DELTA,0,-PREVIEW_ITM_HEIGHT_DELTA);
	_bottomlabelframe = _previewframe;
	_bottomlabelframe.adjust(PREVIEW_ITM_WIDTH_DELTA, 0, -PREVIEW_ITM_WIDTH_DELTA, 0);
	_bottomlabelframe.setTop(_bottomlabelframe.bottom()-BOTTOM_LABEL_HEIGHT-BOTTOM_LABEL_OFF_2_BOTTOM);
	_bottomlabelframe.setBottom(_bottomlabelframe.bottom()-BOTTOM_LABEL_OFF_2_BOTTOM);

	// calculate paperframe
	if ( !_pPaperPage )
	{
		return ;
	}
	QSize papersize;
	_pPaperPage->getSize(papersize);

	QRectF paperframe = _previewframe;
	paperframe.adjust(PREVIEW_ITM_WIDTH_DELTA,PREVIEW_ITM_HEIGHT_DELTA, -PREVIEW_ITM_WIDTH_DELTA,
		-BOTTOM_LABEL_OFF_2_BOTTOM-BOTTOM_LABEL_HEIGHT-PREVIEW_ITM_HEIGHT_DELTA);

	qreal paperheight = paperframe.height();
	qreal paperwidth = paperframe.width();
	if ( paperframe.height() * papersize.width()*1.0/papersize.height() > paperframe.width() )
	{
		// cal height according width
		paperheight = paperwidth * papersize.height()*1.0/papersize.width();
		qreal y = (paperframe.top() + paperframe.bottom())/2.0 - paperheight/2;
		paperframe.setTop(y);
		paperframe.setHeight(paperheight);
	}
	else
	{
		// cal width according height
		paperwidth = paperheight * papersize.width() * 1.0/papersize.height();

		//
		qreal x = (paperframe.left() + paperframe.right())/2.0 - paperwidth/2;
		paperframe.setLeft(x);
		paperframe.setWidth(paperwidth);
	}
	
	_paperpageframe = paperframe;
}

void PaperPagePreviewItmSet::update(bool reload)
{
	//
	_updateRegions();
	if ( reload )
	{
		// re-add items
		_reloadItems();
	}

	this->_updateItems();
	//this->update();

}

void PaperPagePreviewItmSet::_reloadItems()
{
	//
	if ( !this->_pPaperPage )
	{
		return ;
	}

	_removeViewItems();


	PmPhotoPage *pPhotoPage = NULL;
	QList<PmPhotoPage *> photoPages;
	_pPaperPage->getPhotoPages(photoPages);

	QList<PmPhotoPage *>::iterator it;
	for(it=photoPages.begin(); it!=photoPages.end(); it++ )
	{
		//
		_addPhotoPage(*it);
	}

}

void PaperPagePreviewItmSet::_addBackgroundItm()
{
	if ( _pPaperPageBackGround )
	{
		return ;
	}

	QString backgroundimg;
	if (  _pPaperPage->getBackGroundImgInEditView(backgroundimg) )
	{
		backgroundimg = gbires + "white.png";
		_pPaperPageBackGround = new PaperPreviewBgItm(this->_pscene,this,QPixmap::fromImage(QImage(backgroundimg)));
		QLinearGradient linearGrad(QPointF(0, 0), QPointF(1024, 768));
		//gradient.setStops(
		//linearGrad.setColorAt(0, QColor(qRgb(240,240,240)));
		//linearGrad.setColorAt(1, QColor(qRgb(240,240,200)));
		//_pPaperPageLayout->setBrush(QBrush(linearGrad));
		//_pPaperPageLayout->setBrush(QBrush(QColor(qRgb(240,240,240))));
		_pPaperPageBackGround->setFlag(QGraphicsItem::ItemIsSelectable, true);

		this->_pscene->addItem(_pPaperPageBackGround);
		_pPaperPageBackGround->setZValue(0);
	}

}
bool _isPanoramaLayout(PHOTO_LAYOUT layout);

void PaperPagePreviewItmSet::_addPhotoPage(PmPhotoPage *pPhotoPage)
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
		LayoutBoxPos itmrect;
		pPicItm->getRectInPage(itmrect);

		// first add photo page offset

		qreal xoff = 0,yoff = 0;
		qreal itmwidth = 0, itmheight = 0;
		QMargins margin;


		PageViewItm *itm = NULL;
		if ( pPicItm->getPhotoItmType() != PmPageItm::CALENDAR_ITM )
		{

			
			if ( _isPanoramaLayout(pPhotoPage->getLayout()) )
			{
				PanorPhotoPreviewItm* item1 = NULL;

				item1 = new PanorPhotoPreviewItm(QPointF(xoff,yoff),
					QSize((int)itmwidth,(int)itmheight),margin,pPhotoPage->isLeft(),this->_pscene);
				itm = item1;
				QString imgpath;
				pPicItm->getContent(imgpath);
				if ( imgpath.length())
				{
					// get a preview img item
					QPixmap savedpixmap;
					QPixmap *pixmap = pPicItm->getPixmap();
					if ( pixmap )
					{
						savedpixmap = *pixmap;
					}
					{
						item1->setImg(imgpath, savedpixmap);
						pPicItm->setPixmap(savedpixmap);
					}
				}
				else
				{
				}
				item1->setPmPageItm(pPicItm);
				item1->setPaperPagePreviewItmSet(this);
				item1->setShadow(false);
				pPicItm->setPreviewPageViewItm(item1);

			}
			else
			{
				PhotoPreviewItm* item1 = NULL;
				item1 = new PhotoPreviewItm(QPointF(xoff,yoff),
					QSize((int)itmwidth,(int)itmheight),margin,this->_pscene);
				itm = item1;
				QString imgpath;
				pPicItm->getContent(imgpath);
				if ( imgpath.length())
				{
					// get a preview img item
					QPixmap savedpixmap;
					QPixmap *pixmap = pPicItm->getPixmap();
					if ( pixmap )
					{
						savedpixmap = *pixmap;
					}
					{
						item1->setImg(imgpath, savedpixmap);
						pPicItm->setPixmap(savedpixmap);
					}
				}
				else
				{
				}
				QColor color;
				pPicItm->getBgColor(color);
				item1->setItemBGColor(color);
				item1->setPmPageItm(pPicItm);
				item1->setPaperPagePreviewItmSet(this);
				item1->setShadow(false);
				pPicItm->setPreviewPageViewItm(item1);
			}

		}
		else
		{
			// add calendar item
			PROJ_PROPS proj;
			this->_pMainFrame->getDoc()->getProjProps(proj);

			CalViewItm *calitm = CalViewItmFactory::getPreviewItm(proj.lytype,QPointF(0,0),
				QSize((int)0,(int)0),margin,this->_pscene); 

			itm = calitm;
			MonthYearInfo month;
			int year = 0, mon = 0;
			pPicItm->getMonth(year, mon);
			calitm->setYearMonth(year, mon);

			//bool shadow = this->_pMainFrame->getDoc()->shadow();
			calitm->setPmPageItm(pPicItm);
			pPicItm->setPreviewPageViewItm(calitm);
			calitm->setPaperPagePreviewItmSet(this);

		}
		this->_pscene->addItem(itm);
		itm->setPos(int(xoff),(int)(yoff));
		itm->setZValue(2);

		this->_viewitmlst.push_back(itm);
	}
}

void PaperPagePreviewItmSet::_updateItems()
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
	QRectF rect = getRect();

	//rect.adjust(0, 15, 0, 0);
	//qreal height, width;
	//width = (rect.height()-40)*size.width()/size.height();
	//height = rect.height()-40;

	//_paperpageframe.setLeft(rect.left());
	//_paperpageframe.setTop(rect.top() );
	//_paperpageframe.setWidth(rect.width());
	//_paperpageframe.setHeight(rect.height());

	_updateBackgroundItm();

	PmPhotoPage *pPhotoPage = NULL;
	QList<PmPhotoPage *> photoPages;
	_pPaperPage->getPhotoPages(photoPages);

	QList<PmPhotoPage *>::iterator it;
	for(it=photoPages.begin(); it!=photoPages.end(); it++ )
	{
		//
		this->_updatePhotoPage(*it);
	}
	_updateBottomLabel();
	this->_pscene->update();
}

void PaperPagePreviewItmSet::_updateBottomLabel()
{


	//this->_pBottomLabel->setPos(blRect.left(), blRect.top());
	_pBottomLabel->setRect(_bottomlabelframe);
	//_bottomLabel->setFixedWidth(blRect.width());

	//blRect.setBottom(blRect.bottom()-1);
	//blRect.adjust(1, 1, -1, -1);
	//this->_bottomLabel->setGeometry(blRect.left(), blRect.top(), blRect.width(), blRect.height());
	//_pBottomLabelBtnGpWidget->setPos(blRect.left(), blRect.top());
	//_pBottomLabelBtnGpWidget->show();
	//_bottomLabel->resize(blRect.width(), blRect.height());
	//this->_bottomLabel->setTextWidth(blRect.width());
	//this->_pBottomLabelBtnGpWidget->update();
}
void PaperPagePreviewItmSet::_updatePhotoPage(PmPhotoPage *pPhotoPage)
{
	if ( !pPhotoPage )
	{
		return ;
	}

	//
	//
	//  previev itm height = 120, top margin = 30, bottom margin = 30, img item height = 70, 
	//  top margin = 30/120, bottom margin = 30/120, height = 70/120
	//
	// max img height = 120, bottom label height = 20
	//  top margin = (total height - bottom label height - 120 ) * 0.5
	//  bottom margin = (total height - bottom label height - 120 ) * 0.5
	//

	// boundary total heigth 140

	LayoutBoxPos pagepos;
	pPhotoPage->getPagePosInPaper(pagepos);
	

	QRectF photoframe = _paperpageframe;
	//photoframe.adjust(15, 0, -15, 0);
	QRectF paperpagerect = photoframe;

	qreal itmheight = _paperpageframe.height();
	/*
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
	*/

	//
	// adjust paper rect according print paper layout
	//
	QSize size;
	_pPaperPage->getSize(size);

	//
	/*
	if ( paperpagerect.width() * 1.0 /paperpagerect.height()  >  size.width() * 1.0/size.height() )
	{
		// shrink width
		qreal paperwdith = paperpagerect.height() * 1.0 * size.width() /size.height();
		qreal adjustoff = (paperpagerect.width()-paperwdith)/2;
		paperpagerect.adjust(adjustoff, 0, -adjustoff, 0);
	}
	else
	{
		qreal paperwdith = 130;
		qreal adjustoff = (paperpagerect.width()-paperwdith)/2;
		paperpagerect.adjust(adjustoff, 0, -adjustoff, 0);
	}
	*/


	qreal papaerpagexoff = paperpagerect.left() ;
	qreal papaerpageyoff = paperpagerect.top();
	//papaerpagexoff += 15;

	qreal height = paperpagerect.height();
	qreal width = paperpagerect.width();
	//width -= 30;


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

		PageViewItm* item = (PageViewItm* )pPicItm->getPreviewPageViewItm();
		if ( !item )
		{
			continue;
		}
		if ( pPicItm->getPhotoItmType() != PmPageItm::CALENDAR_ITM )
		{
			PhotoViewItm *item1 = (PhotoViewItm*)item;

			QString imgpath;
			pPicItm->getContent(imgpath);
			if ( imgpath.length())
			{
#if 0
				if ( imgpath.lastIndexOf("jpg") > 0  || imgpath.lastIndexOf("JPG") > 0)
				{
					qmeta::Jpeg jpgfile(imgpath);
					QByteArray data = jpgfile.Thumbnail();
					if ( data.size() )
					{
						int namepos = imgpath.lastIndexOf("/");
						QString name = imgpath.right(namepos+1);
						QString thumbnailpath;
						thumbnailpath += ".\\";
						thumbnailpath += name;
						thumbnailpath += ".thumb";

						QFile file(thumbnailpath);
						file.open(QIODevice::WriteOnly);
						file.write(data);
						file.close();

						item1->setImg(thumbnailpath);

						bool ret =  QFile::remove(thumbnailpath);

					}
					else
					{
						item1->setImg(imgpath);
					}
				}
				else
#endif
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
			}
			else
			{
				QPixmap savedpixmap;
				item1->setImg(imgpath, savedpixmap);
				pPicItm->setPixmap(savedpixmap);

			}
		}
		else
		{
			//
			CalViewItm *calitm = (CalViewItm*)item;
		}


		QMargins margin = QMargins(pagerect.width()*itmrect.margin.left,
			pagerect.height()*itmrect.margin.top,
			pagerect.width()*itmrect.margin.right,
			pagerect.height()*itmrect.margin.bottom);

		item->setItemMargin(margin);
		item->setItemSize(QSize((int)itmwidth,(int)itmheight));
		item->setPos(int(xoff),(int)(yoff));
		item->resize();
	}
}

void PaperPagePreviewItmSet::_updateBackgroundItm()
{
	QString backgroundimg;
	_pPaperPage->getBackGroundImgInEditView(backgroundimg);

	if ( _pPaperPageBackGround )
	{
		_pPaperPageBackGround->setX(_previewframe.left());
		_pPaperPageBackGround->setY(_previewframe.top());

		backgroundimg = gbires + "white.png";

		QImage img(backgroundimg);
		QImage newsizeimg = img.scaled(_previewframe.width(), _previewframe.height());

		QPixmap tempPixmap = QPixmap::fromImage(newsizeimg);
		QPainter painter;
		painter.begin(&tempPixmap);
		if ( this->_isnext )
		{
			QRect imgRect = tempPixmap.rect();
			
			QColor color;
			color = QColor(qRgb(255,0,0));
			QPen pen(color);
			pen.setWidth(1);
			painter.setPen(pen);
			painter.drawLine(QPointF(imgRect.width()/2, 0), QPointF(imgRect.width()/2, imgRect.height()));
			//painter.fillRect(tempPixmap.rect(), color);

		}

		//
		// gray rect
		//
		QRect bgrc = QRect(_paperpageframe.left(),_paperpageframe.top(), _paperpageframe.width(), _paperpageframe.height() );
		bgrc.adjust(-_previewframe.left(), -_previewframe.top(), -_previewframe.left(), -_previewframe.top());

        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(1);
        pen.setBrush(Qt::lightGray);
		painter.setPen(pen);
		painter.drawRect(bgrc);
		painter.end();

		_pPaperPageBackGround->setPixmap(tempPixmap);
		_pPaperPageBackGround->setZValue(1);
	}

}


void PaperPagePreviewItmSet::resize(const QRectF &rect)
{
	_rect = rect;
	update();
}
QRectF PaperPagePreviewItmSet::getRect()
{
	return _rect;
}




void PaperPagePreviewItmSet::select(bool select)
{
	if ( _pPaperPageBackGround )
	{
		_pPaperPageBackGround->setSelected(select);
		_pPaperPageBackGround->update();
		this->_pscene->update();
	}
}



PaperPreviewBgItm::PaperPreviewBgItm(PhotoPreviewScene *pscene,PaperPagePreviewItmSet *pPaerPage, const QPixmap &pixmap):
QGraphicsPixmapItem(pixmap), _pPaerPage(pPaerPage), _pscene(pscene)
{
	setAcceptDrops(true);
}

PaperPreviewBgItm::~PaperPreviewBgItm()
{
}


void PaperPreviewBgItm::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if ( event->button() == Qt::LeftButton )
	{
		QGraphicsPixmapItem::mousePressEvent(event);

		if ( this->isSelected() )
		{
			_pscene->select(this->_pPaerPage);
		}
	}
	else if ( event->button() == Qt::RightButton )
	{

		_pscene->selectRightBtnPaper(_pPaerPage);
	}
}

void PaperPreviewBgItm::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{

	PaperPagePreviewItmSet *paperset = (PaperPagePreviewItmSet *)event->mimeData()->data("paper").toLongLong();
	if ( !paperset )
	{
	}
	else
	{
		if (  paperset == this->_pPaerPage)
		{
			// smae page, can not 
			event->ignore();
		}
		else 
		{
			event->accept();
		}
	}
}

void PaperPreviewBgItm::dragMoveEvent ( QGraphicsSceneDragDropEvent * event ) 
{
	QPointF pos = event->pos();
	QRectF rc = this->boundingRect();

	{
		event->ignore();
	}
}

void PaperPreviewBgItm::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
}


void PaperPreviewBgItm::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
{
	QGraphicsPixmapItem::paint(painter, option, widget);
	if ( this->isSelected() )
	{
		_paintSelected(painter, option);
	}

}



void PaperPreviewBgItm::_paintSelected(QPainter *painter,const QStyleOptionGraphicsItem *option)
{

    const QRectF murect = painter->transform().mapRect(QRectF(0, 0, 1, 1));
    if (qFuzzyIsNull(qMax(murect.width(), murect.height())))
        return;

    const QRectF mbrect = painter->transform().mapRect(this->boundingRect());
    if (qMin(mbrect.width(), mbrect.height()) < qreal(1.0))
        return;

    qreal itemPenWidth;
   itemPenWidth = 1.0;
    const qreal pad = itemPenWidth / 2;

    const qreal penWidth = 0; // cosmetic pen

    const QColor fgcolor = option->palette.windowText().color();
    const QColor bgcolor(Qt::gray);

	painter->setPen(QPen(QBrush(Qt::gray), 3, Qt::SolidLine));
    painter->setBrush(Qt::NoBrush);

	painter->drawRect(this->boundingRect().adjusted(0, 2, 0, 0));
}
