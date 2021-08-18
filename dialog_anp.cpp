#include "dialog_anp.h"
#include "ui_dialog_anp.h"

#include "item.h"
#include "fileio.h"

#include <QMessageBox>

Dialog_ANP::Dialog_ANP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ANP)
{
    ui->setupUi(this);
    ui->lineEdit_3->setToolTip(QObject::tr("Only English letters, numbers, symbols."));
    ui->lineEdit_2->setToolTip(QObject::tr("Only English letters, numbers, symbols."));
}

Dialog_ANP::~Dialog_ANP()
{
    delete ui;
    delete FilePath;
}

void Dialog_ANP::setPath(const QString & path)
{
    *FilePath = path;
}

void Dialog_ANP::on_pushButton_clicked()
{
    Item *item = new Item;
    QString * temstr = new QString;
    *temstr = ui->lineEdit->text();
    item->SetItemName(*temstr);
    *temstr = ui->lineEdit_3->text();
    item->SetAccount(*temstr);
    *temstr = ui->lineEdit_2->text();
    item->SetPassword(*temstr);
    delete temstr;
    if(item->GetItemName() == "" || item->GetAccount() == "" || item->GetPassword() == "")
    {
        QMessageBox WarnBox(QMessageBox::Warning, QObject::tr("Input Error"), QObject::tr("Input(s) Cannot Remain Empty"));
        WarnBox.setWindowIcon(QIcon("icon.ico"));
        WarnBox.exec();
    }else
    {
        FileIO *file = new FileIO;
        file->setPath(*FilePath);
        QStringList * temstrl = new QStringList(file->ReadFile());
        bool *repeat = new bool;
        *repeat = false;
        for(int i = 0; i < temstrl->size()-2; i ++) {
            if(file->ReadItemName(*temstrl, i) == item->GetItemName())
            {
                *repeat = true;
                QMessageBox WarnBox(QMessageBox::Information, QObject::tr("Information"), item->GetItemName() + QObject::tr(" already exists"));
                WarnBox.setWindowIcon(QIcon("icon.ico"));
                WarnBox.exec();
                break;
            }
        }
        if(!(*repeat))
        {
            file->AddItem(*temstrl, *item);
        }
        delete file;
        delete temstrl;
        delete repeat;
    }
    delete item;
}


void Dialog_ANP::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }else
    {
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}

