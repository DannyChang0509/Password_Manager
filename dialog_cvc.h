#ifndef DIALOG_CVC_H
#define DIALOG_CVC_H

#include <QDialog>

namespace Ui {
class Dialog_CVC;
}

class Dialog_CVC : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_CVC(QWidget *parent = nullptr);
    ~Dialog_CVC();

private:
    Ui::Dialog_CVC *ui;
};

#endif // DIALOG_CVC_H
