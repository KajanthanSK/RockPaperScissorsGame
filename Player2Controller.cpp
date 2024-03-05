#include "Player2Controller.h"


Player2Controller::Player2Controller(QObject* parent):QObject{parent}
{
    connect(&socket, &QTcpSocket::connected, this, &Player2Controller::connected);
    connect(&socket, &QTcpSocket::readyRead, this, &Player2Controller::receiveMessage);
    connect(&socket, &QTcpSocket::disconnected, this, &Player2Controller::disconnected);
}

Player2Controller::~Player2Controller()
{

}

void Player2Controller::connectToDevice(QString ipAddress, int portNum)
{
    if (socket.isOpen()) {
        if (ip == ipAddress && port == portNum) {
            return;
        }
        socket.close();
    }
    ip = ipAddress;
    port = portNum;
    socket.connectToHost(ip, port);
}

void Player2Controller::send(QString message)
{
    socket.write(message.toUtf8());
}

void Player2Controller::receiveMessage()
{
    QString data = socket.readAll();
    emit dataReady(data);
}

bool Player2Controller::isConnected()
{
    return socket.state() == QAbstractSocket::ConnectedState;
}

void Player2Controller::disconnect()
{
    socket.close();
}
