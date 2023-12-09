#ifndef RESERVATIONDIALOG_H
#define RESERVATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ReservationDialog;
}

class ReservationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReservationDialog(QWidget *parent = nullptr);
    ~ReservationDialog();

    QString getName() const;
    QString getPhoneNumber() const;
    QString getRoomType() const;
    int getRoomNumber() const;
    QDate getStartDate() const;
    QDate getEndDate() const;

private slots:
    void on_submitButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::ReservationDialog *ui;
};

#endif // RESERVATIONDIALOG_H
