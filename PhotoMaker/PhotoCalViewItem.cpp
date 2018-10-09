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
#include "PhotoCalViewItem.h"
#include "photomaker.h"
#include "PhotoEditView.h"
#include "pmundoactionstack.h"

/*********************************************************/
//CalViewItm related
/*********************************************************/
CalViewItm::CalViewItm(const QPointF& pos,
                           const QSize& size,
                           const QMargins& margin,
                           PmViewScnen *scene,
                           QGraphicsItem * parent)
    :PageViewItm(pos, size, margin, scene,parent), _scene(scene)
{
    setItemType(CalType);
}



void CalViewItm::_updateLayout(const QString &layoutname)
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
void CalViewItm::setContent(const QString &cnt)
{
    //
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


	}
	else if ( info.length()>strlen(COLOR_PREFIX) && info.left(strlen(COLOR_PREFIX)) == COLOR_PREFIX )  
	{
		// not support set color on cal view itm
		return ;

	}
	else
	{
		// not support set img on cal view item
	}
}

PmViewScnen *CalViewItm::getScene()
{
    return _scene;
}

CalViewItm::~CalViewItm()
{
    //do nth
}


void CalViewItm::resize(bool update)
{
    //
    //item_pos = pos;
    //item_size = size;
}

void CalViewItm::reload()
{
	//
	PmPageItm *calitm = this->getPmPageItm();

	int year = 0, month = 0;
	calitm->getMonth(year, month);
	this->setYearMonth(year, month);


	// update ui properties
	CAL_PROPS calprops;
	calitm->getCalProps(calprops);
	CalendarInfo ci;
	ci.font = QFont(calprops.fontcfg.name);
	ci.font.setBold(calprops.fontcfg.bold);
	ci.font.setItalic(calprops.fontcfg.iatic);
	ci.font.setUnderline(calprops.fontcfg.underLine);

	ci.color = calprops.fontcfg.color;
	if ( Qt::AlignLeft == Qt::AlignmentFlag(calprops.fontcfg.align & Qt::AlignHorizontal_Mask) )
	{
		ci.hor = HorLeftAlig;
	}
	else if ( Qt::AlignHCenter == Qt::AlignmentFlag(calprops.fontcfg.align & Qt::AlignHorizontal_Mask) )
	{
		ci.hor = HorCenterAlig;
	}
	else
	{
		ci.hor = HorRightAlig;
	}

	if ( Qt::AlignTop ==  Qt::AlignmentFlag(calprops.fontcfg.align & Qt::AlignVertical_Mask) )
	{
		ci.ver = VerTopAlig;
	}
        else if ( Qt::AlignVCenter ==  Qt::AlignmentFlag(calprops.fontcfg.align & Qt::AlignVertical_Mask) )
	{
		ci.ver = VerCenterAlig;
	}
	else
	{
		ci.ver = VerBottomAlig;
	}
	ci.height_in_cell = calprops.fontcfg.heightInCell * 100;


    /*Colors part*/
	ci.bg_color = calprops.bgcolor;
	ci.row_color = calprops.rowcolor;
	ci.cell_color = calprops.cellcolor;
	int index=0; 
	QList<QColor>::iterator it;
	for ( it=calprops.wdcolors.begin(); it!=calprops.wdcolors.end(); it++, index++ )
	{
		ci.everyday_color[index] = *it;
	}

    /*Line spacing part*/
	ci.line_space[0] = calprops.linespace.left;
	ci.line_space[1] = calprops.linespace.top;
	ci.line_space[2] = calprops.linespace.right;
	ci.line_space[3] = calprops.linespace.bottom;

	ci.line_padding[0] = calprops.linespace.leftpad;
	ci.line_padding[1] = calprops.linespace.toppad;
	ci.line_padding[2] = calprops.linespace.rightpad;
	ci.line_padding[3] = calprops.linespace.bottompad;

    /*Cell spacing part*/
	ci.cell_space[0] = calprops.cellspace.left;
	ci.cell_space[1] = calprops.cellspace.top;
	ci.cell_space[2] = calprops.cellspace.right;
	ci.cell_space[3] = calprops.cellspace.bottom;

	ci.cell_padding[0] = calprops.cellspace.leftpad;
	ci.cell_padding[1] = calprops.cellspace.toppad;
	ci.cell_padding[2] = calprops.cellspace.rightpad;
	ci.cell_padding[3] = calprops.cellspace.bottompad;

	this->setCalInfo(ci);



	WEEKDAY_PROPS wdsprops;
	calitm->getWdsProps(wdsprops);
	WeekdaysInfo wi;
	wi.show = wdsprops.showwds;
	wi.size_of_region = wdsprops.regionsize;
	wi.font = QFont(wdsprops.fontcfg.name);
	wi.font.setBold(wdsprops.fontcfg.bold);
	wi.font.setItalic(wdsprops.fontcfg.iatic);
	wi.font.setUnderline(wdsprops.fontcfg.underLine);

	wi.color = wdsprops.fontcfg.color;

	if ( Qt::AlignLeft ==  Qt::AlignmentFlag(wdsprops.fontcfg.align & Qt::AlignHorizontal_Mask) )
	{
		wi.hor = HorLeftAlig;
	}
	else if ( Qt::AlignHCenter ==  Qt::AlignmentFlag(wdsprops.fontcfg.align & Qt::AlignHorizontal_Mask) )
	{
		wi.hor = HorCenterAlig;
	}
	else
	{
		wi.hor = HorRightAlig;
	}

	if ( Qt::AlignTop ==  Qt::AlignmentFlag(wdsprops.fontcfg.align & Qt::AlignVertical_Mask) )
	{
		wi.ver = VerTopAlig;
	}
        else if ( Qt::AlignVCenter ==  Qt::AlignmentFlag(wdsprops.fontcfg.align & Qt::AlignVertical_Mask) )
	{
		wi.ver = VerCenterAlig;
	}
	else
	{
		wi.ver = VerBottomAlig;
	}
	wi.height_in_cell = wdsprops.fontcfg.heightInCell*100;

	wi.row_color = wdsprops.rowcolor;
	wi.cell_color = wdsprops.cellcolor;


   /*Line spacing part*/
	wi.line_space[0] = wdsprops.linespace.left;
	wi.line_space[1] = wdsprops.linespace.top;
	wi.line_space[2] = wdsprops.linespace.right;
	wi.line_space[3] = wdsprops.linespace.bottom;

	wi.line_padding[0] = wdsprops.linespace.leftpad;
	wi.line_padding[1] = wdsprops.linespace.toppad;
	wi.line_padding[2] = wdsprops.linespace.rightpad;
	wi.line_padding[3] = wdsprops.linespace.bottompad;

    /*Cell spacing part*/
	wi.cell_space[0] = wdsprops.cellspace.left;
	wi.cell_space[1] = wdsprops.cellspace.top;
	wi.cell_space[2] = wdsprops.cellspace.right;
	wi.cell_space[3] = wdsprops.cellspace.bottom;

	wi.cell_padding[0] = wdsprops.cellspace.leftpad;
	wi.cell_padding[1] = wdsprops.cellspace.toppad;
	wi.cell_padding[2] = wdsprops.cellspace.rightpad;
	wi.cell_padding[3] = wdsprops.cellspace.bottompad;
	this->setWeekdaysInfo(wi);

	MONTHYEAR_PROPS myprops;
	calitm->getMonthYearProps(myprops);

	MonthYearInfo  mi;

	mi.show = myprops.showmonthyear;
	mi.size_of_region = myprops.regionsize;
	mi.bottom = myprops.showonbottom;
	mi.doublespace = myprops.showmonthyeardouble;

	mi.font = QFont(myprops.fontcfg.name);
        qDebug() << "mi.b" << myprops.fontcfg.bold << " mi.i" << myprops.fontcfg.iatic << " mi.u" << myprops.fontcfg.underLine;
	mi.font.setBold(myprops.fontcfg.bold);
	mi.font.setItalic(myprops.fontcfg.iatic);
	mi.font.setUnderline(myprops.fontcfg.underLine);

	mi.color = myprops.fontcfg.color;

	if ( Qt::AlignLeft ==  Qt::AlignmentFlag(myprops.fontcfg.align & Qt::AlignHorizontal_Mask) )
	{
		mi.hor = HorLeftAlig;
	}
	else if ( Qt::AlignHCenter ==  Qt::AlignmentFlag(myprops.fontcfg.align & Qt::AlignHorizontal_Mask) )
	{
		mi.hor = HorCenterAlig;
	}
	else
	{
		mi.hor = HorRightAlig;
	}

	if ( Qt::AlignTop ==  Qt::AlignmentFlag(myprops.fontcfg.align & Qt::AlignVertical_Mask) )
	{
		mi.ver = VerTopAlig;
	}
        else if ( Qt::AlignVCenter ==  Qt::AlignmentFlag(myprops.fontcfg.align & Qt::AlignVertical_Mask) )
	{
		mi.ver = VerCenterAlig;
	}
	else
	{
		mi.ver = VerBottomAlig;
	}

	mi.height_in_cell = myprops.fontcfg.heightInCell*100;

	mi.row_color = myprops.rowcolor;

	mi.line_space[0] = myprops.linespace.left;
	mi.line_space[1] = myprops.linespace.top;
	mi.line_space[2] = myprops.linespace.right;
	mi.line_space[3] = myprops.linespace.bottom;

	mi.line_padding[0] = myprops.linespace.leftpad;
	mi.line_padding[1] = myprops.linespace.toppad;
	mi.line_padding[2] = myprops.linespace.rightpad;
	mi.line_padding[3] = myprops.linespace.bottompad;

	this->setMonthYearInfo(mi);

	this->update();
}


void CalViewItm::setYearMonth(int year, int month)
{
    m_date.setDate(year, month, 1);

    this->update();
}

void CalViewItm::getYearMonth(int* year, int* month)
{
    *year = m_date.year();
    *month = m_date.month();
}

QDate CalViewItm::getDate(void)
{
    return m_date;
}

void CalViewItm::setCalInfo(const CalendarInfo& ci)
{
    cal_info = ci;

    this->update();
}

void CalViewItm::setWeekdaysInfo(const WeekdaysInfo& wi)
{
    weekdays_info = wi;

    this->update();
}

void CalViewItm::setMonthYearInfo(const MonthYearInfo& mi)
{
    monthyear_info = mi;

    this->update();
}

void CalViewItm::getInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi)
{
    *ci = cal_info;
    *wi = weekdays_info;
    *mi = monthyear_info;
}


