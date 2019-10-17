#include "database_widget.h"
#include <QApplication>

#include <QtCore>
#include <QtWidgets>
#include <QtSql>

void addConnectionsFromCommandline(const QStringList &args, Database_Widget *database_widget)
{
    for (int i = 1; i < args.count(); ++i) // тут мы подсоединяемя к бд
    {
        QUrl url(args.at(i), QUrl::TolerantMode);
        if (!url.isValid()) {
            qWarning("Invalid URL: %s", qPrintable(args.at(i)));
            continue;
        }
        QSqlError err = database_widget->addConnection(url.scheme(), url.path().mid(1), url.host(),
                                               url.userName(), url.password(), url.port(-1));
        if (err.type() != QSqlError::NoError)
            qDebug() << "Unable to open connection:" << err;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow mainWin;
    mainWin.setWindowTitle(QObject::tr("Sql creation"));

    Database_Widget w(&mainWin); // всякие штуки для открытия окна и прочие радости, все понятно, вроде, и так
    mainWin.setCentralWidget(&w);
    mainWin.setMinimumHeight(w.height());
    mainWin.setMinimumWidth(w.width());

    addConnectionsFromCommandline(a.arguments(), &w);
    if (QSqlDatabase::connectionNames().isEmpty())
        QMetaObject::invokeMethod(&w, "addConnection", Qt::QueuedConnection);
    mainWin.show();

    return a.exec();
}
