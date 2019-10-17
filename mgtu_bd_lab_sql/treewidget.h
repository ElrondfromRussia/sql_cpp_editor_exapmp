#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
QT_FORWARD_DECLARE_CLASS(QTreeWidget)
QT_FORWARD_DECLARE_CLASS(QTreeWidgetItem)
QT_FORWARD_DECLARE_CLASS(QSqlDatabase)
QT_FORWARD_DECLARE_CLASS(QMenu)

class TreeWidget : public QWidget // ����� ��� ����������� �������� ������� ����
{
    Q_OBJECT
public:
    TreeWidget(QWidget *parent = 0); // �����������
    virtual ~TreeWidget();

    QSqlDatabase currentDatabase() const; // ��������� ������� ����

signals:
    void tableActivated(const QString &table); // ���������� ���������-������ ������������ �������
    void metaDataRequested(const QString &tableName); // ���������� ������� ����-������

public slots:
    void refresh();// ��������
    void showMetaData(); // �������� ����-������ �� ������� � ���� (�������� �������)

private slots:
    void setActive(QTreeWidgetItem *item); //������� ������, ��������� ������� �������� �������
    void on_tree_itemActivated(QTreeWidgetItem *item, int column); // ���������� ������� �� ������������ �������
    void on_tree_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous); //���������� ���������

private:
    QTreeWidget *tree; //������ ����
    QAction *metaDataAction; //������� ����-������
    QString activeDb; //��� ������� ����
};

#endif // TREEWIDGET_H
