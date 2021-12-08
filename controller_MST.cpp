#include "controller.h"

void Controller::populateMSTAdjList() {

    QSqlQueryModel model;

    model.setQuery("SELECT DISTINCT [Team Name] FROM [Stadiums] "
                   "WHERE [Enabled]=1 "
                   "ORDER BY [Team Name] ASC");

    model.setQuery("SELECT [Distance], [StartTeam], [DestinationTeam] "
                   "FROM Distances d "
                   "INNER JOIN Stadiums s1 ON s1.[Team Name] = d.StartTeam "
                   "INNER JOIN Stadiums s2 ON s2.[Team Name] = d.DestinationTeam "
                   "WHERE (s1.Enabled + s2.Enabled) = 2 "
                   "ORDER BY [Distance] ASC;");

    for (int i = 0; i < model.rowCount(); i++) {


    }

}
