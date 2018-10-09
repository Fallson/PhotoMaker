#include "pmphotomakerdoc.h"
#include <QFile>
#include <QDir> 
#include "base64.h"

PmPhotoMakerDoc::PmPhotoMakerDoc(QObject *parent)
	: QObject(parent),_printpaperpage(NULL), _curpaperindex(0), _shadow(false),
	_nexteditpage(NULL), _lasteditpage(NULL)
{
	// default 8x5 now
	for ( int i=0; i<1; i++ )
	{
		_printpaperpage = new Pm8x5PrintPaper(false,this);
		_paperpages.push_back(_printpaperpage);
	}
	this->setCurPaperPage(_paperpages.first());
	_projprops.type = PROJ_PROPS::PHOTOBOOK8X5;
	_projprops.lytype = PROJ_PROPS::LY8X5TRADITION;
}

PmPhotoMakerDoc::~PmPhotoMakerDoc()
{

}
	
PmPageItm *PmPhotoMakerDoc::getCalItm(PmPrintPaperPage *paper)
{
	return _getCalItm(paper);
}

PmPageItm *PmPhotoMakerDoc::_getCalItm(PmPrintPaperPage *paper)
{
	if ( !paper )
	{
		return NULL;
	}

	QList<PmPhotoPage*> pages;
	paper->getPhotoPages(pages);
	PmPhotoPage *page = NULL;
	if ( pages.size() != 1 )
	{
		return NULL;
	}
	page = pages.first();
	QList<PmPageItm *> pageitms;
	if ( !page )
	{
		return NULL;
	}
	page->getPicItms(pageitms);
	QList<PmPageItm *>::iterator it;
	for ( it=pageitms.begin(); it!=pageitms.end(); it++ )
	{
		if ( (*it)->getPhotoItmType()== PmPageItm::CALENDAR_ITM )
		{
			break;
		}
	}
	if ( it!=pageitms.end() )
	{
		return *it;
	}
	return NULL;
}

bool PmPhotoMakerDoc::updateProjProps(const PROJ_PROPS &prj)
{
	// can only update some props
	if ( this->_projprops.firstmonth != prj.firstmonth )
	{
		// remove the 
		QList<PmPrintPaperPage *>::iterator it;

		if ( prj.firstmonth > _projprops.firstmonth )
		{
			// remove prj.firstmonth  -  _projprops.firstmonth  from front to back
			int count = prj.firstmonth  -  _projprops.firstmonth;
			while(count)
			{
				it = _paperpages.begin();
				if ( it!=_paperpages.end() )
				{
					//
					PmPrintPaperPage *paperpage = *it;
					_paperpages.removeFirst();
					PmPageItm *calitm = this->_getCalItm(paperpage);
					int year=0, month=0;
					calitm->getMonth(year, month);
					year++;
					calitm->setMonth(year, month);
					_paperpages.push_back(paperpage);
				}
				--count;
			}
		}
		else
		{
			// _projprops.firstmonth - prj.firstmonth from back to frond
			int count = _projprops.firstmonth  -  prj.firstmonth;
			while(count)
			{
				if ( !_paperpages.empty() )
				{
					//
					PmPrintPaperPage *paperpage = _paperpages.last();
					_paperpages.removeLast();
					int year=0, month=0;
					PmPageItm *calitm = this->_getCalItm(paperpage);
					calitm->getMonth(year, month);
					year--;
					calitm->setMonth(year, month);
					_paperpages.push_front(paperpage);
				}
				--count;
			}
		}
		this->_projprops.firstmonth = prj.firstmonth;
	}
	
	if (  this->_projprops.year != prj.year )
	{
		//
		QList<PmPrintPaperPage *>::iterator it;
		for ( it=_paperpages.begin(); it!=_paperpages.end(); it++ )
		{
			PmPageItm *calitm = this->_getCalItm(*it);
			if ( !calitm )
			{
				continue;
			}
			int year, month;
			calitm->getMonth(year, month);
			if ( month < _projprops.firstmonth )
			{
				year = prj.year + 1;
			}
			else
			{
				year = prj.year;
			}
			calitm->setMonth(year, month);
			_projprops.year = prj.year;
		}

	}
	
	if ( _projprops.shadow != prj.shadow )
	{
		_projprops.shadow = prj.shadow;
	}
	
	if ( _projprops.txtshadow != prj.txtshadow )
	{
		_projprops.txtshadow = prj.txtshadow;
	}
	
	return true;
}

bool PmPhotoMakerDoc::_getPhotoPageIndex(PmPhotoPage* photopage, int &index, PmPhotoPage* &nextphotopage)
{
	// find the index hold photopage
	PmPhotoPage* next = NULL;
	index = 0;
	QList<PmPrintPaperPage *>::iterator it;
	for ( it=this->_paperpages.begin(); it!=_paperpages.end(); it++ )
	{
		//
		QList<PmPhotoPage*>::iterator pageit;
		QList<PmPhotoPage*> photopages;
		(*it)->getPhotoPages(photopages);
		for ( pageit = photopages.begin(); pageit != photopages.end(); pageit++)
		{
			index++;
			if ( *pageit == photopage )
			{
				// find, 
				break;
			}
		}

		if ( pageit != photopages.end() )
		{
			// find the page
			if ( ++pageit != photopages.end() )
			{
				next = *pageit;
			}
			break;
		}

	}
	if ( it == _paperpages.end() )
	{
		// do not find the page
		return false;
	}

	// now pageit index the pages
	if ( !next )
	{
		if ( ++it != _paperpages.end() && *it )
		{
			QList<PmPhotoPage*> photopages;
			(*it)->getPhotoPages(photopages);
			if ( photopages.size() )
			{
				next = photopages.first();
			}
		}
		else
		{
			// already last page

		}
	}

	nextphotopage = next;

	return true;
}

bool PmPhotoMakerDoc::getPhotoPageIndex(PmPhotoPage* photopage, int &index)
{

	PmPhotoPage* nextpage = NULL;
	return this->_getPhotoPageIndex(photopage, index, nextpage);
}

bool PmPhotoMakerDoc::getLastEditPhotoPage( int &index)
{
	index = _projprops.lastphotopage;
	return true;
}

void PmPhotoMakerDoc::updateLastEditPage()
{
	_updateLastEditPage();
}

bool PmPhotoMakerDoc::updateLastPhotoPage(PmPhotoPage* photopage)
{
	// for calendar, no need to update last/next page
	switch(this->_projprops.type )
	{
	case PROJ_PROPS::CALENDARA4:
	case PROJ_PROPS::CALENDARA5:
	case PROJ_PROPS::CALENDAR4X6:
		return true;
	default:
		;
	}
	int index = 0;
	PmPhotoPage* nextpage = NULL;

	// check if this page is panorama page
	bool panorama = false;
	PHOTO_LAYOUT layout = photopage->getLayout();
	switch(layout)
	{
	case PP_LAYOUT_FULLSIZE_PANOR:
	case PP_LAYOUT_BORDER_PANOR:
	case PP_LAYOUT_PB8X5_FULLSIZE_PANOR:
	case PP_LAYOUT_PB8X5_TRADITION_PANOR:
	case PP_LAYOUT_PB8X5_HORIZON_PANOR:
	case PP_LAYOUT_PB8X5_VERTICON_PANOR:
		panorama = true;
		break;
	default:
		panorama = false;
		;
	}
	if ( panorama )
	{
		QList<PmPhotoPage *> pages;
		PmPrintPaperPage *paper = photopage->getPaperPage();
		paper->getPhotoPages(pages);
		if ( pages.size() == 2  && pages.first() == photopage )
		{
			photopage = pages.last();
		}
	}


	if ( !this->_getPhotoPageIndex(photopage, index, nextpage) )
	{
		return false;
	}

	if ( this->_projprops.lastphotopage < index  || index == 1)
	{
		_projprops.lastphotopage = index;
		this->_lasteditpage = photopage;
		this->_nexteditpage = nextpage;
	}

	// update next page

	return true;
}

bool PmPhotoMakerDoc::getNextEditPaper(PmPrintPaperPage * &nextPaper)
{
	if ( _nexteditpage )
	{
		nextPaper = _nexteditpage->getPaperPage();
	}
	else
	{
		nextPaper = NULL;
	}
	return true;
}

bool PmPhotoMakerDoc::getCurPrintPaperPage(PmPrintPaperPage *&pcurpaper, int &index)
{
	if ( _paperpages.size() )
	{
		pcurpaper =  _paperpages.at(this->_curpaperindex);
		index = _curpaperindex;
		return true;
	}

	return false;
}

PmPrintPaperPage *PmPhotoMakerDoc::_newPaper()
{
	PmPrintPaperPage *paper = NULL;
	switch( _projprops.type )
	{
		//
	case PROJ_PROPS::POCKETBOOK4X3:
		{
			paper = new Pm4x3PrintPaper(_projprops.hasborder,this);
			_constructDefLayout(_projprops.lytype, paper);
		}
		break;
	case PROJ_PROPS::PHOTOBOOK10X15:
		{
			paper = new Pm10x15PrintPaper(_projprops.hasborder,this);
			_constructDefLayout(_projprops.lytype, paper);
		}
		break;
	case PROJ_PROPS::SINGLE4X6:
		break;
	case PROJ_PROPS::PHOTOBOOK8X5:
		{
			//
			paper = new Pm8x5PrintPaper(_projprops.hasborder,this);
			_constructDefLayout(_projprops.lytype, paper);
		}
		break;
	case PROJ_PROPS::CALENDARA4:
		{
			//
			paper = new PmA4CalPrintPaper(false,_projprops.lytype,this);
			_constructDefLayout(_projprops.lytype, paper);
		}
		break;
	case PROJ_PROPS::CALENDARA5:
		{
			//
			paper = new PmA5CalPrintPaper(false,_projprops.lytype,this);
			_constructDefLayout(_projprops.lytype, paper);
		}
		break;
	case PROJ_PROPS::CALENDAR4X6:
		{
			//
			paper = new Pm4x6CalPrintPaper(false,_projprops.lytype,this);
			_constructDefLayout(_projprops.lytype, paper);
		}
		break;
	case PROJ_PROPS::DEFDEMO:
	default:
		;
	}
	return paper;
}

