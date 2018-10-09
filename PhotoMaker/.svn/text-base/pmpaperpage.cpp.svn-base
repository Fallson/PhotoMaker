#include "PmPaperPage.h"
#include "pmphotomakerdoc.h"
#include <QColorDialog>


extern QString gbires;

PmPageItm::PmPageItm(QObject *parent): 
QObject(parent), _pPage(NULL),_photoitm(NULL),
	_itmType(IMG_ITM), _previewphotoitm(NULL),
	_angel(0),_ratio(1),_imglefttop(-1,-1),_bkcolor(Qt::white)
{
}

PmPageItm::PmPageItm(PmPageItm &pageitm)
{
	_layoutbox = pageitm._layoutbox;
	_pPage = NULL; // should be set later

	_cnt = pageitm._cnt;
	_angel = pageitm._angel;
	_ratio = pageitm._ratio;
	_imglefttop = pageitm._imglefttop;
	_bkcolor = pageitm._bkcolor;


	_photoitm = NULL; // will be sate when this item is showed on ui
	_previewphotoitm = NULL;// will be sate when this item is showed on ui

	_itmType = pageitm._itmType;

	_pixmap = pageitm._pixmap;

	// copy calendar props
	_year = pageitm._year;
	_month = pageitm._month;
	_calcfg = pageitm._calcfg;
	_wdcfg = pageitm._wdcfg;
	_monthyearcfg = pageitm._monthyearcfg;
}


PmPageItm::~PmPageItm()
{
}


bool PmPageItm::getRectInPage(LayoutBoxPos &rect)
{
	rect = _layoutbox;
	return true;
}

bool PmPageItm::setRectInPage(const LayoutBoxPos &rect)
{
	_layoutbox = rect;
	return true;
}


bool PmPageItm::setContent(const QString &cnt)
{

	_cnt = cnt;
	return true;
}

bool PmPageItm::getContent(QString &cnt)
{
	cnt = _cnt;
	return true;
}




bool PmPageItm::setPage(PmPhotoPage *page)
{
	_pPage = page;
	return true;
}

PmPhotoPage * PmPageItm::getPage()
{
	return _pPage;
}


bool PmPageItm::setRotate(int angel)
{
	_angel = angel;
	return true;
}
bool PmPageItm::getRotate(int &angel)
{
	angel = _angel;
	return true;
}
bool PmPageItm::setZoom(qreal value)
{
	_ratio = value;
	return true;
}

bool PmPageItm::getZoom(qreal &value)
{
	value = _ratio;
	return true;
}



PmPhotoPage::PmPhotoPage(QObject *parent)
	: QObject(parent), _pPaperPage(NULL),
	_scaleratio(0), _isleft(true), _hasborder(true),_pBkViewItm(NULL)
{
	//
	_pos.x = 0;
	_pos.y = 0;
	_pos.height = 1;
	_pos.width = 1;

	setLayout(PP_LAYOUT_FULLSIZE_SINGLE, _hasborder, _isleft);
}

PmPhotoPage::PmPhotoPage(PmPhotoPage &srcpage)
{
	_layout = srcpage._layout;
	_pPaperPage = NULL; // should be set later
	_pos = srcpage._pos;
	_scaleratio = srcpage._scaleratio;
	_isleft = srcpage._isleft;
	_hasborder = srcpage._hasborder;


	QList<PmPageItm *>::iterator it;
	for (it=srcpage._pagepicitmlst.begin(); it!=srcpage._pagepicitmlst.end(); it++ )
	{
		PmPageItm *pageitm = new PmPageItm(**it);
		pageitm->setPage(this);
		_pagepicitmlst.push_back(pageitm);
	}
	//return true;
}

PmPhotoPage::~PmPhotoPage()
{

}



//
// when a new layout is set, it create a new PmPageItm list.
// then check if old items can be copied into the new one
// at last, it delete the old items.
//
bool PmPhotoPage::setLayout(PHOTO_LAYOUT layout, bool hasborder,bool left, bool adjustlayout)
{
	//
	_layout = layout;
	if ( !adjustlayout )
	{
		return true;
	}

	PPLayout &ly = PPLayoutMgr::getInst().getLayout(layout);
	QList<LayoutBoxPos> layoutboxes;
	ly.getLayout(layoutboxes,hasborder, left);

	int cnt = layoutboxes.size();
	
	QList<PmPageItm *> oldpageitms;
	oldpageitms = _pagepicitmlst;
	_pagepicitmlst.clear();
	int i=0;
	for( QList<LayoutBoxPos>::iterator it=layoutboxes.begin(); it!=layoutboxes.end(); it++, i++ )
	{
		PmPageItm *pOldPageItm = NULL;
		if ( i<oldpageitms.size() )
		{
			pOldPageItm = oldpageitms.at(i);
		}
		PmPageItm *pPicItm = new PmPageItm(this);
		if ( pOldPageItm)
		{
			if ( (*it).type == CalType )
			{
				//
				pPicItm->setPhotoItmType(PmPageItm::CALENDAR_ITM);
				CALENDAR_CFG calcfg;
				pOldPageItm->getCalProps(calcfg.calcfg);
				pOldPageItm->getWdsProps(calcfg.wdcfg);
				pOldPageItm->getMonthYearProps(calcfg.monthyearcfg);
				pPicItm->setCalProps(calcfg.calcfg);
				pPicItm->setWdsProps(calcfg.wdcfg);
				pPicItm->setMonthYearProps(calcfg.monthyearcfg);
				int year = 0, mon = 0;
				pOldPageItm->getMonth(year, mon);
				pPicItm->setMonth(year, mon);
			}
			else
			{
				pPicItm->setPhotoItmType(PmPageItm::IMG_ITM);

				QString imgpath;
				pOldPageItm->getContent(imgpath);
				pPicItm->setContent(imgpath);
				QPixmap *pixmap = pOldPageItm->getPixmap();
				if ( pixmap )
				{
					pPicItm->setPixmap(*pixmap);
				}
			}
		}
		else
		{
			if ( (*it).type == CalType )
			{
				//
				pPicItm->setPhotoItmType(PmPageItm::CALENDAR_ITM);
			}
			else
			{
				pPicItm->setPhotoItmType(PmPageItm::IMG_ITM);
			}
		}
		pPicItm->setPage(this);
		pPicItm->setRectInPage(*it);
		_pagepicitmlst.append(pPicItm);
	}

	return true;
}

bool PmPhotoPage::getPicItms(QList<PmPageItm*> &picitmlst)
{
	picitmlst = _pagepicitmlst;
	return true;
}

bool PmPhotoPage::setPicItms(const QList<PmPageItm *> &picitmlst)
{
	_pagepicitmlst = picitmlst;
	return true;
}


bool PmPhotoPage::getPagePosInPaper(LayoutBoxPos &pagepos)
{
	pagepos = _pos;

	return true;
}

bool PmPhotoPage::setPagePosInPaper(LayoutBoxPos &pagepos)
{
	_pos= pagepos ;

	return true;
}

void PmPhotoPage::reversePagePos()
{
	this->_isleft = !_isleft;
	LayoutBoxPos oldpos = _pos;
	if ( oldpos.x == 0 )
	{
		_pos.x = 0.5;
	}
	else
	{
		_pos.x = 0;
	}
	//_pos.margin.left = oldpos.margin.right;
	//_pos.margin.right = oldpos.margin.left;
	//PHOTO_LAYOUT ly = this->getLayout();
	//this->setLayout(ly, this->hasBorder(), _isleft);

}

class FullSizeSingleLayout: public PPLayout
{
public:
	FullSizeSingleLayout(){}
	~FullSizeSingleLayout(){}
public:
	virtual bool getLayout(QList<LayoutBoxPos> &layoutboxes,bool hasborder, bool left);
};

bool FullSizeSingleLayout::getLayout(QList<LayoutBoxPos> &layoutboxes,bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;
	layoutbox.height = 1;
	layoutbox.width = 1;
	layoutbox.x = 0;
	layoutbox.y = 0;

	layoutboxes.clear();
	layoutboxes.push_back(layoutbox);
	return true;
}


class FullSizeSinglePanLayout: public PPLayout
{
public:
	FullSizeSinglePanLayout(){}
	~FullSizeSinglePanLayout(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes,bool hasborder, bool left);
};

bool FullSizeSinglePanLayout::getLayout(QList<LayoutBoxPos> &layoutboxes,bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;
	layoutbox.height = 1;
	layoutbox.width = 1;
	layoutbox.x = 0;
	layoutbox.y = 0;

	layoutboxes.clear();
	layoutboxes.push_back(layoutbox);
	//layoutbox.x = 0.5;
	//layoutboxes.push_back(layoutbox);

	return true;
}


class BorderSingleLayout: public PPLayout
{
public:
	BorderSingleLayout(){}
	~BorderSingleLayout(){}
public:
	virtual bool getLayout(QList<LayoutBoxPos> &layoutboxes,bool hasborder, bool left);
};

bool BorderSingleLayout::getLayout(QList<LayoutBoxPos> &layoutboxes,bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;
	layoutbox.height = 1-0.054545455*2;
	layoutbox.width = 1-0.072874493927*2;
	//layoutbox.margin.top = layoutbox.margin.bottom = 0.054545455;
	//layoutbox.margin.left = layoutbox.margin.right = 0.072874493927;
	layoutbox.x = 0.072874493927;
	layoutbox.y = 0.054545455;

	layoutboxes.clear();
	layoutboxes.push_back(layoutbox);
	return true;
}


class BorderSinglePanLayout: public PPLayout
{
public:
	BorderSinglePanLayout(){}
	~BorderSinglePanLayout(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes,bool hasborder, bool left);
};

bool BorderSinglePanLayout::getLayout(QList<LayoutBoxPos> &layoutboxes,bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;
	layoutbox.height = 1-0.054545455*2;
	layoutbox.width = 1-0.072874493927;
	//layoutbox.margin.top = layoutbox.margin.bottom = 0.054545455;
	if ( left )
	{
		layoutbox.x = 0.072874493927;
	}
	else
	{
		layoutbox.x = 0;
	}
	layoutbox.y = 0.054545455;

	layoutboxes.clear();
	layoutboxes.push_back(layoutbox);
	return true;

}

class TestLayout: public PPLayout
{
public:
	TestLayout(){}
	~TestLayout(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes);
};

bool TestLayout::getLayout(QList<LayoutBoxPos> &layoutboxes)
{
	LayoutBoxPos layoutbox;
	layoutbox.height = 1;
	layoutbox.width = 0.5;
	layoutbox.x = 0;
	layoutbox.y = 0;

	layoutboxes.clear();
	layoutboxes.push_back(layoutbox);
	layoutbox.x  = 0.5;
	layoutboxes.push_back(layoutbox);

	return true;
}


class LY8X5Base: public PPLayout
{
public:
	LY8X5Base();
	~LY8X5Base(){}

protected:
	qreal _hspan,_vspan;

	LayoutBoxPos imgLayout; // this will control the border of the all imgs
};

LY8X5Base::LY8X5Base()
{
	imgLayout.x = 0;
	imgLayout.y = 0;
	imgLayout.width = 1;
	imgLayout.height = 1;
	imgLayout.margin.top = 0;
	imgLayout.margin.left = 0;
	imgLayout.margin.right = 0;
	imgLayout.margin.bottom = 0;
}


class LY8X5FullSizeA: public LY8X5Base
{
public:
	LY8X5FullSizeA(){}
	~LY8X5FullSizeA(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder,bool left);
};

bool LY8X5FullSizeA::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	{
		layoutbox.height = 0.5;
		layoutbox.width = 1;
		layoutbox.x = 0;
		layoutbox.y = 0;
		layoutbox.margin.left = 0;
		layoutbox.margin.right = 0;
		layoutbox.margin.top = 0;
		layoutbox.margin.bottom = 0.0079;

		layoutboxes.clear();
		layoutboxes.push_back(layoutbox);
		layoutbox.y = 0.5;
		layoutbox.margin.bottom = 0;
		layoutbox.margin.top = 0.0079;

		//layoutbox.margin.left = border;
		//layoutbox.margin.right = 0.038;
		layoutboxes.push_back(layoutbox);
	}


	return true;
}


