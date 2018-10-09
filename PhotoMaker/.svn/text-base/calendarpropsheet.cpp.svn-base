#include "calendarpropsheet.h"
#include "qtcolorpicker.h"
#include "qtcolorcombobox.h"

extern QString gbires;

CalendarPropSheet::CalendarPropSheet(const CAL_PROPS &calprops,QWidget *parent)
	: QWidget(parent), _calprops(calprops)
{
	ui.setupUi(this);


	QColor nocolor = Qt::transparent;
	nocolor.setAlpha(0);

	QtColorComboBox *colorpicker =  dynamic_cast<QtColorComboBox*>( ui.cbbgcolor);
	//colorpicker->sets
	colorpicker->insertColor(0, nocolor, tr("No Color"));
	colorpicker->setStandardColors();
	colorpicker->setColorDialogEnabled(true);
	//colorpicker


	colorpicker =  dynamic_cast<QtColorComboBox*>( ui.cbfontcolor);
	colorpicker->insertColor(0, nocolor, "No Color");
	colorpicker->setStandardColors();
	colorpicker->setColorDialogEnabled(true);


	colorpicker =  dynamic_cast<QtColorComboBox*>( ui.cbcellcolor);
	colorpicker->insertColor(0, nocolor, "No Color");
	colorpicker->setStandardColors();
	colorpicker->setColorDialogEnabled(true);

	colorpicker =  dynamic_cast<QtColorComboBox*>( ui.cbrowcolor);
	colorpicker->insertColor(0,nocolor, "No Color");
	colorpicker->setStandardColors();
	colorpicker->setColorDialogEnabled(true);

	colorpicker =  dynamic_cast<QtColorComboBox*>( ui.cbwdcolor);
	colorpicker->insertColor(0 , nocolor, "No Color");
	colorpicker->setStandardColors();
	colorpicker->setColorDialogEnabled(true);

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

	ui.cbWeekDay->addItem(tr("Monday"), QVariant(QColor(Qt::black)));
	ui.cbWeekDay->addItem(tr("Tuesday"), QVariant(QColor(Qt::black)));
	ui.cbWeekDay->addItem(tr("Wensday"), QVariant(QColor(Qt::black)));
	ui.cbWeekDay->addItem(tr("Thursday"), QVariant(QColor(Qt::black)));
	ui.cbWeekDay->addItem(tr("Friday"), QVariant(QColor(Qt::black)));
	ui.cbWeekDay->addItem(tr("Saturday"), QVariant(QColor(Qt::red)));
	ui.cbWeekDay->addItem(tr("Sunday"), QVariant(QColor(Qt::red)));

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


	connect(ui.cbWeekDay, SIGNAL(currentIndexChanged (int )), this, SLOT(_wdcolorSelChanged(int )));
	connect(ui.cbwdcolor, SIGNAL(currentIndexChanged(int)), this, SLOT(_wdcolorChanged(int )));

	// init the items
	_init();

}

CalendarPropSheet::~CalendarPropSheet()
{

}

void CalendarPropSheet::_init()
{
	_initFont();
	_initColor();
	_initSpace();
}

