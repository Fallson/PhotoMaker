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

#ifndef PhotoBWCEditWidget_H
#define PhotoBWCEditWidget_H

#include <QWidget>
#include <QDialog>
#include <QPixmap>
#include <QImage>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QPushButton>

struct BWC{
    int hue;
    int sat;
};

class PhotoBWCEditWidget : public QDialog
{
    Q_OBJECT

public:
    PhotoBWCEditWidget(const QPixmap& p, QWidget* parent = 0);
    bool isOKClick(){ return ok_; }
    BWC getBWC(){ return bwc_; }
    static bool changeImageBWC(QImage* image, const BWC& bwc, int all = 0);//0 for all chanels, 1 for hue, 2 for sat

private slots:
    void changeHue(int hue);
    void changeHue(QString hue_str);
    void changeSat(int sat);
    void changeSat(QString sat_str);
    void black_white();
    void ok();
    void reset();
    void cancel();

private:
    void updateBWC(const BWC& bwc, int chanel);

private:
    QLabel* left;
    QLabel* right;

    QLabel* hue_label;
    QSlider* hue_slider;
    QLineEdit* hue_edit;

    QLabel* sat_label;
    QSlider* sat_slider;
    QLineEdit* sat_edit;

    QPushButton* reset_btn;
    QPushButton* black_white_btn;
    QPushButton* ok_btn;
    QPushButton* cancel_btn;
private:
    bool ok_;
    BWC bwc_;
    QPixmap left_pixmap;
    QImage  right_img;
};

#endif
