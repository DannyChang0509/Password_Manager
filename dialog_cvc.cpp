#include "dialog_cvc.h"
#include "ui_dialog_cvc.h"

Dialog_CVC::Dialog_CVC(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_CVC)
{
    ui->setupUi(this);
}

Dialog_CVC::~Dialog_CVC()
{
    delete ui;
}
