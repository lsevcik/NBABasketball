#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::constructArenasTab() {
    auto arenasTable = ui->arenas_tableView;
    auto seatingDisplay = ui->arenas_seating_lcdNumber;
    m_arenasModel.setQuery(
        "SELECT [Arena Name], [Team Name], [Stadium Capacity] "
        "FROM [Stadiums] ORDER BY [Stadium Capacity] ASC");
    arenasTable->setModel(&m_arenasModel);
    arenasTable->resizeColumnsToContents();
    QSqlQueryModel seatingModel;
    seatingModel.setQuery(
        "SELECT SUM([Stadium Capacity]) "
        "FROM [Stadiums]"
    );
    int seatingCapacity = seatingModel.record(0).value(0).toInt();
    seatingDisplay->display(seatingCapacity);
}
