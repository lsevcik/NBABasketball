#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::constructCoachesTab() {
    auto coachesTable = ui->coaches_tableView;
    m_coachesModel.setQuery(
        "SELECT [Coach], [Team Name] "
        "FROM [Stadiums] ORDER BY [Team Name] ASC");
    coachesTable->setModel(&m_coachesModel);
    coachesTable->resizeColumnsToContents();
}
