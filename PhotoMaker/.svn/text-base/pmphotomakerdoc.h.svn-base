#ifndef PMPHOTOMAKERDOC_H
#define PMPHOTOMAKERDOC_H

#include <QObject>
#include "PmPaperPage.h"
#include <QtXml/QDomDocument>




class PmPrintPaperPage;
class PmPhotoMakerDoc : public QObject
{
	Q_OBJECT

public:
	PmPhotoMakerDoc(QObject *parent);
	~PmPhotoMakerDoc();

public:
	bool newDoc(const PROJ_PROPS &prj);
	bool saveDoc(const QString &path);
	bool loadDoc(const QString &path);

public:
	void moveNextPaperPage();
	void movePrePaperPage();
	bool setCurPaperPage(PmPrintPaperPage *paperpage);
	bool getCurPrintPaperPage(PmPrintPaperPage *&pcurpaper, int &index);
	bool getPrintPaperPages(QList<PmPrintPaperPage*> &paperpages){paperpages = _paperpages; return true;}
	bool getProjProps(PROJ_PROPS &prj){prj = this->_projprops; return true;}
	bool updateProjProps(const PROJ_PROPS &prj);

	bool getPaperIndex(PmPrintPaperPage *paper, int &index);
	bool getPaperFromIndex(PmPrintPaperPage *&paper, int index);
	bool addPrintPaper(PmPrintPaperPage *paper, bool before, PmPrintPaperPage *&newPaper, int &index);
	bool insertPrintPaper(PmPrintPaperPage *newPaper, bool before, int index);
	bool rmPrintPaper(PmPrintPaperPage *paper, int &index);
	PmPrintPaperPage *createNewPaper();

	void updateLastEditPage();
	bool updateLastPhotoPage(PmPhotoPage* photopage);
	bool getPhotoPageIndex(PmPhotoPage* photopage, int &index);
	bool getLastEditPhotoPage( int &index);
	bool getNextEditPaper(PmPrintPaperPage * &nextPaper);

	PmPageItm *getCalItm(PmPrintPaperPage *Paper);

	//bool shadow(){return _shadow;}
	//void setShadow(bool shadow){_shadow = shadow;}
private:
	//
	void _maketmpfolder();
	void _constructDefLayout(PROJ_PROPS::LAYOUT_TYPE lytype, PmPrintPaperPage *paperpage);
	void _newPocketBook4X3(const PROJ_PROPS &prj);
	void _newPhotoBook10X15(const PROJ_PROPS &prj);
	void _newSingle4X6(const PROJ_PROPS &prj);
	void _newPhotoBook8X5(const PROJ_PROPS &prj);
	void _newCalendarA4(const PROJ_PROPS &prj);
	void _newCalendarA5(const PROJ_PROPS &prj);
	void _newCalendar4X6(const PROJ_PROPS &prj);
	PmPrintPaperPage *_newPaper();

	PmPageItm *_getCalItm(PmPrintPaperPage *paper);
	
private:
	bool _getPhotoPageIndex(PmPhotoPage* photopage, int &index, PmPhotoPage* &nextphotopage);
	void _updateLastEditPage();

private:
	bool _savePrjPropes(QDomDocument &doc,QDomElement &prjpropelem, PROJ_PROPS &prjpropes);
	bool _loadPrjPropes(QDomElement &prjpropselem, PROJ_PROPS &prjpropes);


	bool _saveTextItms(QDomDocument &doc,QDomElement &printpaerpageelem, const QList<PmTextItm*> &txtitmlst);
	bool _loadTextItms(QDomElement &textitmeelem,  QList<PmTextItm*> &txtitmlst);

	bool _saveTextItm(QDomDocument &doc,QDomElement &printpaerpageelem, PmTextItm &textitm);
	bool _loadTextItm(QDomElement &textitmeelem, PmTextItm *&textitm);

	bool _savePhotoItm(QDomDocument &doc, QDomElement &photopageelem, PmPageItm &photoitm);
	bool _loadPhotoItm(QDomElement &photoitmelem, PmPageItm *&photoitm);

	bool _savePhotoPage(QDomDocument &doc, QDomElement &printpaerpageelem, PmPhotoPage &photopage);
	bool _loadPhotoPage(QDomElement &photopageelem, PmPhotoPage *&photopage);

	bool _savePaperPage(QDomDocument &doc, QDomElement &container, PmPrintPaperPage &printpaperpage);
	bool _loadPaperPage(QDomElement &paperpageelem, PmPrintPaperPage *&printpaperpage);

	//
	bool _addContent(QDomDocument &doc,QDomElement &elem, const QString &content);
	bool _getContent(QDomElement &elem, QString &content);

	// basic types
	bool _savePos(QDomDocument &doc,QDomElement &parent, const QString &name, const LayoutBoxPos pos);
	bool _loadPos(QDomElement &poselem, LayoutBoxPos &pos);

	bool _saveMargin(QDomDocument &doc,QDomElement &parent, const QString &name, const LayoutBoxMargin margin);
	bool _loadMargin(QDomElement &marginelem, LayoutBoxMargin &margin);

	bool _saveSize(QDomDocument &doc,QDomElement &parent, const QString &name, const QSize size);
	bool _loadSize(QDomElement &sizeelem,  QSize &size);

	bool _saveInt(QDomDocument &doc,QDomElement &parent, const QString &name, const int value);
	bool _loadInt(QDomElement &elem, int &value);

	bool _saveFloat(QDomDocument &doc,QDomElement &parent, const QString &name, const qreal value);
	bool _loadFloat(QDomElement &elem, qreal &value);

	bool _saveStr(QDomDocument &doc,QDomElement &parent, const QString &name, const QString & value);
	bool _loadStr(QDomElement &elem, QString &value);

	bool _saveColor(QDomDocument &doc,QDomElement &parent, const QString &name, const QColor &color);
	bool _loadColor(QDomElement &elem, QColor &color);

	bool _saveCalCfg(QDomDocument &doc,QDomElement &parent, const QString &name, const CALENDAR_CFG &calcfg);
	bool _loadCalCfg(QDomElement &elem, CALENDAR_CFG &calcfg);

	bool _saveCalProps(QDomDocument &doc,QDomElement &parent, const QString &name, const CAL_PROPS &calcfg);
	bool _loadCalProps(QDomElement &elem, CAL_PROPS &calcfg);
	bool _saveWdProps(QDomDocument &doc,QDomElement &parent, const QString &name, const WEEKDAY_PROPS &calcfg);
	bool _loadWdProps(QDomElement &elem, WEEKDAY_PROPS &calcfg);
	bool _saveYmProps(QDomDocument &doc,QDomElement &parent, const QString &name, const MONTHYEAR_PROPS &calcfg);
	bool _loadYmProps(QDomElement &elem, MONTHYEAR_PROPS &calcfg);
	bool _saveFontProps(QDomDocument &doc,QDomElement &parent, const QString &name, const FONT_PROPS &fontprops);
	bool _loadFontProps(QDomElement &fontpropselem, FONT_PROPS  &fontprops);

	bool _saveSpaceProps(QDomDocument &doc,QDomElement &parent, const QString &name, const SPACE_PROPS &spaceprops);
	bool _loadSpaceProps(QDomElement &fontpropselem, SPACE_PROPS  &spaceprops);

private:
	PROJ_PROPS _projprops;
	PmPrintPaperPage *_printpaperpage;
	int  _curpaperindex;
	QList<PmPrintPaperPage *> _paperpages;

	PmPhotoPage *_lasteditpage;
	PmPhotoPage *_nexteditpage;


	bool _shadow;
};

#endif // PMPHOTOMAKERDOC_H
