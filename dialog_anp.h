#ifndef DIALOG_ANP_H
#define DIALOG_ANP_H

#include <QDialog>

namespace Ui {
class Dialog_ANP;
}

class Dialog_ANP : public QDialog
{
    Q_OBJECT
    QString *FilePath = new QString;
public:
    explicit Dialog_ANP(QWidget *parent = nullptr);
    ~Dialog_ANP();
    void setPath(const QString & path);
private slots:
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::Dialog_ANP *ui;
};

#endif // DIALOG_ANP_H
