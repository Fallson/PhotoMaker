#include "calmonthyearsheet.h"
#include "qtcolorpicker.h"
#include "qtcolorcombobox.h"

extern QString gbires;

CalMonthYearSheet::CalMonthYearSheet(const MONTHYEAR_PROPS &myprops,QWidget *parent)
	: QWidget(parent), _myprops(myprops)
{
	ui.setupUi(this);
	QRect colorrect;
	QtColorComboBox *colorpicker= NULL;


	QColor nocolor = Qt::transparent;
	nocolor.setAlpha(0);

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

	ui.monthYearSize->setValidator(new QIntValidator(1, 100, this));

	// limit space only accept number
	ui.lineleftSpace->setValidator(new QIntValidator(1, 100, this));
	ui.linetopSpace->setValidator(new QIntValidator(1, 100, this));
	ui.linerightSpace->setValidator(new QIntValidator(1, 100, this));
	ui.linebottomSpace->setValidator(new QIntValidator(1, 100, this));

	ui.lineleftPad->setValidator(new QIntValidator(1, 100, this));
	ui.linetopPad->setValidator(new QIntValidator(1, 100, this));
	ui.linerightPad->setValidator(new QIntValidator(1, 100, this));
	ui.linebottomPad->setValidator(new QIntValidator(1, 100, this));



	_init();

}

CalMonthYearSheet::~CalMonthYearSheet()
{

}


void CalMonthYearSheet::_leftBtnClicked()
{
	//
	ui.btnAlignLeft->setChecked(true);
	ui.btnAlignHCenter->setChecked(false);
	ui.btnAlignRight->setChecked(false);

}
void CalMonthYearSheet::_hcenterBtnClicked()
{
	ui.btnAlignHCenter->setChecked(true);
	ui.btnAlignLeft->setChecked(false);
	ui.btnAlignRight->setChecked(false);
}

void CalMonthYearSheet::_rightBtnClicked()
{
	ui.btnAlignRight->setChecked(true);
	ui.btnAlignLeft->setChecked(false);
	ui.btnAlignHCenter->setChecked(false);
}
void CalMonthYearSheet::_topBtnClicked()
{
	ui.btnAlignTop->setChecked(true);
	ui.btnAlignBottom->setChecked(false);
	ui.btnAlignVCenter->setChecked(false);
}

void CalMonthYearSheet::_vcenterBtnClicked()
{
	ui.btnAlignVCenter->setChecked(true);
	ui.btnAlignBottom->setChecked(false);
	ui.btnAlignTop->setChecked(false);
}

void CalMonthYearSheet::_bottomBtnClicked()
{
	ui.btnAlignBottom->setChecked(true);
	ui.btnAlignVCenter->setChecked(false);
	ui.btnAlignTop->setChecked(false);
}



void CalMonthYearSheet::_init()
{
	_initFont();
	_initColor();
	_initSpace();

	ui.monthYearSize->setText(QString("%1").arg(_myprops.regionsize));
	ui.cbShowMonthYear->setChecked(this->_myprops.showmonthyear);
	ui.cbShowOnBottom->setChecked(_myprops.showonbottom);
	ui.cbShowMonthYeardoulbeLine->setChecked(_myprops.showmonthyeardouble);

}

