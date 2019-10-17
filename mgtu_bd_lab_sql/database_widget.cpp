#include "database_widget.h"
#include "connectiondialog.h"
#include "ui_database_widget.h"
#include <QtWidgets>
#include <QtSql>


Database_Widget::Database_Widget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    if (QSqlDatabase::drivers().isEmpty())
        QMessageBox::information(this, tr("No database drivers found"),
                                 tr("This demo requires at least one Qt database driver. "
                                    "Please check the documentation how to build the "
                                    "Qt SQL plugins."));
    statusMessage(tr("Ready."));

    table->setAutoScroll(true); // some things with design of the table
    table->verticalHeader()->hide();

    pushButton->hide();

    QFont font_for_table("Arial", 13, 1, false);
    font_for_table.setBold(true);
    table->horizontalHeader()->setFont(font_for_table);

    QPalette header_palette(Qt::blue);
    table->horizontalHeader()->setPalette(header_palette);

    QPixmap pixmap("cont\\12.png"); // picture with a unihorn))))
    pixmap.scaled(flow_lbl->size().width(),flow_lbl->size().height(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
    flow_lbl->setPixmap(pixmap);
}

Database_Widget::~Database_Widget()
{

}

QSqlError Database_Widget::addConnection(const QString &driver, const QString &dbName, const QString &host, const QString &user, const QString &passwd, int port)
{
    QSqlError err;
    QSqlDatabase db = QSqlDatabase::addDatabase(driver); // addition of database
    db.setDatabaseName(dbName);
    statusMessage(tr("__%1__").arg(driver));
    db.setHostName(host); // setting database attributes
    db.setPort(port);
    if (!db.open(user, passwd))
    {
        err = db.lastError();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(db.databaseName());
    }
    treeView->refresh(); // updating of base tree

    return err;
}

void Database_Widget::statusMessage(const QString &message)
{
    hist_Edit->append(message);
}

void Database_Widget::exit_ask()
{
    if(QMessageBox::question(this, tr("Exit"),
                             tr("Close application?"),
                             QMessageBox::Yes,
                             QMessageBox::No|QMessageBox::Default|QMessageBox::Escape)
            == QMessageBox::Yes)
        exit(0);
}

void Database_Widget::updateActions() // пока не трогаем
{
        QSqlTableModel * tm = qobject_cast<QSqlTableModel *>(table->model());
////        bool enableIns = tm;
////        bool enableDel = enableIns && table->currentIndex().isValid();

//    //    insertRowAction->setEnabled(enableIns);
//    //    deleteRowAction->setEnabled(enableDel);

//        fieldStrategyAction->setEnabled(tm);
//        rowStrategyAction->setEnabled(tm);
//        manualStrategyAction->setEnabled(tm);
//        submitAction->setEnabled(tm);
//        revertAction->setEnabled(tm);
//    //    selectAction->setEnabled(tm);

//        if (tm)
//        {
//            QSqlTableModel::EditStrategy es = tm->editStrategy();
//            fieldStrategyAction->setChecked(es == QSqlTableModel::OnFieldChange);
//            rowStrategyAction->setChecked(es == QSqlTableModel::OnRowChange);
//            manualStrategyAction->setChecked(es == QSqlTableModel::OnManualSubmit);
//        }


    // Здесь лучше, наверное, реализовать механизм занесения изменений в таблице?
    // То есть, на основе измененных элементов таблицы составлять запросы к базе данны
    // И с помощью QSqlQueryModel отправлять его базе
}

void Database_Widget::exec()
{
    QSqlQueryModel *model = new QSqlQueryModel(table); // с помощью этого
                                    //осуществляется отправка нашего запроса бд, по сути
    if(!ask_Edit->toPlainText().isEmpty())
    {
        model->setQuery(QSqlQuery(ask_Edit->toPlainText(), treeView->currentDatabase()));
        table->setModel(model);
        statusMessage(tr("Operation: %1").arg(ask_Edit->toPlainText()));
        if (model->lastError().type() != QSqlError::NoError)
            emit statusMessage(model->lastError().text());
        else if (model->query().isSelect())
            statusMessage(tr("Query OK."));
        else
            statusMessage(tr("Query OK, number of affected rows: %1").arg(
                              model->query().numRowsAffected()));
        //updateActions();
    }
    else
    {
        statusMessage(tr("Enter SOMETHING!"));
    }
}

void Database_Widget::addConnection()
{
    ConnectionDialog dialog(this); // тут открывается диалог соединения
    if (dialog.exec() != QDialog::Accepted)
        return;


    QSqlError err = addConnection(dialog.driverName(), dialog.databaseName(), dialog.hostName(),
                                  dialog.userName(), dialog.password(), dialog.port());
    if (err.type() != QSqlError::NoError)
        QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while "
                                                                     "opening the connection: ") + err.text());
}

