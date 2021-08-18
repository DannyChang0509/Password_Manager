#ifndef FILEIO_H
#define FILEIO_H

#include <QString>
#include <QFile>

#include "item.h"

class FileIO
{
    QString *FilePath = new QString;
    QFile *file = new QFile;

public:
    FileIO();
    ~FileIO();
    void setPath(const QString & path);
    QStringList ReadFile();
    QString ReadVerificationCode(const QStringList & strlist);
    QString ReadItemName(const QStringList & strlist, int index);
    QString ReadAccount(const QStringList & strlist, int index);
    QString ReadPassword(const QStringList & strlist, int index);

    void ChangeVerificationCode(const QStringList &strlist, const QString & NewCode);
    void ChangeUserName(const QStringList &strlist, const QString & OldName, QString & NewName);
    void AddItem(const QStringList &strlist, Item & item);
    void EditItem(const QStringList &strlist, int index, Item & item);
    void DeleteItem(const QStringList &strlist, int index);
    void AddUser(const QStringList &strlist, QString &str);
    void DeleteUser(const QStringList &strlist, QString &str);
    void Rename(const QString & NewfileName);
    void Remove();
    int getLanguage();
    void changeLanguage(int & language);
};

#endif // FILEIO_H
