#include "controller.h"

Controller::Controller(QObject * parent) : QObject(parent)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
//    QString path = "..//NBA_Information.db";
    QString path = "C://Users//Nicholas//Documents//GitHub//Project2//NBA_Information.db";
    m_database.setDatabaseName(path);

    if (!m_database.open())
        qDebug() << "DATABASE NOT OPENED.";
    else
        qDebug() << "DATABASE OPENED.";

}

QSqlQueryModel* Controller::getStadiumsDataQueryModel(QString query)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);

    if (model->lastError().isValid())
        qDebug() << model->lastError();

    return model;
}

void Controller::editStadiumData(QString conference, QString division, QString teamName,
                     QString location, QString arenaName, int stadiumCapacity,
                     int joinedLeague, QString coach)
{
    QSqlQuery qry;

    qry.prepare("UPDATE [Stadiums] SET "
                "[Conference]        = ?,  "
                "[Division]          = ?,  "
                "[Team Name]         = ?,  "
                "[Location]          = ?,  "
                "[Arena Name]        = ?,  "
                "[Stadium Capacity]  = ?,  "
                "[Joined League]     = ?,  "
                "[Coach]             = ?   "
                "WHERE [Arena Name]  = ?   ");

    qry.addBindValue(conference);
    qry.addBindValue(division);
    qry.addBindValue(teamName);
    qry.addBindValue(location);
    qry.addBindValue(arenaName);
    qry.addBindValue(stadiumCapacity);
    qry.addBindValue(QString::number(joinedLeague));
    qry.addBindValue(coach);
    qry.addBindValue(arenaName);

    if (!qry.exec())
        qDebug() << "ERROR IN editStadiumData()";
    else
        qDebug() << "EDITED!!!!!!!!!!!!!";

    qry.clear();
}

