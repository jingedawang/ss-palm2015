#include "communication.h"

Communication::Communication(QString lidarIP, bool isRemoteMode, int listenUdpPort, int listenTcpPort1, int listenTcpPort2, int listenTcpPort3, QObject *parent) : QObject(parent)
{
    this->lidarIP = lidarIP;
    this->listenUdpPort = listenUdpPort;
    this->listenTcpPort1 = listenTcpPort1;
    this->listenTcpPort2 = listenTcpPort2;
    this->listenTcpPort3 = listenTcpPort3;
    this->isRemoteMode = isRemoteMode;
    if(this->isRemoteMode)
        this->lidarUdpPort = 3013;
    else
        this->lidarUdpPort = 2013;
    this->LidarConnected = false;
    this->GPSConnected = false;
    this->IMUConnected = false;
    udpSocket = new QUdpSocket(this);
    tcpSocket1 = new QTcpSocket(this);
    tcpSocket2 = new QTcpSocket(this);
    tcpSocket3 = new QTcpSocket(this);
    //此处设置监听的IP地址
    udpSocket->bind(QHostAddress::Any, this->listenUdpPort);
    tcpSocket1->bind(QHostAddress::Any, listenTcpPort1);
    tcpSocket2->bind(QHostAddress::Any, listenTcpPort2);
    tcpSocket3->bind(QHostAddress::Any, listenTcpPort3);
    connect(tcpSocket1, SIGNAL(connected()), this, SLOT(tcp1Connected()));
    connect(tcpSocket2, SIGNAL(connected()), this, SLOT(tcp2Connected()));
    connect(tcpSocket3, SIGNAL(connected()), this, SLOT(tcp3Connected()));
    connect(tcpSocket1, SIGNAL(readyRead()), this, SLOT(readTcp1()));
    connect(tcpSocket2, SIGNAL(readyRead()), this, SLOT(readTcp2()));
    connect(tcpSocket3, SIGNAL(readyRead()), this, SLOT(readTcp3()));
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    if(!this->isRemoteMode)
    {
        QHostAddress address(this->lidarIP);
        tcpSocket1->connectToHost(address, this->lidarTcpPort1);
        tcpSocket2->connectToHost(address, this->lidarTcpPort2);
        tcpSocket3->connectToHost(address, this->lidarTcpPort3);
    }
}

Communication::~Communication()
{
    tcpSocket1->disconnectFromHost();
    tcpSocket2->disconnectFromHost();
    tcpSocket3->disconnectFromHost();
    udpSocket->deleteLater();
    tcpSocket1->deleteLater();
    tcpSocket2->deleteLater();
    tcpSocket3->deleteLater();
}
void Communication::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        //socket接收到消息
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        //读取接收到的消息，存入datagram
        udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        QString msg(datagram);
        //发射dataReceived信号，参数为接收到的字符串
        emit dataReceived(msg);
    }
}

void Communication::tcp1Connected()
{
    qDebug() << "tcp1Connected" << endl;
}
void Communication::tcp2Connected()
{
    qDebug() << "tcp2Connected" << endl;
}
void Communication::tcp3Connected()
{
    qDebug() << "tcp3Connected" << endl;
}
void Communication::readTcp1()
{
    if(tcpSocket1->bytesAvailable() > 0)
    {
        QByteArray bytes = tcpSocket1->readAll();
        emit tcp1DataReceived(bytes);
    }
}
void Communication::readTcp2()
{
    if(tcpSocket2->bytesAvailable() > 0)
    {
        QByteArray bytes = tcpSocket2->readAll();
        emit tcp2DataReceived(bytes);
    }
}
void Communication::readTcp3()
{
    if(tcpSocket3->bytesAvailable() > 0)
    {
        QByteArray bytes = tcpSocket3->readAll();
        emit tcp3DataReceived(bytes);
    }
}
void Communication::sendCommand(QString command)
{
    //将command指令发送给指定的LiDar
    QHostAddress address(this->lidarIP);
    udpSocket->writeDatagram(command.toUtf8(), address, this->lidarUdpPort);
}

QString Communication::getLidarIP()
{
    return this->lidarIP;
}
