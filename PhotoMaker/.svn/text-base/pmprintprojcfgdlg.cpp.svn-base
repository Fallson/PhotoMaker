#include "pmprintprojcfgdlg.h"
#include <QStringListModel>
#include "photomaker.h"
#include <QItemDelegate>

extern QString gbires;

class ItemDelegate : public QItemDelegate
{
public:
  ItemDelegate()
  {}
  QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
  {
    return QSize(188,30);
  }
};

class MyModel: public QStandardItemModel
{
public:
	MyModel(QObject *parent = 0);
public:
	QVariant data(const QModelIndex &index, int role) const;

};

MyModel::MyModel(QObject *parent):QStandardItemModel(parent)
{
}

 QVariant MyModel::data(const QModelIndex &index, int role) const
 {
     if (  role != Qt::SizeHintRole)
	 {
		 return QStandardItemModel::data(index, role);
	 }
	 QVariant var;
	 var.setValue(QSize(180,30)); 
     return var;
 }

PmPrintProjCfgDlg::PmPrintProjCfgDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//ui.itemSelectList->setGridSize(QSize(188, 30));
	ui.itemSelectList->show();

	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );
    setWindowIcon(QIcon("Resources\\images\\AppIcon.ico"));
	
	/*
#ifdef Q_WS_WIN
	HWND hwnd = winId();
	LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
	style &= ~WS_SYSMENU;
	SetWindowLongPtr(hwnd, GWL_STYLE, style);
#endif
	*/

	//setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint &  ~Qt::WindowSystemMenuHint);
	//setWindowIcon(QIcon());

	QPalette palette = this->palette();   

	QString lstviewstyle;
	lstviewstyle = "QListView::item{background-image:url(" + gbires + "wizard_itm_unsel_background.png)}"
		"QListView::item:selected{background-image:url(" +  gbires + "wizard_itm_sel_background.png)}"
		"QListView{background-color:" +  palette.background().color().name() + "}";
	ui.itemSelectList->setLayoutDirection(Qt::RightToLeft);
	ui.itemSelectList->setStyleSheet(lstviewstyle);
	//ui.itemSelectList->seta
	ui.titleLabel->setStyleSheet("background-image:url(" + gbires + "TitleBarBackGround.png)");
	
	//QString colorvalue = QString("%1").arg(palette.background().color().name());
	//palette.setBrush(QPalette::NoRole, QBrush(Qt::red));
	//ui.itemSelectList->setPalette(palette);
	//ui.itemSelectList->setAutoFillBackground(true);

	/*
	QPalette palette;
	palette.setBrush(ui.titleLabel->backgroundRole(), QBrush(QColor(qRgb(255,255,255))));
	ui.titleLabel->setPalette(palette);
	*/

	//doubleClicked ( const QModelIndex & index )
	connect(ui.itemSelectList, SIGNAL(doubleClicked ( const QModelIndex &)), this, SLOT(doubleclickselection(const QModelIndex &)));
	connect(ui.itemSelectList, SIGNAL(clicked ( const QModelIndex &)), this, SLOT(selectionChange(const QModelIndex &)));
	connect(ui.backBtn, SIGNAL(clicked()), this, SLOT(onBack()));
	connect(ui.nextBtn, SIGNAL(clicked( )), this, SLOT(onNext()));
	//connect(ui.cancelBtn, SIGNAL(clicked (bool )),this,  SLOT(onCancel()));
	connect(ui.openBtn, SIGNAL(clicked ( )), this, SLOT(onOpen()));
	connect(ui.okBtn, SIGNAL(clicked ( )), this, SLOT(onOk()));


	PpPrjWizardPage *pCurrentPage = _ppmodel.Init();
	if ( !pCurrentPage )
	{
		return;
	}
	if ( pCurrentPage->HasNextPage() )
	{
		ui.nextBtn->show();
		ui.okBtn->hide();
	}
	else
	{
		ui.nextBtn->hide();
		ui.okBtn->show();
	}

	ui.backBtn->setEnabled( pCurrentPage->HasPrePage());

	QString title;
	pCurrentPage->getTitle(title);


	this->setTitle(title);

	PRJ_DIR_ITM diritm;
	pCurrentPage->getSelectedItm(diritm);
	this->setShowPic(QImage(diritm.showPicPath));




	//Setting the icon size 
	ui.itemSelectList->setIconSize(QSize(200,50)); 

	//_model = new QStandardItemModel(this); 
	_model = new MyModel(this);

	QList<PRJ_DIR_ITM> diritms;
	pCurrentPage->getDirItm(diritms);

	int index = 0;
	QList<PRJ_DIR_ITM>::iterator it;
	for(it=diritms.begin(),index=0; it!=diritms.end(); it++ ,index++)
	{
		//First item 
		PRJ_DIR_ITM itm = *it;
		QStandardItem* item1 = new QStandardItem(QIcon(itm.iconPath),itm.name); 

		item1->setData(index);
		item1->setEditable(false);

		//Appending the items into model 
		_model->appendRow(item1); 
		//Setting the model 
	}
	ui.itemSelectList->setModel(_model);

	//ItemDelegate *delg = new ItemDelegate();
	//ui.itemSelectList->setItemDelegate(delg);

	QAbstractItemView::SelectionMode sm = ui.itemSelectList->selectionMode();
	ui.itemSelectList->selectionModel()->select(_model->index(0,0),QItemSelectionModel::Select);
	ui.itemSelectList->setFocus();
	
}

