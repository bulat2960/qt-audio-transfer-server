#include <QApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVector<QString> filenames = {"1.wav", "2.wav", "3.wav"};

    Server* server = new Server(filenames);
    server->start(1234);

    return a.exec();
}
