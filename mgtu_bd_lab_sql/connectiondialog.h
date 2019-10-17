#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>

#include "ui_connectiondialog.h"
class ConnectionDialog : public QDialog // ����� ��� ������ ����������� � ����
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();
    //������� ����������
    QString driverName() const;
    QString databaseName() const;
    QString userName() const;
    QString password() const;
    QString hostName() const;
    int port() const;

private slots:
    void on_btn_accept_clicked(); // ���������� ������� �� ������ "accept"
    void on_btn_cancel_clicked(); // ���������� ������� �� ������ "cancel"
    void fill_fields(); // ��������� ���������

private:
    Ui::ConnectionDialog *ui; // �����
    //��������� ��� �����������, �� �������� �������, ��� ���� ���
    QString uN;
    QString dbN;
    QString drN;
    int portN;
    QString psw;
    QString hN;
};

#endif // CONNECTIONDIALOG_H
