#include "pmbottomctrlpane.h"
#include "PhotoEditView.h"
#include "photoEditViewItem.h"


MyTabeWidget::MyTabeWidget(QWidget *parent):QTabWidget(parent)
{
}



void MyTabeWidget::resizeEvent ( QResizeEvent * e )
{
	QTabWidget::resizeEvent(e);
	QRectF rect = this->geometry();
	int i=0;
}


void PmBottomCtrlPane::reTranslate()
{
	pTabContainer->setTabText(0, tr("Page Preview"));
}


PmBottomCtrlPane::PmBottomCtrlPane(PhotoMaker *pMainFrame, QWidget *parent)
	: QWidget(parent), _pMainFrame(pMainFrame), 
	pPhotoEdit(NULL), pColorEdit(NULL), pCalendarEdit(NULL), pTextEdit(NULL)
{

	pTabContainer = new MyTabeWidget(this);
	//pTabContainer->setTabShape(QTabWidget::Triangular);

	QPalette palette;
	//palette.setBrush(tree->backgroundRole(), QBrush(QColor(qRgb(46,63,93))));
	palette.setBrush(pTabContainer->backgroundRole(), QBrush(QColor(qRgb(255,255,255))));

	pTabContainer->setPalette(palette);

	pagepreview = new PrintPagesPreviewView(_pMainFrame, pTabContainer);


	//pTabContainer->setIconSize(QSize(80,80));
	pTabContainer->addTab(pagepreview,QIcon("Resources\\images\\PagePreviewIcon.png"),tr("Page Preview"));

}

PmBottomCtrlPane::~PmBottomCtrlPane()
{

}


void PmBottomCtrlPane::resizeEvent(QResizeEvent *event)
{
	QRect rect = this->geometry();

	pTabContainer->resize(rect.width(), rect.height());

}

bool PmBottomCtrlPane::updateEditPaneInfo()
{
	if ( pTextEdit )
	{
		// update text box info
		PmPageItm *pageitm = NULL;
		PmTextItm *txtitm = NULL;
		this->_pMainFrame->getEditView()->getSelection(pageitm, txtitm);
		if ( !txtitm )
		{
			pTextEdit->setContent("");
			return false;
		}
		QString cnt;
		txtitm->getContent(cnt);
		pTextEdit->setContent(cnt);
	}

	if ( pPhotoEdit )
	{
		// update photo edit info
		PmPageItm *pageitm = NULL;
		PmTextItm *txtitm = NULL;
		this->_pMainFrame->getEditView()->getSelection(pageitm, txtitm);
		if ( !pageitm )
		{
			return false;
		}

		qreal ratio = 0;
		pageitm->getZoom(ratio);
		pPhotoEdit->setScaleRatio(ratio);
		PhotoViewItm *photoviewitm = (PhotoViewItm *)pageitm->getPageViewItm();
		int dpi = 0;
		photoviewitm->getDpi(dpi);
		pPhotoEdit->setDpi(dpi);
	}

	if ( pColorEdit )
	{
		// update color edit info
		PmPageItm *pageitm = NULL;
		PmTextItm *txtitm = NULL;
		this->_pMainFrame->getEditView()->getSelection(pageitm, txtitm);
		if ( !pageitm )
		{
			return false;
		}
		QColor bgcolor;
		pageitm->getBgColor(bgcolor);
		pColorEdit->setColor(bgcolor);
	}
	if ( pCalendarEdit )
	{
		//pCalendarEdit;

	}

	return true;
}

bool PmBottomCtrlPane::showEditPane(EDIT_PANE_TYPE editpane, const QString &cnt)
{
	if ( pTabContainer->count()> 1 )
	{
		pTabContainer->removeTab(1);
	}
	if ( pPhotoEdit )
	{
		delete pPhotoEdit;
		pPhotoEdit = NULL;
	}
	if ( pColorEdit )
	{
		delete pColorEdit;
		pColorEdit = NULL;
	}
	
	if ( pCalendarEdit )
	{
		delete pCalendarEdit;
		pCalendarEdit = NULL;
	}
	if ( pTextEdit )
	{
		delete pTextEdit;
		pTextEdit = NULL;
	}




	
	switch(editpane)
	{
	case TEXT_EDIT:
		{
			//pTabContainer->addTab(pPhotoEdit,QIcon("Resources\\images\\PicEditIcon.png"), "Photo Edit");
			//pTabContainer->addTab(pCalendarEdit,QIcon("Resources\\images\\PicEditIcon.png"), "Calendar Edit");
			pTextEdit = new TextEdit(_pMainFrame, pTabContainer);
			pTabContainer->addTab(pTextEdit,QIcon("Resources\\images\\PicEditIcon.png"), tr("text Edit"));
			pTabContainer->setCurrentIndex(1);
			pTextEdit->setContent(cnt);
		}
		break;
	case PHOTO_EDIT:
		{
			// get photo properties
			PmPageItm *pageitm = NULL;
			PmTextItm *txtitm = NULL;
			this->_pMainFrame->getEditView()->getSelection(pageitm, txtitm);
			if ( !pageitm )
			{
				break;
			}
			QColor bgcolor;
			QString imgpath;
			pageitm->getContent(imgpath);
			pageitm->getBgColor(bgcolor);
			if ( imgpath.length() || bgcolor == Qt::white)
			{
				pPhotoEdit = new PmPicEdit(_pMainFrame, pTabContainer);
				pTabContainer->addTab(pPhotoEdit,QIcon("Resources\\images\\PicEditIcon.png"), tr("Photo Edit"));
				pTabContainer->setCurrentIndex(1);

				qreal ratio = 0;
				pageitm->getZoom(ratio);
				pPhotoEdit->setScaleRatio(ratio);
				PhotoViewItm *photoviewitm = (PhotoViewItm *)pageitm->getPageViewItm();
				int dpi = 0;
				photoviewitm->getDpi(dpi);
				pPhotoEdit->setDpi(dpi);

			}
			else
			{
				pColorEdit = new PmColorEdit(_pMainFrame, pTabContainer);
				pTabContainer->addTab(pColorEdit,QIcon("Resources\\images\\PicColorIcon.png"), tr("Color Edit"));
				pTabContainer->setCurrentIndex(1);

				pColorEdit->setColor(bgcolor);
			}

		}
		break;
	case CALENDAR_EDIT:
		{
			pCalendarEdit = new PmCalendarEdit(_pMainFrame, pTabContainer);
			pTabContainer->addTab(pCalendarEdit,QIcon("Resources\\images\\PicEditIcon.png"), tr("Calendar Edit"));
			pTabContainer->setCurrentIndex(1);

			// get photo properties
		}
		break;
	case HIDE_EDIT:
	default:
		pTabContainer->setCurrentIndex(0);
		;
	}

	return true;
}
