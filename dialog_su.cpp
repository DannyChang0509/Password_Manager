#include "dialog_su.h"
#include "ui_dialog_su.h"

#include "fileio.h"

#include <QMessageBox>

Dialog_SU::Dialog_SU(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_SU)
{
    ui->setupUi(this);
    userfile->setPath("data/User.dat");
    ui->lineEdit_2->setToolTip(QObject::tr("Set a verification code of your own, will use identity verification.\nOnly English letters, numbers, symbols."));
}

Dialog_SU::~Dialog_SU()
{
    delete ui;
    delete userfile;
}

void Dialog_SU::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }else
    {
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}


void Dialog_SU::on_pushButton_clicked()
{
    QString * UserName = new QString(ui->lineEdit->text());
    QString * VerificationCode = new QString(ui->lineEdit_2->text());
    if(*UserName != "" && *VerificationCode != "")
    {
        QFile * oldfile = new QFile;
        oldfile->setFileName("data/document_" + *UserName + ".dat");
        if(oldfile->exists())
        {
            QMessageBox WarnBox(QMessageBox::Information, QObject::tr("Information"), *UserName + QObject::tr(" is already registered"));
            WarnBox.setWindowIcon(QIcon("icon.ico"));
            WarnBox.exec();
        }else{
            FileIO * newfile = new FileIO;
            newfile->setPath("data/document_" + *UserName + ".dat");
            newfile->ChangeVerificationCode(newfile->ReadFile(), *VerificationCode);
            userfile->AddUser(userfile->ReadFile(), *UserName);
            delete newfile;
        }
        delete oldfile;
    }else{
        QMessageBox WarnBox(QMessageBox::Warning, QObject::tr("Input Error"), QObject::tr("Input(s) Cannot Remain Empty"));
        WarnBox.setWindowIcon(QIcon("icon.ico"));
        WarnBox.exec();
    }
    delete UserName;
    delete VerificationCode;
}

