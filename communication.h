/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: communication.h
 * Description: Communication类的头文件。该类提供使用IP地址和端口的
 * 构造方法，发送命令方法，和收到数据信号。
 * Version: 1.0
 ************************************************************/
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>

class Communication : public QObject
{
    Q_OBJECT
public:
    explicit Communication(QString lidarIP = "192.168.0.188", bool isRemoteMode=false, int listenUdpPort = 11110, int listenTcpPort1=11111, int listenTcpPort2=11112, int listenTcpPort3=11113, QObject* parent = 0);
                                                        //构造函数
    ~Communication();                                   //析构函数

    void sendCommand(QString command);                  //发送命令
    QString getLidarIP();                               //获取LidarIP

public slots:
    void readPendingDatagrams();                        //读命令消息
    void tcp1Connected();                               //文件头通道已连接
    void tcp2Connected();                               //慢数据通道已连接
    void tcp3Connected();                               //快数据通道已连接
    void readTcp1();                                    //读文件头数据
    void readTcp2();                                    //读慢数据
    void readTcp3();                                    //读快数据

signals:
    void dataReceived(QString msg);                     //接收到命令信号
    void tcp1DataReceived(QByteArray bytes);            //接收到文件头数据信号
    void tcp2DataReceived(QByteArray bytes);            //接收到慢数据信号
    void tcp3DataReceived(QByteArray bytes);            //接收到快数据信号

private:
    QUdpSocket* udpSocket;                              //命令通道
    QTcpSocket* tcpSocket1;                             //文件头数据通道
    QTcpSocket* tcpSocket2;                             //慢数据通道
    QTcpSocket* tcpSocket3;                             //快数据通道
    QString lidarIP;                                    //Lidar地址
    int lidarUdpPort;                                   //Lidar命令端口
    static const int lidarTcpPort1 = 2011;              //Lidar文件头数据端口
    static const int lidarTcpPort2 = 2012;              //Lidar慢数据端口
    static const int lidarTcpPort3 = 2009;              //Lidar快数据端口
    int listenUdpPort;                                  //命令监听端口
    int listenTcpPort1;                                 //文件头数据监听端口
    int listenTcpPort2;                                 //慢数据监听端口
    int listenTcpPort3;                                 //快数据监听端口
    bool LidarConnected;                                //Lidar已连接标志
    bool GPSConnected;                                  //GPS已连接标志
    bool IMUConnected;                                  //IMU已连接标志
    bool isRemoteMode;                                  //远程模式标志
};

#endif // COMMUNICATION_H
