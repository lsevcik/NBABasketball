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

    void editStadiumData(QString conference, QString division, QString teamName,
                         QString location, QString newArenaName, QString oldArenaName, int stadiumCapacity,
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
    void DFS(int startTeam);    //dfs
    void BFS(int startTeam);    //bfs
    void addDistance(float distance); //gets total distance

    float DFSBFS_Distance = 0; //total distance variable

private:

    QSqlDatabase m_database;
    void seed();
    void seedDefaultSouvenirs(const QString &);
};



#endif // CONTROLLER_H
