#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::constructConferencesTab()
{
    auto colView = ui->conferences_columnView;
    auto sModel = new QStandardItemModel(this);
    auto root = sModel->invisibleRootItem();
    auto flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    auto conferencesModel = m_controller->getStadiumsDataQueryModel(
        "SELECT DISTINCT [Conference] FROM [Stadiums];");

    /* Add the "Any" item */
    auto conference = "Any";
    auto conferenceNode = new QStandardItem(conference);
    conferenceNode->setFlags(flags);
    root->appendRow(conferenceNode);
    auto division = "Any";
    auto divisionNode = new QStandardItem(division);
    divisionNode->setFlags(flags);
    conferenceNode->appendRow(divisionNode);
    auto teamsModel = m_controller->getStadiumsDataQueryModel(
        "SELECT [Team Name] FROM [Stadiums];");
    for (int i = 0; i < teamsModel->rowCount(); ++i) {
        auto teamName = teamsModel->record(i).value(0).toString();
        auto teamNameNode = new QStandardItem(teamName);
        teamNameNode->setFlags(flags);
        divisionNode->appendRow(teamNameNode);
    }

    for (int i = 0; i < conferencesModel->rowCount(); ++i) {
        auto conference = conferencesModel->record(i).value(0).toString();
        auto conferenceNode = new QStandardItem(conference);
        conferenceNode->setFlags(flags);
        root->appendRow(conferenceNode);
        auto divisionsModel = m_controller->getStadiumsDataQueryModel(
            "SELECT DISTINCT [Division] FROM [Stadiums] WHERE [Conference] = '"+ conference +"';");

        /* Add the "Any item" */
        auto division = "Any";
        auto divisionNode = new QStandardItem(division);
        divisionNode->setFlags(flags);
        conferenceNode->appendRow(divisionNode);
        auto teamsModel = m_controller->getStadiumsDataQueryModel(
            "SELECT [Team Name] FROM [Stadiums] WHERE "
            "[Conference] = '" + conference + "';");
        for (int i = 0; i < teamsModel->rowCount(); ++i) {
            auto teamName = teamsModel->record(i).value(0).toString();
            auto teamNameNode = new QStandardItem(teamName);
            teamNameNode->setFlags(flags);
            divisionNode->appendRow(teamNameNode);
        }

        for (int i = 0; i < divisionsModel->rowCount(); ++i) {
            auto division = divisionsModel->record(i).value(0).toString();
            auto divisionNode = new QStandardItem(division);
            divisionNode->setFlags(flags);
            conferenceNode->appendRow(divisionNode);
            auto teamsModel = m_controller->getStadiumsDataQueryModel(
                "SELECT [Team Name] FROM [Stadiums] WHERE "
                "[Conference] = '" + conference + "' AND "
                "[Division] = '" + division + "';");
            for (int i = 0; i < teamsModel->rowCount(); ++i) {
                auto teamName = teamsModel->record(i).value(0).toString();
                auto teamNameNode = new QStandardItem(teamName);
                teamNameNode->setFlags(flags);
                divisionNode->appendRow(teamNameNode);
            }
        }
    }

    colView->setModel(sModel);
}

void MainWindow::on_conferences_columnView_updatePreviewWidget(const QModelIndex &index) {
    auto teamName = index.data().toString();
    auto tableView = ui->conferences_tableView;
    auto sModel = new QStandardItemModel(this);
    auto root = sModel->invisibleRootItem();
    auto teamModel = m_controller->getStadiumsDataQueryModel(
        "SELECT * FROM [Stadiums] "
        "WHERE [Team Name] = '" + teamName + "';");
    auto headerColumn = QList<QStandardItem *>();
    auto valueColumn = QList<QStandardItem *>();

    for (int i = 0; i < teamModel->columnCount(); ++i) {
        auto fieldName = teamModel->record(0).fieldName(i);
        auto fieldValue = teamModel->record(0).value(i).toString();
        auto headerNode = new QStandardItem(fieldName);
        auto valueNode = new QStandardItem(fieldValue);
        headerColumn.append(headerNode);
        valueColumn.append(valueNode);
    }

    root->appendColumn(headerColumn);
    root->appendColumn(valueColumn);
    tableView->setModel(sModel);
    tableView->resizeColumnsToContents();
}