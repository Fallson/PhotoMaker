#include "calweekdaysheet.h"
#include "qtcolorpicker.h"
#include "qtcolorcombobox.h"

extern QString gbires;

CalWeekDaySheet::CalWeekDaySheet(const WEEKDAY_PROPS &wdprops,QWidget *parent)
	: QWidget(parent), _wdprops(wdprops)
{
	ui.setupUi(this);

	QColor nocolor = Qt::transparent;
	nocolor.setAlpha(0);

	QtColorComboBox *colorpicker  = NULL;
	colorpicker =  dynamic_cast<QtColorComboBox*>( ui.cbcellcolor);
	 
	colorpicker->insertColor(0, nocolor, "No Color");
	colorpicker->setStandardColors();
	colorpicker->setColorDialogEnabled(true);

	colorpicker =  dynamic_cast<QtColorComboBox*>( ui.cbfontcolor);
	colorpicker->setColorDialogEnabled(true);
	colorpicker->insertColor(0, nocolor, "No Color");
	colorpicker->setStandardColors();


	colorpicker =  dynamic_cast<QtColorComboBox*>( ui.cbrowcolor);
	colorpicker->setColorDialogEnabled(true);
	colorpicker->insertColor(0, nocolor, "No Color");
	colorpicker->setStandardColors();



	ui.btnAlignLeft->setCheckable(true);
	ui.btnAlignHCenter->setCheckable(true);
	ui.btnAlignRight->setCheckable(true);
	ui.btnAlignTop->setCheckable(true);
	ui.btnAlignBottom->setCheckable(true);
	ui.btnAlignVCenter->setCheckable(true);
	ui.btnBold->setCheckable(true);
	ui.btnItalic->setCheckable(true);
	ui.btnUnderLine->setCheckable(true);
	ui.fontheightIncell->setValidator(new QIntValidator(1, 100, this));

	ui.btnAlignLeft->setIcon(QIcon(gbires + "textleft.png"));
	ui.btnAlignHCenter->setIcon(QIcon(gbires + "textcenter.png"));
	ui.btnAlignRight->setIcon(QIcon(gbires + "textright.png"));
	ui.btnAlignLeft->setChecked(true);

	ui.btnAlignTop->setIcon(QIcon(gbires + "texttop.png"));
	ui.btnAlignVCenter->setIcon(QIcon(gbires + "textvcenter.png"));
	ui.btnAlignBottom->setIcon(QIcon(gbires + "textbottom.png"));
	ui.btnAlignTop->setChecked(true);

	ui.btnBold->setIcon(QIcon(gbires + "textbold.png"));
	ui.btnItalic->setIcon(QIcon(gbires + "textitalic.png"));
	ui.btnUnderLine->setIcon(QIcon(gbires + "textunder.png"));

	ui.btnAlignLeft->setText("");
	ui.btnAlignHCenter->setText("");
	ui.btnAlignRight->setText("");
	ui.btnAlignTop->setText("");
	ui.btnAlignVCenter->setText("");
	ui.btnAlignBottom->setText("");

	ui.btnBold->setText("");
	ui.btnItalic->setText("");
	ui.btnUnderLine->setText("");

	ui.wdSize->setValidator(new QIntValidator(1, 100, this));
	// limit space only accept number
	ui.lineleftSpace->setValidator(new QIntValidator(1, 100, this));
	ui.linetopSpace->setValidator(new QIntValidator(1, 100, this));
	ui.linerightSpace->setValidator(new QIntValidator(1, 100, this));
	ui.linebottomSpace->setValidator(new QIntValidator(1, 100, this));

	ui.lineleftPad->setValidator(new QIntValidator(1, 100, this));
	ui.linetopPad->setValidator(new QIntValidator(1, 100, this));
	ui.linerightPad->setValidator(new QIntValidator(1, 100, this));
	ui.linebottomPad->setValidator(new QIntValidator(1, 100, this));

	ui.cellLeftSpace->setValidator(new QIntValidator(1, 100, this));
	ui.celltopspace->setValidator(new QIntValidator(1, 100, this));
	ui.cellrightspace->setValidator(new QIntValidator(1, 100, this));
	ui.cellbottomspace->setValidator(new QIntValidator(1, 100, this));

	ui.cellleftpad->setValidator(new QIntValidator(1, 100, this));
	ui.celltoppad->setValidator(new QIntValidator(1, 100, this));
	ui.cellrightpad->setValidator(new QIntValidator(1, 100, this));
	ui.cellbottompad->setValidator(new QIntValidator(1, 100, this));


	_init();

}

