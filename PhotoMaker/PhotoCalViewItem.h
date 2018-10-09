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

#ifndef PhotoCalViewItm_H
#define PhotoCalViewItm_H

#include "PhotoEditViewItem.h"
#include "PhotoEditView.h"
#include <QGraphicsSceneDragDropEvent>

struct CalendarInfo
{
    /*Font part*/
    QFont font;
    QColor color;

    HorAlignment hor;
    VerAlignment ver;

    int height_in_cell;

    /*Colors part*/
    QColor bg_color;
    QColor row_color;
    QColor cell_color;
    QColor everyday_color[7];

    /*Line spacing part*/
    qreal line_space[4];
    qreal line_padding[4];

    /*Cell spacing part*/
    qreal cell_space[4];
    qreal cell_padding[4];
};

struct WeekdaysInfo
{
    bool show;
    qreal size_of_region;

    /*Font part*/
    QFont font;
    QColor color;

    HorAlignment hor;
    VerAlignment ver;

    int height_in_cell;

    /*Colors part*/
    QColor row_color;
    QColor cell_color;

    /*Line spacing part*/
    qreal line_space[4];
    qreal line_padding[4];

    /*Cell spacing part*/
    qreal cell_space[4];
    qreal cell_padding[4];
};

struct MonthYearInfo
{
    bool show;
    qreal size_of_region;
    bool bottom;
    bool doublespace;

    /*Font part*/
    QFont font;
    QColor color;

    HorAlignment hor;
    VerAlignment ver;

    int height_in_cell;

    /*Colors part*/
    QColor row_color;

    /*Line spacing part*/
    qreal line_space[4];
    qreal line_padding[4];
};

class CalViewItm: public PageViewItm
{
public:
    CalViewItm(const QPointF& pos,
               const QSize& size,
               const QMargins& margin,
               PmViewScnen *scene = NULL,
               QGraphicsItem * parent = 0);
    virtual ~CalViewItm();

public:
	// properties

    void setYearMonth(int year, int month);
    void getYearMonth(int* year, int* month);
    QDate getDate(void);

    void setCalInfo(const CalendarInfo& ci);
    void setWeekdaysInfo(const WeekdaysInfo& wi);
    void setMonthYearInfo(const MonthYearInfo& mi);
    void getInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi);

public:
    // this function will be called to accpet a drag drop
    virtual void setContent(const QString &cnt);

    // edit view assist functions

    // Peview assit function
    virtual void setPaperPagePreviewItmSet(PaperPagePreviewItmSet *pPaperpagePreviewItm){}

public :
    virtual PmViewScnen *getScene();

public:
    virtual void reload();
    virtual void resize(bool update = true);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void drawWeekdays_cell(QPainter *painter, const QRectF& cell_rect, const QString& str, const WeekdaysInfo& wi);
    void drawCalendar_cell(QPainter *painter, const QRectF& cell_rect, const QString& str, const QColor& clr, const CalendarInfo& ci);
    virtual void drawContent(QPainter *painter, const QRectF& rect, const CalendarInfo& ci, const WeekdaysInfo& wi, const MonthYearInfo& mi, const QDate& d);
    virtual void drawMonthYear(QPainter *painter, const QRectF& rect, const MonthYearInfo& mi, const QDate& d);
    virtual void drawWeekdays(QPainter *painter, const QRectF& rect, const WeekdaysInfo& wi, const QDate& d) = 0;
    virtual void drawCalendar(QPainter *painter, const QRectF& rect, const CalendarInfo& ci, const QDate& d) = 0;

    QList<QRectF> split_rect(const QRectF& rect, int row, int col);
    void scale_rect(const QRectF& from, QRectF* to, const qreal* factor, int n);
    void align_flag(HorAlignment hor, VerAlignment ver, int* flag);


	void _updateLayout(const QString &layoutname);

private:
    CalendarInfo cal_info;
    WeekdaysInfo weekdays_info;
    MonthYearInfo monthyear_info;
    QDate m_date;

    PmViewScnen *_scene;
};

/*******************************A4 Cals**********************************/
class A4Cal1ViewItm: public CalViewItm
{
public:
    A4Cal1ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene = NULL,
                  QGraphicsItem * parent = 0);
    virtual ~A4Cal1ViewItm();

protected:
    void loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi);

private:
    void drawWeekdays(QPainter *painter, const QRectF& rect, const WeekdaysInfo& wi, const QDate& d);
    void drawCalendar(QPainter *painter, const QRectF& rect, const CalendarInfo& ci, const QDate& d);
};

class A4Cal2ViewItm: public A4Cal1ViewItm
{
public:
    A4Cal2ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene = NULL,
                  QGraphicsItem * parent = 0);
    virtual ~A4Cal2ViewItm();

protected:
    void loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi);
};

class A4Cal3ViewItm: public CalViewItm
{
public:
    A4Cal3ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene = NULL,
                  QGraphicsItem * parent = 0);
    virtual ~A4Cal3ViewItm();

protected:
    void loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi);

private:
    void drawWeekdays(QPainter *painter, const QRectF& rect, const WeekdaysInfo& wi, const QDate& d);
    void drawCalendar(QPainter *painter, const QRectF& rect, const CalendarInfo& ci, const QDate& d);
};

class A4Cal4ViewItm: public CalViewItm
{
public:
    A4Cal4ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene = NULL,
                  QGraphicsItem * parent = 0);
    virtual ~A4Cal4ViewItm();

protected:
    void loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi);

private:
    void drawContent(QPainter *painter, const QRectF &rect, const CalendarInfo &ci, const WeekdaysInfo &wi, const MonthYearInfo &mi, const QDate &d);
    void drawWeekdays(QPainter *painter, const QRectF& rect, const WeekdaysInfo& wi, const QDate& d);
    void drawCalendar(QPainter *painter, const QRectF& rect, const CalendarInfo& ci, const QDate& d);
};

