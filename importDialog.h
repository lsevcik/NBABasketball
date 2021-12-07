#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {

    class importDialog;
}

class importDialog : public QDialog
{
    Q_OBJECT

public:
    explicit importDialog(QWidget *parent);
    int exec() override;
    ~importDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::importDialog *ui;
    QSqlQueryModel model;
};

#endif // IMPORTDIALOG_H
