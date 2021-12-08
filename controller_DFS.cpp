#include "controller.h"

void Controller::DFS(int startTeam) {

    visited[startTeam] = true;
    completedDFS.push_front(listOfTeams[startTeam]);

    for (int i = 0; i < adjList[startTeam].size(); i++) {

        int destinationTeam = adjList[startTeam][i].destinationTeam;

        if (!visited[destinationTeam]) {

            addDistance(adjList[startTeam][i].distance);
            DFS(destinationTeam);
        }
    }
}

void Controller::addDistance(float distance) {

    DFS_Distance += distance;
}

void Controller::populateListOfTeams() {

    DFS_Distance = 0;
    visited.clear();
    adjList.clear();
    completedDFS.clear();
    listOfTeams.clear();

    QSqlQueryModel model;
    model.setQuery("SELECT DISTINCT [StartTeam] FROM [Distances] "
                   "ORDER BY [StartTeam], [Distance] ASC");

    for (int i = 0; i < model.rowCount(); i++) {

//        qDebug() << model.record(i).value("StartTeam").toString();
        listOfTeams.append(model.record(i).value("StartTeam").toString());
        adjList[i].append(QVector<Edge>());
    }

    model.clear();
    model.setQuery("SELECT * FROM [Distances] "
                   "ORDER BY [StartTeam], [Distance] ASC");

    for (int i = 0; i < adjList.size(); i++) {

        for (int j = 0; j < model.rowCount(); j++) {

            QString startTeam =
                    model.record(j).value("StartTeam").toString();
            QString destinationTeam =
                    model.record(j).value("DestinationTeam").toString();

            if (startTeam == listOfTeams.at(i)) {

                int destIndex = listOfTeams.lastIndexOf(destinationTeam);
                float distance = model.record(j).value("Distance").toFloat();
                Edge *e = new Edge();
                e->destinationTeam = destIndex;
                e->distance = distance;
                adjList[i].append(*e);
            }
        }
    }

//    for (int i = 0; i < adjList.size(); i++) {

//        qDebug() << i << ": ";

//        for (int j = 0; j < adjList[i].size(); j++) {

//            qDebug() << adjList[i][j].destinationTeam << " -- " << adjList[i][j].distance;

//        }
//    }
}
