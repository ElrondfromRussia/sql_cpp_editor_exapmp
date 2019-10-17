#include "connectiondialog.h"
#include "ui_connectiondialog.h"

#include <QtSql>
#include <QMessageBox>


ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    QStringList drivers = QSqlDatabase::drivers();
    //drivers.removeAll("QMYSQL3");
    //drivers.removeAll("QOCI8");
    //drivers.removeAll("QODBC3");
    //drivers.removeAll("QPSQL7");
    //drivers.removeAll("QTDS7");

    ui->driver_b->addItems(drivers);

    QPixmap pixmap("cont\\12.png");
        pixmap.scaled(ui->label_pic->size().width(),ui->label_pic->size().height(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
        ui->label_pic->setPixmap(pixmap);

}

ConnectionDialog::~ConnectionDialog()
{

}

////////////////////////////
///Секция геттеров
QString ConnectionDialog::driverName() const
{
    return this->drN;
}
QString ConnectionDialog::databaseName() const
{
    return this->dbN;
}
QString ConnectionDialog::userName() const
{
    return this->uN;
}
QString ConnectionDialog::password() const
{
    return this->psw;
}
QString ConnectionDialog::hostName() const
{
    return this->hN;
}
int ConnectionDialog::port() const
{
    return this->portN;
}
///////////////////////////////////////


void ConnectionDialog::fill_fields()
{
    this->portN = ui->port_box->value();
    this->drN = ui->driver_b->currentText();
    this->dbN = ui->dbn_edit->text();
    this->psw = ui->pswd_edit->text();
    this->hN = ui->hn_edit->text();
    this->uN = ui->un_edit->text();
}

void ConnectionDialog::on_btn_accept_clicked()
{
    if (ui->driver_b->currentText().isEmpty())
    {
        QMessageBox::information(this, tr("No database driver selected"),
                                 tr("Please select a database driver"));
        ui->driver_b->setFocus();
    }
    else
    {
        fill_fields();
        accept();
    }
}

void ConnectionDialog::on_btn_cancel_clicked()
{
    reject();
}
