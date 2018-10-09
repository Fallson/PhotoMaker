#include "pmdirbrowsetree.h"
#include <qdir.h>

#if 0
#ifdef WIN32
#include <Windows.h>
#include <ShlObj.h>
#endif
#endif
#include <QDesktopServices>

extern QString  gbires ;

void PmDirBrowseTree::reTranslate()
{
	if ( _desktopitm )
	{
		_desktopitm->setText( tr("Desktop"));
	}
	if ( _compitm )
	{
		_compitm->setText( tr("My Computer"));
	}
}
PmDirBrowseTree::PmDirBrowseTree(QWidget *parent1)
	: QTreeView(parent1), _desktopitm(NULL), _compitm(NULL)
{
	QPalette palette;
	//palette.setBrush(tree->backgroundRole(), QBrush(QColor(qRgb(46,63,93))));
	palette.setBrush(backgroundRole(), QBrush(QColor(qRgb(255,255,255))));
	setPalette(palette);

	_model = new QStandardItemModel(4, 1, this);

	QDir dir("/");


	setExpandsOnDoubleClick(true);
	

	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	dir.setSorting(QDir::Name );


	QString desktoppath = QDesktopServices::storageLocation(QDesktopServices::DesktopLocation);

	QStandardItem *itm1 = new QStandardItem(QIcon("Resources\\images\\desktop.png"), tr("Desktop"));
	_desktopitm = itm1;
	itm1->setEditable(false);
	//itm1->setCheckable(true);
	itm1->setData(QVariant(desktoppath),Qt::UserRole);
	_model->setItem(0,0, itm1);

	QStandardItem *itm2 = new QStandardItem(QIcon( gbires  + "computer.png"), tr("My Computer"));
	_compitm = itm2;
	itm2->setEditable(false);
	//itm2->setCheckable(true);
	_model->setItem(1, 0, itm2);


	QFileInfoList list = dir.drives();
	for (int i = 0; i < list.size(); ++i) 
	{
		QFileInfo fileInfo = list.at(i);
		QString check = fileInfo.absoluteFilePath();
		QString drive = check.left(check.length()-1);
		QStandardItem *itmdrive = new QStandardItem(QIcon(gbires + "drive.png"),drive);
		itmdrive->setData(check);
		itmdrive->setEditable(false);
		//itmdrive->setCheckable(true);
		itm2->appendRow(itmdrive);
	}

    QString desktopdirpath = QString(tr("%1/Desktop")).arg(QDir::homePath());
	QDir desktopdir(desktopdirpath);
	desktopdir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
	desktopdir.setSorting(QDir::Name );

	list = desktopdir.entryInfoList();
	for (int subindex=0;subindex<list.size(); subindex++ )
	{
		QFileInfo fileInfo = list.at(subindex);
		QString check = fileInfo.absoluteFilePath();
		QString dirpath = check;
		if ( dirpath.at(dirpath.length()-1) == '/' )
		{
			dirpath = dirpath.left(dirpath.length()-1);
		}
		int lastslashpos = dirpath.lastIndexOf("\\");
		if ( lastslashpos == -1 )
		{
			lastslashpos = dirpath.lastIndexOf("/");
		}
		QString dirname;
		if ( lastslashpos > 0 & dirpath.length()-lastslashpos-1 >0 )
		{
			dirname = dirpath.right(dirpath.length()-lastslashpos-1);
		}
		else
		{
			dirname = dirpath;
		}
		if ( '/' == dirname.at(dirname.length()-1) )
		{
			dirname = dirname.left(dirname.length()-1);
		}
		QStandardItem *itmfloder = new QStandardItem(QIcon( gbires + "folder.png"),dirname);
		itmfloder->setData(check);
		itmfloder->setEditable(false);
		//itmfloder->setCheckable(true);
		_model->setItem(2+subindex,itmfloder);

		_insertChild(itmfloder);
		// insert child
		//child->appendRow(itmfloder);
	}
	/*
	QModelIndex parent;
	for(int i=0; i<3; i++ )
	{
		//
		parent = _model->index(0,0,parent);
		_model->insertRows(0, 1,parent);
		_model->insertColumns(0, 1, parent);
		QModelIndex index = _model->index(0, 0, parent);
		_model->setData(index, "this");
	}
	*/

	this->setModel(_model);

	QTreeView *pTreeView = this;
	connect(pTreeView, SIGNAL(collapsed(const QModelIndex &)), this, SLOT(tree_collapsed(const QModelIndex &)));
	connect(pTreeView, SIGNAL(expanded(const QModelIndex &)), this, SLOT(tree_expanded(const QModelIndex &)));

}

PmDirBrowseTree::~PmDirBrowseTree()
{

}


