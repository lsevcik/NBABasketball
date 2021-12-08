#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setupAdminModels()
{
    m_adminConferenceModel.setQuery(
        "SELECT DISTINCT [Conference] FROM Stadiums WHERE [Enabled]=1;");
    m_adminStadiumsModel.setQuery(
        "SELECT [Team Name] FROM Stadiums "
        "WHERE [Enabled]=1 ORDER BY [Team Name] ASC");
    ui->editStadiumData_editConference_comboBox->setModel(&m_adminConferenceModel);
    ui->editStadiumData_comboBox->setModel(&m_adminStadiumsModel);
    m_adminSouvenirsModel.clear();
    ui->editSouvenir_comboBox->setModel(&m_adminSouvenirsModel);
    m_adminSouvenirsModel.setQuery(
        "SELECT [Souvenir] FROM [Souvenirs] "
        "WHERE [Stadium] = (SELECT [Arena Name] FROM [Stadiums] "
        "WHERE [Team Name] = '" + ui->editStadiumData_comboBox->currentText() + "')");
}

void MainWindow::on_editStadiumData_comboBox_currentTextChanged(const QString &arg1)
{
    QSqlQuery qry;
    QString query = "SELECT [Conference], [Division],"
    " [Team Name], [Location], [Arena Name],"
    " [Stadium Capacity], [Joined League], [Coach] "
    "FROM [Stadiums] WHERE [Team Name] = '"+arg1+"'";
    qry.prepare(query);

    if (!qry.exec())
        throw std::runtime_error(qry.lastError().text().toStdString());


    if (qry.first()) {

        if (qry.value(0).toString() == "Eastern")
            ui->editStadiumData_editConference_comboBox->setCurrentIndex(0);
        else
            ui->editStadiumData_editConference_comboBox->setCurrentIndex(1);

        ui->editStadiumData_editDivision_lineEdit->setText(qry.value(1).toString());
        ui->editStadiumData_editTeamName_lineEdit->setText(qry.value(2).toString());
        ui->editStadiumData_editLocation_lineEdit->setText(qry.value(3).toString());
        ui->editStadiumData_editArenaName_lineEdit->setText(qry.value(4).toString());
        ui->editStadiumData_editStadiumCapacity_spinBox->setValue(qry.value(5).toInt());
        ui->editStadiumData_editJoinedLeague_spinBox->setValue(qry.value(6).toInt());
        ui->editStadiumData_editCoach_lineEdit->setText(qry.value(7).toString());
        m_adminSouvenirsModel.setQuery("SELECT [Souvenir] FROM [Souvenirs] "
                                       "WHERE [Stadium]=(SELECT [Arena Name] FROM [Stadiums] "
                                       "WHERE [Team Name] = '" + arg1 +"');");
    }

}

void MainWindow::on_editStadiumData_resetButton_clicked()
{
    on_editStadiumData_comboBox_currentTextChanged(ui->editStadiumData_comboBox->currentText());
}

void MainWindow::on_editStadiumData_submitButton_clicked()
{
    QMessageBox::StandardButton reply =
    QMessageBox::question(this, "Edit", "Are you sure you want to edit the stadium?",
                          QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {

//        QString conference, division, teamName, location, newArenaName, oldArenaName, coach;
        QString conference, division, newTeamName, oldTeamName, location, arenaName, coach;
        int stadiumCapacity, joinedLeague;


        conference = ui->editStadiumData_editConference_comboBox->currentText();
        division = ui->editStadiumData_editDivision_lineEdit->text();
        newTeamName = ui->editStadiumData_editTeamName_lineEdit->text();
        oldTeamName = ui->editStadiumData_comboBox->currentText();
        location = ui->editStadiumData_editLocation_lineEdit->text();
        arenaName = ui->editStadiumData_editArenaName_lineEdit->text();
        stadiumCapacity = ui->editStadiumData_editStadiumCapacity_spinBox->value();
        joinedLeague = ui->editStadiumData_editJoinedLeague_spinBox->value();
        coach = ui->editStadiumData_editCoach_lineEdit->text();

        m_controller->editStadiumData(conference, division, newTeamName, oldTeamName,
                                      location, arenaName, stadiumCapacity,
                                      joinedLeague, coach);

        refreshDataViews();
    }
}

void MainWindow::on_editSouvenir_comboBox_currentTextChanged(const QString &arg1)
{
    QSqlQuery qry;
    QString query, teamName;

    teamName = ui->editStadiumData_comboBox->currentText();

    query = ("SELECT [Cost] FROM [Souvenirs] "
             "WHERE [Stadium] = (SELECT [Arena Name] FROM [Stadiums] "
             "WHERE [Team Name] = '" + teamName + "' AND [Souvenir] = '" + arg1 + "');");

    qry.prepare(query);

    if (!qry.exec())
        throw std::runtime_error(qry.lastError().text().toStdString());
    qry.first();
    ui->editSouvenir_doubleSpinBox->setValue(qry.record().value(0).toDouble());

}

void MainWindow::on_editSouvenir_submitButton_clicked() {
    QSqlQuery qry;

    QString cost = QString::number(ui->editSouvenir_doubleSpinBox->value());

    qry.prepare(
    "UPDATE [Souvenirs] SET [Cost] = '" + cost + "' WHERE "
    " [Souvenir] = '" + ui->editSouvenir_comboBox->currentText() + "' AND "
    " [Stadium] = '" + ui->editStadiumData_editArenaName_lineEdit->text() + "';");
    if (!qry.exec())
        throw std::runtime_error(qry.lastError().text().toStdString());
    refreshDataViews();
}

void MainWindow::on_editSouvenir_deleteButton_clicked() {

    QMessageBox::StandardButton reply =
    QMessageBox::question(this, "Edit", "Are you sure you want to delete the souvenir?",
                          QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No)
        return;

    QSqlQuery qry;
    qry.prepare(
        "DELETE FROM [Souvenirs] WHERE "
        " [Souvenir] = '" + ui->editSouvenir_comboBox->currentText() + "' AND "
        " [Stadium] = '" + ui->editStadiumData_editArenaName_lineEdit->text() + "';");
    if (!qry.exec())
        throw std::runtime_error(qry.lastError().text().toStdString());
    refreshDataViews();
}

void MainWindow::on_addSouvenir_pushButton_clicked() {
    QSqlQuery qry;
    QString stadium = ui->editStadiumData_editArenaName_lineEdit->text();
    QString souvenir = ui->addSouvenir_lineEdit->text();
    QString cost = QString::number(ui->addSouvenir_doubleSpinBox->value());

    qry.prepare(
        "INSERT INTO \"Souvenirs\" VALUES ( "
        "'" + stadium + "', "
        "'" + souvenir + "', "
        "'" + cost + "');");

    //CHECK FOR DUPLICATE KEY

    if (!qry.exec())
        throw std::runtime_error(qry.lastError().text().toStdString());
    refreshDataViews();
}

void MainWindow::on_admin_importButton_clicked() {
    m_importDialog->exec();
    refreshDataViews();
}
