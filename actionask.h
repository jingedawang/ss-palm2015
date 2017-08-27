/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: actionask.h
 * Description: 查询动作，继承自Action类。未包含任何参数。
 * Version: 1.0
 ************************************************************/
#ifndef ACTIONASK_H
#define ACTIONASK_H

#include <QObject>
#include "action.h"

class ActionASK : public Action
{
public:
    ActionASK();                                        //构造函数
    ~ActionASK();                                       //析构函数

    virtual QString toString();                         //[虚函数]使用内部已赋值的参数生成字符串
    virtual void notify();                              //[虚函数]触发所有更新过的参数的Changed信号
};

#endif // ACTIONASK_H
