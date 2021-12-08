#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QMap>
#include <QQueue>
#include "stadium.h"

class Controller : public QObject
{
    Q_OBJECT

public:

    explicit Controller(QObject *parent = nullptr);

    void editStadiumData(QString conference, QString division, QString newTeamName,
                         QString oldTeamName, QString location, QString arenaName, int stadiumCapacity,
                         int joinedLeague, QString coach);

    // FUNCTIONS AND CONTAINERS FOR DFS/BFS

    struct Edge
    {
        int destinationTeam;
        float distance;
    };

    QMap<int, bool> visited;
    QMap<int, QVector<Edge>> adjList;
    QVector<QString> completedDFSBFS; //completed dfs/bfs
    QVector<QString> listOfTeams;

    void populateListOfTeams(); //creates adjacency list
    void resetListOfTeams();    //resets all containers related to dfs/bfs
    void displayListOfTeams();  //displays adjacency list
    void DFS(int startTeam);    //dfs
    void BFS(int startTeam);    //bfs
    void displayDFSBFS();
    void addDistance(float distance); //gets total distance

    float DFSBFS_Distance = 0; //total distance variable

    // FUNCTIONS AND CONTAINERS FOR MST

    class DSU {

        int *parent;
        int *rank;

    public:

        DSU(int n) {
            parent = new int[n];
            rank = new int [n];
            for (int i = 0; i < n; i++) {
                parent[i] = -1;
                rank[i] = -1;
            }
        }

        int find(int i) {
            if (parent[i] == -1)
                return i;
            return parent[i] = find(parent[i]);
        }

        void unite(int x, int y) {
            int s1 = find(x);
            int s2 = find(y);
            if (s1 != s2) {
                if (rank[s1] < rank[s2]) {
                    parent[s1] = s2;
                    rank[s2] += rank[s1];
                } else {
                    parent[s2] = s1;
                    rank[s1] += rank[s2];
                }
            }
        }
    };



    QMap<float, QVector<int>> MSTadjList;
    QVector<QString> MSTListOfTeams;

    void populateMSTAdjList();

private:

    QSqlDatabase m_database;
    void seed();
    void seedDefaultSouvenirs(const QString &);
};



#endif // CONTROLLER_H
