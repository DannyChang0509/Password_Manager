#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog_cv.h"
#include "dialog_anp.h"
#include "dialog_dop.h"
#include "dialog_eop.h"
#include "dialog_su.h"
#include "dialog_eui.h"
#include "dialog_du.h"
#include "fileio.h"
#include "item.h"

#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_6->setText("");
    ui->toolButton->hide();
    ui->toolButton->setToolTip(QObject::tr("Log Out"));
    userfile->setPath("data/User.dat");
    ResetUserComboBox();
    connect(ui->comboBox, SIGNAL(clicked()), this, SLOT(ResetFileComboBox()));
    connect(ui->comboBox_2, SIGNAL(clicked()), this, SLOT(ResetUserComboBox()));
    trsChinese = new QTranslator();
    trsEnglish = new QTranslator();
    trsChinese->load("system/language/translation_chinese.qm");
    trsEnglish->load("system/language/translation_english.qm");
    *language = languagefile->getLanguage();
    if(*language == 0)
    {
        qApp->installTranslator(trsChinese);
        ui->retranslateUi(this);
    }else if(*language == 1)
    {
        qApp->installTranslator(trsEnglish);
        ui->retranslateUi(this);
    }
}

void MainWindow::ResetComboBox(int num)
{
    temstrl->clear();
    file->setPath(*FilePath);
    if(num == 1)
    {
        *temstrl << file->ReadFile();
        ui->comboBox->clear();
    }else if(num == 2){
        *temstrl << userfile->ReadFile();
        ui->comboBox_2->clear();
    }
    *ItemNum = temstrl->size();
    for(int i = 2; i < *ItemNum; i ++)
    {
        if(num == 1)
        {
            ui->comboBox->addItem(file->ReadItemName(*temstrl, i));
        }else if(num == 2){
            ui->comboBox_2->addItem(userfile->ReadItemName(*temstrl, i));
        }
    }
}

void MainWindow::ResetFileComboBox(){
    ResetComboBox(1);
}

void MainWindow::ResetUserComboBox(){
    ResetComboBox(2);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete file;
    delete userfile;
    delete languagefile;
    delete temstrl;
    delete ItemNum;
    delete User;
    delete trsChinese;
    delete trsEnglish;
    delete language;
}

void MainWindow::on_actionAbout_this_APP_triggered()
{
    QFile *file2 = new QFile;
    if(*language)
    {
        file2->setFileName("system/about_english.dat");
    }else{
        file2->setFileName("system/about_chinese.dat");
    }
    file2->open(QIODevice::ReadOnly | QIODevice::Text);
    QString *allStr = new QString((QString)file2->readAll());
    file2->close();

    QMessageBox AboutBox(QMessageBox::NoIcon, QObject::tr("About Password Manager"), *allStr);
    AboutBox.setIconPixmap(QPixmap("icon_s.png"));
    AboutBox.setWindowIcon(QIcon("icon.ico"));
    AboutBox.exec();

    delete file2;
    delete allStr;
}

void MainWindow::on_pushButton_clicked()
{
    if(*ItemNum <= 2)
    {
        QMessageBox InfoBox(QMessageBox::Information, QObject::tr("Information"), QObject::tr("No Data Exist"));
        InfoBox.setWindowIcon(QIcon("icon.ico"));
        InfoBox.exec();
    }else
    {
        int *ItemN = new int(ui->comboBox->currentIndex());
        *ItemN += 2;
        temstrl->clear();
        *temstrl << file->ReadFile();
        if(ui->lineEdit->text() == file->ReadVerificationCode(*temstrl))
        {
            ui->stackedWidget->setCurrentIndex(2);
            ui->toolButton->hide();
            ui->label_2->setText(file->ReadItemName(*temstrl, *ItemN));
            ui->lineEdit_2->setText(file->ReadAccount(*temstrl, *ItemN));
            ui->lineEdit_3->setText(file->ReadPassword(*temstrl, *ItemN));
        }else
        {
            QMessageBox WarnBox(QMessageBox::Warning, QObject::tr("Error"), QObject::tr("Verification Code ERROR"));
            WarnBox.setWindowIcon(QIcon("icon.ico"));
            WarnBox.exec();
        }
        delete ItemN;
    }
    ui->lineEdit->clear();
}

