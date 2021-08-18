#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTranslator>

#include "fileio.h"
#include "click_combobox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT;
    FileIO *file = new FileIO;
    FileIO *userfile = new FileIO;
    FileIO *languagefile = new FileIO;
    QStringList * temstrl = new QStringList;
    int *ItemNum = new int;
    QString *FilePath = new QString;
    QString *User = new QString;
    QTranslator * trsChinese;
    QTranslator * trsEnglish;
    int *language = new int;    //0:Traditional Chinese(default)    1:English
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ResetComboBox(int num);
private slots:
    void on_actionAbout_this_APP_triggered();

    void on_pushButton_clicked();

    void on_actionset_verification_code_triggered();

    void on_pushButton_2_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_actionInstruction_triggered();

    void on_pushButton_3_clicked();

    void on_actionAdd_new_Password_triggered();

    void ResetFileComboBox();

    void ResetUserComboBox();

    void on_actionDelet_password_triggered();

    void on_actionEdit_password_triggered();

    void on_toolButton_clicked();

    void on_checkBox_2_stateChanged(int arg1);

    void on_pushButton_4_clicked();

    void on_actionAdd_New_User_triggered();

    void on_actionDelete_User_triggered();

    void on_actionChinese_Traditional_triggered();

    void on_actionEnglish_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