void PmPhotoMakerDoc::_updateLastEditPage()
{
	bool twopage = false;
	switch(this->_projprops.type)
	{
	case PROJ_PROPS::POCKETBOOK4X3:
	case PROJ_PROPS::PHOTOBOOK10X15:
	case PROJ_PROPS::SINGLE4X6:
		{
			twopage = false;
		}
		break;
	case PROJ_PROPS::PHOTOBOOK8X5:
		{
			twopage = true;
		}
		break;
	case PROJ_PROPS::CALENDARA4:
	case PROJ_PROPS::CALENDARA5:
	case PROJ_PROPS::CALENDAR4X6:
		{
			PmPrintPaperPage *paper = _paperpages.last();
			if ( !paper )
			{
				return ;
			}
			QList<PmPhotoPage *> photopages;
			paper->getPhotoPages(photopages);
			this->_lasteditpage = photopages.first();
			this->_nexteditpage = NULL;
			return ;
		}
		break;
	default:
		;
	}

	PmPhotoPage *lasteditpage = NULL;
	QList<PmPrintPaperPage *>::iterator it, lasteditpaperit = _paperpages.end();
	int i = 0;
	it=_paperpages.begin();
	for ( ; it!=_paperpages.end(); it++,i++ )
	{
		//
		PmPrintPaperPage *paper = *it;
		if ( !paper )
		{
			continue;
		}
		
		bool gotone = false;
		QList<PmPhotoPage *> photopages;
		paper->getPhotoPages(photopages);
		QList<PmPhotoPage *>::iterator pageit;
		for ( pageit=photopages.begin(); pageit!=photopages.end(); pageit++ )
		{
			//
			PmPhotoPage *page = *pageit;
			if ( !page )
			{
				continue;
			}
			QList<PmPageItm*> pageitmlst;
			page->getPicItms(pageitmlst);
			QList<PmPageItm*>::iterator pageitmit;
			for ( pageitmit = pageitmlst.begin(); pageitmit!=pageitmlst.end(); pageitmit++ )
			{
				PmPageItm *pageitm = *pageitmit;
				if ( !pageitm )
				{
					continue;
				}
				QString cnt;
				pageitm->getContent(cnt);
				if ( cnt.length() )
				{
					gotone = true;
					break;
				}
				QColor color;
				pageitm->getBgColor(color);
				if ( color.isValid() && color!=Qt::white )
				{
					gotone = true;
					break;
				}
			}
			if ( gotone )
			{
				break;
			}
		}

		//
		if ( gotone )
		{
			//
			lasteditpaperit = it;
			lasteditpage = *pageit;
		}
	}

	this->_lasteditpage = lasteditpage;
	QList<PmPhotoPage *> photopages;
	//
	if ( lasteditpaperit == _paperpages.end() )
	{
		//
		this->_lasteditpage = NULL;
		this->_nexteditpage = NULL;
	}
	else
	{
		//
		PmPrintPaperPage *lasteditpaper = *lasteditpaperit;
		lasteditpaper->getPhotoPages(photopages);
		if ( photopages.size() == 2 && lasteditpage == photopages.first())
		{
			//
			this->_nexteditpage = photopages.last();
		}
		else
		{
			QList<PmPrintPaperPage *>::iterator nexteditpaperit = lasteditpaperit+1;
			if ( nexteditpaperit != _paperpages.end() )
			{
				//
				PmPrintPaperPage *nexteditpaper = *nexteditpaperit;
				if ( !nexteditpaper )
				{
					this->_nexteditpage = NULL;
				}
				else
				{
					nexteditpaper->getPhotoPages(photopages);
					this->_nexteditpage = photopages.first();
				}

			}
			else
			{
				this->_nexteditpage = NULL;
			}
		}

	}
	int lastindex = 0;
	PmPhotoPage *pnextpage = NULL;

	if ( !this->_getPhotoPageIndex(this->_lasteditpage, lastindex, pnextpage) )
	{
		return ;
	}

	_projprops.lastphotopage = lastindex;

}

bool PmPhotoMakerDoc::insertPrintPaper(PmPrintPaperPage *newPaper, bool before, int index)
{
	//

	// get the item before the pos should be inserted
	QList<PmPrintPaperPage *>::iterator it;
	int i = 0;
	it=_paperpages.begin();
	for ( ; it!=_paperpages.end(); it++,i++ )
	{
		if ( i == index)
		{
			break;
		}
	}
	if ( it != _paperpages.end() )
	{
		if ( !before )
		{
			it++;
		}

		if ( it == _paperpages.end())
		{
			// insert as last one
			_paperpages.push_back(newPaper);
		}
		else
		{
			_paperpages.insert(it, newPaper);
		}
#if 0
		int lasteditpaperindex = 0, nexteditpaperindex = 0;
		this->getPaperIndex(_lasteditpage->getPaperPage(), lasteditpaperindex);
		this->getPaperIndex(_nexteditpage->getPaperPage(), nexteditpaperindex);
		if ( lasteditpaperindex < index )
		{
			// update last edit page
			QList<PmPhotoPage *> photopages;
			newPaper->getPhotoPages(photopages);
			_lasteditpage = photopages.back();
		}
		if ( nexteditpaperindex < index + 1 )
		{
			//
			PmPrintPaperPage *pnexteditpaper = NULL;
			this->getPaperFromIndex( pnexteditpaper, index + 1 );
			QList<PmPhotoPage *> photopages;
			if ( pnexteditpaper )
			{
				pnexteditpaper->getPhotoPages(photopages);
				this->_nexteditpage = photopages.first();
			}
		}
#endif
		_updateLastEditPage();
		return true;
	}

	// fail to find the one
	return false;
}

bool PmPhotoMakerDoc::addPrintPaper(PmPrintPaperPage *paper, bool before, PmPrintPaperPage *&newPaper, int &index)
{
	//

	QList<PmPrintPaperPage *>::iterator it;
	int i = 0;
	it=_paperpages.begin();
	for ( ; it!=_paperpages.end(); it++,i++ )
	{
		if ( *it == paper )
		{
			break;
		}
	}
	if ( it != _paperpages.end() )
	{
		newPaper = _newPaper();
		if ( !insertPrintPaper(newPaper, before, i) )
		{
			delete newPaper;
			newPaper = NULL;
			return false;
		}
		return true;
	}

	// fail to find the one
	return false;
}

bool PmPhotoMakerDoc::getPaperFromIndex(PmPrintPaperPage *&paper, int index)
{
	if ( index < 0  || index >= _paperpages.size() )
	{
		return false;
	}
	paper = _paperpages[index];
	return true;
}

bool PmPhotoMakerDoc::getPaperIndex(PmPrintPaperPage *paper, int &index)
{
	QList<PmPrintPaperPage *>::iterator it;
	int i = 0;
	it=_paperpages.begin();
	for ( ; it!=_paperpages.end(); it++,i++ )
	{
		if ( *it == paper )
		{
			break;
		}
	}
	if ( it != _paperpages.end() )
	{
		index = i;
		return true;
	}

	// fail to find the one
	return false;
}


bool PmPhotoMakerDoc::rmPrintPaper(PmPrintPaperPage *paper, int &index)
{
	QList<PmPrintPaperPage *>::iterator it;
	int i = 0;
	it=_paperpages.begin();
	for ( ; it!=_paperpages.end(); it++,i++ )
	{
		if ( *it == paper )
		{
			break;
		}
	}
	if ( it != _paperpages.end() )
	{
		index = i;

		// updte last eidt page
#if 0
		QList<PmPhotoPage *> photopages;
		(*it)->getPhotoPages(photopages);
		QList<PmPhotoPage *>::iterator pageit;
		for ( pageit=photopages.begin(); pageit!=photopages.end(); pageit++ )
		{
			//
			bool finished = false;
			if ( *pageit == this->_lasteditpage )
			{
				// last edit page changes
				if ( it == _paperpages.begin() )
				{
					this->_lasteditpage = NULL;
				}
				else
				{
					QList<PmPrintPaperPage *>::iterator newlasteditit = it-1;
					QList<PmPhotoPage *> pagesinlasteditpaper;
					(*newlasteditit)->getPhotoPages(pagesinlasteditpaper);
					if ( pagesinlasteditpaper.size() )
					{
						this->_lasteditpage = pagesinlasteditpaper.last();
					}
					else
					{
						_lasteditpage = NULL;
					}
					finished = true;
				}
			}

			if ( *pageit == this->_nexteditpage )
			{
				// last edit page changes

				QList<PmPrintPaperPage *>::iterator newnextditit = it+1;
				QList<PmPhotoPage *> pagesinlasteditpaper;
				if ( newnextditit != _paperpages.end() )
				{
					(*newnextditit)->getPhotoPages(pagesinlasteditpaper);
					if ( pagesinlasteditpaper.size() )
					{
						this->_nexteditpage = pagesinlasteditpaper.first();
					}
					else
					{
						_nexteditpage = NULL;
					}
				}
				else
				{
					_nexteditpage = NULL;
				}
				finished = true;
			}
			if ( finished )
			{
				break;
			}
		}
#endif
		_paperpages.erase(it);
	

		PmPrintPaperPage *_printpaperpage;
		if ( paper == this->_printpaperpage )
		{
			//
			_curpaperindex--;
			if ( _curpaperindex < 0 )
			{
				_curpaperindex = 0;
			}
			getPaperFromIndex(_printpaperpage, _curpaperindex);
		}

		_updateLastEditPage();
		return true;
	}

	// fail to find the one
	return false;
}


