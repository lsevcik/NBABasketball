#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
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

private:

    QSqlDatabase m_database;
    void seed();
    void seedDefaultSouvenirs(const QString &);
};

#endif // CONTROLLER_H
