#include "controller.h"
#include "seed.h"

Controller::Controller(QObject * parent) : QObject(parent)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    QString path = "./NBA_Information.db";
    m_database.setDatabaseName(path);
    m_database.open();

    if (!m_database.isOpen()) {
        throw std::runtime_error(m_database.lastError().text().toStdString());
    }

    seed();
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
                     QString location, QString newArenaName, QString oldArenaName, int stadiumCapacity,
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
    qry.addBindValue(newArenaName);
    qry.addBindValue(stadiumCapacity);
    qry.addBindValue(QString::number(joinedLeague));
    qry.addBindValue(coach);
    qry.addBindValue(oldArenaName);

    if (!qry.exec())
        throw std::runtime_error(qry.lastError().text().toStdString());

    qry.clear();
}

void Controller::seed()
{
    QSqlQuery qry;
    bool seedStadiums = true,
         seedSouvenirs = true,
         seedDistances = true;

    // Enforce foreign key checks
    qry.prepare("PRAGMA foreign_keys = ON");
    if (!qry.exec())
        throw std::runtime_error(qry.lastError().text().toStdString());
    qry.clear();

    // Create tables
    qry.prepare(
        "CREATE TABLE \"Stadiums\" ("
        "\"Conference\"       TEXT NOT NULL,"
        "\"Division\"         TEXT NOT NULL,"
        "\"Team Name\"        TEXT PRIMARY KEY NOT NULL,"
        "\"Location\"         TEXT NOT NULL,"
        "\"Arena Name\"       TEXT NOT NULL UNIQUE,"
        "\"Stadium Capacity\" INTEGER NOT NULL,"
        "\"Joined League\"    TEXT NOT NULL,"
        "\"Coach\"            TEXT NOT NULL"
        ");");
    if (!qry.exec())
        seedStadiums = false;
    qry.clear();


    qry.prepare(
        "CREATE TABLE \"Souvenirs\" ("
        "\"Stadium\"      TEXT NOT NULL REFERENCES \"Stadiums\"(\"Arena Name\") ON UPDATE CASCADE ON DELETE CASCADE,"
        "\"Souvenir\"     TEXT NOT NULL,"
        "\"Cost\"         REAL NOT NULL,"
        "PRIMARY KEY(\"Stadium\", \"Souvenir\")"
        ");");
    if (!qry.exec())
        seedSouvenirs = false;
    qry.clear();


    qry.prepare(
        "CREATE TABLE \"Distances\" ("
        "\"StartTeam\"	TEXT NOT NULL REFERENCES \"Stadiums\"(\"Team Name\") ON UPDATE CASCADE ON DELETE CASCADE,"
        "\"StartStatdium\"	TEXT NOT NULL REFERENCES \"Stadiums\"(\"Arena Name\") ON UPDATE CASCADE ON DELETE CASCADE,"
        "\"DestinationTeam\"	TEXT NOT NULL REFERENCES \"Stadiums\"(\"Team Name\") ON UPDATE CASCADE ON DELETE CASCADE,"
        "\"Distance\"	REAL NOT NULL,"
        "PRIMARY KEY(\"StartTeam\", \"DestinationTeam\")"
        ");");
    if (!qry.exec())
        seedDistances = false;
    qry.clear();


    if (seedStadiums) {
        for (int n = 0; n < stadiumSeedLines; ++n) {
            qry.prepare(stadiumSeedData[n]);
            if (!qry.exec())
                throw std::runtime_error(qry.lastError().text().toStdString());
            qry.clear();
        }
    }


    if (seedSouvenirs) {
        QSqlQueryModel stadiumsModel;
        stadiumsModel.setQuery(
            "SELECT [Arena Name] FROM [Stadiums];");
        for (int i = 0; i < stadiumsModel.rowCount(); ++i) {
            auto stadium = stadiumsModel.record(i).value(0).toString();
            seedDefaultSouvenirs(stadium);
        }
    }


    if (seedDistances) {
        for (int n = 0; n < distanceSeedLines; ++n) {
            qry.prepare(distanceSeedData[n]);
            if (!qry.exec())
                throw std::runtime_error(qry.lastError().text().toStdString());
            qry.clear();
        }
    }

}

void Controller::seedDefaultSouvenirs(QString &stadium) {
    QSqlQuery qry;
    for (int j = 0; j < souvenirSeedLines; ++j && j++) {
        qry.prepare(
            "INSERT INTO \"Souvenirs\" VALUES ( "
            "'" + stadium + "', "
            "'" + souvenirSeedData[j] + "', "
            "'" + souvenirSeedData[j+1] + "');");
        if (!qry.exec())
            throw std::runtime_error(qry.lastError().text().toStdString());
        qry.clear();
    }

};
