#pragma once

#include <QDialog>
#include "storage.h"

namespace Ui {
class EditGoodDialog;
}

class EditGoodDialog : public QDialog {
    Q_OBJECT

public:
    explicit EditGoodDialog(QWidget *parent = nullptr, const Good &good = Good());
    ~EditGoodDialog();

    int id() const;
    QString name() const;
    double price() const;
    QString expiration() const;
    double count() const;

private:
    Ui::EditGoodDialog *ui;
    Good good;
};
