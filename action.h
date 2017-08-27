/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: action.h
 * Description: 所有动作的基类，它的每一个派生类代表激光雷达外设的一个
 * 可能执行的动作，如启动、停止或查询。
 * Version: 1.0
 ************************************************************/
#ifndef ACTION_H
#define ACTION_H

#include <QObject>

class Action : public QObject
{
    Q_OBJECT

public:
   Action(QObject *parent = 0);                         //构造函数
   ~Action();                                           //析构函数

   virtual QString toString();                          //[虚函数]使用内部已赋值的参数生成字符串
   static Action *fromQString(QString actionName);      //[静态]使用actionName字符串构造Action对象
   virtual void setFromQString(QList<QString> list);    //[虚函数]使用list更新参数
   virtual void notify();                               //[虚函数]触发所有更新过的参数的Changed信号
};

#endif // ACTION_H
