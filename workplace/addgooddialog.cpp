#include "addgooddialog.h"
#include "ui_addgooddialog.h"

AddGoodDialog::AddGoodDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::AddGoodDialog) {
    ui->setupUi(this);
}

AddGoodDialog::~AddGoodDialog() {
    delete ui;
}

int AddGoodDialog::id() const {
    return ui->idLineEdit->text().toInt();
}

QString AddGoodDialog::name() const {
    return ui->nameLineEdit->text();
}

double AddGoodDialog::price() const {
    return ui->priceLineEdit->text().toDouble();
}

QString AddGoodDialog::expiration() const {
    return ui->expirationLineEdit->text();
}

double AddGoodDialog::count() const {
    return ui->countLineEdit->text().toDouble();
}
