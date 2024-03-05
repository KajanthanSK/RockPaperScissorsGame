#ifndef PLAYER1CONTROLLER_H
#define PLAYER1CONTROLLER_H

//QT
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Player1Controller: public QObject
{
    Q_OBJECT
public:
    explicit Player1Controller(int port, QObject *parent = nullptr);
    bool isStarted() const;
    void sendToAll(QString message);

private slots:
    void onClientConnecting();
    void clientDisconnected();
    void clientDataReady();

signals:
    void newClientConnected();
    void clientDisconnect();
    void dataReceived(QString message);

private:
    QTcpServer* server;
    bool started;
    QList<QTcpSocket *> socketsList;
};

#endif // PLAYER1CONTROLLER_H
