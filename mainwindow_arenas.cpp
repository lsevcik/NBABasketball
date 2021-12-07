#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::constructArenasTab() {
    auto arenasTable = ui->arenas_tableView;
    auto seatingDisplay = ui->arenas_seating_lcdNumber;
    m_arenasModel.setQuery(
        "SELECT [Arena Name], [Team Name], [Stadium Capacity], [Joined League],"
        " [Coach] FROM [Stadiums] WHERE [Enabled]=1 ORDER BY [Arena Name] ASC");
    m_arenasSortedModel.setSourceModel(&m_arenasModel);
    arenasTable->setModel(&m_arenasSortedModel);

    arenasTable->resizeColumnsToContents();
    QSqlQueryModel seatingModel;
    seatingModel.setQuery(
        "SELECT SUM([Stadium Capacity]) "
        "FROM [Stadiums] WHERE [Enabled]=1"
    );
    int seatingCapacity = seatingModel.record(0).value(0).toInt();
    seatingDisplay->display(seatingCapacity);
}