void CalendarPropSheet::_initFont()
{
	ui.fontComboBox->setCurrentFont(QFont(this->_calprops.fontcfg.name));
	QtColorComboBox *colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbfontcolor);
	if ( colorpicker )
	{
		if( _calprops.fontcfg.color.alpha() == 0 )
		{
			QColor nocolor = Qt::transparent;
			nocolor.setAlpha(0);
			colorpicker->setCurrentColor(nocolor);
		}
		else
		{
			colorpicker->setCurrentColor(_calprops.fontcfg.color);
		}
	}
	if ( _calprops.fontcfg.bold )
	{
		ui.btnBold->setChecked(true);
	}
	else
	{
		ui.btnBold->setChecked(false);
	}
	if ( _calprops.fontcfg.iatic )
	{
		ui.btnItalic->setChecked(true);
	}
	else
	{
		ui.btnItalic->setChecked(false);
	}
	if ( _calprops.fontcfg.underLine )
	{
		ui.btnUnderLine->setChecked(true);
	}
	else
	{
		ui.btnUnderLine->setChecked(false);
	}
	if ( _calprops.fontcfg.align & Qt::AlignLeft)
	{
		ui.btnAlignLeft->setChecked(true);
	}
	else
	{
		ui.btnAlignLeft->setChecked(false);
	}
	if ( _calprops.fontcfg.align & Qt::AlignHCenter)
	{
		ui.btnAlignHCenter->setChecked(true);
	}
	else
	{
		ui.btnAlignHCenter->setChecked(false);
	}
	if ( _calprops.fontcfg.align & Qt::AlignRight)
	{
		ui.btnAlignRight->setChecked(true);
	}
	else
	{
		ui.btnAlignRight->setChecked(false);
	}

	if ( _calprops.fontcfg.align & Qt::AlignTop)
	{
		ui.btnAlignTop->setChecked(true);
	}
	else
	{
		ui.btnAlignTop->setChecked(false);
	}
	if ( _calprops.fontcfg.align & Qt::AlignVCenter)
	{
		ui.btnAlignVCenter->setChecked(true);
	}
	else
	{
		ui.btnAlignVCenter->setChecked(false);
	}
	if ( _calprops.fontcfg.align & Qt::AlignBottom)
	{
		ui.btnAlignBottom->setChecked(true);
	}
	else
	{
		ui.btnAlignBottom->setChecked(false);
	}
	ui.fontheightIncell->setText(QString("%1").arg(_calprops.fontcfg.heightInCell*100));

	connect(ui.btnAlignLeft, SIGNAL(clicked()), SLOT(_leftBtnClicked()));
	connect(ui.btnAlignHCenter, SIGNAL(clicked()), SLOT(_hcenterBtnClicked()));
	connect(ui.btnAlignRight, SIGNAL(clicked()), SLOT(_rightBtnClicked()));
	connect(ui.btnAlignTop, SIGNAL(clicked()), SLOT(_topBtnClicked()));
	connect(ui.btnAlignVCenter, SIGNAL(clicked()), SLOT(_vcenterBtnClicked()));
	connect(ui.btnAlignBottom, SIGNAL(clicked()), SLOT(_bottomBtnClicked()));


}


void CalendarPropSheet::_leftBtnClicked()
{
	//
	ui.btnAlignLeft->setChecked(true);
	ui.btnAlignHCenter->setChecked(false);
	ui.btnAlignRight->setChecked(false);

}
void CalendarPropSheet::_hcenterBtnClicked()
{
	ui.btnAlignHCenter->setChecked(true);
	ui.btnAlignLeft->setChecked(false);
	ui.btnAlignRight->setChecked(false);
}

void CalendarPropSheet::_rightBtnClicked()
{
	ui.btnAlignRight->setChecked(true);
	ui.btnAlignLeft->setChecked(false);
	ui.btnAlignHCenter->setChecked(false);
}
void CalendarPropSheet::_topBtnClicked()
{
	ui.btnAlignTop->setChecked(true);
	ui.btnAlignBottom->setChecked(false);
	ui.btnAlignVCenter->setChecked(false);
}

void CalendarPropSheet::_vcenterBtnClicked()
{
	ui.btnAlignVCenter->setChecked(true);
	ui.btnAlignBottom->setChecked(false);
	ui.btnAlignTop->setChecked(false);
}

void CalendarPropSheet::_bottomBtnClicked()
{
	ui.btnAlignBottom->setChecked(true);
	ui.btnAlignVCenter->setChecked(false);
	ui.btnAlignTop->setChecked(false);
}


