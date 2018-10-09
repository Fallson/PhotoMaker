
#include <QString>
#include "resValidator.h"
#include <QFile>
#include <QCryptographicHash>

bool IsResValidator(const QString &respath)
{
	//
	// 1. 
        #ifdef Q_OS_MACX
            return true;
        #endif

	QString resdatafilepath =  "./pmres.dll";
	QFile resdatafile(resdatafilepath);
	resdatafile.open(QIODevice::ReadOnly);
	QByteArray mymail = resdatafile.readLine();
	if ( mymail != QByteArray("any request, please contract pennerchang@gmail.com\n") )
	{
		return false;
	}

	if ( respath == "Resources/images/splash.jpg" )
	{

		// Resources/images/splash.jpg
		QString filepath ="./Resources/images/splash.jpg";

		QFile file(filepath);
		file.open(QIODevice::ReadOnly);
		QByteArray fileByteArray=file.readAll();
		QByteArray md5QByteArray=QCryptographicHash::hash(fileByteArray,QCryptographicHash::Md5);
		QString md5;
		md5.append(md5QByteArray.toHex());

		
		QByteArray resmd5ByteArray=resdatafile.readLine();;
		if ( md5 + "\n"  == resmd5ByteArray )
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	else if ( respath == "Resources/images/about.jpg" )
	{
	}
	else 
	{
	}

	return false;
	

	//
	// 
	//
}
