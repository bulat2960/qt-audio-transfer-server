#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QMap>
#include <QDir>

class Server : public QTcpServer
{
private:
    QTcpSocket* clientSocket;
    QMap<QString, QByteArray> audioFiles;
public:
    Server(QVector<QString> filenames);
    void start(quint16 port);
public slots:
    void sendFile(QString data);
    void readData();
protected slots:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // SERVER_H
