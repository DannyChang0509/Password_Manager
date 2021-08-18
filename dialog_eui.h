#ifndef DIALOG_EUI_H
#define DIALOG_EUI_H

#include <QDialog>

namespace Ui {
class Dialog_EUI;
}

class Dialog_EUI : public QDialog
{
    Q_OBJECT
    QString * UserName = new QString;
public:
    explicit Dialog_EUI(QWidget *parent = nullptr);
    ~Dialog_EUI();
    void setUser(const QString & name);
private slots:
    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Dialog_EUI *ui;
};

#endif // DIALOG_EUI_H
