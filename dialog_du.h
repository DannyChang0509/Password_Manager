#ifndef DIALOG_DU_H
#define DIALOG_DU_H

#include <QDialog>

namespace Ui {
class Dialog_DU;
}

class Dialog_DU : public QDialog
{
    Q_OBJECT
    QString * UserName = new QString;
public:
    explicit Dialog_DU(QWidget *parent = nullptr);
    ~Dialog_DU();
    void setUser(const QString & name);
private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::Dialog_DU *ui;
};

#endif // DIALOG_DU_H
