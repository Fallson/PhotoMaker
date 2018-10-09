#include "pmcentralpane.h"
#include "pmpaperpagectrlpane.h"

PmCentralPane::PmCentralPane(PhotoMaker *pMainFrame, QWidget *parent)
	: QWidget(parent), _pMainFrame(pMainFrame)
{
	pPageCtrlPane = new PmPaperPageCtrlPane(_pMainFrame, this);

	QRect rect = this->geometry();
	pPageCtrlPane->setGeometry(0, 0, rect.width(), 50);

	_pPhotoEditView = new PhotoEditView(_pMainFrame, this);
	_pPhotoEditView->setGeometry(0,51, rect.width(), rect.height());
}

PmCentralPane::~PmCentralPane()
{

}



void PmCentralPane::resizeEvent(QResizeEvent *)
{
	QRect rect = this->geometry();
	pPageCtrlPane->setGeometry(0, 0, rect.width(), 50);
	_pPhotoEditView->setGeometry(0,51, rect.width(), rect.height()-51);


}

void PmCentralPane::showPageInfo(const QString &pageInfo)
{
	if ( pPageCtrlPane )
	{
		pPageCtrlPane->showPageInfo(pageInfo);
	}
}
