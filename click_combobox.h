#ifndef CLICK_COMBOBOX_H
#define CLICK_COMBOBOX_H

#include <QComboBox>
#include <QMouseEvent>
class Click_ComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit Click_ComboBox(QWidget *parent = 0);
    ~Click_ComboBox();
protected:
    virtual void mousePressEvent(QMouseEvent *e);

signals:
    void clicked();
};

#endif
