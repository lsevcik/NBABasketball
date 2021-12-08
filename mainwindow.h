#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStandardItem>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QtDebug>
#include <QMessageBox>
#include "loginDialog.h"
#include "importDialog.h"
#include "purchaseDialog.h"
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
    void purchaseCallback(double);

public slots:

private slots:
    void on_editStadiumData_comboBox_currentTextChanged(const QString &arg1);
    void on_editStadiumData_resetButton_clicked();
    void on_editStadiumData_submitButton_clicked();
    void on_editSouvenir_submitButton_clicked();
    void on_editSouvenir_deleteButton_clicked();
    void on_addSouvenir_pushButton_clicked();
    void on_actionLogin_triggered();
    void on_actionQuit_triggered();
    void on_actionRefresh_triggered();
    void on_actionAbout_triggered();
    void on_conferences_columnView_updatePreviewWidget(const QModelIndex &);
    void on_admin_importButton_clicked();
    void on_editSouvenir_comboBox_currentTextChanged(const QString &arg1);
    void on_plan_purchaseButton_clicked();
    void on_plan_searchComboBox_currentTextChanged(const QString &);
    void on_plan_startingComboBox_currentTextChanged(const QString &);
    void on_plan_addTeamButton_clicked();
    void on_plan_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    loginDialog *m_loginDialog;
    importDialog *m_importDialog;
    purchaseDialog *m_purchaseDialog;
    Controller *m_controller;
    QSqlQueryModel m_arenasModel;
    QSortFilterProxyModel m_arenasSortedModel;
    QStandardItemModel m_souvenirsModel;
    QSqlQueryModel m_coachesModel;
    QSqlQueryModel m_adminConferenceModel;
    QSqlQueryModel m_adminStadiumsModel;
    QSqlQueryModel m_adminSouvenirsModel;
    QSqlQueryModel m_souvenirsTeamsModel;
    QSqlQueryModel m_startingTeamsModel;
    QSqlQueryModel m_availableTeamsModel;
    QStringListModel m_currentTeamsModel;
    QStandardItemModel m_conferencesStandardModel;
    QStandardItemModel m_conferencesPreviewModel;
    void setupShortcuts();
    void refreshDataViews();
    void constructConferencesTab();
    void constructArenasTab();
    void constructSouvenirsTab();
    void constructPlansTab();
    void setupAdminModels();
    void on_souvenir_selectionChanged(const QItemSelection &, const QItemSelection &);
    void updateSouvenirsLogo(QString);
    void updateSouvenirsList(QString);
    void resetPlan(const QString&, const QString&);
    double dijkstra(const QString &, const QString &);
    void orderedDijkstra(QStringList);
    void recursiveDijkstra(QStringList);
    void startDFS(int index);
    void startBFS(int index);
    void showAllTeamsAsCurrent();
};

#endif // MAINWINDOW_H
