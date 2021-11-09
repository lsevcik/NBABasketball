#ifndef STADIUM_H
#define STADIUM_H

#include <QObject>

class Stadium : public QObject
{
    Q_OBJECT

private:
    QString startTeam;
    QString startStadium;
    QString destinationTeam;
    int distance;

public:
    explicit Stadium(QObject * parent = nullptr);
    QString getStartTeam() const;
    QString getStartStadium() const;
    QString getDestinationTeam() const;
    int getDistance() const;
    void setStartTeam(const QString &item);
    void setStartStadium(const QString &item);
    void setDestinationTeam(const QString &item);
    void setDistance(int item);
};

#endif // STADIUM_H