void CalMonthYearSheet::_initFont()
{
	ui.fontComboBox->setCurrentFont(QFont(this->_myprops.fontcfg.name));
	QtColorComboBox *colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbfontcolor);
	if ( colorpicker )
	{
		if ( _myprops.fontcfg.color.alpha() == 0 )
		{
			QColor nocolor = Qt::transparent;
			nocolor.setAlpha(0);
			colorpicker->setCurrentColor(nocolor);
		}
		else
		{
			colorpicker->setCurrentColor(_myprops.fontcfg.color);
		}
	}
	if ( _myprops.fontcfg.bold )
	{
		ui.btnBold->setChecked(true);
	}
	else
	{
		ui.btnBold->setChecked(false);
	}
	if ( _myprops.fontcfg.iatic )
	{
		ui.btnItalic->setChecked(true);
	}
	else
	{
		ui.btnItalic->setChecked(false);
	}
	if ( _myprops.fontcfg.underLine )
	{
		ui.btnUnderLine->setChecked(true);
	}
	else
	{
		ui.btnUnderLine->setChecked(false);
	}
	if ( _myprops.fontcfg.align & Qt::AlignLeft)
	{
		ui.btnAlignLeft->setChecked(true);
	}
	else
	{
		ui.btnAlignLeft->setChecked(false);
	}
	if ( _myprops.fontcfg.align & Qt::AlignHCenter)
	{
		ui.btnAlignHCenter->setChecked(true);
	}
	else
	{
		ui.btnAlignHCenter->setChecked(false);
	}
	if ( _myprops.fontcfg.align & Qt::AlignRight)
	{
		ui.btnAlignRight->setChecked(true);
	}
	else
	{
		ui.btnAlignRight->setChecked(false);
	}

	if ( _myprops.fontcfg.align & Qt::AlignTop)
	{
		ui.btnAlignTop->setChecked(true);
	}
	else
	{
		ui.btnAlignTop->setChecked(false);
	}
	if ( _myprops.fontcfg.align & Qt::AlignVCenter)
	{
		ui.btnAlignVCenter->setChecked(true);
	}
	else
	{
		ui.btnAlignVCenter->setChecked(false);
	}
	if ( _myprops.fontcfg.align & Qt::AlignBottom)
	{
		ui.btnAlignBottom->setChecked(true);
	}
	else
	{
		ui.btnAlignBottom->setChecked(false);
	}
	ui.fontheightIncell->setText(QString("%1").arg(_myprops.fontcfg.heightInCell*100));

	connect(ui.btnAlignLeft, SIGNAL(clicked()), SLOT(_leftBtnClicked()));
	connect(ui.btnAlignHCenter, SIGNAL(clicked()), SLOT(_hcenterBtnClicked()));
	connect(ui.btnAlignRight, SIGNAL(clicked()), SLOT(_rightBtnClicked()));
	connect(ui.btnAlignTop, SIGNAL(clicked()), SLOT(_topBtnClicked()));
	connect(ui.btnAlignVCenter, SIGNAL(clicked()), SLOT(_vcenterBtnClicked()));
	connect(ui.btnAlignBottom, SIGNAL(clicked()), SLOT(_bottomBtnClicked()));


}

void CalMonthYearSheet::_initSpace()
{

	ui.lineleftSpace->setText(QString("%1").arg(_myprops.linespace.left));
	ui.linetopSpace->setText(QString("%1").arg(_myprops.linespace.top));
	ui.linerightSpace->setText(QString("%1").arg(_myprops.linespace.right));
	ui.linebottomSpace->setText(QString("%1").arg(_myprops.linespace.bottom));

	ui.lineleftPad->setText(QString("%1").arg(_myprops.linespace.leftpad));
	ui.linetopPad->setText(QString("%1").arg(_myprops.linespace.toppad));
	ui.linerightPad->setText(QString("%1").arg(_myprops.linespace.rightpad));
	ui.linebottomPad->setText(QString("%1").arg(_myprops.linespace.bottompad));

}

void CalMonthYearSheet::_initColor()
{
	QtColorComboBox *colorpicker = NULL; //dynamic_cast<QtColorComboBox *>(ui.btnBackColor);
	/*
	if ( colorpicker )
	{
		colorpicker->setCurrentColor(_myprops.bgcolor);
	}
	*/

	colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbrowcolor);
	if ( colorpicker )
	{
		if ( _myprops.rowcolor.alpha() == 0 )
		{
			QColor nocolor = Qt::transparent;
			nocolor.setAlpha(0);
			colorpicker->setCurrentColor(nocolor);
		}
		else
		{
			colorpicker->setCurrentColor(_myprops.rowcolor);
		}
	}

	/*
	colorpicker = dynamic_cast<QtColorComboBox *>(ui.btnCellColor);
	if ( colorpicker )
	{
		colorpicker->setCurrentColor(_myprops.cellcolor);
	}
	*/

	// init week days color later
	//QList<QColor> wdcolors;

}



