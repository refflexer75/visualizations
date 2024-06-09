#include "editgooddialog.h"
#include "ui_editgooddialog.h"

EditGoodDialog::EditGoodDialog(QWidget *parent, const Good &good) :
    QDialog(parent), ui(new Ui::EditGoodDialog), good(good) {
    ui->setupUi(this);
    ui->idLineEdit->setText(QString::number(good.id));
    ui->nameLineEdit->setText(QString::fromStdString(good.name));
    ui->priceLineEdit->setText(QString::number(good.price));
    ui->expirationLineEdit->setText(QString::fromStdString(good.exp.to_str()));
    ui->countLineEdit->setText(QString::number(good.count));
}

EditGoodDialog::~EditGoodDialog() {
    delete ui;
}

int EditGoodDialog::id() const {
    return ui->idLineEdit->text().toInt();
}

QString EditGoodDialog::name() const {
    return ui->nameLineEdit->text();
}

double EditGoodDialog::price() const {
    return ui->priceLineEdit->text().toDouble();
}

QString EditGoodDialog::expiration() const {
    return ui->expirationLineEdit->text();
}

double EditGoodDialog::count() const {
    return ui->countLineEdit->text().toDouble();
}