/*******************************A5 Cals**********************************/
class A5Cal1ViewItm: public A4Cal1ViewItm
{
public:
    A5Cal1ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene = NULL,
                  QGraphicsItem * parent = 0);
    virtual ~A5Cal1ViewItm();

protected:
    void loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi);
};

class A5Cal2ViewItm: public A4Cal1ViewItm
{
public:
    A5Cal2ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene = NULL,
                  QGraphicsItem * parent = 0);
    virtual ~A5Cal2ViewItm();

protected:
    void loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi);
};

class A5Cal3ViewItm: public A4Cal3ViewItm
{
public:
    A5Cal3ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene = NULL,
                  QGraphicsItem * parent = 0);
    virtual ~A5Cal3ViewItm();

protected:
    void loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi);
};

/*******************************A6 Cals**********************************/
class A6Cal1ViewItm: public A4Cal4ViewItm
{
public:
    A6Cal1ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene = NULL,
                  QGraphicsItem * parent = 0);
    virtual ~A6Cal1ViewItm();

protected:
    void loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi);

private:
    void drawWeekdays(QPainter *painter, const QRectF& rect, const WeekdaysInfo& wi, const QDate& d);
    void drawCalendar(QPainter *painter, const QRectF& rect, const CalendarInfo& ci, const QDate& d);
};

class A6Cal2ViewItm: public CalViewItm
{
public:
    A6Cal2ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene = NULL,
                  QGraphicsItem * parent = 0);
    virtual ~A6Cal2ViewItm();

protected:
    void loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi);

private:
    void drawWeekdays(QPainter *painter, const QRectF& rect, const WeekdaysInfo& wi, const QDate& d);
    void drawCalendar(QPainter *painter, const QRectF& rect, const CalendarInfo& ci, const QDate& d);
};


class A6Cal3ViewItm: public A4Cal1ViewItm
{
public:
    A6Cal3ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene = NULL,
                  QGraphicsItem * parent = 0);
    virtual ~A6Cal3ViewItm();

protected:
    void loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi);
};

class A6Cal4ViewItm: public A4Cal1ViewItm
{
public:
    A6Cal4ViewItm(const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene = NULL,
                  QGraphicsItem * parent = 0);
    virtual ~A6Cal4ViewItm();

protected:
    void loadDefaultInfo(CalendarInfo* ci, WeekdaysInfo* wi, MonthYearInfo* mi);
};


/*******************************Preview**********************************/
template<typename CVI>
class CalPreviewItm: public CVI
{
public:
    CalPreviewItm(const QPointF& pos,
                   const QSize& size,
                   const QMargins& margin,
                   PhotoPreviewScene *scene = NULL,
                   QGraphicsItem * parent = 0)
        :CVI(pos, size, margin, NULL, parent),
          _pPaperPagePreviwItm(NULL), _pScene(scene)
    {
                CVI::setItemType(ImgType);
    }

    ~CalPreviewItm(){}
public:
        void reload()
		{
                        CVI::reload();
		}
        PmViewScnen *getScene(){return _pScene;}

public:
        void setPaperPagePreviewItmSet(PaperPagePreviewItmSet *pPaperpagePreviewItm){_pPaperPagePreviwItm = pPaperpagePreviewItm;}

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
	{
		if ( _pPaperPagePreviwItm )
		{
			//
			_pScene->select(_pPaperPagePreviwItm);
		}

	}
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event){}
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event){}
    void dropEvent(QGraphicsSceneDragDropEvent *event)
	{
		PhotoMaker *pMainFrame = _pScene->getMainFrame();

		// only accept alyout

		/// update path
		QString info;
		if (event->mimeData()->hasText())
			info = event->mimeData()->text();

                PmPageItm* ppi = CVI::getPmPageItm();
                if ( !ppi )
		{
			return ;
		}
		QString srcloc = event->mimeData()->data("srcloc");
		if ( srcloc != "filelistview" )
		{
			return ;
		}
		if ( !(info.length()>8 && info.left(7) == LY_PREFIX) )
		{
			return ;
		}
		// layout
		QString layoutname = info.right(info.length()-7);

                PmPhotoPage *pPage = ppi->getPage();
		PmPrintPaperPage *pPaperPage = pPage->getPaperPage();
		if ( pPaperPage )
		{				
			PROJ_PROPS projprops;

			pMainFrame->getDoc()->getProjProps(projprops);

			PHOTO_LAYOUT layout = PPLayoutMgr::getInst().getLayoutFromName(projprops,layoutname);


			pPaperPage->setLayout(pPage, layout);


			((PhotoPreviewScene*)_pScene)->reloadPaperPage(pPaperPage);
			PmPhotoView *pEditView = (PmPhotoView*)pPaperPage->getEditView();
			if ( pEditView )
			{
				pEditView->reloadPaperPage(pPaperPage);
			}
		}	

		// update all views
		pMainFrame->updateViews(false);

	}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
	{
		CVI::paint(painter, option, widget);
	}

private:
        PaperPagePreviewItmSet *_pPaperPagePreviwItm;
        PhotoPreviewScene *_pScene;
};


class CalViewItmFactory
{
public:
	static CalViewItm *getPreviewItm(PROJ_PROPS::LAYOUT_TYPE lytype,const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PhotoPreviewScene *scene,
                  QGraphicsItem * parent = NULL);
	static CalViewItm *getViewItm(PROJ_PROPS::LAYOUT_TYPE lytype,const QPointF& pos,
                  const QSize& size,
                  const QMargins& margin,
                  PmViewScnen *scene,
                  QGraphicsItem * parent = NULL);
};

#endif
