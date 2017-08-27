/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: remoteservice.h
 * Description: RemoteService类的头文件。该类实现了单例模式。在选择
 * 了远程模式并连接设备后启动远程服务。该服务作为ss-palm2015和TURNServer
 * 的中转服务。
 * Version: 1.0
 ************************************************************/
#ifndef REMOTESERVICE_H
#define REMOTESERVICE_H

#define SIMULATE

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>

class RemoteService : public QObject
{
    Q_OBJECT
public:
    ~RemoteService();                                   //析构函数
    static RemoteService *getInstance();                //[静态]本类型单例的获取方法
    void startService();                                //启动远程服务
    void stopService();                                 //停止远程服务

signals:
    void connectToServerFailed();                       //连接TURN服务器失败信号
    void connectToServerSucceed();                      //连接TURN服务器成功信号

public slots:
    void readPendingDatagrams();                        //读ss-palm2015发来的命令字符串
    void tcpSocketConnected();                          //同TURNServer连接建立
    void tcpSocketError(QAbstractSocket::SocketError);  //同TURNServer连接出错
    void tcpReadyRead();                                //读TURNServer发来的命令字符串

private:
    QString turnIP;                                     //TURN服务器地址
    RemoteService(QObject *parent = 0);                 //构造函数
    static RemoteService *remoteService;                //[静态]本类型单例
    QUdpSocket udpSocket;                               //与ss-palm2015的命令通道
    QTcpSocket tcpSocket;                               //与TURN服务器的命令通道
};

#endif // REMOTESERVICE_H
