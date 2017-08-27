/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: communicationmanager.h
 * Description: CommunicationManager类的头文件。该类实现了单例模式，
 * 提供了使用地址创建Communication对象的方法，获取已创建的Communication
 * 对象的方法，以及进入或退出远程模式的方法。
 * Version: 1.0
 ************************************************************/
#ifndef COMMUNICATIONMANAGER_H
#define COMMUNICATIONMANAGER_H

#include <QObject>
#include <QList>
#include "communication.h"

class CommunicationManager : public QObject
{
    Q_OBJECT
public:
    ~CommunicationManager();                            //析构函数

    static CommunicationManager *getInstance();         //[静态]本类型单例的获取方法
    Communication *createCommunication(QString IP);     //使用给定的IP获得Communication对象
    Communication *getCommunication();                  //获取已创建的Communication对象
    void enterRemoteMode();                             //进入远程模式
    void quitRemoteMode();                              //退出远程模式
    void deleteCommunication();                         //删除已创建的Communication对象

private:
    CommunicationManager(QObject *parent = 0);          //构造函数
    static CommunicationManager *manager;               //[静态]本类型单例
    QList<Communication *> communicationList;           //保存本地连接的Communication列表
    QList<Communication *> remoteCommunicationList;     //保存远程连接的Communication列表
    bool remoteMode;                                    //远程模式标志
};

#endif // COMMUNICATIONMANAGER_H
