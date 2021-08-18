#include "dialog_cv.h"
#include "ui_dialog_cv.h"

#include <QMessageBox>

Dialog_CV::Dialog_CV(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_CV)
{
    ui->setupUi(this);
    ui->lineEdit_3->setToolTip(QObject::tr("Only English letters, numbers, symbols."));
}

Dialog_CV::~Dialog_CV()
{
    delete ui;
    delete file;
    delete FilePath;
}

void Dialog_CV::setPath(const QString & path)
{
    *FilePath = path;
}

void Dialog_CV::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->lineEdit->setEchoMode(QLineEdit::Normal);
    }else
    {
        ui->lineEdit->setEchoMode(QLineEdit::Password);
    }
}


void Dialog_CV::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->lineEdit_3->setEchoMode(QLineEdit::Normal);
    }else
    {
        ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    }
}


void Dialog_CV::on_pushButton_clicked()
{
    file->setPath(*FilePath);
    QStringList * temstrl = new QStringList(file->ReadFile());
    QString *OldVerificationCode = new QString(file->ReadVerificationCode(*temstrl));
    QString *OldVerificationCodeIn = new QString(ui->lineEdit->text());
    QString *NewVerificationCode = new QString(ui->lineEdit_3->text());
    if(*OldVerificationCode == *OldVerificationCodeIn)
    {
        if(*NewVerificationCode != "")
        {
            file->ChangeVerificationCode(*temstrl, *NewVerificationCode);
        }else
        {
            QMessageBox WarnBox(QMessageBox::Warning, QObject::tr("Input Error"), QObject::tr("Input(s) Cannot Remain Empty"));
            WarnBox.setWindowIcon(QIcon("icon.ico"));
            WarnBox.exec();
        }
    }else
    {
        QMessageBox WarnBox(QMessageBox::Warning, QObject::tr("Error"), QObject::tr("Verification Code ERROR"));
        WarnBox.setWindowIcon(QIcon("icon.ico"));
        WarnBox.exec();
    }
    delete temstrl;
    delete OldVerificationCode;
    delete OldVerificationCodeIn;
    delete NewVerificationCode;
}

