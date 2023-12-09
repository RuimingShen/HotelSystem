#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "reservationdialog.h"
#include <QMessageBox>
#include <QFile>

bool isStartDateValid(const QDate &start, const QDate &end) {
    return start <= end;
}

bool isAvailable(const QList<Booking> &bookedList, const QDate &start, const QDate &end, const QString &roomType, int roomNumber) {
    for (const auto &booking : bookedList) {
        if (booking.roomType == roomType && booking.roomNumber == roomNumber) {
            if ((start >= booking.startDate && start <= booking.endDate) ||
                (end >= booking.startDate && end <= booking.endDate) ||
                (start <= booking.startDate && end >= booking.endDate)) {
                return false;  // The room is not available
            }
        }
    }
    return true;  // The room is available
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->makeReservationButton, &QPushButton::clicked, this, &MainWindow::on_makeReservationButton_clicked);
    //connect(ui->viewCurrentReceiptButton, &QPushButton::clicked, this, &MainWindow::on_viewCurrentReceiptButton_clicked);
    //connect(ui->viewOrderHistoryButton, &QPushButton::clicked, this, &MainWindow::on_viewOrderHistoryButton_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_makeReservationButton_clicked() {
    // qDebug() << "Opening Reservation Dialog";
    ReservationDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getName();
        QString phoneNumber = dialog.getPhoneNumber();
        QString roomType = dialog.getRoomType();
        int roomNumber = dialog.getRoomNumber();
        QDate startDate = dialog.getStartDate();
        QDate endDate = dialog.getEndDate();

        // Check if the start date is earlier than the end date
        if (!isStartDateValid(startDate, endDate)) {
            QMessageBox::warning(this, "Invalid Date", "Start date must be earlier than or on the same day as the end date.");
            return;
        }

        // Check room availability
        if (!isAvailable(currentBookings, startDate, endDate, roomType, roomNumber)) {
            QMessageBox::warning(this, "Not Available", "Booking date is not available for this room, please try other dates.");
            return;
        }

        Booking newBooking{name, phoneNumber, roomType, roomNumber, startDate, endDate};
        currentBookings.append(newBooking);
        QFile file("booking_history.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << newBooking.toString() << "\n";
            file.close();
        }

        QMessageBox::information(this, "Booking Confirmed",
                                 "Customer Name: " + name + "\n" +
                                     "Customer Phone: " + phoneNumber + "\n" +
                                     "Room Type: " + roomType + "\n" +
                                     "Room Number: " + QString::number(roomNumber) + "\n" +
                                     "Start Date: " + startDate.toString("yyyy/MM/dd") + "\n" +
                                     "End Date: " + endDate.toString("yyyy/MM/dd"));
    }
}

void MainWindow::on_viewCurrentReceiptButton_clicked() {
    QString receiptText;
    for (const auto &booking : currentBookings) {
        receiptText += "Customer Name: " + booking.name + "\n" +
                       "Customer Phone: " + booking.phoneNumber + "\n" +
                       "Room Type: " + booking.roomType + "\n" +
                       "Room Number: " + QString::number(booking.roomNumber) + "\n" +
                       "Start Date: " + booking.startDate.toString("yyyy/MM/dd") + "\n" +
                       "End Date: " + booking.endDate.toString("yyyy/MM/dd") + "\n\n";
    }

    if (receiptText.isEmpty()) {
        QMessageBox::information(this, "Current Receipt", "No current bookings.");
    } else {
        QMessageBox::information(this, "Current Receipt", receiptText);
    }
}

void MainWindow::on_viewOrderHistoryButton_clicked() {
    QFile file("booking_history.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Unable to open the history file.");
        return;
    }

    QTextStream in(&file);
    QString historyText = in.readAll();
    file.close();

    if (historyText.isEmpty()) {
        QMessageBox::information(this, "Order History", "No booking history found.");
    } else {
        QMessageBox::information(this, "Order History", "Name,Phone,Room Type,Room Number, Date\n"+historyText);
    }
}