CalWeekDaySheet::~CalWeekDaySheet()
{

}

void CalWeekDaySheet::_setupUI()
{
 
}



void CalWeekDaySheet::_init()
{
	_initFont();
	_initColor();
	_initSpace();

	ui.wdSize->setText(QString("%1").arg(_wdprops.regionsize));
	ui.cbShowWd->setChecked(this->_wdprops.showwds);
}

void CalWeekDaySheet::_initFont()
{
	ui.cbFont->setCurrentFont(QFont(this->_wdprops.fontcfg.name));
	QtColorComboBox *colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbfontcolor);
	if ( colorpicker )
	{
		if (_wdprops.fontcfg.color.alpha() == 0 )
		{
			QColor nocolor = Qt::transparent;
			nocolor.setAlpha(0);
			colorpicker->setCurrentColor(nocolor);
		}
		else
		{
			colorpicker->setCurrentColor(_wdprops.fontcfg.color);
		}
	}
	if ( _wdprops.fontcfg.bold )
	{
		ui.btnBold->setChecked(true);
	}
	else
	{
		ui.btnBold->setChecked(false);
	}
	if ( _wdprops.fontcfg.iatic )
	{
		ui.btnItalic->setChecked(true);
	}
	else
	{
		ui.btnItalic->setChecked(false);
	}
	if ( _wdprops.fontcfg.underLine )
	{
		ui.btnUnderLine->setChecked(true);
	}
	else
	{
		ui.btnUnderLine->setChecked(false);
	}
	if ( _wdprops.fontcfg.align & Qt::AlignLeft)
	{
		ui.btnAlignLeft->setChecked(true);
	}
	else
	{
		ui.btnAlignLeft->setChecked(false);
	}
	if ( _wdprops.fontcfg.align & Qt::AlignHCenter)
	{
		ui.btnAlignHCenter->setChecked(true);
	}
	else
	{
		ui.btnAlignHCenter->setChecked(false);
	}
	if ( _wdprops.fontcfg.align & Qt::AlignRight)
	{
		ui.btnAlignRight->setChecked(true);
	}
	else
	{
		ui.btnAlignRight->setChecked(false);
	}

	if ( _wdprops.fontcfg.align & Qt::AlignTop)
	{
		ui.btnAlignTop->setChecked(true);
	}
	else
	{
		ui.btnAlignTop->setChecked(false);
	}
	if ( _wdprops.fontcfg.align & Qt::AlignVCenter)
	{
		ui.btnAlignVCenter->setChecked(true);
	}
	else
	{
		ui.btnAlignVCenter->setChecked(false);
	}
	if ( _wdprops.fontcfg.align & Qt::AlignBottom)
	{
		ui.btnAlignBottom->setChecked(true);
	}
	else
	{
		ui.btnAlignBottom->setChecked(false);
	}
	ui.fontheightIncell->setText(QString("%1").arg(_wdprops.fontcfg.heightInCell*100));


	connect(ui.btnAlignLeft, SIGNAL(clicked()), SLOT(_leftBtnClicked()));
	connect(ui.btnAlignHCenter, SIGNAL(clicked()), SLOT(_hcenterBtnClicked()));
	connect(ui.btnAlignRight, SIGNAL(clicked()), SLOT(_rightBtnClicked()));
	connect(ui.btnAlignTop, SIGNAL(clicked()), SLOT(_topBtnClicked()));
	connect(ui.btnAlignVCenter, SIGNAL(clicked()), SLOT(_vcenterBtnClicked()));
	connect(ui.btnAlignBottom, SIGNAL(clicked()), SLOT(_bottomBtnClicked()));

}

