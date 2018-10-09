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
#include "PhotoLCIGEditWidget.h"

static const QSize imageSize(200,140);

PhotoLCIGEditWidget::PhotoLCIGEditWidget(const QPixmap& pixmap, QWidget* parent)
:QDialog(parent)
{
    setWindowIcon(QIcon("Resources\\images\\AppIcon.ico"));
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );


    memset(&lcig_, 0, sizeof(LCIG));
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

    lig_label = new QLabel("Lightness");
    lig_slider = new QSlider(Qt::Horizontal);
    lig_slider->setRange(-100,100);
    lig_slider->setSingleStep(1);
    lig_slider->setTickPosition(QSlider::TicksBelow);
    lig_slider->setTickInterval(10);
    lig_slider->setValue(0);
    lig_slider->setTracking(false);
    lig_edit = new QLineEdit("0");
    QHBoxLayout *ligLayout = new QHBoxLayout;
    ligLayout->addWidget(lig_label);
    ligLayout->addWidget(lig_slider);
    ligLayout->addWidget(lig_edit);
    ligLayout->setStretch(0,12);
    ligLayout->setStretch(1,100);
    ligLayout->setStretch(2,8);
    connect(lig_slider, SIGNAL(valueChanged(int)), this, SLOT(changeLightness(int)));
    connect(lig_edit, SIGNAL(textChanged(QString)), this, SLOT(changeLightness(QString)));

    con_label = new QLabel("Contrast ");
    con_slider = new QSlider(Qt::Horizontal);
    con_slider->setRange(-100,100);
    con_slider->setSingleStep(1);
    con_slider->setTickPosition(QSlider::TicksBelow);
    con_slider->setTickInterval(10);
    con_slider->setValue(0);
    con_slider->setTracking(false);
    con_edit = new QLineEdit("0");
    QHBoxLayout *conLayout = new QHBoxLayout;
    conLayout->addWidget(con_label);
    conLayout->addWidget(con_slider);
    conLayout->addWidget(con_edit);
    conLayout->setStretch(0,12);
    conLayout->setStretch(1,100);
    conLayout->setStretch(2,8);
    connect(con_slider, SIGNAL(valueChanged(int)), this, SLOT(changeContrast(int)));
    connect(con_edit, SIGNAL(textChanged(QString)), this, SLOT(changeContrast(QString)));

    ite_label = new QLabel("Itensity   ");
    ite_slider = new QSlider(Qt::Horizontal);
    ite_slider->setRange(-100,100);
    ite_slider->setSingleStep(1);
    ite_slider->setTickPosition(QSlider::TicksBelow);
    ite_slider->setTickInterval(10);
    ite_slider->setValue(0);
    ite_slider->setTracking(false);
    ite_edit = new QLineEdit("0");
    QHBoxLayout *iteLayout = new QHBoxLayout;
    iteLayout->addWidget(ite_label);
    iteLayout->addWidget(ite_slider);
    iteLayout->addWidget(ite_edit);
    iteLayout->setStretch(0,12);
    iteLayout->setStretch(1,100);
    iteLayout->setStretch(2,8);
    connect(ite_slider, SIGNAL(valueChanged(int)), this, SLOT(changeItensity(int)));
    connect(ite_edit, SIGNAL(textChanged(QString)), this, SLOT(changeItensity(QString)));

    gam_label = new QLabel("Gamma    ");
    gam_slider = new QSlider(Qt::Horizontal);
    gam_slider->setRange(-100,100);
    gam_slider->setSingleStep(1);
    gam_slider->setTickPosition(QSlider::TicksBelow);
    gam_slider->setTickInterval(10);
    gam_slider->setValue(0);
    gam_slider->setTracking(false);
    gam_edit = new QLineEdit("1.0");
    QHBoxLayout *gamLayout = new QHBoxLayout;
    gamLayout->addWidget(gam_label);
    gamLayout->addWidget(gam_slider);
    gamLayout->addWidget(gam_edit);
    gamLayout->setStretch(0,12);
    gamLayout->setStretch(1,100);
    gamLayout->setStretch(2,8);
    connect(gam_slider, SIGNAL(valueChanged(int)), this, SLOT(changeGamma(int)));
    connect(gam_edit, SIGNAL(textChanged(QString)), this, SLOT(changeGamma(QString)));

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
    mainLayout->addLayout(ligLayout);
    mainLayout->addLayout(conLayout);
    mainLayout->addLayout(iteLayout);
    mainLayout->addLayout(gamLayout);
    mainLayout->addLayout(btnLayout);

    this->setLayout(mainLayout);
    //this->setFixedSize(400,200);
    this->setWindowTitle("Lightness, contrast, itensity, gamma");
    //this->setWindowModality(Qt::ApplicationModal);
}

void PhotoLCIGEditWidget::changeLightness(int lig)
{
    lig_edit->setText(QString("%1").arg(lig));
    lcig_.lig = lig;
    updateLCIG(lcig_);
}

void PhotoLCIGEditWidget::changeLightness(QString lig_str)
{
    int lig_value = lig_str.toInt();
    if( lig_value > 100 )
        lig_value = 100;
    if( lig_value < -100 )
        lig_value = -100;

    lig_slider->setValue(lig_value);
    lcig_.lig = lig_value;
    updateLCIG(lcig_);
}

