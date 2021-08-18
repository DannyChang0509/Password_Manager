#include "dialog_du.h"
#include "ui_dialog_du.h"

#include "fileio.h"

#include <QMessageBox>

Dialog_DU::Dialog_DU(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_DU)
{
    ui->setupUi(this);
}

Dialog_DU::~Dialog_DU()
{
    delete ui;
    delete UserName;
}

void Dialog_DU::setUser(const QString & name)
{
    *UserName = name;
}

void Dialog_DU::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->lineEdit_3->setEchoMode(QLineEdit::Normal);
    }else
    {
        ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    }
}

void Dialog_DU::on_pushButton_clicked()
{
    QString * path = new QString("data/document_" + *UserName + ".dat");
    FileIO *file2 = new FileIO;
    file2->setPath(*path);
    FileIO * file1 = new FileIO;
    file1->setPath("data/User.dat");
    if(ui->lineEdit_3->text() == file2->ReadVerificationCode(file2->ReadFile()))
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, QObject::tr("Delete User"), QObject::tr("Are you sure you want to delete this user?\n§Note: This action cannot be undone."), QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            file1->DeleteUser(file1->ReadFile(), *UserName);
            file2->Remove();
        }
    }else
    {
        QMessageBox WarnBox(QMessageBox::Warning, QObject::tr("Error"), QObject::tr("Verification Code ERROR"));
        WarnBox.setWindowIcon(QIcon("icon.ico"));
        WarnBox.exec();
    }
    delete file1;
    delete file2;
    delete path;
}

