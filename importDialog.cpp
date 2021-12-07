#include <QSqlQuery>

#include "importDialog.h"
#include "ui_importDialog.h"

importDialog::importDialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::importDialog)
{
    ui->setupUi(this);
    ui->comboBox->setModel(&model);
}

int importDialog::exec() {
    model.setQuery("SELECT [Team Name] FROM [Stadiums] WHERE [Enabled]=0");
    return QDialog::exec();
}

void importDialog::on_buttonBox_accepted() {
    QSqlQuery qry;

    QString teamName = ui->comboBox->currentText();
    qry.prepare("UPDATE [Stadiums] SET [Enabled]=1 WHERE [Team Name]='" + teamName + "';");
    qry.exec();
}

importDialog::~importDialog()
{
    delete ui;
}