void PmDirBrowseTree::selectionChanged(const QItemSelection & selected, const QItemSelection & deselected)
{

}
void PmDirBrowseTree::currentChanged( const QModelIndex & current, const QModelIndex & previous )
{
	// update the current folders
	// notify parent selection changed
	QStandardItem *itm = _model->itemFromIndex(current);
	QVariant data = itm->data();

	this->_pNotifyer(this->_context,data.toString() );
}

void PmDirBrowseTree::_expendFolde(QStandardItem *modelitm, const QString &pathsufix)
{
	// first expend this layer
	QModelIndex index = _model->indexFromItem (modelitm);
	this->expand(index);

	if ( !pathsufix.length() )
	{
		return ;
	}

	QString nextdir;
	QString leftpath;
	int pos = pathsufix.indexOf("/");
	if ( pos == -1 )
	{
		nextdir = pathsufix;
		leftpath = "";
	}
	else
	{
		nextdir = pathsufix.left(pos);
		leftpath = pathsufix.right(pathsufix.length()-pos-1);
	}


	int count = modelitm->rowCount();
	int i;
	QStandardItem * childitm = NULL;
	for ( i=0; i<count; i++ )
	{
		childitm = modelitm->child(i,0);
		QVariant data = childitm->data();
		QString folderpath = data.toString();
		QString dir;
		int dirpos = folderpath.lastIndexOf("/");
		dir = folderpath.right(folderpath.length()-dirpos-1);
		if ( dir == nextdir )
		{
			break;
		}
	}

	//
	if ( i < count )
	{
		this->_expendFolde(childitm, leftpath);
	}
}

void PmDirBrowseTree::selectCurFolder(const QString &path)
{
	//
	// first select my computers 
	//
	// item 2 is computer
	QModelIndex index = _model->index(1, 0);
	this->expand(index);

	int pos = path.indexOf(":/");
	QString drive = path.left(pos+2);
	QString filepath = path.right(path.length()-pos-2);

	QStandardItem *compitm = _model->itemFromIndex(index);
	// enume all children
	int count = compitm->rowCount();
	for ( int i=0; i<count; i++ )
	{
		QStandardItem * itm = compitm->child(i,0);
		QVariant data = itm->data();
		if ( data.toString() == drive )
		{
			// break;
			_expendFolde(itm, filepath);
			break;
		}
	}
}

void PmDirBrowseTree::tree_expanded(const QModelIndex &index)
{
	int i = 0;
	// expend next layer dir
	QVariant data = index.data();
	//index.
	QStandardItem *itm = _model->itemFromIndex(index);
	if ( itm->hasChildren() )
	{
		//
		int childrencnt = itm->rowCount();
		for( int i=0; i<childrencnt; i++ )
		{
			QStandardItem *child = itm->child(i);
			_insertChild(child);
		}
	}

}

void PmDirBrowseTree::tree_collapsed(const QModelIndex &index)
{
	int i = 0;

	// do nothing
}


void PmDirBrowseTree::_insertChild(QStandardItem *pFolderItm)
{
	if ( !pFolderItm )
	{
		return ;
	}

	// check if this child has been expended
	QVariant expended = pFolderItm->data( Qt::UserRole + 2);
	if ( expended.toUInt() == 1 )
	{
		return;
	}
	QVariant data = pFolderItm->data();

	QDir dir(data.toString());
	dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
	dir.setSorting(QDir::Name);

	QFileInfoList list = dir.entryInfoList();
	for (int subindex = 0; subindex < list.size(); ++subindex) 
	{
		QFileInfo fileInfo = list.at(subindex);
		QString check = fileInfo.absoluteFilePath();

		QString dirpath = check;
		if ( dirpath.at(dirpath.length()-1) == '/' )
		{
			dirpath = dirpath.left(dirpath.length()-1);
		}
		int lastslashpos = dirpath.lastIndexOf("\\");
		if ( lastslashpos == -1 )
		{
			lastslashpos = dirpath.lastIndexOf("/");
		}
		QString dirname;
		if ( lastslashpos > 0 & dirpath.length()-lastslashpos-1 >0 )
		{
			dirname = dirpath.right(dirpath.length()-lastslashpos-1);
		}
		else
		{
			dirname = dirpath;
		}
		if ( '/' == dirname.at(dirname.length()-1) )
		{
			dirname = dirname.left(dirname.length()-1);
		}


		QStandardItem *itmfloder = new QStandardItem(QIcon(gbires + "folder.png"),dirname);
		itmfloder->setData(check);
		itmfloder->setEditable(false);
		//itmfloder->setCheckable(true);
		pFolderItm->appendRow(itmfloder);
	}
	pFolderItm->setData(QVariant(1), Qt::UserRole + 2);
}

void PmDirBrowseTree::subscribeSelectionChanged(PATH_SEL_CHANGE_NF func, void *context)
{
	_pNotifyer = func;
	_context = context;

}

