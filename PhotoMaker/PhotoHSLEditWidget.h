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

#ifndef PhotoHSLEditWidget_H
#define PhotoHSLEditWidget_H

#include <QWidget>
#include <QDialog>
#include <QPixmap>
#include <QImage>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QPushButton>

struct HSL{
    int hue;
    int sat;
    int light;
};

class PhotoHSLEditWidget : public QDialog
{
    Q_OBJECT

public:
    PhotoHSLEditWidget(const QPixmap& p, QWidget* parent = 0);
    bool isOKClick(){ return ok_; }
    HSL getHSL(){ return hsl_; }
    static bool changeImageHSL(QImage* image, const HSL& hsl, int all = 0);//0 for all chanels, 1 for hue, 2 for sat, 3 for lig only

private slots:
    void changeHue(int hue);
    void changeHue(QString hue_str);
    void changeSat(int sat);
    void changeSat(QString sat_str);
    void changeLight(int light);
    void changeLight(QString light_str);
    void ok();
    void reset();
    void cancel();

private:
    void updateHSL(const HSL& hsl, int chanel);

private:
    QLabel* left;
    QLabel* right;

    QLabel* hue_label;
    QSlider* hue_slider;
    QLineEdit* hue_edit;

    QLabel* sat_label;
    QSlider* sat_slider;
    QLineEdit* sat_edit;

    QLabel* light_label;
    QSlider* light_slider;
    QLineEdit* light_edit;

    QPushButton* reset_btn;
    QPushButton* ok_btn;
    QPushButton* cancel_btn;
private:
    bool ok_;
    HSL hsl_;
    QPixmap left_pixmap;
    QImage  right_img;
};

#endif
