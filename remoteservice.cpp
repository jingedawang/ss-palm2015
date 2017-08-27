#include "remoteservice.h"

RemoteService::RemoteService(QObject *parent) : QObject(parent)
{
    //在此设置TURN服务器的IP地址
    turnIP = "127.0.0.1";           //本机仿真
//    turnIP = "192.168.0.24";        //局域网仿真
//    turnIP = "122.0.114.220";       //实际，但2015年5月后已停用，请换为可用的服务器
}

RemoteService::~RemoteService()
{

}

RemoteService *RemoteService::getInstance()
{
    if(remoteService == NULL)
    {
        remoteService = new RemoteService();
    }
    return remoteService;
}

void RemoteService::startService()
{
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(tcpSocketConnected()));
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(tcpSocketError(QAbstractSocket::SocketError)));
    tcpSocket.connectToHost(QHostAddress(turnIP), 5555);
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(tcpReadyRead()));
}

void RemoteService::stopService()
{
    disconnect(&tcpSocket, SIGNAL(connected()), this, SLOT(tcpSocketConnected()));
    disconnect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(tcpSocketError(QAbstractSocket::SocketError)));
    tcpSocket.disconnectFromHost();
}

void RemoteService::readPendingDatagrams()
{
    while (udpSocket.hasPendingDatagrams())
    {
        //socket接收到消息
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        //读取接收到的消息，存入datagram
        udpSocket.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        //立即转发给服务器
        tcpSocket.write(datagram);
    }
}

void RemoteService::tcpSocketConnected()
{
    emit connectToServerSucceed();
    udpSocket.bind(QHostAddress::Any, 3013);
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void RemoteService::tcpSocketError(QAbstractSocket::SocketError)
{
    emit connectToServerFailed();
}

void RemoteService::tcpReadyRead()
{

    while(tcpSocket.bytesAvailable())
    {
        QByteArray bytes = tcpSocket.readAll();
        udpSocket.writeDatagram(bytes, QHostAddress::LocalHost, 11110);
    }
}

RemoteService *RemoteService::remoteService = NULL;
