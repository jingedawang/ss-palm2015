/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: commandmanager.h
 * Description: CommandManager类的头文件。该类实现了单例模式，提供
 * 创建命令的createCommand方法和解析字符串命令的parseCommand方法。
 * Version: 1.0
 ************************************************************/
#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>
#include "command.h"
#include "device.h"

class CommandManager : public QObject
{
    Q_OBJECT

public:
    ~CommandManager();                                  //析构函数

    static CommandManager* getInstance();               //[静态]本类型单例的获取方法
    Command* createCommand(Device* device);             //使用device创建Command对象，内部调用Command对象的setDevice方法
    QList<Command*>* parseCommand(QString parseStr);    //解析字符串命令，内部调用Command::fromQString方法

private:
    static CommandManager *commandManager;              //[静态]本类型单例
    CommandManager(QObject *parent = 0);                //构造函数
};

#endif // COMMANDMANAGER_H
