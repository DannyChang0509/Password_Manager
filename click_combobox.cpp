#include "click_combobox.h"

Click_ComboBox::Click_ComboBox(QWidget *parent):QComboBox(parent)
{

}

Click_ComboBox::~Click_ComboBox()
{

}

void Click_ComboBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }

    QComboBox::mousePressEvent(event);
}
