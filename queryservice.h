/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: queryservice.h
 * Description: QueryService类的头文件。该类在设备连接后后台启动查
 * 询服务，以维持Lidar状态实时显示。
 * Version: 1.0
 ************************************************************/
#ifndef QUERYSERVICE_H
#define QUERYSERVICE_H

#include <QObject>
#include <QTimer>

class QueryService : public QObject
{
    Q_OBJECT
public:
    explicit QueryService(QObject *parent = 0);         //构造函数
    ~QueryService();                                    //析构函数
    void disable();                                     //禁用查询服务

signals:

public slots:
    void timeout();                                     //定时器时间到

private:
    void query();                                       //查询Lidar各个设备的工作状态和参数信息
    QTimer *timer;                                      //定时器，用来定时调用query方法
};

#endif // QUERYSERVICE_H
