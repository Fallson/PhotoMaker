#ifndef PMCENTRALPANE_H
#define PMCENTRALPANE_H

#include <QWidget>
#include <QtGui/QMainWindow>
#include "ui_photomaker.h"
#include <QtGui/qtoolbar.h>
#include <QtGui/qlabel.h>
#include <QtGui/qtreeview.h>
#include <QtGui/qsplitter.h>
#include <QtGui/qtextedit.h>
#include "pmpaperpagectrlpane.h"
#include "PhotoEditView.h"
#include "photomaker.h"


class PmCentralPane : public QWidget
{
	Q_OBJECT

public:
	PmCentralPane(PhotoMaker *pMainFrame, QWidget *parent);
	~PmCentralPane();

public:
	PhotoEditView *getEditView(){return _pPhotoEditView;}
	void showPageInfo(const QString &pageInfo);

protected:
    virtual void resizeEvent(QResizeEvent *);

private:
	PmPaperPageCtrlPane *pPageCtrlPane;
	PhotoEditView  *_pPhotoEditView;
	PhotoMaker *_pMainFrame;
};

#endif // PMCENTRALPANE_H