class LY8X5FullSizeB: public LY8X5Base
{
public:
	LY8X5FullSizeB(){}
	~LY8X5FullSizeB(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5FullSizeB::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

		layoutbox.height = 1;
		layoutbox.width = 1;
		layoutbox.x = 0;
		layoutbox.y = 0;
		layoutbox.margin.left = 0;
		layoutbox.margin.right = 0;
		layoutbox.margin.top = 0;
		layoutbox.margin.bottom = 0;

	layoutboxes.clear();
	layoutboxes.push_back(layoutbox);
	return true;
}



class LY8X5FullSizeC: public LY8X5Base
{
public:
	LY8X5FullSizeC():LY8X5Base(){}
	~LY8X5FullSizeC(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5FullSizeC::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	layoutboxes.clear();

	LayoutBoxPos layoutbox;

	//if ( left )
	{
		layoutbox.height = 0.5;
		layoutbox.width = 0.5;
		layoutbox.x = 0;
		layoutbox.y = 0;
		layoutbox.margin.left = 0;
		layoutbox.margin.top = 0;
		layoutbox.margin.bottom = 0.0079;
		layoutbox.margin.right = 0.01119;
		layoutboxes.push_back(layoutbox);

		layoutbox.height = 0.5;
		layoutbox.width = 0.5;
		layoutbox.x = 0.5;
		layoutbox.y = 0;
		layoutbox.margin.left = 0.01119;
		layoutbox.margin.top = 0;
		layoutbox.margin.bottom = 0.0079;
		layoutbox.margin.right = 0;
		layoutboxes.push_back(layoutbox);

		layoutbox.width =1;
		layoutbox.x = 0;
		layoutbox.y = 0.5;
		layoutbox.margin.bottom = 0;
		layoutbox.margin.top = 0.0079;
		layoutbox.margin.left = 0;
		layoutbox.margin.right = 0;
		layoutboxes.push_back(layoutbox);
	}

	return true;
}

class LY8X5FullSizeD: public LY8X5Base
{
public:
	LY8X5FullSizeD(){}
	~LY8X5FullSizeD(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5FullSizeD::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	layoutboxes.clear();

	LayoutBoxPos layoutbox;

	{
		layoutbox.height = 0.5;
		layoutbox.width = 0.5;
		layoutbox.x = 0;
		layoutbox.y = 0;
		layoutbox.margin.left = 0;
		layoutbox.margin.top = 0;
		layoutbox.margin.bottom = 0.0079;
		layoutbox.margin.right = 0.01119;
		layoutboxes.push_back(layoutbox);

		layoutbox.height = 0.5;
		layoutbox.width = 0.5;
		layoutbox.x = 0.5;
		layoutbox.y = 0;
		layoutbox.margin.left = 0.01119;
		layoutbox.margin.top = 0;
		layoutbox.margin.bottom = 0.0079;
		layoutbox.margin.right = 0;
		layoutboxes.push_back(layoutbox);



		layoutbox.width =0.5;
		layoutbox.x = 0;
		layoutbox.y = 0.5;
		layoutbox.margin.bottom = 0;
		layoutbox.margin.top = 0.0079;
		layoutbox.margin.left = 0;
		layoutbox.margin.right = 0.01119;
		layoutboxes.push_back(layoutbox);

		layoutbox.width =0.5;
		layoutbox.x = 0.5;
		layoutbox.y = 0.5;
		layoutbox.margin.bottom = 0;
		layoutbox.margin.top = 0.0079;
		layoutbox.margin.left = 0.01119;
		layoutbox.margin.right = 0;
		layoutboxes.push_back(layoutbox);
	}

	return true;
}

class LY8X5FullSizePanor: public LY8X5Base
{
public:
	LY8X5FullSizePanor(){}
	~LY8X5FullSizePanor(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5FullSizePanor::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.height = 1;
	layoutbox.width = 1;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutbox.margin.left = 0/2;
	layoutbox.margin.right = 0/2;
	layoutbox.margin.top = 0;
	layoutbox.margin.bottom = 0;

	layoutboxes.push_back(layoutbox);

	return true;
}

//////////////////////////


class LY8X5TraditionA: public LY8X5Base
{
public:
	LY8X5TraditionA(){}
	~LY8X5TraditionA(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5TraditionA::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	qreal border = 0;
	if ( hasborder )
	{
		//border = 0.0308;
	}
	
	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;

	layoutboxes.clear();
	if ( left )
	{
		layoutbox.height = 0.45779;
		layoutbox.width = 0.97;

		layoutbox.x = 0.03;
		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

		layoutbox.y = 0.51136364;
		layoutboxes.push_back(layoutbox);
	}
	else
	{
		layoutbox.height = 0.45779;
		layoutbox.width = 0.97;

		layoutbox.x = 0;
		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

		layoutbox.y = 0.51136364;
		layoutboxes.push_back(layoutbox);
	}

	return true;
}


class LY8X5TraditionB: public LY8X5Base
{
public:
	LY8X5TraditionB(){}
	~LY8X5TraditionB(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5TraditionB::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;
	qreal border = 0;
	if ( hasborder )
	{
		border = 0.0308;
	}

	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;
	layoutboxes.clear();
	if ( left )
	{
		layoutbox.height = 0.9383;
		layoutbox.width = 0.97;
		layoutbox.x = 0.03;
		layoutbox.y = 0.0324675;
	}
	else
	{
		layoutbox.height = 0.9383;
		layoutbox.width = 0.97;

		layoutbox.x = 0;
		layoutbox.y = 0.0324675;
	}

	layoutboxes.push_back(layoutbox);
	return true;
}



class LY8X5TraditionC: public LY8X5Base
{
public:
	LY8X5TraditionC(){}
	~LY8X5TraditionC(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5TraditionC::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	layoutboxes.clear();

	LayoutBoxPos layoutbox;
	qreal border = 0;
	if ( hasborder )
	{
		//border = 0.0308;
	}

	
	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;

	layoutboxes.clear();
	if ( left )
	{
		layoutbox.height = 0.458119;
		layoutbox.width = 0.46311;

		layoutbox.x = 0.03;
		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0.507556;
		layoutbox.x += 0.03;		
		layoutboxes.push_back(layoutbox);

		layoutbox.height = 0.45779;
		layoutbox.width = 0.97;
		layoutbox.x = 0.03;
		layoutbox.y = 0.51136364;
		layoutboxes.push_back(layoutbox);
	}
	else
	{
		layoutbox.height = 0.458119;
		layoutbox.width = 0.46311;
		layoutbox.x = 0;
		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0.5057399;
		layoutbox.x += 0;
		layoutboxes.push_back(layoutbox);

		layoutbox.height = 0.45779;
		layoutbox.width = 0.97;

		layoutbox.x = 0;
		layoutbox.y = 0.51136364;
		layoutboxes.push_back(layoutbox);
	}
	return true;
}

class LY8X5TraditionD: public LY8X5Base
{
public:
	LY8X5TraditionD(){}
	~LY8X5TraditionD(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5TraditionD::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	layoutboxes.clear();

	LayoutBoxPos layoutbox;
	qreal border = 0;
	if ( hasborder )
	{
		//border = 0.0308;
	}
	
	
	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;

	layoutboxes.clear();
	if ( left )
	{
		layoutbox.height = 0.458119;
		layoutbox.width = 0.46311;

		layoutbox.x = 0.03;
		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0.507556;
		layoutbox.x += 0.03;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0;
		layoutbox.x += 0.03;
		layoutbox.y = 0.51136364;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0.507556;
		layoutbox.x += 0.03;
		layoutbox.y = 0.51136364;
		layoutboxes.push_back(layoutbox);
	}
	else
	{

		layoutbox.height = 0.458119;
		layoutbox.width = 0.46311;
		layoutbox.x = 0;
		layoutbox.x += 0;
		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0.5057399;
		layoutbox.x += 0;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0;
		layoutbox.x += 0;
		layoutbox.y = 0.51136364;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0.5057399;
		layoutbox.x += 0;
		layoutboxes.push_back(layoutbox);
	}
	return true;
}
class LY8X5TraditionPanor: public LY8X5Base
{
public:
	LY8X5TraditionPanor(){}
	~LY8X5TraditionPanor(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5TraditionPanor::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;
	qreal border = 0;
	if ( hasborder )
	{
		border = 0.0308;
	}

	layoutboxes.clear();
	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;
	layoutbox.height = 0.9383;


	// parorama is speical, the border is narrow than others
	qreal panoramaadjust = 0.025;
	if ( !hasborder )
	{
		panoramaadjust = 0;
	}

	layoutbox.width = 0.97 + panoramaadjust;
	layoutbox.y = 0.0324675;
	if ( left )
	{
		layoutbox.x += 0.03;
	}
	else
	{
		layoutbox.x = 0-panoramaadjust;
	}


	layoutboxes.push_back(layoutbox);
	return true;
}
// horizon


class LY8X5HorizonA: public LY8X5Base
{
public:
	LY8X5HorizonA(){}
	~LY8X5HorizonA(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5HorizonA::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	qreal border = 0;
	if ( hasborder )
	{
		//border = 0.0308;
	}
	
	layoutboxes.clear();
	
	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;
	
	if ( left )
	{
		layoutbox.height = 0.3393756294;
		layoutbox.width = 0.97;
		layoutbox.x = 0;
		layoutbox.x += 0.03;

		layoutbox.y = 0.154;
		layoutboxes.push_back(layoutbox);

		layoutbox.y = 0.50654582;
		layoutboxes.push_back(layoutbox);
	}
	else
	{
		layoutbox.height = 0.3393756294;
		layoutbox.width = 0.97;
		layoutbox.x = 0;
		layoutbox.x += 0;

		layoutbox.y = 0.154;
		layoutboxes.push_back(layoutbox);

		layoutbox.y = 0.50654582;
		layoutboxes.push_back(layoutbox);
	}

	return true;
}


class LY8X5HorizonB: public LY8X5Base
{
public:
	LY8X5HorizonB(){}
	~LY8X5HorizonB(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5HorizonB::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	qreal border = 0;
	if ( hasborder )
	{
		//border = 0.0308;
	}
	
	layoutboxes.clear();
	
	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;
	
	if ( left )
	{
		layoutbox.height = 0.69184;
		layoutbox.width = 0.97;
		layoutbox.x = 0;
		layoutbox.x += 0.03;
		layoutbox.y = 0.154;
	}
	else
	{
		layoutbox.height = 0.69184;
		layoutbox.width = 0.97;
		layoutbox.x = 0;
		layoutbox.y = 0.154;
	}
	layoutboxes.push_back(layoutbox);

	return true;
}



class LY8X5HorizonC: public LY8X5Base
{
public:
	LY8X5HorizonC(){}
	~LY8X5HorizonC(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5HorizonC::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;
	qreal border = 0;
	if ( hasborder )
	{
		//border = 0.0308;
	}
	layoutboxes.clear();

	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;

	if ( left )
	{
		layoutbox.height = 0.3393756294;
		layoutbox.width = 0.46311;
		layoutbox.x = 0;
		layoutbox.x += 0.03;
		layoutbox.y = 0.154;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0.507556;
		layoutbox.x += 0.03;
		layoutboxes.push_back(layoutbox);

		layoutbox.width = 0.97;
		layoutbox.x = 0;
		layoutbox.x += 0.03;
		layoutbox.y = 0.50654582;
		layoutboxes.push_back(layoutbox);
	}
	else
	{
		layoutbox.height = 0.3393756294;
		layoutbox.width = 0.46311;
		layoutbox.x = 0;
		layoutbox.y = 0.154;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0.5057399;
		layoutboxes.push_back(layoutbox);

		layoutbox.width = 0.97;
		layoutbox.x = 0;
		layoutbox.y = 0.50654582;
		layoutboxes.push_back(layoutbox);
	}
	return true;
}

class LY8X5HorizonD: public LY8X5Base
{
public:
	LY8X5HorizonD(){}
	~LY8X5HorizonD(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5HorizonD::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;
	qreal border = 0;
	if ( hasborder )
	{
		//border = 0.0308;
	}
	layoutboxes.clear();

	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;

	if ( left )
	{
		layoutbox.height = 0.69184;
		layoutbox.width = 0.46311;
		layoutbox.x = 0;
		layoutbox.x += 0.03;
		layoutbox.y = 0.154;
		layoutboxes.push_back(layoutbox);

		layoutbox.height = 0.3393756294;
		layoutbox.x = 0.507556;
		layoutbox.x += 0.03;
		layoutboxes.push_back(layoutbox);

		layoutbox.y = 0.50654582;
		layoutboxes.push_back(layoutbox);

	}
	else
	{
		layoutbox.height = 0.69184;
		layoutbox.width = 0.46311;
		layoutbox.x = 0;
		layoutbox.y = 0.154;
		layoutboxes.push_back(layoutbox);

		layoutbox.height = 0.3393756294;
		layoutbox.x = 0.5057399;
		layoutboxes.push_back(layoutbox);

		layoutbox.y = 0.50654582;
		layoutboxes.push_back(layoutbox);
	}
	return true;
}


class LY8X5HorizonE: public LY8X5Base
{
public:
	LY8X5HorizonE(){}
	~LY8X5HorizonE(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5HorizonE::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;
	qreal border = 0;
	if ( hasborder )
	{
		//border = 0.0308;
	}
	layoutboxes.clear();

	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;

	if ( left )
	{
		layoutbox.height = 0.3393756294;
		layoutbox.width = 0.46311;
		layoutbox.x = 0;
		layoutbox.x += 0.03;
		layoutbox.y = 0.154;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0.507556;
		layoutbox.x += 0.03;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0;
		layoutbox.x += 0.03;
		layoutbox.y = 0.50654582;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0.507556;
		layoutbox.x += 0.03;
		layoutboxes.push_back(layoutbox);

	}
	else
	{
		layoutbox.height = 0.3393756294;
		layoutbox.width = 0.46311;
		layoutbox.x = 0;
		layoutbox.y = 0.154;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0.5057399;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0;
		layoutbox.y = 0.50654582;
		layoutboxes.push_back(layoutbox);

		layoutbox.x = 0.5057399;
		layoutboxes.push_back(layoutbox);

	}
	return true;
}

class LY8X5HorizonPanor: public LY8X5Base
{
public:
	LY8X5HorizonPanor(){}
	~LY8X5HorizonPanor(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5HorizonPanor::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.bottom = 0;


	// parorama is speical, the border is narrow than others
	qreal panoramaadjust = 0.025;
	if ( !hasborder )
	{
		panoramaadjust = 0;
	}

	layoutbox.y =  0.154;
	layoutbox.height = 0.69184;
	layoutbox.width = 0.97;
	layoutbox.width += panoramaadjust;
	if ( left )
	{
		layoutbox.x = 0;
		layoutbox.x += 0.03;

	}
	else
	{
		layoutbox.x = 0;
		layoutbox.x -= panoramaadjust;
	}
	layoutboxes.push_back(layoutbox);

	return true;
}


//verticon

class LY8X5VerticonA: public LY8X5Base
{
public:
	LY8X5VerticonA(){}
	~LY8X5VerticonA(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5VerticonA::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	qreal border = 0;
	if ( hasborder )
	{
		//border = 0.0308;
	}
	layoutboxes.clear();

	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;

	if ( left )
	{
		layoutbox.height = 0.45779;
		layoutbox.width = 0.76;
		layoutbox.x = 0.21;
		layoutbox.x += 0.03;
		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

		layoutbox.y = 0.51136364;
		layoutboxes.push_back(layoutbox);
	}
	else
	{
		layoutbox.height = 0.45779;
		layoutbox.width = 0.76;
		layoutbox.x = 0;
		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

		layoutbox.y = 0.51136364;
		layoutboxes.push_back(layoutbox);

	}

	return true;
}


class LY8X5VerticonB: public LY8X5Base
{
public:
	LY8X5VerticonB(){}
	~LY8X5VerticonB(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5VerticonB::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	qreal border = 0;
	if ( hasborder )
	{
		//border = 0.0308;
	}
	layoutboxes.clear();

	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;

	if ( left )
	{
		layoutbox.height = 0.9383;
		layoutbox.width = 0.76;
		layoutbox.x = 0.21;
		layoutbox.x += 0.03;
		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

	}
	else
	{
		layoutbox.height = 0.9383;
		layoutbox.width = 0.76;
		layoutbox.x = 0;
		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

	}
	return true;
}



class LY8X5VerticonC: public LY8X5Base
{
public:
	LY8X5VerticonC(){}
	~LY8X5VerticonC(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5VerticonC::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	qreal border = 0;
	if ( hasborder )
	{
		//border = 0.0308;
	}
	layoutboxes.clear();

	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;

	if ( left )
	{
		layoutbox.height = 0.303116;
		layoutbox.width = 0.76;
		layoutbox.x = 0.21;
		layoutbox.x += 0.03;
		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

		layoutbox.height = 0.621813;
		layoutbox.y = 0.34844;
		layoutboxes.push_back(layoutbox);

	}
	else
	{
		layoutbox.height = 0.303116;
		layoutbox.width = 0.76;
		layoutbox.x = 0;


		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

		layoutbox.height = 0.621813;
		layoutbox.y = 0.34844;
		layoutboxes.push_back(layoutbox);

	}

	return true;
}

class LY8X5VertcionD: public LY8X5Base
{
public:
	LY8X5VertcionD(){}
	~LY8X5VertcionD(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5VertcionD::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	qreal border = 0;
	if ( hasborder )
	{
		//border = 0.0308;
	}
	layoutboxes.clear();

	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;

	if ( left )
	{
		layoutbox.height = 0.303116;
		layoutbox.width = 0.76;
		layoutbox.x = 0.21;
		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

		layoutbox.y = 0.34844;
		layoutboxes.push_back(layoutbox);

		layoutbox.y = 0.6671388;
		layoutboxes.push_back(layoutbox);

	}
	else
	{
		layoutbox.height = 0.303116;
		layoutbox.width = 0.76;
		layoutbox.x = 0;

		layoutbox.y = 0.0324675;
		layoutboxes.push_back(layoutbox);

		layoutbox.y = 0.34844;
		layoutboxes.push_back(layoutbox);

		layoutbox.y = 0.6671388;
		layoutboxes.push_back(layoutbox);

	}


	return true;
}

class LY8X5VertcionPanor: public LY8X5Base
{
public:
	LY8X5VertcionPanor(){}
	~LY8X5VertcionPanor(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY8X5VertcionPanor::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	qreal border = 0;
	if ( hasborder )
	{
		//border = 0.0308;
	}		

	layoutboxes.clear();

	layoutbox.margin.left = 0; //border;
	layoutbox.margin.right = 0; //0.0298 + border;
	layoutbox.margin.top = 0; //0.064935;
	layoutbox.margin.bottom = 0; //0.01948;

	// parorama is speical, the border is narrow than others
	qreal panoramaadjust = 0.025;
	if ( !hasborder )
	{
		panoramaadjust = 0;
	}

	layoutbox.height = 0.9383;
	layoutbox.y = 0.0324675;

	layoutbox.width = 0.76;
	layoutbox.width += panoramaadjust;
	if ( left )
	{
		layoutbox.x = 0.21;
		layoutbox.x += 0.03;
	}
	else
	{
		layoutbox.x = 0;
		layoutbox.x -= panoramaadjust;
	}
	layoutboxes.push_back(layoutbox);


	return true;
}


class LYA4CalL1And1: public PPLayout
{
public:
	LYA4CalL1And1(){}
	~LYA4CalL1And1(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL1And1::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.70152;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutbox.margin.left = 0.1228;
	layoutbox.margin.top = 0.1228;
	layoutbox.margin.right = 0.1228;
	layoutbox.margin.bottom = 0.0691;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 1;
	layoutbox.height = 0.29848 + 0.001; // in order to cover the bottom line, add additional 0.001
	layoutbox.x = 0.001;
	layoutbox.y = 0.70152;
	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;
	layoutboxes.push_back(layoutbox);

	return true;

}


class LYA4CalL1And2: public PPLayout
{
public:
	LYA4CalL1And2(){}
	~LYA4CalL1And2(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL1And2::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.70152;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutbox.margin.left = 0.1228;
	layoutbox.margin.top = 0.1228;
	layoutbox.margin.right = 0.1228;
	layoutbox.margin.bottom = 0.0691;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.5;
	layoutbox.height = 0.29848+ 0.001;
	layoutbox.x = 0.001;
	layoutbox.y = 0.70152;
	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.5+0.001;
	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;
	layoutboxes.push_back(layoutbox);

	return true;
}



class LYA4CalL1And3: public PPLayout
{
public:
	LYA4CalL1And3(){}
	~LYA4CalL1And3(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL1And3::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.70152;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutbox.margin.left = 0.1228;
	layoutbox.margin.top = 0.1228;
	layoutbox.margin.right = 0.1228;
	layoutbox.margin.bottom = 0.0691;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.3333;
	layoutbox.height = 0.29848+ 0.001;
	layoutbox.x = 0+0.001;
	layoutbox.y = 0.70152;
	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.width = 0.3333;
	layoutbox.x = 0.3333+0.001;
	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.6667+0.001;
	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;
	layoutboxes.push_back(layoutbox);

	return true;
}




class LYA4CalL1And4: public PPLayout
{
public:
	LYA4CalL1And4(){}
	~LYA4CalL1And4(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL1And4::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.70152;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutbox.margin.left = 0.1228;
	layoutbox.margin.top = 0.1228;
	layoutbox.margin.right = 0.1228;
	layoutbox.margin.bottom = 0.0691;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.6667;
	layoutbox.height = 0.29848+ 0.001;
	layoutbox.x = 0+0.001;
	layoutbox.y = 0.70152;
	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.width = 0.3333;
	layoutbox.x = 0.6667+0.001;
	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;
	layoutboxes.push_back(layoutbox);

	return true;
}



class LYA4CalL2And1: public PPLayout
{
public:
	LYA4CalL2And1(){}
	~LYA4CalL2And1(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL2And1::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.27304;
	layoutbox.x = 0;
	layoutbox.y = 0.7321739 ;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 1;
	layoutbox.height = 0.716521739;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	return true;
}



class LYA4CalL2And2: public PPLayout
{
public:
	LYA4CalL2And2(){}
	~LYA4CalL2And2(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL2And2::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.27304;
	layoutbox.x = 0;
	layoutbox.y = 0.7321739 ;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 0.481971;
	layoutbox.height = 0.347826;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.518;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0;
	layoutbox.y = 0.3669565;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.518;
	layoutbox.y = 0.3669565;
	layoutboxes.push_back(layoutbox);




	return true;
}


class LYA4CalL2And3: public PPLayout
{
public:
	LYA4CalL2And3(){}
	~LYA4CalL2And3(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL2And3::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.27304;
	layoutbox.x = 0;
	layoutbox.y = 0.7321739 ;
	layoutboxes.push_back(layoutbox);



	layoutbox.type = ImgType;
	layoutbox.width = 1;
	layoutbox.height = 0.48173913;
	layoutbox.x = 0;
	layoutbox.y = 0.1165217;
	layoutboxes.push_back(layoutbox);


	return true;
}



class LYA4CalL2And4: public PPLayout
{
public:
	LYA4CalL2And4(){}
	~LYA4CalL2And4(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL2And4::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;


	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.27304;
	layoutbox.x = 0;
	layoutbox.y = 0.7321739 ;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 0.6586538;
	layoutbox.height = 0.716521739;
	layoutbox.x = 0.170673;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);



