#include "pmprintseamdlg.h"
#include "pmprintseamauto1.h"
#include "pmprintseamauto2.h"
#include "pmprintseamauto3.h"


PmPrintSeamDlg::PmPrintSeamDlg(const QPrinterInfo &printerinfo,const QString &printername, QWidget *parent)
	: QDialog(parent), _printername(printername), _printerinfo(printerinfo),_calibrationNo(0)
{
	ui.setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );
    setWindowIcon(QIcon("Resources\\images\\AppIcon.ico"));

	ui.PsDemo->setPixmap(QPixmap::fromImage(QImage("Resources/Images/PrintSeamDemo.png")));
	ui.btnInc->setText("");
	ui.btnInc->setFlat(true);
	ui.btndec->setText("");
	ui.btndec->setFlat(true);

	ui.btnInc->setIcon(QIcon("Resources/Images/next.png"));
	ui.btndec->setIcon(QIcon("Resources/Images/pre.png"));

//	QString off = QString(tr("
	ui.lbOffset->setText("0.0 mm");

	connect(ui.btnAutoAdjust, SIGNAL(clicked()), this, SLOT(OnAutoAdjust()));
	connect(ui.btndec, SIGNAL(clicked()), this, SLOT(OnDesc()));
	connect(ui.btnInc, SIGNAL(clicked()), this, SLOT(OnInc()));
  	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnOK()));
	connect(ui.btnCancel, SIGNAL(clicked()), this, SLOT(OnCancel()));
}

PmPrintSeamDlg::~PmPrintSeamDlg()
{

}



void PmPrintSeamDlg::OnOK()
{
	accept();
	this->close();
}

void PmPrintSeamDlg::OnCancel()
{
	reject();
	this->close();
}
void PmPrintSeamDlg::OnDesc()
{
	_calibrationNo--;
	if ( _calibrationNo < 1 )
	{
		_calibrationNo = 1;
	}
	_adjustCalibrationLabel();

}

void PmPrintSeamDlg::OnInc()
{
	_calibrationNo++;
	if ( _calibrationNo > 50 )
	{
		_calibrationNo = 50;
	}
	_adjustCalibrationLabel();
}

void PmPrintSeamDlg::OnAutoAdjust()
{
	PmPrintSeamAuto1 auto1(_printerinfo, _printername);
	PmPrintSeamAuto2 auto2(_printerinfo,_printername);
	PmPrintSeamAuto3 auto3;

	if ( QDialog::Accepted != auto1.exec() )
	{
		return ;
	}

	if ( QDialog::Accepted != auto2.exec() )
	{
		return ;
	}

	if ( QDialog::Accepted != auto3.exec() )
	{
		return ;
	}

	auto3.getCalibrationNo(_calibrationNo);
	_adjustCalibrationLabel();

}

void PmPrintSeamDlg::_adjustCalibrationLabel()
{
	QString offset;
	if ( _calibrationNo == 13 )
	{
		// center 
		offset = tr("0.0 mm");
	}
	else if ( _calibrationNo < 13 )
	{
		// left
		qreal seamoff = (13 - _calibrationNo) * 0.1;
		offset = QString(tr("%1 mm to left")).arg(seamoff);
	}
	else if ( _calibrationNo > 13 )
	{
		// right
		qreal seamoff = (_calibrationNo - 13) * 0.1;
		offset = QString(tr("%1 mm to right")).arg(seamoff);
	}

	ui.lbOffset->setText(offset);
}


bool PmPrintSeamDlg::getCalibrationNo(int &calibrationNo)
{
	calibrationNo = _calibrationNo;
	return true;
}

bool PmPrintSeamDlg::setCalibrationNo(int calibrationNo)
{
	if ( calibrationNo != _calibrationNo )
	{
		_calibrationNo = calibrationNo;
	}

	QString offset;
	if ( _calibrationNo == 13 )
	{
		// center 
		offset = tr("0.0 mm");
	}
	else if ( _calibrationNo < 13 )
	{
		// left
		qreal seamoff = (13 - _calibrationNo) * 0.1;
		offset = QString(tr("%1 mm to left")).arg(seamoff);
	}
	else if ( _calibrationNo > 13 )
	{
		// right
		qreal seamoff = (_calibrationNo - 13) * 0.1;
		offset = QString(tr("%1 mm to right")).arg(seamoff);
	}

	ui.lbOffset->setText(offset);

	return true;
}

