#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItem>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QtDebug>
#include <QMessageBox>
#include "loginDialog.h"
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loginCallback(bool);

public slots:

private slots:
    void on_editStadiumData_comboBox_currentTextChanged(const QString &arg1);
    void on_editStadiumData_resetButton_clicked();
    void on_editStadiumData_submitButton_clicked();
    void on_actionLogin_triggered();
    void on_actionQuit_triggered();
    void on_actionRefresh_triggered();
    void on_actionAbout_triggered();
    void on_conferences_columnView_updatePreviewWidget(const QModelIndex &);

    void on_editSouvenir_comboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    loginDialog *m_loginDialog;
    Controller *m_controller;
    QSqlQueryModel m_arenasModel;
    QStandardItemModel m_souvenirsModel;
    void setupShortcuts();
    void refreshDataViews();
    void constructConferencesTab();
    void constructCoachesTab();
    void constructArenasTab();
    void constructSouvenirsTab();
    void setupAdminModels();
    void on_souvenir_selectionChanged(const QItemSelection &, const QItemSelection &);
    void updateSouvenirsLogo(QString);
    void updateSouvenirsList(QString);
};

#endif // MAINWINDOW_H
