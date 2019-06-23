#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>

class Server : public QTcpServer
{
private:
    QTcpSocket* clientSocket;
    QByteArray audioFile;
public:
    Server(QString filename);
    void start(quint16 port);
public slots:
    void sendFile();
protected slots:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // SERVER_H
