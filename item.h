#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item
{
    QString *ItemName = new QString;
    QString *Account = new QString;
    QString *Password = new QString;
public:
    Item();
    ~Item();
    void SetItemName(QString & str);
    void SetAccount(QString & str);
    void SetPassword(QString & str);
    QString GetItemName();
    QString GetAccount();
    QString GetPassword();
};

#endif // ITEM_H
