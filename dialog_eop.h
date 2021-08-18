#ifndef DIALOG_EOP_H
#define DIALOG_EOP_H

#include <QDialog>
#include "fileio.h"

namespace Ui {
class Dialog_EOP;
}

class Dialog_EOP : public QDialog
{
    Q_OBJECT
    FileIO *file = new FileIO;
    int *ItemNum = new int;
    QStringList * temstrl = new QStringList;
    QString *FilePath = new QString;
public:
    explicit Dialog_EOP(QWidget *parent = nullptr);
    ~Dialog_EOP();
    void setPath(const QString & path);
private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void ResetComboBox();

    void on_pushButton_clicked();

    void on_comboBox_activated(int index);

private:
    Ui::Dialog_EOP *ui;
};

#endif // DIALOG_EOP_H
