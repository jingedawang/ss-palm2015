/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: actionrun.h
 * Description: 启动动作，继承自Action类。包含所有可启动的设备的所有
 * 可设置的参数。
 * Version: 1.0
 ************************************************************/
#ifndef ACTIONRUN_H
#define ACTIONRUN_H

#include <QObject>
#include <QDebug>
#include "action.h"

class ActionRUN : public Action
{
    Q_OBJECT
public:
    ActionRUN(QObject *parent = 0);                     //构造函数
    ~ActionRUN();                                       //析构函数
    void setFreq(int value);                            //设置freq参数
    void setFreq(float value);                          //设置freq参数
    void setPower(int value);                           //设置power参数
    void setM();                                        //设置m参数
    void setM(int value);                               //设置m参数
    void setQ();                                        //设置q参数
    void setRoit(int start, int end);                   //设置roit参数
    void setMin(int value);                             //设置min参数
    void setMax(int value);                             //设置max参数
    void setEcho(int value);                            //设置echo参数
    void setNetFlow();                                  //设置netflow参数
    void setRois(int start, int end);                   //设置rois参数
    void setCmra();                                     //设置cmra参数
    void setCmrb();                                     //设置cmrb参数
    void setCode(unsigned int value);                   //设置code参数
    void setCirc(float value);                          //设置circ参数
    void setRes(int res);                               //设置res参数
    void setAnti();                                     //设置anti参数
    void setA();                                        //设置a参数
    void setStrimu();                                   //设置strimu参数
    void setStrgps();                                   //设置strgps参数
    virtual QString  toString();                        //[虚函数]使用内部已赋值的参数生成字符串

private:
    QString str;                                        //已赋值的参数字符串

};

#endif // ACTIONRUN_H
