#include "respublisher.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ResPublisher w;
	w.show();
	return a.exec();
}
