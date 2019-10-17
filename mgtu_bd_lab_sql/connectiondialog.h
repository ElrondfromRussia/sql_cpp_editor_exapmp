#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>

#include "ui_connectiondialog.h"
class ConnectionDialog : public QDialog // класс для окошка подключения к базе
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();
    //геттеры аттрибутов
    QString driverName() const;
    QString databaseName() const;
    QString userName() const;
    QString password() const;
    QString hostName() const;
    int port() const;

private slots:
    void on_btn_accept_clicked(); // обработчик нажатия на кнопку "accept"
    void on_btn_cancel_clicked(); // обработчик нажатия на кнопку "cancel"
    void fill_fields(); // заполнить аттрибуты

private:
    Ui::ConnectionDialog *ui; // форма
    //аттрибуты для подключения, по геттерам понятно, что есть что
    QString uN;
    QString dbN;
    QString drN;
    int portN;
    QString psw;
    QString hN;
};

#endif // CONNECTIONDIALOG_H
