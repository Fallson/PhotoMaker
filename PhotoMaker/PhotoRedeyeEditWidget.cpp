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
#include "PhotoRedeyeEditWidget.h"

static const QSize imageSize(400,280);

static void redeye_remove(QImage* img, const QRect& rect)
{
    qDebug() << "The rect is: " << rect;

    if( img->rect().contains(rect) )
    {
        for( int i = rect.x(); i <= rect.right(); i++ )
        {
            for( int j = rect.y(); j <= rect.bottom(); j++ )
            {
                QColor clr = img->pixel(i,j);
                qreal redIntensity = (qreal)clr.red() / ((qreal)(clr.green() + clr.blue())/2);
                if( redIntensity > 1.75 )
                {
                    clr.setRed((clr.green() + clr.blue())/2);
                    img->setPixel(i,j,clr.rgb());
                }
            }
        }
    }
}

/***************************************Photolabel******************************************/
PhotoLabel::PhotoLabel(QWidget *parent)
    :QLabel(parent)
{
    b_leftbtn_down = false;
    last_pos = QPoint(0,0);
    cur_pos = QPoint(0,0);
}

void PhotoLabel::setImg(QImage* parent_img, QImage *img)
{
    m_parent_img = parent_img;
    m_ori_img = img;
    m_paint_img = *m_ori_img;

    this->setPixmap(QPixmap::fromImage(m_paint_img));
    this->update();
}

void PhotoLabel::mouseMoveEvent(QMouseEvent *event)
{
    if( !b_leftbtn_down )
        return;

    cur_pos = event->pos();
    QPoint d = cur_pos - last_pos;

    if( qAbs(d.x()) > 5 && qAbs(d.y()) > 5 )
    {
        //draw the rect
        m_paint_img = *m_ori_img;
        QPainter img_painter(&m_paint_img);
        QPen pen;
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(2);
        pen.setBrush(Qt::black);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        img_painter.setPen(pen);
        img_painter.setBrush(Qt::NoBrush);
        img_painter.drawRect(QRect(last_pos, cur_pos).normalized());

        this->setPixmap(QPixmap::fromImage(m_paint_img));
        this->update();
    }
}

void PhotoLabel::mousePressEvent(QMouseEvent *event)
{
    if( event->button() != Qt::LeftButton )
        return;

    b_leftbtn_down = true;
    last_pos = event->pos();
}

void PhotoLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if( !b_leftbtn_down )
        return;

    cur_pos = event->pos();

    qreal xfactor = (qreal)m_parent_img->width()/(qreal)m_ori_img->width();
    qreal yfactor = (qreal)m_parent_img->height()/(qreal)m_ori_img->height();

    QRect rect = QRect(last_pos, cur_pos).normalized();
    QPoint p1 = rect.topLeft();
    p1.setX(p1.x() * xfactor);
    p1.setY(p1.y() * yfactor);
    QPoint p2 = rect.bottomRight();
    p2.setX(p2.x() * xfactor);
    p2.setY(p2.y() * yfactor);
    QRect rect2 = QRect(p1, p2);

    //update the image of the parent
    redeye_remove(m_parent_img, rect2);

    //update the pixmap of the label
    redeye_remove(m_ori_img, rect);
    m_paint_img = *m_ori_img;
    this->setPixmap(QPixmap::fromImage(m_paint_img));
    this->update();

    //hide the rect drawing
    b_leftbtn_down = false;
}

/***************************************PhotoRedeyeEditWidget******************************************/
PhotoRedeyeEditWidget::PhotoRedeyeEditWidget(const QPixmap& pixmap, QWidget* parent)
:QDialog(parent)
{
    setWindowIcon(QIcon("Resources\\images\\AppIcon.ico"));
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );


    ok_ = true;
    ori_img = pixmap.toImage();
    left_img = ori_img;
    right_img = left_img.scaled(imageSize, Qt::KeepAspectRatio);

    this->setGeometry(100, 100, right_img.width(), right_img.height() + 20);

    right = new PhotoLabel(this);
    right->resize(QSize(right_img.width(), right_img.height()));
    right->setImg(&left_img, &right_img);
    QHBoxLayout *imageLayout = new QHBoxLayout;
    imageLayout->addWidget(right);

    reset_btn = new QPushButton("Reset");
    ok_btn = new QPushButton("OK");
    cancel_btn = new QPushButton("Cancel");
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(reset_btn);
    btnLayout->addWidget(ok_btn);
    btnLayout->addWidget(cancel_btn);
    btnLayout->insertSpacing(1, 180);
    connect(reset_btn, SIGNAL(clicked()), this, SLOT(reset()));
    connect(ok_btn, SIGNAL(clicked()), this, SLOT(ok()));
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(cancel()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(imageLayout);
    mainLayout->setAlignment(imageLayout, Qt::AlignHCenter);
    mainLayout->addLayout(btnLayout);

    this->setLayout(mainLayout);
    //this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("Red eye remove");
    //this->setWindowModality(Qt::ApplicationModal);
}

void PhotoRedeyeEditWidget::ok()
{
    ok_ = true;
    this->close();
}

void PhotoRedeyeEditWidget::cancel()
{
    ok_ = false;
    this->close();
}

void PhotoRedeyeEditWidget::reset()
{
    left_img = ori_img;
    right_img = left_img.scaled(imageSize, Qt::IgnoreAspectRatio);
    right->setImg(&left_img, &right_img);
}


