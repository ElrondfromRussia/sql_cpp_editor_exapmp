#ifndef DATABASE_WIDGET_H
#define DATABASE_WIDGET_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include "ui_database_widget.h"
#include <QSqlError>

class TreeWidget;
QT_FORWARD_DECLARE_CLASS(QTableView)
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QTextEdit)
QT_FORWARD_DECLARE_CLASS(QSqlError)


class Database_Widget : public QWidget, private Ui::Database_Widget // класс основной формы для работы с базами
{
    Q_OBJECT

public:
    Database_Widget(QWidget *parent = 0); //конструктор
    virtual ~Database_Widget();

    QSqlError addConnection(const QString &driver, const QString &dbName, const QString &host,
                  const QString &user, const QString &passwd, int port = -1); //добавления подключения со свойствами


    void statusMessage(const QString &message); //вывод текста в историю
    void exit_ask(); //подтверждение выхода по нажатию на esc
    void updateActions(); //обновить

public slots:
    void exec(); // отправка запроса базе

    void addConnection(); // добавить соединение с базой

    void on_btn_submit_clicked(); // обработка нажатия на "submit"
    void on_btn_clear_ask_clicked(); // очистка поля запросов
    void on_btn_clear_hist_clicked(); // очистка истории
    void on_btn_add_nc_clicked(); // добавить новое подключение

    void showMetaData(const QString &table); // показать свойста таблицы
    void showTable(const QString &table); // показать таблицу

    void currentChanged(); // надо понять, как это рабоатет в примере и сделать свой вариант

private:


private slots:
    void keyPressEvent(QKeyEvent * pressedKey); //обработка нажатий на клавиши

    void on_treeView_tableActivated(const QString &table) //обработка двойного клика на таблицу в дереве
    { showTable(table); }                                   // ну или выбора "show table" в меню пкм
    void on_treeView_metaDataRequested(const QString &table) //обработка запроса свойств таблицы в меню пкм
    { showMetaData(table); }

};


class CModel: public QSqlRelationalTableModel //класс для выделения измененных ячеек в таблице
{
    Q_OBJECT
public:
    explicit CModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase()):QSqlRelationalTableModel(parent, db) {}
    QVariant data(const QModelIndex &idx, int role) const Q_DECL_OVERRIDE
    {
        if (role == Qt::BackgroundRole && isDirty(idx))
            return QBrush(QColor(Qt::green));
        return QSqlRelationalTableModel::data(idx, role);
    }
};

#endif // DATABASE_WIDGET_H