void PmPhotoMakerDoc::_constructDefLayout(PROJ_PROPS::LAYOUT_TYPE lytype, PmPrintPaperPage *paperpage)
{
	if ( !paperpage )
	{
		return ;
	}

	LayoutBoxPos pagepos;
	QList<PmPhotoPage *> photopages;
	paperpage->getPhotoPages(photopages);
	PHOTO_LAYOUT layout = PP_LAYOUT_FULLSIZE_SINGLE;
	switch(lytype)
	{
	case PROJ_PROPS::LY8X5FULL:
		{
			layout = PP_LAYOUT_PB8X5_FULLSIZE_A;
			if ( photopages.size() <= 0 ||   photopages.size()> 2 )
			{
				return ;
			}

			if ( photopages.size() == 1 )
			{
				// must be first or last page
				PmPhotoPage *photopage = photopages.front();
				if ( photopage )
				{
					photopage->getPagePosInPaper(pagepos);
					if ( pagepos.x == 0 )
					{
						// last page
						paperpage->setLayout(photopage,
							PP_LAYOUT_PB8X5_FULLSIZE_B, PmPrintPaperPage::LF_PG_LAYOUT);
					}
					else
					{
						// first page
						paperpage->setLayout(photopage,
							PP_LAYOUT_PB8X5_FULLSIZE_B, PmPrintPaperPage::RT_PG_LAYOUT);
					}
				}
			}
			else
			{
				paperpage->setLayout(photopages.first(),
					layout, PmPrintPaperPage::LF_PG_LAYOUT);
				paperpage->setLayout(photopages.back(),
					layout, PmPrintPaperPage::RT_PG_LAYOUT);
			}
		}
		break;
	case PROJ_PROPS::LY8X5TRADITION:
		{
			layout = PP_LAYOUT_PB8X5_TRADITION_A;
			if ( photopages.size() <= 0 ||   photopages.size()> 2 )
			{
				return ;
			}
			if ( photopages.size() == 1 )
			{
				// must be first or last page
				PmPhotoPage *photopage = photopages.front();
				if ( photopage )
				{
					photopage->getPagePosInPaper(pagepos);
					if ( pagepos.x == 0 )
					{
						// last page
						paperpage->setLayout(photopage,
							PP_LAYOUT_PB8X5_TRADITION_B, PmPrintPaperPage::LF_PG_LAYOUT);
					}
					else
					{
						// first page
						paperpage->setLayout(photopage,
							PP_LAYOUT_PB8X5_TRADITION_B, PmPrintPaperPage::RT_PG_LAYOUT);
					}
				}
			}
			else
			{
				paperpage->setLayout(photopages.first(),
					layout, PmPrintPaperPage::LF_PG_LAYOUT);
				paperpage->setLayout(photopages.back(),
					layout, PmPrintPaperPage::RT_PG_LAYOUT);
			}
		}
		break;
	case PROJ_PROPS::LY8X5VERTICON:
		{
			layout = PP_LAYOUT_PB8X5_VERTICON_A;
			if ( photopages.size() <= 0 ||   photopages.size()> 2 )
			{
				return ;
			}
			if ( photopages.size() == 1 )
			{
				// must be first or last page
				PmPhotoPage *photopage = photopages.front();
				if ( photopage )
				{
					photopage->getPagePosInPaper(pagepos);
					if ( pagepos.x == 0 )
					{
						// last page
						paperpage->setLayout(photopage,
							PP_LAYOUT_PB8X5_VERTICON_B, PmPrintPaperPage::LF_PG_LAYOUT);
					}
					else
					{
						// first page
						paperpage->setLayout(photopage,
							PP_LAYOUT_PB8X5_VERTICON_B, PmPrintPaperPage::RT_PG_LAYOUT);
					}
				}
			}
			else
			{
				paperpage->setLayout(photopages.first(),
					layout, PmPrintPaperPage::LF_PG_LAYOUT);
				paperpage->setLayout(photopages.back(),
					layout, PmPrintPaperPage::RT_PG_LAYOUT);
			}
		}
		break;
	case PROJ_PROPS::LY8X5HORIZON:
		{
			layout = PP_LAYOUT_PB8X5_HORIZON_A;

			if ( photopages.size() <= 0 ||   photopages.size()> 2 )
			{
				return ;
			}
			if ( photopages.size() == 1 )
			{
				// must be first or last page
				PmPhotoPage *photopage = photopages.front();
				if ( photopage )
				{
					photopage->getPagePosInPaper(pagepos);
					if ( pagepos.x == 0 )
					{
						// last page
						paperpage->setLayout(photopage,
							PP_LAYOUT_PB8X5_HORIZON_B, PmPrintPaperPage::LF_PG_LAYOUT);
					}
					else
					{
						// first page
						paperpage->setLayout(photopage,
							PP_LAYOUT_PB8X5_HORIZON_B, PmPrintPaperPage::RT_PG_LAYOUT);
					}
				}
			}
			else
			{
				paperpage->setLayout(photopages.first(),
					layout, PmPrintPaperPage::LF_PG_LAYOUT);
				paperpage->setLayout(photopages.back(),
					layout, PmPrintPaperPage::RT_PG_LAYOUT);
			}
		}
		break;
	case PROJ_PROPS::LYCALA4L1:
		{
			layout = PP_LAYOUT_CALENDAR_A4_L1_L1;
			if ( photopages.size() != 1 )
			{
				return ;
			}

			// must be first or last page
			PmPhotoPage *photopage = photopages.front();
			paperpage->setLayout(photopage,layout);
		}
		break;
	case PROJ_PROPS::LYCALA4L2:
		{
			layout = PP_LAYOUT_CALENDAR_A4_L2_L1;
			if ( photopages.size() != 1 )
			{
				return ;
			}

			// must be first or last page
			PmPhotoPage *photopage = photopages.front();
			paperpage->setLayout(photopage,layout);
		}
		break;
	case PROJ_PROPS::LYCALA4L3:
		{
			layout = PP_LAYOUT_CALENDAR_A4_L3_L1;
			if ( photopages.size() != 1 )
			{
				return ;
			}

			// must be first or last page
			PmPhotoPage *photopage = photopages.front();
			paperpage->setLayout(photopage,layout);
		}
		break;
	case PROJ_PROPS::LYCALA4L4:
		{
			layout = PP_LAYOUT_CALENDAR_A4_L4_L1;
			if ( photopages.size() != 1 )
			{
				return ;
			}

			// must be first or last page
			PmPhotoPage *photopage = photopages.front();
			paperpage->setLayout(photopage,layout);
		}
		break;
	case PROJ_PROPS::LYCALA5L1:
		{
			layout = PP_LAYOUT_CALENDAR_A5_L1_L1;
			if ( photopages.size() != 1 )
			{
				return ;
			}

			// must be first or last page
			PmPhotoPage *photopage = photopages.front();
			paperpage->setLayout(photopage,layout);
		}
		break;

	case PROJ_PROPS::LYCALA5L2:
		{
			layout = PP_LAYOUT_CALENDAR_A5_L2_L1;
			if ( photopages.size() != 1 )
			{
				return ;
			}

			// must be first or last page
			PmPhotoPage *photopage = photopages.front();
			paperpage->setLayout(photopage,layout);
		}
		break;
	case PROJ_PROPS::LYCALA5L3:
		{
			layout = PP_LAYOUT_CALENDAR_A5_L3_L1;
			if ( photopages.size() != 1 )
			{
				return ;
			}

			// must be first or last page
			PmPhotoPage *photopage = photopages.front();
			paperpage->setLayout(photopage,layout);
		}
		break;
	case PROJ_PROPS::LYCAL4X6L1:
		{
			layout = PP_LAYOUT_CALENDAR_4X6_L1_L1;
			if ( photopages.size() != 1 )
			{
				return ;
			}

			// must be first or last page
			PmPhotoPage *photopage = photopages.front();
			paperpage->setLayout(photopage,layout);
		}
		break;

	case PROJ_PROPS::LYCAL4X6L2:
		{
			layout = PP_LAYOUT_CALENDAR_4X6_L2_L1;
			if ( photopages.size() != 1 )
			{
				return ;
			}

			// must be first or last page
			PmPhotoPage *photopage = photopages.front();
			paperpage->setLayout(photopage,layout);
		}
		break;
	case PROJ_PROPS::LYCAL4X6L3:
		{
			layout = PP_LAYOUT_CALENDAR_4X6_L3_L1;
			if ( photopages.size() != 1 )
			{
				return ;
			}

			// must be first or last page
			PmPhotoPage *photopage = photopages.front();
			paperpage->setLayout(photopage,layout);
		}
		break;
	case PROJ_PROPS::LYCAL4X6L4:
		{
			layout = PP_LAYOUT_CALENDAR_4X6_L4_L1;
			if ( photopages.size() != 1 )
			{
				return ;
			}

			// must be first or last page
			PmPhotoPage *photopage = photopages.front();
			paperpage->setLayout(photopage,layout);
		}
		break;
	case PROJ_PROPS::DEFLYTYPE:
	default:
		;
	}
}

