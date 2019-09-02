#include "server.h"

Server::Server(QVector<QString> filenames)
{    
    for (int i = 0; i < filenames.size(); i++)
    {
        QString filename = filenames[i];
        QFile file(QDir::currentPath() + "/audio/" + filename);
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray data = file.readAll();
            audioFiles.insert(filename, data);
        }
    }
}

void Server::start(quint16 port)
{
    if (this->listen(QHostAddress("92.42.26.61"), port))
    {
        qDebug() << "Сервер прослушивает соединения по порту" << port;
    }
    else
    {
        qDebug() << "Ошибка!" << this->errorString();
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "Новое подключение";

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
        clientSocket->waitForBytesWritten();
    }
    else
    {
        qDebug() << "Не найден файл с именем" << data;
        qDebug() << "Отправляю cообщение об отсутствии файла";
        clientSocket->write(QByteArray("File doesn't exist"));
        clientSocket->waitForBytesWritten();
    }
}
