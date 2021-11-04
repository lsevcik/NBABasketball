#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::constructCoachesTab() {
    auto coachesTable = ui->coaches_tableView;
    auto model = m_controller->getStadiumsDataQueryModel(
        "SELECT [Coach], [Team Name] "
        "FROM [Stadiums] ORDER BY [Team Name] ASC");
    coachesTable->setModel(model);
    coachesTable->resizeColumnsToContents();
}
