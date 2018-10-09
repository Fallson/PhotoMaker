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
#include "PhotoTextViewItem.h"
#include "photomaker.h"
#include "PhotoEditView.h"

/*********************************************************/
//TextItem related
/*********************************************************/
#define DEFAULT_MAR_W 300
#define DEFAULT_MAR_H 64
#define MIN_HW 32
#define RADIUS 2.5
#define RIGHT_RAT 8

TextViewItem::TextViewItem(bool print_item, const QPointF& pos, QGraphicsItem *parent)
    :QGraphicsTextItem(parent)
{
    item_pos = pos;

    text = QString("");
    text_horalign = HorLeftAlig;
    text_veralign = VerTopAlig;

    text_font_ratio = 1.0;

    calItemRect(QRectF(0,0,DEFAULT_MAR_W,DEFAULT_MAR_H), text_font_ratio);
    rot_angle = 0;

    print_text_item = print_item;

    item_shadow = false;
    setShadow(true);

    mm_style = MMN;
    b_leftbtn_dwn = false;

    setFlag( QGraphicsItem::ItemIsSelectable );
    setFlag( QGraphicsItem::ItemIsMovable );
    setAcceptHoverEvents(true);

    rotate_cur = QCursor(QPixmap(gbires + "curs/rotate.png"));
}

TextViewItem::~TextViewItem()
{
    //do nth
}


void TextViewItem::setText(const QString &txt)
{
    if( text == txt )
        return;

    text = txt;
    setHtml(text);

    this->update();
}

void TextViewItem::setShadow(bool s)
{
    if( item_shadow == s )
        return;

    item_shadow = s;

    QGraphicsDropShadowEffect* gdse =  (QGraphicsDropShadowEffect*)this->graphicsEffect();
    if( gdse == 0 )
    {
        gdse = new QGraphicsDropShadowEffect(this);
        gdse->setOffset(SHADOW_OFFSET, SHADOW_OFFSET);
        gdse->setBlurRadius(SHADOW_BLUR);
        this->setGraphicsEffect(gdse);
    }

    if( item_shadow )
    {
        gdse->setBlurRadius(SHADOW_BLUR);
        gdse->setOffset(SHADOW_OFFSET, SHADOW_OFFSET);
    }
    else
    {
        gdse->setBlurRadius(0.0);
        gdse->setOffset(0,0);
    }
    this->update();
}

void TextViewItem::setHorAlignment(HorAlignment ha)
{
    if( text_horalign == ha )
        return;

    text_horalign = ha;

    QTextDocument* doc = this->document();
    QTextOption op = doc->defaultTextOption();
    if( ha == HorLeftAlig )
    {
        op.setAlignment(Qt::AlignLeft);
    }
    else if( ha == HorCenterAlig )
    {
        op.setAlignment(Qt::AlignHCenter);
    }
    else if( ha == HorRightAlig )
    {
        op.setAlignment(Qt::AlignRight);
    }
    doc->setDefaultTextOption(op);

    this->update();
}

void TextViewItem::setVerAlignment(VerAlignment va)
{
    if( text_veralign == va )
        return;

    text_veralign = va;

    QRectF rect = QGraphicsTextItem::boundingRect();

    if( rect.height() >= item_rect.height() )//the text is full of the item_rect
        return;

    qreal dy = 0.0;
    if( va == VerTopAlig )
    {
        dy = rect.y() - item_rect.y();
    }
    else if( va == VerCenterAlig )
    {
        dy = rect.y() - item_rect.y() + rect.height()/2.0 - item_rect.height()/2.0;
    }
    else if( va == VerBottomAlig )
    {
        dy = rect.y() + rect.height() - item_rect.y() - item_rect.height();
    }

    item_rect.translate(QPointF(0,dy));
    calItemRect(item_rect, text_font_ratio);

    this->translate(0,-dy*text_font_ratio);

    this->update();
}

QPainterPath TextViewItem::shape() const
{
    QPainterPath path;

    qreal adjust = RADIUS/text_font_ratio;
    QRectF rect(item_rect.x() - adjust, item_rect.y() - adjust,
                item_rect.width() + adjust*RIGHT_RAT, item_rect.height() + adjust);
    path.addRect(rect);
    return path;
}

QRectF TextViewItem::boundingRect() const
{
    qreal adjust = RADIUS/text_font_ratio;
    QRectF rect(item_rect.x() - adjust, item_rect.y() - adjust,
                item_rect.width() + adjust*RIGHT_RAT, item_rect.height() + adjust);
    return rect;
}

void TextViewItem::setFontViewRatio(qreal fontratio)
{
    text_font_ratio = fontratio;

    calItemRect(item_rect, text_font_ratio);

    this->setTransformOriginPoint(item_rect.center());
    this->setScale(fontratio);
}

