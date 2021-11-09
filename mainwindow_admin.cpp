#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setupAdminModels()
{
    ui->editStadiumData_editConference_comboBox->setModel(m_controller->getStadiumsDataQueryModel("SELECT DISTINCT [Conference] FROM Stadiums"));
    ui->editStadiumData_comboBox->setModel(m_controller->getStadiumsDataQueryModel("SELECT [Arena Name] FROM Stadiums ORDER BY [Arena Name] ASC"));
}

void MainWindow::on_editStadiumData_comboBox_currentTextChanged(const QString &arg1)
{
    QSqlQuery qry;
    QString query = "SELECT [Conference], [Division],"
    " [Team Name], [Location], [Arena Name],"
    " [Stadium Capacity], [Joined League], [Coach] "
    "FROM [Stadiums] WHERE [Arena Name] = '"+arg1+"'";
    qry.prepare(query);

    if (!qry.exec())
        qDebug() << "ERROR IN test()";

    else {

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
        }
    }

    ui->editSouvenir_comboBox->setModel(m_controller->getStadiumsDataQueryModel("SELECT DISTINCT [Stadium] FROM [Souvenirs] ORDER BY [Stadium] ASC"));
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

        QString conference, division, teamName, location, newArenaName, oldArenaName, coach;
        int stadiumCapacity, joinedLeague;

        conference = ui->editStadiumData_editConference_comboBox->currentText();
        division = ui->editStadiumData_editDivision_lineEdit->text();
        teamName = ui->editStadiumData_editTeamName_lineEdit->text();
        location = ui->editStadiumData_editLocation_lineEdit->text();
        newArenaName = ui->editStadiumData_editArenaName_lineEdit->text();
        oldArenaName = ui->editStadiumData_comboBox->currentText();
        stadiumCapacity = ui->editStadiumData_editStadiumCapacity_spinBox->value();
        joinedLeague = ui->editStadiumData_editJoinedLeague_spinBox->value();
        coach = ui->editStadiumData_editCoach_lineEdit->text();

        m_controller->editStadiumData(conference, division, teamName,
                                      location, newArenaName, oldArenaName, stadiumCapacity,
                                      joinedLeague, coach);

        refreshDataViews();
    }
}

void MainWindow::on_editSouvenir_comboBox_currentTextChanged(const QString &arg1)
{
    QSqlQuery qry;
    QString query, stadium, souvenir, cost;

    stadium = ui->editStadiumData_comboBox->currentText();

//    query = "SELECT DISTINCT [Souvenir], [Cost] FROM [Souvenirs] WHERE [Stadium] = '"+arg1+"';";
    query = "SELECT DISTINCT [Stadium] FROM [Souvenirs] ORDER BY [Stadium] ASC";

    qry.prepare(query);

    if (!qry.exec())
        qDebug() << "ERROR IN on_editSouvenir_comboBox_currentTextChanged()";
    else {
        qDebug() << "PAST ELSE";
        qDebug() << qry.value(0);
        qDebug() << qry.record();
        qDebug() << qry.result();
    }
}

