#include "respublisher.h"
#include <QFileDialog>
#include <QCryptographicHash>

ResPublisher::ResPublisher(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	connect(ui.btnGenerate, SIGNAL(clicked()), this, SLOT(OnGenerateResData()));
	connect(ui.btnBrowser, SIGNAL(clicked()), this, SLOT(OnBrowse()));
}

ResPublisher::~ResPublisher()
{

}

void ResPublisher::OnGenerateResData()
{
	//
	// 1. 
	QString resdatafilepath = this->ui.etResPath->text();
	resdatafilepath += "/";
	resdatafilepath += "pmres.dll";
	QFile resdatafile(resdatafilepath);
	resdatafile.open(QIODevice::WriteOnly);

	resdatafile.write("any request, please contract pennerchang@gmail.com\n");


	// Resources/images/splash.jpg
	QString filepath = this->ui.etResPath->text();
	filepath += "/";
	filepath += "Resources/images/splash.jpg";

	{
		QFile file(filepath);
		file.open(QIODevice::ReadOnly);
		QByteArray fileByteArray=file.readAll();
		QByteArray md5QByteArray=QCryptographicHash::hash(fileByteArray,QCryptographicHash::Md5);
		QString md5;
		md5.append(md5QByteArray.toHex());

		resdatafile.write(md5.toAscii().data());
		resdatafile.write("\n");
	}

	

	//
	// 
	//
}

void ResPublisher::OnBrowse()
{
	QFileDialog filedlg;
	filedlg.setAcceptMode(QFileDialog::AcceptOpen);
	//filedlg.exec();
	QString filepath = filedlg.getExistingDirectory(this, tr("Select resource folder"));
	ui.etResPath->setText(filepath);

}
