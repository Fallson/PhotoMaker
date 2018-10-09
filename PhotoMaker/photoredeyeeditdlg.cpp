#include "photoredeyeeditdlg.h"
#include "ui_photoredeyeeditdlg.h"

PhotoRedeyeEditDlg::PhotoRedeyeEditDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhotoRedeyeEditDlg)
{
    ui->setupUi(this);
}

PhotoRedeyeEditDlg::~PhotoRedeyeEditDlg()
{
    delete ui;
}
