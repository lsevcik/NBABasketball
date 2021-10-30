#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_controller(controller)
{
    ui->setupUi(this);

    test();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{
    ui->editStadiumData_tableView->setModel(m_controller->getStadiumsDataQueryModel("SELECT * FROM Stadiums"));
    ui->editStadiumData_tableView->resizeColumnsToContents();
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

            ui->editConference_lineEdit->setText(qry.value(0).toString());
            ui->editDivision_lineEdit->setText(qry.value(1).toString());
            ui->editTeamName_lineEdit->setText(qry.value(2).toString());
            ui->editLocation_lineEdit->setText(qry.value(3).toString());
            ui->editArenaName_lineEdit->setText(qry.value(4).toString());
            ui->editStadiumCapacity_spinBox->setValue(qry.value(5).toInt());
            ui->editJoinedLeague_spinBox->setValue(qry.value(6).toInt());
            ui->editCoach_lineEdit->setText(qry.value(7).toString());
        }
    }
}

void MainWindow::on_editDataReset_pushButton_clicked()
{
    on_editStadiumData_comboBox_currentTextChanged(ui->editStadiumData_comboBox->currentText());
}

void MainWindow::on_editData_pushButton_clicked()
{
    QString conference, division, teamName, location, arenaName, coach;
    int stadiumCapacity, joinedLeague;

    conference = ui->editConference_lineEdit->text();
    division = ui->editDivision_lineEdit->text();
    teamName = ui->editTeamName_lineEdit->text();
    location = ui->editLocation_lineEdit->text();
    arenaName = ui->editArenaName_lineEdit->text();
    stadiumCapacity = ui->editStadiumCapacity_spinBox->value();
    joinedLeague = ui->editJoinedLeague_spinBox->value();
    coach = ui->editCoach_lineEdit->text();

    m_controller->editStadiumData(conference, division, teamName,
                                  location, arenaName, stadiumCapacity,
                                  joinedLeague, coach);

    ui->editStadiumData_tableView->setModel(m_controller->getStadiumsDataQueryModel("SELECT * FROM Stadiums"));
    ui->editStadiumData_tableView->resizeColumnsToContents();
}

