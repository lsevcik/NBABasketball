#include "controller.h"

void Controller::DFS(int startTeam) {

    visited[startTeam] = true;
    completedDFSBFS.push_back(listOfTeams[startTeam]);

    for (int i = 0; i < adjList[startTeam].size(); i++) {

        int destinationTeam = adjList[startTeam][i].destinationTeam;

        if (!visited[destinationTeam]) {

            addDistance(adjList[startTeam][i].distance);
            DFS(destinationTeam);
        }
    }
}

void Controller::BFS(int startTeam) {

    QList<int> queue;

    visited[startTeam] = true;
    queue.push_back(startTeam);
    qDebug() << "pushing back: " << listOfTeams[startTeam] << "....";
    completedDFSBFS.push_back(listOfTeams[startTeam]);

    while (!queue.empty()) {

        startTeam = queue.front();
        queue.pop_front();
        qDebug() << "popping front: " <<  listOfTeams[startTeam] << "....";


        for (int i = 0; i < adjList[startTeam].size(); i++) {

            if (!visited[adjList[startTeam][i].destinationTeam]) {

                qDebug() << "adj: " << listOfTeams[adjList[startTeam][i].destinationTeam]
                         << adjList[startTeam][i].distance;
            }
        }

        for (int i = 0; i < adjList[startTeam].size(); i++) {

            if (!visited[adjList[startTeam][i].destinationTeam]) {

                visited[adjList[startTeam][i].destinationTeam] = true;
                queue.push_back(adjList[startTeam][i].destinationTeam);
                completedDFSBFS.push_back(listOfTeams[adjList[startTeam][i].destinationTeam]);
                addDistance(adjList[startTeam][i].distance);
                qDebug() << "pushing back: " << listOfTeams[adjList[startTeam][i].destinationTeam] << "....";

            }
        }
    }
}

void Controller::addDistance(float distance) {

    DFSBFS_Distance += distance;
}

void Controller::populateListOfTeams() {

    resetListOfTeams();
    QSqlQueryModel model;
    model.setQuery("SELECT DISTINCT [Team Name] FROM [Stadiums] "
                   "WHERE [Enabled]=1 "
                   "ORDER BY [Team Name] ASC");

    for (int i = 0; i < model.rowCount(); i++) {

        qDebug() << model.record(i).value("Team Name").toString();
        listOfTeams.append(model.record(i).value("Team Name").toString());
        adjList[i].append(QVector<Edge>());
    }

    qDebug() << listOfTeams.size();

    model.clear();
    model.setQuery("SELECT [StartTeam], [DestinationTeam], [Distance] "
                   "FROM Distances d "
                   "INNER JOIN Stadiums s1 ON s1.[Team Name] = d.StartTeam "
                   "INNER JOIN Stadiums s2 ON s2.[Team Name] = d.DestinationTeam "
                   "WHERE (s1.Enabled + s2.Enabled) = 2 "
                   "ORDER BY [StartTeam], [Distance] ASC;");
//    model.setQuery("SELECT [StartTeam], [DestinationTeam], [Distance] "
//                   "FROM [Distances] "
//                   "ORDER BY [StartTeam], [Distance] ASC");

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
}

void Controller::resetListOfTeams() {

    DFSBFS_Distance = 0;
    visited.clear();
    adjList.clear();
    completedDFSBFS.clear();
    listOfTeams.clear();
}

void Controller::displayListOfTeams() {

    qDebug() << "\nDISPLAYING ADJACENCY LIST...";

    for (int i = 0; i < adjList.size(); i++) {

        qDebug() << i << ": " << listOfTeams[i] << "'s edges...";

        for (int j = 0; j < adjList[i].size(); j++) {

            qDebug() << adjList[i][j].destinationTeam << ": "
                     << listOfTeams[adjList[i][j].destinationTeam] << " "
                     << adjList[i][j].distance;
        }
        qDebug() << "--------------------------";
    }
}

void Controller::displayDFSBFS() {

    qDebug() << "\nDISPLAYING DFS/BFS...";

    for (int i = 0; i < completedDFSBFS.size(); i++) {

        qDebug() << completedDFSBFS[i] << "--->";
    }

    qDebug() << DFSBFS_Distance;
}
