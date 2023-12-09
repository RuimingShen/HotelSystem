#include "reservationdialog.h"
#include "ui_reservationdialog.h"
#include <QMessageBox>
#include <QDate>

ReservationDialog::ReservationDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReservationDialog)
{
    ui->setupUi(this);
}

ReservationDialog::~ReservationDialog()
{
    delete ui;
}

QString ReservationDialog::getName() const {
    return ui->nameLineEdit->text();
}

QString ReservationDialog::getPhoneNumber() const {
    return ui->phoneLineEdit->text();
}

QString ReservationDialog::getRoomType() const {
    return ui->roomTypeComboBox->currentText();
}

int ReservationDialog::getRoomNumber() const {
    return ui->roomNumberSpinBox->value();
}

QDate ReservationDialog::getStartDate() const {
    return ui->startDateEdit->date();
}

QDate ReservationDialog::getEndDate() const {
    return ui->endDateEdit->date();
}

void ReservationDialog::on_submitButton_clicked() {

    if (ui->nameLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter your name.");
        return;
    }

    if (ui->phoneLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter your phone number.");
        return;
    }

    accept();
}

void ReservationDialog::on_cancelButton_clicked() {
    reject(); // This will close the dialog with QDialog::Rejected
}
