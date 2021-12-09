#include "controller.h"

void Controller::populateMSTAdjList() {

    QSqlQueryModel model;

    model.setQuery("SELECT DISTINCT [Team Name] FROM [Stadiums] "
                   "WHERE [Enabled]=1 "
                   "ORDER BY [Team Name] ASC");

    for (int i = 0; i < model.rowCount(); i++) {

        MSTListOfTeams.append(model.record(i).value("Team Name").toString());
    }

    model.setQuery("SELECT [Distance], [StartTeam], [DestinationTeam] "
                   "FROM Distances d "
                   "INNER JOIN Stadiums s1 ON s1.[Team Name] = d.StartTeam "
                   "INNER JOIN Stadiums s2 ON s2.[Team Name] = d.DestinationTeam "
                   "WHERE (s1.Enabled + s2.Enabled) = 2 "
                   "ORDER BY [Distance] ASC;");

    for (int i = 0; i < model.rowCount(); i++) {

//        edgeList[i] = model.record(i)
    }

}

int Controller::findIndex(QString teamName) {

    for (int i = 0; i < MSTListOfTeams.size(); i++) {

        if (teamName == MSTListOfTeams[i])
            return i;
    }

    return -1;
}

int Controller::Graph::KruskalMST() {

    float mst_wt = 0;

    // function to sort edges?

    DisjointSets ds(V);
    QString team, tempTeam;
}
