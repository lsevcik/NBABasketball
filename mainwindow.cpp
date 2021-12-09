#include "loginDialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,  m_loginDialog(new loginDialog(this))
    ,  m_importDialog(new importDialog(this))
    ,  m_purchaseDialog(new purchaseDialog(this))
    ,  m_controller(new Controller)
    , m_conferencesStandardModel(this)
    , m_conferencesPreviewModel(this)
{
    ui->setupUi(this);

    auto adminTabIndex = ui->tabWidget->indexOf(ui->adminTab);
    ui->tabWidget->setTabVisible(adminTabIndex, false);

    setupShortcuts();
    refreshDataViews();
}

MainWindow::~MainWindow()
{
    delete m_controller;
    delete m_loginDialog;
    delete ui;
}

void MainWindow::setupShortcuts() {
    auto refreshShortcuts = QList<QKeySequence>();
    refreshShortcuts.append(QKeySequence::Refresh);
    refreshShortcuts.append(QKeySequence("Ctrl+R"));
    ui->actionRefresh->setShortcuts(refreshShortcuts);
}

void MainWindow::refreshDataViews() {
    setupAdminModels();
    constructConferencesTab();
    constructArenasTab();
    constructSouvenirsTab();
    constructPlansTab();
}

void MainWindow::loginCallback(bool succ)
{
    auto tabWidget = ui->tabWidget;
    auto adminTabIndex = tabWidget->indexOf(ui->adminTab);
    tabWidget->setTabVisible(adminTabIndex, succ);
    if (succ)
        tabWidget->setCurrentIndex(adminTabIndex);
}

void MainWindow::on_actionLogin_triggered()
{
    m_loginDialog->exec();
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionRefresh_triggered() {
    refreshDataViews();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::aboutQt(this, "About");
}


