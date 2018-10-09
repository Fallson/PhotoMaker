#include "pmprintseamauto2.h"
#include <QPrintDialog>
#include <QPrinterInfo>
#include <QPrinter>
#include <QPainter>

#ifdef WIN32
#define WINVER 0x0500
#include <Windows.h>
#include <Commdlg.h>
#include <Winspool.h>
#endif



PmPrintSeamAuto2::PmPrintSeamAuto2(const QPrinterInfo &printerinfo,const QString &printername, QWidget *parent)
	: QDialog(parent), _printername(printername), _printerinfo(printerinfo)
{
	ui.setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );
    setWindowIcon(QIcon("Resources\\images\\AppIcon.ico"));


	connect(ui.btnPrint, SIGNAL(clicked()), this, SLOT(OnPrint()));
	connect(ui.btnPrinterProps, SIGNAL(clicked()), this, SLOT(OnPrintProps()));

}

PmPrintSeamAuto2::~PmPrintSeamAuto2()
{

}

void PmPrintSeamAuto2::_print()
{
	QPrinter *printer = new QPrinter(_printerinfo);

	if ( _printerinfo.isNull() )
	{
		printer->setOutputFormat(QPrinter::PdfFormat);
		printer->setOutputFileName("C:/Users/penner/desktop/auto2.pdf");
	}

	bool a4=false, a5=false, b5=false;
	QList<QPrinter::PaperSize> supportedpapers = _printerinfo.supportedPaperSizes();
	QList<QPrinter::PaperSize>::iterator it;
	for ( it=supportedpapers.begin(); it!=supportedpapers.end(); it++ )
	{
		if ( (*it) == QPrinter::A4 )
		{
			// a4
			break;
		}
		if ( *it == QPrinter::A5 )
		{
			// a5
			break;
		}

		if ( *it == QPrinter::B5 )
		{
			// b5
			break;
		}
	}
	a4 = true;

	if ( a4 )
	{

		  printer->setPaperSize(QPrinter::A4);
		  printer->setOrientation(QPrinter::Landscape);
		  printer->setPageMargins(0,0,0,0, QPrinter::Point);
       
		  QPainter  *painter = new QPainter(printer);

		  QPen pen;
		  pen.setColor(Qt::gray);
		  pen.setWidth(4);
		  QPen oldpen = painter->pen();
		  painter->setPen(pen);

		  QRectF pageRect ;
		  pageRect = printer->pageRect(/*QPrinter::Point*/);

		  QPolygon polygon;
		  polygon.push_back(QPoint(pageRect.width()*1.0*(0.5 + 80*1.0/1110), pageRect.height()*0.5));
		  polygon.push_back(QPoint(pageRect.width()*1.0*(0.5 + 141*1.0/1110), pageRect.height()*(0.5-61*1.0/783)));
		  polygon.push_back(QPoint(pageRect.width()*1.0*(0.5 + 141*1.0/1110), pageRect.height()*(0.5-32*1.0/783)));
		  polygon.push_back(QPoint(pageRect.width()*1.0*(0.5 + 257*1.0/1110), pageRect.height()*(0.5-32*1.0/783)));
		  polygon.push_back(QPoint(pageRect.width()*1.0*(0.5 + 257*1.0/1110), pageRect.height()*(0.5+32*1.0/783)));
		  polygon.push_back(QPoint(pageRect.width()*1.0*(0.5 + 141*1.0/1110), pageRect.height()*(0.5+32*1.0/783)));
		  polygon.push_back(QPoint(pageRect.width()*1.0*(0.5 + 141*1.0/1110), pageRect.height()*(0.5+61*1.0/783)));
		  polygon.push_back(QPoint(pageRect.width()*1.0*(0.5 + 80*1.0/1110), pageRect.height()*0.5));
		  painter->drawPolygon(polygon);


		  QPen boldpen;
		  boldpen.setColor(Qt::black);
		  QFont font;
		  font.setBold(true);
		  //font.setFamily(QFont::SansSerif);
		  font.setPointSize(15);
		  QFont oldfont = painter->font();
		  painter->setPen(oldpen);
		  painter->setFont(font);
		  painter->drawText(QPointF(pageRect.width()*0.65, pageRect.height()*0.39 ), "2.");
		  painter->setFont(oldfont);
		  QTextOption txtopt;
		  txtopt.setWrapMode(QTextOption::WordWrap);
		  painter->drawText(QRectF(pageRect.width()*0.65, pageRect.height()*0.4 ,pageRect.width()*1.0*124/654,pageRect.height()*1.0*45/464),
			  "Please select the number where the red line is exactly over the black line",txtopt);

		  pen.setColor(Qt::red);
		  pen.setWidth(1);
		  painter->setPen(pen);
		  painter->drawLine(QPointF(pageRect.width()*1.0/2, 0), 
			  QPointF(pageRect.width()*1.0/2, pageRect.height()));

		  delete painter;
	}

	delete printer;
}

void PmPrintSeamAuto2::OnPrint()
{
	_print();
	this->accept();
}

void PmPrintSeamAuto2::OnPrintProps()
{
#ifdef WIN32

	HANDLE hPrint;
	BOOL ret = OpenPrinterW((LPWSTR)_printername.toStdWString().c_str(), &hPrint, NULL);
	if ( !ret )
	{
		return ;
	}
	QStdWString name = _printername.toStdWString();

	DEVMODE *pDevNode;

	HWND hWnd = this->window()->winId();
	DWORD dwRet = DocumentPropertiesW(hWnd,hPrint, (LPWSTR)name.c_str(),NULL, NULL, 0);
	if ( dwRet <= 0 )
	{
		CloseHandle(hPrint);
		return ;
	}
	pDevNode = (DEVMODE *)malloc(dwRet);
	if ( !pDevNode )
	{
		CloseHandle(hPrint);
		return ;
	}

	memset(pDevNode, 0, dwRet);
	PRINTER_INFO_1W *printerinfo;
	dwRet = 0;
	ret = GetPrinterW(hPrint, 1,NULL, 0, &dwRet);
	if ( !dwRet )
	{
		CloseHandle(hPrint);
		free(pDevNode);
		return ;
	}

	printerinfo = (PRINTER_INFO_1W*)malloc(dwRet);
	if ( !printerinfo )
	{
		CloseHandle(hPrint);
		free(pDevNode);
		return ;
	}
	ret = GetPrinterW(hPrint, 1,(LPBYTE)printerinfo, dwRet, &dwRet);
	if (!ret )
	{
		CloseHandle(hPrint);
		free(pDevNode);
		free(printerinfo);
		return ;
	}
	wcsncpy(pDevNode->dmDeviceName,printerinfo->pName,_countof(pDevNode->dmDeviceName));
	if ( wcslen(printerinfo->pName) >= _countof(pDevNode->dmDeviceName) )
	{
		pDevNode->dmDeviceName[_countof(pDevNode->dmDeviceName)-1] = 0;
	}

	dwRet = DocumentPropertiesW(hWnd,NULL, (LPWSTR)name.c_str(),pDevNode, pDevNode, DM_IN_BUFFER|DM_OUT_BUFFER|DM_PROMPT);

	free(pDevNode);
	ClosePrinter(hPrint);
	//printpropdlg.exec();
#endif
}
