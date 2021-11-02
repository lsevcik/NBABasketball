#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Controller *controller, QWidget *parent = nullptr);
    ~MainWindow();
    void test();

private slots:
    void on_editStadiumData_comboBox_currentTextChanged(const QString &arg1);

    void on_editDataReset_pushButton_clicked();

    void on_editData_pushButton_clicked();

    void on_showSingleStadium_radioButton_clicked();

    void showSingleStadium();

private:

    Ui::MainWindow *ui;
    Controller *m_controller;
};
#endif // MAINWINDOW_H