void PmPhotoMakerDoc::_newPocketBook4X3(const PROJ_PROPS &prj)
{
	_printpaperpage = NULL;
	_paperpages.clear();
	_printpaperpage = new Pm4x3PrintPaper(prj.hasborder,this, FIRST_PAGE);
	QList<PmPhotoPage *> pages;
	PmPhotoPage *leftpage, *rightpage;
	_printpaperpage->getPhotoPages(pages);
	rightpage = pages.last();
	//_constructDefLayout(prj.lytype, _printpaperpage);
	if ( prj.hasborder )
	{
		rightpage->setLayout(PP_LAYOUT_BORDER_SINGLE, true, false);
	}
	else
	{
		rightpage->setLayout(PP_LAYOUT_FULLSIZE_SINGLE, false, false);
	}
	_paperpages.push_back(_printpaperpage);

	for ( int i=0; i<15; i++ )
	{
		_printpaperpage = new Pm4x3PrintPaper(prj.hasborder,this);
		//_constructDefLayout(prj.lytype, _printpaperpage);
		_printpaperpage->getPhotoPages(pages);
		rightpage = pages.last();
		leftpage = pages.first();
		if ( prj.hasborder )
		{
			rightpage->setLayout(PP_LAYOUT_BORDER_SINGLE, true, true);
			leftpage->setLayout(PP_LAYOUT_BORDER_SINGLE, true, true);

		}
		else
		{
			rightpage->setLayout(PP_LAYOUT_FULLSIZE_SINGLE, false, true);
			leftpage->setLayout(PP_LAYOUT_FULLSIZE_SINGLE, false, true);

		}
		_paperpages.push_back(_printpaperpage);
	}
	_printpaperpage = new Pm4x3PrintPaper(prj.hasborder,this, LAST_PAGE);
	_constructDefLayout(prj.lytype, _printpaperpage);
	_printpaperpage->getPhotoPages(pages);
	leftpage = pages.last();
	if ( prj.hasborder )
	{
		leftpage->setLayout(PP_LAYOUT_BORDER_SINGLE, true, true);
	}
	else
	{
		leftpage->setLayout(PP_LAYOUT_FULLSIZE_SINGLE, false, true);
	}
	_paperpages.push_back(_printpaperpage);
	this->setCurPaperPage(_paperpages.first());
}
void PmPhotoMakerDoc::_newPhotoBook10X15(const PROJ_PROPS &prj)
{
	_printpaperpage = NULL;
	_paperpages.clear();
	_printpaperpage = new Pm10x15PrintPaper(prj.hasborder,this, FIRST_PAGE);
	_constructDefLayout(prj.lytype, _printpaperpage);
	_paperpages.push_back(_printpaperpage);

	for ( int i=0; i<15; i++ )
	{
		_printpaperpage = new Pm10x15PrintPaper(prj.hasborder,this);
		_constructDefLayout(prj.lytype, _printpaperpage);
		_paperpages.push_back(_printpaperpage);
	}
	_printpaperpage = new Pm10x15PrintPaper(prj.hasborder,this, LAST_PAGE);
	_constructDefLayout(prj.lytype, _printpaperpage);
	_paperpages.push_back(_printpaperpage);
	this->setCurPaperPage(_paperpages.first());
}
void PmPhotoMakerDoc::_newSingle4X6(const PROJ_PROPS &prj)
{

}
void PmPhotoMakerDoc::_newPhotoBook8X5(const PROJ_PROPS &prj)
{
	_printpaperpage = NULL;
	_paperpages.clear();
	_printpaperpage = new Pm8x5PrintPaper(prj.hasborder,this, FIRST_PAGE);
	_constructDefLayout(prj.lytype, _printpaperpage);
	_paperpages.push_back(_printpaperpage);

	for ( int i=0; i<15; i++ )
	{
		_printpaperpage = new Pm8x5PrintPaper(prj.hasborder,this);
		_constructDefLayout(prj.lytype, _printpaperpage);
		_paperpages.push_back(_printpaperpage);
	}
	_printpaperpage = new Pm8x5PrintPaper(prj.hasborder,this, LAST_PAGE);
	_constructDefLayout(prj.lytype, _printpaperpage);
	_paperpages.push_back(_printpaperpage);
	this->setCurPaperPage(_paperpages.first());

}
void PmPhotoMakerDoc::_newCalendarA4(const PROJ_PROPS &prj)
{
	_printpaperpage = NULL;
	_paperpages.clear();

	this->_projprops.lastphotopage = 12;
	this->_nexteditpage = NULL;
	for ( int i=0; i<12; i++ )
	{
		_printpaperpage = new PmA4CalPrintPaper(false,_projprops.lytype,this);
		_constructDefLayout(prj.lytype, _printpaperpage);


		PmPageItm *calitm = NULL;
		calitm = this->_getCalItm(_printpaperpage);

		int year=0, month = 0;
		year = prj.year;
		month = i+1;
		calitm->setMonth(year, month);

		_paperpages.push_back(_printpaperpage);
		QList<PmPhotoPage *> pages;
		_printpaperpage->getPhotoPages(pages);
		_lasteditpage = pages.last();
	}
	_printpaperpage = new PmA4CalPrintPaper(false,_projprops.lytype,this, LAST_PAGE);
	_paperpages.push_back(_printpaperpage);
	QList<PmPhotoPage *> pages;
	_printpaperpage->getPhotoPages(pages);
	_lasteditpage = pages.last();

	this->setCurPaperPage(_paperpages.first());
}
void PmPhotoMakerDoc::_newCalendarA5(const PROJ_PROPS &prj)
{
	_printpaperpage = NULL;
	_paperpages.clear();


	this->_projprops.lastphotopage = 12;
	this->_nexteditpage = NULL;
	for ( int i=0; i<12; i++ )
	{
		_printpaperpage = new PmA5CalPrintPaper(false,_projprops.lytype,this);
		_constructDefLayout(prj.lytype, _printpaperpage);

		PmPageItm *calitm = NULL;
		calitm = this->_getCalItm(_printpaperpage);

		int year=0, month = 0;
		year = prj.year;
		month = i+1;
		calitm->setMonth(year, month);
		_paperpages.push_back(_printpaperpage);

		QList<PmPhotoPage *> pages;
		_printpaperpage->getPhotoPages(pages);
		_lasteditpage = pages.last();
	}
	_printpaperpage = new PmA5CalPrintPaper(false,_projprops.lytype,this, LAST_PAGE);
	_paperpages.push_back(_printpaperpage);
	QList<PmPhotoPage *> pages;
	_printpaperpage->getPhotoPages(pages);
	_lasteditpage = pages.last();

	this->setCurPaperPage(_paperpages.first());
}
void PmPhotoMakerDoc::_newCalendar4X6(const PROJ_PROPS &prj)
{
	_printpaperpage = NULL;
	_paperpages.clear();

	this->_nexteditpage = NULL;
	this->_projprops.lastphotopage = 12;
	for ( int i=0; i<12; i++ )
	{
		_printpaperpage = new Pm4x6CalPrintPaper(false,_projprops.lytype,this);
		_constructDefLayout(prj.lytype, _printpaperpage);

		PmPageItm *calitm = NULL;
		calitm = this->_getCalItm(_printpaperpage);

		int year=0, month = 0;
		year = prj.year;
		month = i+1;
		calitm->setMonth(year, month);
		_paperpages.push_back(_printpaperpage);
		QList<PmPhotoPage *> pages;
		_printpaperpage->getPhotoPages(pages);
		_lasteditpage = pages.last();
	}
	_printpaperpage = new Pm4x6CalPrintPaper(false,_projprops.lytype,this, LAST_PAGE);
	_paperpages.push_back(_printpaperpage);
	QList<PmPhotoPage *> pages;
	_printpaperpage->getPhotoPages(pages);
	_lasteditpage = pages.last();

	this->setCurPaperPage(_paperpages.first());
}


bool PmPhotoMakerDoc::newDoc(const PROJ_PROPS &prj)
{
	// delete all files in project folder
	QDir prjfolder("./prj");
	//file.delte
	QFileInfoList list = prjfolder.entryInfoList();
	for (int subindex=0;subindex<list.size(); subindex++ )
	{
		QFileInfo fileinfo = list[subindex];
		if ( fileinfo.isDir() )
		{
			continue;
		}
		QString path = fileinfo.fileName();
		bool ret = prjfolder.remove(path);
		if ( !ret )
		{
			QFile file;
			file.setPermissions("./prj/" + path, QFile::WriteOwner|QFile::WriteUser);
			ret = prjfolder.remove(path);
		}
	}

	//
	_projprops = prj;
	switch( _projprops.type )
	{
		//
	case PROJ_PROPS::POCKETBOOK4X3:
		{
			_newPocketBook4X3(prj);
		}
		break;
	case PROJ_PROPS::PHOTOBOOK10X15:
		{
			_newPhotoBook10X15(prj);
		}
		break;
	case PROJ_PROPS::SINGLE4X6:
		break;
	case PROJ_PROPS::PHOTOBOOK8X5:
		{
			//
			_newPhotoBook8X5(prj);
		}
		break;
	case PROJ_PROPS::CALENDARA4:
		{
			//
			_newCalendarA4(prj);
		}
		break;
	case PROJ_PROPS::CALENDARA5:
		{
			//
			_newCalendarA5(prj);
		}
		break;
	case PROJ_PROPS::CALENDAR4X6:
		{
			//
			_newCalendar4X6(prj);
		}
		break;
	case PROJ_PROPS::DEFDEMO:
	default:
		;
	}


	return true;
}

PmPrintPaperPage *PmPhotoMakerDoc::createNewPaper()
{
	PmPrintPaperPage *paper = NULL;
	switch( _projprops.type )
	{
		//
	case PROJ_PROPS::POCKETBOOK4X3:
		{
			paper = new Pm4x3PrintPaper(_projprops.hasborder,this);
		}
		break;
	case PROJ_PROPS::PHOTOBOOK10X15:
		{
			paper = new Pm10x15PrintPaper(_projprops.hasborder,this);
		}
		break;
	case PROJ_PROPS::SINGLE4X6:
		break;
	case PROJ_PROPS::PHOTOBOOK8X5:
		{
			//
			paper = new Pm8x5PrintPaper(_projprops.hasborder,this);
		}
		break;
	case PROJ_PROPS::CALENDARA4:
		{
			//
			paper = new PmA4CalPrintPaper(false,_projprops.lytype, this);
		}
		break;
	case PROJ_PROPS::CALENDARA5:
		{
			//
			paper = new PmA5CalPrintPaper(false,_projprops.lytype, this);
		}
		break;
	case PROJ_PROPS::CALENDAR4X6:
		{
			//
			paper = new Pm4x6CalPrintPaper(false,_projprops.lytype, this);
		}
		break;
	case PROJ_PROPS::DEFDEMO:
	default:
		;
	}

	return paper;
}

/*

   <paperpage>
       <photopage>
	         <photoitm>
			      <...>
			 </photoitm>
	   </photopage>

	   <textitm/>
   </paperpage>


*/

bool PmPhotoMakerDoc::_saveInt(QDomDocument &doc,QDomElement &parent, const QString &name, const int value)
{
    QString tmpbuf = QString("%1").arg(value);
    return this->_saveStr(doc, parent, name, tmpbuf);
}

bool PmPhotoMakerDoc::_saveFloat(QDomDocument &doc,QDomElement &parent, const QString &name, const qreal value)
{
    QString tmpbuf = QString("%1").arg(value);
    return this->_saveStr(doc, parent, name, tmpbuf);
}

bool PmPhotoMakerDoc::_saveTextItms(QDomDocument &doc,QDomElement &printpaerpageelem, const QList<PmTextItm*> &txtitmlst)
{
	QDomElement textitmlstelem = doc.createElement("TextItemLst");
	printpaerpageelem.appendChild(textitmlstelem);
	QList<PmTextItm*>::const_iterator it;
	for ( it=txtitmlst.begin(); it!=txtitmlst.end(); it++ )
	{
		this->_saveTextItm(doc, textitmlstelem, **it);
	}

	return true;
}

bool PmPhotoMakerDoc::_loadTextItms(QDomElement &textitmlsteelem,  QList<PmTextItm*> &txtitmlst)
{
	QDomElement textitmelem;

	txtitmlst.clear();

	textitmelem = textitmlsteelem.firstChildElement("TextItem");
	while(!textitmelem.isNull() )
	{
		PmTextItm *ptxtitm = NULL;
		this->_loadTextItm(textitmelem, ptxtitm);
		if ( ptxtitm )
		{
			txtitmlst.push_back(ptxtitm);
		}
		textitmelem = textitmelem.nextSiblingElement("TextItem");
	}

	return true;
}

