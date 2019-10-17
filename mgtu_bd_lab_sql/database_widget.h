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


class Database_Widget : public QWidget, private Ui::Database_Widget // ����� �������� ����� ��� ������ � ������
{
    Q_OBJECT

public:
    Database_Widget(QWidget *parent = 0); //�����������
    virtual ~Database_Widget();

    QSqlError addConnection(const QString &driver, const QString &dbName, const QString &host,
                  const QString &user, const QString &passwd, int port = -1); //���������� ����������� �� ����������


    void statusMessage(const QString &message); //����� ������ � �������
    void exit_ask(); //������������� ������ �� ������� �� esc
    void updateActions(); //��������

public slots:
    void exec(); // �������� ������� ����

    void addConnection(); // �������� ���������� � �����

    void on_btn_submit_clicked(); // ��������� ������� �� "submit"
    void on_btn_clear_ask_clicked(); // ������� ���� ��������
    void on_btn_clear_hist_clicked(); // ������� �������
    void on_btn_add_nc_clicked(); // �������� ����� �����������

    void showMetaData(const QString &table); // �������� ������� �������
    void showTable(const QString &table); // �������� �������

    void currentChanged(); // ���� ������, ��� ��� �������� � ������� � ������� ���� �������

private:


private slots:
    void keyPressEvent(QKeyEvent * pressedKey); //��������� ������� �� �������

    void on_treeView_tableActivated(const QString &table) //��������� �������� ����� �� ������� � ������
    { showTable(table); }                                   // �� ��� ������ "show table" � ���� ���
    void on_treeView_metaDataRequested(const QString &table) //��������� ������� ������� ������� � ���� ���
    { showMetaData(table); }

};


class CModel: public QSqlRelationalTableModel //����� ��� ��������� ���������� ����� � �������
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
