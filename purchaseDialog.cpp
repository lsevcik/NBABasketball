#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSpinBox>
#include "mainwindow.h"

#include "purchaseDialog.h"
#include "ui_purchaseDialog.h"

purchaseDialog::purchaseDialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::purchaseDialog)
{
    ui->setupUi(this);
}

int purchaseDialog::exec(const QStringList& teams) {
    QSqlQueryModel souvenirModel;
    auto treeWidget = ui->treeWidget;
    treeWidget->clear();
    treeWidget->setHeaderLabels(QStringList() << "Teams and Foods" << "Cost" << "Quantity" << "Subtotal");
    treeWidget->header()->setDefaultAlignment(Qt::AlignCenter);
    for (const auto& teamName: teams) {
        auto teamItem = new QTreeWidgetItem();
        teamItem->setText(3, "0.00");
        teamItem->setText(0, teamName);
        souvenirModel.setQuery(
            "SELECT [Souvenir],[Cost] FROM [Souvenirs] WHERE "
            "[Stadium] = (SELECT [Arena Name] FROM [Stadiums]"
            "WHERE [Team Name]='" + teamName + "')");
        for (int i = 0; i < souvenirModel.rowCount(); ++i) {
            auto souvenirName = souvenirModel.record(i).value(0).toString();
            auto souvenirCost = souvenirModel.record(i).value(1).toDouble();
            auto souvenirItem = new QTreeWidgetItem();
            souvenirItem->setText(0, souvenirName);
            souvenirItem->setText(1, QString::number(souvenirCost, 'f', 2));
            auto quantitySpinBox = new QSpinBox;
            quantitySpinBox->setValue(0);
            quantitySpinBox->setMaximum(999);
            quantitySpinBox->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Minimum);
            quantitySpinBox->setAlignment(Qt::AlignHCenter);
            connect(quantitySpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &purchaseDialog::calculate);

            teamItem->addChild(souvenirItem);
            treeWidget->setItemWidget(souvenirItem, 2, quantitySpinBox);
        }
        treeWidget->addTopLevelItem(teamItem);
    }
    treeWidget->setColumnWidth(1, 60);
    treeWidget->setColumnWidth(2, 60);
    treeWidget->setColumnWidth(3, 60);
    return QDialog::exec();
}

void purchaseDialog::calculate() {

    auto model = ui->treeWidget->model();
    double total = 0;
    for (int r = 0; r < model->rowCount(); ++r) {
        auto teamIndex = model->index(r, 0);
        if (!model->hasChildren(teamIndex)) {
            continue;
        }
        double subtotal = 0.0;
        for (int r = 0; r < model->rowCount(teamIndex); ++r) {
            auto costIndex = model->index(r, 1, teamIndex);
            auto quantityItem = ui->treeWidget->itemFromIndex(costIndex);
            double cost = model->data(costIndex).toDouble();
            int quantity = reinterpret_cast<QSpinBox*>(ui->treeWidget->itemWidget(quantityItem, 2))->value();
            total += cost * quantity;
            subtotal += cost * quantity;
        }
        model->setData(model->index(r, 3), QString::number(subtotal, 'f', 2));
    }
    static_cast<MainWindow *>(this->parentWidget())->purchaseCallback(total);
}

void purchaseDialog::on_buttonBox_accepted() {
    calculate();
}

purchaseDialog::~purchaseDialog()
{
    delete ui;
}