bool PmPhotoMakerDoc::_saveTextItm(QDomDocument &doc,QDomElement &txtitmlstelem, PmTextItm &textitm)
{
	QDomElement textitmelem = doc.createElement("TextItem");
	txtitmlstelem.appendChild(textitmelem);

	// pos in printpaper
	LayoutBoxPos posinprintpaper;
	textitm.getRectInPrintPage(posinprintpaper);
	this->_savePos(doc, textitmelem, "posinprintpaper", posinprintpaper);

	QString content;
	textitm.getContent(content);
	QString orgcnt = content;
	QByteArray utf8cnt = content.toUtf8();
	int utf8cntlen = utf8cnt.length();

	int outlen = utf8cnt.length()*4; 
	char *output = new char[outlen];
	if ( output )
	{
		memset(output, 0, outlen);
		ToB64Enc(utf8cnt.data(), output, utf8cnt.length());
		//output[datalen] = 0;
		int outlen = strlen(output);
		content = output;

		/*
		{
			unsigned int delen = 0;
			char *dcode = (char *)Base64Decode(output, &delen);
			//dcode[delen] = 0;
			QString check = QString::fromUtf8(dcode);
			delete dcode;
			if ( check == orgcnt )
			{
				int err = 1;
			}
		}
		*/
		delete output;
	}
	else
	{
		content = "";
	}

	this->_saveStr(doc, textitmelem, "conent", content);

	int aligntype = textitm.getAlign();
	this->_saveInt(doc, textitmelem, "aligntype", aligntype);

	qreal scale = textitm.getScale();
	this->_saveFloat(doc, textitmelem, "scale", scale);

	qreal rotate = textitm.getRotate();
	this->_saveFloat(doc, textitmelem, "rotate", rotate);

	bool enableShadow = textitm.isShadowEnable();
	this->_saveStr(doc, textitmelem, "enableshadow", enableShadow?"true":"false");


	return true;
}

bool PmPhotoMakerDoc::_savePhotoItm(QDomDocument &doc, QDomElement &photopageelem, PmPageItm &photoitm)
{
	QDomElement photoitmelem = doc.createElement("PageItm");
	photopageelem.appendChild(photoitmelem);


	// pos
	LayoutBoxPos itmposinpage;
	photoitm.getRectInPage(itmposinpage);
	this->_savePos(doc, photoitmelem, "posinpage", itmposinpage);

	// type
	PmPageItm::PHOTO_ITM_TYPE type = photoitm.getPhotoItmType();
	this->_saveInt(doc, photoitmelem, "pageitmtype", (int)type);

	// image path
	if ( PmPageItm::CALENDAR_ITM == photoitm.getPhotoItmType() )
	{
		// calendar 
		int year, mon;
		photoitm.getMonth(year, mon);
		this->_saveInt(doc, photoitmelem, "calyear", year);
		this->_saveInt(doc, photoitmelem, "calmonth", mon);


		// save calendar config
		CALENDAR_CFG calcfg;
		photoitm.getCalProps(calcfg.calcfg);
		photoitm.getWdsProps(calcfg.wdcfg);
		photoitm.getMonthYearProps(calcfg.monthyearcfg);

		this->_saveCalCfg(doc, photoitmelem, "calcfg", calcfg);
	}
	else
	{
		QString imgpath;
		photoitm.getContent(imgpath);
		this->_saveStr(doc, photoitmelem, "imagepath", imgpath);

		int angel = 0;
		photoitm.getRotate(angel);
		this->_saveInt(doc, photoitmelem, "rotate", angel);

		qreal ratio = 0;
		photoitm.getZoom(ratio);
		this->_saveFloat(doc, photoitmelem, "scale", ratio);

		QPointF lefttop;
		photoitm.getImgLeftTop(lefttop);
		this->_saveFloat(doc, photoitmelem, "imgleftoff", lefttop.rx());
		this->_saveFloat(doc, photoitmelem, "imgtopoff", lefttop.ry());

		QColor color;
		photoitm.getBgColor(color);
		QString colorval = QString("%1").arg(color.rgba());
		this->_saveStr(doc, photoitmelem, "backgroundcolor", colorval);
	}

	return true;
}


bool PmPhotoMakerDoc::_savePhotoPage(QDomDocument &doc, QDomElement &printpaerpageelem, PmPhotoPage &photopage)
{
	QDomElement photopageelem = doc.createElement("PhotoPage");
	printpaerpageelem.appendChild(photopageelem);


	//
	int type = photopage.getType();
	_saveInt(doc, photopageelem, "type", type);


	PHOTO_LAYOUT layout = photopage.getLayout();
	QString layoutname = PPLayoutMgr::getInst().getLayoutName(layout);
	_saveStr(doc, photopageelem, "layout", layoutname);


	LayoutBoxPos pagepos;
	photopage.getPagePosInPaper(pagepos);
	this->_savePos(doc, photopageelem, "pageposinpaper", pagepos);

	qreal scaleratio = photopage.getScaleRatio();
	this->_saveFloat(doc, photopageelem, "scaleratio", scaleratio);

	// border
	this->_saveInt(doc, photopageelem, "border", photopage.hasBorder()?1:0);
	// left
	this->_saveInt(doc, photopageelem, "isleft", photopage.isLeft()?1:0);


	QList<PmPageItm *> picitmlst;
	photopage.getPicItms(picitmlst);

	QList<PmPageItm *>::iterator it;
	for ( it=picitmlst.begin(); it!=picitmlst.end(); it++ )
	{
		this->_savePhotoItm(doc, photopageelem, **it);
	}
	return true;
}


bool PmPhotoMakerDoc::_saveMargin(QDomDocument &doc,QDomElement &parent, const QString &name, const LayoutBoxMargin margin)
{
	QDomElement marginelem = doc.createElement(name);
	parent.appendChild(marginelem);
	this->_saveFloat(doc, marginelem, "left", margin.left);
	this->_saveFloat(doc, marginelem, "top", margin.top);
	this->_saveFloat(doc, marginelem, "right", margin.right);
	this->_saveFloat(doc, marginelem, "bottom", margin.bottom);

	return true;
}

bool PmPhotoMakerDoc::_savePos(QDomDocument &doc,QDomElement &parent, const QString &name, const LayoutBoxPos pos)
{
	QDomElement poselem = doc.createElement(name);
	parent.appendChild(poselem);

	this->_saveFloat(doc, poselem, "x", pos.x);
	this->_saveFloat(doc, poselem, "y", pos.y);
	this->_saveFloat(doc, poselem, "width", pos.width);
	this->_saveFloat(doc, poselem, "height", pos.height);
	this->_saveMargin(doc, poselem, "margins", pos.margin);

	return true;
}


bool PmPhotoMakerDoc::_saveSize(QDomDocument &doc,QDomElement &parent, const QString &name, const QSize size)
{
// size
	QDomElement sizeelem = doc.createElement(name);
	parent.appendChild(sizeelem);
	this->_saveInt(doc, sizeelem, "width", size.width());
	this->_saveInt(doc, sizeelem, "height", size.height());

	return true;
}

bool PmPhotoMakerDoc::_addContent(QDomDocument &doc,QDomElement &elem, const QString &content)
{
	QDomText txtnode = doc.createTextNode(content);
	elem.appendChild(txtnode);
	return true;
}

bool PmPhotoMakerDoc::_getContent(QDomElement &elem, QString &content)
{
	if ( elem.isNull() )
	{
		return false;
	}
	/*
	if ( QDomNode::TextNode !=  elem.nodeType() )
	{
		return false;
	}
	*/
	content = elem.text();
	return true;
}

bool PmPhotoMakerDoc::_saveStr(QDomDocument &doc,QDomElement &parent, const QString &name, const QString & value)
{
	QDomElement elem = doc.createElement(name);
	parent.appendChild(elem);
	this->_addContent(doc, elem, value);

	return true;
}

bool PmPhotoMakerDoc::_loadPos(QDomElement &poselem, LayoutBoxPos &pos)
{
	if ( poselem.isNull() )
	{
		return false;
	}
	qreal val = 0;
	QDomElement elem = poselem.firstChildElement("x");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		pos.x = val;
	}
	elem = poselem.firstChildElement("y");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		pos.y = val;
	}
	elem = poselem.firstChildElement("width");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		pos.width = val;
	}
	elem = poselem.firstChildElement("height");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		pos.height = val;
	}
	elem = poselem.firstChildElement("margins");
	if ( !elem.isNull()  )
	{
		this->_loadMargin(elem, pos.margin);
	}

	return true;
}

bool PmPhotoMakerDoc::_loadMargin(QDomElement &marginelem, LayoutBoxMargin &margin)
{
	if ( marginelem.isNull() )
	{
		return false;
	}

	qreal val;
	QDomElement elem = marginelem.firstChildElement("left");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		margin.left = val;
	}

	elem = marginelem.firstChildElement("top");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		margin.top = val;
	}
	elem = marginelem.firstChildElement("right");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		margin.right = val;
	}
	elem = marginelem.firstChildElement("bottom");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		margin.bottom = val;
	}
	return true;
}

bool PmPhotoMakerDoc::_loadInt(QDomElement &elem, int &value)
{
	QString strval;
	if ( !_loadStr(elem, strval) )
	{
		return false;
	}
	sscanf(strval.toAscii().data(), "%d", &value);
	return true;
}

bool PmPhotoMakerDoc::_loadFloat(QDomElement &elem, qreal &value)
{
	QString strval;
	if ( !_loadStr(elem, strval) )
	{
		return false;
	}
	float tmp;
	QByteArray ba = strval.toAscii();
	char *data = ba.data();
	sscanf(data, "%f", &tmp);
	value = tmp;
	return true;
}

bool PmPhotoMakerDoc::_loadStr(QDomElement &elem, QString &value)
{
	return _getContent(elem, value);
}
	
bool PmPhotoMakerDoc::_saveColor(QDomDocument &doc,QDomElement &parent, const QString &name, const QColor &color)
{
	QDomElement elem = doc.createElement(name);
	parent.appendChild(elem);

	int alpha = color.alpha();
	int red = color.red();
	int green = color.green();
	int blue = color.blue();

	_saveInt(doc, elem, "alpha", alpha);
	_saveInt(doc, elem, "red", red);
	_saveInt(doc, elem, "green", green);
	_saveInt(doc, elem, "blue", blue);

	//
	return true;
}


