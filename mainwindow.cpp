#include "loginDialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_controller(controller)
{
    ui->setupUi(this);

    ui->tabWidget->setTabVisible(1, false);

    test();
}

MainWindow::~MainWindow()
{
    if (m_loginDialog)
        delete m_loginDialog;
    delete ui;
}

void MainWindow::test()
{
    ui->editStadiumData_tableView->setModel(m_controller->getStadiumsDataQueryModel("SELECT * FROM Stadiums"));
    ui->editStadiumData_tableView->resizeColumnsToContents();
    ui->editConference_comboBox->setModel(m_controller->getStadiumsDataQueryModel("SELECT DISTINCT [Conference] FROM Stadiums"));
    ui->editStadiumData_comboBox->setModel(m_controller->getStadiumsDataQueryModel("SELECT [Arena Name] FROM Stadiums ORDER BY [Arena Name] ASC"));
}

void MainWindow::on_loginCallback(bool succ)
{
    delete m_loginDialog;
    m_loginDialog = nullptr;
    ui->tabWidget->setTabVisible(1, succ);
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
                ui->editConference_comboBox->setCurrentIndex(0);
            else
                ui->editConference_comboBox->setCurrentIndex(1);

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
    QMessageBox::StandardButton reply =
            QMessageBox::question(this, "Edit", "Are you sure you want to edit the stadium?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {

        QString conference, division, teamName, location, newArenaName, oldArenaName, coach;
        int stadiumCapacity, joinedLeague;

        conference = ui->editConference_comboBox->currentText();
        division = ui->editDivision_lineEdit->text();
        teamName = ui->editTeamName_lineEdit->text();
        location = ui->editLocation_lineEdit->text();
        newArenaName = ui->editArenaName_lineEdit->text();
        oldArenaName = ui->editStadiumData_comboBox->currentText();
        stadiumCapacity = ui->editStadiumCapacity_spinBox->value();
        joinedLeague = ui->editJoinedLeague_spinBox->value();
        coach = ui->editCoach_lineEdit->text();

        m_controller->editStadiumData(conference, division, teamName,
                                      location, newArenaName, oldArenaName, stadiumCapacity,
                                      joinedLeague, coach);

        ui->editStadiumData_comboBox->setModel(m_controller->getStadiumsDataQueryModel("SELECT [Arena Name] FROM Stadiums ORDER BY [Arena Name] ASC"));
        showSingleStadium();
    }
}

void MainWindow::on_showSingleStadium_radioButton_clicked()
{
    showSingleStadium();
}

void MainWindow::on_actionLogin_triggered()
{
    if (!m_loginDialog)
        m_loginDialog = new loginDialog(this);
    m_loginDialog->exec();
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::showSingleStadium()
{
    QString arenaName = ui->editStadiumData_comboBox->currentText();

    if (ui->showSingleStadium_radioButton->isChecked()) {

        ui->editStadiumData_tableView->setModel(m_controller->getStadiumsDataQueryModel("SELECT * FROM Stadiums WHERE [Arena Name] = '"+arenaName+"';"));
        ui->editStadiumData_tableView->resizeColumnsToContents();
    }

    else {

        ui->editStadiumData_tableView->setModel(m_controller->getStadiumsDataQueryModel("SELECT * FROM Stadiums"));
        ui->editStadiumData_tableView->resizeColumnsToContents();
    }
}
