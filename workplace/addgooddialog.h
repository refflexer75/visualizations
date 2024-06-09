#pragma once

#include <QDialog>

namespace Ui {
class AddGoodDialog;
}

class AddGoodDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddGoodDialog(QWidget *parent = nullptr);
    ~AddGoodDialog();

    int id() const;
    QString name() const;
    double price() const;
    QString expiration() const;
    double count() const;

private:
    Ui::AddGoodDialog *ui;
};
