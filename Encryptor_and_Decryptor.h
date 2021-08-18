#ifndef ENCRYPTOR_AND_DECRYPTOR_H
#define ENCRYPTOR_AND_DECRYPTOR_H

#include <QString>
#include <QChar>

QString Encryptor(QString & str);
QString Decryptor(QString & str);

QString Encryptor(QString & str)
{
    QString *temstr = new QString("");
    int length = str.size();
    for(int i = 0; i < length; i ++)
    {
        if(i%2 == 0)
        {
            *temstr += QChar(str.at((int)(i/2)).toLatin1() + 3);
        }else
        {
            *temstr += QChar(str.at(length-(int)((i+1)/2)).toLatin1() + 3);
        }
    }
    str.replace(0, length, *temstr);
    delete temstr;
    return str;
}

QString Decryptor(QString & str)
{
    QString *temstr = new QString("");
    int length = str.size();
    int middle;
    if(length%2 == 0)
    {
        middle = (int)(length/2);
    }else
    {
        middle = (int)((length+1)/2);
    }
    for(int i = 0; i < middle; i ++)
    {
        *temstr += QChar(str.at(i*2).toLatin1() - 3);
    }
    for(int j = middle; j < length; j ++)
    {
        *temstr += QChar(str.at(length*2 - j*2 - 1).toLatin1() - 3);
    }
    str.replace(0, length, *temstr);
    delete temstr;
    return str;
}

#endif // ENCRYPTOR_AND_DECRYPTOR_H
