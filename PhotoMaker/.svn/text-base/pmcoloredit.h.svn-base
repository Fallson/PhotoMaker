#ifndef PMCOLOREDIT_H
#define PMCOLOREDIT_H

#include <QWidget>
#include "ui_pmcoloredit.h"
//#include "photomaker.h"
#include <QColor>

class PhotoMaker;
class PmColorEdit : public QWidget
{
	Q_OBJECT

public:
	PmColorEdit(PhotoMaker *pMainFrame, QWidget *parent = 0);
	~PmColorEdit();

public:
	void setColor(const QColor &color);
	void getColor(QColor &color);

protected slots:
	void onChgColor();

private:
	Ui::PmColorEdit ui;
	PhotoMaker *_pMainFrame;


	QColor _color;
};

#endif // PMCOLOREDIT_H
