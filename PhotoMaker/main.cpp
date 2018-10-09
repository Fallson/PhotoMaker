#include "photomaker.h"
#include <QtGui/QApplication>
#include <QtGui/qsplitter.h>
#include <QtGui/qtextedit.h>
#include <Qsplashscreen>
#include <QDesktopWidget>
#include <QThread>
#include <QSettings>
#include <QProcess>
#include <QDir>

#include "pmphotomakerdoc.h"
#include "pmprintprojcfgdlg.h"
#include "resValidator.h"

#if defined(Q_WS_WIN)
#include <Windows.h>
#include <Dbghelp.h>
#include <string>
using namespace std;
#endif

QApplication *g_app = NULL;


#if defined(Q_WS_WIN)

LONG
WINAPI
DSAUnhandledExceptionFilter(
    __in struct _EXCEPTION_POINTERS *ExceptionInfo
	)
{


	MINIDUMP_EXCEPTION_INFORMATION minidumpExcInfo;

	wstring path;
	path = L".\\pmphotomaker.dmp";

	minidumpExcInfo.ThreadId = ::GetCurrentThreadId();
	minidumpExcInfo.ExceptionPointers = ExceptionInfo;
	minidumpExcInfo.ClientPointers = FALSE; // in our own address space

	// do generate the dump
	MINIDUMP_TYPE dumpFlags;
	dumpFlags = MiniDumpWithFullMemory;


	HANDLE hDumpFile = CreateFileW(path.c_str(), GENERIC_READ|GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( !MiniDumpWriteDump(
		::GetCurrentProcess(),
		::GetCurrentProcessId(),
		hDumpFile,                    // file to write to
		dumpFlags,                  // kind of dump to craete
		&minidumpExcInfo,
		NULL,                       // no extra user-defined data
		NULL                        // no callbacks
		) )
	{
		// fail to create
	}

	CloseHandle(hDumpFile);

	return 0;
}


void DlpDefInvalidParameterHandler(const wchar_t* expression,
   const wchar_t* function, 
   const wchar_t* file, 
   unsigned int line, 
   uintptr_t pReserved)
{
   wprintf(L"Invalid parameter detected in function %s."
            L" File: %s Line: %d\n", function, file, line);
   wprintf(L"Expression: %s\n", expression);
   char *p = (char *) 0x0000235;
   //*p = 1;
   //printf("%d", *p);

}

#endif

void _connectFiletype()
{
	QSettings *ukenvFileReg = new QSettings("HKEY_CLASSES_ROOT\\.pm", QSettings::NativeFormat);   //

	QString currentValue = ukenvFileReg->value("Default").toString();
	if (currentValue.isEmpty() ||
		currentValue != "PhotoMaker.exe")
	{
		//QMessageBox::information(NULL,"information","Unregistered or Uncorrect");
		ukenvFileReg->setValue("Default", "PhotoMaker.exe");

		QSettings *ukenvIconReg = new QSettings("HKEY_CLASSES_ROOT\\PhotoMaker.exe\\DefaultIcon", QSettings::NativeFormat);
		ukenvIconReg->setValue("Default", QString(qApp->argv()[0]) + ",0"); 
		delete ukenvIconReg;

		QSettings *ukenvProgramReg = new QSettings("HKEY_CLASSES_ROOT\\PhotoMaker.exe\\shell\\open\\command", QSettings::NativeFormat);
                ukenvProgramReg->setValue("Default", QString(qApp->argv()[0]) + " %1");
		delete ukenvProgramReg; 
	}
	delete ukenvFileReg;  

}


class Producer : public QThread
{
public:
    int run(int argc, char *argv[], unsigned long ms);
};



int Producer::run(int argc, char *argv[], unsigned long ms)
{
    QApplication a(argc, argv);
	g_app = &a;

	QFont curfont;
	curfont =a.font();
	QString family = curfont.family();
	curfont.setFamily("Arial");
	curfont.setPointSizeF(9);
	QApplication::setFont(curfont);

#if defined(Q_WS_WIN)
	QString exepath = QCoreApplication::applicationFilePath();
	int index = exepath.lastIndexOf("/");
	QString workdir = exepath.left(index);
	QDir::setCurrent(workdir);
#endif

    QPixmap pixmap("Resources\\images\\splash.jpg");
    QSplashScreen splash(pixmap);
	splash.setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
    splash.show();

	//if ( !IsResValidator("Resources/images/splash.jpg") )
	//{
	//	return 0;
	//}
	
	splash.showMessage(tr("Wait..."), Qt::AlignLeft|Qt::AlignBottom, Qt::black);
    a.processEvents();//This is used to accept a click on the screen so that user can cancel the screen

    PmPhotoMakerDoc doc(NULL);
    PhotoMaker w(&doc);

    w.setWindowIcon(QIcon("Resources\\images\\AppIcon.ico"));
	//w.hide();

	if ( argc == 0 )
	{
		_connectFiletype();
	}

  //  QDesktopWidget* desktop = QApplication::desktop();
   // w.move((desktop->width() - w.width())/2, (desktop->height() - w.height())/2);
    w.show();
	a.processEvents();


    // wait some seconds
    this->msleep(ms);

    splash.finish(&w);


	if ( argc > 1 )
	{
		w.OpenProj(QString(argv[1]));
	}
	else
	{
		w.OnNewProj();
	}
	/*
    PmPrintProjCfgDlg dlg(&w);
    dlg.exec();
	*/

    // set infromation to doc

    // update views

    return a.exec();
}


int main(int argc, char *argv[])
{
#if defined(Q_WS_WIN)
	_invalid_parameter_handler oldHandler, newHandler;
	newHandler = DlpDefInvalidParameterHandler;
	oldHandler = _set_invalid_parameter_handler(newHandler);
	::SetUnhandledExceptionFilter(DSAUnhandledExceptionFilter);
#endif

    Producer p;
    p.run(argc, argv, 3000);
}