void TextViewItem::setWidthHeight(int width, int height)
{
    calItemRect(QRectF(0,0,width,height), text_font_ratio);

    this->update();
}

void TextViewItem::setTextItm(PmTextItm *pTextItm)
{
	LayoutBoxPos pos;
	if ( pTextItm->getRectInPrintPage(pos) && pos.width < 1)
	{
		pos.width = this->item_rect.width();
		pos.height = item_rect.height();
		pTextItm->setRectInPrintPage(pos);
	}
	_txtitm = pTextItm;
}


void TextViewItem::reload()
{
    LayoutBoxPos pos;
    this->_txtitm->getRectInPrintPage(pos);
    //this->_txtitm->getPrintPage()->getitem

    item_rect.setX(pos.x);
    item_rect.setY(pos.y);
    item_rect.setWidth(pos.width);
    item_rect.setHeight(pos.height);
    rot_angle = _txtitm->getRotate();

    item_shadow = _txtitm->isShadowEnable();

	int align = 0;
	align = _txtitm->getAlign();
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
	this->setHorAlignment(haligninview);

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
	this->setVerAlignment(verigninview);

    //Todo: change the text font according to the font_ratio

    this->update();
}


void TextViewItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if ( this->isSelected() )
    {
        //first draw the boundary
        QPen pen;
        pen.setColor(Qt::gray);
        pen.setStyle(Qt::DotLine);
        pen.setWidth(0);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(item_rect);

        //second draw the scale hits
        pen.setColor(Qt::black);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(0);
        painter->setPen(pen);
        painter->setBrush(Qt::green);
        for(int i = 0; i < 8; i++)
        {
            painter->drawRect(dragRects[i]);
        }

        //third draw the rotate hit
        painter->setBrush(Qt::red);
        painter->drawEllipse(rotateRect);
    }
    else if( !print_text_item )
    {
        //paint 4 corner
        QPen pen;
        pen.setColor(Qt::gray);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(0);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);

        QVector<QLineF> lines;

        qreal len = RADIUS*2/text_font_ratio;
        QPointF p1 = item_rect.topLeft();
        QPointF p2 = p1 + QPointF(len, 0.0);
        lines.push_back(QLineF(p1,p2));
        p2 = p1 + QPointF(0.0, len);
        lines.push_back(QLineF(p1,p2));

        p1 = item_rect.topRight();
        p2 = p1 - QPointF(len, 0.0);
        lines.push_back(QLineF(p1,p2));
        p2 = p1 + QPointF(0.0, len);
        lines.push_back(QLineF(p1,p2));

        p1 = item_rect.bottomRight();
        p2 = p1 - QPointF(len, 0.0);
        lines.push_back(QLineF(p1,p2));
        p2 = p1 - QPointF(0.0, len);
        lines.push_back(QLineF(p1,p2));

        p1 = item_rect.bottomLeft();
        p2 = p1 + QPointF(len, 0.0);
        lines.push_back(QLineF(p1,p2));
        p2 = p1 - QPointF(0.0, len);
        lines.push_back(QLineF(p1,p2));

        painter->drawLines(lines);
    }

    if( this->isSelected() )
    {
        QStyleOptionGraphicsItem op(*option);
        op.state &= ~(QStyle::State_Selected|QStyle::State_HasFocus);
        QGraphicsTextItem::paint(painter, &op, widget);
    }
    else
    {
        QGraphicsTextItem::paint(painter, option, widget);
    }
}

void TextViewItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsTextItem::mousePressEvent(event);
    if( event->button() != Qt::LeftButton )
    {
        b_leftbtn_dwn = false;
        return;
    }

    PhotoEditViewScene *pEditScene = dynamic_cast<PhotoEditViewScene*>(this->scene());
    if ( pEditScene )
    {
        pEditScene->selectItm(NULL, this);
    }

    b_leftbtn_dwn = true;

    if( mm_style == MMN )
    {
        //do nth
        return;
    }

    QPointF pos = this->pos();
    QRectF itmrct = item_rect.translated(pos.x(), pos.y());

    PhotoEditViewScene *editscene = dynamic_cast<PhotoEditViewScene *>(scene());
    if( mm_style >= MM0 && mm_style <= MM7 )
    {
        editscene->getMainFrame()->OnResizeTxtBox(itmrct, 0);
    }
    else if( mm_style == MMR )
    {
        editscene->getMainFrame()->OnRotateTxtBox(itmrct, rot_angle, 0);
    }
    else if( mm_style == MMT )
    {
        editscene->getMainFrame()->OnMvTxtBox(itmrct, 0);
    }
   // setCursor(mouse_curs[(int)mm_style]);
}

void TextViewItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{   
    static QPointF d; //accumulated pos

    if( !b_leftbtn_dwn )
        return;

    if( !this->isSelected() )
        return;

    if( mm_style == MMN )
    {
        //do nth
        return;
    }

    QPointF dd = event->pos() - event->lastPos();
    d += dd;

    bool need_update = false;
    do{
        if( mm_style == MM0 )
        {
            if( (qAbs(d.x()) >= MOUSEMV_THRES || qAbs(d.y()) >= MOUSEMV_THRES) &&
                (d.x()*d.y()>0) &&
                ((item_rect.width() - d.x() >= MIN_HW) && (item_rect.height() - d.y() >= MIN_HW)) )
            {
                QPointF tmp = pos();
                tmp += (d*text_font_ratio);
                setPos(tmp);

                item_rect.adjust(0, 0, -d.x(), -d.y());
                need_update = true;
            }
        }
        else if( mm_style == MM1 )
        {
            if( qAbs(d.y()) >= MOUSEMV_THRES &&
                (item_rect.height() - d.y() >= MIN_HW) )
            {
                QPointF tmp = pos();
                tmp += QPointF(0, d.y()*text_font_ratio);
                setPos(tmp);

                item_rect.adjust(0, 0, 0, -d.y());
                need_update = true;
            }
        }
        else if( mm_style == MM2 )
        {
            if( (qAbs(d.x()) >= MOUSEMV_THRES || qAbs(d.y()) >= MOUSEMV_THRES) &&
                (d.x()*d.y()<0) &&
                ((item_rect.width() + d.x() >= MIN_HW)&&(item_rect.height() - d.y() >= MIN_HW)) )
            {
                QPointF tmp = pos();
                tmp += QPointF(0, d.y()*text_font_ratio);
                setPos(tmp);

                item_rect.adjust(0, 0, d.x(), -d.y());
                need_update = true;
            }
        }
        else if( mm_style == MM3 )
        {
            if( qAbs(d.x()) >= MOUSEMV_THRES &&
                (item_rect.width() + d.x() >= MIN_HW) )
            {
                item_rect.adjust(0, 0, d.x(), 0);
                need_update = true;
            }
        }
        else if( mm_style == MM4 )
        {
            if( (qAbs(d.x()) >= MOUSEMV_THRES || qAbs(d.y()) >= MOUSEMV_THRES) &&
                (d.x()*d.y()>0) &&
                    ((item_rect.width() + d.x() >= MIN_HW)&&(item_rect.height() + d.y() >= MIN_HW)) )
            {
                item_rect.adjust(0, 0, d.x(), d.y());
                need_update = true;
            }
        }
        else if( mm_style == MM5 )
        {
            if( qAbs(d.y()) >= MOUSEMV_THRES &&
                (item_rect.height() + d.y() >= MIN_HW) )
            {
                item_rect.adjust(0, 0, 0, d.y());
                need_update = true;
            }
        }
        else if( mm_style == MM6 )
        {
            if( (qAbs(d.x()) >= MOUSEMV_THRES || qAbs(d.y()) >= MOUSEMV_THRES) &&
                (d.x()*d.y()<0) &&
                    ((item_rect.width() - d.x() >= MIN_HW)&&(item_rect.height() + d.y() >= MIN_HW)) )
            {
                QPointF tmp = pos();
                tmp += QPointF(d.x()*text_font_ratio,0);
                setPos(tmp);

                item_rect.adjust(0, 0, -d.x(), d.y());
                need_update = true;
            }
        }
        else if( mm_style == MM7 )
        {
            if( qAbs(d.x()) >= MOUSEMV_THRES &&
                (item_rect.width() - d.x() >= MIN_HW) )
            {
                QPointF tmp = pos();
                tmp += QPointF(d.x()*text_font_ratio,0);
                setPos(tmp);

                item_rect.adjust(0, 0, -d.x(), 0);
                need_update = true;
            }
        }
        else if( mm_style == MMR )
        {
            if( d.y() > 2*MOUSEMV_THRES )//make the rotate not too fast
            {
                rot_angle += 5*text_font_ratio;
                this->rotate(rot_angle);
                need_update = true;
            }
            else if( d.y() < -2*MOUSEMV_THRES )
            {
                rot_angle -= 5*text_font_ratio;
                this->rotate(rot_angle);
                need_update = true;
            }
        }
        else if( mm_style == MMT )
        {
            if( qAbs(d.x()) >= MOUSEMV_THRES || qAbs(d.y()) >= MOUSEMV_THRES )
            {
                this->translate(d.x()*text_font_ratio,d.y()*text_font_ratio);
                need_update = true;
            }
        }

        if( need_update && mm_style >= MM0 && mm_style <= MM7 )
        {
            calItemRect(item_rect, text_font_ratio);
        }
    }while(0);

    if( need_update )
    {
        QPointF pos = this->pos();
        QRectF itmrct = item_rect.translated(pos.x(), pos.y());

        PhotoEditViewScene *editscene = dynamic_cast<PhotoEditViewScene *>(scene());
        if( mm_style >= MM0 && mm_style <= MM7 )
        {
            editscene->getMainFrame()->OnResizeTxtBox(itmrct);
        }
        else if( mm_style == MMR )
        {
            editscene->getMainFrame()->OnRotateTxtBox(itmrct, rot_angle);
        }
        else if( mm_style == MMT )
        {
            editscene->getMainFrame()->OnMvTxtBox(itmrct);
        }

        // this->scene()->update();//not call this->update, because it maybe smaller
        d = QPointF();
    }
}

void TextViewItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    b_leftbtn_dwn = false;

    if( mm_style == MMN )
    {
        //do nth
        return;
    }

    QPointF pos = this->pos();
    QRectF itmrct = item_rect.translated(pos.x(), pos.y());

    PhotoEditViewScene *editscene = dynamic_cast<PhotoEditViewScene *>(scene());
    if( mm_style >= MM0 && mm_style <= MM7 )
    {
        editscene->getMainFrame()->OnResizeTxtBox(itmrct, 3);
    }
    else if( mm_style == MMR )
    {
        editscene->getMainFrame()->OnRotateTxtBox(itmrct, rot_angle, 3);
    }
    else if( mm_style == MMT )
    {
        editscene->getMainFrame()->OnMvTxtBox(itmrct, 3);
    }

    //setCursor(mouse_curs[(int)mm_style]);
}

void TextViewItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
}

void TextViewItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    static QCursor mouse_curs[] = {
        Qt::SizeFDiagCursor,
        Qt::SizeVerCursor,
        Qt::SizeBDiagCursor,
        Qt::SizeHorCursor,
        Qt::SizeFDiagCursor,
        Qt::SizeVerCursor,
        Qt::SizeBDiagCursor,
        Qt::SizeHorCursor,
        rotate_cur, //rotate
        Qt::OpenHandCursor, //translate
        Qt::ArrowCursor //normal one
    };

    if( b_leftbtn_dwn )
        return;

    if( !this->isSelected() )
        return;

    do{
        QPointF pnt = event->pos();
        bool hit = false;
        for(int i = 0; i < 8; i++)
        {
            if( dragRects[i].contains(pnt) )
            {
                mm_style = MouseMovStyle(i);
                hit = true;
                break;
            }
        }
        if( hit )
            break;

        if( rotateRect.contains(pnt) )
        {
            mm_style = MMR;
            hit = true;
        }
        if( hit )
            break;

        QRectF rect = item_rect;
        qreal dia = 2*RADIUS/text_font_ratio;
        rect.adjust(dia,dia,-dia,-dia);
        if( rect.contains(pnt) )
        {
            mm_style = MMT;
            hit = true;
        }
        if( !hit )
        {
            mm_style = MMN;
        }
    }while(0);

    setCursor(mouse_curs[(int)mm_style]);
}

void TextViewItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
}

/*******************Private Part of TextItem***************************/
void TextViewItem::calItemRect(const QRectF& rect, qreal font_ratio)
{
    prepareGeometryChange();

    item_rect = rect;

    qreal dia = 2*RADIUS/font_ratio;

    dragRects[0] = QRectF(item_rect.x()-(dia/2.0), item_rect.y()-(dia/2.0), dia, dia);
    dragRects[1] = dragRects[0].translated(item_rect.width()/2, 0);
    dragRects[2] = dragRects[1].translated(item_rect.width()/2, 0);
    dragRects[3] = dragRects[2].translated(0, item_rect.height()/2);
    dragRects[4] = dragRects[3].translated(0, item_rect.height()/2);
    dragRects[5] = dragRects[4].translated(-item_rect.width()/2, 0);
    dragRects[6] = dragRects[5].translated(-item_rect.width()/2, 0);
    dragRects[7] = dragRects[6].translated(0,-item_rect.height()/2);

    rotateRect = QRectF(item_rect.x() + item_rect.width() + (dia/2.0) * (RIGHT_RAT-2),
                        item_rect.y() + item_rect.height()/2,
                        dia, dia);

    this->setTextWidth(item_rect.width());
}

void TextViewItem::rotate(qreal angle)
{
    qDebug() << "pos of rotate is: " << this->pos();
    qDebug() << "item_rect of rotate is: " << item_rect;
    this->setTransformOriginPoint(item_rect.center());
    this->setRotation(angle);
    qDebug() << "after pos of rotate is: " << this->pos();
    qDebug() << "after item_rect of rotate is: " << item_rect;
}

void TextViewItem::translate(qreal dx, qreal dy)
{
    qDebug() << "item_rect of translate is: " << item_rect;
    this->moveBy(dx,dy);
}
