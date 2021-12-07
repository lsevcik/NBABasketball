#include <vector>

#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_plan_purchaseButton_clicked() {
    std::vector<QString> teams {
        "Los Angeles Lakers",
        "Los Angeles Clippers",
        "Golden State Warriors"
    };
    m_purchaseDialog->exec(teams);
}

void MainWindow::purchaseCallback(double total) {
    ui->plan_costLCD->display(total);
}
