/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: actionstp.h
 * Description: 停止动作，继承自Action类。包含imu和gps两个参数。
 * Version: 1.0
 ************************************************************/
#ifndef ACTIONSTP_H
#define ACTIONSTP_H

#include <QObject>
#include "action.h"

class ActionSTP : public Action
{
public:
    ActionSTP();                                        //构造函数
    ~ActionSTP();                                       //析构函数

    void setStpimu();                                   //设置stpimu参数
    void setStpgps();                                   //设置stpgps参数

    virtual QString toString();                         //[虚函数]使用内部已赋值的参数生成字符串
    virtual void notify();                              //[虚函数]触发所有更新过的参数的Changed信号

private:
    QString str;                                        //已赋值的参数字符串
};

#endif // ACTIONSTP_H
