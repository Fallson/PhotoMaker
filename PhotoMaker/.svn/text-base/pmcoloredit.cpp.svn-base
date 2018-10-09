#include "pmcoloredit.h"
#include <QColorDialog>
#include "photomaker.h"
#include <QPainter>

PmColorEdit::PmColorEdit(PhotoMaker *pMainFrame, QWidget *parent)
	: QWidget(parent),_pMainFrame(pMainFrame)
{
	ui.setupUi(this);

	connect(ui.btnChgColor, SIGNAL(clicked()), SLOT(onChgColor()));
}

PmColorEdit::~PmColorEdit()
{

}

void PmColorEdit::onChgColor()
{
	QColorDialog colordlg;
	colordlg.setCurrentColor(_color);

	if ( QDialog::Accepted == colordlg.exec() )
	{
		_color = colordlg.currentColor();
		this->setColor(_color);
		this->_pMainFrame->OnSetBgColor(_color);
	}

}


void PmColorEdit::setColor(const QColor &color)
{
	_color = color;
	int red = color.red();
	int green = color.green();
	int blue = color.blue();

	QString value;
	value = QString("%1").arg(red);
	ui.lbRval->setText(value);
	value = QString("%1").arg(green);
	ui.lbGval->setText(value);
	value = QString("%1").arg(blue);
	ui.lbBval->setText(value);

	QPixmap pixmap(200,200);
    QPainter colorpainter(&pixmap);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    pen.setBrush(_color);

	colorpainter.setPen(pen);
    colorpainter.setBrush(_color);
    colorpainter.drawRect(0, 0,200, 200);
	colorpainter.drawText(QRectF(0,0, 100,50), "hello");
	QString txt;

	ui.lbColorShow->setPixmap(pixmap);
}

void PmColorEdit::getColor(QColor &color)
{
	color = _color;
}

