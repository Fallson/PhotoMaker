#ifndef PMDIRBROWSETREE_H
#define PMDIRBROWSETREE_H

#include <QTreeView>
#include <QtGui/qstandarditemmodel.h>

typedef void (* PATH_SEL_CHANGE_NF)( void *context, const QString &path );

class PmDirBrowseTree : public QTreeView
{
	Q_OBJECT

public:
	PmDirBrowseTree(QWidget *parent);
	~PmDirBrowseTree();

public:
	void subscribeSelectionChanged(PATH_SEL_CHANGE_NF func, void *context);
	void selectCurFolder(const QString &path);

	void reTranslate();
protected:
	virtual void selectionChanged(const QItemSelection & selected, const QItemSelection & deselected);
	virtual void currentChanged ( const QModelIndex & current, const QModelIndex & previous );

public slots:
    void tree_expanded(const QModelIndex &index);
    void tree_collapsed(const QModelIndex &index);

private:
	void _insertChild(QStandardItem *pFolderItm);
	void _expendFolde(QStandardItem *modelitm, const QString &pathsufix);

private:
	QStandardItemModel *_model;
	QStandardItem *_desktopitm;
	QStandardItem *_compitm;

private:
	PATH_SEL_CHANGE_NF _pNotifyer;
	void * _context;
};

#endif // PMDIRBROWSETREE_H
