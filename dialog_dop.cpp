#include "dialog_dop.h"
#include "ui_dialog_dop.h"

#include <QMessageBox>
#include <QString>

Dialog_DOP::Dialog_DOP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_DOP)
{
    ui->setupUi(this);
    connect(ui->comboBox, SIGNAL(clicked()), this, SLOT(ResetComboBox()));
}

Dialog_DOP::~Dialog_DOP()
{
    delete ui;
    delete file;
    delete ItemNum;
    delete temstrl;
    delete FilePath;
}

void Dialog_DOP::setPath(const QString & path)
{
    *FilePath = path;
}

void Dialog_DOP::ResetComboBox()
{
    file->setPath(*FilePath);
    temstrl->clear();
    *temstrl << file->ReadFile();
    *ItemNum = temstrl->size();
    ui->comboBox->clear();
    for(int i = 2; i < *ItemNum; i ++)
    {
        ui->comboBox->addItem(file->ReadItemName(*temstrl, i));
    }
}

void Dialog_DOP::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }else
    {
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}


void Dialog_DOP::on_pushButton_clicked()
{
    file->setPath(*FilePath);
    temstrl->clear();
    *temstrl << file->ReadFile();
    int *DeleteItem = new int(ui->comboBox->currentIndex());
    QString *VerificationCode = new QString(file->ReadVerificationCode(*temstrl));
    QString *VerificationCodeIn = new QString(ui->lineEdit_2->text());
    if(*VerificationCode == *VerificationCodeIn)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, QObject::tr("Delete Old Password"), QObject::tr("Are you sure you want to delete this password?\n§Note: This action cannot be undone."), QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            file->DeleteItem(*temstrl, *DeleteItem);
        }
    }else
    {
        QMessageBox WarnBox(QMessageBox::Warning, QObject::tr("Error"), QObject::tr("Verification Code ERROR"));
        WarnBox.setWindowIcon(QIcon("icon.ico"));
        WarnBox.exec();
    }
    delete DeleteItem;
    delete VerificationCode;
    delete VerificationCodeIn;
}