void MainWindow::on_actionset_verification_code_triggered()
{
    if(ui->stackedWidget->currentIndex() != 0)
    {
        Dialog_CV dCV;
        dCV.setPath(*FilePath);
        dCV.setWindowTitle(QObject::tr("Change Verification Code"));
        dCV.setWindowIcon(QIcon("icon.ico"));
        dCV.exec();
    }else{
        QMessageBox InfoBox(QMessageBox::Information, QObject::tr("Information"), QObject::tr("Please Log In First"));
        InfoBox.setWindowIcon(QIcon("icon.ico"));
        InfoBox.exec();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->toolButton->show();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->lineEdit->setEchoMode(QLineEdit::Normal);
    }else
    {
        ui->lineEdit->setEchoMode(QLineEdit::Password);
    }
}

void MainWindow::on_actionInstruction_triggered()
{
    QFile *file2 = new QFile;
    if(*language)
    {
        file2->setFileName("system/instruction_english.dat");
    }else{
        file2->setFileName("system/instruction_chinese.dat");
    }
    file2->open(QIODevice::ReadOnly | QIODevice::Text);
    QString *allStr = new QString((QString)file2->readAll());
    file2->close();

    QMessageBox AboutBox(QMessageBox::NoIcon, QObject::tr("Instruction"), *allStr);
    AboutBox.setWindowIcon(QIcon("icon.ico"));
    AboutBox.exec();

    delete allStr;
}

void MainWindow::on_actionAdd_new_Password_triggered()
{
    if(ui->stackedWidget->currentIndex() != 0)
    {
        Dialog_ANP dANP;
        dANP.setPath(*FilePath);
        dANP.setWindowTitle(QObject::tr("Add New Password"));
        dANP.setWindowIcon(QIcon("icon.ico"));
        dANP.exec();
    }else{
        QMessageBox InfoBox(QMessageBox::Information, QObject::tr("Information"), QObject::tr("Please Log In First"));
        InfoBox.setWindowIcon(QIcon("icon.ico"));
        InfoBox.exec();
    }
}


void MainWindow::on_actionDelet_password_triggered()
{
    if(ui->stackedWidget->currentIndex() != 0)
    {
        temstrl->clear();
        *temstrl << file->ReadFile();
        int * num = new int(temstrl->size());
        if(*num <= 2)
        {
            QMessageBox InfoBox(QMessageBox::Information, QObject::tr("Information"), QObject::tr("No Data Exist"));
            InfoBox.setWindowIcon(QIcon("icon.ico"));
            InfoBox.exec();
        }else
        {
            Dialog_DOP dDOP;
            dDOP.setPath(*FilePath);
            dDOP.setWindowTitle(QObject::tr("Delete Old Password"));
            dDOP.setWindowIcon(QIcon("icon.ico"));
            dDOP.exec();
        }
        delete num;
    }else{
        QMessageBox InfoBox(QMessageBox::Information, QObject::tr("Information"), QObject::tr("Please Log In First"));
        InfoBox.setWindowIcon(QIcon("icon.ico"));
        InfoBox.exec();
    }
}


void MainWindow::on_actionEdit_password_triggered()
{
    if(ui->stackedWidget->currentIndex() != 0)
    {
        temstrl->clear();
        *temstrl << file->ReadFile();
        int *num = new int(temstrl->size());
        if(*num <= 2)
        {
            QMessageBox InfoBox(QMessageBox::Information, QObject::tr("Information"), QObject::tr("No Data Exist"));
            InfoBox.setWindowIcon(QIcon("icon.ico"));
            InfoBox.exec();
        }else
        {
            Dialog_EOP dEOP;
            dEOP.setPath(*FilePath);
            dEOP.setWindowTitle(QObject::tr("Edit Old Password"));
            dEOP.setWindowIcon(QIcon("icon.ico"));
            dEOP.exec();
        }
        delete num;
    }else{
        QMessageBox InfoBox(QMessageBox::Information, QObject::tr("Information"), QObject::tr("Please Log In First"));
        InfoBox.setWindowIcon(QIcon("icon.ico"));
        InfoBox.exec();
    }
}

