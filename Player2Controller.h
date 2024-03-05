#ifndef PLAYER2CONTROLLER_H
#define PLAYER2CONTROLLER_H

//QT
#include <QObject>
#include <QTcpSocket>

class Player2Controller:public QObject
{
    Q_OBJECT
public:
    explicit Player2Controller(QObject* parent=nullptr);
    ~Player2Controller();
    void connectToDevice(QString ip,int port);
    void send(QString message);
    bool isConnected();
    void disconnect();

signals:
    void connected();
    void readyRead();
    void dataReady(QString);
    void disconnected();

private: //QTcpServer
    QTcpSocket socket;
    QString ip;
    int port;

private slots:   //Methods
    void receiveMessage();
};

#endif // PLAYER2CONTROLLER_H
