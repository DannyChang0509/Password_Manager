#include "dialog_eop.h"
#include "ui_dialog_eop.h"
#include "item.h"

#include <QMessageBox>
#include <QString>

Dialog_EOP::Dialog_EOP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_EOP)
{
    ui->setupUi(this);
    connect(ui->comboBox, SIGNAL(clicked()), this, SLOT(ResetComboBox()));
    ui->lineEdit_3->setToolTip(QObject::tr("Only English letters, numbers, symbols."));
    ui->lineEdit_2->setToolTip(QObject::tr("Only English letters, numbers, symbols."));
}

Dialog_EOP::~Dialog_EOP()
{
    delete ui;
    delete file;
    delete ItemNum;
    delete temstrl;
    delete FilePath;
}

void Dialog_EOP::setPath(const QString & path)
{
    *FilePath = path;
}

void Dialog_EOP::ResetComboBox()
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

void Dialog_EOP::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }else
    {
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}


void Dialog_EOP::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->lineEdit_4->setEchoMode(QLineEdit::Normal);
    }else
    {
        ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    }
}


void Dialog_EOP::on_pushButton_clicked()
{
    file->setPath(*FilePath);
    temstrl->clear();
    *temstrl << file->ReadFile();
    int * EditItem = new int(ui->comboBox->currentIndex());
    QString * VerificationCode = new QString(file->ReadVerificationCode(*temstrl));
    QString * VerificationCodeIn = new QString(ui->lineEdit_4->text());
    Item * item = new Item;
    QString * temstr = new QString;
    *temstr = ui->lineEdit_5->text();
    item->SetItemName(*temstr);
    *temstr = ui->lineEdit_3->text();
    item->SetAccount(*temstr);
    *temstr = ui->lineEdit_2->text();
    item->SetPassword(*temstr);
    delete  temstr;
    if(*VerificationCode == *VerificationCodeIn)
    {
        if(item->GetItemName() == "" || item->GetAccount() == "" || item->GetPassword() == "")
        {
            QMessageBox WarnBox(QMessageBox::Warning, QObject::tr("Input Error"), QObject::tr("Input(s) Cannot Remain Empty"));
            WarnBox.setWindowIcon(QIcon("icon.ico"));
            WarnBox.exec();
        }else
        {
            file->EditItem(*temstrl, *EditItem, *item);
        }
    }else
    {
        QMessageBox WarnBox(QMessageBox::Warning, QObject::tr("Error"), QObject::tr("Verification Code ERROR"));
        WarnBox.setWindowIcon(QIcon("icon.ico"));
        WarnBox.exec();
    }
    delete EditItem;
    delete VerificationCode;
    delete VerificationCodeIn;
    delete item;
}


void Dialog_EOP::on_comboBox_activated(int index)
{
    file->setPath(*FilePath);
    temstrl->clear();
    *temstrl << file->ReadFile();
    ui->lineEdit_5->setText(file->ReadItemName(*temstrl, index+2));
    ui->lineEdit_3->setText(file->ReadAccount(*temstrl, index+2));
}