void CalViewItm::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug() << "cal_info.height_in_cell is: " << cal_info.height_in_cell;

    if( m_date.isNull() || !m_date.isValid() )
    {
        PageViewItm::paint(painter, option, widget);
    }
    else
    {
        //draw the backgroud
        painter->setPen(Qt::NoPen);
        if( cal_info.bg_color == Qt::transparent )
            painter->setBrush(Qt::NoBrush);
        else
            painter->setBrush(cal_info.bg_color);
        int win_w = getItemSize().width()-getItemMargin().left()-getItemMargin().right();
        int win_h = getItemSize().height()-getItemMargin().top()-getItemMargin().bottom();
        QRect rect(getItemMargin().left(), getItemMargin().top(), win_w, win_h);
        painter->drawRect(rect);

        if( this->isSelected() )//draw the boundary
        {
            QPen pen;
            pen.setStyle(Qt::SolidLine);
            pen.setWidth(2*NORM_LINE);
            pen.setBrush(Qt::blue);
            pen.setCapStyle(Qt::RoundCap);
            pen.setJoinStyle(Qt::RoundJoin);
            painter->setPen(pen);
            painter->setBrush(Qt::NoBrush);
            painter->drawRect(rect);
        }

        qDebug() << "the main rect: " << rect;
        drawContent(painter, rect, cal_info, weekdays_info, monthyear_info, m_date);
    }
}

void CalViewItm::drawContent(QPainter *painter,
                                const QRectF &rect,
                                const CalendarInfo &ci,
                                const WeekdaysInfo &wi,
                                const MonthYearInfo &mi,
                                const QDate &d)
{
    qDebug() << "the input rect: " << rect;
    qDebug() << "weeksday_info.height_in_cell is: " << wi.size_of_region;
    qDebug() << "monthyear_info.height_in_cell is: " << mi.size_of_region;

    qreal cal_region = 100;
    if( wi.show )
        cal_region -= wi.size_of_region;
    if( mi.show )
        cal_region -= mi.size_of_region;

    qDebug() << "cal_region is:" << cal_region;

    QRectF rect_monthyear(rect);
    QRectF rect_weekdays(rect);
    QRectF rect_calendar(rect);

    if( mi.bottom )
    {
        //draw weekdays
        if( wi.show )
        {
            Q_ASSERT(wi.size_of_region > 0);
            rect_weekdays.setTop(rect.top());
            rect_weekdays.setHeight(rect.height()*wi.size_of_region/100.0);

            drawWeekdays(painter, rect_weekdays, wi, d);
        }
        else
        {
            rect_weekdays.setHeight(0.0);
        }

        //draw calendar
        if( cal_region <= 0 )
        {
            QMessageBox msgBox;
            msgBox.setText(QString("MonthYear(%1) + Weekdays(%2) size of region >= 100")
                           .arg(mi.size_of_region)
                           .arg(wi.size_of_region) );
            msgBox.exec();
        }
        else
        {
            rect_calendar.setTop(rect.top() + rect_weekdays.height());
            rect_calendar.setHeight(rect.height()*cal_region/100.0);

            drawCalendar(painter, rect_calendar, ci, d);
        }

        //draw monthyear
        if( mi.show )
        {
            Q_ASSERT(mi.size_of_region > 0);
            rect_monthyear.setTop(rect.top() + rect_weekdays.height() + rect_calendar.height());
            rect_monthyear.setHeight(rect.height()*mi.size_of_region/100.0);

            drawMonthYear(painter, rect_monthyear, mi, d);
        }
        else
        {
            rect_monthyear.setHeight(0.0);
        }
    }
    else
    {
        //draw monthyear
        if( mi.show )
        {
            Q_ASSERT(mi.size_of_region > 0);
            rect_monthyear.setTop(rect.top());
            rect_monthyear.setHeight(rect.height()*mi.size_of_region/100.0);

            drawMonthYear(painter, rect_monthyear, mi, d);
        }
        else
        {
            rect_monthyear.setHeight(0.0);
        }

        //draw weekdays
        if( wi.show )
        {
            Q_ASSERT(wi.size_of_region > 0);
            rect_weekdays.setTop(rect.top() + rect_monthyear.height());
            rect_weekdays.setHeight(rect.height()*wi.size_of_region/100.0);

            drawWeekdays(painter, rect_weekdays, wi, d);
        }
        else
        {
            rect_weekdays.setHeight(0.0);
        }

        //draw calendar
        if( cal_region <= 0 )
        {
            QMessageBox msgBox;
            msgBox.setText(QString("MonthYear(%1) + Weekdays(%2) size of region >= 100")
                           .arg(mi.size_of_region)
                           .arg(wi.size_of_region) );
            msgBox.exec();
        }
        else
        {
            rect_calendar.setTop(rect.top() + rect_monthyear.height() + rect_weekdays.height());
            rect_calendar.setHeight(rect.height()*cal_region/100.0);

            qDebug() << "rect_calendar: " << rect_calendar;
            drawCalendar(painter, rect_calendar, ci, d);
        }
    }
}

void CalViewItm::drawWeekdays_cell(QPainter *painter, const QRectF& cell_rect, const QString& str, const WeekdaysInfo& wi)
{
    QRectF rect_space(cell_rect);
    scale_rect(cell_rect, &rect_space, wi.cell_space, 4);

    painter->setPen(Qt::NoPen);
    if( wi.cell_color == Qt::transparent )
        painter->setBrush(Qt::NoBrush);
    else
        painter->setBrush(wi.cell_color);
    painter->drawRect(rect_space);

    QRectF rect_padding(rect_space);
    scale_rect(rect_space, &rect_padding, wi.cell_padding, 4);

    painter->setPen(QPen(wi.color));
    painter->setBrush(QBrush(Qt::NoBrush));
    QFont fnt(wi.font);
    fnt.setPointSize(int(wi.height_in_cell*rect_padding.height()/100.0));
    painter->setFont(fnt);
    int flags = 0;
    align_flag(wi.hor, wi.ver, &flags);

    painter->drawText(rect_padding, flags, str);
}

void CalViewItm::drawCalendar_cell(QPainter *painter, const QRectF &cell_rect, const QString& str, const QColor& clr, const CalendarInfo &ci)
{
    QRectF rect_space(cell_rect);
    scale_rect(cell_rect, &rect_space, ci.cell_space, 4);

    painter->setPen(Qt::NoPen);
    if( ci.cell_color == Qt::transparent )
        painter->setBrush(Qt::NoBrush);
    else
        painter->setBrush(ci.cell_color);
    painter->drawRect(rect_space);

    QRectF rect_padding(rect_space);
    scale_rect(rect_space, &rect_padding, ci.cell_padding, 4);

    painter->setPen(QPen(clr));
    painter->setBrush(QBrush(Qt::NoBrush));
    QFont fnt(ci.font);
    fnt.setPointSize(int(ci.height_in_cell*rect_padding.height()/100.0));
    painter->setFont(fnt);
    int flags = 0;
    align_flag(ci.hor, ci.ver, &flags);

    painter->drawText(rect_padding, flags, str);
}

void CalViewItm::drawMonthYear(QPainter *painter, const QRectF& rect, const MonthYearInfo& mi, const QDate& d)
{
    QRectF rect_space(rect);
    scale_rect(rect, &rect_space, mi.line_space, 4);

    painter->setPen(Qt::NoPen);
    if( mi.row_color == Qt::transparent )
        painter->setBrush(Qt::NoBrush);
    else
        painter->setBrush(mi.row_color);
    painter->drawRect(rect_space);


    QRectF rect_padding(rect_space);
    scale_rect(rect_space, &rect_padding, mi.line_padding, 4);

    painter->setPen(QPen(mi.color));
    painter->setBrush(QBrush(Qt::NoBrush));
    QFont fnt(mi.font);
    fnt.setPointSize(int(mi.height_in_cell*rect_padding.height()/100.0));
    painter->setFont(fnt);

    int flags = 0;
    align_flag(mi.hor, mi.ver, &flags);

    static QString month_strs[12] = {
        tr("January"),
        tr("February"),
        tr("March"),
        tr("April"),
        tr("May"),
        tr("June"),
        tr("July"),
        tr("August"),
        tr("September"),
        tr("October"),
        tr("November"),
        tr("December")};

    if( mi.doublespace )
    {
        QRectF rect_padding_month = rect_padding;
        QRectF rect_padding_year = rect_padding;

        rect_padding_month.setHeight(rect_padding.height()*3.0/5.0);
        painter->drawText(rect_padding_month, flags,
                          QString("%1").arg(month_strs[d.month()-1]));

        rect_padding_year.setTop(rect_padding.top() + rect_padding_month.height());
        fnt.setPointSize((int)(fnt.pointSize()*2.5/3.0));
        painter->setFont(fnt);
        painter->drawText(rect_padding_year, flags,
                          QString("%1").arg(d.year()));
    }
    else
    {
        painter->drawText(rect_padding, flags,
                          QString("%1 %2").arg(month_strs[d.month()-1]).arg(d.year()));
    }
}

void CalViewItm::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //if(event->button() == Qt::LeftButton)
    {
        PhotoEditViewScene *pEditScene = dynamic_cast<PhotoEditViewScene*>(this->getScene());
        if ( pEditScene )
        {
            pEditScene->selectItm(this, NULL);
        }
    }

    this->scene()->update();
}

QList<QRectF> CalViewItm::split_rect(const QRectF& rect, int row, int col)
{
    QList<QRectF> lists;
    QRectF r(rect);
    qreal w = rect.width()/col;
    qreal h = rect.height()/row;
    r.setHeight(h);
    r.setWidth(w);

    for( int i = 0; i < row; i++ )
    {
        for( int j = 0; j < col; j++ )
        {
            QRectF r2 = r.translated(j*w, i*h);
            lists.push_back(r2);
        }
    }

    return lists;
}

void CalViewItm::scale_rect(const QRectF& from, QRectF* to, const qreal* factor, int n)
{
    //we make sure the init state: *to == from
    //*to = from;
    if( n != 4 )
        return;

    if( factor[0] != 0 )
    {
        to->setLeft(from.left() + from.width()*factor[0]/100.0);
    }
    if( factor[1] != 0 )
    {
        to->setTop(from.top() + from.height()*factor[1]/100.0);
    }
    if( factor[2] != 0 )
    {
        to->setRight(from.right() - from.width()*factor[2]/100.0);
    }
    if( factor[3] != 0 )
    {
        to->setBottom(from.bottom() - from.height()*factor[3]/100.0);
    }
}

void CalViewItm::align_flag(HorAlignment hor, VerAlignment ver, int *flag)
{
    if( hor == HorLeftAlig )
    {
        *flag |= Qt::AlignLeft;
    }
    else if( hor == HorCenterAlig )
    {
        *flag |= Qt::AlignHCenter;
    }
    else if( hor == HorRightAlig )
    {
        *flag |= Qt::AlignRight;
    }
    if( ver == VerTopAlig )
    {
        *flag |= Qt::AlignTop;
    }
    else if( ver == VerCenterAlig )
    {
        *flag |= Qt::AlignVCenter;
    }
    else if( ver == VerBottomAlig )
    {
        *flag |= Qt::AlignBottom;
    }
}

