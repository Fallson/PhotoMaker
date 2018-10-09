#include "PhotoPrintPrjModel.h"
#include <QDate>



PhotoPrintPrjModel::PhotoPrintPrjModel()
{
}

PhotoPrintPrjModel::~PhotoPrintPrjModel()
{
}

PpPrjWizardPage *PhotoPrintPrjModel::Init()
{
	_pCurPage = new PpFormatSelectPage(this);
	return _pCurPage;
}

PpPrjWizardPage *PhotoPrintPrjModel::goNext()
{
	if ( NULL == _pCurPage->getNextPage() )
	{
		return NULL;
	}
	PRJ_DIR_ITM selecteditm;
	if ( _pCurPage && _pCurPage->getSelectedItm(selecteditm) )
	{
		_fillProjProps(selecteditm, this->_projprops);
	}

	_pCurPage = _pCurPage->getNextPage();
	return _pCurPage;
}

PpPrjWizardPage *PhotoPrintPrjModel::goPre()
{
	if ( !_pCurPage->getPrePage() )
	{
		return NULL;
	}
	_pCurPage = _pCurPage->getPrePage();
	return _pCurPage;
}

PpPrjWizardPage *PhotoPrintPrjModel::getCurPage()
{
	return this->_pCurPage;
}

void PhotoPrintPrjModel::onOk()
{
	PRJ_DIR_ITM selecteditm;
	if ( _pCurPage && _pCurPage->getSelectedItm(selecteditm) )
	{
		_fillProjProps(selecteditm, this->_projprops);
	}
}