	return true;
}



class LYA4CalL2And5: public PPLayout
{
public:
	LYA4CalL2And5(){}
	~LYA4CalL2And5(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL2And5::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.27304;
	layoutbox.x = 0;
	layoutbox.y = 0.7321739 ;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 1;
	layoutbox.height = 0.347826;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0;
	layoutbox.y = 0.3669565;
	layoutboxes.push_back(layoutbox);



	return true;
}



class LYA4CalL2And6: public PPLayout
{
public:
	LYA4CalL2And6(){}
	~LYA4CalL2And6(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL2And6::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.27304;
	layoutbox.x = 0;
	layoutbox.y = 0.7321739 ;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 0.481971;
	layoutbox.height = 0.347826;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.518;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.width = 1;
	layoutbox.x = 0;
	layoutbox.y = 0.3669565;
	layoutboxes.push_back(layoutbox);



	return true;
}




class LYA4CalL3And1: public PPLayout
{
public:
	LYA4CalL3And1(){}
	~LYA4CalL3And1(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL3And1::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 0.9137931;
	layoutbox.height = 0.07012;
	layoutbox.x = 0.0366379;
	layoutbox.y = 0.914634;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 1;
	layoutbox.height = 0.884146;
	layoutbox.x = 0+0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	return true;
}





class LYA4CalL3And2: public PPLayout
{
public:
	LYA4CalL3And2(){}
	~LYA4CalL3And2(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL3And2::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 0.9137931;
	layoutbox.height = 0.07012;
	layoutbox.x = 0.0366379;
	layoutbox.y = 0.914634;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 1;
	layoutbox.height = 0.4375;
	layoutbox.x = 0+0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.width = 1;
	layoutbox.x = 0+0.001;
	layoutbox.y = 0.4527439;
	layoutboxes.push_back(layoutbox);

	return true;
}


class LYA4CalL3And3: public PPLayout
{
public:
	LYA4CalL3And3(){}
	~LYA4CalL3And3(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL3And3::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 0.9137931;
	layoutbox.height = 0.07012;
	layoutbox.x = 0.0366379;
	layoutbox.y = 0.914634;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.48922;
	layoutbox.height = 0.4375;
	layoutbox.x = 0+0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.51155+0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.width = 1;
	layoutbox.x = 0+0.001;
	layoutbox.y = 0.4527439;
	layoutboxes.push_back(layoutbox);


	return true;
}



class LYA4CalL3And4: public PPLayout
{
public:
	LYA4CalL3And4(){}
	~LYA4CalL3And4(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL3And4::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;


	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 0.9137931;
	layoutbox.height = 0.07012;
	layoutbox.x = 0.0366379;
	layoutbox.y = 0.914634;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 0.48922;
	layoutbox.height = 0.4375;
	layoutbox.x = 0+0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.51155+0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0+0.001;
	layoutbox.y = 0.4527439;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.51155+0.001;
	layoutbox.y = 0.4527439;
	layoutboxes.push_back(layoutbox);


	return true;
}




class LYA4CalL4And1: public PPLayout
{
public:
	LYA4CalL4And1(){}
	~LYA4CalL4And1(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL4And1::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 0.21767;
	layoutbox.height = 1;
	layoutbox.x = 0.78233;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 0.78233;
	layoutbox.height = 1;
	layoutbox.x = 0+0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	return true;
}




class LYA4CalL4And2: public PPLayout
{
public:
	LYA4CalL4And2(){}
	~LYA4CalL4And2(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL4And2::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 0.21767;
	layoutbox.height = 1;
	layoutbox.x = 0.78233;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.78233;
	layoutbox.height = 0.492378;
	layoutbox.x = 0+0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.y = 0.507622;
	layoutboxes.push_back(layoutbox);


	return true;
}



class LYA4CalL4And3: public PPLayout
{
public:
	LYA4CalL4And3(){}
	~LYA4CalL4And3(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL4And3::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 0.21767;
	layoutbox.height = 1;
	layoutbox.x = 0.78233;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 0.78233;
	layoutbox.height = 0.3246951;
	layoutbox.x = 0+0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.y = 0.339939;
	layoutboxes.push_back(layoutbox);

	layoutbox.y = 0.679878;
	layoutboxes.push_back(layoutbox);

	return true;
}




class LYA4CalL4And4: public PPLayout
{
public:
	LYA4CalL4And4(){}
	~LYA4CalL4And4(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA4CalL4And4::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 0.21767;
	layoutbox.height = 1;
	layoutbox.x = 0.78233;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.78233;
	layoutbox.height = 0.3246951;
	layoutbox.x = 0+0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.height = 0.660061;
	layoutbox.y = 0.339939;
	layoutboxes.push_back(layoutbox);


	return true;
}



class LYCalA4FontPg: public PPLayout
{
public:
	LYCalA4FontPg(bool border=false):_border(border){}
	~LYCalA4FontPg(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);

private:
	bool _border;
};


bool LYCalA4FontPg::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	if ( _border )
	{
		layoutbox.margin.left = 0.049;
		layoutbox.margin.top = 0.034985;
		layoutbox.margin.right = 0.049;
		layoutbox.margin.bottom = 0.034985;
	}
	else
	{
		layoutbox.margin.left = 0;
		layoutbox.margin.top = 0;
		layoutbox.margin.right = 0;
		layoutbox.margin.bottom = 0;
	}
	layoutbox.type = ImgType;
	layoutbox.width = 0.99;
	layoutbox.height = 0.997;
	layoutbox.x = 0.005;
	layoutbox.y = 0.005;
	layoutboxes.push_back(layoutbox);

	return true;
}



class LYCalA5FontPg: public PPLayout
{
public:
	LYCalA5FontPg(bool border=false):_border(border){}
	~LYCalA5FontPg(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);

private:
	bool _border;
};


bool LYCalA5FontPg::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	if ( _border )
	{
		layoutbox.margin.left = 0.04958677686;
		layoutbox.margin.top = 0.06976744;
		layoutbox.margin.right = 0.04958677686;
		layoutbox.margin.bottom = 0.06976744;
	}
	else
	{
		layoutbox.margin.left = 0;
		layoutbox.margin.top = 0;
		layoutbox.margin.right = 0;
		layoutbox.margin.bottom = 0;
	}
	layoutbox.type = ImgType;
	layoutbox.width = 0.99;
	layoutbox.height = 0.997;
	layoutbox.x = 0.005;
	layoutbox.y = 0.005;
	layoutboxes.push_back(layoutbox);

	return true;
}


class LYCal4x6FontPg: public PPLayout
{
public:
	LYCal4x6FontPg(bool border=false):_border(border){}
	~LYCal4x6FontPg(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);

private:
	bool _border;
};


bool LYCal4x6FontPg::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	if ( _border )
	{
		layoutbox.margin.left = 0.05116279;
		layoutbox.margin.top = 0.09593;
		layoutbox.margin.right = 0.05116279;
		layoutbox.margin.bottom = 0.03773;
	}
	else
	{
		layoutbox.margin.left = 0;
		layoutbox.margin.top = 0;
		layoutbox.margin.right = 0;
		layoutbox.margin.bottom = 0;
	}
	layoutbox.type = ImgType;
	layoutbox.width = 0.99;
	layoutbox.height = 0.997;
	layoutbox.x = 0.005;
	layoutbox.y = 0.005;
	layoutboxes.push_back(layoutbox);

	return true;
}

class LYA5CalL1And1: public PPLayout
{
public:
	LYA5CalL1And1(){}
	~LYA5CalL1And1(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL1And1::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 0.3189;
	layoutbox.height = 1;
	layoutbox.x = 0.681;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.652278;
	layoutbox.height = 1;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	return true;
}


class LYA5CalL1And2: public PPLayout
{
public:
	LYA5CalL1And2(){}
	~LYA5CalL1And2(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL1And2::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 0.3189;
	layoutbox.height = 1;
	layoutbox.x = 0.681;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 0.31055;
	layoutbox.height = 0.4825688;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.342925659;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0;
	layoutbox.y = 0.515596;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.342925659;
	layoutboxes.push_back(layoutbox);

	return true;
}



class LYA5CalL1And3: public PPLayout
{
public:
	LYA5CalL1And3(){}
	~LYA5CalL1And3(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL1And3::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;


	layoutbox.type = CalType;
	layoutbox.width = 0.3189;
	layoutbox.height = 1;
	layoutbox.x = 0.681;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.31055;
	layoutbox.height = 0.4825688;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.342925659;
	layoutboxes.push_back(layoutbox);


	layoutbox.width = 0.652278;
	layoutbox.x = 0;
	layoutbox.y = 0.515596;
	layoutboxes.push_back(layoutbox);


	return true;
}



class LYA5CalL1And4: public PPLayout
{
public:
	LYA5CalL1And4(){}
	~LYA5CalL1And4(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL1And4::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	//
	// layout, to adjust
	//

	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 0.3189;
	layoutbox.height = 1;
	layoutbox.x = 0.681;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.652278;
	layoutbox.height = 0.6672794;
	layoutbox.x = 0;
	layoutbox.y = 0.16544;
	layoutboxes.push_back(layoutbox);


	return true;
}



class LYA5CalL1And5: public PPLayout
{
public:
	LYA5CalL1And5(){}
	~LYA5CalL1And5(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL1And5::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 0.3189;
	layoutbox.height = 1;
	layoutbox.x = 0.681;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.4328537;
	layoutbox.height = 1;
	layoutbox.x = 0.1079478;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	return true;
}



class LYA5CalL1And6: public PPLayout
{
public:
	LYA5CalL1And6(){}
	~LYA5CalL1And6(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL1And6::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 0.3189;
	layoutbox.height = 1;
	layoutbox.x = 0.681;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.652278;
	layoutbox.height = 0.4825688;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	layoutbox.y = 0.515596;
	layoutboxes.push_back(layoutbox);



	return true;
}




class LYA5CalL2And1: public PPLayout
{
public:
	LYA5CalL2And1(){}
	~LYA5CalL2And1(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL2And1::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.70668693;
	layoutbox.x = 0;
	layoutbox.y = 0.05;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 1.0/7;
	layoutbox.height = 0.205167;
	layoutbox.x = 0;
	layoutbox.y = 0.79635258;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 1.0/7;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 2.0/7;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 3.0/7;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 4.0/7;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 5.0/7;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 6.0/7;
	layoutboxes.push_back(layoutbox);

	return true;
}




class LYA5CalL2And2: public PPLayout
{
public:
	LYA5CalL2And2(){}
	~LYA5CalL2And2(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL2And2::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.70668693;
	layoutbox.x = 0;
	layoutbox.y = 0.05;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 1.0/3;
	layoutbox.height = 0.205167;
	layoutbox.x = 0;
	layoutbox.y = 0.79635258;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 1.0/3;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 2.0/3;
	layoutboxes.push_back(layoutbox);

	return true;
}



class LYA5CalL2And3: public PPLayout
{
public:
	LYA5CalL2And3(){}
	~LYA5CalL2And3(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL2And3::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.70668693;
	layoutbox.x = 0;
	layoutbox.y = 0.05;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 1.0/4;
	layoutbox.height = 0.205167;
	layoutbox.x = 0;
	layoutbox.y = 0.79635258;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 1.0/4;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 2.0/4;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 3.0/4;
	layoutboxes.push_back(layoutbox);

	return true;
}



class LYA5CalL2And4: public PPLayout
{
public:
	LYA5CalL2And4(){}
	~LYA5CalL2And4(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL2And4::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.70668693;
	layoutbox.x = 0;
	layoutbox.y = 0.05;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 1.0/5;
	layoutbox.height = 0.205167;
	layoutbox.x = 0;
	layoutbox.y = 0.79635258;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 1.0/5;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 2.0/5;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 3.0/5;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 4.0/5;
	layoutboxes.push_back(layoutbox);

	return true;
}



class LYA5CalL2And5: public PPLayout
{
public:
	LYA5CalL2And5(){}
	~LYA5CalL2And5(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL2And5::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.70668693;
	layoutbox.x = 0;
	layoutbox.y = 0.05;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 1.0/6;
	layoutbox.height = 0.205167;
	layoutbox.x = 0;
	layoutbox.y = 0.79635258;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 1.0/6;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 2.0/6;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 3.0/6;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 4.0/6;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 5.0/6;
	layoutboxes.push_back(layoutbox);

	return true;
}


class LYA5CalL3And1: public PPLayout
{
public:
	LYA5CalL3And1(){}
	~LYA5CalL3And1(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL3And1::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.height = 0.153;
	layoutbox.width = 0.906148867;
	layoutbox.x = 0.048439;
	layoutbox.y = 0.8;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 1;
	layoutbox.height = 0.7547826;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	return true;
}



class LYA5CalL3And2: public PPLayout
{
public:
	LYA5CalL3And2(){}
	~LYA5CalL3And2(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL3And2::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.height = 0.153;
	layoutbox.width = 0.906148867;
	layoutbox.x = 0.048439;
	layoutbox.y = 0.8;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.485468;
	layoutbox.height = 0.7547826;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.5156;
	layoutboxes.push_back(layoutbox);


	return true;
}




class LYA5CalL3And3: public PPLayout
{
public:
	LYA5CalL3And3(){}
	~LYA5CalL3And3(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL3And3::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.height = 0.153;
	layoutbox.width = 0.906148867;
	layoutbox.x = 0.048439;
	layoutbox.y = 0.8;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.3143;
	layoutbox.height = 0.7547826;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.344564;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.6857;
	layoutboxes.push_back(layoutbox);


	return true;
}



class LYA5CalL3And4: public PPLayout
{
public:
	LYA5CalL3And4(){}
	~LYA5CalL3And4(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};


bool LYA5CalL3And4::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.height = 0.153;
	layoutbox.width = 0.906148867;
	layoutbox.x = 0.048439;
	layoutbox.y = 0.8;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 0.485468;
	layoutbox.height = 0.36;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	layoutbox.height = 0.7547826;
	layoutbox.x = 0.5156;
	layoutboxes.push_back(layoutbox);