/*********************************************************/
/********** A4 type 1 Cal***************/
/*********************************************************/
A4Cal1ViewItm::A4Cal1ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene,
                  QGraphicsItem * parent)
    :CalViewItm(pos,size,margin,scene,parent)
{
    CalendarInfo ci;
    WeekdaysInfo wi;
    MonthYearInfo mi;

    this->loadDefaultInfo(&ci, &wi, &mi);
    this->setCalInfo(ci);
    this->setWeekdaysInfo(wi);
    this->setMonthYearInfo(mi);
}

A4Cal1ViewItm::~A4Cal1ViewItm()
{
    //do nth
}

void A4Cal1ViewItm::loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi)
{
    //CalendarInfo()
    {
        ci->font = QFont("Trebuchet MS");
        ci->font.setBold(false);
        ci->font.setItalic(false);
        ci->font.setUnderline(false);
        ci->color = Qt::black;
        ci->hor = HorCenterAlig;
        ci->ver = VerBottomAlig;
        ci->height_in_cell = 37;

        ci->bg_color = Qt::transparent;
        ci->row_color = Qt::transparent;
        ci->cell_color = Qt::lightGray;
        for(int i = 1; i < 8; i++)
        {
            if( i != Qt::Sunday && i != Qt::Saturday )
            {
               ci->everyday_color[i-1] = ci->color;
            }
            else if( i == Qt::Saturday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
            else if( i == Qt::Sunday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
        }

        ci->line_space[0] = 0;
        ci->line_space[1] = 0;
        ci->line_space[2] = 0;
        ci->line_space[3] = 0;
        ci->line_padding[0] = 0;
        ci->line_padding[1] = 0;
        ci->line_padding[2] = 0;
        ci->line_padding[3] = 0;

        ci->cell_space[0] = 7;
        ci->cell_space[1] = 7;
        ci->cell_space[2] = 7;
        ci->cell_space[3] = 7;
        ci->cell_padding[0] = 0;
        ci->cell_padding[1] = 0;
        ci->cell_padding[2] = 0;
        ci->cell_padding[3] = 7;
    }

    //WeekdaysInfo()
    {
        wi->show = true;
        wi->size_of_region = 18;

        wi->font = QFont("Trebuchet MS");
        wi->font.setBold(true);
        wi->font.setItalic(false);
        wi->font.setUnderline(false);
        wi->color = Qt::black;
        wi->hor = HorCenterAlig;
        wi->ver = VerCenterAlig;
        wi->height_in_cell = 33;

        wi->row_color = Qt::lightGray;
        wi->cell_color = Qt::transparent;

        wi->line_space[0] = 1;
        wi->line_space[1] = 10;
        wi->line_space[2] = 1;
        wi->line_space[3] = 35;
        wi->line_padding[0] = 0;
        wi->line_padding[1] = 0;
        wi->line_padding[2] = 0;
        wi->line_padding[3] = 0;

        wi->cell_space[0] = 0;
        wi->cell_space[1] = 0;
        wi->cell_space[2] = 0;
        wi->cell_space[3] = 0;
        wi->cell_padding[0] = 0;
        wi->cell_padding[1] = 0;
        wi->cell_padding[2] = 0;
        wi->cell_padding[3] = 0;
    }

    //MonthYearInfo()
    {
        mi->show = true;
        mi->size_of_region = 15;
        mi->bottom = false;
        mi->doublespace = false;

        mi->font = QFont("Trebuchet MS");
        mi->font.setBold(false);
        mi->font.setItalic(true);
        mi->font.setUnderline(false);
        mi->color = Qt::black;
        mi->hor = HorCenterAlig;
        mi->ver = VerCenterAlig;
        mi->height_in_cell = 40;

        mi->row_color = Qt::transparent;

        mi->line_space[0] = 0;
        mi->line_space[1] = 0;
        mi->line_space[2] = 0;
        mi->line_space[3] = 0;
        mi->line_padding[0] = 0;
        mi->line_padding[1] = 0;
        mi->line_padding[2] = 0;
        mi->line_padding[3] = 0;
    }
}

void A4Cal1ViewItm::drawWeekdays(QPainter *painter, const QRectF& rect, const WeekdaysInfo& wi, const QDate& d)
{
    Q_UNUSED(d);

    QRectF rect_space(rect);
    scale_rect(rect, &rect_space, wi.line_space, 4);

    painter->setPen(Qt::NoPen);
    if( wi.row_color == Qt::transparent )
        painter->setBrush(Qt::NoBrush);
    else
        painter->setBrush(wi.row_color);
    painter->drawRect(rect_space);

    QRectF rect_padding(rect_space);
    scale_rect(rect_space, &rect_padding, wi.line_padding, 4);
    QList<QRectF> cell_rects = split_rect(rect_padding, 1, 7);
    QString week_strs[7] = {tr("Mo"), tr("Tu"), tr("We"), tr("Th"), tr("Fr"), tr("Sa"), tr("Su")};
    for( int i = 0; i < 7; i++ )
        drawWeekdays_cell(painter, cell_rects[i], week_strs[i], wi);
}

void A4Cal1ViewItm::drawCalendar(QPainter *painter, const QRectF& rect, const CalendarInfo& ci, const QDate& d)
{
    int row = d.daysInMonth() + d.dayOfWeek() - 1;
    if( row%7 == 0 )
        row = row/7;
    else
        row = row/7 + 1;

    QList<QRectF> line_rects = split_rect(rect, row, 1);
    QDate date = d;
    int days = 0;
    for( int i = 0; i < row; i++ )
    {
        QRectF rect_space(line_rects[i]);
        scale_rect(line_rects[i], &rect_space, ci.line_space, 4);

        painter->setPen(Qt::NoPen);
        if( ci.row_color == Qt::transparent )
            painter->setBrush(Qt::NoBrush);
        else
            painter->setBrush(ci.row_color);
        painter->drawRect(rect_space);

        QRectF rect_padding(rect_space);
        scale_rect(rect_space, &rect_padding, ci.line_padding, 4);
        QList<QRectF> cell_rects = split_rect(rect_padding, 1, 7);
        for( int j = 0; j < 7; j++ )
        {
            if( days < d.daysInMonth() )
            {
                if( (i == 0 && date.dayOfWeek() - 1 == j) || i > 0 )
                {
                    drawCalendar_cell(painter, cell_rects[j], QString("%1").arg(++days), ci.everyday_color[date.dayOfWeek()-1], ci);
                    date = date.addDays(1);
                }
            }
            else
                break;
        }
    }
}

/*********************************************************/
/********** A4 type 2 Cal***************/
/*********************************************************/
A4Cal2ViewItm::A4Cal2ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene,
                  QGraphicsItem * parent)
    :A4Cal1ViewItm(pos, size, margin, scene, parent)
{
    CalendarInfo ci;
    WeekdaysInfo wi;
    MonthYearInfo mi;

    this->loadDefaultInfo(&ci, &wi, &mi);
    this->setCalInfo(ci);
    this->setWeekdaysInfo(wi);
    this->setMonthYearInfo(mi);
}

A4Cal2ViewItm::~A4Cal2ViewItm()
{
}

void A4Cal2ViewItm::loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi)
{
    //CalendarInfo()
    {
        ci->font = QFont("Trebuchet MS");
        ci->font.setBold(false);
        ci->font.setItalic(false);
        ci->font.setUnderline(false);
        ci->color = Qt::black;
        ci->hor = HorCenterAlig;
        ci->ver = VerCenterAlig;
        ci->height_in_cell = 70;

        ci->bg_color = Qt::lightGray;
        ci->row_color = Qt::white;
        ci->cell_color = Qt::transparent;
        for(int i = 1; i < 8; i++)
        {
            if( i != Qt::Sunday && i != Qt::Saturday )
            {
               ci->everyday_color[i-1] = ci->color;
            }
            else if( i == Qt::Saturday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
            else if( i == Qt::Sunday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
        }

        ci->line_space[0] = 0;
        ci->line_space[1] = 10;
        ci->line_space[2] = 0;
        ci->line_space[3] = 10;
        ci->line_padding[0] = 5;
        ci->line_padding[1] = 0;
        ci->line_padding[2] = 5;
        ci->line_padding[3] = 0;

        ci->cell_space[0] = 0;
        ci->cell_space[1] = 0;
        ci->cell_space[2] = 0;
        ci->cell_space[3] = 0;
        ci->cell_padding[0] = 0;
        ci->cell_padding[1] = 0;
        ci->cell_padding[2] = 0;
        ci->cell_padding[3] = 0;
    }

    //WeekdaysInfo()
    {
        wi->show = true;
        wi->size_of_region = 18;

        wi->font = QFont("Trebuchet MS");
        wi->font.setBold(true);
        wi->font.setItalic(false);
        wi->font.setUnderline(false);
        wi->color = Qt::black;
        wi->hor = HorCenterAlig;
        wi->ver = VerCenterAlig;
        wi->height_in_cell = 47;

        wi->row_color = Qt::lightGray;
        wi->cell_color = Qt::transparent;

        wi->line_space[0] = 0;
        wi->line_space[1] = 0;
        wi->line_space[2] = 0;
        wi->line_space[3] = 30;
        wi->line_padding[0] = 5;
        wi->line_padding[1] = 0;
        wi->line_padding[2] = 5;
        wi->line_padding[3] = 0;

        wi->cell_space[0] = 0;
        wi->cell_space[1] = 0;
        wi->cell_space[2] = 0;
        wi->cell_space[3] = 0;
        wi->cell_padding[0] = 0;
        wi->cell_padding[1] = 0;
        wi->cell_padding[2] = 0;
        wi->cell_padding[3] = 0;
    }

    //MonthYearInfo()
    {
        mi->show = true;
        mi->size_of_region = 20;
        mi->bottom = true;
        mi->doublespace = false;

        mi->font = QFont("Trebuchet MS");
        mi->font.setBold(false);
        mi->font.setItalic(true);
        mi->font.setUnderline(false);
        mi->color = Qt::black;
        mi->hor = HorCenterAlig;
        mi->ver = VerCenterAlig;
        mi->height_in_cell = 45;

        mi->row_color = Qt::transparent;

        mi->line_space[0] = 0;
        mi->line_space[1] = 0;
        mi->line_space[2] = 0;
        mi->line_space[3] = 0;
        mi->line_padding[0] = 0;
        mi->line_padding[1] = 0;
        mi->line_padding[2] = 0;
        mi->line_padding[3] = 0;
    }
}


/*********************************************************/
/********** A4 type 3 Cal***************/
/*********************************************************/
A4Cal3ViewItm::A4Cal3ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene,
                  QGraphicsItem * parent)
    :CalViewItm(pos,size,margin,scene,parent)
{
    CalendarInfo ci;
    WeekdaysInfo wi;
    MonthYearInfo mi;

    this->loadDefaultInfo(&ci, &wi, &mi);
    this->setCalInfo(ci);
    this->setWeekdaysInfo(wi);
    this->setMonthYearInfo(mi);
}

A4Cal3ViewItm::~A4Cal3ViewItm()
{
    //do nth
}

void A4Cal3ViewItm::loadDefaultInfo(CalendarInfo *ci, WeekdaysInfo *wi, MonthYearInfo *mi)
{
    //CalendarInfo()
    {
        ci->font = QFont("Trebuchet MS");
        ci->font.setBold(false);
        ci->font.setItalic(false);
        ci->font.setUnderline(false);
        ci->color = Qt::black;
        ci->hor = HorCenterAlig;
        ci->ver = VerCenterAlig;
        ci->height_in_cell = 45;

        ci->bg_color = Qt::transparent;
        ci->row_color = Qt::transparent;
        ci->cell_color = Qt::transparent;
        for(int i = 1; i < 8; i++)
        {
            if( i != Qt::Sunday && i != Qt::Saturday )
            {
               ci->everyday_color[i-1] = ci->color;
            }
            else if( i == Qt::Saturday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
            else if( i == Qt::Sunday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
        }

        ci->line_space[0] = 0;
        ci->line_space[1] = 0;
        ci->line_space[2] = 0;
        ci->line_space[3] = 0;
        ci->line_padding[0] = 0;
        ci->line_padding[1] = 0;
        ci->line_padding[2] = 0;
        ci->line_padding[3] = 0;

        ci->cell_space[0] = 0;
        ci->cell_space[1] = 0;
        ci->cell_space[2] = 0;
        ci->cell_space[3] = 0;
        ci->cell_padding[0] = 0;
        ci->cell_padding[1] = 0;
        ci->cell_padding[2] = 0;
        ci->cell_padding[3] = 0;
    }

    //WeekdaysInfo()
    {
        wi->show = false;
        wi->size_of_region = 15;

        wi->font = QFont("Arial");
        wi->font.setBold(false);
        wi->font.setItalic(false);
        wi->font.setUnderline(false);
        wi->color = Qt::black;
        wi->hor = HorCenterAlig;
        wi->ver = VerCenterAlig;
        wi->height_in_cell = 50;

        wi->row_color = Qt::transparent;
        wi->cell_color = Qt::transparent;

        wi->line_space[0] = 0;
        wi->line_space[1] = 0;
        wi->line_space[2] = 0;
        wi->line_space[3] = 0;
        wi->line_padding[0] = 0;
        wi->line_padding[1] = 0;
        wi->line_padding[2] = 0;
        wi->line_padding[3] = 0;

        wi->cell_space[0] = 0;
        wi->cell_space[1] = 0;
        wi->cell_space[2] = 0;
        wi->cell_space[3] = 0;
        wi->cell_padding[0] = 0;
        wi->cell_padding[1] = 0;
        wi->cell_padding[2] = 0;
        wi->cell_padding[3] = 0;
    }

    //MonthYearInfo()
    {
        mi->show = true;
        mi->size_of_region = 55;
        mi->bottom = false;
        mi->doublespace = false;

        mi->font = QFont("Trebuchet MS");
        mi->font.setBold(false);
        mi->font.setItalic(true);
        mi->font.setUnderline(false);
        mi->color = Qt::black;
        mi->hor = HorRightAlig;
        mi->ver = VerCenterAlig;
        mi->height_in_cell = 80;

        mi->row_color = Qt::transparent;

        mi->line_space[0] = 0;
        mi->line_space[1] = 0;
        mi->line_space[2] = 0;
        mi->line_space[3] = 0;
        mi->line_padding[0] = 0;
        mi->line_padding[1] = 0;
        mi->line_padding[2] = 0;
        mi->line_padding[3] = 0;
    }
}

void A4Cal3ViewItm::drawWeekdays(QPainter *painter, const QRectF& rect, const WeekdaysInfo& wi, const QDate& d)
{
    int days = d.daysInMonth();

    QRectF rect_space(rect);
    scale_rect(rect, &rect_space, wi.line_space, 4);

    painter->setPen(Qt::NoPen);
    if( wi.row_color == Qt::transparent )
        painter->setBrush(Qt::NoBrush);
    else
        painter->setBrush(wi.row_color);
    painter->drawRect(rect_space);

    QRectF rect_padding(rect_space);
    scale_rect(rect_space, &rect_padding, wi.line_padding, 4);
    QList<QRectF> cell_rects = split_rect(rect_padding, 1, days);
    QString week_strs[7] = {tr("Mo"), tr("Tu"), tr("We"), tr("Th"), tr("Fr"), tr("Sa"), tr("Su")};
    for( int i = 0, j = d.dayOfWeek() - 1; i < days; i++, j++ )
    {
        drawWeekdays_cell(painter, cell_rects[i], week_strs[j%7], wi);
    }
}

void A4Cal3ViewItm::drawCalendar(QPainter *painter, const QRectF& rect, const CalendarInfo& ci, const QDate& d)
{
    int days = d.daysInMonth();

    QRectF rect_space(rect);
    scale_rect(rect, &rect_space, ci.line_space, 4);

    painter->setPen(Qt::NoPen);
    if( ci.row_color == Qt::transparent )
        painter->setBrush(Qt::NoBrush);
    else
        painter->setBrush(ci.row_color);
    painter->drawRect(rect_space);

    QRectF rect_padding(rect_space);
    scale_rect(rect_space, &rect_padding, ci.line_padding, 4);
    QList<QRectF> cell_rects = split_rect(rect_padding, 1, days);
    for( int i = 0, j = d.dayOfWeek() - 1; i < days; i++, j++ )
    {
        drawCalendar_cell(painter, cell_rects[i], QString("%1").arg(i+1), ci.everyday_color[j%7], ci);
    }
}

/*********************************************************/
/********** A4 type 4 Cal***************/
/*********************************************************/
A4Cal4ViewItm::A4Cal4ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene,
                  QGraphicsItem * parent)
    :CalViewItm(pos,size,margin,scene,parent)
{
    CalendarInfo ci;
    WeekdaysInfo wi;
    MonthYearInfo mi;

    this->loadDefaultInfo(&ci, &wi, &mi);
    this->setCalInfo(ci);
    this->setWeekdaysInfo(wi);
    this->setMonthYearInfo(mi);
}

A4Cal4ViewItm::~A4Cal4ViewItm()
{
    //do nth
}

void A4Cal4ViewItm::loadDefaultInfo(CalendarInfo *ci, WeekdaysInfo *wi, MonthYearInfo *mi)
{
    //CalendarInfo()
    {
        ci->font = QFont("Trebuchet MS");
        ci->font.setBold(true);
        ci->font.setItalic(false);
        ci->font.setUnderline(false);
        ci->color = Qt::black;
        ci->hor = HorRightAlig;
        ci->ver = VerCenterAlig;
        ci->height_in_cell = 60;

        ci->bg_color = Qt::transparent;
        ci->row_color = Qt::transparent;
        ci->cell_color = Qt::transparent;
        for(int i = 1; i < 8; i++)
        {
            if( i != Qt::Sunday && i != Qt::Saturday )
            {
               ci->everyday_color[i-1] = ci->color;
            }
            else if( i == Qt::Saturday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
            else if( i == Qt::Sunday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
        }

        ci->line_space[0] = 0;
        ci->line_space[1] = 0;
        ci->line_space[2] = 0;
        ci->line_space[3] = 0;
        ci->line_padding[0] = 0;
        ci->line_padding[1] = 4;
        ci->line_padding[2] = 22;
        ci->line_padding[3] = 4;

        ci->cell_space[0] = 0;
        ci->cell_space[1] = 0;
        ci->cell_space[2] = 0;
        ci->cell_space[3] = 0;
        ci->cell_padding[0] = 0;
        ci->cell_padding[1] = 0;
        ci->cell_padding[2] = 0;
        ci->cell_padding[3] = 0;
    }

    //WeekdaysInfo()
    {
        wi->show = false;
        wi->size_of_region = 15;

        wi->font = QFont("Arial");
        wi->font.setBold(false);
        wi->font.setItalic(false);
        wi->font.setUnderline(false);
        wi->color = Qt::black;
        wi->hor = HorCenterAlig;
        wi->ver = VerCenterAlig;
        wi->height_in_cell = 50;

        wi->row_color = Qt::transparent;
        wi->cell_color = Qt::transparent;

        wi->line_space[0] = 0;
        wi->line_space[1] = 0;
        wi->line_space[2] = 0;
        wi->line_space[3] = 0;
        wi->line_padding[0] = 2;
        wi->line_padding[1] = 4;
        wi->line_padding[2] = 22;
        wi->line_padding[3] = 4;

        wi->cell_space[0] = 0;
        wi->cell_space[1] = 0;
        wi->cell_space[2] = 0;
        wi->cell_space[3] = 0;
        wi->cell_padding[0] = 0;
        wi->cell_padding[1] = 0;
        wi->cell_padding[2] = 0;
        wi->cell_padding[3] = 0;
    }

    //MonthYearInfo()
    {
        mi->show = true;
        mi->size_of_region = 6.7;
        mi->bottom = true;
        mi->doublespace = true;

        mi->font = QFont("Trebuchet MS");
        mi->font.setBold(false);
        mi->font.setItalic(true);
        mi->font.setUnderline(false);
        mi->color = Qt::black;
        mi->hor = HorRightAlig;
        mi->ver = VerCenterAlig;
        mi->height_in_cell = 35;

        mi->row_color = Qt::gray;

        mi->line_space[0] = 0;
        mi->line_space[1] = 0;
        mi->line_space[2] = -2;
        mi->line_space[3] = 0;
        mi->line_padding[0] = 0;
        mi->line_padding[1] = 0;
        mi->line_padding[2] = 22;
        mi->line_padding[3] = 0;
    }
}

void A4Cal4ViewItm::drawContent(QPainter *painter, const QRectF &rect, const CalendarInfo &ci, const WeekdaysInfo &wi, const MonthYearInfo &mi, const QDate &d)
{
    qreal cal_hight_region = 100;
    if( mi.show )
        cal_hight_region -= mi.size_of_region;

    QRectF rect_monthyear(rect);
    QRectF rect_weekdays(rect);
    QRectF rect_calendar(rect);

    if( mi.bottom )
    {
        if( cal_hight_region <= 0 )
        {
            QMessageBox msgBox;
            msgBox.setText(QString("MonthYear(%1) size of region >= 100")
                           .arg(mi.size_of_region));
            msgBox.exec();
        }
        else
        {
            qreal cal_width_region = 100;
            if( wi.show )
                cal_width_region -= wi.size_of_region;

            if( wi.show )
            {
                Q_ASSERT(wi.size_of_region > 0);
                rect_weekdays.setTop(rect.top());
                rect_weekdays.setHeight(rect.height()*cal_hight_region/100.0);
                rect_weekdays.setWidth(rect.width()*wi.size_of_region/100.0);

                drawWeekdays(painter, rect_weekdays, wi, d);
            }
            else
            {
                rect_weekdays.setHeight(0.0);
                rect_weekdays.setWidth(0.0);
            }

            if( cal_width_region <= 0 )
            {
                QMessageBox msgBox;
                msgBox.setText(QString("Weekdays(%1) size of region >= 100")
                               .arg(wi.size_of_region));
                msgBox.exec();
            }
            else
            {
                rect_calendar.setTop(rect.top());
                rect_calendar.setHeight(rect.height()*cal_hight_region/100.0);
                rect_calendar.setWidth(rect.width()*cal_width_region/100.0);
                rect_calendar.translate(rect_weekdays.width(), 0.0);

                drawCalendar(painter, rect_calendar, ci, d);
            }
        }

        if( mi.show )
        {
            Q_ASSERT(mi.size_of_region > 0);
            rect_monthyear.setTop(rect.top() + rect_calendar.height());
            rect_monthyear.setHeight(rect.height()*mi.size_of_region/100.0);

            drawMonthYear(painter, rect_monthyear, mi, d);
        }
        else
        {
            rect_monthyear.setHeight(0.0);
        }
    }
    else
    {
        if( mi.show )
        {
            Q_ASSERT(mi.size_of_region > 0);
            rect_monthyear.setTop(rect.top());
            rect_monthyear.setHeight(rect.height()*mi.size_of_region/100.0);

            drawMonthYear(painter, rect_monthyear, mi, d);
        }
        else
        {
            rect_monthyear.setHeight(0.0);
        }

        if( cal_hight_region <= 0 )
        {
            QMessageBox msgBox;
            msgBox.setText(QString("MonthYear(%1) size of region >= 100")
                           .arg(mi.size_of_region));
            msgBox.exec();
        }
        else
        {
            qreal cal_width_region = 100;
            if( wi.show )
                cal_width_region -= wi.size_of_region;

            if( wi.show )
            {
                Q_ASSERT(wi.size_of_region > 0);
                rect_weekdays.setTop(rect.top() + rect_monthyear.height());
                rect_weekdays.setHeight(rect.height()*cal_hight_region/100.0);
                rect_weekdays.setWidth(rect.width()*wi.size_of_region/100.0);

                drawWeekdays(painter, rect_weekdays, wi, d);
            }
            else
            {
                rect_weekdays.setHeight(0.0);
                rect_weekdays.setWidth(0.0);
            }

            if( cal_width_region <= 0 )
            {
                QMessageBox msgBox;
                msgBox.setText(QString("Weekdays(%1) size of region >= 100")
                               .arg(wi.size_of_region));
                msgBox.exec();
            }
            else
            {
                rect_calendar.setTop(rect.top() + rect_monthyear.height());
                rect_calendar.setHeight(rect.height()*cal_hight_region/100.0);
                rect_calendar.setWidth(rect.width()*cal_width_region/100.0);
                rect_calendar.translate(rect_weekdays.width(), 0.0);

                drawCalendar(painter, rect_calendar, ci, d);
            }
        }
    }
}

void A4Cal4ViewItm::drawWeekdays(QPainter *painter, const QRectF& rect, const WeekdaysInfo& wi, const QDate& d)
{
    int days = d.daysInMonth();

    QRectF rect_space(rect);
    scale_rect(rect, &rect_space, wi.line_space, 4);

    painter->setPen(Qt::NoPen);
    if( wi.row_color == Qt::transparent )
        painter->setBrush(Qt::NoBrush);
    else
        painter->setBrush(wi.row_color);
    painter->drawRect(rect_space);

    QRectF rect_padding(rect_space);
    scale_rect(rect_space, &rect_padding, wi.line_padding, 4);
    QList<QRectF> cell_rects = split_rect(rect_padding, days, 1);
    QString week_strs[7] = {tr("Mo"), tr("Tu"), tr("We"), tr("Th"), tr("Fr"), tr("Sa"), tr("Su")};
    for( int i = 0, j = d.dayOfWeek() - 1; i < days; i++, j++ )
    {
        drawWeekdays_cell(painter, cell_rects[i], week_strs[j%7], wi);
    }
}

void A4Cal4ViewItm::drawCalendar(QPainter *painter, const QRectF& rect, const CalendarInfo& ci, const QDate& d)
{
    int days = d.daysInMonth();

    QRectF rect_space(rect);
    scale_rect(rect, &rect_space, ci.line_space, 4);

    painter->setPen(Qt::NoPen);
    if( ci.row_color == Qt::transparent )
        painter->setBrush(Qt::NoBrush);
    else
        painter->setBrush(ci.row_color);
    painter->drawRect(rect_space);

    QRectF rect_padding(rect_space);
    scale_rect(rect_space, &rect_padding, ci.line_padding, 4);
    QList<QRectF> cell_rects = split_rect(rect_padding, days, 1);
    for( int i = 0, j = d.dayOfWeek() - 1; i < days; i++, j++ )
    {
        drawCalendar_cell(painter, cell_rects[i], QString("%1").arg(i+1), ci.everyday_color[j%7], ci);
    }
}

/*********************************************************/
/********** A5 type 1 Cal***************/
/*********************************************************/
A5Cal1ViewItm::A5Cal1ViewItm(const QPointF &pos, const QSize &size, const QMargins &margin, PmViewScnen *scene, QGraphicsItem *parent)
    :A4Cal1ViewItm(pos,size,margin,scene,parent)
{
    qDebug() << "A5Cal1ViewItm Ctr";
    CalendarInfo ci;
    WeekdaysInfo wi;
    MonthYearInfo mi;

    this->loadDefaultInfo(&ci, &wi, &mi);
    this->setCalInfo(ci);
    this->setWeekdaysInfo(wi);
    this->setMonthYearInfo(mi);
}

A5Cal1ViewItm::~A5Cal1ViewItm()
{

}

void A5Cal1ViewItm::loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi)
{
    //CalendarInfo()
    {
        ci->font = QFont("Trebuchet MS");
        ci->font.setBold(false);
        ci->font.setItalic(false);
        ci->font.setUnderline(false);
        ci->color = Qt::black;
        ci->hor = HorCenterAlig;
        ci->ver = VerCenterAlig;
        ci->height_in_cell = 70;

        ci->bg_color = Qt::lightGray;
        ci->row_color = Qt::white;
        ci->cell_color = Qt::transparent;
        for(int i = 1; i < 8; i++)
        {
            if( i != Qt::Sunday && i != Qt::Saturday )
            {
               ci->everyday_color[i-1] = ci->color;
            }
            else if( i == Qt::Saturday )
            {
               ci->everyday_color[i-1] = Qt::gray;
            }
            else if( i == Qt::Sunday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
        }

        ci->line_space[0] = 0;
        ci->line_space[1] = 32;
        ci->line_space[2] = 0;
        ci->line_space[3] = 32;
        ci->line_padding[0] = 5;
        ci->line_padding[1] = 0;
        ci->line_padding[2] = 5;
        ci->line_padding[3] = 0;

        ci->cell_space[0] = 0;
        ci->cell_space[1] = 0;
        ci->cell_space[2] = 0;
        ci->cell_space[3] = 0;
        ci->cell_padding[0] = 0;
        ci->cell_padding[1] = 0;
        ci->cell_padding[2] = 0;
        ci->cell_padding[3] = 0;
    }

    //WeekdaysInfo()
    {
        wi->show = true;
        wi->size_of_region = 13;

        wi->font = QFont("Trebuchet MS");
        wi->font.setBold(true);
        wi->font.setItalic(false);
        wi->font.setUnderline(false);
        wi->color = Qt::black;
        wi->hor = HorCenterAlig;
        wi->ver = VerCenterAlig;
        wi->height_in_cell = 47;

        wi->row_color = Qt::lightGray;
        wi->cell_color = Qt::transparent;

        wi->line_space[0] = 0;
        wi->line_space[1] = 0;
        wi->line_space[2] = 0;
        wi->line_space[3] = 47;
        wi->line_padding[0] = 5;
        wi->line_padding[1] = 0;
        wi->line_padding[2] = 5;
        wi->line_padding[3] = 0;

        wi->cell_space[0] = 0;
        wi->cell_space[1] = 0;
        wi->cell_space[2] = 0;
        wi->cell_space[3] = 0;
        wi->cell_padding[0] = 0;
        wi->cell_padding[1] = 0;
        wi->cell_padding[2] = 0;
        wi->cell_padding[3] = 0;
    }

    //MonthYearInfo()
    {
        mi->show = true;
        mi->size_of_region = 20;
        mi->bottom = true;
        mi->doublespace = true;

        mi->font = QFont("Trebuchet MS");
        mi->font.setBold(false);
        mi->font.setItalic(true);
        mi->font.setUnderline(false);
        mi->color = Qt::white;
        mi->hor = HorCenterAlig;
        mi->ver = VerCenterAlig;
        mi->height_in_cell = 45;

        mi->row_color = Qt::black;

        mi->line_space[0] = 0;
        mi->line_space[1] = 30;
        mi->line_space[2] = 0;
        mi->line_space[3] = -2;
        mi->line_padding[0] = 0;
        mi->line_padding[1] = 0;
        mi->line_padding[2] = 0;
        mi->line_padding[3] = 0;
    }
}


/*********************************************************/
/********** A5 type 2 Cal***************/
/*********************************************************/
A5Cal2ViewItm::A5Cal2ViewItm(const QPointF &pos, const QSize &size, const QMargins &margin, PmViewScnen *scene, QGraphicsItem *parent)
    :A4Cal1ViewItm(pos,size,margin,scene,parent)
{
    CalendarInfo ci;
    WeekdaysInfo wi;
    MonthYearInfo mi;

    this->loadDefaultInfo(&ci, &wi, &mi);
    this->setCalInfo(ci);
    this->setWeekdaysInfo(wi);
    this->setMonthYearInfo(mi);
}

A5Cal2ViewItm::~A5Cal2ViewItm()
{

}

void A5Cal2ViewItm::loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi)
{
    //CalendarInfo()
    {
        ci->font = QFont("Trebuchet MS");
        ci->font.setBold(false);
        ci->font.setItalic(false);
        ci->font.setUnderline(false);
        ci->color = Qt::black;
        ci->hor = HorCenterAlig;
        ci->ver = VerCenterAlig;
        ci->height_in_cell = 47;

        ci->bg_color = Qt::transparent;
        ci->row_color = Qt::transparent;
        ci->cell_color = Qt::transparent;
        for(int i = 1; i < 8; i++)
        {
            if( i != Qt::Sunday && i != Qt::Saturday )
            {
               ci->everyday_color[i-1] = ci->color;
            }
            else if( i == Qt::Saturday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
            else if( i == Qt::Sunday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
        }

        ci->line_space[0] = 0;
        ci->line_space[1] = 0;
        ci->line_space[2] = 0;
        ci->line_space[3] = 0;
        ci->line_padding[0] = 5;
        ci->line_padding[1] = 0;
        ci->line_padding[2] = 5;
        ci->line_padding[3] = 0;

        ci->cell_space[0] = 0;
        ci->cell_space[1] = 0;
        ci->cell_space[2] = 0;
        ci->cell_space[3] = 0;
        ci->cell_padding[0] = 0;
        ci->cell_padding[1] = 0;
        ci->cell_padding[2] = 0;
        ci->cell_padding[3] = 0;
    }

    //WeekdaysInfo()
    {
        wi->show = true;
        wi->size_of_region = 13;

        wi->font = QFont("Trebuchet MS");
        wi->font.setBold(true);
        wi->font.setItalic(false);
        wi->font.setUnderline(false);
        wi->color = Qt::white;
        wi->hor = HorCenterAlig;
        wi->ver = VerCenterAlig;
        wi->height_in_cell = 45;

        wi->row_color = Qt::darkGray;
        wi->cell_color = Qt::transparent;

        wi->line_space[0] = 0;
        wi->line_space[1] = 0;
        wi->line_space[2] = 0;
        wi->line_space[3] = 0;
        wi->line_padding[0] = 5;
        wi->line_padding[1] = 0;
        wi->line_padding[2] = 5;
        wi->line_padding[3] = 0;

        wi->cell_space[0] = 0;
        wi->cell_space[1] = 0;
        wi->cell_space[2] = 0;
        wi->cell_space[3] = 0;
        wi->cell_padding[0] = 0;
        wi->cell_padding[1] = 0;
        wi->cell_padding[2] = 0;
        wi->cell_padding[3] = 0;
    }

    //MonthYearInfo()
    {
        mi->show = true;
        mi->size_of_region = 15;
        mi->bottom = false;
        mi->doublespace = false;

        mi->font = QFont("Trebuchet MS");
        mi->font.setBold(false);
        mi->font.setItalic(true);
        mi->font.setUnderline(false);
        mi->color = Qt::black;
        mi->hor = HorCenterAlig;
        mi->ver = VerCenterAlig;
        mi->height_in_cell = 60;

        mi->row_color = Qt::transparent;

        mi->line_space[0] = 0;
        mi->line_space[1] = 0;
        mi->line_space[2] = 0;
        mi->line_space[3] = 0;
        mi->line_padding[0] = 0;
        mi->line_padding[1] = 0;
        mi->line_padding[2] = 0;
        mi->line_padding[3] = 0;
    }
}


/*********************************************************/
/********** A5 type 3 Cal***************/
/*********************************************************/
A5Cal3ViewItm::A5Cal3ViewItm(const QPointF &pos, const QSize &size, const QMargins &margin, PmViewScnen *scene, QGraphicsItem *parent)
    :A4Cal3ViewItm(pos,size,margin,scene,parent)
{
    CalendarInfo ci;
    WeekdaysInfo wi;
    MonthYearInfo mi;

    this->loadDefaultInfo(&ci, &wi, &mi);
    this->setCalInfo(ci);
    this->setWeekdaysInfo(wi);
    this->setMonthYearInfo(mi);
}

A5Cal3ViewItm::~A5Cal3ViewItm()
{

}

void A5Cal3ViewItm::loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi)
{
    //CalendarInfo()
    {
        ci->font = QFont("Trebuchet MS");
        ci->font.setBold(false);
        ci->font.setItalic(false);
        ci->font.setUnderline(false);
        ci->color = Qt::black;
        ci->hor = HorCenterAlig;
        ci->ver = VerCenterAlig;
        ci->height_in_cell = 40;

        ci->bg_color = Qt::transparent;
        ci->row_color = Qt::transparent;
        ci->cell_color = Qt::transparent;
        for(int i = 1; i < 8; i++)
        {
            if( i != Qt::Sunday && i != Qt::Saturday )
            {
               ci->everyday_color[i-1] = ci->color;
            }
            else if( i == Qt::Saturday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
            else if( i == Qt::Sunday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
        }

        ci->line_space[0] = 0;
        ci->line_space[1] = 0;
        ci->line_space[2] = 0;
        ci->line_space[3] = 0;
        ci->line_padding[0] = 0;
        ci->line_padding[1] = 0;
        ci->line_padding[2] = 0;
        ci->line_padding[3] = 0;

        ci->cell_space[0] = 0;
        ci->cell_space[1] = 0;
        ci->cell_space[2] = 0;
        ci->cell_space[3] = 0;
        ci->cell_padding[0] = 0;
        ci->cell_padding[1] = 0;
        ci->cell_padding[2] = 0;
        ci->cell_padding[3] = 0;
    }

    //WeekdaysInfo()
    {
        wi->show = false;
        wi->size_of_region = 15;

        wi->font = QFont("Arial");
        wi->font.setBold(false);
        wi->font.setItalic(false);
        wi->font.setUnderline(false);
        wi->color = Qt::black;
        wi->hor = HorCenterAlig;
        wi->ver = VerCenterAlig;
        wi->height_in_cell = 50;

        wi->row_color = Qt::transparent;
        wi->cell_color = Qt::transparent;

        wi->line_space[0] = 0;
        wi->line_space[1] = 0;
        wi->line_space[2] = 0;
        wi->line_space[3] = 0;
        wi->line_padding[0] = 0;
        wi->line_padding[1] = 0;
        wi->line_padding[2] = 0;
        wi->line_padding[3] = 0;

        wi->cell_space[0] = 0;
        wi->cell_space[1] = 0;
        wi->cell_space[2] = 0;
        wi->cell_space[3] = 0;
        wi->cell_padding[0] = 0;
        wi->cell_padding[1] = 0;
        wi->cell_padding[2] = 0;
        wi->cell_padding[3] = 0;
    }

    //MonthYearInfo()
    {
        mi->show = true;
        mi->size_of_region = 50;
        mi->bottom = false;
        mi->doublespace = false;

        mi->font = QFont("Trebuchet MS");
        mi->font.setBold(false);
        mi->font.setItalic(true);
        mi->font.setUnderline(false);
        mi->color = Qt::black;
        mi->hor = HorRightAlig;
        mi->ver = VerCenterAlig;
        mi->height_in_cell = 70;

        mi->row_color = Qt::transparent;

        mi->line_space[0] = 0;
        mi->line_space[1] = 0;
        mi->line_space[2] = 0.8;
        mi->line_space[3] = 0;
        mi->line_padding[0] = 0;
        mi->line_padding[1] = 0;
        mi->line_padding[2] = 0;
        mi->line_padding[3] = 0;
    }
}


/*********************************************************/
/********** A6 type 1 Cal***************/
/*********************************************************/
A6Cal1ViewItm::A6Cal1ViewItm(const QPointF &pos, const QSize &size, const QMargins &margin, PmViewScnen *scene, QGraphicsItem *parent)
    :A4Cal4ViewItm(pos,size,margin,scene,parent)
{
    CalendarInfo ci;
    WeekdaysInfo wi;
    MonthYearInfo mi;

    this->loadDefaultInfo(&ci, &wi, &mi);
    this->setCalInfo(ci);
    this->setWeekdaysInfo(wi);
    this->setMonthYearInfo(mi);
}

A6Cal1ViewItm::~A6Cal1ViewItm()
{

}

void A6Cal1ViewItm::loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi)
{
    //CalendarInfo()
    {
        ci->font = QFont("Trebuchet MS");
        ci->font.setBold(true);
        ci->font.setItalic(false);
        ci->font.setUnderline(false);
        ci->color = Qt::black;
        ci->hor = HorRightAlig;
        ci->ver = VerCenterAlig;
        ci->height_in_cell = 60;

        ci->bg_color = Qt::lightGray;
        ci->row_color = Qt::transparent;
        ci->cell_color = Qt::transparent;
        for(int i = 1; i < 8; i++)
        {
            if( i != Qt::Sunday && i != Qt::Saturday )
            {
               ci->everyday_color[i-1] = ci->color;
            }
            else if( i == Qt::Saturday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
            else if( i == Qt::Sunday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
        }

        ci->line_space[0] = 0;
        ci->line_space[1] = 0;
        ci->line_space[2] = 0;
        ci->line_space[3] = 0;
        ci->line_padding[0] = 0;
        ci->line_padding[1] = 4;
        ci->line_padding[2] = 22;
        ci->line_padding[3] = 4;

        ci->cell_space[0] = 0;
        ci->cell_space[1] = 0;
        ci->cell_space[2] = 0;
        ci->cell_space[3] = 0;
        ci->cell_padding[0] = 0;
        ci->cell_padding[1] = 0;
        ci->cell_padding[2] = 0;
        ci->cell_padding[3] = 0;
    }

    //WeekdaysInfo()
    {
        wi->show = false;
        wi->size_of_region = 15;

        wi->font = QFont("Arial");
        wi->font.setBold(false);
        wi->font.setItalic(false);
        wi->font.setUnderline(false);
        wi->color = Qt::black;
        wi->hor = HorCenterAlig;
        wi->ver = VerCenterAlig;
        wi->height_in_cell = 50;

        wi->row_color = Qt::transparent;
        wi->cell_color = Qt::transparent;

        wi->line_space[0] = 0;
        wi->line_space[1] = 0;
        wi->line_space[2] = 0;
        wi->line_space[3] = 0;
        wi->line_padding[0] = 2;
        wi->line_padding[1] = 4;
        wi->line_padding[2] = 22;
        wi->line_padding[3] = 4;

        wi->cell_space[0] = 0;
        wi->cell_space[1] = 0;
        wi->cell_space[2] = 0;
        wi->cell_space[3] = 0;
        wi->cell_padding[0] = 0;
        wi->cell_padding[1] = 0;
        wi->cell_padding[2] = 0;
        wi->cell_padding[3] = 0;
    }

    //MonthYearInfo()
    {
        mi->show = true;
        mi->size_of_region = 14.3;
        mi->bottom = true;
        mi->doublespace = true;

        mi->font = QFont("Trebuchet MS");
        mi->font.setBold(false);
        mi->font.setItalic(true);
        mi->font.setUnderline(false);
        mi->color = Qt::white;
        mi->hor = HorRightAlig;
        mi->ver = VerCenterAlig;
        mi->height_in_cell = 35;

        mi->row_color = Qt::darkGray;

        mi->line_space[0] = -352;
        mi->line_space[1] = 0;
        mi->line_space[2] = 0;
        mi->line_space[3] = -2;
        mi->line_padding[0] = 0;
        mi->line_padding[1] = 0;
        mi->line_padding[2] = 4.9;
        mi->line_padding[3] = 0;
    }
}


void A6Cal1ViewItm::drawWeekdays(QPainter *painter, const QRectF &rect, const WeekdaysInfo &wi, const QDate &d)
{
    Q_UNUSED(d);

    QRectF rect_space(rect);
    scale_rect(rect, &rect_space, wi.line_space, 4);

    painter->setPen(Qt::NoPen);
    if( wi.row_color == Qt::transparent )
        painter->setBrush(Qt::NoBrush);
    else
        painter->setBrush(wi.row_color);
    painter->drawRect(rect_space);

    QRectF rect_padding(rect_space);
    scale_rect(rect_space, &rect_padding, wi.line_padding, 4);
    QList<QRectF> cell_rects = split_rect(rect_padding, 21, 1);
    QString week_strs[7] = {tr("Mo"), tr("Tu"), tr("We"), tr("Th"), tr("Fr"), tr("Sa"), tr("Su")};
    for( int i = 0; i < 21; i++ )
        drawWeekdays_cell(painter, cell_rects[i], week_strs[i%7], wi);
}

void A6Cal1ViewItm::drawCalendar(QPainter *painter, const QRectF &rect, const CalendarInfo &ci, const QDate &d)
{
    int col = d.daysInMonth() + d.dayOfWeek() - 1;
    if( col%21 == 0 )
        col = col/21;
    else
        col = col/21 + 1;

    QList<QRectF> line_rects = split_rect(rect, 1, col);
    QDate date = d;
    int days = 0;
    for( int i = 0; i < col; i++ )
    {
        QRectF rect_space(line_rects[i]);
        scale_rect(line_rects[i], &rect_space, ci.line_space, 4);

        painter->setPen(Qt::NoPen);
        if( ci.row_color == Qt::transparent )
            painter->setBrush(Qt::NoBrush);
        else
            painter->setBrush(ci.row_color);
        painter->drawRect(rect_space);

        QRectF rect_padding(rect_space);
        scale_rect(rect_space, &rect_padding, ci.line_padding, 4);
        QList<QRectF> cell_rects = split_rect(rect_padding, 21, 1);
        for( int j = 0; j < 21; j++ )
        {
            if( days < d.daysInMonth() )
            {
                if( (i == 0 && date.dayOfWeek() - 1 == j%7) || i > 0 )
                {
                    drawCalendar_cell(painter, cell_rects[j], QString("%1").arg(++days), ci.everyday_color[date.dayOfWeek()-1], ci);
                    date = date.addDays(1);
                }
            }
            else
                break;
        }
    }
}

/*********************************************************/
/********** A6 type 2 Cal***************/
/*********************************************************/
A6Cal2ViewItm::A6Cal2ViewItm(const QPointF &pos, const QSize &size, const QMargins &margin, PmViewScnen *scene, QGraphicsItem *parent)
    :CalViewItm(pos,size,margin,scene,parent)
{
    CalendarInfo ci;
    WeekdaysInfo wi;
    MonthYearInfo mi;

    this->loadDefaultInfo(&ci, &wi, &mi);
    this->setCalInfo(ci);
    this->setWeekdaysInfo(wi);
    this->setMonthYearInfo(mi);
}

A6Cal2ViewItm::~A6Cal2ViewItm()
{

}

void A6Cal2ViewItm::loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi)
{
    //CalendarInfo()
    {
        ci->font = QFont("Trebuchet MS");
        ci->font.setBold(false);
        ci->font.setItalic(false);
        ci->font.setUnderline(false);
        ci->color = Qt::black;
        ci->hor = HorCenterAlig;
        ci->ver = VerCenterAlig;
        ci->height_in_cell = 50;

        ci->bg_color = Qt::transparent;
        ci->row_color = Qt::transparent;
        ci->cell_color = Qt::transparent;
        for(int i = 1; i < 8; i++)
        {
            if( i != Qt::Sunday && i != Qt::Saturday )
            {
               ci->everyday_color[i-1] = ci->color;
            }
            else if( i == Qt::Saturday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
            else if( i == Qt::Sunday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
        }

        ci->line_space[0] = 5;
        ci->line_space[1] = 0;
        ci->line_space[2] = 5;
        ci->line_space[3] = 0;
        ci->line_padding[0] = 0;
        ci->line_padding[1] = 0;
        ci->line_padding[2] = 0;
        ci->line_padding[3] = 0;

        ci->cell_space[0] = 0;
        ci->cell_space[1] = 0;
        ci->cell_space[2] = 0;
        ci->cell_space[3] = 0;
        ci->cell_padding[0] = 0;
        ci->cell_padding[1] = 0;
        ci->cell_padding[2] = 0;
        ci->cell_padding[3] = 0;
    }

    //WeekdaysInfo()
    {
        wi->show = false;
        wi->size_of_region = 18;

        wi->font = QFont("Trebuchet MS");
        wi->font.setBold(true);
        wi->font.setItalic(false);
        wi->font.setUnderline(false);
        wi->color = Qt::black;
        wi->hor = HorCenterAlig;
        wi->ver = VerCenterAlig;
        wi->height_in_cell = 33;

        wi->row_color = Qt::transparent;
        wi->cell_color = Qt::transparent;

        wi->line_space[0] = 0;
        wi->line_space[1] = 0;
        wi->line_space[2] = 0;
        wi->line_space[3] = 0;
        wi->line_padding[0] = 0;
        wi->line_padding[1] = 0;
        wi->line_padding[2] = 0;
        wi->line_padding[3] = 0;

        wi->cell_space[0] = 0;
        wi->cell_space[1] = 0;
        wi->cell_space[2] = 0;
        wi->cell_space[3] = 0;
        wi->cell_padding[0] = 0;
        wi->cell_padding[1] = 0;
        wi->cell_padding[2] = 0;
        wi->cell_padding[3] = 0;
    }

    //MonthYearInfo()
    {
        mi->show = true;
        mi->size_of_region = 45;
        mi->bottom = false;
        mi->doublespace = false;

        mi->font = QFont("Trebuchet MS");
        mi->font.setBold(false);
        mi->font.setItalic(true);
        mi->font.setUnderline(false);
        mi->color = Qt::black;
        mi->hor = HorCenterAlig;
        mi->ver = VerCenterAlig;
        mi->height_in_cell = 30;

        mi->row_color = Qt::transparent;

        mi->line_space[0] = 0;
        mi->line_space[1] = 0;
        mi->line_space[2] = 0;
        mi->line_space[3] = 0;
        mi->line_padding[0] = 0;
        mi->line_padding[1] = 0;
        mi->line_padding[2] = 0;
        mi->line_padding[3] = 0;
    }
}

void A6Cal2ViewItm::drawWeekdays(QPainter *painter, const QRectF& rect, const WeekdaysInfo& wi, const QDate& d)
{
    Q_UNUSED(d);

    QRectF rect_space(rect);
    scale_rect(rect, &rect_space, wi.line_space, 4);

    painter->setPen(Qt::NoPen);
    if( wi.row_color == Qt::transparent )
        painter->setBrush(Qt::NoBrush);
    else
        painter->setBrush(wi.row_color);
    painter->drawRect(rect_space);

    QRectF rect_padding(rect_space);
    scale_rect(rect_space, &rect_padding, wi.line_padding, 4);
    QList<QRectF> cell_rects = split_rect(rect_padding, 1, 14);
    QString week_strs[7] = {tr("Mo"), tr("Tu"), tr("We"), tr("Th"), tr("Fr"), tr("Sa"), tr("Su")};
    for( int i = 0; i < 14; i++ )
        drawWeekdays_cell(painter, cell_rects[i], week_strs[i%7], wi);
}

void A6Cal2ViewItm::drawCalendar(QPainter *painter, const QRectF& rect, const CalendarInfo& ci, const QDate& d)
{
    int row = d.daysInMonth() + d.dayOfWeek() - 1;
    if( row%14 == 0 )
        row = row/14;
    else
        row = row/14 + 1;

    QList<QRectF> line_rects = split_rect(rect, row, 1);
    QDate date = d;
    int days = 0;
    for( int i = 0; i < row; i++ )
    {
        QRectF rect_space(line_rects[i]);
        scale_rect(line_rects[i], &rect_space, ci.line_space, 4);

        painter->setPen(Qt::NoPen);
        if( ci.row_color == Qt::transparent )
            painter->setBrush(Qt::NoBrush);
        else
            painter->setBrush(ci.row_color);
        painter->drawRect(rect_space);

        QRectF rect_padding(rect_space);
        scale_rect(rect_space, &rect_padding, ci.line_padding, 4);
        QList<QRectF> cell_rects = split_rect(rect_padding, 1, 14);
        for( int j = 0; j < 14; j++ )
        {
            if( days < d.daysInMonth() )
            {
                if( (i == 0 && date.dayOfWeek() - 1 == j%7) || i > 0 )
                {
                    drawCalendar_cell(painter, cell_rects[j], QString("%1").arg(++days), ci.everyday_color[date.dayOfWeek()-1], ci);
                    date = date.addDays(1);
                }
            }
            else
                break;
        }
    }
}

/*********************************************************/
/********** A6 type 3 Cal***************/
/*********************************************************/
A6Cal3ViewItm::A6Cal3ViewItm(const QPointF &pos, const QSize &size, const QMargins &margin, PmViewScnen *scene, QGraphicsItem *parent)
    :A4Cal1ViewItm(pos,size,margin,scene,parent)
{
    CalendarInfo ci;
    WeekdaysInfo wi;
    MonthYearInfo mi;

    this->loadDefaultInfo(&ci, &wi, &mi);
    this->setCalInfo(ci);
    this->setWeekdaysInfo(wi);
    this->setMonthYearInfo(mi);
}

A6Cal3ViewItm::~A6Cal3ViewItm()
{

}

void A6Cal3ViewItm::loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi)
{
    //CalendarInfo()
    {
        ci->font = QFont("Trebuchet MS");
        ci->font.setBold(false);
        ci->font.setItalic(false);
        ci->font.setUnderline(false);
        ci->color = Qt::black;
        ci->hor = HorCenterAlig;
        ci->ver = VerCenterAlig;
        ci->height_in_cell = 50;

        ci->bg_color = Qt::white;
        ci->row_color = Qt::transparent;
        ci->cell_color = Qt::transparent;
        for(int i = 1; i < 8; i++)
        {
            if( i != Qt::Sunday && i != Qt::Saturday )
            {
               ci->everyday_color[i-1] = ci->color;
            }
            else if( i == Qt::Saturday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
            else if( i == Qt::Sunday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
        }

        ci->line_space[0] = 0;
        ci->line_space[1] = 0;
        ci->line_space[2] = 0;
        ci->line_space[3] = 0;
        ci->line_padding[0] = 6;
        ci->line_padding[1] = 2;
        ci->line_padding[2] = 6;
        ci->line_padding[3] = 2;

        ci->cell_space[0] = 0;
        ci->cell_space[1] = 0;
        ci->cell_space[2] = 0;
        ci->cell_space[3] = 0;
        ci->cell_padding[0] = 0;
        ci->cell_padding[1] = 0;
        ci->cell_padding[2] = 0;
        ci->cell_padding[3] = 0;
    }

    //WeekdaysInfo()
    {
        wi->show = true;
        wi->size_of_region = 18;

        wi->font = QFont("Trebuchet MS");
        wi->font.setBold(false);
        wi->font.setItalic(false);
        wi->font.setUnderline(false);
        wi->color = Qt::black;
        wi->hor = HorCenterAlig;
        wi->ver = VerCenterAlig;
        wi->height_in_cell = 30;

        wi->row_color = Qt::white;
        wi->cell_color = Qt::transparent;

        wi->line_space[0] = 0;
        wi->line_space[1] = 0;
        wi->line_space[2] = 0;
        wi->line_space[3] = 0;
        wi->line_padding[0] = 6;
        wi->line_padding[1] = 25;
        wi->line_padding[2] = 6;
        wi->line_padding[3] = 0;

        wi->cell_space[0] = 0;
        wi->cell_space[1] = 0;
        wi->cell_space[2] = 0;
        wi->cell_space[3] = 0;
        wi->cell_padding[0] = 0;
        wi->cell_padding[1] = 0;
        wi->cell_padding[2] = 0;
        wi->cell_padding[3] = 0;
    }

    //MonthYearInfo()
    {
        mi->show = true;
        mi->size_of_region = 20;
        mi->bottom = true;
        mi->doublespace = false;

        mi->font = QFont("Trebuchet MS");
        mi->font.setBold(false);
        mi->font.setItalic(true);
        mi->font.setUnderline(false);
        mi->color = Qt::black;
        mi->hor = HorCenterAlig;
        mi->ver = VerCenterAlig;
        mi->height_in_cell = 45;

        mi->row_color = Qt::lightGray;

        mi->line_space[0] = 0;
        mi->line_space[1] = 0;
        mi->line_space[2] = 0;
        mi->line_space[3] = 0;
        mi->line_padding[0] = 0;
        mi->line_padding[1] = 0;
        mi->line_padding[2] = 0;
        mi->line_padding[3] = 0;
    }
}


/*********************************************************/
/********** A6 type 4 Cal***************/
/*********************************************************/
A6Cal4ViewItm::A6Cal4ViewItm(const QPointF &pos, const QSize &size, const QMargins &margin, PmViewScnen *scene, QGraphicsItem *parent)
    :A4Cal1ViewItm(pos,size,margin,scene,parent)
{
    CalendarInfo ci;
    WeekdaysInfo wi;
    MonthYearInfo mi;

    this->loadDefaultInfo(&ci, &wi, &mi);
    this->setCalInfo(ci);
    this->setWeekdaysInfo(wi);
    this->setMonthYearInfo(mi);
}

A6Cal4ViewItm::~A6Cal4ViewItm()
{

}

void A6Cal4ViewItm::loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi)
{
    //CalendarInfo()
    {
        ci->font = QFont("Trebuchet MS");
        ci->font.setBold(false);
        ci->font.setItalic(false);
        ci->font.setUnderline(false);
        ci->color = Qt::black;
        ci->hor = HorCenterAlig;
        ci->ver = VerBottomAlig;
        ci->height_in_cell = 37;

        ci->bg_color = Qt::transparent;
        ci->row_color = Qt::transparent;
        ci->cell_color = Qt::lightGray;
        for(int i = 1; i < 8; i++)
        {
            if( i != Qt::Sunday && i != Qt::Saturday )
            {
               ci->everyday_color[i-1] = ci->color;
            }
            else if( i == Qt::Saturday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
            else if( i == Qt::Sunday )
            {
               ci->everyday_color[i-1] = Qt::red;
            }
        }

        ci->line_space[0] = 5;
        ci->line_space[1] = 0;
        ci->line_space[2] = 5;
        ci->line_space[3] = 0;
        ci->line_padding[0] = 0;
        ci->line_padding[1] = 0;
        ci->line_padding[2] = 0;
        ci->line_padding[3] = 0;

        ci->cell_space[0] = 7;
        ci->cell_space[1] = 7;
        ci->cell_space[2] = 7;
        ci->cell_space[3] = 7;
        ci->cell_padding[0] = 0;
        ci->cell_padding[1] = 0;
        ci->cell_padding[2] = 0;
        ci->cell_padding[3] = 7;
    }

    //WeekdaysInfo()
    {
        wi->show = true;
        wi->size_of_region = 18;

        wi->font = QFont("Trebuchet MS");
        wi->font.setBold(true);
        wi->font.setItalic(false);
        wi->font.setUnderline(false);
        wi->color = Qt::black;
        wi->hor = HorCenterAlig;
        wi->ver = VerCenterAlig;
        wi->height_in_cell = 33;

        wi->row_color = Qt::lightGray;
        wi->cell_color = Qt::transparent;

        wi->line_space[0] = 5;
        wi->line_space[1] = 10;
        wi->line_space[2] = 5;
        wi->line_space[3] = 30;
        wi->line_padding[0] = 0;
        wi->line_padding[1] = 0;
        wi->line_padding[2] = 0;
        wi->line_padding[3] = 0;

        wi->cell_space[0] = 0;
        wi->cell_space[1] = 0;
        wi->cell_space[2] = 0;
        wi->cell_space[3] = 0;
        wi->cell_padding[0] = 0;
        wi->cell_padding[1] = 0;
        wi->cell_padding[2] = 0;
        wi->cell_padding[3] = 0;
    }

    //MonthYearInfo()
    {
        mi->show = true;
        mi->size_of_region = 15;
        mi->bottom = false;
        mi->doublespace = false;

        mi->font = QFont("Trebuchet MS");
        mi->font.setBold(false);
        mi->font.setItalic(true);
        mi->font.setUnderline(false);
        mi->color = Qt::black;
        mi->hor = HorCenterAlig;
        mi->ver = VerCenterAlig;
        mi->height_in_cell = 40;

        mi->row_color = Qt::transparent;

        mi->line_space[0] = 0;
        mi->line_space[1] = 0;
        mi->line_space[2] = 0;
        mi->line_space[3] = 0;
        mi->line_padding[0] = 0;
        mi->line_padding[1] = 0;
        mi->line_padding[2] = 0;
        mi->line_padding[3] = 0;
    }
}



// implement factory

CalViewItm *CalViewItmFactory::getViewItm(PROJ_PROPS::LAYOUT_TYPE lytype,
	const QPointF& pos, const QSize& size, const QMargins& margin,
                  PmViewScnen *scene,QGraphicsItem * parent)
{

	CalViewItm *calitm = NULL;
	switch(lytype)
	{
	case PROJ_PROPS::LYCALA4L1:
		{
			calitm = new A4Cal1ViewItm(pos,size,margin,scene, parent);
		}
		break;
	case PROJ_PROPS::LYCALA4L2:
		{
			calitm = new A4Cal2ViewItm(pos,size,margin,scene,parent);
		}
		break;
	case PROJ_PROPS::LYCALA4L3:
		{
			calitm = new A4Cal3ViewItm(pos,size,margin,scene,parent);
		}
		break;
	case PROJ_PROPS::LYCALA4L4:
		{
			calitm = new A4Cal4ViewItm(pos, size,margin,scene,parent);
		}
		break;
	case PROJ_PROPS::LYCALA5L1:
		{
			calitm = new A5Cal1ViewItm(pos,size,margin,scene,parent);
		}
		break;
	case PROJ_PROPS::LYCALA5L2:
		{
			calitm = new A5Cal2ViewItm(pos,size,margin,scene,parent);
		}
		break;
	case PROJ_PROPS::LYCALA5L3:
		{
			calitm = new A5Cal3ViewItm(pos,size,margin,scene,parent);
		}
		break;
	case PROJ_PROPS::LYCAL4X6L1:
		{
			calitm = new A6Cal1ViewItm(pos,size,margin,scene,parent);
		}
		break;
	case PROJ_PROPS::LYCAL4X6L2:
		{
			calitm = new A6Cal2ViewItm(pos,size,margin,scene,parent);
		}
		break;
	case PROJ_PROPS::LYCAL4X6L3:
		{
			calitm = new A6Cal3ViewItm(pos,
				size,margin,scene,parent);
		}
		break;
	case PROJ_PROPS::LYCAL4X6L4:
		{
			calitm = new A6Cal4ViewItm(pos,
				size,margin,scene,parent);
		}
		break;
	default:
		calitm = new A4Cal1ViewItm(pos,size,margin,scene,parent);

	}
	return calitm;
}

CalViewItm *CalViewItmFactory::getPreviewItm(PROJ_PROPS::LAYOUT_TYPE lytype,const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PhotoPreviewScene *scene,
                  QGraphicsItem * parent)
{
	CalViewItm *calitm = NULL;
	switch(lytype)
	{
	case PROJ_PROPS::LYCALA4L1:
		{
			calitm = new CalPreviewItm<A4Cal1ViewItm>(QPointF(0,0),
				QSize((int)0,(int)0),margin,scene, parent);
		}
		break;
	case PROJ_PROPS::LYCALA4L2:
		{
			calitm = new CalPreviewItm<A4Cal2ViewItm>(QPointF(0,0),
				QSize((int)0,(int)0),margin,scene, parent);

		}
		break;
	case PROJ_PROPS::LYCALA4L3:
		{
			calitm = new CalPreviewItm<A4Cal3ViewItm>(QPointF(0,0),
				QSize((int)0,(int)0),margin,scene, parent);
		}
		break;
	case PROJ_PROPS::LYCALA4L4:
		{
			calitm = new CalPreviewItm<A4Cal4ViewItm>(QPointF(0,0),
				QSize((int)0,(int)0),margin,scene, parent);
		}
		break;
       case PROJ_PROPS::LYCALA5L1:
                {
                        calitm = new CalPreviewItm<A5Cal1ViewItm>(QPointF(0,0),
                                QSize((int)0,(int)0),margin,scene, parent);
                }
                 break;
        case PROJ_PROPS::LYCALA5L2:
                {
                        calitm = new CalPreviewItm<A5Cal2ViewItm>(QPointF(0,0),
                                QSize((int)0,(int)0),margin,scene, parent);
                }
                 break;
        case PROJ_PROPS::LYCALA5L3:
                {
                        calitm = new CalPreviewItm<A5Cal3ViewItm>(QPointF(0,0),
                                QSize((int)0,(int)0),margin,scene, parent);
                }
                 break;
        case PROJ_PROPS::LYCAL4X6L1:
                {
                        calitm = new CalPreviewItm<A6Cal1ViewItm>(QPointF(0,0),
                                QSize((int)0,(int)0),margin,scene, parent);
                }
                 break;
        case PROJ_PROPS::LYCAL4X6L2:
                {
                        calitm = new CalPreviewItm<A6Cal2ViewItm>(QPointF(0,0),
                                QSize((int)0,(int)0),margin,scene, parent);
                }
                 break;
        case PROJ_PROPS::LYCAL4X6L3:
                {
                        calitm = new CalPreviewItm<A6Cal3ViewItm>(QPointF(0,0),
                                QSize((int)0,(int)0),margin,scene, parent);
                }
                 break;
        case PROJ_PROPS::LYCAL4X6L4:
                {
                        calitm = new CalPreviewItm<A6Cal4ViewItm>(QPointF(0,0),
                                QSize((int)0,(int)0),margin,scene, parent);
                }
                 break;
	default:
		calitm = new CalPreviewItm<A4Cal1ViewItm>(QPointF(0,0),
			QSize((int)0,(int)0),margin,scene, parent);

	}

	return calitm;
}

