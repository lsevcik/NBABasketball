#include "mainwindow.h"
#include "loginDialog.h"
#include "ui_loginDialog.h"

loginDialog::loginDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::loginDialog)
{
    ui->setupUi(this);
}

void loginDialog::on_buttonBox_accepted() {
    static_cast<MainWindow *>(this->parentWidget())->loginCallback(true);
}

void loginDialog::on_buttonBox_rejected() {
    static_cast<MainWindow *>(this->parentWidget())->loginCallback(false);
}

loginDialog::~loginDialog()
{
    delete ui;
}
