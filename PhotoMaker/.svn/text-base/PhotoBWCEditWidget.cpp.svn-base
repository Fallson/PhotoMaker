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
#include "PhotoBWCEditWidget.h"


static const QSize imageSize(200,140);

PhotoBWCEditWidget::PhotoBWCEditWidget(const QPixmap& pixmap, QWidget* parent)
:QDialog(parent)
{
    setWindowIcon(QIcon("Resources\\images\\AppIcon.ico"));
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );

	memset(&bwc_, 0, sizeof(BWC));
    ok_ = true;
    left_pixmap = pixmap.scaled(imageSize, Qt::KeepAspectRatio);
    right_img = left_pixmap.toImage();

    this->setGeometry(200, 200, 400, 200);


    left = new QLabel("left image");
    left->resize(imageSize);
    left->setPixmap(left_pixmap);
    right = new QLabel("right image");
    right->resize(imageSize);
    right->setPixmap(left_pixmap);
    QHBoxLayout *imageLayout = new QHBoxLayout;
    imageLayout->addWidget(left);
    imageLayout->addWidget(right);
    imageLayout->insertSpacing(1, 30);

    hue_label = new QLabel("Hue          ");
    hue_slider = new QSlider(Qt::Horizontal);
    hue_slider->setRange(-100,100);
    hue_slider->setSingleStep(1);
    hue_slider->setTickPosition(QSlider::TicksBelow);
    hue_slider->setTickInterval(10);
    hue_slider->setValue(0);
    hue_slider->setTracking(false);
    hue_edit = new QLineEdit("0");
    QHBoxLayout *hueLayout = new QHBoxLayout;
    hueLayout->addWidget(hue_label);
    hueLayout->addWidget(hue_slider);
    hueLayout->addWidget(hue_edit);
    hueLayout->setStretch(0,12);
    hueLayout->setStretch(1,100);
    hueLayout->setStretch(2,8);
    connect(hue_slider, SIGNAL(valueChanged(int)), this, SLOT(changeHue(int)));
    connect(hue_edit, SIGNAL(textChanged(QString)), this, SLOT(changeHue(QString)));

    sat_label = new QLabel("Saturation");
    sat_slider = new QSlider(Qt::Horizontal);
    sat_slider->setRange(-100,100);
    sat_slider->setSingleStep(1);
    sat_slider->setTickPosition(QSlider::TicksBelow);
    sat_slider->setTickInterval(10);
    sat_slider->setValue(0);
    sat_slider->setTracking(false);
    sat_edit = new QLineEdit("0");
    QHBoxLayout *satLayout = new QHBoxLayout;
    satLayout->addWidget(sat_label);
    satLayout->addWidget(sat_slider);
    satLayout->addWidget(sat_edit);
    satLayout->setStretch(0,12);
    satLayout->setStretch(1,100);
    satLayout->setStretch(2,8);
    connect(sat_slider, SIGNAL(valueChanged(int)), this, SLOT(changeSat(int)));
    connect(sat_edit, SIGNAL(textChanged(QString)), this, SLOT(changeSat(QString)));

    reset_btn = new QPushButton("Reset");
    black_white_btn = new QPushButton("Black and white");
    ok_btn = new QPushButton("OK");
    cancel_btn = new QPushButton("Cancel");
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(reset_btn);
    btnLayout->addWidget(black_white_btn);
    btnLayout->addWidget(ok_btn);
    btnLayout->addWidget(cancel_btn);
    btnLayout->insertSpacing(2, 200);
    connect(reset_btn, SIGNAL(clicked()), this, SLOT(reset()));
    connect(black_white_btn, SIGNAL(clicked()), this, SLOT(black_white()));
    connect(ok_btn, SIGNAL(clicked()), this, SLOT(ok()));
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(cancel()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(imageLayout);
    mainLayout->setAlignment(imageLayout, Qt::AlignHCenter);
    mainLayout->addLayout(hueLayout);
    mainLayout->addLayout(satLayout);
    mainLayout->addLayout(btnLayout);

    this->setLayout(mainLayout);
    //this->setFixedSize(400,200);
    this->setWindowTitle("Black and white, colorize");
    //this->setWindowModality(Qt::ApplicationModal);

    reset();
}

void PhotoBWCEditWidget::changeHue(int hue)
{
    hue_edit->setText(QString("%1").arg(hue));
    bwc_.hue = hue;
    updateBWC(bwc_,1);
}

void PhotoBWCEditWidget::changeHue(QString hue_str)
{
    int hue_value = hue_str.toInt();
    if( hue_value > 100 )
        hue_value = 100;
    if( hue_value < -100 )
        hue_value = -100;

    hue_slider->setValue(hue_value);
    bwc_.hue = hue_value;
    updateBWC(bwc_,1);
}

void PhotoBWCEditWidget::changeSat(int sat)
{
    sat_edit->setText(QString("%1").arg(sat));
    bwc_.sat = sat;
    updateBWC(bwc_,2);
}

void PhotoBWCEditWidget::changeSat(QString sat_str)
{
    int sat_value = sat_str.toInt();
    if( sat_value > 100 )
        sat_value = 100;
    if( sat_value < -100)
        sat_value = -100;

    sat_slider->setValue(sat_value);
    bwc_.sat = sat_value;
    updateBWC(bwc_,2);
}

void PhotoBWCEditWidget::ok()
{
    ok_ = true;
    this->close();
}

void PhotoBWCEditWidget::black_white()
{
    bwc_.sat = -100;
    sat_slider->setValue(bwc_.sat);
    sat_edit->setText(QString("%1").arg(bwc_.sat));
    updateBWC(bwc_,2);
}

void PhotoBWCEditWidget::cancel()
{
    ok_ = false;
    this->close();
}

void PhotoBWCEditWidget::reset()
{
    bwc_.hue = -80;
    bwc_.sat = -40;

    hue_slider->setValue(bwc_.hue);
    hue_edit->setText(QString("%1").arg(bwc_.hue));

    sat_slider->setValue(bwc_.sat);
    sat_edit->setText(QString("%1").arg(bwc_.sat));

    right_img = left_pixmap.toImage();
    updateBWC(bwc_, 0);
}

void PhotoBWCEditWidget::updateBWC(const BWC& bwc, int chanel)
{
    //update the right_img into right label
    bool ret = changeImageBWC(&right_img, bwc, chanel);
    if( ret == false )
        return;

    right->setPixmap(QPixmap::fromImage(right_img));
}

#define HUEMAX 1.0
#define HUEMIN 0.0
#define SATMAX 1.0
#define SATMIN 0.0
bool PhotoBWCEditWidget::changeImageBWC(QImage *image, const BWC &bwc, int all)
{
    //static function to change the image's hsv

    int width = image->width();
    int height = image->height();

    qreal d_hue = (HUEMAX-HUEMIN)/200;
    qreal d_sat = (SATMAX-SATMIN)/200;
    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            QColor clr = image->pixel(i,j);
            QColor hsvclr = clr.toHsv();

            qreal hue, sat, val;
            hsvclr.getHsvF(&hue, &sat, &val);

            switch(all)
            {
            case 0:
                hue = d_hue * (bwc.hue + 100) + HUEMIN;
                sat = d_sat * (bwc.sat + 100) + SATMIN;
                break;
            case 1:
                hue = d_hue * (bwc.hue + 100) + HUEMIN;
                break;
            case 2:
                sat = d_sat * (bwc.sat + 100) + SATMIN;
                break;
            }

            hsvclr.setHsvF(hue,sat,val);
            image->setPixel(i,j,hsvclr.toRgb().rgb());
        }
    }

    return true;
}
