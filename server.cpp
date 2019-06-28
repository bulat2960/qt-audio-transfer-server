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
    qDebug() << "Получен запрос на скачивание файла" << data;
    qDebug() << "Передаю управление отправке файла";
    sendFile(QString(data));
}

void Server::sendFile(QString data)
{
    if (audioFiles.contains(data))
    {

        qDebug() << "Отправляю файл" << data << "размером" << audioFiles[data].size() << "байт";
        clientSocket->write(audioFiles[data]);
    }
    else
    {
        qDebug() << "Не найден файл с именем" << data;
        qDebug() << "Отправляю пустой массив данных";
        clientSocket->write(QByteArray());
    }
}
