#include <QApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString filename = "D:/1.wav";

    Server* server = new Server(filename);
    server->start(1234);

    return a.exec();
}
