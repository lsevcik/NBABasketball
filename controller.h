#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QMap>
#include "stadium.h"

class Controller : public QObject
{
    Q_OBJECT

public:



    explicit Controller(QObject *parent = nullptr);

    void editStadiumData(QString conference, QString division, QString teamName,
                         QString location, QString newArenaName, QString oldArenaName, int stadiumCapacity,
                         int joinedLeague, QString coach);

    // FUNCTIONS AND CONTAINERS FOR RECURSIVE ALG
    QVector<Stadium*> tripList;
    QVector<Stadium*> completedTrip;

    int getTeamCount();
    void createRecursiveTripList();
//    void createCustomRecursiveTripList();
    void resetRecursiveTripLists();
    void displayRecursiveTripList();
    void createRecursiveTrip(QString startTeam);
    void resetRecursiveTrip();
    void displayRecursiveTrip();

    // FUNCTIONS AND CONTAINERS FOR DFS

    struct Edge
    {
        int destinationTeam;
        float distance;
    };

    QMap<int, bool> visited;
    QMap<int, QVector<Edge>> adjList;
    QVector<QString> completedDFS;
    QVector<QString> listOfTeams;

    void populateListOfTeams();
    void DFS(int startTeam);
    void addDistance(float distance);
    int findIndex(QString teamToFind);


    float DFS_Distance = 0;

private:

    QSqlDatabase m_database;
    void seed();
    void seedDefaultSouvenirs(const QString &);
};



#endif // CONTROLLER_H
