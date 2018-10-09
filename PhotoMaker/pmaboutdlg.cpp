#include "pmaboutdlg.h"
#ifdef Q_OS_WIN32
#include <Windows.h>
#endif

PmAboutDlg::PmAboutDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );
    setWindowIcon(QIcon("Resources\\images\\AppIcon.ico"));

	ui.lbShowPic->setPixmap(QPixmap("Resources\\images\\about.jpg"));

	ui.lbInternetAddr->setOpenExternalLinks(true);
	ui.lbInternetAddr->setText("<a href=www.misiland.com.cn>www.misiland.com.cn</a>");
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(close()));
	//ui.lbInternetAddr->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard);
	//connect(ui.lbInternetAddr, SIGNAL(clicked()), this, SLOT(OnVisitWeb()));
}

PmAboutDlg::~PmAboutDlg()
{

}

void PmAboutDlg::OnVisitWeb()
{
#ifdef Q_OS_WIN32

	QString url;
	QString str = ui.lbInternetAddr->text();
	HWND parent = ::GetDesktopWindow();
	wchar_t *wszurl = (TCHAR *)str.utf16();
	HINSTANCE result = ::ShellExecuteW(0, NULL, wszurl, NULL, NULL, SW_SHOWNORMAL);
	return ;

	#endif

	#ifdef Q_OS_MACX

//can not compile in macx

	#endif
}
