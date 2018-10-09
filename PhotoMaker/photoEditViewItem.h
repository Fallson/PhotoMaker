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

#ifndef PageViewItm_H
#define PageViewItm_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QSize>
#include <QPointF>
#include <QMargins>
#include <QDate>
#include "pmpaperpage.h"
#include "PhotoEditViewScene.h"
#include <QSemaphore>

/*****************************************************************************/
#define NORM_LINE 1
#define SHADOW_OFFSET 2
#define SHADOW_BLUR   10.0
#define MOUSEMV_THRES 5

enum HorAlignment{HorLeftAlig, HorCenterAlig, HorRightAlig};
enum VerAlignment{VerTopAlig, VerCenterAlig, VerBottomAlig};

/*****************************************************************************/

class PageViewItm : public QGraphicsObject
{
	Q_OBJECT
public:
    PageViewItm(const QPointF& pos,
                const QSize& size,
                const QMargins& margin,
                PmViewScnen *scene = NULL,
                QGraphicsItem * parent = 0);
    virtual ~PageViewItm();

public:
    virtual void reload(){}  // used when content is changed
    virtual void resize(bool update = true){}

    // this function will be called to accpet a drag drop
    virtual void setContent(const QString &cnt) = 0;

    // edit view assist functions
public :
    virtual PmViewScnen *getScene() = 0;


    void setPmPageItm(PmPageItm *pPagePicItm){_pPageItm = pPagePicItm;}
    PmPageItm * getPmPageItm(){return _pPageItm;}

   // void updateCursor(QCursor cursor);
   // static void setContentFunc(void *context);
    // properties
public:
    void setItemBGColor(const QColor& clr);//the bgcolor for item
	void clearItmBgColor();
    void setShadow(bool s);
    bool getItemShadow(){ return item_shadow; }
    void setItemSize(const QSize& size, bool update=false){ item_size = size; if ( update) this->update(); }
    QSize getItemSize(){ return item_size; }
    void setItemMargin(const QMargins& margin, bool update=false){ item_margin = margin; if ( update) this->update(); }
    QMargins getItemMargin(){ return item_margin; }
    void setItemType(ITEM_TYPE type){ item_type = type; }
    ITEM_TYPE getItemType(){ return item_type; }

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    //void paint_shadow(QPainter *painter);

    // void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);


protected slots:
	void _updateCntTimerFunc();

protected:
    QSize    item_size;
    QPointF  item_pos; //in parent scene's pos, it is deprecated
    QMargins item_margin;
    bool     item_shadow;
    QColor   item_bgcolor;

    ITEM_TYPE item_type;

    PmPageItm *_pPageItm;

    QString _cnt;
    Qt::CursorShape _cursor;
    QSemaphore _eventforcursorupdate;
};


class PageBkgrndViewItm: public QGraphicsRectItem
{
public:
	PageBkgrndViewItm(PhotoEditViewScene *scene, PmPhotoPage *photopage);
	~PageBkgrndViewItm(){}

protected:
	virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	virtual void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
	void _updateLayout(const QString &layoutname);

private:
	PhotoEditViewScene *_editsecne;
	PmPhotoPage *_photopage;
};


class PreviewBkgrndViewItm: public QGraphicsRectItem
{
public:
	PreviewBkgrndViewItm(PhotoPreviewScene *scene, PhotoMaker *pMainFrame);
	~PreviewBkgrndViewItm();


protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
	virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
	virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
	//virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseMoveEvent( QGraphicsSceneMouseEvent * event );
	virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
private:

private:
	//PhotoEditViewScene *_editsecne;
	bool _dropping;
	int _droppos;
	PhotoPreviewScene *_previescene;
	PhotoMaker *_pMainFrame;
};



class PreviewPaperLabelViewItm: public QGraphicsRectItem
{
public:
	PreviewPaperLabelViewItm(PaperPagePreviewItmSet *paperpageset, PhotoPreviewScene *scene);
	~PreviewPaperLabelViewItm();

public:
	void setContent(const QString &cnt){_cnt = cnt;}
	void enableDrag(bool enable);

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
	virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
	virtual void dropEvent(QGraphicsSceneDragDropEvent *event);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:

private:
	//PhotoEditViewScene *_editsecne;
	PhotoPreviewScene *_previescene;
	PaperPagePreviewItmSet *_paperpageset;
	QString _cnt;
	bool _drag ;
	bool _enableDrag;
	QCursor _orgcursor;
};


class PhotoViewItm: public PageViewItm
{
public:
    PhotoViewItm(const QPointF& pos,
                   const QSize& size,
                   const QMargins& margin,
                   PhotoEditViewScene *scene = NULL,
                   QGraphicsItem * parent = 0);
    virtual ~PhotoViewItm();

public:
    virtual void reload();
    virtual void setContent(const QString &cnt);
    virtual PmViewScnen *getScene(){return _pScene;}


public:
	virtual bool getDpi(int &dpi);

public:
	//properties
    void setImg(const QString& filepath, QPixmap &savedpixmap);

public:
	// photo edit functions
    void scale(qreal ratio);
    void rotate(int  angel);

    void setRE();
    void setLCIG();
    void setHSL();
    void setBWC();

	// asist function
    bool selectPanoramaPair(bool selected);
	bool updatePanoramaPair(){return _updatePanoramaPair();}

public:
    virtual void resize(bool update = true);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    virtual bool _getScale(qreal &scale);
    //virtual bool _getScale(QSize viewSize, QSize imgSize, qreal &scale);
    virtual void _getImgDefOff(qreal &xoff,qreal &yoff);
    virtual void _getPixmapOffInViewItm(int &xoff,int &yoff);

private:
    void _updateLayout(const QString &layoutname);
    void _updateImg(const QString &imgpath);
    void _updateColor(const QString &colorname);

