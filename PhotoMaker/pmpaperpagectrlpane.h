#ifndef PMPAPERPAGECTRLPANE_H
#define PMPAPERPAGECTRLPANE_H

#include <QWidget>
#include <QtGui/QMainWindow>
#include "ui_photomaker.h"
#include <QtGui/qtoolbar.h>
#include <QtGui/qlabel.h>
#include <QtGui/qtreeview.h>
#include <QtGui/qsplitter.h>
#include <QtGui/qtextedit.h>
#include <QtGui/qpushbutton.h>
#include "photomaker.h"

class PmPaperPageCtrlPane : public QLabel
{
	Q_OBJECT

public:
	PmPaperPageCtrlPane(PhotoMaker *pMainFrame, QWidget *parent);
	~PmPaperPageCtrlPane();

public:
	void showPageInfo(const QString &pageInfo);

protected:
    virtual void resizeEvent(QResizeEvent *);

public slots:
	void ZoomIn();
	void ZoomOut();
	void Zoom(int value);

private:
	QLabel *pZoomIcon;
	QWidget *pMidItm;
	QPushButton *pPreButn;
	QLabel *ppageShow;
	QPushButton *pNextButn;
	QSlider *pSlider;
	QPushButton *pZoomOutBtn;
	QPushButton *pZoomInBtn;

	PhotoMaker *_pMainFrame;
};

#endif // PMPAPERPAGECTRLPANE_H
