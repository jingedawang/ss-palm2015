/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: actionbrk.h
 * Description: 暂停动作，继承自Action类。未包含任何参数。
 * Version: 1.0
 ************************************************************/
#ifndef ACTIONBRK_H
#define ACTIONBRK_H

#include <QObject>
#include <action.h>

class ActionBRK : public Action
{
public:
    ActionBRK();                                        //构造函数
    ~ActionBRK();                                       //析构函数
    virtual QString toString();                         //[虚函数]使用内部已赋值的参数生成字符串
    virtual void notify();                              //[虚函数]触发所有更新过的参数的Changed信号
};

#endif // ACTIONBRK_H