	layoutbox.width = 0.230355;
	layoutbox.height = 0.36;
	layoutbox.x = 0;
	layoutbox.y = 0.39478;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.25942;
	layoutboxes.push_back(layoutbox);

	return true;
}


// 4x6 calendar


class LY4X6CalL1And1: public PPLayout
{
public:
	LY4X6CalL1And1(){}
	~LY4X6CalL1And1(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL1And1::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;




	layoutbox.type = CalType;
	layoutbox.x = 0.778;
	layoutbox.y = 0;
	layoutbox.width = 0.222;
	layoutbox.height = 1;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.778;
	layoutbox.height = 0.855;
	layoutbox.x = 0.001; // in view, it may be out box, now adjust a little slip show that it can be show smoothly
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	/*
	layoutbox.type = CalMonthType;
	layoutbox.x = 0;
	layoutbox.y = 0.8566;
	layoutbox.width = 0.778;
	layoutbox.height = 0.1434;
	layoutboxes.push_back(layoutbox);
	*/
	return true;
}



class LY4X6CalL1And2: public PPLayout
{
public:
	LY4X6CalL1And2(){}
	~LY4X6CalL1And2(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL1And2::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;


	layoutbox.type = CalType;
	layoutbox.x = 0.778;
	layoutbox.y = 0;
	layoutbox.width = 0.222;
	layoutbox.height = 1;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.778;
	layoutbox.height = 0.410389;
	layoutbox.x = 0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	layoutbox.y = 0.44424778761;
	layoutboxes.push_back(layoutbox);



	/*
	layoutbox.type = CalMonthType;
	layoutbox.x = 0;
	layoutbox.y = 0.8566;
	layoutbox.width = 0.778;
	layoutbox.height = 0.1434;
	layoutboxes.push_back(layoutbox);
	*/

	return true;
}


class LY4X6CalL1And3: public PPLayout
{
public:
	LY4X6CalL1And3(){}
	~LY4X6CalL1And3(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL1And3::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;


	layoutbox.type = CalType;
	layoutbox.x = 0.778;
	layoutbox.y = 0;
	layoutbox.width = 0.222;
	layoutbox.height = 1;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.778;
	layoutbox.height = 0.410389;
	layoutbox.x = 0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	layoutbox.width = 0.361;
	layoutbox.x = 0.001;
	layoutbox.y = 0.44424778761;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.41951;
	layoutboxes.push_back(layoutbox);


	/*
	layoutbox.type = CalMonthType;
	layoutbox.x = 0;
	layoutbox.y = 0.8566;
	layoutbox.width = 0.778;
	layoutbox.height = 0.1434;
	layoutboxes.push_back(layoutbox);
	*/
	return true;
}





class LY4X6CalL1And4: public PPLayout
{
public:
	LY4X6CalL1And4(){}
	~LY4X6CalL1And4(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL1And4::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.x = 0.778;
	layoutbox.y =0;
	layoutbox.width = 0.222;
	layoutbox.height = 1;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 0.361;
	layoutbox.height = 0.410389;
	layoutbox.x = 0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	layoutbox.x = 0.41951;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.001;
	layoutbox.y = 0.44424778761;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.41951;
	layoutboxes.push_back(layoutbox);


	/*
	layoutbox.type = CalMonthType;
	layoutbox.x = 0;
	layoutbox.y = 0.8566;
	layoutbox.width = 0.778;
	layoutbox.height = 0.1434;
	layoutboxes.push_back(layoutbox);
	*/
	return true;
}



class LY4X6CalL2And1: public PPLayout
{
public:
	LY4X6CalL2And1(){}
	~LY4X6CalL2And1(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL2And1::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;



	layoutbox.type = CalType;
	layoutbox.x = 0;
	layoutbox.y = 0.7744755;
	layoutbox.width = 1;
	layoutbox.height = 0.2255245;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 1;
	layoutbox.height = 0.7744755;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);



	return true;
}


class LY4X6CalL2And2: public PPLayout
{
public:
	LY4X6CalL2And2(){}
	~LY4X6CalL2And2(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL2And2::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;



	layoutbox.type = CalType;
	layoutbox.x = 0;
	layoutbox.y = 0.7744755;
	layoutbox.width = 1;
	layoutbox.height = 0.2255245;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 1;
	layoutbox.height = 0.374125874;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.y = 0.4020979;
	layoutbox.width = 1;
	layoutboxes.push_back(layoutbox);



	return true;
}


class LY4X6CalL2And3: public PPLayout
{
public:
	LY4X6CalL2And3(){}
	~LY4X6CalL2And3(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL2And3::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;



	layoutbox.type = CalType;
	layoutbox.x = 0;
	layoutbox.y = 0.7744755;
	layoutbox.width = 1;
	layoutbox.height = 0.2255245;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.46756757;
	layoutbox.height = 0.374125874;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.535135;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0;
	layoutbox.y = 0.4020979;
	layoutbox.width = 1;
	layoutboxes.push_back(layoutbox);



	return true;
}


class LY4X6CalL2And4: public PPLayout
{
public:
	LY4X6CalL2And4(){}
	~LY4X6CalL2And4(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL2And4::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;



	layoutbox.type = CalType;
	layoutbox.x = 0;
	layoutbox.y = 0.7744755;
	layoutbox.width = 1;
	layoutbox.height = 0.2255245;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.46756757;
	layoutbox.height = 0.374125874;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.535135;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0;
	layoutbox.y = 0.4020979;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.535135;
	layoutboxes.push_back(layoutbox);



	return true;
}



class LY4X6CalL3And1: public PPLayout
{
public:
	LY4X6CalL3And1(){}
	~LY4X6CalL3And1(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL3And1::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;


	layoutbox.type = CalType;
	layoutbox.x = 0;
	layoutbox.y = 0.5;
	layoutbox.width = 1;
	layoutbox.height = 0.5;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 1-0.001;
	layoutbox.height = 0.5;
	layoutbox.x = 0.001;  // ajust view , should be 0
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);