bool PmPhotoMakerDoc::_loadColor(QDomElement &colorelem, QColor &color)
{
	//
	QDomElement elem;

	int alpha = -1;
	int red = 0;
	int green = 0;
	int blue = 0;


	elem = colorelem.firstChildElement("alpha");
	_loadInt(elem, alpha);
	elem = colorelem.firstChildElement("red");
	_loadInt(elem, red);
	elem = colorelem.firstChildElement("green");
	_loadInt(elem, green);
	elem = colorelem.firstChildElement("blue");
	_loadInt(elem, blue);

	color = QColor(red, green, blue, alpha);

	return true;
}


bool PmPhotoMakerDoc::_saveCalCfg(QDomDocument &doc,QDomElement &parent, const QString &name, const CALENDAR_CFG &calcfg)
{
	//
	QDomElement elem = doc.createElement(name);
	parent.appendChild(elem);
	//this->_addContent(doc, elem, value);
	this->_saveCalProps(doc, elem, "calprops", calcfg.calcfg);
	this->_saveWdProps(doc, elem, "wdprops", calcfg.wdcfg);
	this->_saveYmProps(doc, elem, "ymprops", calcfg.monthyearcfg);

	return true;
}

bool PmPhotoMakerDoc::_loadCalCfg(QDomElement &calcfgitm, CALENDAR_CFG &calcfg)
{
	QDomElement calpropselem = calcfgitm.firstChildElement("calprops");
	this->_loadCalProps(calpropselem, calcfg.calcfg);

	QDomElement wdpropselem = calcfgitm.firstChildElement("wdprops");
	this->_loadWdProps(wdpropselem, calcfg.wdcfg);

	QDomElement ympropselem = calcfgitm.firstChildElement("ymprops");
	this->_loadYmProps(ympropselem, calcfg.monthyearcfg);

	return true;
}

bool PmPhotoMakerDoc::_saveCalProps(QDomDocument &doc,QDomElement &calcfgelem, const QString &name, const CAL_PROPS &calcfg)
{
	//
	QDomElement calpropselem = doc.createElement(name);
	calcfgelem.appendChild(calpropselem);

	// 
	_saveFontProps(doc, calpropselem, "calfont", calcfg.fontcfg);

	// color
	_saveColor(doc, calpropselem, "bgcolor", calcfg.bgcolor);
	_saveColor(doc, calpropselem, "rowcolor", calcfg.rowcolor);
	_saveColor(doc, calpropselem, "cellcolor", calcfg.cellcolor);
	for ( int i=0; i<calcfg.wdcolors.size(); i++ )
	{
		QString wd = QString("wd_%1_color").arg(i);
		_saveColor(doc, calpropselem, wd, calcfg.wdcolors[i]);
	}

	_saveSpaceProps(doc, calpropselem, "linespace", calcfg.linespace);
	_saveSpaceProps(doc, calpropselem, "cellspace", calcfg.cellspace);

	return true;
}

bool PmPhotoMakerDoc::_loadCalProps(QDomElement &calcfgelem, CAL_PROPS &calprops)
{
	//
	QDomElement fontpropselem = calcfgelem.firstChildElement("calfont");

	_loadFontProps(fontpropselem, calprops.fontcfg);

	QDomElement colorelem = calcfgelem.firstChildElement("bgcolor");
	_loadColor(colorelem, calprops.bgcolor);

	 colorelem = calcfgelem.firstChildElement("rowcolor");
	_loadColor(colorelem, calprops.rowcolor);

	 colorelem = calcfgelem.firstChildElement("cellcolor");
	_loadColor(colorelem, calprops.cellcolor);

	for ( int i=0; i<7; i++ )
	{
		QString wd = QString("wd_%1_color").arg(i);
		colorelem = calcfgelem.firstChildElement(wd);
		QColor color;
		_loadColor(colorelem, color);
		calprops.wdcolors.push_back(color);
	}
	 
	QDomElement spaceelem = calcfgelem.firstChildElement("linespace");
	this->_loadSpaceProps(spaceelem, calprops.linespace);
	spaceelem = calcfgelem.firstChildElement("cellspace");
	this->_loadSpaceProps(spaceelem, calprops.cellspace);

	return true;
}

bool PmPhotoMakerDoc::_saveWdProps(QDomDocument &doc,QDomElement &calcfgelem, const QString &name, const WEEKDAY_PROPS &wdprops)
{
	QDomElement wdpropselem = doc.createElement(name);
	calcfgelem.appendChild(wdpropselem);

	_saveInt(doc, wdpropselem, "show", wdprops.showwds?1:0);
	_saveFloat(doc, wdpropselem, "size", wdprops.regionsize);

	_saveFontProps(doc, wdpropselem, "font", wdprops.fontcfg);

	_saveColor(doc, wdpropselem, "rowcolor", wdprops.rowcolor);
	_saveColor(doc, wdpropselem, "cellcolor", wdprops.cellcolor);

	_saveSpaceProps(doc, wdpropselem, "linespace", wdprops.linespace);
	_saveSpaceProps(doc, wdpropselem, "cellspace", wdprops.cellspace);

	return true;
}

bool PmPhotoMakerDoc::_loadWdProps(QDomElement &wdpropselem, WEEKDAY_PROPS &wdprops)
{
	int show = 0;
	QDomElement elem = wdpropselem.firstChildElement("show");
	_loadInt(elem, show);
	wdprops.showwds = show!=0;

	elem = wdpropselem.firstChildElement("size");
	_loadFloat(elem, wdprops.regionsize);

	QDomElement fontpropselem = wdpropselem.firstChildElement("font");
	_loadFontProps(fontpropselem, wdprops.fontcfg);

	QDomElement colorelem = wdpropselem.firstChildElement("rowcolor");
	_loadColor(colorelem, wdprops.rowcolor);

	 colorelem = wdpropselem.firstChildElement("cellcolor");
	_loadColor(colorelem, wdprops.cellcolor);

	QDomElement spaceelem = wdpropselem.firstChildElement("linespace");
	this->_loadSpaceProps(spaceelem, wdprops.linespace);
	spaceelem = wdpropselem.firstChildElement("cellspace");
	this->_loadSpaceProps(spaceelem, wdprops.cellspace);

	return true;
}

bool PmPhotoMakerDoc::_saveYmProps(QDomDocument &doc,QDomElement &calcfgelem, const QString &name, const MONTHYEAR_PROPS &ymprops)
{
	QDomElement ympropselem = doc.createElement(name);
	calcfgelem.appendChild(ympropselem);

	_saveInt(doc, ympropselem, "show", ymprops.showmonthyear?1:0);
	_saveInt(doc, ympropselem, "showatbottom", ymprops.showonbottom?1:0);
	_saveInt(doc, ympropselem, "showymdouble", ymprops.showmonthyeardouble?1:0);
	_saveFloat(doc, ympropselem, "size", ymprops.regionsize);

	_saveFontProps(doc, ympropselem, "font", ymprops.fontcfg);

	_saveColor(doc, ympropselem, "rowcolor", ymprops.rowcolor);

	_saveSpaceProps(doc, ympropselem, "linespace", ymprops.linespace);

	return true;
}

bool PmPhotoMakerDoc::_loadYmProps(QDomElement &ympropselem, MONTHYEAR_PROPS &ymprops)
{
	int val = 0;
	QDomElement elem = ympropselem.firstChildElement("show");
	_loadInt(elem, val);
	ymprops.showmonthyear = val!=0;

	elem = ympropselem.firstChildElement("showatbottom");
	_loadInt(elem, val);
	ymprops.showonbottom = val!=0;

	elem = ympropselem.firstChildElement("showymdouble");
	_loadInt(elem, val);
	ymprops.showmonthyeardouble = val!=0;

	elem = ympropselem.firstChildElement("size");
	_loadFloat(elem, ymprops.regionsize);

	QDomElement fontpropselem = ympropselem.firstChildElement("font");
	_loadFontProps(fontpropselem, ymprops.fontcfg);

	QDomElement colorelem = ympropselem.firstChildElement("rowcolor");
	_loadColor(colorelem, ymprops.rowcolor);

	QDomElement spaceelem = ympropselem.firstChildElement("linespace");
	this->_loadSpaceProps(spaceelem, ymprops.linespace);

	return true;
}

bool PmPhotoMakerDoc::_saveSpaceProps(QDomDocument &doc,QDomElement &parent, const QString &name, const SPACE_PROPS &spaceprops)
{
	QDomElement spacepropelem = doc.createElement(name);
	parent.appendChild(spacepropelem);

	_saveFloat(doc, spacepropelem, "left", spaceprops.left);
	_saveFloat(doc, spacepropelem, "top", spaceprops.left);
	_saveFloat(doc, spacepropelem, "right", spaceprops.left);
	_saveFloat(doc, spacepropelem, "bottom", spaceprops.left);
	_saveFloat(doc, spacepropelem, "leftpad", spaceprops.left);
	_saveFloat(doc, spacepropelem, "toppad", spaceprops.left);
	_saveFloat(doc, spacepropelem, "rightpad", spaceprops.left);
	_saveFloat(doc, spacepropelem, "bottompad", spaceprops.left);

	return true;
}
bool PmPhotoMakerDoc::_loadSpaceProps(QDomElement &spacepropselem, SPACE_PROPS  &spaceprops)
{
	QDomElement elem;

	elem = spacepropselem.firstChildElement("left");
	_loadFloat(elem, spaceprops.left);
	elem = spacepropselem.firstChildElement("top");
	_loadFloat(elem, spaceprops.top);
	elem = spacepropselem.firstChildElement("right");
	_loadFloat(elem, spaceprops.right);
	elem = spacepropselem.firstChildElement("bottom");
	_loadFloat(elem, spaceprops.bottom);
	elem = spacepropselem.firstChildElement("leftpad");
	_loadFloat(elem, spaceprops.leftpad);
	elem = spacepropselem.firstChildElement("toppad");
	_loadFloat(elem, spaceprops.toppad);
	elem = spacepropselem.firstChildElement("rightpad");
	_loadFloat(elem, spaceprops.rightpad);
	elem = spacepropselem.firstChildElement("bottompad");
	_loadFloat(elem, spaceprops.bottompad);

	return true;
}