void PhotoLCIGEditWidget::changeContrast(int con)
{
    con_edit->setText(QString("%1").arg(con));
    lcig_.con = con;
    updateLCIG(lcig_);
}

void PhotoLCIGEditWidget::changeContrast(QString con_str)
{
    int con_value = con_str.toInt();
    if( con_value > 100 )
        con_value = 100;
    if( con_value < -100)
        con_value = -100;

    con_slider->setValue(con_value);
    lcig_.con = con_value;
    updateLCIG(lcig_);
}

void PhotoLCIGEditWidget::changeItensity(int ite)
{
    ite_edit->setText(QString("%1").arg(ite));
    lcig_.ite = ite;
    updateLCIG(lcig_);
}

void PhotoLCIGEditWidget::changeItensity(QString ite_str)
{
    int ite_value = ite_str.toInt();
    if( ite_value > 100 )
        ite_value = 100;
    if( ite_value < -100)
        ite_value = -100;

    ite_slider->setValue(ite_value);
    lcig_.ite = ite_value;
    updateLCIG(lcig_);
}

void PhotoLCIGEditWidget::changeGamma(int gam)
{
    qreal g = translateGamma(gam);
    gam_edit->setText(QString("%1").arg(g));
    lcig_.gam = gam;
    updateLCIG(lcig_);
}

void PhotoLCIGEditWidget::changeGamma(QString gam_str)
{
    qreal gam_value = gam_str.toDouble();
    if( gam_value > 10.0 )
        gam_value = 10.0;
    if( gam_value < 0.1)
        gam_value = 0.1;

    int g = retranslateGamma(gam_value);
    gam_slider->setValue(g);
    lcig_.gam = g;
    updateLCIG(lcig_);
}

void PhotoLCIGEditWidget::ok()
{
    ok_ = true;
    this->close();
}

void PhotoLCIGEditWidget::cancel()
{
    ok_ = false;
    this->close();
}

void PhotoLCIGEditWidget::reset()
{
    memset(&lcig_, 0, sizeof(LCIG));

    lig_slider->setValue(lcig_.lig);
    lig_edit->setText(QString("%1").arg(lcig_.lig));

    con_slider->setValue(lcig_.con);
    con_edit->setText(QString("%1").arg(lcig_.con));

    ite_slider->setValue(lcig_.ite);
    ite_edit->setText(QString("%1").arg(lcig_.ite));

    gam_slider->setValue(lcig_.gam);
    gam_edit->setText(QString("1.0"));

    right_img = left_pixmap.toImage();
    right->setPixmap(left_pixmap);
}

int PhotoLCIGEditWidget::retranslateGamma(qreal g)
{
    int value = 0;

    if( g >= 1.0 && g <= 10.0 )
    {
        value = 100.0*(g-1.0)/(10.0-1.0);
    }
    else if( g >= 0.1 && g < 1.0 )
    {
        value = 100.0*(g-1.0)/(1.0-0.1);
    }
    else
    {
        value = 0;
    }

    return value;
}

qreal PhotoLCIGEditWidget::translateGamma(int g)
{
    qreal value = 0;
    if( g > 0 )
    {
        value = (10.0-1.0)*g/100.0 + 1.0;
    }
    else
    {
        value = (1.0-0.1)*g/100.0 + 1.0;
    }
    return value;
}

void PhotoLCIGEditWidget::updateLCIG(const LCIG &lcig)
{
    //update the right_img into right label
    QImage tmp_img(right_img);
    bool ret = changeImageLCIG(&tmp_img, lcig);
    if( ret == false )
    {
        reset();
        return;
    }
    right->setPixmap(QPixmap::fromImage(tmp_img));
}

#define RGBMAX 255
#define RGBMIN 0
bool PhotoLCIGEditWidget::changeImageLCIG(QImage *image, const LCIG &lcig)
{
    //static function to change the image's lcig
    if( lcig.lig == 0 && lcig.con == 0 && lcig.ite == 0 && lcig.gam == 0 )
        return false;

    int width = image->width();
    int height = image->height();
    int r, g, b;

    int l = 255*lcig.lig/100;
    qreal c = 0.0;
    if( lcig.con > 0 )
        c = (10.0-1.0)*lcig.con/100.0 + 1.0;
    else
        c = (1.0-0.0)*lcig.con/100.0 + 1.0;
    int cc =127*(1-c);
    qreal it = lcig.ite/100.0 + 1.0;
    qreal ga = translateGamma(lcig.gam);

    for( int i = 0; i < width; i++ )
    {
        for( int j = 0; j < height; j++ )
        {
            QColor clr = image->pixel(i,j);

            r = (clr.red()*c + cc + l)*it;
            g = (clr.green()*c + cc + l)*it;
            b = (clr.blue()*c + cc + l)*it;

            r = qPow(r,ga);
            g = qPow(g,ga);
            b = qPow(b,ga);

            if( r > RGBMAX )
                r = RGBMAX;
            else if( r < RGBMIN )
                r = RGBMIN;
            clr.setRed(r);

            if( g > RGBMAX )
                g = RGBMAX;
            else if( g < RGBMIN )
                g = RGBMIN;
            clr.setGreen(g);

            if( b > RGBMAX )
                b = RGBMAX;
            else if( b < RGBMIN )
                b = RGBMIN;
            clr.setBlue(b);

            image->setPixel(i,j,clr.rgb());
        }
    }

    return true;
}
