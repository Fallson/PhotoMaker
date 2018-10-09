#include "pmundoactionstack.h"

PmUndoActionStack::PmUndoActionStack():_updated(false)
{

}

PmUndoActionStack::~PmUndoActionStack()
{

}


PmUndoActionStack& PmUndoActionStack::getInst()
{
	static PmUndoActionStack inst;
	return inst;
}


bool PmUndoActionStack::pushAction(const PE_UNDOACT_ITEM &undoactitm )
{
	this->_updated = true;
	_actionlst.push_back(undoactitm);
	if ( _actionlst.size() > 10 )
	{
		//
		PE_UNDOACT_ITEM undoactitm = _actionlst.front();
		_actionlst.pop_front();
		switch(undoactitm.action)
		{
		case PE_UNDOACT_ITEM::ACTION_PG_SETIMG:
		case PE_UNDOACT_ITEM::ACTION_PG_SETLAYOUT:
		case PE_UNDOACT_ITEM::ACTION_IMG_ZOOMIMG:
		case PE_UNDOACT_ITEM::ACTION_IMG_MOVEIMG:
		case PE_UNDOACT_ITEM::ACTION_PG_RMIMG:
		case PE_UNDOACT_ITEM::ACTION_PG_SWITCHIMG:
		case PE_UNDOACT_ITEM::ACTION_PG_EDITIMG:
			{
				delete undoactitm.saved.pageedit.psavepaper; // has item has no parent, must be destroied
				if ( undoactitm.saved.pageedit.p2ndsavepaper )
				{
					delete undoactitm.saved.pageedit.p2ndsavepaper;
				}
			}
			break;
		case PE_UNDOACT_ITEM::ACTION_PG_ADD_PAPER:
			{
				// the added page should be delted
				//PmPrintPaperPage *paddedpaper = undoactitm.saved.paddedpaper;

				// this paper should be deleted
				//delete paddedpaper;
			}
			break;
		case PE_UNDOACT_ITEM::ACTION_PG_DEL_PAPER:
			{
				// the delete paper should be restored
				PmPrintPaperPage *pdeletedpaper = undoactitm.saved.rmpaper.pdeletedpaper;
				PmPrintPaperPage * porgbeforepaper = undoactitm.saved.rmpaper.porgbeforepaper;
				delete pdeletedpaper;
			}
			break;
		case PE_UNDOACT_ITEM::ACTION_PG_MV_PAPER:
			{
				// the paper should be moved back to original position

				PmPrintPaperPage *pmvingpaper = undoactitm.saved.mvpaper.pmvingpaper;
				PmPrintPaperPage * porgbeforepaper = undoactitm.saved.mvpaper.porgbeforepaper;

			}
			break;
		}

	}
	return true;
}

bool PmUndoActionStack::popAction(PE_UNDOACT_ITEM &undoactitm)
{
	this->_updated = true;

	if ( _actionlst.empty())
	{
		return false;
	}
	undoactitm = _actionlst.back();
	_actionlst.pop_back();
	return true;
}

void PmUndoActionStack::clearUndoStack()
{
	//
	PE_UNDOACT_ITEM _undoActitm;
	while ( popAction(_undoActitm) )
	{
		switch(_undoActitm.action)
		{
		case PE_UNDOACT_ITEM::ACTION_PG_SETIMG:
		case PE_UNDOACT_ITEM::ACTION_PG_SETLAYOUT:
		case PE_UNDOACT_ITEM::ACTION_IMG_ZOOMIMG:
		case PE_UNDOACT_ITEM::ACTION_IMG_MOVEIMG:
		case PE_UNDOACT_ITEM::ACTION_PG_RMIMG:
		case PE_UNDOACT_ITEM::ACTION_PG_SWITCHIMG:
			{
				// all these are edit a paper
				delete _undoActitm.saved.pageedit.psavepaper; // has item has no parent, must be destroied
				// check if there's 2nd edit paper
				if ( _undoActitm.saved.pageedit.p2ndeditpaper )
				{
					delete _undoActitm.saved.pageedit.p2ndsavepaper;
				}
			}
			break;
		case PE_UNDOACT_ITEM::ACTION_PG_EDITIMG:
			{
				// should delete the edit copy file
				if ( _undoActitm.saved.imgedit.pupdatedphotopath )
				{
					delete _undoActitm.saved.imgedit.pupdatedphotopath;
				}

				// all these are edit a paper
				delete _undoActitm.saved.imgedit.pphotoeditsavepaper; // has item has no parent, must be destroied

			}
			break;
		case PE_UNDOACT_ITEM::ACTION_PG_ADD_PAPER:
			{
				// the added page should be delted
				PmPrintPaperPage *paddedpaper = _undoActitm.saved.addpaper.paddedpaper;

				// this paper should be deleted
				delete paddedpaper;
			}
			break;
		case PE_UNDOACT_ITEM::ACTION_PG_DEL_PAPER:
			{
				// the delete paper should be restored
				PmPrintPaperPage *pdeletedpaper = _undoActitm.saved.rmpaper.pdeletedpaper;
				PmPrintPaperPage * porgbeforepaper = _undoActitm.saved.rmpaper.porgbeforepaper;

				delete pdeletedpaper;
			}
			break;
		case PE_UNDOACT_ITEM::ACTION_PG_MV_PAPER:
			{
				// the paper should be moved back to original position

				PmPrintPaperPage *pmvingpaper = _undoActitm.saved.mvpaper.pmvingpaper;
				PmPrintPaperPage * porgbeforepaper = _undoActitm.saved.mvpaper.porgbeforepaper;
			}
			break;
		}
	}
	this->_updated = false;
}


bool PmUndoActionStack::hasActionStored()
{
	return !_actionlst.empty();
}
