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
#include "PhotoHSLEditWidget.h"


static const QSize imageSize(200,140);

PhotoHSLEditWidget::PhotoHSLEditWidget(const QPixmap& pixmap, QWidget* parent)
:QDialog(parent)
{
    setWindowIcon(QIcon("Resources\\images\\AppIcon.ico"));
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );


    memset(&hsl_, 0, sizeof(HSL));
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

    light_label = new QLabel("Lightness ");
    light_slider = new QSlider(Qt::Horizontal);
    light_slider->setRange(-100,100);
    light_slider->setSingleStep(1);
    light_slider->setTickPosition(QSlider::TicksBelow);
    light_slider->setTickInterval(10);
    light_slider->setValue(0);
    light_slider->setTracking(false);
    light_edit = new QLineEdit("0");
    QHBoxLayout *lightLayout = new QHBoxLayout;
    lightLayout->addWidget(light_label);
    lightLayout->addWidget(light_slider);
    lightLayout->addWidget(light_edit);
    lightLayout->setStretch(0,12);
    lightLayout->setStretch(1,100);
    lightLayout->setStretch(2,8);
    connect(light_slider, SIGNAL(valueChanged(int)), this, SLOT(changeLight(int)));
    connect(light_edit, SIGNAL(textChanged(QString)), this, SLOT(changeLight(QString)));

    reset_btn = new QPushButton("Reset");
    ok_btn = new QPushButton("OK");
    cancel_btn = new QPushButton("Cancel");
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(reset_btn);
    btnLayout->addWidget(ok_btn);
    btnLayout->addWidget(cancel_btn);
    btnLayout->insertSpacing(1, 300);
    connect(reset_btn, SIGNAL(clicked()), this, SLOT(reset()));
    connect(ok_btn, SIGNAL(clicked()), this, SLOT(ok()));
    connect(cancel_btn, SIGNAL(clicked()), this, SLOT(cancel()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(imageLayout);
    mainLayout->setAlignment(imageLayout, Qt::AlignHCenter);
    mainLayout->addLayout(hueLayout);
    mainLayout->addLayout(satLayout);
    mainLayout->addLayout(lightLayout);
    mainLayout->addLayout(btnLayout);

    this->setLayout(mainLayout);
    //this->setFixedSize(this->width(),this->height());
    this->setWindowTitle("Hue, saturation, lightness");
    //this->setWindowModality(Qt::ApplicationModal);
}

void PhotoHSLEditWidget::changeHue(int hue)
{
    hue_edit->setText(QString("%1").arg(hue));
    hsl_.hue = hue;
    updateHSL(hsl_,1);
}

void PhotoHSLEditWidget::changeHue(QString hue_str)
{
    int hue_value = hue_str.toInt();
    if( hue_value > 100 )
        hue_value = 100;
    if( hue_value < -100 )
        hue_value = -100;

    hue_slider->setValue(hue_value);
    hsl_.hue = hue_value;
    updateHSL(hsl_,1);
}

void PhotoHSLEditWidget::changeSat(int sat)
{
    sat_edit->setText(QString("%1").arg(sat));
    hsl_.sat = sat;
    updateHSL(hsl_,2);
}

void PhotoHSLEditWidget::changeSat(QString sat_str)
{
    int sat_value = sat_str.toInt();
    if( sat_value > 100 )
        sat_value = 100;
    if( sat_value < -100)
        sat_value = -100;

    sat_slider->setValue(sat_value);
    hsl_.sat = sat_value;
    updateHSL(hsl_,2);
}

void PhotoHSLEditWidget::changeLight(int light)
{
    light_edit->setText(QString("%1").arg(light));
    hsl_.light = light;
    updateHSL(hsl_,3);
}

void PhotoHSLEditWidget::changeLight(QString light_str)
{
    int light_value = light_str.toInt();
    if( light_value > 100 )
        light_value = 100;
    if( light_value < -100)
        light_value = -100;

    light_slider->setValue(light_value);
    hsl_.light = light_value;
    updateHSL(hsl_,3);
}

void PhotoHSLEditWidget::ok()
{
    ok_ = true;
    this->close();
}

void PhotoHSLEditWidget::cancel()
{
    ok_ = false;
    this->close();
}

void PhotoHSLEditWidget::reset()
{
    memset(&hsl_, 0, sizeof(HSL));

    hue_slider->setValue(hsl_.hue);
    hue_edit->setText(QString("%1").arg(hsl_.hue));

    sat_slider->setValue(hsl_.sat);
    sat_edit->setText(QString("%1").arg(hsl_.sat));

    light_slider->setValue(hsl_.light);
    light_edit->setText(QString("%1").arg(hsl_.light));

    right_img = left_pixmap.toImage();
    right->setPixmap(left_pixmap);
}

void PhotoHSLEditWidget::updateHSL(const HSL& hsl, int chanel)
{
    //update the right_img into right label
    bool ret = changeImageHSL(&right_img, hsl, chanel);
    if( ret == false )
    {
        reset();
        return;
    }
    right->setPixmap(QPixmap::fromImage(right_img));
}

#define HUEMAX 359
#define HUEMIN 0
#define SATMAX 255
#define SATMIN 0
#define LIGMAX 255
#define LIGMIN 0
bool PhotoHSLEditWidget::changeImageHSL(QImage *image, const HSL &hsl, int all)
{
    //static function to change the image's hsl
    if( hsl.hue == 0 && hsl.sat == 0 && hsl.light == 0 )
        return false;

    int width = image->width();
    int height = image->height();

    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            QColor clr = image->pixel(i,j);
            QColor hslclr = clr.toHsl();

            int hue, sat, lig;
            hslclr.getHsl(&hue, &sat, &lig);
#if 0
            qDebug() << "hue value is: " << hue;
            qDebug() << "sat value is: " << sat;
            qDebug() << "lig value is: " << lig;
#endif
            switch(all)
            {
            case 0:
                if( hsl.hue > 0 )
                    hue = (HUEMAX-hue)*hsl.hue/100 + hue;
                else
                    hue = (hue-HUEMIN)*hsl.hue/100 + hue;

                if( hsl.sat > 0 )
                    sat = (SATMAX-sat)*hsl.sat/100 + sat;
                else
                    sat = (sat-SATMIN)*hsl.sat/100 + sat;

                if( hsl.light > 0 )
                    lig = (LIGMAX-lig)*hsl.light/100 + lig;
                else
                    lig = (lig-LIGMIN)*hsl.light/100 + lig;
                break;
            case 1:
                if( hsl.hue > 0 )
                    hue = (HUEMAX-hue)*hsl.hue/100 + hue;
                else
                    hue = (hue-HUEMIN)*hsl.hue/100 + hue;
                break;
            case 2:
                if( hsl.sat > 0 )
                    sat = (SATMAX-sat)*hsl.sat/100 + sat;
                else
                    sat = (sat-SATMIN)*hsl.sat/100 + sat;
                break;
            case 3:
                if( hsl.light > 0 )
                    lig = (LIGMAX-lig)*hsl.light/100 + lig;
                else
                    lig = (lig-LIGMIN)*hsl.light/100 + lig;
                break;
            }

            hslclr.setHsl(hue,sat,lig);
            image->setPixel(i,j,hslclr.toRgb().rgb());
        }
    }

    return true;
}
