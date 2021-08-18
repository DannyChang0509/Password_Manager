#ifndef DIALOG_DOP_H
#define DIALOG_DOP_H

#include <QDialog>
#include "fileio.h"

namespace Ui {
class Dialog_DOP;
}

class Dialog_DOP : public QDialog
{
    Q_OBJECT
    FileIO *file = new FileIO;
    int *ItemNum = new int;
    QStringList * temstrl = new QStringList;
    QString *FilePath = new QString;
public:
    explicit Dialog_DOP(QWidget *parent = nullptr);
    ~Dialog_DOP();
    void setPath(const QString & path);
private slots:
    void on_checkBox_stateChanged(int arg1);

    void ResetComboBox();

    void on_pushButton_clicked();

private:
    Ui::Dialog_DOP *ui;
};

#endif // DIALOG_DOP_H
