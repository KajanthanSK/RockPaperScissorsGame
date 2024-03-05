#include "Player1Controller.h"

Player1Controller::Player1Controller(int port, QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &Player1Controller::onClientConnecting);
    started = server->listen(QHostAddress::Any, port);
    if(!started)
        qDebug() << "Server could not start";
    else
        qDebug() << "Server started...";


}

bool Player1Controller::isStarted() const
{
    return started;
}

void Player1Controller::sendToAll(QString message)
{
    foreach (auto socket, socketsList)
        socket->write(message.toUtf8());
}

void Player1Controller::onClientConnecting()
{
    qDebug() << "Friend is connected with you!";
    auto socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Player1Controller::clientDataReady);
    connect(socket, &QTcpSocket::disconnected, this, &Player1Controller::clientDisconnected);
    socketsList.append(socket);
    //socket->write("Welcome to Play!");
    emit newClientConnected();
}

void Player1Controller::clientDisconnected()
{
    emit clientDisconnect();
}

void Player1Controller::clientDataReady()
{
    auto socket = qobject_cast<QTcpSocket *>(sender());
    auto data = QString(socket->readAll());
    emit dataReceived(data);
    foreach (auto s, socketsList)
    {
        if (s != socket)
            s->write(data.toUtf8());
    }
}