void MainWindow::on_toolButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->toolButton->hide();
    ui->label_6->setText("");
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->lineEdit_4->setEchoMode(QLineEdit::Normal);
    }else
    {
        ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    *User = ui->comboBox_2->currentText();
    if(*User == ""){
        QMessageBox InfoBox(QMessageBox::Information, QObject::tr("Information"), QObject::tr("No User"));
        InfoBox.setWindowIcon(QIcon("icon.ico"));
        InfoBox.exec();
    }else
    {
        *FilePath = "data/document_";
        FilePath->append(*User);
        FilePath->append(".dat");
        file->setPath(*FilePath);
        temstrl->clear();
        *temstrl << file->ReadFile();
        if(ui->lineEdit_4->text() == file->ReadVerificationCode(*temstrl))
        {
             ui->stackedWidget->setCurrentIndex(1);
             ResetComboBox(1);
             ui->toolButton->show();
             ui->label_6->setText(*User);
        }else{
            QMessageBox WarnBox(QMessageBox::Warning, QObject::tr("Error"), QObject::tr("Verification Code ERROR"));
            WarnBox.setWindowIcon(QIcon("icon.ico"));
            WarnBox.exec();
        }
    }
    ui->lineEdit_4->clear();
}


void MainWindow::on_pushButton_4_clicked()
{
    Dialog_SU dSU;
    dSU.setWindowTitle(QObject::tr("Sign Up"));
    dSU.setWindowIcon(QIcon("icon.ico"));
    dSU.exec();
    ResetComboBox(2);
    ui->comboBox_2->setCurrentIndex(userfile->ReadFile().size()-3);
}


void MainWindow::on_actionAdd_New_User_triggered()
{
    if(ui->stackedWidget->currentIndex() != 0)
    {
        Dialog_EUI dEUI;
        dEUI.setUser(*User);
        dEUI.setWindowTitle(QObject::tr("Edit User Information"));
        dEUI.setWindowIcon(QIcon("icon.ico"));
        dEUI.exec();
        QFile * temfile = new QFile;
        int * num = new int(ui->comboBox_2->currentIndex());
        temfile->setFileName(*FilePath);
        if(!temfile->exists()){
            ui->stackedWidget->setCurrentIndex(0);
            ResetComboBox(2);
            ui->comboBox_2->setCurrentIndex(*num);
            ui->toolButton->hide();
            ui->label_6->setText("");
        }
        delete num;
        delete temfile;
    }else{
        QMessageBox InfoBox(QMessageBox::Information, QObject::tr("Information"), QObject::tr("Please Log In First"));
        InfoBox.setWindowIcon(QIcon("icon.ico"));
        InfoBox.exec();
    }
}


void MainWindow::on_actionDelete_User_triggered()
{
    if(ui->stackedWidget->currentIndex() != 0)
    {
        Dialog_DU dDU;
        dDU.setUser(*User);
        dDU.setWindowTitle(QObject::tr("Delete User"));
        dDU.setWindowIcon(QIcon("icon.ico"));
        dDU.exec();
        QFile * temfile = new QFile;
        temfile->setFileName(*FilePath);
        if(!temfile->exists()){
            ui->stackedWidget->setCurrentIndex(0);
            ResetComboBox(2);
            ui->toolButton->hide();
            ui->label_6->setText("");
        }
        delete temfile;
    }else{
        QMessageBox InfoBox(QMessageBox::Information, QObject::tr("Information"), QObject::tr("Please Log In First"));
        InfoBox.setWindowIcon(QIcon("icon.ico"));
        InfoBox.exec();
    }
}


void MainWindow::on_actionChinese_Traditional_triggered()
{
    qApp->installTranslator(trsChinese);
    ui->retranslateUi(this);
    *language = 0;
    languagefile->changeLanguage(*language);
    if(ui->stackedWidget->currentIndex() != 0)
    {
        ui->label_6->setText(*User);
    }
}


void MainWindow::on_actionEnglish_triggered()
{
    qApp->installTranslator(trsEnglish);
    ui->retranslateUi(this);
    *language = 1;
    languagefile->changeLanguage(*language);
    if(ui->stackedWidget->currentIndex() != 0)
    {
        ui->label_6->setText(*User);
    }
}

