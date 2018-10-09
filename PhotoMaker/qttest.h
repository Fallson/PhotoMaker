#ifndef QTTEST_H
#define QTTEST_H

#include <QObject>

class QtTest : public QObject
{
	Q_OBJECT

public:
	QtTest(QObject *parent);
	~QtTest();

private:
	
};

#endif // QTTEST_H