bool PmPhotoMakerDoc::_saveFontProps(QDomDocument &doc,QDomElement &parent, const QString &name, const FONT_PROPS &fontprops)
{
	QDomElement fontpropelem = doc.createElement(name);
	parent.appendChild(fontpropelem);

	this->_saveStr(doc, fontpropelem, "family", fontprops.name);
	this->_saveColor(doc, fontpropelem, "color", fontprops.color);
	_saveInt(doc, fontpropelem, "bold", fontprops.bold?1:0);
	_saveInt(doc, fontpropelem, "iatic", fontprops.iatic?1:0);
	_saveInt(doc, fontpropelem, "underline", fontprops.underLine);
	_saveInt(doc, fontpropelem, "align", fontprops.align);
	_saveFloat(doc, fontpropelem, "heightInCell", fontprops.heightInCell);

	return true;
}
bool PmPhotoMakerDoc::_loadFontProps(QDomElement &fontpropselem, FONT_PROPS  &fontprops)
{
	QDomElement elem;

	int val;
	elem = fontpropselem.firstChildElement("family");
	_loadStr(elem, fontprops.name);
	
	elem = fontpropselem.firstChildElement("color");
	_loadColor(elem, fontprops.color);

	elem = fontpropselem.firstChildElement("bold");
	_loadInt(elem, val);
	fontprops.bold = val != 0;

	elem = fontpropselem.firstChildElement("iatic");
	_loadInt(elem, val);
	fontprops.iatic= val != 0;

	elem = fontpropselem.firstChildElement("underline");
	_loadInt(elem, val);
	fontprops.underLine = val != 0;

	elem = fontpropselem.firstChildElement("align");
	_loadInt(elem, fontprops.align);

	elem = fontpropselem.firstChildElement("heightInCell");
	_loadFloat(elem, fontprops.heightInCell);

	return true;
}


bool PmPhotoMakerDoc::_savePaperPage(QDomDocument &doc, QDomElement &container, PmPrintPaperPage &printpaperpage)
{
	QDomElement paperpageelem = doc.createElement("PrintPaperPage");
	container.appendChild(paperpageelem);

	// size
	QSize size;
	printpaperpage.getSize(size);
	this->_saveSize(doc, paperpageelem, "papersize", size);

	// margin in edit view, 
	LayoutBoxMargin marginInEditView;
	printpaperpage.getMarginInEditView(marginInEditView);
	this->_saveMargin(doc, paperpageelem, "marginineditview", marginInEditView);

	// save background image of edit view "path", no need to save
	QString imgpath;
	printpaperpage.getBackGroundImgInEditView(imgpath);
	//_saveStr(doc, paperpageelem, "paperbgimginedit", imgpath);

	// save border property
	//_saveStr(doc, paperpageelem, "paperbgimginedit", printpaperpage.getborder()?"true":"false");



	// photo pages
	QList<PmPhotoPage *> photopages;
	printpaperpage.getPhotoPages(photopages);
	QList<PmPhotoPage *>::iterator it;
	for(it=photopages.begin(); it!=photopages.end(); it++ )
	{
		//
		this->_savePhotoPage(doc, paperpageelem, **it);
	}


	// text item
	PmTextItm *pTextItm = NULL;
	QList<PmTextItm *> txtitmlst;
	printpaperpage.getTextbox(txtitmlst);
	if ( txtitmlst.size() )
	{
		_saveTextItms(doc, paperpageelem, txtitmlst);
	}

	return true;
}

bool PmPhotoMakerDoc::_loadPaperPage(QDomElement &paperpageelem, PmPrintPaperPage *&printpaperpage)
{
	//
	QString name = paperpageelem.nodeName();
	if ( name != "PrintPaperPage" )
	{
		printpaperpage = NULL;
		return false;
	}

	QDomElement sizeelem = paperpageelem.firstChildElement("papersize");

	// get the page type
	switch( _projprops.type )
	{
	case PROJ_PROPS::POCKETBOOK4X3:
		{
			printpaperpage = new Pm4x3PrintPaper(true, NULL);
		}
		break;
	case PROJ_PROPS::PHOTOBOOK10X15:
		{
			printpaperpage = new Pm10x15PrintPaper(true, NULL);
		}
		break;
	case PROJ_PROPS::PHOTOBOOK8X5:
		{
			printpaperpage = new Pm8x5PrintPaper(true, NULL);
		}
		break;
	case PROJ_PROPS::CALENDARA4:
		{
			printpaperpage = new PmA4CalPrintPaper(true,_projprops.lytype, NULL);
		}
		break;
	case PROJ_PROPS::CALENDARA5:
		{
			printpaperpage = new PmA5CalPrintPaper(true,_projprops.lytype, NULL);
		}
		break;
	case PROJ_PROPS::CALENDAR4X6:
		{
			printpaperpage = new Pm4x6CalPrintPaper(true,_projprops.lytype, NULL);
		}
		break;
	case PROJ_PROPS::SINGLE4X6:
	case PROJ_PROPS::DEFDEMO:
	default:
		{
			printpaperpage = new Pm8x5PrintPaper(true, NULL);
		}
		break;
	}

	// photo pages

	QList<PmPhotoPage *> photopages;
	PmPhotoPage * pphotopage;

	QDomElement photopageelem = paperpageelem.firstChildElement("PhotoPage");
	while(!photopageelem.isNull())
	{
		if ( _loadPhotoPage(photopageelem, pphotopage) &&  pphotopage)
		{
			pphotopage->setPaperPage(printpaperpage);
			photopages.push_back(pphotopage);
		}

		//
		photopageelem = photopageelem.nextSiblingElement("PhotoPage");
	}
	printpaperpage->setPhotoPages(photopages);

	// text item
	QDomElement textitmelem = paperpageelem.firstChildElement("TextItemLst");

	PmTextItm *pTxtItm = NULL;
	QList<PmTextItm *> txtitmlst; 
	this->_loadTextItms(textitmelem, txtitmlst);

	QList<PmTextItm *>::iterator it;
	for ( it=txtitmlst.begin(); it!=txtitmlst.end(); it++ )
	{
		printpaperpage->addTextbox(*it); 
	}

	return true;
}


bool PmPhotoMakerDoc::_loadTextItm(QDomElement &textitmeelem, PmTextItm *&textitm)
{
		//
	QString name = textitmeelem.nodeName();
	if ( name != "TextItem" || textitmeelem.isNull() )
	{
		textitm = NULL;
		return false;
	}

	textitm = new PmTextItm(NULL);
	if ( !textitm )
	{
		return false;
	}

	QDomElement poselem = textitmeelem.firstChildElement("posinprintpaper");
	if ( poselem.isNull() )
	{
		return false;
	}
	LayoutBoxPos pos;
	this->_loadPos(poselem, pos);
	textitm->setRectInPrintPage(pos);

	QDomElement cntelem = textitmeelem.firstChildElement("conent");
	QString content;
	this->_loadStr(cntelem, content);


	QByteArray base64str = content.toAscii();
	int base64len = base64str.length(); 
	char *base64buf = new char[base64len+1];
	memcpy(base64buf, base64str.data(), base64len);
	base64buf[base64len] = 0;

	unsigned int srccntlen = 0;
	unsigned char *srccnt = Base64Decode(base64buf, &srccntlen);
	//content = (char *)srccnt;
	char *cnt = NULL;
	if ( srccnt && srccntlen > 0 )
	{
		cnt = new char[srccntlen+1];
		if ( cnt )
		{
			memcpy(cnt, srccnt, srccntlen);
			cnt[srccntlen] = 0;
			content = content.fromUtf8((char *)cnt);
			delete cnt;
		}
		delete srccnt;
	}
	textitm->setContent(content);

	QDomElement alignelem = textitmeelem.firstChildElement("aligntype");
	int aligntype = 0;
	this->_loadInt(alignelem, aligntype);
	textitm->setAlign(aligntype);

	QDomElement scaleelem = textitmeelem.firstChildElement("scale");
	qreal scale = 0;
	this->_loadFloat(scaleelem, scale);
	textitm->setScale(scale);

	QDomElement rotateelem = textitmeelem.firstChildElement("rotate");
	qreal rotate = 0;
	this->_loadFloat(rotateelem, rotate);
	textitm->setRotate(rotate);

	QDomElement enableShadowElem = textitmeelem.firstChildElement("enableshadow");
	QString enableShadow;
	this->_loadStr(enableShadowElem, enableShadow);
	textitm->enableShadow(enableShadow=="true");

	return true;
}

bool PmPhotoMakerDoc::_loadPhotoItm(QDomElement &photoitmelem, PmPageItm *&photoitm)
{
	if ( photoitmelem.isNull() || photoitmelem.nodeName() != "PageItm" )
	{
		return false;
	}

	photoitm = new PmPageItm(NULL);
	if ( !photoitm )
	{
		return false;
	}

	// pos
	QDomElement poselem = photoitmelem.firstChildElement("posinpage");
	LayoutBoxPos itmposinpage;
	if ( this->_loadPos(poselem, itmposinpage) )
	{
		photoitm->setRectInPage(itmposinpage);
	}


	// type
	QDomElement typeelem = photoitmelem.firstChildElement("pageitmtype");
	int type = 0;
	if ( this->_loadInt(typeelem, type) )
	{
		photoitm->setPhotoItmType((PmPageItm::PHOTO_ITM_TYPE )type);
	}


	if ( PmPageItm::CALENDAR_ITM ==  photoitm->getPhotoItmType() )
	{
		// calendar 
		int year, mon;
		QDomElement elem;
		elem = photoitmelem.firstChildElement("calyear");
		_loadInt(elem, year);
		elem = photoitmelem.firstChildElement("calmonth");
		_loadInt(elem, mon);
		photoitm->setMonth(year, mon);

		// save calendar config
		elem =  photoitmelem.firstChildElement("calcfg");
		CALENDAR_CFG calcfg;
		this->_loadCalCfg(elem, calcfg);

		photoitm->setCalProps(calcfg.calcfg);
		photoitm->setWdsProps(calcfg.wdcfg);
		photoitm->setMonthYearProps(calcfg.monthyearcfg);

	}
	else
	{

		// image path
		QDomElement imgpathelem = photoitmelem.firstChildElement("imagepath");
		QString imgpath;
		if ( this->_loadStr(imgpathelem, imgpath) )
		{
			photoitm->setContent(imgpath);
		}


		int angel = 0;
		QDomElement rotateelem = photoitmelem.firstChildElement("rotate");
		this->_loadInt(rotateelem, angel);
		photoitm->setRotate(angel);


		qreal ratio = 0;
		QDomElement scaleelem = photoitmelem.firstChildElement("scale");
		this->_loadFloat(scaleelem, ratio);
		photoitm->setZoom(ratio);

		QPointF lefttop;
		QDomElement imgleftelem = photoitmelem.firstChildElement("imgleftoff");
		QDomElement imgtopelem = photoitmelem.firstChildElement("imgtopoff");
		qreal left = 0, top = 0;
		this->_loadFloat(imgleftelem, left);
		this->_loadFloat(imgtopelem, top);
		lefttop.setX(left);
		lefttop.setY(top);
		photoitm->setImgLeftTop(lefttop);

		QString colorval;
		QDomElement colorelem = photoitmelem.firstChildElement("backgroundcolor");
		this->_loadStr(colorelem, colorval);
		QColor color;
		ulong val = colorval.toULong();
		color.setRgba(QRgb(val));
		photoitm->setBgColor(color);
	}
	return true;
}

