#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::constructSouvenirsTab() {
    auto teamsList = ui->souvenirs_team_listView;
    m_souvenirsTeamsModel.setQuery(
        "SELECT [Team Name] FROM [Stadiums] "
        "WHERE [Enabled]=1 ORDER BY [Team Name] ASC;");
    teamsList->setModel(&m_souvenirsTeamsModel);
    auto selectionModel = teamsList->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &MainWindow::on_souvenir_selectionChanged);
}

void MainWindow::on_souvenir_selectionChanged(const QItemSelection &current, const QItemSelection &) {
    auto teamName = current.indexes()[0].data().toString();
    updateSouvenirsList(teamName);
}

void MainWindow::updateSouvenirsList(QString teamName) {
    auto souvenirsList = ui->souvenirs_souvenir_listView;
    m_souvenirsModel.clear();
    auto root = m_souvenirsModel.invisibleRootItem();
    QSqlQueryModel souvenirsModel;
    souvenirsModel.setQuery(
        "SELECT [Souvenir], [Cost] FROM [Souvenirs] "
        "WHERE [Stadium]=(SELECT [Arena Name] FROM [Stadiums] "
        "   WHERE [Team Name] = '" + teamName + "' LIMIT 1);");
    auto souvneirsColumn = QList<QStandardItem *>();
    for (int i = 0; i < souvenirsModel.rowCount(); ++i) {
        auto souvenirName = souvenirsModel.record(i).value(0).toString();
        auto souvenirPrice = souvenirsModel.record(i).value(1).toString();
        auto souvenirItem = new QStandardItem(souvenirName + " - $" + souvenirPrice);
        souvenirItem->setIcon(QIcon(":/"+souvenirName+".png"));
        // TODO: Set a different icon if it is not found
        souvenirItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        souvenirItem->setWhatsThis("$"+souvenirPrice);
        souvneirsColumn.append(souvenirItem);
    }
    root->insertColumn(0, souvneirsColumn);
    souvenirsList->setModel(&m_souvenirsModel);
}
