#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
QT_FORWARD_DECLARE_CLASS(QTreeWidget)
QT_FORWARD_DECLARE_CLASS(QTreeWidgetItem)
QT_FORWARD_DECLARE_CLASS(QSqlDatabase)
QT_FORWARD_DECLARE_CLASS(QMenu)

class TreeWidget : public QWidget // класс для отображения иерархии текущей базы
{
    Q_OBJECT
public:
    TreeWidget(QWidget *parent = 0); // конструктор
    virtual ~TreeWidget();

    QSqlDatabase currentDatabase() const; // получение текущей базы

signals:
    void tableActivated(const QString &table); // обработчик активации-выбора определенной таблицы
    void metaDataRequested(const QString &tableName); // обработчик запроса мета-данных

public slots:
    void refresh();// обновить
    void showMetaData(); // показать мета-данные по таблице в базе (свойства таблицы)

private slots:
    void setActive(QTreeWidgetItem *item); //условно говоря, выделение текущей открытой таблицы
    void on_tree_itemActivated(QTreeWidgetItem *item, int column); // обработчик нажатия на определенную таблицу
    void on_tree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous); //обработчик изменения

private:
    QTreeWidget *tree; //дерево базы
    QAction *metaDataAction; //событие мета-данных
    QString activeDb; //имя текущей базы
};

#endif // TREEWIDGET_H
