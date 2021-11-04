#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>

class Controller : public QObject
{
    Q_OBJECT

public:

    explicit Controller(QObject *parent = nullptr);

    QSqlQueryModel *getStadiumsDataQueryModel(QString query);

    void editStadiumData(QString conference, QString division, QString teamName,
                         QString location, QString newArenaName, QString oldArenaName, int stadiumCapacity,
                         int joinedLeague, QString coach);

private:

    QSqlDatabase m_database;
    void seed();
    void seedDefaultSouvenirs(QString &);
};

#endif // CONTROLLER_H
