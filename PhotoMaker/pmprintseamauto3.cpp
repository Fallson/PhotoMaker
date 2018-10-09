#include "pmprintseamauto3.h"

PmPrintSeamAuto3::PmPrintSeamAuto3(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.etCalibrationNum->setValidator(new QIntValidator(1, 50, this));

	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );
    setWindowIcon(QIcon("Resources\\images\\AppIcon.ico"));

	connect(ui.btnFinish, SIGNAL(clicked()), this, SLOT(OnFinish()));

}

PmPrintSeamAuto3::~PmPrintSeamAuto3()
{

}


void PmPrintSeamAuto3::OnFinish()
{
	_calibrationNo = ui.etCalibrationNum->text();
	accept();
}

bool PmPrintSeamAuto3::getCalibrationNo(int &no)
{
	no = _calibrationNo.toInt();
	return true;
}
