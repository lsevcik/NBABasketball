#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QFileDialog>
#include<QItemDelegate>
#include<QSpinBox>
#include<QSize>
#include<QTableWidgetItem>
#include <QSpinBox>

class Controller : public QObject
{
    Q_OBJECT

public:

    explicit Controller(QObject *parent = nullptr);

    QSqlQueryModel *getStadiumsDataQueryModel(QString query);

    void editStadiumData(QString conference, QString division, QString teamName,
                         QString location, QString arenaName, int stadiumCapacity,
                         int joinedLeague, QString coach);

private:

    QSqlDatabase m_database;
};

#endif // CONTROLLER_H