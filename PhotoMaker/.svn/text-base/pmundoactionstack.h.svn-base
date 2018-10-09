#ifndef PMUNDOACTIONSTACK_H
#define PMUNDOACTIONSTACK_H

#include <QString>
#include "pmpaperpage.h"
#include <QSize>

typedef struct _PeUndoActionItm
{
	typedef enum{ACTION_PG_SETIMG,ACTION_PG_SWITCHIMG,  ACTION_PG_RMIMG,
		ACTION_PG_SETLAYOUT,ACTION_IMG_ZOOMIMG, ACTION_IMG_MOVEIMG,
		ACTION_PG_EDITIMG,
		ACTION_PG_ADD_PAPER, ACTION_PG_DEL_PAPER, ACTION_PG_MV_PAPER,
		ACTION_CAL_CFG_EDIT, ACTION_CAL_FIRSTMONTH, ACTION_CAL_YEAR,
		ACTION_PRJ_CHG_SHADOW
	}PE_ACTION;
	PE_ACTION action;
	union
	{
		struct 
		{
			PmPrintPaperPage *peditpaper;
			PmPrintPaperPage *psavepaper;
			PmPrintPaperPage *p2ndeditpaper; // some operation update two papers
			PmPrintPaperPage *p2ndsavepaper;
		}pageedit;
		struct 
		{
			PmPrintPaperPage *pphotoeditpaper;
			PmPrintPaperPage *pphotoeditsavepaper;
			QString *pupdatedphotopath;
		}imgedit;

		struct
		{
			PmPrintPaperPage *paddedpaper;
		}addpaper;
		struct
		{
			PmPrintPaperPage *pdeletedpaper;
			PmPrintPaperPage *porgbeforepaper;
		}rmpaper;
		struct
		{
			PmPrintPaperPage *pmvingpaper;
			PmPrintPaperPage *porgbeforepaper;
		}mvpaper;
		struct
		{
			int cnt;
			PmPrintPaperPage *edtpaper[12];
			PCALENDAR_CFG savedcalcfgs[12];
		}caledit;
		struct
		{
			int firstmonth;
		}calfirstmon;
		struct
		{
			int year;
		}calyear;
		struct
		{
			bool shadow;
		}prjprop;
	}saved;

	_PeUndoActionItm()
	{
		action = ACTION_PG_SETIMG;
		memset(&saved, 0, sizeof(saved));
	}

}PE_UNDOACT_ITEM;

class PmUndoActionStack 
{
private:
	PmUndoActionStack();
	~PmUndoActionStack();
public:
	static PmUndoActionStack& getInst();
	bool isUpdated(){return _updated;}
	void clearUpdated(){_updated = false;}
	void clearUndoStack();

public:
	bool pushAction(const PE_UNDOACT_ITEM &undoactitm );
	bool popAction(PE_UNDOACT_ITEM &undoactitm);
	bool hasActionStored();

private:
	QList<PE_UNDOACT_ITEM> _actionlst;
	bool _updated;
	
};

#endif // PMUNDOACTIONSTACK_H