void CalMonthYearSheet::_getColor()
{
	QtColorComboBox *colorpicker = NULL;


	colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbrowcolor);
	if ( colorpicker )
	{
		_myprops.rowcolor = colorpicker->currentColor();
	}
	// init week days color later
	//QList<QColor> wdcolors;

}


void CalMonthYearSheet::_getSpace()
{
	_myprops.linespace.left = ui.lineleftSpace->text().toFloat();
	_myprops.linespace.top = ui.linetopSpace->text().toFloat();
	_myprops.linespace.right = ui.linerightSpace->text().toFloat();
	_myprops.linespace.bottom = ui.linebottomSpace->text().toFloat();

	_myprops.linespace.leftpad = ui.lineleftPad->text().toFloat();
	_myprops.linespace.toppad = ui.linetopPad->text().toFloat();
	_myprops.linespace.rightpad = ui.linerightPad->text().toFloat();
	_myprops.linespace.bottompad = ui.linebottomPad->text().toFloat();

}


void CalMonthYearSheet::_getFont()
{
	_myprops.fontcfg.name = ui.fontComboBox->currentFont().family();

	QtColorComboBox *colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbfontcolor);
	if ( colorpicker )
	{
		_myprops.fontcfg.color = colorpicker->currentColor();
	}
	if ( ui.btnBold->isChecked() )
	{
		_myprops.fontcfg.bold = true;
	}
	else
	{
		_myprops.fontcfg.bold = false;
	}

	if ( ui.btnItalic->isChecked() )
	{
		_myprops.fontcfg.iatic = true;
	}
	else
	{
		_myprops.fontcfg.iatic = false;
	}

	if ( ui.btnUnderLine->isChecked() )
	{
		_myprops.fontcfg.underLine = true;
	}
	else
	{
		_myprops.fontcfg.underLine = false;
	}

	_myprops.fontcfg.align = 0;
	if ( ui.btnAlignLeft->isChecked() )
	{
		_myprops.fontcfg.align |= Qt::AlignLeft;
	}
	if ( ui.btnAlignHCenter->isChecked() )
	{
		_myprops.fontcfg.align |= Qt::AlignHCenter;
	}
	if ( ui.btnAlignRight->isChecked() )
	{
		_myprops.fontcfg.align |= Qt::AlignRight;
	}
	
	if ( ui.btnAlignTop->isChecked() )
	{
		_myprops.fontcfg.align |= Qt::AlignTop;
	}
	if ( ui.btnAlignVCenter->isChecked() )
	{
		_myprops.fontcfg.align |= Qt::AlignVCenter;
	}
	if ( ui.btnAlignBottom->isChecked() )
	{
		_myprops.fontcfg.align |= Qt::AlignBottom;
	}

	//
	_myprops.fontcfg.heightInCell = ui.fontheightIncell->text().toFloat()/100;
}


bool CalMonthYearSheet::getMonthYearProps(MONTHYEAR_PROPS &monthyearprops)
{
	this->_getFont();
	this->_getColor();
	this->_getSpace();
	_myprops.regionsize  = ui.monthYearSize->text().toFloat();
	if ( ui.cbShowMonthYear->isChecked() )
	{
		this->_myprops.showmonthyear = true;
	}
	else
	{
		this->_myprops.showmonthyear = false;
	}
	if ( ui.cbShowOnBottom->isChecked() )
	{
		_myprops.showonbottom = true;
	}
	else
	{
		_myprops.showonbottom = false;
	}
	
	if ( ui.cbShowMonthYeardoulbeLine->isChecked() )
	{
		_myprops.showmonthyeardouble = true;
	}
	else
	{
		_myprops.showmonthyeardouble = false;
	}


	monthyearprops = this->_myprops;
	return true;
}


