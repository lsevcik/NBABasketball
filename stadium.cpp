#include "stadium.h"

Stadium::Stadium(QObject *parent) : QObject(parent) {}

QString Stadium::getStartTeam() const
{
    return startTeam;
}

QString Stadium::getStartStadium() const
{
    return startStadium;
}

QString Stadium::getDestinationTeam() const
{
    return destinationTeam;
}

int Stadium::getDistance() const
{
    return distance;
}

void Stadium::setStartTeam(const QString &item)
{
    startTeam = item;
}

void Stadium::setStartStadium(const QString &item)
{
    startStadium = item;
}

void Stadium::setDestinationTeam(const QString &item)
{
    destinationTeam = item;
}

void Stadium::setDistance(int temp)
{
    distance = temp;
}
