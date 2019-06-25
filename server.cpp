#include "server.h"

Server::Server(QVector<QString> filenames)
{    
    for (int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        QFile file("D:/DevQt/LizaAudioTransfer/AudioTransferServer/audio/" + filename);
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray data = file.readAll();
            audioFiles.insert(filename, data);
        }
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

    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readData);
}

void Server::readData()
{
    QByteArray data = clientSocket->readAll();
    sendFile(QString(data));
}

void Server::sendFile(QString data)
{
    clientSocket->write(audioFiles[data]);
}