void CalWeekDaySheet::_initSpace()
{
	qreal left, top, right, bottom;
	qreal leftpad, toppad, rightpad, bottompad;

	this->_wdprops.linespace;
	ui.lineleftSpace->setText(QString("%1").arg(_wdprops.linespace.left));
	ui.linetopSpace->setText(QString("%1").arg(_wdprops.linespace.top));
	ui.linerightSpace->setText(QString("%1").arg(_wdprops.linespace.right));
	ui.linebottomSpace->setText(QString("%1").arg(_wdprops.linespace.bottom));

	ui.lineleftPad->setText(QString("%1").arg(_wdprops.linespace.leftpad));
	ui.linetopPad->setText(QString("%1").arg(_wdprops.linespace.toppad));
	ui.linerightPad->setText(QString("%1").arg(_wdprops.linespace.rightpad));
	ui.linebottomPad->setText(QString("%1").arg(_wdprops.linespace.bottompad));

	ui.cellLeftSpace->setText(QString("%1").arg(_wdprops.cellspace.left));
	ui.celltopspace->setText(QString("%1").arg(_wdprops.cellspace.top));
	ui.cellrightspace->setText(QString("%1").arg(_wdprops.cellspace.right));
	ui.cellbottomspace->setText(QString("%1").arg(_wdprops.cellspace.bottom));

	ui.cellleftpad->setText(QString("%1").arg(_wdprops.cellspace.leftpad));
	ui.celltoppad->setText(QString("%1").arg(_wdprops.cellspace.toppad));
	ui.cellrightpad->setText(QString("%1").arg(_wdprops.cellspace.rightpad));
	ui.cellbottompad->setText(QString("%1").arg(_wdprops.cellspace.bottompad));

}

void CalWeekDaySheet::_initColor()
{
	QtColorComboBox *colorpicker = NULL;

	colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbrowcolor);
	if ( colorpicker )
	{
		if (_wdprops.rowcolor.alpha() == 0 )
		{
			QColor nocolor = Qt::transparent;
			nocolor.setAlpha(0);
			colorpicker->setCurrentColor(nocolor);
		}
		else
		{
			colorpicker->setCurrentColor(_wdprops.rowcolor);
		}
	}

	colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbcellcolor);
	if ( colorpicker )
	{
		if (_wdprops.cellcolor.alpha() == 0 )
		{
			QColor nocolor = Qt::transparent;
			nocolor.setAlpha(0);
			colorpicker->setCurrentColor(nocolor);
		}
		else
		{
			colorpicker->setCurrentColor(_wdprops.cellcolor);
		}
	}

	// init week days color later
	//QList<QColor> wdcolors;

}

void CalWeekDaySheet::_leftBtnClicked()
{
	//
	ui.btnAlignLeft->setChecked(true);
	ui.btnAlignHCenter->setChecked(false);
	ui.btnAlignRight->setChecked(false);

}
void CalWeekDaySheet::_hcenterBtnClicked()
{
	ui.btnAlignHCenter->setChecked(true);
	ui.btnAlignLeft->setChecked(false);
	ui.btnAlignRight->setChecked(false);
}

void CalWeekDaySheet::_rightBtnClicked()
{
	ui.btnAlignRight->setChecked(true);
	ui.btnAlignLeft->setChecked(false);
	ui.btnAlignHCenter->setChecked(false);
}
void CalWeekDaySheet::_topBtnClicked()
{
	ui.btnAlignTop->setChecked(true);
	ui.btnAlignBottom->setChecked(false);
	ui.btnAlignVCenter->setChecked(false);
}

void CalWeekDaySheet::_vcenterBtnClicked()
{
	ui.btnAlignVCenter->setChecked(true);
	ui.btnAlignBottom->setChecked(false);
	ui.btnAlignTop->setChecked(false);
}

void CalWeekDaySheet::_bottomBtnClicked()
{
	ui.btnAlignBottom->setChecked(true);
	ui.btnAlignVCenter->setChecked(false);
	ui.btnAlignTop->setChecked(false);
}



