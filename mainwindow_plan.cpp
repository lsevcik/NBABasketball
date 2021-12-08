#include <vector>
#include <set>

#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::constructPlansTab() {
    m_startingTeamsModel.setQuery(
        "SELECT [Team Name] FROM [Stadiums] WHERE [Enabled]=1");
    ui->plan_startingComboBox->setModel(&m_startingTeamsModel);
    ui->plan_currentListView->setModel(&m_currentTeamsModel);
    ui->plan_availableListView->setModel(&m_availableTeamsModel);
}

void MainWindow::on_plan_searchComboBox_currentTextChanged(const QString& searchType) {
    resetPlan(searchType, ui->plan_startingComboBox->currentText());
}

void MainWindow::on_plan_startingComboBox_currentTextChanged(const QString &startingTeam) {
    resetPlan(ui->plan_searchComboBox->currentText(), startingTeam);
}

void MainWindow::on_plan_addTeamButton_clicked() {
    auto selectedIndex = ui->plan_availableListView->currentIndex();
    QString newTeam = selectedIndex.data(Qt::DisplayRole).toString();
    QStringList currentTeams = m_currentTeamsModel.stringList();
    if (currentTeams.contains(newTeam))
        return;
    currentTeams << newTeam;
    if (ui->plan_searchComboBox->currentText() == "Dijkstra Ordered") {
        orderedDijkstra(currentTeams);
    } else if (ui->plan_searchComboBox->currentText() == "Dijkstra Efficient") {
        recursiveDijkstra(currentTeams);
    }
    m_currentTeamsModel.setStringList(currentTeams);
}

void MainWindow::on_plan_resetButton_clicked() {
    resetPlan(ui->plan_searchComboBox->currentText(),
              ui->plan_startingComboBox->currentText());
}

void MainWindow::on_plan_purchaseButton_clicked() {
    m_purchaseDialog->exec(m_currentTeamsModel.stringList() << ui->plan_startingComboBox->currentText());
}

void MainWindow::purchaseCallback(double total) {
    ui->plan_costLCD->display(total);
}

void MainWindow::resetPlan(const QString &searchType, const QString &startingTeam) {
    auto availList = ui->plan_availableListView;
    ui->plan_costLCD->display(0);
    ui->plan_distanceLCD->display(0);
    m_currentTeamsModel.setStringList(QStringList());
    m_availableTeamsModel.clear();

    if (searchType.contains("Dijkstra")) {
        //populate from the starting city
        m_availableTeamsModel.setQuery(
            "SELECT [Team Name] FROM [Stadiums] WHERE [Team Name] != '" +
            startingTeam + "' AND [Enabled]=1");
    }
}

void MainWindow::orderedDijkstra(QStringList teams) {
    auto startingTeam = ui->plan_startingComboBox->currentText();
    double total = 0.0;
    for (auto team : teams) {
        total += dijkstra(startingTeam, team);
        startingTeam = team;
    }
    ui->plan_distanceLCD->display(total);
}

void MainWindow::recursiveDijkstra(QStringList teams) {
    auto startingTeam = ui->plan_startingComboBox->currentText();
    double total = 0.0;
    while (!teams.empty()) {
        double smallestDist = std::numeric_limits<double>::infinity();
        QString smallestTeam;
        for (auto team : teams) {
            double distance = dijkstra(startingTeam, team);
            if (distance < smallestDist) {
                smallestDist = distance;
                smallestTeam = team;
            }
        }
        teams.removeAt(teams.indexOf(smallestTeam));
        startingTeam = smallestTeam;
        total += smallestDist;
    }
    ui->plan_distanceLCD->display(total);
}

double MainWindow::dijkstra(const QString &src, const QString &dest){
    std::map<QString,std::list<std::pair<QString,double>>> l;
    QSqlQueryModel availTeams;
    availTeams.setQuery(
        "SELECT [Team Name] FROM [Stadiums] WHERE [Enabled]=1");
    for (int i = 0; i < availTeams.rowCount(); ++i) {
        QSqlQueryModel adjMat;
        QString team = availTeams.record(i).value(0).toString();
        adjMat.setQuery(
            "SELECT e.DestinationTeam, Distance FROM Stadiums n "
            "LEFT JOIN Distances e ON [Team Name] = StartTeam "
            "WHERE [Team Name] = '" + team + "';");
        for (int i = 0; i < adjMat.rowCount(); ++i) {
            QString dest = adjMat.record(i).value(0).toString();
            double dist = adjMat.record(i).value(1).toDouble();
            l[team].push_back(std::make_pair(dest, dist));
        }
    }
    std::map<QString,double> dist;
    for(auto i=l.begin();i!=l.end();i++){
        dist[i->first]=std::numeric_limits<double>::infinity();
    }
    dist[src]=0;
    std::set<std::pair<double,QString>>s;
    s.insert(std::make_pair(0.0,src));
    while(!s.empty()){
        auto p=*(s.begin());
        QString node=p.second;
        double nodeDist=p.first;
        s.erase(s.begin());
        for(auto i=l[p.second].begin();i!=l[p.second].end();i++){
            if(nodeDist+i->second<dist[i->first]){
                QString dest=i->first;
                auto f= s.find(std::make_pair(dist[dest],dest));
                if(f!=s.end()){
                    s.erase(f);
                }
                dist[dest]=nodeDist+i->second;
                s.insert(std::make_pair(dist[dest],dest));
            }
        }
    }
    auto path = dist.find(dest);
    if (path == dist.end())
        return std::numeric_limits<double>::infinity();
    return path->second;
}
