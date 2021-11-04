#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::constructArenasTab() {
    auto arenasTable = ui->arenas_tableView;
    auto seatingDisplay = ui->arenas_seating_lcdNumber;
    auto arenasModel = m_controller->getStadiumsDataQueryModel(
        "SELECT [Arena Name], [Team Name], [Stadium Capacity] "
        "FROM [Stadiums] ORDER BY [Stadium Capacity] ASC");
    arenasTable->setModel(arenasModel);
    arenasTable->resizeColumnsToContents();
    auto seatingModel = m_controller->getStadiumsDataQueryModel(
        "SELECT SUM([Stadium Capacity]) "
        "FROM [Stadiums]");
    auto seatingCapacity = seatingModel->record(0).value(0).toInt();
    seatingDisplay->display(seatingCapacity);
}