void Database_Widget::keyPressEvent(QKeyEvent *pressedKey)
{
    switch (pressedKey->key())
    {
    case Qt::Key_F1:
        on_btn_add_nc_clicked();
        break;
    case Qt::Key_F2:
        on_btn_submit_clicked();
        break;
    case Qt::Key_F3:
        on_btn_clear_ask_clicked();
        break;
    case Qt::Key_F4:
        on_btn_clear_hist_clicked();
        break;
    case Qt::Key_Escape:
        exit_ask();
        break;
    }
}

void Database_Widget::on_btn_submit_clicked()
{
    exec();
    ask_Edit->setFocus();
}

void Database_Widget::on_btn_clear_ask_clicked()
{
    exec();
    ask_Edit->setFocus();
}

void Database_Widget::on_btn_clear_hist_clicked()
{
    hist_Edit->clear();
}

void Database_Widget::on_btn_add_nc_clicked()
{
    addConnection();
}

void Database_Widget::showMetaData(const QString &t)
{
    QSqlRecord rec = treeView->currentDatabase().record(t);
    QStandardItemModel *model = new QStandardItemModel(table);

    model->insertRows(0, rec.count());
    model->insertColumns(0, 7);

    model->setHeaderData(0, Qt::Horizontal, "Fieldname");
    model->setHeaderData(1, Qt::Horizontal, "Type");
    model->setHeaderData(2, Qt::Horizontal, "Length");
    model->setHeaderData(3, Qt::Horizontal, "Precision");
    model->setHeaderData(4, Qt::Horizontal, "Required");
    model->setHeaderData(5, Qt::Horizontal, "AutoValue");
    model->setHeaderData(6, Qt::Horizontal, "DefaultValue");


    for (int i = 0; i < rec.count(); ++i)
    {
        QSqlField fld = rec.field(i);
        model->setData(model->index(i, 0), fld.name());
        model->setData(model->index(i, 1), fld.typeID() == -1
                       ? QString(QMetaType::typeName(fld.type()))
                       : QString("%1 (%2)").arg(QMetaType::typeName(fld.type())).arg(fld.typeID()));
        model->setData(model->index(i, 2), fld.length());
        model->setData(model->index(i, 3), fld.precision());
        model->setData(model->index(i, 4), fld.requiredStatus() == -1 ? QVariant("?")
                                                                      : QVariant(bool(fld.requiredStatus())));
        model->setData(model->index(i, 5), fld.isAutoValue());
        model->setData(model->index(i, 6), fld.defaultValue());
    }

    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //updateActions();
}

void Database_Widget::showTable(const QString &t)
{
    QSqlRelationalTableModel *model = new CModel(table, treeView->currentDatabase());
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->setTable(treeView->currentDatabase().driver()->escapeIdentifier(t, QSqlDriver::TableName));
    model->select();
    if (model->lastError().type() != QSqlError::NoError)
        statusMessage(model->lastError().text());
    table->setModel(model);
    table->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);

    connect(table->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
              this, SLOT(currentChanged()));
    //updateActions();
}

void Database_Widget::currentChanged()
{
    updateActions();
}

