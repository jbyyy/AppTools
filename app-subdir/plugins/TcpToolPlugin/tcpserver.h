#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServerPrivate;
class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = nullptr);

public slots:
    void onSendMessage(const QByteArray&, const QString &clientInfo = QString(""));

signals:
    void errorMessage(const QString&);
    void newClientInfo(const QString&);
    void disconnectClientInfo(const QString&);
    void clientMessage(const QString&, const QByteArray&);

private slots:
    void onAcceptError();
    void onNewConnect();
    void onClientError(QAbstractSocket::SocketError);
    void onClientDisconnect();
    void onClientReadyRead();

private:
    void buildConnect();

    TcpServerPrivate* d;
};

#endif // TCPSERVER_H