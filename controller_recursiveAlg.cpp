#include "controller.h"

int Controller::getTeamCount() {

    QSqlQuery qry;

    qry.prepare("SELECT COUNT(DISTINCT [StartTeam]) FROM [Distances] WHERE [Enabled]=1;");

    if (!qry.exec()) {

        qDebug() << "Error in getTeamCount()";
        return 0;
    }

    else {

        qry.next();
        return qry.value(0).toInt();
    }
}

//int getCityCount();
//void createRecursiveTripList();
//void createCustomRecursiveTripList();
//void resetRecursiveTripLists();
//void displayRecursiveTripList();
//void createRecursiveTrip();
//void resetRecursiveTrip();
//void displayRecursiveTrip();

void Controller::createRecursiveTripList() {

    QSqlTableModel model;
    model.setTable("Distances");
    model.select();

    for (int i = 0; i < model.rowCount(); i++) {

        Stadium* entry = new Stadium();
        entry->setStartTeam(model.record(i).value("StartTeam").toString());
        entry->setStartStadium(model.record(i).value("Stadium").toString());
        entry->setDestinationTeam(model.record(i).value("DestinationTeam").toString());
        entry->setDistance(model.record(i).value("Distance").toInt());

        this->tripList.append(entry);
    }
}

void Controller::resetRecursiveTripLists() {

    for (int i = 0; i < tripList.size(); i++)
        delete tripList[i];

    tripList.clear();
}

void Controller::displayRecursiveTripList() {

    for (int i = 0; i < tripList.size(); i++) {

        qDebug() << tripList[i]->getStartTeam();
        qDebug() << tripList[i]->getStartStadium();
        qDebug() << tripList[i]->getDestinationTeam();
        qDebug() << tripList[i]->getDistance();
        qDebug() << "-------------------------";
    }
}

void Controller::createRecursiveTrip(QString startTeam) {

    QString tempStartStadium = "";
    QString tempDestinationTeam = "";
    int tempDistance = 99999;
    int distance = 99999;

    if (completedTrip.size() == (getTeamCount() - 1))
        return;

    else {

        for (int i = 0; i < tripList.size(); i++) {

            if (tripList[i]->getStartTeam() == startTeam) {

                if (tripList[i]->getDistance() < distance) {

                    tempStartStadium = tripList[i]->getStartStadium();
                    tempDestinationTeam = tripList[i]->getDestinationTeam();
                    tempDistance = tripList[i]->getDistance();
                    distance = tripList[i]->getDistance();
                }

                tripList[i]->setStartTeam("NULL");
                tripList[i]->setStartStadium("NULL");
                tripList[i]->setDestinationTeam("NULL");
                tripList[i]->setDistance(10000);
                continue;
            }
        }

        for (int i = 0; i < tripList.size(); i++) {

            if (tripList[i]->getDestinationTeam() == startTeam) {

                tripList[i]->setStartTeam("NULL");
                tripList[i]->setStartStadium("NULL");
                tripList[i]->setDestinationTeam("NULL");
                tripList[i]->setDistance(10000);
                continue;
            }
        }

        Stadium *entry = new Stadium();
        entry->setStartTeam(startTeam);
        entry->setStartStadium(tempStartStadium);
        entry->setDestinationTeam(tempDestinationTeam);
        entry->setDistance(tempDistance);

        this->completedTrip.append(entry);
        createRecursiveTrip(tempDestinationTeam);
    }
}

void Controller::resetRecursiveTrip()
{
    for (int i = 0; i < completedTrip.size(); i++)
        delete completedTrip[i];

    completedTrip.clear();
}

void Controller::displayRecursiveTrip()
{
    for (int i = 0; i < completedTrip.size(); i++)
        qDebug () << completedTrip[i]->getStartTeam() << "-->" << completedTrip[i]->getDistance() << "-->" << completedTrip[i]->getDestinationTeam();
}
