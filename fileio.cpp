#include "fileio.h"
#include "Encryptor_and_Decryptor.h"

#include <QTextStream>

FileIO::FileIO()
{
    *FilePath = "";
}

FileIO::~FileIO()
{
    delete FilePath;
    delete file;
}

void FileIO::setPath(const QString &path)
{
    *FilePath = path;
}

QStringList FileIO::ReadFile(){
    file->setFileName(*FilePath);
    file->open(QIODevice::Text | QIODevice::ReadWrite);
    QStringList str;
    while(!file->atEnd())
    {
        QByteArray array = file->readLine();
        QString * temstr = new QString;
        *temstr = QString(array).trimmed();
        str.append(*temstr);
        delete temstr;
    }
    if(str.size() == 0)
    {
        QTextStream out(file);
        QString InitialPassword = "0000";
        Encryptor(InitialPassword);
        out << InitialPassword << "\n\n";
    }
    file->close();
    return str;
}

QString FileIO::ReadVerificationCode(const QStringList &strlist)
{
    QString * temstr = new QString(strlist.at(0));
    Decryptor(*temstr);
    return *temstr;
}

QString FileIO::ReadItemName(const QStringList &strlist, int index)
{
    return strlist.at(index).split("/").at(0);
}

QString FileIO::ReadAccount(const QStringList &strlist, int index)
{
    QString * temstr = new QString(strlist.at(index).split("/").at(1));
    Decryptor(*temstr);
    return *temstr;
}

QString FileIO::ReadPassword(const QStringList &strlist, int index)
{
    QString * temstr = new QString(strlist.at(index).split("/").at(2));
    Decryptor(*temstr);
    return *temstr;
}

void FileIO::ChangeVerificationCode(const QStringList &strlist, const QString & NewCode)
{
    file->setFileName(*FilePath);
    file->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(file);
    QString * temstr = new QString;
    *temstr = NewCode;
    Encryptor(*temstr);
    out << *temstr << "\n\n";
    delete temstr;
    for(int i = 2; i < strlist.size(); i ++)
    {
        QString * temstr2 = new QString;
        *temstr2 = strlist.at(i);
        Encryptor(*temstr2);
        out << *temstr2 << "\n";
        delete temstr2;
    }
    file->close();
}

void FileIO::ChangeUserName(const QStringList &strlist, const QString & OldName, QString & NewName)
{
    file->setFileName(*FilePath);
    file->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(file);
    QString * temstr = new QString;
    *temstr = strlist.at(0);
    out << *temstr << "\n\n";
    delete temstr;
    for(int i = 2; i < strlist.size(); i ++)
    {
        if(strlist.at(i) == OldName)
        {
            out << NewName << "\n";
        }else
        {
            QString * temstr3 = new QString;
            *temstr3 = strlist.at(i);
            out << *temstr3 << "\n";
            delete temstr3;
        }
    }
    file->close();
}

void FileIO::AddItem(const QStringList &strlist, Item & item){
    file->setFileName(*FilePath);
    file->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(file);
    QString * temstr = new QString;
    *temstr = strlist.at(0);
    out << *temstr << "\n\n";
    delete temstr;
    for(int i = 2; i < strlist.size(); i ++)
    {
        QString * temstr2 = new QString;
        *temstr2 = strlist.at(i);
        out << *temstr2 << "\n";
        delete temstr2;
    }
    QString * temstr3 = new QString;
    *temstr3 = item.GetItemName();
    *temstr3 += "/";
    QString * temstr4 = new QString(item.GetAccount());
    Encryptor(*temstr4);
    *temstr3 += *temstr4;
    *temstr3 += "/";
    *temstr4 = item.GetPassword();
    Encryptor(*temstr4);
    *temstr3 += *temstr4;
    out << *temstr3;
    delete temstr3;
    delete temstr4;
    file->close();
}

void FileIO::EditItem(const QStringList &strlist, int index, Item & item){
    file->setFileName(*FilePath);
    file->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(file);
    QString * temstr = new QString;
    *temstr = strlist.at(0);
    out << *temstr << "\n\n";
    delete temstr;
    for(int i = 2; i < strlist.size(); i ++)
    {
        if(i == index+2)
        {
            QString * temstr2 = new QString;
            *temstr2 = item.GetItemName();
            *temstr2 += "/";
            QString * temstr3 = new QString(item.GetAccount());
            Encryptor(*temstr3);
            *temstr2 += *temstr3;
            *temstr2 += "/";
            *temstr3 = item.GetPassword();
            Encryptor(*temstr3);
            *temstr2 += *temstr3;
            out << *temstr2 << "\n";
            delete temstr2;
            delete temstr3;
        }else
        {
            QString * temstr3 = new QString;
            *temstr3 = strlist.at(i);
            out << *temstr3 << "\n";
            delete temstr3;
        }
    }
    file->close();
}

void FileIO::DeleteItem(const QStringList &strlist, int index){
    file->setFileName(*FilePath);
    file->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(file);
    QString * temstr = new QString;
    *temstr = strlist.at(0);
    out << *temstr << "\n\n";
    delete temstr;
    for(int i = 2; i < strlist.size(); i ++)
    {
        if(i != index+2)
        {
            QString * temstr2 = new QString;
            *temstr2 = strlist.at(i);
            out << *temstr2 << "\n";
            delete temstr2;
        }
    }
    file->close();
}

void FileIO::AddUser(const QStringList &strlist, QString &str)
{
    file->setFileName(*FilePath);
    file->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(file);
    QString * temstr = new QString;
    *temstr = strlist.at(0);
    out << *temstr << "\n\n";
    delete temstr;
    for(int i = 2; i < strlist.size(); i ++)
    {
        QString * temstr2 = new QString;
        *temstr2 = strlist.at(i);
        out << *temstr2 << "\n";
        delete temstr2;
    }
    out << str;
    file->close();
}

void FileIO::DeleteUser(const QStringList &strlist, QString &str)
{
    file->setFileName(*FilePath);
    file->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(file);
    QString * temstr = new QString;
    *temstr = strlist.at(0);
    out << *temstr << "\n\n";
    delete temstr;
    for(int i = 2; i < strlist.size(); i ++)
    {
        if(strlist.at(i) != str)
        {
            QString * temstr2 = new QString;
            *temstr2 = strlist.at(i);
            out << *temstr2 << "\n";
            delete temstr2;
        }
    }
    file->close();
}

void FileIO::Rename(const QString & NewfileName)
{
    file->setFileName(*FilePath);
    file->rename(NewfileName);
}

void FileIO::Remove()
{
    file->setFileName(*FilePath);
    file->remove(*FilePath);
}

int FileIO::getLanguage()
{
    file->setFileName("system/language/current_language.dat");
    file->open(QIODevice::Text | QIODevice::ReadWrite);
    int tem = file->readLine().toInt();
    file->close();
    return tem;
}

void FileIO::changeLanguage(int &language)
{
    file->setFileName("system/language/current_language.dat");
    file->open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(file);
    out << QString::number(language) << "\n\n0:Traditional Chinese\n1:English";
    file->close();
}
