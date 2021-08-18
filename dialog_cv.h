#ifndef DIALOG_CV_H
#define DIALOG_CV_H

#include <QDialog>

#include "fileio.h"

namespace Ui {
class Dialog_CV;
}

class Dialog_CV : public QDialog
{
    Q_OBJECT
    FileIO *file = new FileIO;
    QString *FilePath = new QString;
public:
    explicit Dialog_CV(QWidget *parent = nullptr);
    ~Dialog_CV();
    void setPath(const QString & path);
private slots:
    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::Dialog_CV *ui;
};

#endif // DIALOG_CV_H
