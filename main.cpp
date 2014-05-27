#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include "qsnake.h"
#include <QTime>
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qsrand(QTime::currentTime().msec());
    qmlRegisterType<QSnake>("QGameModule", 1, 0, "QSnake");
    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/QGameApp/main.qml"));
    viewer.showExpanded();


    return app.exec();
}
