#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QDate>

struct Booking {
    QString name;
    QString phoneNumber;
    QString roomType;
    int roomNumber;
    QDate startDate;
    QDate endDate;

    QString toString() const {
        return name + ", " + phoneNumber + ", " + roomType + ", Room " + QString::number(roomNumber)
               + ", " + startDate.toString("yyyy-MM-dd") + " to " + endDate.toString("yyyy-MM-dd");
    }
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_makeReservationButton_clicked();
    void on_viewCurrentReceiptButton_clicked();
    void on_viewOrderHistoryButton_clicked();

private:
    Ui::MainWindow *ui;
    QList<Booking> currentBookings;
};



#endif // MAINWINDOW_H