void CalWeekDaySheet::_getColor()
{
	QtColorComboBox *colorpicker = NULL;

	colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbrowcolor);
	if ( colorpicker )
	{
		_wdprops.rowcolor = colorpicker->currentColor();
	}

	colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbcellcolor);
	if ( colorpicker )
	{
		_wdprops.cellcolor = colorpicker->currentColor();
	}

	// init week days color later
	//QList<QColor> wdcolors;

}


void CalWeekDaySheet::_getSpace()
{
	_wdprops.linespace.left = ui.lineleftSpace->text().toFloat();
	_wdprops.linespace.top = ui.linetopSpace->text().toFloat();
	_wdprops.linespace.right = ui.linerightSpace->text().toFloat();
	_wdprops.linespace.bottom = ui.linebottomSpace->text().toFloat();

	_wdprops.linespace.leftpad = ui.lineleftPad->text().toFloat();
	_wdprops.linespace.toppad = ui.linetopPad->text().toFloat();
	_wdprops.linespace.rightpad = ui.linerightPad->text().toFloat();
	_wdprops.linespace.bottompad = ui.linebottomPad->text().toFloat();

	_wdprops.cellspace.left = ui.cellLeftSpace->text().toFloat();
	_wdprops.cellspace.top = ui.celltopspace->text().toFloat();
	_wdprops.cellspace.right = ui.cellrightspace->text().toFloat();
	_wdprops.cellspace.bottom = ui.cellbottomspace->text().toFloat();

	_wdprops.cellspace.leftpad = ui.cellleftpad->text().toFloat();
	_wdprops.cellspace.toppad = ui.celltoppad->text().toFloat();
	_wdprops.cellspace.rightpad = ui.cellrightpad->text().toFloat();
	_wdprops.cellspace.bottompad = ui.cellbottompad->text().toFloat();

}


void CalWeekDaySheet::_getFont()
{
	_wdprops.fontcfg.name = ui.cbFont->currentFont().family();

	QtColorComboBox *colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbfontcolor);
	if ( colorpicker )
	{
		_wdprops.fontcfg.color = colorpicker->currentColor();
	}
	if ( ui.btnBold->isChecked() )
	{
		_wdprops.fontcfg.bold = true;
	}
	else
	{
		_wdprops.fontcfg.bold = false;
	}

	if ( ui.btnItalic->isChecked() )
	{
		_wdprops.fontcfg.iatic = true;
	}
	else
	{
		_wdprops.fontcfg.iatic = false;
	}

	if ( ui.btnUnderLine->isChecked() )
	{
		_wdprops.fontcfg.underLine = true;
	}
	else
	{
		_wdprops.fontcfg.underLine = false;
	}

	_wdprops.fontcfg.align = 0;
	if ( ui.btnAlignLeft->isChecked() )
	{
		_wdprops.fontcfg.align |= Qt::AlignLeft;
	}
	if ( ui.btnAlignHCenter->isChecked() )
	{
		_wdprops.fontcfg.align |= Qt::AlignHCenter;
	}
	if ( ui.btnAlignRight->isChecked() )
	{
		_wdprops.fontcfg.align |= Qt::AlignRight;
	}
	
	if ( ui.btnAlignTop->isChecked() )
	{
		_wdprops.fontcfg.align |= Qt::AlignTop;
	}
	if ( ui.btnAlignVCenter->isChecked() )
	{
		_wdprops.fontcfg.align |= Qt::AlignVCenter;
	}
	if ( ui.btnAlignBottom->isChecked() )
	{
		_wdprops.fontcfg.align |= Qt::AlignBottom;
	}

	//
	_wdprops.fontcfg.heightInCell = ui.fontheightIncell->text().toFloat()/100;
}


bool CalWeekDaySheet::getWeekdaysPorps(WEEKDAY_PROPS &wdprops)
{
	_getFont();
	_getColor();
	_getSpace();

	_wdprops.regionsize = ui.wdSize->text().toFloat();
	if ( ui.cbShowWd->isChecked() )
	{
		this->_wdprops.showwds  = true;
	}
	else
	{
		this->_wdprops.showwds = false;
	}

	wdprops = _wdprops;
	return true;
}
