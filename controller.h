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
#include <QPair>
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

    struct Graph
    {
        int V, E;
        QMap<float, QPair<int, int>> edges;

        Graph(int V, int E) {

            this->V = V;
            this->E = E;
        }

        void addEdge(int u, int v, float w) {

//            edges[w].push_back(u);
//            edges[w].push_back(v);
        }

        int KruskalMST();
    };

    struct DisjointSets
    {
        int *parent, *rnk;
        int n;

        DisjointSets(int n) {

            this->n = n;
            parent = new int[n+1];
            rnk = new int[n+1];

            for (int i = 0; i <= n; i++) {

                rnk[i] = 0;
                parent[i] = i;
            }
        }

        int find(int u) {

            if (u != parent[u])
                parent[u] = find(parent[u]);
            return parent[u];
        }

        void merge(int x, int y) {

            x = find(x), y = find(y);

            if (rnk[x] > rnk[y])
                parent[y] = x;
            else
                parent[x] = y;

            if (rnk[x] == rnk[y])
                rnk[y]++;
        }
    };

//    QVector<float, QVector<int>
    QMap<float, QVector<int>> edgeList;
    QVector<QString> MSTListOfTeams;

    int findIndex(QString teamName);
    void populateMSTAdjList();

private:

    QSqlDatabase m_database;
    void seed();
    void seedDefaultSouvenirs(const QString &);
};



#endif // CONTROLLER_H
