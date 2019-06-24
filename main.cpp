#include <QApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString filenames = "D:/1.wav";

    Server* server = new Server(filenames);
    server->start(1234);

    return a.exec();
}