    bool _updatePanoramaPair();

    bool _isPanoramaLayout();

	bool _saveNewImgFile(const QImage &img, QString &path);


protected:
    QString  img_filepath;
    //QPixmap  orgpixmap;
    QPixmap  pixmap;
    QPoint   img_lefttop;

    PhotoEditViewScene *_pScene;
	QCursor _orgcur;

    bool b_drag;
};

class PhotoPanoViewItm: public PhotoViewItm
{
public:
    typedef enum{Left_Pano, Right_Pano}PanoType;
public:
    PhotoPanoViewItm(const QPointF& pos,
                   const QSize& size,
                   const QMargins& margin,
                   PanoType type,
                   PhotoEditViewScene *scene = NULL,
                   QGraphicsItem * parent = 0);
    ~PhotoPanoViewItm();

public:
    PanoType getPanoType() const{return panotype;}

public:

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
 

   // virtual bool _getScale(QSize viewSize, QSize imgSize, qreal &scale);
	virtual bool _getScale(qreal &scale);

    virtual void _getImgDefOff(qreal &xoff,qreal &yoff);
	virtual void _getPixmapOffInViewItm(int &xoff,int &yoff);

private:
    PanoType panotype;
};

class PaperPagePreviewItmSet;

class PhotoPreviewItm: public PhotoViewItm
{
public:
    PhotoPreviewItm(const QPointF& pos,
                   const QSize& size,
                   const QMargins& margin,
                   PhotoPreviewScene *scene = NULL,
                   QGraphicsItem * parent = 0);
    ~PhotoPreviewItm();

public:
	virtual void reload();

	virtual PmViewScnen *getScene(){return _pScene;}

public:
	void setPaperPagePreviewItmSet(PaperPagePreviewItmSet *pPaperpagePreviewItm){_pPaperPagePreviwItm = pPaperpagePreviewItm;}

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

private:
	PaperPagePreviewItmSet *_pPaperPagePreviwItm;
	PhotoPreviewScene *_pScene;
	QCursor _orgcur;
};

// dupliate implementation for pano photoview item

class PanorPhotoPreviewItm: public PhotoPanoViewItm
{
public:
    PanorPhotoPreviewItm(const QPointF& pos,
                   const QSize& size,
                   const QMargins& margin,bool left,
                   PhotoPreviewScene *scene = NULL,
                   QGraphicsItem * parent = 0);
    ~PanorPhotoPreviewItm();

public:
	virtual void reload();

	virtual PmViewScnen *getScene(){return _pScene;}

public:
	void setPaperPagePreviewItmSet(PaperPagePreviewItmSet *pPaperpagePreviewItm){_pPaperPagePreviwItm = pPaperpagePreviewItm;}

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

private:
	PaperPagePreviewItmSet *_pPaperPagePreviwItm;
	PhotoPreviewScene *_pScene;

};

class PaperPagePreviewItmSet;
class PaperPreviewBgItm: public QGraphicsPixmapItem
{
public:
	PaperPreviewBgItm(PhotoPreviewScene *pscene,PaperPagePreviewItmSet *pPaerPage, const QPixmap &pixmap);
	~PaperPreviewBgItm();

public:
	virtual  void paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget);
protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
	virtual void dragMoveEvent ( QGraphicsSceneDragDropEvent * event ) ;


private:
	void _paintSelected(QPainter *painter,const QStyleOptionGraphicsItem *option);

private:
	PaperPagePreviewItmSet *_pPaerPage;
	PhotoPreviewScene *_pscene;
};


class PaperPagePreviewItmSet
{
public:
	PaperPagePreviewItmSet(PhotoPreviewScene *pscene, PmPrintPaperPage *pPaperPage, const QRectF &rect,PhotoMaker *pMainFrame );
	~PaperPagePreviewItmSet();

public:
	PmPrintPaperPage *getPaperpage(){return _pPaperPage;}
	bool setNextEditPaper(bool isnext){  _isnext = isnext; return true;}
public:
	void update(bool reload = false);
	void remove();

	void resize(const QRectF &rect);

	QRectF getRect();
	void setRect(const QRectF &rect){_rect = rect;}
	void setBottomLabel(const QString &label);
	void select(bool select = true);

	void enableMvPaper(bool enable);


private:
	void _updateRegions();

	void _reloadItems();
	void _addBackgroundItm();
	void _addPhotoPage(PmPhotoPage *pPhotoPage);

	void _updateItems();
	void _updatePhotoPage(PmPhotoPage *pPhotoPage);
	void _updateBackgroundItm();
	void _updateBottomLabel();

	void _removeViewItems();


private:
	//
	PmPrintPaperPage *_pPaperPage;
	PhotoPreviewScene *_pscene;

	QList<PageViewItm*> _viewitmlst;  // can be photo item or calendar item
	PreviewPaperLabelViewItm *_pBottomLabel;
	//QPushButton *_bottomLabel;
	QString			_bottomLabelTxt;

private:
    int bound_size;
	QRectF _bottomlabelframe;
	QRectF _previewframe;
	QRectF _paperpageframe;
	PaperPreviewBgItm  *_pPaperPageBackGround;
	PhotoMaker *_pMainFrame;

	QRectF _rect;
	bool _isnext;

	bool _enableMv;
};

#endif