PmPrintProjCfgDlg::~PmPrintProjCfgDlg()
{

}

void PmPrintProjCfgDlg::onBack()
{
	PpPrjWizardPage *pCurrentPage = _ppmodel.goPre();
	if ( !pCurrentPage )
	{
		return;
	}
	this->_updateUI();
	this->_updateList();

}

void PmPrintProjCfgDlg::onNext()
{
	PpPrjWizardPage *pCurrentPage = _ppmodel.goNext();
	if ( !pCurrentPage )
	{
		return;
	}

	this->_updateUI();
	this->_updateList();
}

void PmPrintProjCfgDlg::onCancel()
{
}

void PmPrintProjCfgDlg::onOk()
{
	_ppmodel.onOk();
	accept();
	emit close();
}


void PmPrintProjCfgDlg::onOpen()
{
	//emit close();
	PhotoMaker *pMainFrame = (PhotoMaker*)this->parent();
	pMainFrame->OnOpenProj();
	reject();
}

void PmPrintProjCfgDlg::setShowPic(const QImage &showpic)
{
	ui.showPicLable->setPixmap(QPixmap(QPixmap::fromImage(showpic)));
}
void PmPrintProjCfgDlg::setTitle(const QString &title)
{
	//ui.titleLabel->setPixmap(QPixmap(QPixmap::fromImage(titlepic)));
	QString titletxt;
	titletxt += "<font color=white><h2>";
	titletxt += title;
	titletxt += "</i></h2></font>";
	ui.titleLabel->setText(titletxt);
}

void PmPrintProjCfgDlg::clearSelectItm()
{
}

void PmPrintProjCfgDlg::addSelectItm(PSEL_ITM selItm)
{
}


void PmPrintProjCfgDlg::_updateUI()
{
	PpPrjWizardPage * pCurPage = this->_ppmodel.getCurPage();
	if ( !pCurPage )
	{
		return ;
	}
	PRJ_DIR_ITM diritm;
	pCurPage->getSelectedItm(diritm);
	if ( diritm.showPicPath.length() )
	{
		this->setShowPic(QImage(diritm.showPicPath));
	}

	// update buttons
	if ( pCurPage->HasNextPage() )
	{
		ui.nextBtn->show();
		ui.okBtn->hide();
	}
	else
	{
		ui.nextBtn->hide();
		ui.okBtn->show();
	}

	ui.backBtn->setEnabled( pCurPage->HasPrePage());
}

void PmPrintProjCfgDlg::_updateList()
{
	PpPrjWizardPage * pCurPage = this->_ppmodel.getCurPage();
	if ( !pCurPage )
	{
		return ;
	}

	_model->clear();

	QList<PRJ_DIR_ITM> diritms;
	pCurPage->getDirItm(diritms);

	int index = 0;
	QList<PRJ_DIR_ITM>::iterator it;
	for(it=diritms.begin(),index=0; it!=diritms.end(); it++ ,index++)
	{
		//First item 
		PRJ_DIR_ITM itm = *it;
		QStandardItem* item1 = new QStandardItem(QIcon(itm.iconPath),itm.name); 

		item1->setData(index);
		item1->setEditable(false);

		//Appending the items into model 
		_model->appendRow(item1); 
		//Setting the model 
	}
	ui.itemSelectList->setModel(_model);

	PRJ_DIR_ITM diritm;
	pCurPage->getSelectedItm(diritm);
	QAbstractItemView::SelectionMode sm = ui.itemSelectList->selectionMode();
	ui.itemSelectList->selectionModel()->select(_model->index(diritm.index,0),QItemSelectionModel::Select);
	ui.itemSelectList->setFocus();
}

void PmPrintProjCfgDlg::selectionChange(const QModelIndex & slectedIndex)
{
	//
	QStandardItem *itm = _model->itemFromIndex(slectedIndex);
	QVariant data = itm->data();
	int index = data.toInt();

	PpPrjWizardPage * pCurPage = this->_ppmodel.getCurPage();
	if ( !pCurPage )
	{
		return ;
	}
	pCurPage->setSelectedIndex(index);

	_updateUI();
}

void PmPrintProjCfgDlg::doubleclickselection(const QModelIndex & slectedIndex)
{
	selectionChange(slectedIndex);
	PpPrjWizardPage * pCurPage = this->_ppmodel.getCurPage();
	if (  !pCurPage )
	{
		return ;
	}
	if ( pCurPage->getNextPage() )
	{
		this->onNext();
	}
	else
	{
		this->onOk();
	}
}
