#include <QApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir dir = QDir::currentPath() + "/audio/";
    QStringList dirContent = dir.entryList(QStringList() << "*.wav", QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

    QVector<QString> filenames = dirContent.toVector();

    Server* server = new Server(filenames);
    server->start(1234);

    return a.exec();
}
