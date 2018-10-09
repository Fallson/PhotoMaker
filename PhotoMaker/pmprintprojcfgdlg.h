#ifndef PMPRINTPROJCFGDLG_H
#define PMPRINTPROJCFGDLG_H

#include <QDialog>
#include "ui_pmprintprojcfgdlg.h"
#include <QStandardItemModel>
#include "PhotoPrintPrjModel.h"
#include "pmpaperpage.h"
#include "pmphotomakerdoc.h"

typedef struct _SelItm
{
	QString name;
	QString value;
}SEL_ITM, *PSEL_ITM;

class PmPrintProjCfgDlg : public QDialog
{
	Q_OBJECT

public:
	PmPrintProjCfgDlg(QWidget *parent = 0);
	~PmPrintProjCfgDlg();

public:
	bool getProjProps(PROJ_PROPS &projprops){ projprops = _ppmodel.getPrjProps(); return true;}

public:
	void setShowPic(const QImage &showpic);
	void setTitle(const QString &title);

	void clearSelectItm();
	void addSelectItm(PSEL_ITM selItm);

public slots:
	void selectionChange(const QModelIndex & slectedIndex);
	void doubleclickselection(const QModelIndex & slectedIndex);
	void onBack();
	void onNext();
	void onCancel();
	void onOpen();
	void onOk();

private:
	void _updateUI();
	void _updateList();

private:
	Ui::PmPrintProjCfgDlg ui;
	QStandardItemModel *_model;
	PhotoPrintPrjModel _ppmodel;
};

#endif // PMPRINTPROJCFGDLG_H