	return true;
}


class LY4X6CalL3And2: public PPLayout
{
public:
	LY4X6CalL3And2(){}
	~LY4X6CalL3And2(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL3And2::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;


	layoutbox.type = CalType;
	layoutbox.x = 0;
	layoutbox.y = 0.5;
	layoutbox.width = 1;
	layoutbox.height = 0.5;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 0.46715;
	layoutbox.height = 0.5;
	layoutbox.x = 0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.52798 + 0.001;
	layoutboxes.push_back(layoutbox);

	return true;
}


class LY4X6CalL3And3: public PPLayout
{
public:
	LY4X6CalL3And3(){}
	~LY4X6CalL3And3(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL3And3::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;


	layoutbox.type = CalType;
	layoutbox.x = 0;
	layoutbox.y = 0.5;
	layoutbox.height = 0.5;
	layoutbox.width = 1;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 0.46715;
	layoutbox.height = 0.5;
	layoutbox.x = 0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.height = 0.23841;
	layoutbox.x = 0.52798 + 0.001;
	layoutboxes.push_back(layoutbox);

	layoutbox.y = 0.2649;
	layoutboxes.push_back(layoutbox);


	return true;
}


class LY4X6CalL3And4: public PPLayout
{
public:
	LY4X6CalL3And4(){}
	~LY4X6CalL3And4(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL3And4::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;


	layoutbox.type = CalType;
	layoutbox.x = 0;
	layoutbox.y = 0.5;
	layoutbox.width = 1;
	layoutbox.height = 0.5;
	layoutboxes.push_back(layoutbox);

	layoutbox.type = ImgType;
	layoutbox.width = 0.46715;
	layoutbox.height = 0.23841;
	layoutbox.x = 0.001;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.52798 + 0.001;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.001;
	layoutbox.y = 0.2649;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 0.52798 + 0.001;
	layoutboxes.push_back(layoutbox);


	return true;
}



class LY4X6CalL4And1: public PPLayout
{
public:
	LY4X6CalL4And1(){}
	~LY4X6CalL4And1(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL4And1::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.708469;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 1.0/3;
	layoutbox.height = 0.25732899;
	layoutbox.y = 0.742671;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 1.0/3;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 2.0/3;
	layoutboxes.push_back(layoutbox);

	return true;
}



class LY4X6CalL4And2: public PPLayout
{
public:
	LY4X6CalL4And2(){}
	~LY4X6CalL4And2(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL4And2::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.708469;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.y = 0.742671;
	layoutbox.height = 0.25732899;
	layoutboxes.push_back(layoutbox);

	return true;
}


class LY4X6CalL4And3: public PPLayout
{
public:
	LY4X6CalL4And3(){}
	~LY4X6CalL4And3(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL4And3::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.708469;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 1.0/2;
	layoutbox.height = 0.25732899;
	layoutbox.y = 0.742671;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 1.0/2;
	layoutboxes.push_back(layoutbox);

	return true;
}




class LY4X6CalL4And4: public PPLayout
{
public:
	LY4X6CalL4And4(){}
	~LY4X6CalL4And4(){}
public:
	bool getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left);
};

bool LY4X6CalL4And4::getLayout(QList<LayoutBoxPos> &layoutboxes, bool hasborder, bool left)
{
	LayoutBoxPos layoutbox;

	layoutbox.margin.left = 0;
	layoutbox.margin.top = 0;
	layoutbox.margin.right = 0;
	layoutbox.margin.bottom = 0;

	layoutbox.type = CalType;
	layoutbox.width = 1;
	layoutbox.height = 0.708469;
	layoutbox.x = 0;
	layoutbox.y = 0;
	layoutboxes.push_back(layoutbox);


	layoutbox.type = ImgType;
	layoutbox.width = 1.0/4;
	layoutbox.height = 0.25732899;
	layoutbox.y = 0.742671;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 1.0/4;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 2.0/4;
	layoutboxes.push_back(layoutbox);

	layoutbox.x = 3.0/4;
	layoutboxes.push_back(layoutbox);

	return true;
}



//
QString  PPLayoutMgr::getLayoutName(const PHOTO_LAYOUT layout)
{
	switch(layout)
	{
	case PP_LAYOUT_PB8X5_FULLSIZE_A:
		return LY_8X5_FULLSIZE_A;
	case PP_LAYOUT_PB8X5_FULLSIZE_B:
		return LY_8X5_FULLSIZE_B;
	case PP_LAYOUT_PB8X5_FULLSIZE_C:
		return LY_8X5_FULLSIZE_C;
	case PP_LAYOUT_PB8X5_FULLSIZE_D:
		return LY_8X5_FULLSIZE_D;
	case PP_LAYOUT_PB8X5_FULLSIZE_PANOR:
		return LY_8X5_FULLSIZE_PANOR;
	case PP_LAYOUT_PB8X5_TRADITION_A:
		return LY_8X5_TRADITION_A;
	case PP_LAYOUT_PB8X5_TRADITION_B:
		return LY_8X5_TRADITION_B;
	case PP_LAYOUT_PB8X5_TRADITION_C:
		return LY_8X5_TRADITION_C;
	case PP_LAYOUT_PB8X5_TRADITION_D:
		return LY_8X5_TRADITION_D;
	case PP_LAYOUT_PB8X5_TRADITION_PANOR:
		return LY_8X5_TRADITION_PANOR;
	case PP_LAYOUT_PB8X5_HORIZON_A:
		return LY_8X5_HORIZON_A;
	case PP_LAYOUT_PB8X5_HORIZON_B:
		return LY_8X5_HORIZON_B;
	case PP_LAYOUT_PB8X5_HORIZON_C:
		return LY_8X5_HORIZON_C;
	case PP_LAYOUT_PB8X5_HORIZON_D:
		return LY_8X5_HORIZON_D;
	case PP_LAYOUT_PB8X5_HORIZON_E:
		return LY_8X5_HORIZON_E;
	case PP_LAYOUT_PB8X5_HORIZON_PANOR:
		return LY_8X5_HORIZON_PANOR;
	case PP_LAYOUT_PB8X5_VERTICON_A:
		return LY_8X5_VERTICON_A;
	case PP_LAYOUT_PB8X5_VERTICON_B:
		return LY_8X5_VERTICON_B;
	case PP_LAYOUT_PB8X5_VERTICON_C:
		return LY_8X5_VERTICON_C;
	case PP_LAYOUT_PB8X5_VERTICON_D:
		return LY_8X5_VERTICON_D;
	case PP_LAYOUT_PB8X5_VERTICON_PANOR:
		return LY_8X5_VERTICON_PANOR;

	// calandar
	case PP_LAYOUT_CALENDAR_A4_L1_L1:
		return  LY_CALA4_L1_1;
		break;
	case PP_LAYOUT_CALENDAR_A4_L1_L2:
		return LY_CALA4_L1_2;
		break;
	case PP_LAYOUT_CALENDAR_A4_L1_L3:
		return LY_CALA4_L1_3;
		break;
	case PP_LAYOUT_CALENDAR_A4_L1_L4:
		return LY_CALA4_L1_4;
		break;
	case PP_LAYOUT_CALENDAR_A4_L2_L1:
		return LY_CALA4_L2_1;
		break;
	case PP_LAYOUT_CALENDAR_A4_L2_L2:
		return LY_CALA4_L2_2;
		break;
	case PP_LAYOUT_CALENDAR_A4_L2_L3: 
		return LY_CALA4_L2_3;
		break; 
	case  PP_LAYOUT_CALENDAR_A4_L2_L4: 
		return LY_CALA4_L2_4;
		break; 
	case  PP_LAYOUT_CALENDAR_A4_L2_L5: 
		return LY_CALA4_L2_5;
		break; 
	case  PP_LAYOUT_CALENDAR_A4_L2_L6: 
		return LY_CALA4_L2_6;
		break; 
	case PP_LAYOUT_CALENDAR_A4_L3_L1:
		return LY_CALA4_L3_1;
		break; 
	case  PP_LAYOUT_CALENDAR_A4_L3_L2: 
		return LY_CALA4_L3_2;
		break; 
	case  PP_LAYOUT_CALENDAR_A4_L3_L3: 
		return LY_CALA4_L3_3;
		break; 
	case  PP_LAYOUT_CALENDAR_A4_L3_L4: 
		return LY_CALA4_L3_4;
		break;
	case PP_LAYOUT_CALENDAR_A4_L4_L1: 
		return LY_CALA4_L4_1;
		break; 
	case PP_LAYOUT_CALENDAR_A4_L4_L2: 
		return LY_CALA4_L4_2;
		break; 
	case  PP_LAYOUT_CALENDAR_A4_L4_L3: 
		return LY_CALA4_L4_3;
		break; 
	case  PP_LAYOUT_CALENDAR_A4_L4_L4: 
		return LY_CALA4_L4_4;
		break; 
	case PP_LAYOUT_CALENDAR_A5_L1_L1: 
		return LY_CALA5_L1_1;
		break; 
	case  PP_LAYOUT_CALENDAR_A5_L1_L2:
		return LY_CALA5_L1_2;
		break;
	case  PP_LAYOUT_CALENDAR_A5_L1_L3: 
		return LY_CALA5_L1_3;
		break;
	case  PP_LAYOUT_CALENDAR_A5_L1_L4: 
		return LY_CALA5_L1_4;
		break; 
	case  PP_LAYOUT_CALENDAR_A5_L1_L5: 
		return LY_CALA5_L1_5;
		break; 
	case  PP_LAYOUT_CALENDAR_A5_L1_L6: 
		return LY_CALA5_L1_6;
		break; 
	case PP_LAYOUT_CALENDAR_A5_L2_L1: 
		return LY_CALA5_L2_1;
		break;
	case PP_LAYOUT_CALENDAR_A5_L2_L2: 
		return LY_CALA5_L2_2;
		break; 
	case  PP_LAYOUT_CALENDAR_A5_L2_L3: 
		return LY_CALA5_L2_3;
		break; 
	case  PP_LAYOUT_CALENDAR_A5_L2_L4: 
		return LY_CALA5_L2_4;
		break;
	case  PP_LAYOUT_CALENDAR_A5_L2_L5: 
		return LY_CALA5_L2_5;
		break;
	case PP_LAYOUT_CALENDAR_A5_L3_L1: 
		return LY_CALA5_L3_1;
		break; 
	case PP_LAYOUT_CALENDAR_A5_L3_L2: 
		return LY_CALA5_L3_2;
		break; 
	case  PP_LAYOUT_CALENDAR_A5_L3_L3:
		return LY_CALA5_L3_3;
		break; 
	case  PP_LAYOUT_CALENDAR_A5_L3_L4: 
		return LY_CALA5_L3_4;
		break; 
	case PP_LAYOUT_CALENDAR_4X6_L1_L1:
		return LY_CAL4X6_L1_1;
		break;
	case  PP_LAYOUT_CALENDAR_4X6_L1_L2: 
		return LY_CAL4X6_L1_2;
		break; 
	case  PP_LAYOUT_CALENDAR_4X6_L1_L3: 
		return LY_CAL4X6_L1_3;
		break; 
	case  PP_LAYOUT_CALENDAR_4X6_L1_L4:
		return LY_CAL4X6_L1_4;
		break;
	case PP_LAYOUT_CALENDAR_4X6_L2_L1:
		return LY_CAL4X6_L2_1;
		break; 
	case PP_LAYOUT_CALENDAR_4X6_L2_L2: 
		return LY_CAL4X6_L2_2;
		break;
	case  PP_LAYOUT_CALENDAR_4X6_L2_L3:
		return LY_CAL4X6_L2_3;
		break;
	case  PP_LAYOUT_CALENDAR_4X6_L2_L4:
		return LY_CAL4X6_L2_4;
		break;
	case PP_LAYOUT_CALENDAR_4X6_L3_L1: 
		return LY_CAL4X6_L3_1;
		break;
	case PP_LAYOUT_CALENDAR_4X6_L3_L2: 
		return LY_CAL4X6_L3_2;
		break; 
	case  PP_LAYOUT_CALENDAR_4X6_L3_L3:
		return LY_CAL4X6_L3_3;
		break;
	case  PP_LAYOUT_CALENDAR_4X6_L3_L4:
		return LY_CAL4X6_L3_4;
		break;
	case PP_LAYOUT_CALENDAR_4X6_L4_L1: 
		return LY_CAL4X6_L4_1;
		break; 
	case  PP_LAYOUT_CALENDAR_4X6_L4_L2:
		return LY_CAL4X6_L4_2;
		break;
	case PP_LAYOUT_CALENDAR_4X6_L4_L3: 
		return LY_CAL4X6_L4_3;
		break; 
	case PP_LAYOUT_CALENDAR_4X6_L4_L4:
		return LY_CAL4X6_L4_4;
		break;

	default:
		return "";
	}

	return "";
}


PHOTO_LAYOUT PPLayoutMgr::getLayoutFromName(const PROJ_PROPS &projprops,const QString &name)
{


	if ( projprops.lytype == PROJ_PROPS::LYCALA4L1)
	{
		if ( LY_CALA4_L1_1 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L1_L1;
		}
		else if ( LY_CALA4_L1_2 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L1_L2;
		}
		else if ( LY_CALA4_L1_3 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L1_L3;
		}
		else if ( LY_CALA4_L1_4 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L1_L4;
		}
		else if ( LY_CALA4_FP_1 == name )
		{
			return PP_LAYOUT_CALENDARA4_BORDER_FONTPG;
		}
		else if ( LY_CALA4_FP_2 == name )
		{
			return PP_LAYOUT_CALENDARA4_FONTPG;
		}
	}
	else if ( projprops.lytype == PROJ_PROPS::LYCALA4L2 )
	{
		if ( LY_CALA4_L2_1 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L2_L1;
		}
		else if ( LY_CALA4_L2_2 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L2_L2;
		}
		else if ( LY_CALA4_L2_3 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L2_L3;
		}
		else if ( LY_CALA4_L2_4 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L2_L4;
		}
		else if ( LY_CALA4_L2_5 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L2_L5;
		}
		else if ( LY_CALA4_L2_6 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L2_L6;
		}
		else if ( LY_CALA4_FP_1 == name )
		{
			return PP_LAYOUT_CALENDARA4_BORDER_FONTPG;
		}
		else if ( LY_CALA4_FP_2 == name )
		{
			return PP_LAYOUT_CALENDARA4_FONTPG;
		}
	}
	else if ( projprops.lytype == PROJ_PROPS::LYCALA4L3 )
	{
		if ( LY_CALA4_L3_1 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L3_L1;
		}
		else if ( LY_CALA4_L3_2 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L3_L2;
		}
		else if ( LY_CALA4_L3_3 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L3_L3;
		}
		else if ( LY_CALA4_L3_4 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L3_L4;
		}
		else if ( LY_CALA4_FP_1 == name )
		{
			return PP_LAYOUT_CALENDARA4_BORDER_FONTPG;
		}
		else if ( LY_CALA4_FP_2 == name )
		{
			return PP_LAYOUT_CALENDARA4_FONTPG;
		}
	}
	else if ( projprops.lytype == PROJ_PROPS::LYCALA4L4 )
	{
		if ( LY_CALA4_L4_1 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L4_L1;
		}
		else if ( LY_CALA4_L4_2 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L4_L2;
		}
		else if ( LY_CALA4_L4_3 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L4_L3;
		}
		else if ( LY_CALA4_L4_4 == name )
		{
			return PP_LAYOUT_CALENDAR_A4_L4_L4;
		}
		else if ( LY_CALA4_FP_1 == name )
		{
			return PP_LAYOUT_CALENDARA4_BORDER_FONTPG;
		}
		else if ( LY_CALA4_FP_2 == name )
		{
			return PP_LAYOUT_CALENDARA4_FONTPG;
		}
	}
	else if (  projprops.lytype == PROJ_PROPS::LYCALA5L1 )
	{
		if ( LY_CALA5_L1_1 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L1_L1;
		}
		else if ( LY_CALA5_L1_2 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L1_L2;
		}
		else if ( LY_CALA5_L1_3 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L1_L3;
		}
		else if ( LY_CALA5_L1_4 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L1_L4;
		}
		else if ( LY_CALA5_L1_5 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L1_L5;
		}
		else if ( LY_CALA5_L1_6 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L1_L6;
		}
		else if ( LY_CALA5_FP_1 == name )
		{
			return PP_LAYOUT_CALENDARA5_BORDER_FONTPG;
		}
		else if ( LY_CALA5_FP_2 == name )
		{
			return PP_LAYOUT_CALENDARA5_FONTPG;
		}
	}
	else if ( projprops.lytype == PROJ_PROPS::LYCALA5L2 )
	{

		if ( LY_CALA5_L2_1 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L2_L1;
		}
		else if ( LY_CALA5_L2_2 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L2_L2;
		}
		else if ( LY_CALA5_L2_3 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L2_L3;
		}
		else if ( LY_CALA5_L2_4 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L2_L4;
		}
		else if ( LY_CALA5_L2_5 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L2_L5;
		}
		else if ( LY_CALA5_FP_1 == name )
		{
			return PP_LAYOUT_CALENDARA5_BORDER_FONTPG;
		}
		else if ( LY_CALA5_FP_2 == name )
		{
			return PP_LAYOUT_CALENDARA5_FONTPG;
		}
	}
	else if ( projprops.lytype == PROJ_PROPS::LYCALA5L3 )
	{

		if ( LY_CALA5_L3_1 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L3_L1;
		}
		else if ( LY_CALA5_L3_2 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L3_L2;
		}
		else if ( LY_CALA5_L3_3 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L3_L3;
		}
		else if ( LY_CALA5_L3_4 == name )
		{
			return PP_LAYOUT_CALENDAR_A5_L3_L4;
		}
		else if ( LY_CALA5_FP_1 == name )
		{
			return PP_LAYOUT_CALENDARA5_BORDER_FONTPG;
		}
		else if ( LY_CALA5_FP_2 == name )
		{
			return PP_LAYOUT_CALENDARA5_FONTPG;
		}
	}
	else if ( projprops.lytype == PROJ_PROPS::LYCAL4X6L1 )
	{

		if ( LY_CAL4X6_L1_1 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L1_L1;
		}
		else if ( LY_CAL4X6_L1_2 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L1_L2;
		}
		else if ( LY_CAL4X6_L1_3 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L1_L3;
		}
		else if ( LY_CAL4X6_L1_4 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L1_L4;
		}
		else if ( LY_CALA4x6_FP_1 == name )
		{
			return PP_LAYOUT_CALENDAR4x6_BORDER_FONTPG;
		}
		else if ( LY_CALA4x6_FP_2 == name )
		{
			return PP_LAYOUT_CALENDAR4x6_FONTPG;
		}
	}
	else if ( projprops.lytype == PROJ_PROPS::LYCAL4X6L2 )
	{

		if ( LY_CAL4X6_L2_1 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L2_L1;
		}
		else if ( LY_CAL4X6_L2_2 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L2_L2;
		}
		else if ( LY_CAL4X6_L2_3 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L2_L3;
		}
		else if ( LY_CAL4X6_L2_4 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L2_L4;
		}
		else if ( LY_CALA4x6_FP_1 == name )
		{
			return PP_LAYOUT_CALENDAR4x6_BORDER_FONTPG;
		}
		else if ( LY_CALA4x6_FP_2 == name )
		{
			return PP_LAYOUT_CALENDAR4x6_FONTPG;
		}
	}
	else if ( projprops.lytype == PROJ_PROPS::LYCAL4X6L3 )
	{

		if ( LY_CAL4X6_L3_1 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L3_L1;
		}
		else if ( LY_CAL4X6_L3_2 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L3_L2;
		}
		else if ( LY_CAL4X6_L3_3 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L3_L3;
		}
		else if ( LY_CAL4X6_L3_4 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L3_L4;
		}
		else if ( LY_CALA4x6_FP_1 == name )
		{
			return PP_LAYOUT_CALENDAR4x6_BORDER_FONTPG;
		}
		else if ( LY_CALA4x6_FP_2 == name )
		{
			return PP_LAYOUT_CALENDAR4x6_FONTPG;
		}
	}
	else if ( projprops.lytype == PROJ_PROPS::LYCAL4X6L4 )
	{

		if( LY_CAL4X6_L4_1 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L4_L1;
		}
		else if ( LY_CAL4X6_L4_2 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L4_L2;
		}
		else if ( LY_CAL4X6_L4_3 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L4_L3;
		}
		else if ( LY_CAL4X6_L4_4 == name )
		{
			return PP_LAYOUT_CALENDAR_4X6_L4_L4;
		}
		else if ( LY_CALA4x6_FP_1 == name )
		{
			return PP_LAYOUT_CALENDAR4x6_BORDER_FONTPG;
		}
		else if ( LY_CALA4x6_FP_2 == name )
		{
			return PP_LAYOUT_CALENDAR4x6_FONTPG;
		}
	}
	else
	{
		if ( LY_8X5_FULLSIZE_A == name )
		{
			return PP_LAYOUT_PB8X5_FULLSIZE_A;
		}
		else if ( LY_8X5_FULLSIZE_B == name )
		{
			return PP_LAYOUT_PB8X5_FULLSIZE_B;
		}
		else if ( LY_8X5_FULLSIZE_C == name )
		{
			return PP_LAYOUT_PB8X5_FULLSIZE_C;
		}
		else if ( LY_8X5_FULLSIZE_D == name )
		{
			return PP_LAYOUT_PB8X5_FULLSIZE_D;
		}
		else if ( LY_8X5_FULLSIZE_PANOR == name )
		{
			return PP_LAYOUT_PB8X5_FULLSIZE_PANOR;
		}
		else if ( LY_8X5_TRADITION_A == name )
		{
			return PP_LAYOUT_PB8X5_TRADITION_A;
		}
		else if ( LY_8X5_TRADITION_B == name )
		{
			return PP_LAYOUT_PB8X5_TRADITION_B;
		}
		else if ( LY_8X5_TRADITION_C == name )
		{
			return PP_LAYOUT_PB8X5_TRADITION_C;

		}
		else if ( LY_8X5_TRADITION_D == name )
		{
			return PP_LAYOUT_PB8X5_TRADITION_D;
		}
		else if ( LY_8X5_TRADITION_PANOR == name )
		{
			return PP_LAYOUT_PB8X5_TRADITION_PANOR;
		}
		else if ( LY_8X5_HORIZON_A == name )
		{
			return PP_LAYOUT_PB8X5_HORIZON_A;
		}
		else if ( LY_8X5_HORIZON_B == name )
		{
			return PP_LAYOUT_PB8X5_HORIZON_B;
		}
		else if ( LY_8X5_HORIZON_C == name )
		{
			return PP_LAYOUT_PB8X5_HORIZON_C;
		}
		else if ( LY_8X5_HORIZON_D == name )
		{
			return PP_LAYOUT_PB8X5_HORIZON_D;
		}
		else if ( LY_8X5_HORIZON_E == name )
		{
			return PP_LAYOUT_PB8X5_HORIZON_E;
		}
		else if ( LY_8X5_HORIZON_PANOR == name )
		{
			return PP_LAYOUT_PB8X5_HORIZON_PANOR;
		}
		else if ( LY_8X5_VERTICON_A == name )
		{
			return PP_LAYOUT_PB8X5_VERTICON_A;
		}
		else if ( LY_8X5_VERTICON_B == name )
		{
			return PP_LAYOUT_PB8X5_VERTICON_B;
		}
		else if ( LY_8X5_VERTICON_C == name )
		{
			return PP_LAYOUT_PB8X5_VERTICON_C;
		}
		else if ( LY_8X5_VERTICON_D == name )
		{
			return PP_LAYOUT_PB8X5_VERTICON_D;
		}
		else if ( LY_8X5_VERTICON_PANOR == name )
		{
			return PP_LAYOUT_PB8X5_VERTICON_PANOR;
		}
		else if ( LY_4X3_FULLSIZE_SINGLE == name )
		{
			return PP_LAYOUT_FULLSIZE_SINGLE;
		}
		else if ( LY_4X3_FULLSIZE_PANORAMA == name )
		{
			return PP_LAYOUT_FULLSIZE_PANOR;
		}
		else if ( LY_4X3_BORDER_SINGLE == name )
		{
			return PP_LAYOUT_BORDER_SINGLE;
		}
		else if ( LY_4X3_BORDER_PANORAMA == name )
		{
			return PP_LAYOUT_BORDER_PANOR;
		}

	}

	// WRONT
	return PP_LAYOUT_PB8X5_VERTICON_A;

}

PPLayout &PPLayoutMgr::getLayout(const PROJ_PROPS &projprops,const QString &layoutname)
{
	PHOTO_LAYOUT layout = getLayoutFromName(projprops, layoutname);
	return getLayout(layout);
}


PPLayout &PPLayoutMgr::getLayout(PHOTO_LAYOUT layout)
{
	switch(layout)
	{
		// 8x5
	case PP_LAYOUT_PB8X5_FULLSIZE_A:
		{
			static LY8X5FullSizeA layout;
			return layout;
		}
	case PP_LAYOUT_PB8X5_FULLSIZE_B:
		{
			static LY8X5FullSizeB layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_FULLSIZE_C:
		{
			static LY8X5FullSizeC layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_FULLSIZE_D:
		{
			static LY8X5FullSizeD layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_FULLSIZE_PANOR:
		{
			static LY8X5FullSizePanor layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_TRADITION_A:
		{
			static LY8X5TraditionA layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_TRADITION_B:
		{
			static LY8X5TraditionB layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_TRADITION_C:
		{
			static LY8X5TraditionC layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_TRADITION_D:
		{
			static LY8X5TraditionD layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_TRADITION_PANOR:
		{
			static LY8X5TraditionPanor layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_HORIZON_A:
		{
			static LY8X5HorizonA layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_HORIZON_B:
		{
			static LY8X5HorizonB layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_HORIZON_C:
		{
			static LY8X5HorizonC layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_HORIZON_D:
		{
			static LY8X5HorizonD layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_HORIZON_E:
		{
			static LY8X5HorizonE layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_HORIZON_PANOR:
		{
			static LY8X5HorizonPanor layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_VERTICON_A:
		{
			static LY8X5VerticonA layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_VERTICON_B:
		{
			static LY8X5VerticonB layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_VERTICON_C:
		{
			static LY8X5VerticonC layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_VERTICON_D:
		{
			static LY8X5VertcionD layout;
			return layout;
		}
		break;
	case PP_LAYOUT_PB8X5_VERTICON_PANOR:
		{
			static LY8X5VertcionPanor layout;
			return layout;
		}
		break;
	case PP_LAYOUT_FULLSIZE_SINGLE:
		{
			static FullSizeSingleLayout layout;
			return layout;

		}
		break;
	case PP_LAYOUT_FULLSIZE_PANOR:
		{
			static FullSizeSinglePanLayout layout;
			return layout;
		}
		break;
	case PP_LAYOUT_BORDER_SINGLE:
		{
			static BorderSingleLayout layout;
			return layout;
		}
		break;
	case PP_LAYOUT_BORDER_PANOR:
		{
			static BorderSinglePanLayout layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L1_L1:
		{
			static LYA4CalL1And1 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L1_L2:
		{
			static LYA4CalL1And2 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L1_L3:
		{
			static LYA4CalL1And3 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L1_L4:
		{
			static LYA4CalL1And4 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L2_L1:
		{
			static LYA4CalL2And1 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L2_L2:
		{
			static LYA4CalL2And2 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L2_L3:
		{
			static LYA4CalL2And3 layout;
			return layout;

		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L2_L4:
		{
			static LYA4CalL2And4 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L2_L5:
		{
			static LYA4CalL2And5 layout;
			return layout;

		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L2_L6:
		{
			static LYA4CalL2And6 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L3_L1:
		{
			static LYA4CalL3And1 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L3_L2:
		{
			static LYA4CalL3And2 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L3_L3:
		{
			static LYA4CalL3And3 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L3_L4:
		{
			static LYA4CalL3And4 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L4_L1:
		{
			static LYA4CalL4And1 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L4_L2:
		{
			static LYA4CalL4And2 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L4_L3:
		{
			static LYA4CalL4And3 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A4_L4_L4:
		{
			static LYA4CalL4And4 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L1_L1:
		{
			static LYA5CalL1And1 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L1_L2:
		{
			static LYA5CalL1And2 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L1_L3:
		{
			static LYA5CalL1And3 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L1_L4:
		{
			static LYA5CalL1And4 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L1_L5:
		{
			static LYA5CalL1And5 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L1_L6:
		{
			static LYA5CalL1And6 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L2_L1:
		{
			static LYA5CalL2And1 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L2_L2:
		{
			static LYA5CalL2And2 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L2_L3:
		{
			static LYA5CalL2And3 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L2_L4:
		{
			static LYA5CalL2And4 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L2_L5:
		{
			static LYA5CalL2And5 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L3_L1:
		{
			static LYA5CalL3And1 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L3_L2:
		{
			static LYA5CalL3And2 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L3_L3:
		{
			static LYA5CalL3And3 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_A5_L3_L4:
		{
			static LYA5CalL3And4 layout;
			return layout;
		}
		break;

		// 4x6 not ready now
	case PP_LAYOUT_CALENDAR_4X6_L1_L1:
		{
			static LY4X6CalL1And1 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L1_L2:
		{
			static LY4X6CalL1And2 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L1_L3:
		{
			static LY4X6CalL1And3 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L1_L4:
		{
			static LY4X6CalL1And4 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L2_L1:
		{
			static LY4X6CalL2And1 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L2_L2:
		{
			static LY4X6CalL2And2 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L2_L3:
		{
			static LY4X6CalL2And3 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L2_L4:
		{
			static LY4X6CalL2And4 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L3_L1:
		{
			static LY4X6CalL3And1 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L3_L2:
		{
			static LY4X6CalL3And2 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L3_L3:
		{
			static LY4X6CalL3And3 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L3_L4:
		{
			static LY4X6CalL3And4 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L4_L1:
		{
			static LY4X6CalL4And1 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L4_L2:
		{
			static LY4X6CalL4And2 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L4_L3:
		{
			static LY4X6CalL4And3 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR_4X6_L4_L4:
		{
			static LY4X6CalL4And4 layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDARA4_FONTPG:
		{
			static LYCalA4FontPg layout;
			return layout;
		}
	case PP_LAYOUT_CALENDARA4_BORDER_FONTPG:
		{
			static LYCalA4FontPg layout(true);
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDARA5_FONTPG:
		{
			static LYCalA5FontPg layout;
			return layout;
		}
	case PP_LAYOUT_CALENDARA5_BORDER_FONTPG:
		{
			static LYCalA5FontPg layout(true);
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR4x6_FONTPG:
		{
			static LYCal4x6FontPg layout;
			return layout;
		}
		break;
	case PP_LAYOUT_CALENDAR4x6_BORDER_FONTPG:
		{
			static LYCal4x6FontPg layout(true);
			return layout;
		}
		break;
	default:
		;
	}
	static LY8X5FullSizeA testlayout;
	return testlayout;
}


PmPrintPaperPage::PmPrintPaperPage(QObject *parent, PAGE_POS_INBOOK pagepos):QObject(parent),
	 _pPapaerPreviewView(NULL), _pPhotoEditView(NULL), _paperpos(pagepos)
{
}

bool PmPrintPaperPage::copy(PmPrintPaperPage &srcpaper)
{
	_paperpos = srcpaper._paperpos;
	_txtlst.clear();
	if ( srcpaper._txtlst.size() )
	{
		QList<PmTextItm *>::iterator it;
		for(it=srcpaper._txtlst.begin(); it!=srcpaper._txtlst.end(); it++ )
		{
			//
			PmTextItm *txtitm = new PmTextItm(**it);
			txtitm->setPrintPage(this);
			_txtlst.push_back(txtitm);
		}
	}

	_pPhotoEditView = srcpaper._pPhotoEditView;
	_pPapaerPreviewView = srcpaper._pPapaerPreviewView;

	_photoPages.clear();
	QList<PmPhotoPage *>::iterator it;
	for ( it=srcpaper._photoPages.begin(); it!=srcpaper._photoPages.end(); it++ )
	{
		PmPhotoPage *page = new PmPhotoPage(**it);
		//page->copy(**it);
		page->setPaperPage(this);
		_photoPages.push_back(page);
	}

	return true;
}


PmPrintPaperPage::~PmPrintPaperPage()
{
}


PHOTO_LAYOUT PmPrintPaperPage::_getLayoutMatch2Panor(PHOTO_LAYOUT panorlayout)
{
	PHOTO_LAYOUT pagelayout = panorlayout;
	if ( panorlayout == PP_LAYOUT_FULLSIZE_PANOR )
	{
		pagelayout = PP_LAYOUT_FULLSIZE_SINGLE;
	}
	else if ( panorlayout == PP_LAYOUT_BORDER_PANOR )
	{
		pagelayout = PP_LAYOUT_BORDER_SINGLE;
	}
	else if ( panorlayout == PP_LAYOUT_PB8X5_FULLSIZE_PANOR )
	{
		pagelayout = PP_LAYOUT_PB8X5_FULLSIZE_B;
	}
	else if ( panorlayout == PP_LAYOUT_PB8X5_TRADITION_PANOR )
	{
		pagelayout = PP_LAYOUT_PB8X5_TRADITION_B;
	}
	else if ( panorlayout == PP_LAYOUT_PB8X5_HORIZON_PANOR )
	{
		pagelayout = PP_LAYOUT_PB8X5_HORIZON_B;
	}
	else if ( panorlayout == PP_LAYOUT_PB8X5_VERTICON_PANOR )
	{
		pagelayout = PP_LAYOUT_PB8X5_VERTICON_B;
	}
	else
	{
		// wrong
	}

	return pagelayout;
}


bool PmPrintPaperPage::updatePanoramaPages(PmPhotoPage *srcpage, PmPhotoPage *&dstpage)
{
	//
	QList<PmPhotoPage *>  photopages;
	this->getPhotoPages(photopages);
	if ( photopages.size() != 2 )
	{
		return false;
	}

	//
	if ( !srcpage )
	{
		return false;
	}
	QList<PmPageItm *> srcitmlst;
	srcpage->getPicItms(srcitmlst);
	if ( srcitmlst.size() != 1)
	{
		return false;
	}
	PmPageItm *srcitm = srcitmlst[0];


	dstpage = NULL;
	if ( srcpage->isLeft() )
	{
		dstpage = photopages.back();
	}
	else
	{
		dstpage = photopages.first();
	}
	QList<PmPageItm *> dstitmlst;
	PmPageItm *dstitm;
	dstpage->getPicItms(dstitmlst);
	if ( dstitmlst.size() != 1)
	{
		return false;
	}
	dstitm = dstitmlst[0];
	QString imgpath;
	srcitm->getContent(imgpath);
	dstitm->setContent(imgpath);
	QPixmap *srcpixmap = srcitm->getPixmap();
	dstitm->setPixmap(*srcpixmap);

	QColor color;
	srcitm->getBgColor(color);
	dstitm->setBgColor(color);

	int angel = 0;
	srcitm->getRotate(angel);
	qreal ratio = 0;
	srcitm->getZoom(ratio);
	dstitm->setRotate(angel);
	dstitm->setZoom(ratio);

	QPointF imglefttop;
	srcitm->getImgLeftTop(imglefttop);
	dstitm->setImgLeftTop(imglefttop);

	return true;
}

#if 0
bool PmPrintPaperPage::splitPhotoPage()
{
	// should be 1 pages
	if ( this->_photoPages.size() != 1 )
	{
		return false;
	}
	PmPhotoPage *photopage = _photoPages.back();
	//_photoPages.pop_back();
	if ( !photopage )
	{
		return false;
	}
	QList<PmPageItm*> picitmlst;
	photopage->getPicItms(picitmlst);
	if ( picitmlst.size() != 1 )
	{
		return false;
	}
	PmPageItm *pPhotoItm = picitmlst.front();
	pPhotoItm->setPhotoItmType(PmPageItm::IMG_ITM);
	PHOTO_LAYOUT pagelayout = photopage->getLayout();

	pagelayout = _getLayoutMatch2Panor(pagelayout);
	photopage->setLayout(pagelayout,this->getborder(), false);

	QList<LayoutBoxPos> pagespos;
	//getPhotoPagesPos(pagespos);

	PmPhotoPage *newphotopage;
	newphotopage = new PmPhotoPage(this);

	newphotopage->setPaperPage(this);
	newphotopage->setLayout(pagelayout,this->getborder(),  true);
	QList<PmPageItm*> photoitmlst;
	newphotopage->getPicItms(photoitmlst);
	if ( photoitmlst.size() == 1 )
	{
		QList<PmPageItm*> oldphotoitmlst;
		photopage->getPicItms(oldphotoitmlst);
		PmPageItm *poldpicitm = NULL;
		QString imgpath;
		if ( oldphotoitmlst.size() )
		{
			poldpicitm = oldphotoitmlst.front();
			poldpicitm->getContent(imgpath);
		}

		PmPageItm* photoitm = photoitmlst.front();
		photoitm->setContent(imgpath);
	}
	if ( photopage->isLeft() )
	{
		_photoPages.push_back(newphotopage);
	}
	else
	{
		_photoPages.push_front(newphotopage);
	}
	

	LayoutBoxPos pagepos;

	if (photopage->isLeft() )
	{
		pagepos.x = 0.5;
		pagepos.y = 0;
		pagepos.width = 0.5;
		pagepos.height = 1;
		pagepos.margin.left = 0.004;
		pagepos.margin.right = 0.01;
		pagepos.margin.top = pagepos.margin.bottom = 0.02;

		newphotopage->setPagePosInPaper(pagepos);
		pagepos.x = 0;
		//pagepos.margin.right = 0;
		//pagepos.margin.left = 0.01;
		pagepos.margin.left = 0.01;
		pagepos.margin.right = 0.004;

		photopage->setPagePosInPaper(pagepos);
		pagelayout = _getLayoutMatch2Panor(pagelayout);
		newphotopage->setLayout(pagelayout,this->getborder(), false);
	}
	else
	{
		pagepos.x = 0;
		pagepos.y = 0;
		pagepos.width = 0.5;
		pagepos.height = 1;
		pagepos.margin.left = 0.01;
		pagepos.margin.right = 0.004;
		pagepos.margin.top = pagepos.margin.bottom = 0.02;

		newphotopage->setPagePosInPaper(pagepos);
		pagepos.x = 0.5;
		pagepos.margin.left = 0.004;
		pagepos.margin.right = 0.01;

		photopage->setPagePosInPaper(pagepos);
		pagelayout = _getLayoutMatch2Panor(pagelayout);
		photopage->setLayout(pagelayout,this->getborder(), false);
	}


	return true;
}

bool PmPrintPaperPage::mergePhotoPage()
{
	// should be 2 pages
	if ( this->_photoPages.size() != 2 )
	{
		return false;
	}
	PmPhotoPage *photopage = _photoPages.back();
	_photoPages.pop_back();

	photopage = _photoPages.back();
	if ( !photopage )
	{
		return false;
	}
	LayoutBoxPos pagepos;
	photopage->getPagePosInPaper(pagepos);
	pagepos.x = 0;
	pagepos.y = 0;
	pagepos.height = 1;
	pagepos.width = 1;

	pagepos.x = 0;
	pagepos.y = 0;
	pagepos.width = 1;
	pagepos.height = 1;
	pagepos.margin.left = 0.01;
	pagepos.margin.right = 0.01;
	pagepos.margin.top = pagepos.margin.bottom = 0.02;


	photopage->setPagePosInPaper(pagepos);

	return true;
}
#endif

bool PmPrintPaperPage::_need2SplitPage(PmPhotoPage *pPhotoPage, PHOTO_LAYOUT newlayout)
{
	PHOTO_LAYOUT currentlayout = pPhotoPage->getLayout();

	// current panor, new not panor
	switch( currentlayout )
	{
	case PP_LAYOUT_FULLSIZE_PANOR:
	case PP_LAYOUT_BORDER_PANOR:
	case PP_LAYOUT_PB8X5_FULLSIZE_PANOR:
	case PP_LAYOUT_PB8X5_TRADITION_PANOR:
	case PP_LAYOUT_PB8X5_HORIZON_PANOR:
	case PP_LAYOUT_PB8X5_VERTICON_PANOR:
		{
			if ( newlayout != PP_LAYOUT_FULLSIZE_PANOR &&
				newlayout != PP_LAYOUT_BORDER_PANOR &&
				newlayout != PP_LAYOUT_PB8X5_FULLSIZE_PANOR &&
				newlayout != PP_LAYOUT_PB8X5_TRADITION_PANOR &&
				newlayout != PP_LAYOUT_PB8X5_HORIZON_PANOR &&
				newlayout != PP_LAYOUT_PB8X5_VERTICON_PANOR )
			{
				return true;
			}
		}
	default:
		;
	}
	return false;
}

PHOTO_LAYOUT PmPrintPaperPage::_getLayoutBind2PanoramaLayout(PHOTO_LAYOUT panoramalayout)
{
	switch(panoramalayout)
	{
	case PP_LAYOUT_FULLSIZE_PANOR:
		return PP_LAYOUT_FULLSIZE_SINGLE;
		break;
	case PP_LAYOUT_BORDER_PANOR:
		return PP_LAYOUT_BORDER_SINGLE;
		break;
	case PP_LAYOUT_PB8X5_FULLSIZE_PANOR:
		return PP_LAYOUT_PB8X5_FULLSIZE_B;
		break;
	case PP_LAYOUT_PB8X5_TRADITION_PANOR:
		return PP_LAYOUT_PB8X5_TRADITION_B;
		break;
	case PP_LAYOUT_PB8X5_HORIZON_PANOR:
		return PP_LAYOUT_PB8X5_HORIZON_B;
		break;
	case PP_LAYOUT_PB8X5_VERTICON_PANOR:
		return PP_LAYOUT_PB8X5_VERTICON_B;
		break;
	default:
		;
	}
	return PP_LAYOUT_FULLSIZE_SINGLE;
}

bool PmPrintPaperPage::_isPanoramaLayout(PHOTO_LAYOUT layout)
{
	if ( layout != PP_LAYOUT_FULLSIZE_PANOR &&
		layout != PP_LAYOUT_BORDER_PANOR &&
		layout != PP_LAYOUT_PB8X5_FULLSIZE_PANOR &&
		layout != PP_LAYOUT_PB8X5_TRADITION_PANOR &&
		layout != PP_LAYOUT_PB8X5_HORIZON_PANOR &&
		layout != PP_LAYOUT_PB8X5_VERTICON_PANOR )
	{
		return false;
	}

	return true;

}

bool PmPrintPaperPage::_switch2AnotherPanorama(PmPhotoPage *pPhotoPage, PHOTO_LAYOUT newlayout)
{
	PHOTO_LAYOUT currentlayout = pPhotoPage->getLayout();

	// current not panor, new  panor

	if ( _isPanoramaLayout(currentlayout) && _isPanoramaLayout(newlayout) && (currentlayout != newlayout) )
	{
		return true;
	}

	return false;

}

bool PmPrintPaperPage::_need2BindPage(PmPhotoPage *pPhotoPage, PHOTO_LAYOUT newlayout)
{
	PHOTO_LAYOUT currentlayout = pPhotoPage->getLayout();

	// current not panor, new  panor

	if ( !this->_isPanoramaLayout(currentlayout) && _isPanoramaLayout(newlayout) )
	{	
		return true;
	}

	return false;
}

void PmPrintPaperPage::_clearImgOff()
{
	QList<PmPhotoPage*> pages;
	this->getPhotoPages(pages);

	QList<PmPhotoPage*>::iterator it;
	for ( it=pages.begin(); it!=pages.end(); it++ )
	{
		PmPhotoPage *photopage = *it;
		if ( !photopage )
		{
			continue;
		}
		QList<PmPageItm *> pageitmlst;
		photopage->getPicItms(pageitmlst);
		QList<PmPageItm *>::iterator pageitmit;
		for ( pageitmit = pageitmlst.begin(); pageitmit!=pageitmlst.end(); pageitmit++ )
		{
			PmPageItm *pageitm = *pageitmit;
			if ( !pageitm )
			{
				continue;
			}
			pageitm->clearImgLeftTop();
		}
	}


}

bool PmPrintPaperPage::setLayout(PmPhotoPage *pPhotoPage, PHOTO_LAYOUT layout,LAYOUT_POS layoutpos)
{
	if ( !pPhotoPage )
	{
		return false;
	}

	if ( layout == pPhotoPage->getLayout() )
	{
		// no need to update
		return true;
	}

	// check if panorama

	if ( this->_need2BindPage(pPhotoPage, layout) || this->_switch2AnotherPanorama(pPhotoPage, layout) )
	{
			//this->mergePhotoPage();
			// shoud be only one page now
			QList<PmPhotoPage*> pages;
			this->getPhotoPages(pages);

			if ( pages.size() == 1 )
			{
				// first or last page, just set the layout
				PHOTO_LAYOUT panoramalayout = pPhotoPage->getLayout();
				PHOTO_LAYOUT panoramarelatedly = this->_getLayoutBind2PanoramaLayout(panoramalayout);
				pPhotoPage->setLayout(layout,this->getborder(),  pPhotoPage->isLeft() );
				return true;
			}
			else
			{
				if ( pPhotoPage->isLeft() )
				{
					//
					pPhotoPage->setLayout(layout, this->getborder(), true);
					PmPhotoPage *pRightPage = new PmPhotoPage(*pPhotoPage);
					pRightPage->setIsLeft(false);
					pRightPage->setLayout(layout,this->getborder(), false);
					PmPhotoPage *pOldRight = pages.back();
					
					LayoutBoxPos pagepos;
					pOldRight->getPagePosInPaper(pagepos);
					pRightPage->setPagePosInPaper(pagepos);
					delete pOldRight;

					pages.clear();
					pPhotoPage->setPaperPage(this);
					pRightPage->setPaperPage(this);
					pages.push_back(pPhotoPage);
					pages.push_back(pRightPage);
					this->setPhotoPages(pages);

				}
				else
				{
					pPhotoPage->setLayout(layout, this->getborder(), false);
					PmPhotoPage *pLeftPage = new PmPhotoPage(*pPhotoPage);
					pLeftPage->setIsLeft(true);
					pLeftPage->setLayout(layout,this->getborder(), true);
					PmPhotoPage *pOldLeft = pages.first();

					LayoutBoxPos pagepos;
					pOldLeft->getPagePosInPaper(pagepos);
					pLeftPage->setPagePosInPaper(pagepos);

					delete pOldLeft;
					pages.clear();

					pPhotoPage->setPaperPage(this);
					pLeftPage->setPaperPage(this);
					pages.push_back(pLeftPage);
					pages.push_back(pPhotoPage);
					this->setPhotoPages(pages);
				}

				// clear imgoff 
				_clearImgOff();

			}

			return true;
	}
	else if ( this->_need2SplitPage(pPhotoPage, layout) )
	{
		PHOTO_LAYOUT panoramalayout = pPhotoPage->getLayout();
		PHOTO_LAYOUT panoramarelatedly = this->_getLayoutBind2PanoramaLayout(panoramalayout);

		QList<PmPhotoPage*> pages;
		this->getPhotoPages(pages);

		PmPhotoPage *pOtherPage;
		if ( pPhotoPage->isLeft() )
		{
			// upate right page
			pOtherPage = pages.back();
		}
		else
		{
			pOtherPage = pages.first();
		}
		pOtherPage->setLayout(panoramarelatedly, getborder(), pOtherPage->isLeft(), true);
		pPhotoPage->setLayout(layout,this->getborder(), pPhotoPage->isLeft());
				
		_clearImgOff();

		return true;
	}
	else
	{
		pPhotoPage->setLayout(layout,this->getborder(),  layoutpos == LF_PG_LAYOUT );
	}


	return true;
}

bool PmPrintPaperPage::getPhotoPages(QList<PmPhotoPage *> &photopages)
{
	photopages = _photoPages;
	return true;
}

bool PmPrintPaperPage::setPhotoPages(const QList<PmPhotoPage *> &photopages)
{
	_photoPages.clear();
	_photoPages = photopages;
	return true;
}


bool PmPrintPaperPage::addTextbox(PmTextItm *pTextItm)
{
	if ( pTextItm )
	{
		pTextItm->setPrintPage(this);
		this->_txtlst.push_back(pTextItm);
	}
	else
	{
		PmTextItm *txtitm = new PmTextItm(this);
		txtitm->setPrintPage(this);

		LayoutBoxPos rect;
		if ( 2 == this->_photoPages.size() )
		{
			rect.x = 0.1;
		}
		else
		{
			rect.x = 0.6;
		}
		rect.y = 0.5;
		rect.width = 0.5;
		rect.height = 0.05;
		txtitm->setRectInPrintPage(rect);
		_txtlst.push_back(txtitm);
	}

	return true;
}


bool PmPrintPaperPage::getTextbox(QList<PmTextItm *> &txtlst)
{

	if ( !_txtlst.size() )
	{
		return false;
	}

	/*
	LayoutBoxPos pos;
	pos.x = 0.2;
	pos.y = 0.4;
	pos.width = 0.25;
	pos.height = 0.02;
	//pos.margin
	_pTextItem->setRectInPrintPage(pos);

	pTextItm =  _pTextItem;
	*/
	txtlst = _txtlst;
	return true;
}

bool PmPrintPaperPage::delTextbox(PmTextItm *pTextItm)
{
	QList<PmTextItm *>::iterator it;
	for ( it=_txtlst.begin(); it!=_txtlst.end(); it++ )
	{
		if ( *it == pTextItm )
		{
			_txtlst.erase(it);
			break;
		}

	}

	return true;
}



Pm8x5PrintPaper::Pm8x5PrintPaper(bool hasborder, QObject *parent, PAGE_POS_INBOOK pos):PmPrintPaperPage(parent, pos), _borderless(!hasborder)
{
	qreal border = 0.06;
	if ( pos == NORMAL_PAGE )
	{
		PmPhotoPage *pLeftPage, *pRightPage;
		pLeftPage = new PmPhotoPage(this);
		LayoutBoxPos pagepos;
		pagepos.x = 0;
		pagepos.y = 0;
		pagepos.width = 0.5;
		pagepos.height = 1;


		pagepos.margin.top = pagepos.margin.bottom = 0;
		pagepos.margin.left = 0;
		pagepos.margin.right = 0;

		if ( hasborder )
		{
			// left page
			pagepos.margin.left = 0;
			pagepos.margin.right = border;

		}

		pLeftPage->setPagePosInPaper(pagepos);
		pLeftPage->setPaperPage(this);
		pLeftPage->setBorder(!_borderless);

		pRightPage = new PmPhotoPage(this);
		pagepos.x = 0.5;


		if ( hasborder )
		{
			// left page
			pagepos.margin.left = border;
			pagepos.margin.right = 0;
		}

		pRightPage->setPagePosInPaper(pagepos);
		pRightPage->setIsLeft(false);
		pRightPage->setBorder(!_borderless);
		pRightPage->setPaperPage(this);
		_photoPages.push_back(pLeftPage);
		_photoPages.push_back(pRightPage);
	}
	else if(  pos == FIRST_PAGE )
	{
		// HAS NO LEFT PAGE
		PmPhotoPage *pLeftPage, *pRightPage;
		LayoutBoxPos pagepos;

		pagepos.width = 0.5;
		pagepos.height = 1;
		pagepos.margin.top = pagepos.margin.bottom = 0;


		pRightPage = new PmPhotoPage(this);
		pagepos.x = 0.5;
		pagepos.y = 0;
		
		if ( hasborder )
		{
			pagepos.margin.left = border;
			pagepos.margin.right = 0; 
		}
		pRightPage->setPagePosInPaper(pagepos);
		pRightPage->setIsLeft(false);
		pRightPage->setBorder(!_borderless);
		pRightPage->setPaperPage(this);
		//_photoPages.push_back(pLeftPage);
		_photoPages.push_back(pRightPage);
	}
	else
	{
		PmPhotoPage *pLeftPage, *pRightPage;
		LayoutBoxPos pagepos;

		pagepos.x = 0;
		pagepos.y = 0;
		pagepos.width = 0.5;
		pagepos.height = 1;

		pagepos.margin.top = pagepos.margin.bottom = 0;

		pLeftPage = new PmPhotoPage(this);
		pLeftPage->setPagePosInPaper(pagepos);
		pLeftPage->setPaperPage(this);
		pLeftPage->setBorder(!_borderless);

		pagepos.x = 0.5;
		if ( hasborder )
		{
			pagepos.margin.right = border;
			pagepos.margin.left = 0;
		}

		_photoPages.push_back(pLeftPage);
	}

	//
	// width(1-0.014-0.014-0.0086568*2)/(height(1-0.0197869-0.0197869)) = 1169/827
	//
	// width / height = 1169/827 * (1-2*0.0197869)/(1-0.014*2-0.0086568)
	//
	_size = QSize(1409, 1000);
}

Pm8x5PrintPaper::~Pm8x5PrintPaper()
{
}

void Pm8x5PrintPaper::getSize(QSize &size)
{
	size = _size;
}

bool Pm8x5PrintPaper::getMarginInEditView(LayoutBoxMargin &marginInEditView)
{
	marginInEditView.left = 0.014;  // leftmargin/viewsize
	marginInEditView.right = 0.014;
	marginInEditView.mid = 0.0086568;
	marginInEditView.top = 0.0197869;
	marginInEditView.bottom = 0.0197869;

	return true;
}


bool Pm8x5PrintPaper::getBackGroundImgInEditView(QString &imgpath)
{
	imgpath = gbires + "layout/8x5background.png";
	return true;
}



void Pm8x5PrintPaper::rotate()
{
	QSize newsize(_size.height(), _size.width());
	_size = newsize;
}




PmTextItm::PmTextItm(QObject *parent):_pPage(NULL),
	_aligntype(ALIGN_TOP|ALIGN_LEFT),_shadow(true), _viewitm(NULL),
	_scale(1), _rotate(0)
{
	_lastbacktime = QDateTime::currentDateTime();
}

PmTextItm::PmTextItm(PmTextItm &txtitm)
{
	_layoutbox = txtitm._layoutbox;
	_pPage = NULL; // set later

	_cnt = txtitm._cnt;
	_scale = txtitm._scale;
	_rotate = txtitm._rotate;
	_shadow = txtitm._shadow;
	_aligntype = txtitm._aligntype;

	_viewitm = NULL;  // will be set when show the item in ui

}




Pm10x15PrintPaper::Pm10x15PrintPaper(bool hasborder, QObject *parent, PAGE_POS_INBOOK pos):PmPrintPaperPage(parent, pos), _borderless(!hasborder)
{

	PmPhotoPage *pPage;
	pPage = new PmPhotoPage(this);
	LayoutBoxPos pagepos;
	pagepos.x = 0;
	pagepos.y = 0;
	pagepos.width = 1;
	pagepos.height = 1;
	pagepos.margin.left = 0;
	pagepos.margin.right = 0;
	pagepos.margin.top = pagepos.margin.bottom = 0;

	pPage->setPagePosInPaper(pagepos);
	pPage->setPaperPage(this);
	pPage->setBorder(false);
	//pPage->setLayout(PP_LAYOUT_FULLSIZE_SINGLE,false,true);

	_photoPages.push_back(pPage);
	_size = QSize(8, 5);
}

Pm10x15PrintPaper::~Pm10x15PrintPaper()
{
}

void Pm10x15PrintPaper::getSize(QSize &size)
{
	size = _size;
}

bool Pm10x15PrintPaper::getMarginInEditView(LayoutBoxMargin &marginInEditView)
{
	marginInEditView.left = 0.0664;  // leftmargin/viewsize
	marginInEditView.right = 0;
	marginInEditView.mid = 0;
	marginInEditView.top = 0;
	marginInEditView.bottom = 0.001;

	return true;
}

bool Pm10x15PrintPaper::getBackGroundImgInEditView(QString &imgpath)
{
	imgpath = gbires + "layout/10x15background.png";
	return true;
}



void Pm10x15PrintPaper::rotate()
{
	return ;
	QSize newsize(_size.height(), _size.width());
	_size = newsize;
}




Pm4x3PrintPaper::Pm4x3PrintPaper(bool hasborder, QObject *parent, PAGE_POS_INBOOK pos):PmPrintPaperPage(parent, pos), _borderless(!hasborder)
{
	if ( pos == NORMAL_PAGE )
	{
		PmPhotoPage *pLetPage, *pRightPage;
		pLetPage = new PmPhotoPage(this);
		LayoutBoxPos pagepos;
		pagepos.x = 0;
		pagepos.y = 0;
		pagepos.width = 0.5;
		pagepos.height = 1;
		pagepos.margin.left = 0;
		pagepos.margin.right = 0.00535;
		pagepos.margin.top = pagepos.margin.bottom = 0;

		pLetPage->setPagePosInPaper(pagepos);
		pLetPage->setPaperPage(this);
		pLetPage->setBorder(false);
		pLetPage->setIsLeft(true);

		_photoPages.push_back(pLetPage);


		pRightPage = new PmPhotoPage(this);
		pagepos.x = 0.5;
		pagepos.y = 0;
		pagepos.width = 0.5;
		pagepos.height = 1;
		pagepos.margin.left = 0.00535;
		pagepos.margin.right = 0;
		pagepos.margin.top = pagepos.margin.bottom = 0;

		pRightPage->setPagePosInPaper(pagepos);
		pRightPage->setPaperPage(this);
		pRightPage->setBorder(false);
		pRightPage->setIsLeft(false);

		_photoPages.push_back(pRightPage);
	}
	else if(  pos == FIRST_PAGE )
	{
		// HAS NO LEFT PAGE
		PmPhotoPage *pLetPage, *pRightPage;
		LayoutBoxPos pagepos;


		pRightPage = new PmPhotoPage(this);
		pagepos.x = 0.5;
		pagepos.y = 0;
		pagepos.width = 0.5;
		pagepos.height = 1;
		pagepos.margin.left = 0.00535;
		pagepos.margin.right = 0;
		pagepos.margin.top = pagepos.margin.bottom = 0;

		pRightPage->setPagePosInPaper(pagepos);
		pRightPage->setPaperPage(this);
		pRightPage->setBorder(false);
		pRightPage->setIsLeft(false);

		_photoPages.push_back(pRightPage);
	}
	else
	{
		PmPhotoPage *pLetPage, *pRightPage;
		pLetPage = new PmPhotoPage(this);
		LayoutBoxPos pagepos;
		pagepos.x = 0;
		pagepos.y = 0;
		pagepos.width = 0.5;
		pagepos.height = 1;
		pagepos.margin.left = 0;
		pagepos.margin.right = 0.00535;
		pagepos.margin.top = pagepos.margin.bottom = 0;

		pLetPage->setPagePosInPaper(pagepos);
		pLetPage->setPaperPage(this);
		pLetPage->setBorder(false);
		pLetPage->setIsLeft(true);

		_photoPages.push_back(pLetPage);

	}



	_size = QSize(3, 2);
}

Pm4x3PrintPaper::~Pm4x3PrintPaper()
{
}

void Pm4x3PrintPaper::getSize(QSize &size)
{
	size = _size;
}

bool Pm4x3PrintPaper::getMarginInEditView(LayoutBoxMargin &marginInEditView)
{
	marginInEditView.left = 0.014;  // leftmargin/viewsize
	marginInEditView.right = 0.014;
	marginInEditView.mid = 0.0086568;
	marginInEditView.top = 0.0197869;
	marginInEditView.bottom = 0.0197869;

	return true;
}


bool Pm4x3PrintPaper::getBackGroundImgInEditView(QString &imgpath)
{
	imgpath = gbires + "layout/8x5background.png";
	return true;
}



void Pm4x3PrintPaper::rotate()
{
	return ;
	QSize newsize(_size.height(), _size.width());
	_size = newsize;
}






PmA4CalPrintPaper::PmA4CalPrintPaper(bool hasborder, PROJ_PROPS::LAYOUT_TYPE lytype, QObject *parent, PAGE_POS_INBOOK pos):PmPrintPaperPage(parent, pos), _borderless(!hasborder)
{
	PmPhotoPage *pPage;
	pPage = new PmPhotoPage(this);
	LayoutBoxPos pagepos;

	if ( pos == LAST_PAGE )
	{
		// last is font page
		pagepos.x = 0;
		pagepos.y = 0;
		pagepos.width = 1;
		pagepos.height = 1;
		pagepos.margin.left = 0;
		pagepos.margin.right = 0;
		pagepos.margin.top = pagepos.margin.bottom = 0;
		pPage->setLayout(PP_LAYOUT_CALENDARA4_BORDER_FONTPG,false, false);
	}
	else
	{
		if ( lytype == PROJ_PROPS::LYCALA4L1 )
		{
			pagepos.x = 0;
			pagepos.y = 0;
			pagepos.width = 1;
			pagepos.height = 1;
			pagepos.margin.left = 0;
			pagepos.margin.right = 0;
			pagepos.margin.top = pagepos.margin.bottom = 0;

			pPage->setLayout(PP_LAYOUT_CALENDAR_A4_L1_L1,false, false);
		}
		else if ( lytype == PROJ_PROPS::LYCALA4L2 )
		{
			pagepos.x = 0;
			pagepos.y = 0;
			pagepos.width = 1;
			pagepos.height = 1;
			pagepos.margin.left = 0.053879;
			pagepos.margin.right = 0.053879;
			pagepos.margin.top = 0.053879;
			pagepos.margin.bottom = 0.05945124;

			pPage->setLayout(PP_LAYOUT_CALENDAR_A4_L1_L2,false, false);
		}
		else if ( lytype == PROJ_PROPS::LYCALA4L3 )
		{
			pagepos.x = 0;
			pagepos.y = 0;
			pagepos.width = 1;
			pagepos.height = 1;
			pagepos.margin.left = 0;
			pagepos.margin.right = 0;
			pagepos.margin.top = pagepos.margin.bottom = 0;

			pPage->setLayout(PP_LAYOUT_CALENDAR_A4_L1_L3,false, false);
		}
		else if ( lytype == PROJ_PROPS::LYCALA4L4 )
		{
			pagepos.x = 0;
			pagepos.y = 0;
			pagepos.width = 1;
			pagepos.height = 1;
			pagepos.margin.left = 0;
			pagepos.margin.right = 0;
			pagepos.margin.top = pagepos.margin.bottom = 0;

			pPage->setLayout(PP_LAYOUT_CALENDAR_A4_L1_L4,false, false);
		}
	}
	pPage->setPagePosInPaper(pagepos);
	pPage->setPaperPage(this);
	pPage->setBorder(false);
	pPage->setIsLeft(true);
	_photoPages.push_back(pPage);


	_size = QSize(5, 7);
}

PmA4CalPrintPaper::~PmA4CalPrintPaper()
{
}

void PmA4CalPrintPaper::getSize(QSize &size)
{
	size = _size;
}

bool PmA4CalPrintPaper::getMarginInEditView(LayoutBoxMargin &marginInEditView)
{
	marginInEditView.left = 0;
	marginInEditView.right = 0;
	marginInEditView.top = 0;
	marginInEditView.bottom = 0;

	return true;
}


bool PmA4CalPrintPaper::getBackGroundImgInEditView(QString &imgpath)
{
	//imgpath = gbires + "layout/Calendar.png";
	//imgpath = "";
	return true;
}



void PmA4CalPrintPaper::rotate()
{
	return ;
	QSize newsize(_size.height(), _size.width());
	_size = newsize;
}




PmA5CalPrintPaper::PmA5CalPrintPaper(bool hasborder, PROJ_PROPS::LAYOUT_TYPE lytype, QObject *parent, PAGE_POS_INBOOK pos):PmPrintPaperPage(parent, pos), _borderless(!hasborder)
{
	PmPhotoPage *pPage;
	pPage = new PmPhotoPage(this);
	LayoutBoxPos pagepos;


	if ( pos == LAST_PAGE )
	{
		// last is font page
		pagepos.x = 0;
		pagepos.y = 0;
		pagepos.width = 1;
		pagepos.height = 1;
		pagepos.margin.left = 0;
		pagepos.margin.right = 0;
		pagepos.margin.top = pagepos.margin.bottom = 0;
		pPage->setLayout(PP_LAYOUT_CALENDARA5_BORDER_FONTPG,false, false);
	}
	else
	{
		if ( lytype == PROJ_PROPS::LYCALA5L1 )
		{
			pagepos.x = 0;
			pagepos.y = 0;
			pagepos.width = 1;
			pagepos.height = 1;
			pagepos.margin.left = 0.05166846;
			pagepos.margin.right = 0.05166846;
			pagepos.margin.top = 0.09893455;
			pagepos.margin.bottom = 0.07306545;
			pPage->setLayout(PP_LAYOUT_CALENDAR_A5_L1_L1,false, false);
		}
		else if ( lytype == PROJ_PROPS::LYCALA5L2 )
		{
			pagepos.x = 0;
			pagepos.y = 0;
			pagepos.width = 1;
			pagepos.height = 1;
			pagepos.margin.left = 0;
			pagepos.margin.right = 0;
			pagepos.margin.top = pagepos.margin.bottom = 0;
			pPage->setLayout(PP_LAYOUT_CALENDAR_A5_L2_L1,false, false);
		}
		else if ( lytype == PROJ_PROPS::LYCALA5L3 )
		{
			pagepos.x = 0;
			pagepos.y = 0;
			pagepos.width = 1;
			pagepos.height = 1;
			pagepos.margin.left = 0;
			pagepos.margin.right = 0;
			pagepos.margin.top = 0.12937595;
			pagepos.margin.bottom = 0;
			pPage->setLayout(PP_LAYOUT_CALENDAR_A5_L3_L1,false, false);
		}
	}
	pPage->setPagePosInPaper(pagepos);
	pPage->setPaperPage(this);
	pPage->setBorder(false);
	pPage->setIsLeft(true);

	_photoPages.push_back(pPage);



	_size = QSize(7, 5);
}

PmA5CalPrintPaper::~PmA5CalPrintPaper()
{
}

void PmA5CalPrintPaper::getSize(QSize &size)
{
	size = _size;
}

bool PmA5CalPrintPaper::getMarginInEditView(LayoutBoxMargin &marginInEditView)
{
	marginInEditView.left = 0;
	marginInEditView.right = 0;
	marginInEditView.top = 0;
	marginInEditView.bottom = 0;

	return true;
}


bool PmA5CalPrintPaper::getBackGroundImgInEditView(QString &imgpath)
{
	//imgpath = gbires + "layout/Calendar.png";
	return true;
}



void PmA5CalPrintPaper::rotate()
{
	return ;
	QSize newsize(_size.height(), _size.width());
	_size = newsize;
}




Pm4x6CalPrintPaper::Pm4x6CalPrintPaper(bool hasborder, PROJ_PROPS::LAYOUT_TYPE lytype,QObject *parent, PAGE_POS_INBOOK pos):PmPrintPaperPage(parent, pos), _borderless(!hasborder)
{
	PmPhotoPage *pPage;
	pPage = new PmPhotoPage(this);
	LayoutBoxPos pagepos;

	if ( pos == LAST_PAGE )
	{
		// last is font page
		pagepos.x = 0;
		pagepos.y = 0;
		pagepos.width = 1;
		pagepos.height = 1;
		pagepos.margin.left = 0;
		pagepos.margin.right = 0;
		pagepos.margin.top = pagepos.margin.bottom = 0;
		pPage->setLayout(PP_LAYOUT_CALENDAR4x6_BORDER_FONTPG,false, false);
	}
	else
	{
		if ( lytype == PROJ_PROPS::LYCAL4X6L1 )
		{
			pagepos.x = 0;
			pagepos.y = 0;
			pagepos.width = 1;
			pagepos.height = 1;
			pagepos.margin.left = 0;
			pagepos.margin.right = 0;
			pagepos.margin.top = 0.14176825;
			pagepos.margin.bottom = 0;
			pPage->setLayout(PP_LAYOUT_CALENDAR_4X6_L1_L1,false, false);


		}
		else if ( lytype == PROJ_PROPS::LYCAL4X6L2)
		{
			//
			pagepos.x = 0;
			pagepos.y = 0;
			pagepos.width = 1;
			pagepos.height = 1;
			pagepos.margin.left = 0.0535;
			pagepos.margin.right = 0.0535;
			pagepos.margin.top = 0.099;
			pagepos.margin.bottom = 0.035;
			pPage->setLayout(PP_LAYOUT_CALENDAR_4X6_L2_L1,false, false);

		}
		else if ( lytype == PROJ_PROPS::LYCAL4X6L3 )
		{
			pagepos.x = 0;
			pagepos.y = 0;
			pagepos.width = 1;
			pagepos.height = 1;
			pagepos.margin.left = 0;
			pagepos.margin.right = 0;
			pagepos.margin.top = 0.082317;
			pagepos.margin.bottom = 0;
			pPage->setLayout(PP_LAYOUT_CALENDAR_4X6_L3_L1,false, false);

		}
		else if ( lytype == PROJ_PROPS::LYCAL4X6L4 )
		{
			pagepos.x = 0;
			pagepos.y = 0;
			pagepos.width = 1;
			pagepos.height = 1;
			pagepos.margin.left = 0;
			pagepos.margin.right = 0;
			pagepos.margin.top = 0.06859756;
			pagepos.margin.bottom = 0;
			pPage->setLayout(PP_LAYOUT_CALENDAR_4X6_L4_L1,false, false);

		}
	}

	pPage->setPagePosInPaper(pagepos);
	pPage->setPaperPage(this);
	pPage->setBorder(false);
	pPage->setIsLeft(true);

	_photoPages.push_back(pPage);


	_size = QSize(5, 8);
}

Pm4x6CalPrintPaper::~Pm4x6CalPrintPaper()
{
}

void Pm4x6CalPrintPaper::getSize(QSize &size)
{
	size = _size;
}

bool Pm4x6CalPrintPaper::getMarginInEditView(LayoutBoxMargin &marginInEditView)
{
	marginInEditView.left = 0; //0.021;
	marginInEditView.right = 0; //0.021;
	marginInEditView.top = 0; //0.03;
	marginInEditView.bottom = 0;//0.03;

	return true;
}


bool Pm4x6CalPrintPaper::getBackGroundImgInEditView(QString &imgpath)
{
	//imgpath = gbires + "layout/Calendar4x6bg.png";
	return true;
}


void Pm4x6CalPrintPaper::rotate()
{
	return ;
	QSize newsize(_size.height(), _size.width());
	_size = newsize;
}


bool ColorMgr::getColor(const QString &name, QColor &color)
{
	if ( name == COLOR_LIGHT_GREY_NAME )
	{
		color = QColor(COLOR_LIGHT_GREY_VALUE);
	}
	else if ( COLOR_GREY_NAME == name )
	{
		color = QColor(COLOR_GREY_VALUE);
	}
	else if ( COLOR_DARK_GREY_NAME == name )
	{
		color = QColor(COLOR_DARK_GREY_VALUE);
	}
	else if (   COLOR_BLACK_NAME == name )
	{
		color = QColor(COLOR_BLACK_VALUE);
	}
	else if ( COLOR_BRIGHT_YELLOW_NAME	== name )
	{
		color = QColor(COLOR_BRIGHT_YELLOW_VALUE);
	}
	else if (  COLOR_YELLOW_NAME	== name )
	{
		color = QColor(COLOR_YELLOW_VALUE);
	}
	else if ( COLOR_ORANGE_NAME	== name )
	{
		color = QColor(COLOR_ORANGE_VALUE);
	}
	else if (  COLOR_PINK_NAME	== name )
	{
		color = QColor(COLOR_PINK_VALUE);
	}
	else if(  COLOR_LIGHT_PINK_NAME	== name )
	{
		color = QColor(COLOR_LIGHT_PINK_VALUE);
	}
	else if (COLOR_BLUE_NAME	== name )
	{
		color = QColor(COLOR_BLUE_VALUE);
	}
	else if ( COLOR_LIGHT_BLUE_NAME	== name )
	{
		color = QColor(COLOR_LIGHT_BLUE_VALUE);
	}
	else if (  COLOR_LIGHT_GREEN_NAME	== name )
	{
		color = QColor(COLOR_LIGHT_GREEN_VALUE);
	}
	else if (  COLOR_GREEN_NAME	== name )
	{
		color = QColor(COLOR_GREEN_VALUE);
	}
	else if ( COLOR_CUSTOMER_NAME == name )
	{
		QColorDialog colordlg;
		if ( colordlg.exec() == QDialog::Accepted )
		{
			color = colordlg.currentColor();
		}
		else
		{
			return false;
		}

	}
	else
	{
		return false;
	}
	return true;
}
	
bool ColorMgr::getColorName(const QColor &color, QString &name)
{
	if ( color.rgb() == COLOR_LIGHT_GREY_VALUE )
	{
		name = COLOR_LIGHT_GREY_NAME;
	}
	else if (  color.rgb() == COLOR_GREY_VALUE	 )
	{
		name = COLOR_GREY_NAME;
	}
	else if ( color.rgb() ==  COLOR_DARK_GREY_VALUE )
	{
		name = COLOR_DARK_GREY_NAME;
	}
	else if ( color.rgb() ==  COLOR_BLACK_VALUE )
	{
		name = COLOR_BLACK_NAME;
	}
	else if ( color.rgb() == COLOR_BRIGHT_YELLOW_VALUE )
	{
		name = COLOR_BRIGHT_YELLOW_NAME;
	}
	else if ( color.rgb() == COLOR_YELLOW_VALUE )
	{
		name = COLOR_YELLOW_NAME;
	}
	else if ( color.rgb() ==  COLOR_ORANGE_VALUE	)
	{
		name = COLOR_ORANGE_NAME;
	}
	else if ( color.rgb() ==  COLOR_PINK_VALUE	)
	{
		name = COLOR_PINK_NAME;
	}
	else if ( color.rgb() == COLOR_LIGHT_PINK_VALUE )
	{
		name = COLOR_LIGHT_PINK_NAME;
	}
	else if ( color.rgb() == COLOR_BLUE_VALUE	)
	{
		name = COLOR_BLUE_NAME;
	}
	else if ( color.rgb() ==  COLOR_LIGHT_BLUE_VALUE )
	{
		name = COLOR_LIGHT_BLUE_NAME;
	}
	else if (  color.rgb() == COLOR_LIGHT_GREEN_VALUE	)
	{
		name = COLOR_LIGHT_GREEN_NAME;
	}
	else if ( color.rgb() ==  COLOR_GREEN_VALUE )
	{
		name = COLOR_GREEN_NAME;
	}
	else
	{
		return false;
	}

	return true;
}