bool PmPhotoMakerDoc::_loadPhotoPage(QDomElement &photopageelem, PmPhotoPage *&photopage)
{
	if ( photopageelem.isNull() || photopageelem.nodeName() != "PhotoPage"  )
	{
		return false;
	}
	photopage = new PmPhotoPage(NULL);
	if ( !photopage )
	{
		return false;
	}

	QDomElement typeelem = photopageelem.firstChildElement("type");
	int type = 0;
	this->_loadInt(typeelem, type);
	photopage->setType(type);


	//
	// load page border property
	//

	//
	QDomElement layoutelem = photopageelem.firstChildElement("layout");
	QString layoutname ;
	this->_loadStr(layoutelem, layoutname);
	PROJ_PROPS prjprops;
	this->getProjProps(prjprops);
	PHOTO_LAYOUT layout = PPLayoutMgr::getInst().getLayoutFromName(prjprops, layoutname);
	photopage->setLayout(layout,photopage->hasBorder(), false);



	QDomElement pageposelem = photopageelem.firstChildElement("pageposinpaper");
	LayoutBoxPos pagepos;
	this->_loadPos(pageposelem, pagepos);
	photopage->setPagePosInPaper(pagepos);

	QDomElement scaleratioelem = photopageelem.firstChildElement("scaleratio");
	qreal scaleratio = 0;
	this->_loadFloat(scaleratioelem, scaleratio);
	photopage->setScaleRatio(scaleratio);

	// border
	QDomElement borderelem = photopageelem.firstChildElement("border");
	int border = 0;;
	this->_loadInt(borderelem, border);
	photopage->setBorder(border!=0);

	// left
	QDomElement isleftelem = photopageelem.firstChildElement("isleft");
	int isleft = 0;
	this->_loadInt(isleftelem, isleft);
	photopage->setIsLeft(isleft!=0);


	QList<PmPageItm *> picitmlst;
	QDomElement pageelem = photopageelem.firstChildElement("PageItm");
	while( !pageelem.isNull() )
	{
		PmPageItm *photoitm = NULL;
		if ( _loadPhotoItm(pageelem, photoitm) && photoitm )
		{
			photoitm->setPage(photopage);
			picitmlst.push_back(photoitm);
		}
		
		pageelem = pageelem.nextSiblingElement("PageItm");
	}

	photopage->setPicItms(picitmlst);
	//photopage->setLayout(layout,photopage->hasBorder(), true);
	return true;
}



bool PmPhotoMakerDoc::_savePrjPropes(QDomDocument &doc,QDomElement &projpropselem, PROJ_PROPS &prjpropes)
{
	this->_saveInt(doc, projpropselem, "ProjectType", prjpropes.type);
	this->_saveInt(doc, projpropselem, "hasborder", prjpropes.hasborder?1:0);
	this->_saveInt(doc, projpropselem, "layoutType", prjpropes.lytype);
	this->_saveInt(doc, projpropselem, "year", prjpropes.year);
	this->_saveInt(doc, projpropselem, "shadow", prjpropes.shadow?1:0);
	this->_saveInt(doc, projpropselem, "textshadow", prjpropes.txtshadow?1:0);

	return true;
}

bool PmPhotoMakerDoc::_loadPrjPropes(QDomElement &prjpropselem, PROJ_PROPS &prjpropes)
{
	int value;

	prjpropes.type = PROJ_PROPS::DEFDEMO;
	prjpropes.hasborder = true;
	prjpropes.lytype = PROJ_PROPS::LY8X5TRADITION;
	prjpropes.year = 0; 

	if ( prjpropselem.isNull())
	{
		return true;
	}

	QDomElement elem  = prjpropselem.firstChildElement("ProjectType");
	if ( !elem.isNull() )
	{
		this->_loadInt(elem, value);
		prjpropes.type = (PROJ_PROPS::PROJ_TYPE)value;
	}

	elem  = prjpropselem.firstChildElement("hasborder");
	if ( !elem.isNull() )
	{
		this->_loadInt(elem, value);
		prjpropes.hasborder = value != 0;
	}

	elem  = prjpropselem.firstChildElement("layoutType");
	if ( !elem.isNull() )
	{
		this->_loadInt(elem, value);
		prjpropes.lytype = (PROJ_PROPS::LAYOUT_TYPE)value;
	}


	elem  = prjpropselem.firstChildElement("year");
	if ( !elem.isNull() )
	{
		this->_loadInt(elem, value);
		prjpropes.year = value;
	}
	elem  = prjpropselem.firstChildElement("shadow");
	if ( !elem.isNull() )
	{
		this->_loadInt(elem, value);
		prjpropes.shadow = value==1;
	}
	elem  = prjpropselem.firstChildElement("textshadow");
	if ( !elem.isNull() )
	{
		this->_loadInt(elem, value);
		prjpropes.txtshadow = value==1;
	}

	return true;
}


bool PmPhotoMakerDoc::saveDoc(const QString &path)
{
	//
	// generate a xml file to represent the pages

	 QFile file(path);
     if (!file.open(QFile::ReadWrite | QFile::Text)) 
	 {
		 return false;
	 }

	 QDomDocument domDocument("photomakerdoc");

	 QString errorStr;
     int errorLine;
     int errorColumn;
	 /*
	 if ( !domDocument.setContent(&file, true,  &errorStr, &errorLine,
                                 &errorColumn) )
	 {
		 return false;
	 }
	 */

	 QDomElement root = domDocument.createElement("PmProjStg");
	 domDocument.appendChild(root);

	 // save project properties
	 QDomElement projpropselem = domDocument.createElement("ProjectPropes");
	 root.appendChild(projpropselem);
	 this->_savePrjPropes(domDocument, projpropselem, this->_projprops);

	 QDomElement paperpageselem = domDocument.createElement("PrintPaperPages");
	 root.appendChild(paperpageselem);

	 // enum all papaer pages
	 QList<PmPrintPaperPage *>::iterator it;
	 for ( it=_paperpages.begin(); it!=_paperpages.end(); it++ )
	 {
		 //
		 this->_savePaperPage(domDocument, paperpageselem, **it);
	 }
	 //this->_savePaperPage(domDocument, paperpageselem,  *this->_printpaperpage);

	 QString xml = domDocument.toString();
	 

	 file.write(xml.toUtf8());


	// unpack the project file

	// save pictures in working folder

	// load all pages according the xml file


	// packet the xml file and all the pictures in working folder

	return true;
}

bool PmPhotoMakerDoc::loadDoc(const QString &path)
{
	 QFile file(path);
     if (!file.open(QFile::ReadOnly | QFile::Text)) 
	 {
		 return false;
	 }

	 QDomDocument domDocument;

	 QString errorStr;
     int errorLine;
     int errorColumn;
	 if ( !domDocument.setContent(&file, true,  &errorStr, &errorLine,
                                 &errorColumn) )
	 {
		 return false;
	 }

     QDomElement root = domDocument.documentElement();
     if (root.tagName() != "PmProjStg") 
	 {
         return false;
     } 

	 QDomElement prjpropselem = root.firstChildElement("ProjectPropes");
	 if ( !prjpropselem.isNull() )
	 {
		 this->_loadPrjPropes(prjpropselem, _projprops);
	 }


	 QDomElement paperpageselem = root.firstChildElement("PrintPaperPages");
	 if ( paperpageselem.isNull() )
	 {
		 return false;
	 }

	 
	 _paperpages.clear();
	 QDomElement paperpageelem = paperpageselem.firstChildElement("PrintPaperPage");
	 while( !paperpageelem.isNull() )
	 {
		 PmPrintPaperPage *printpaperpage = NULL;
		 if ( _loadPaperPage(paperpageelem, printpaperpage) && printpaperpage )
		 {
			 _paperpages.push_back(printpaperpage);
		 }
		 paperpageelem = paperpageelem.nextSiblingElement("PrintPaperPage");
	 }
	 if ( _paperpages.size() )
	 {
		 _printpaperpage = _paperpages.first();
	 }


	return true;
}


void PmPhotoMakerDoc::moveNextPaperPage()
{
	if ( 0 == _paperpages.size() )
	{
		return ;
	}
	if ( _curpaperindex == _paperpages.size() - 1)
	{
		// last page
		return ;
	}
	_curpaperindex++;
	_printpaperpage = _paperpages.at(_curpaperindex);


}

void PmPhotoMakerDoc::movePrePaperPage()
{
	if ( 0 == _paperpages.size() )
	{
		return ;
	}
	if ( _curpaperindex ==  0 )
	{
		// first page
		return ;
	}
	_curpaperindex--;
	_printpaperpage = _paperpages.at(_curpaperindex);
}


bool PmPhotoMakerDoc::setCurPaperPage(PmPrintPaperPage *paperpage)
{
	QList<PmPrintPaperPage *>::iterator it;
	int index = 0;
	for ( it=_paperpages.begin(); it!=_paperpages.end(); it++, index++)
	{
		if ( *it == paperpage )
		{
			break;
		}
	}

	if ( it == _paperpages.end() )
	{
		return false;
	}

	if ( _curpaperindex == index )
	{
		return true;
	}

	_curpaperindex = index;
	_printpaperpage = paperpage;

	return true;
}
