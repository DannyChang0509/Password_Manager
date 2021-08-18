#ifndef DIALOG_SU_H
#define DIALOG_SU_H

#include <QDialog>

#include "fileio.h"

namespace Ui {
class Dialog_SU;
}

class Dialog_SU : public QDialog
{
    Q_OBJECT
    FileIO * userfile = new FileIO;
public:
    explicit Dialog_SU(QWidget *parent = nullptr);
    ~Dialog_SU();

private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::Dialog_SU *ui;
};

#endif // DIALOG_SU_H