bool PhotoPrintPrjModel::_fillProjProps(const PRJ_DIR_ITM &selecteditm, PROJ_PROPS &projprops)
{
	switch(selecteditm.dirtype)
	{
		// project type
	case PP_FORMAT_PB4X3:
		{
			projprops.type = PROJ_PROPS::POCKETBOOK4X3;
		}
		break;
	case PP_FORMAT_PB10X15:
		{
			projprops.type = PROJ_PROPS::PHOTOBOOK10X15;
		}
		break;
	case PP_FORMAT_SINGLE4X6:
		{
			projprops.type = PROJ_PROPS::SINGLE4X6;
		}
		break;
	case PP_FORMAT_PB8X5:
		{
			projprops.type = PROJ_PROPS::PHOTOBOOK8X5;
		}
		break;
	case PP_FORMAT_CALENDAR_A4:
		{
			projprops.type = PROJ_PROPS::CALENDARA4;
		}
		break;
	case PP_FORMAT_CALENDAR_A5:
		{
			projprops.type = PROJ_PROPS::CALENDARA5;
		}
		break;
	case PP_FORMAT_CALENDAR_4X6:
		{
			projprops.type = PROJ_PROPS::CALENDAR4X6;
		}
		break;
		// border
	case PP_LAYOUT_FULLSIZE:
	case PP_LAYOUT_PB8X5_BORDERLESS:
		{
			projprops.hasborder = false;
		}
		break;
	case PP_LAYOUT_BORDER:
	case PP_LAYOUT_PB8X5:
		{
			projprops.hasborder = true;
			projprops.shadow = true;
		}
		break;
	case PP_LAYOUT_PB8X5_FULLSIZE:
		{
			projprops.lytype = PROJ_PROPS::LY8X5FULL;
		}
		break;
	case PP_LAYOUT_PB8X5_TRADITION:
		{
			projprops.lytype = PROJ_PROPS::LY8X5TRADITION;
		}
		break;
	case PP_LAYOUT_PB8X5_HORIZON:
		{
			projprops.lytype = PROJ_PROPS::LY8X5HORIZON;
		}
		break;
	case PP_LAYOUT_PB8X5_VERTICON:
		{
			projprops.lytype = PROJ_PROPS::LY8X5VERTICON;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L1_NAME:
		{
			projprops.lytype = PROJ_PROPS::LYCALA4L1;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L2_NAME:
		{
			projprops.lytype = PROJ_PROPS::LYCALA4L2;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L3_NAME:
		{
			projprops.lytype = PROJ_PROPS::LYCALA4L3;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L4_NAME:
		{
			projprops.lytype = PROJ_PROPS::LYCALA4L4;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L1_NAME:
		{
			projprops.lytype = PROJ_PROPS::LYCALA5L1;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L2_NAME:
		{
			projprops.lytype = PROJ_PROPS::LYCALA5L2;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L3_NAME:
		{
			projprops.lytype = PROJ_PROPS::LYCALA5L3;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L1_NAME:
		{
			projprops.lytype = PROJ_PROPS::LYCAL4X6L1;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L2_NAME:
		{
			projprops.lytype = PROJ_PROPS::LYCAL4X6L2;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L3_NAME:
		{
			projprops.lytype = PROJ_PROPS::LYCAL4X6L3;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L4_NAME:
		{
			projprops.lytype = PROJ_PROPS::LYCAL4X6L4;
		}
		break;
	case PP_CALENDAR_YEAR:
		{
			projprops.year = selecteditm.name.toInt();
			if ( projprops.year>2020)
			{
				projprops.year = 2020;
			}
			else if (  projprops.year < 2012 )
			{
				projprops.year = 2012;
			}
		}
		break;
	}
	return true;
}



PpBaseSelectPage::PpBaseSelectPage(PhotoPrintPrjModel *pModel):
_selectedindex(0), _pPrePage(NULL), _model(pModel)
{

}

PpBaseSelectPage::~PpBaseSelectPage(){}

bool PpBaseSelectPage::getDirItm(QList<PRJ_DIR_ITM> &diritms)
{
	diritms = _diritmslst;
	return true;
}

bool PpBaseSelectPage::getSelectedItm(PRJ_DIR_ITM &selctedItm)
{
	return _getSelectItm(_selectedindex, selctedItm);
}

bool PpBaseSelectPage::setSelectedIndex(const int index)
{
	_selectedindex = index;
	return true;
}

bool PpBaseSelectPage::_getSelectItm(const int index, PRJ_DIR_ITM &selecteditm)
{

	QList<PRJ_DIR_ITM>::iterator it;
	int i;
	for ( i=0,it=_diritmslst.begin(); it!=_diritmslst.end(); it++, i++ )
	{
		if ( i==index)
		{
			break;
		}
	}
	if ( it == _diritmslst.end() )
	{
		return false;
	}

	selecteditm = *it;

	return true;
}

PpPrjWizardPage* PpBaseSelectPage::getNextPage()
{
	PRJ_DIR_ITM diritm;
	if ( !_getSelectItm(_selectedindex, diritm) )
	{
		return NULL;
	}

	//
	//
	//

	return diritm.nextPage;
}

PpFormatSelectPage::PpFormatSelectPage(PhotoPrintPrjModel* model):PpBaseSelectPage(model),_isFinal(false)
{
	PRJ_DIR_ITM diritm;

	diritm.index = 0;
	diritm.name = tr("PocketBooklet 4:3");
	diritm.iconPath = "";
	diritm.showPicPath = "Resources/images/Pocket4x3_show.png";
	diritm.dirtype= PP_FORMAT_PB4X3;
	diritm.nextPage = new Pp4X3LayoutSelectPage(_model);
	diritm.nextPage->setPrePage(this);
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("PhotoBook 10x15");
	diritm.showPicPath = "Resources/images/Photobook10x15_show.png";
	diritm.dirtype= PP_FORMAT_PB10X15;
	diritm.nextPage = NULL;
	_diritmslst.push_back(diritm);

	/*
	diritm.index++;
	diritm.name = tr("4x6\" Single");
	diritm.showPicPath = "Resources/images/4x6Singles_show.png";
	diritm.dirtype= PP_FORMAT_SINGLE4X6;
	diritm.nextPage = NULL;
	_diritmslst.push_back(diritm);
	*/

	diritm.index++;
	diritm.name = tr("PhotoBook 8:5");
        diritm.showPicPath = "Resources/images/Photobook8x5_show.png";
	diritm.dirtype= PP_FORMAT_PB8X5;
	diritm.nextPage = new Pp8x5BorderSelectPage(_model);
	diritm.nextPage->setPrePage(this);
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Calendar A4");
	diritm.showPicPath = "Resources/images/CalendarA4_show.png";
	diritm.dirtype = PP_FORMAT_CALENDAR_A4;
	diritm.nextPage = new PpCalendarA4LayoutSelectPage(_model);
	diritm.nextPage->setPrePage(this);
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Calendar A5");
	diritm.showPicPath = "Resources/images/CalendarA5_show.png";
	diritm.dirtype = PP_FORMAT_CALENDAR_A5;
	diritm.nextPage = new PpCalendarA5LayoutSelectPage(_model);
	diritm.nextPage->setPrePage(this);
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("\"Calendar 4x6");
	diritm.showPicPath = "Resources/images/Calendar4x6_show.png";
	diritm.dirtype = PP_FORMAT_CALENDAR_4X6;
	diritm.nextPage = new PpCalendar4x6LayoutSelectPage(_model);
	diritm.nextPage->setPrePage(this);
	_diritmslst.push_back(diritm);

}

PpFormatSelectPage::~PpFormatSelectPage()
{
}




bool PpFormatSelectPage::HasPrePage()
{
	return false;
}
bool PpFormatSelectPage::HasNextPage()
{
	return !this->_isFinal;
}



bool PpFormatSelectPage::setSelectedIndex(const int index)
{
	this->_selectedindex = index;

	//
	PRJ_DIR_ITM diritm;
	if ( !_getSelectItm(index, diritm) )
	{
		return false;
	}

	switch(diritm.dirtype)
	{
	case PP_FORMAT_PB4X3:
		_isFinal = false;
		break;
	case PP_FORMAT_PB10X15:
		_isFinal = true;
		break;
	case PP_FORMAT_SINGLE4X6:
		_isFinal = true;
		break;
	case PP_FORMAT_PB8X5:
		_isFinal = false;
		break;
	case PP_FORMAT_CALENDAR_A4:
		_isFinal = false;
		break;
	case PP_FORMAT_CALENDAR_A5:
		_isFinal = false;
		break;
	case PP_FORMAT_CALENDAR_4X6:
		_isFinal = false;
		break;
	default:
		;
	}

	
	return true;
}

bool PpFormatSelectPage::getTitle(QString &title)
{
	title =  tr("Choose Your Format");
	return true;
}

PpPrjWizardPage* PpFormatSelectPage::getPrePage()
{
	return NULL;
}




Pp4X3LayoutSelectPage::Pp4X3LayoutSelectPage(PhotoPrintPrjModel* model):PpBaseSelectPage(model),_isFinal(false)
{
	PRJ_DIR_ITM diritm;

	diritm.index = 0;
	diritm.name = tr("Fullsize");
	diritm.iconPath = "";
	diritm.showPicPath = "Resources/images/Pocket4x3_show.png";
	diritm.dirtype= PP_LAYOUT_FULLSIZE;
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Border");
        diritm.showPicPath = "Resources/images/Pocket4x3_border_show.png";
	diritm.dirtype= PP_LAYOUT_BORDER;
	_diritmslst.push_back(diritm);
}

Pp4X3LayoutSelectPage::~Pp4X3LayoutSelectPage()
{
}




bool Pp4X3LayoutSelectPage::HasPrePage()
{
	return true;
}
bool Pp4X3LayoutSelectPage::HasNextPage()
{
	return false;
}


bool Pp4X3LayoutSelectPage::getTitle(QString &title)
{
	title =  tr("PocketBooklet 4:3 - Choose your base layout");
	return true;
}



PpPrjWizardPage* Pp4X3LayoutSelectPage::getNextPage()
{
	return NULL;
}


Pp8x5BorderSelectPage::Pp8x5BorderSelectPage(PhotoPrintPrjModel* model):PpBaseSelectPage(model),_isFinal(false)
{
	PRJ_DIR_ITM diritm;

	diritm.index=0;
	diritm.name = tr("PhotoBook 8:5");
	diritm.iconPath = "";
        diritm.showPicPath = "Resources/images/Photobook8x5_show.png";
	diritm.dirtype= PP_LAYOUT_PB8X5;
	diritm.nextPage = new Pp8x5LayoutSelectPage(_model);
	diritm.nextPage->setPrePage(this);
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("PhotoBook 8:5 Borderless");
        diritm.showPicPath = "Resources/images/photobook8x5_borderless_show.png";
	diritm.dirtype= PP_LAYOUT_PB8X5_BORDERLESS;
	diritm.nextPage = new Pp8x5NoBorderLayoutSelectPage(_model);
	diritm.nextPage->setPrePage(this);
	_diritmslst.push_back(diritm);
}

Pp8x5BorderSelectPage::~Pp8x5BorderSelectPage()
{
}




bool Pp8x5BorderSelectPage::HasPrePage()
{
	return true;
}
bool Pp8x5BorderSelectPage::HasNextPage()
{
	return true;
}



bool Pp8x5BorderSelectPage::getTitle(QString &title)
{
	title =  tr("PhotoBook 8:5 - Choose your base layout");
	return true;
}



Pp8x5LayoutSelectPage::Pp8x5LayoutSelectPage(PhotoPrintPrjModel* model):PpBaseSelectPage(model)
{
	PRJ_DIR_ITM diritm;

	diritm.nextPage = NULL;
	diritm.index=0;
	diritm.name = tr("Tradition");
	diritm.iconPath = "";
        diritm.showPicPath = "Resources/images/Photobook8x5_show.png";
	diritm.dirtype= PP_LAYOUT_PB8X5_TRADITION;
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Horizon");
        diritm.showPicPath = "Resources/images/Photobook8x5_hor_show.png";
	diritm.dirtype= PP_LAYOUT_PB8X5_HORIZON;
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Verticon");
        diritm.showPicPath = "Resources/images/Photobook8x5_ver_show.png";
	diritm.dirtype= PP_LAYOUT_PB8X5_VERTICON;
	_diritmslst.push_back(diritm);
}

Pp8x5LayoutSelectPage::~Pp8x5LayoutSelectPage()
{
}

bool Pp8x5LayoutSelectPage::HasPrePage()
{
	return true;
}

bool Pp8x5LayoutSelectPage::HasNextPage()
{
	return false;
}

bool Pp8x5LayoutSelectPage::getTitle(QString &title)
{
	title = tr("PhotoBook 8:5 - Choose your base layout");
	return true;
}




Pp8x5NoBorderLayoutSelectPage::Pp8x5NoBorderLayoutSelectPage(PhotoPrintPrjModel* model):PpBaseSelectPage(model)
{
	PRJ_DIR_ITM diritm;

	diritm.nextPage = NULL;
	diritm.index=0;
	diritm.name = tr("Fullsize");
	diritm.iconPath = "";
        diritm.showPicPath = "Resources/images/photobook8x5_borderless_show.png";
	diritm.dirtype= PP_LAYOUT_PB8X5_FULLSIZE;
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Tradition");
	diritm.iconPath = "";
        diritm.showPicPath = "Resources/images/photobook8x5_borderless_tra_show.png";
	diritm.dirtype= PP_LAYOUT_PB8X5_TRADITION;
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Horizon");
        diritm.showPicPath = "Resources/images/photobook8x5_borderless_hor_show.png";
	diritm.dirtype= PP_LAYOUT_PB8X5_HORIZON;
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Verticon");
        diritm.showPicPath = "Resources/images/photobook8x5_borderless_ver_show.png";
	diritm.dirtype= PP_LAYOUT_PB8X5_VERTICON;
	_diritmslst.push_back(diritm);
}

Pp8x5NoBorderLayoutSelectPage::~Pp8x5NoBorderLayoutSelectPage()
{
}

bool Pp8x5NoBorderLayoutSelectPage::HasPrePage(){return true;}
bool Pp8x5NoBorderLayoutSelectPage::HasNextPage(){return false;}

bool Pp8x5NoBorderLayoutSelectPage::getTitle(QString &title)
{
	title = tr("PhotoBook 8:5 borderless - Choose your base layout");
	return true;
}



PpCalendarA4LayoutSelectPage::PpCalendarA4LayoutSelectPage(PhotoPrintPrjModel* model):PpBaseSelectPage(model)
{
	PRJ_DIR_ITM diritm;
	diritm.nextPage = NULL;

	diritm.index=0;
	diritm.name = tr("Layout 1");
	diritm.iconPath = "";
	diritm.showPicPath = "Resources/images/CalendarA4_show.png";
	diritm.dirtype= PP_LAYOUT_CALENDAR_A4_L1_NAME;
	diritm.nextPage = new PpCalendarYearSelectPage(_model);
	diritm.nextPage->setPrePage(this);
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Layout 2");
	diritm.iconPath = "";
	diritm.showPicPath = "Resources/images/CalendarA4_l2_show.png";
	diritm.dirtype= PP_LAYOUT_CALENDAR_A4_L2_NAME;
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Layout 3");
	diritm.showPicPath = "Resources/images/CalendarA4_l3_show.png";
	diritm.dirtype= PP_LAYOUT_CALENDAR_A4_L3_NAME;
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Layout 4");
	diritm.showPicPath = "Resources/images/CalendarA4_l4_show.png";
	diritm.dirtype= PP_LAYOUT_CALENDAR_A4_L4_NAME;
	_diritmslst.push_back(diritm);
}
PpCalendarA4LayoutSelectPage::~PpCalendarA4LayoutSelectPage()
{
}

bool PpCalendarA4LayoutSelectPage::HasPrePage()
{
	return true;
}

bool PpCalendarA4LayoutSelectPage::HasNextPage()
{
	return true;
}


bool PpCalendarA4LayoutSelectPage::getTitle(QString &title)
{
	title = tr("Calendar A4 - Choose your base layout");
	return true;
}



PpCalendarA5LayoutSelectPage::PpCalendarA5LayoutSelectPage(PhotoPrintPrjModel* model):PpBaseSelectPage(model)
{
	PRJ_DIR_ITM diritm;
	diritm.nextPage = NULL;

	diritm.index=0;
	diritm.name = tr("Layout 1");
	diritm.iconPath = "";
	diritm.showPicPath = "Resources/images/CalendarA5_show.png";
	diritm.dirtype= PP_LAYOUT_CALENDAR_A5_L1_NAME;
	diritm.nextPage = new PpCalendarYearSelectPage(_model);
	diritm.nextPage->setPrePage(this);
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Layout 2");
	diritm.iconPath = "";
	diritm.showPicPath = "Resources/images/CalendarA5_l2_show.png";
	diritm.dirtype= PP_LAYOUT_CALENDAR_A5_L2_NAME;
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Layout 3");
	diritm.showPicPath = "Resources/images/CalendarA5_l3_show.png";
	diritm.dirtype= PP_LAYOUT_CALENDAR_A5_L3_NAME;
	_diritmslst.push_back(diritm);

}
PpCalendarA5LayoutSelectPage::~PpCalendarA5LayoutSelectPage()
{
}

bool PpCalendarA5LayoutSelectPage::HasPrePage()
{
	return true;
}

bool PpCalendarA5LayoutSelectPage::HasNextPage()
{
	return true;
}


bool PpCalendarA5LayoutSelectPage::getTitle(QString &title)
{
	title = tr("Calendar A5 - Choose your base layout");
	return true;
}




PpCalendar4x6LayoutSelectPage::PpCalendar4x6LayoutSelectPage(PhotoPrintPrjModel* model):PpBaseSelectPage(model)
{
	PRJ_DIR_ITM diritm;
	diritm.nextPage = NULL;

	diritm.index=0;
	diritm.name = tr("Layout 1");
	diritm.iconPath = "";
	diritm.showPicPath = "Resources/images/Calendar4x6_show.png";
	diritm.dirtype= PP_LAYOUT_CALENDAR_4X6_L1_NAME;
	diritm.nextPage = new PpCalendarYearSelectPage(_model);
	diritm.nextPage->setPrePage(this);
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Layout 2");
	diritm.iconPath = "";
	diritm.showPicPath = "Resources/images/Calendar4x6_l2_show.png";
	diritm.dirtype= PP_LAYOUT_CALENDAR_4X6_L2_NAME;
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Layout 3");
	diritm.showPicPath = "Resources/images/Calendar4x6_l3_show.png";
	diritm.dirtype= PP_LAYOUT_CALENDAR_4X6_L3_NAME;
	_diritmslst.push_back(diritm);

	diritm.index++;
	diritm.name = tr("Layout 4");
	diritm.showPicPath = "Resources/images/Calendar4x6_l4_show.png";
	diritm.dirtype= PP_LAYOUT_CALENDAR_4X6_L4_NAME;
	_diritmslst.push_back(diritm);

}
PpCalendar4x6LayoutSelectPage::~PpCalendar4x6LayoutSelectPage()
{
}

bool PpCalendar4x6LayoutSelectPage::HasPrePage()
{
	return true;
}

bool PpCalendar4x6LayoutSelectPage::HasNextPage()
{
	return true;
}


bool PpCalendar4x6LayoutSelectPage::getTitle(QString &title)
{
	title = tr("Calendar 4x6\" - Choose your base layout");
	return true;
}





	

PpCalendarYearSelectPage::PpCalendarYearSelectPage(PhotoPrintPrjModel* model):PpBaseSelectPage(model)
{
	PRJ_DIR_ITM diritm;
	diritm.nextPage = NULL;

        QDate curdate = QDate::currentDate();
        int year = curdate.year();

	diritm.index=0;
        diritm.name = tr("%1").arg(year++);
	diritm.iconPath = "";
	//diritm.showPicPath = "Resources/images/Pocket4x3_show.png";
	diritm.dirtype= PP_CALENDAR_YEAR;
	_diritmslst.push_back(diritm);

	diritm.index++;
        diritm.name = tr("%1").arg(year++);
	diritm.iconPath = "";
	_diritmslst.push_back(diritm);

	diritm.index++;
        diritm.name = tr("%1").arg(year++);
	_diritmslst.push_back(diritm);

	diritm.index++;
        diritm.name = tr("%1").arg(year++);
	_diritmslst.push_back(diritm);

	diritm.index++;
        diritm.name = tr("%1").arg(year++);
	_diritmslst.push_back(diritm);

}
PpCalendarYearSelectPage::~PpCalendarYearSelectPage()
{
}

bool PpCalendarYearSelectPage::HasPrePage()
{
	return true;
}

bool PpCalendarYearSelectPage::HasNextPage()
{
	return false;
}


bool PpCalendarYearSelectPage::getTitle(QString &title)
{
	title = tr("Please select the desired year");
	return true;
}

