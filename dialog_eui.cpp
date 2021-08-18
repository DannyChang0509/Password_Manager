#include "dialog_eui.h"
#include "ui_dialog_eui.h"

#include "fileio.h"

#include <QMessageBox>

Dialog_EUI::Dialog_EUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_EUI)
{
    ui->setupUi(this);
}

Dialog_EUI::~Dialog_EUI()
{
    delete ui;
    delete UserName;
}

void Dialog_EUI::setUser(const QString & name)
{
    *UserName = name;
    ui->lineEdit->setText(*UserName);
}

void Dialog_EUI::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->lineEdit_3->setEchoMode(QLineEdit::Normal);
    }else
    {
        ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    }
}


void Dialog_EUI::on_pushButton_clicked()
{
    QString * path = new QString("data/document_" + *UserName + ".dat");
    FileIO *file2 = new FileIO;
    file2->setPath(*path);
    FileIO * file1 = new FileIO;
    file1->setPath("data/User.dat");
    if(ui->lineEdit_3->text() == file2->ReadVerificationCode(file2->ReadFile()))
    {
        QString * NewName = new QString(ui->lineEdit->text());
        if(*NewName == "")
        {
            QMessageBox WarnBox(QMessageBox::Warning, QObject::tr("Input Error"), QObject::tr("Input(s) Cannot Remain Empty"));
            WarnBox.setWindowIcon(QIcon("icon.ico"));
            WarnBox.exec();
        }else
        {
            file1->ChangeUserName(file1->ReadFile(), *UserName, *NewName);
            QString * newpath = new QString("data/document_" + *NewName + ".dat");
            file2->Rename(*newpath);
            delete NewName;
            delete newpath;
            QMessageBox InfoBox(QMessageBox::Information, QObject::tr("Information"), QObject::tr("Please Log In Again"));
            InfoBox.setWindowIcon(QIcon("icon.ico"));
            InfoBox.exec();
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


void Dialog_EUI::on_pushButton_3_clicked()
{

}

