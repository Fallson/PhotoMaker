#ifndef PMPICEDIT_H
#define PMPICEDIT_H

#include <QWidget>
#include "ui_pmpicedit.h"

class PhotoMaker;
class PmPicEdit : public QWidget
{
	Q_OBJECT

public:
	PmPicEdit(PhotoMaker *pMainFrame, QWidget *parent = 0);
	~PmPicEdit();

public:
	void setScaleRatio(qreal ratio);
	void setDpi(int dpi);
public slots:
	void OnZoomPhoto(int);

private:
	Ui::PmPicEdit ui;

	PhotoMaker *_pMainFrame;
};

#endif // PMPICEDIT_H
