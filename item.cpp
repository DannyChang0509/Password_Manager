#include "item.h"

Item::Item()
{
    *ItemName = "";
    *Account = "";
    *Password = "";
}

Item::~Item()
{
    delete ItemName;
    delete Account;
    delete Password;
}

void Item::SetItemName(QString & str)
{
    *ItemName = str;
}

void Item::SetAccount(QString & str)
{
    *Account = str;
}

void Item::SetPassword(QString & str)
{
    *Password = str;
}

QString Item::GetItemName()
{
    return *ItemName;
}

QString Item::GetAccount()
{
    return *Account;
}

QString Item::GetPassword()
{
    return *Password;
}