void CalendarPropSheet::_initSpace()
{
	ui.lineleftSpace->setText(QString("%1").arg(_calprops.linespace.left));
	ui.linetopSpace->setText(QString("%1").arg(_calprops.linespace.top));
	ui.linerightSpace->setText(QString("%1").arg(_calprops.linespace.right));
	ui.linebottomSpace->setText(QString("%1").arg(_calprops.linespace.bottom));

	ui.lineleftPad->setText(QString("%1").arg(_calprops.linespace.leftpad));
	ui.linetopPad->setText(QString("%1").arg(_calprops.linespace.toppad));
	ui.linerightPad->setText(QString("%1").arg(_calprops.linespace.rightpad));
	ui.linebottomPad->setText(QString("%1").arg(_calprops.linespace.bottompad));

	ui.cellLeftSpace->setText(QString("%1").arg(_calprops.cellspace.left));
	ui.celltopspace->setText(QString("%1").arg(_calprops.cellspace.top));
	ui.cellrightspace->setText(QString("%1").arg(_calprops.cellspace.right));
	ui.cellbottomspace->setText(QString("%1").arg(_calprops.cellspace.bottom));

	ui.cellleftpad->setText(QString("%1").arg(_calprops.cellspace.leftpad));
	ui.celltoppad->setText(QString("%1").arg(_calprops.cellspace.toppad));
	ui.cellrightpad->setText(QString("%1").arg(_calprops.cellspace.rightpad));
	ui.cellbottompad->setText(QString("%1").arg(_calprops.cellspace.bottompad));

}

void CalendarPropSheet::_initColor()
{
	QtColorComboBox *colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbbgcolor);
	if ( colorpicker )
	{
		if ( _calprops.bgcolor.alpha() == 0 )
		{
			// no color
			QColor nocolor = Qt::transparent;
			nocolor.setAlpha(0);
			colorpicker->setCurrentColor(nocolor);
		}
		else
		{
			colorpicker->setCurrentColor(_calprops.bgcolor);
		}
	}

	colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbrowcolor);
	if ( colorpicker )
	{
		if ( _calprops.rowcolor.alpha() == 0 )
		{
			QColor nocolor = Qt::transparent;
			nocolor.setAlpha(0);
			colorpicker->setCurrentColor(nocolor);
		}
		else
		{
			colorpicker->setCurrentColor(_calprops.rowcolor);
		}
	}

	colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbcellcolor);
	if ( colorpicker )
	{
		if ( _calprops.cellcolor.alpha() == 0 )
		{
			QColor nocolor = Qt::transparent;
			nocolor.setAlpha(0);
			colorpicker->setCurrentColor(nocolor);
		}
		else
		{
			colorpicker->setCurrentColor(_calprops.cellcolor);
		}
	}

	// init week days color later
	//QList<QColor> wdcolors;
	QList<QColor>::iterator it;
	int i=0;
	for ( it = _calprops.wdcolors.begin(); it!=_calprops.wdcolors.end(); it++ ,i++)
	{
		ui.cbWeekDay->setItemData(i, *it);
	}
	ui.cbWeekDay->setCurrentIndex(0);
	ui.cbwdcolor->setCurrentColor(_calprops.wdcolors[0]);

}



void CalendarPropSheet::_getColor()
{
	QtColorComboBox *colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbbgcolor);
	if ( colorpicker )
	{
		_calprops.bgcolor = colorpicker->currentColor();
	}

	colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbrowcolor);
	if ( colorpicker )
	{
		_calprops.rowcolor = colorpicker->currentColor();
	}

	colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbcellcolor);
	if ( colorpicker )
	{
		_calprops.cellcolor = colorpicker->currentColor();
	}

	// init week days color later
	//QList<QColor> wdcolors;
	int i=0;
	for ( ; i<_calprops.wdcolors.size(); i++)
	{
		//ui.cbWeekDay->addItem(tr("Monday"), QVariant(QColor(Qt::black)));
		//QVariant data = ui.cbWeekDay->itemData(i);
		//QColor color = data.toULongLong();
		//ui.cbWeekDay->setItemData(i, *it);
		//QVariant data = ui.cbWeekDay->itemData(i);
		//_calprops.wdcolors[i] = data.value<QColor>();;

	}

}


