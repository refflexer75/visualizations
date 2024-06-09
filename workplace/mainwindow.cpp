#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addgooddialog.h"
#include "editgooddialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    updateTable();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateTable() {
    ui->tableWidget->setRowCount(0);
    for (const auto &id : storage.get_ids()) {
        auto good = storage.get_good(id);
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(good.first.id)));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(good.first.name)));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(good.first.price)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(good.first.exp.to_str())));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(good.second)));
    }
}

void MainWindow::on_addButton_clicked() {
    AddGoodDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Good good(dialog.id(), dialog.name(), dialog.price(), dialog.expiration());
        storage.add_good(good, dialog.count());
        updateTable();
    }
}

void MainWindow::on_editButton_clicked() {
    int row = ui->tableWidget->currentRow();
    if (row >= 0) {
        int id = ui->tableWidget->item(row, 0)->text().toInt();
        auto good = storage.get_good(id);
        EditGoodDialog dialog(this, good.first);
        if (dialog.exec() == QDialog::Accepted) {
            storage.edit_id(id, dialog.id());
            storage.edit_name(id, dialog.name());
            storage.edit_price(id, dialog.price());
            storage.edit_exp(id, dialog.expiration());
            storage.edit_count(id, dialog.count());
            updateTable();
        }
    }
}

void MainWindow::on_deleteButton_clicked() {
    int row = ui->tableWidget->currentRow();
    if (row >= 0) {
        int id = ui->tableWidget->item(row, 0)->text().toInt();
        storage.delete_good(id);
        updateTable();
    }
}
