#include "server.h"

Server::Server(QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
        audioFile = file.readAll();
    }
}

void Server::start(quint16 port)
{
    this->listen(QHostAddress::Any, port);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket* socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    clientSocket = socket;

    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::sendFile);
}

void Server::sendFile()
{
    qDebug() << "Read file";
    clientSocket->write(audioFile);
}
