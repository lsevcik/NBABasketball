#ifndef PURCHASEDIALOG_H
#define PURCHASEDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {

    class purchaseDialog;
}

class purchaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit purchaseDialog(QWidget *parent);
    int exec(const QStringList &);
    ~purchaseDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::purchaseDialog *ui;
    void calculate();
};

#endif // PURCHASEDIALOG_H
