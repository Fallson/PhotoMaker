#ifndef PMBOTTOMCTRLPANE_H
#define PMBOTTOMCTRLPANE_H

#include <QWidget>
#include <QtGui/QMainWindow>
#include "ui_photomaker.h"
#include <QtGui/qtoolbar.h>
#include <QtGui/qlabel.h>
#include <QtGui/qtreeview.h>
#include <QtGui/qsplitter.h>
#include "pmpicedit.h"
#include "pmcalendaredit.h"
#include "textedit.h"
#include "PmColorEdit.h"
//#include "photomaker.h"



class PhotoMaker;
class PrintPagesPreviewView;


class MyTabeWidget: public QTabWidget
{
	Q_OBJECT
public:
	MyTabeWidget(QWidget *parent);
protected:
	virtual void resizeEvent ( QResizeEvent * e );
};

class PmBottomCtrlPane : public QWidget
{
	Q_OBJECT
public:
	typedef enum{TEXT_EDIT, PHOTO_EDIT, CALENDAR_EDIT, HIDE_EDIT}EDIT_PANE_TYPE;

public:
	PmBottomCtrlPane(PhotoMaker *pMainFrame, QWidget *parent);
	~PmBottomCtrlPane();

public:
	PrintPagesPreviewView *getPreviewView(){return pagepreview;}
	bool showEditPane(EDIT_PANE_TYPE editpane, const QString &cnt = QString(""));
	bool updateEditPaneInfo();

	void reTranslate();
protected:
    virtual void resizeEvent(QResizeEvent *);


private:
	PrintPagesPreviewView *pagepreview;
	PmPicEdit *pPhotoEdit;
	PmColorEdit *pColorEdit;
	PmCalendarEdit *pCalendarEdit;
	TextEdit *pTextEdit;
	MyTabeWidget *pTabContainer;

	PhotoMaker *_pMainFrame;

};

#endif // PMBOTTOMCTRLPANE_H
