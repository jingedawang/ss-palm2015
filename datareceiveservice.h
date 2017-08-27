/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: datareceiveservice.h
 * Description: DataReceiveService类的头文件。该类提供了本地模式下
 * 存储IMP文件的一系列方法。该类作为服务类，在设备连接后后台启动。
 * Version: 1.0
 ************************************************************/
#ifndef DATARECEIVESERVICE_H
#define DATARECEIVESERVICE_H

#include <QObject>
#include <QLinkedList>
#include <QTimer>
#include <QFile>
#include <QMutex>

class DataReceiveService : public QObject
{
    Q_OBJECT
public:
    explicit DataReceiveService(QObject *parent = 0);   //构造函数
    ~DataReceiveService();                              //析构函数

signals:
    void fileHeaderFilled();                            //文件头接收完毕信号
    void slowDataBytesFilled();                         //慢数据接收完毕信号
    void fastDataBytesFilled();                         //快数据接收完毕信号

public slots:
    void tcp1DataReceived(QByteArray bytes);            //文件头数据到达
    void tcp2DataReceived(QByteArray bytes);            //慢数据到达
    void tcp3DataReceived(QByteArray bytes);            //快数据到达
    void writeToFile();                                 //写文件头
    void writeSlowData();                               //写慢数据
    void writeFastData();                               //写快数据

private:
    QByteArray *fileHeader;                             //文件头数据
    QLinkedList<QByteArray *> slowDataBytesList;        //慢数据缓存列表
    QLinkedList<QByteArray *> fastDataBytesList;        //快数据缓存列表
    static const int fileHeaderSize = 24 * 1024;        //文件头大小
    static const int slowDataSize = 16 * 1024 * 1024;   //慢数据大小
    static const int fastDataSize = 128 * 1024 * 1024 - slowDataSize - fileHeaderSize;
                                                        //快数据大小
    QString dirPath;                                    //文件目录
    QTimer timer;                                       //文件头写入用定时器
    QList<QFile *> fileList;                            //文件列表
    int fileHeaderCount;                                //记录已写入文件头的次数
    int slowCount;                                      //记录已写入慢数据的次数
    int fastCount;                                      //记录已写入快数据的次数
    QMutex mutex;                                       //线程锁
};

#endif // DATARECEIVESERVICE_H