void CalendarPropSheet::_getSpace()
{
	_calprops.linespace.left = ui.lineleftSpace->text().toFloat();
	_calprops.linespace.top = ui.linetopSpace->text().toFloat();
	_calprops.linespace.right = ui.linerightSpace->text().toFloat();
	_calprops.linespace.bottom = ui.linebottomSpace->text().toFloat();

	_calprops.linespace.leftpad = ui.lineleftPad->text().toFloat();
	_calprops.linespace.toppad = ui.linetopPad->text().toFloat();
	_calprops.linespace.rightpad = ui.linerightPad->text().toFloat();
	_calprops.linespace.bottompad = ui.linebottomPad->text().toFloat();

	_calprops.cellspace.left = ui.cellLeftSpace->text().toFloat();
	_calprops.cellspace.top = ui.celltopspace->text().toFloat();
	_calprops.cellspace.right = ui.cellrightspace->text().toFloat();
	_calprops.cellspace.bottom = ui.cellbottomspace->text().toFloat();

	_calprops.cellspace.leftpad = ui.cellleftpad->text().toFloat();
	_calprops.cellspace.toppad = ui.celltoppad->text().toFloat();
	_calprops.cellspace.rightpad = ui.cellrightpad->text().toFloat();
	_calprops.cellspace.bottompad = ui.cellbottompad->text().toFloat();

}


void CalendarPropSheet::_getFont()
{
	_calprops.fontcfg.name = ui.fontComboBox->currentFont().family();

	QtColorComboBox *colorpicker = dynamic_cast<QtColorComboBox *>(ui.cbfontcolor);
	if ( colorpicker )
	{
		_calprops.fontcfg.color = colorpicker->currentColor();
	}
	if ( ui.btnBold->isChecked() )
	{
		_calprops.fontcfg.bold = true;
	}
	else
	{
		_calprops.fontcfg.bold = false;
	}

	if ( ui.btnItalic->isChecked() )
	{
		_calprops.fontcfg.iatic = true;
	}
	else
	{
		_calprops.fontcfg.iatic = false;
	}

	if ( ui.btnUnderLine->isChecked() )
	{
		_calprops.fontcfg.underLine = true;
	}
	else
	{
		_calprops.fontcfg.underLine = false;
	}

	_calprops.fontcfg.align = 0;
	if ( ui.btnAlignLeft->isChecked() )
	{
		_calprops.fontcfg.align |= Qt::AlignLeft;
	}
	if ( ui.btnAlignHCenter->isChecked() )
	{
		_calprops.fontcfg.align |= Qt::AlignHCenter;
	}
	if ( ui.btnAlignRight->isChecked() )
	{
		_calprops.fontcfg.align |= Qt::AlignRight;
	}
	
	if ( ui.btnAlignTop->isChecked() )
	{
		_calprops.fontcfg.align |= Qt::AlignTop;
	}
	if ( ui.btnAlignVCenter->isChecked() )
	{
		_calprops.fontcfg.align |= Qt::AlignVCenter;
	}
	if ( ui.btnAlignBottom->isChecked() )
	{
		_calprops.fontcfg.align |= Qt::AlignBottom;
	}

	//
	_calprops.fontcfg.heightInCell = ui.fontheightIncell->text().toFloat()/100;
}

bool CalendarPropSheet::getCalProps(CAL_PROPS &calprops)
{
	// update all data
	this->_getFont();
	this->_getColor();
	this->_getSpace();

	calprops = _calprops;
	return true;
}


void CalendarPropSheet::_wdcolorSelChanged(int curindex)
{
	int i=0;
	if ( curindex < 0 || curindex >= _calprops.wdcolors.size() )
	{
		return ;
	}
	//QVariant data = ui.cbWeekDay->itemData(curindex);
	//_calprops.wdcolors[curindex];

	this->ui.cbwdcolor->setCurrentColor(_calprops.wdcolors[curindex]);

}

void CalendarPropSheet::_wdcolorChanged(int curindex)
{
	int oldindex = ui.cbWeekDay->currentIndex();
	_calprops.wdcolors[oldindex] = ui.cbwdcolor->currentColor();
}