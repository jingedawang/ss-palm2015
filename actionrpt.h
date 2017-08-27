/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: actionrpt.h
 * Description: 报告动作，继承自Action类。包含所有设备的所有可以报告
 * 的参数。
 * Version: 1.0
 ************************************************************/
#ifndef ACTIONRPT_H
#define ACTIONRPT_H

#include <QObject>
#include "action.h"

class ActionRPT : public Action
{
    Q_OBJECT
public:
    ActionRPT();                                        //构造函数
    ~ActionRPT();                                       //析构函数
    virtual void setFromQString(QList<QString> list);   //[虚函数]使用list更新参数
    virtual void notify();                              //[虚函数]触发所有更新过的参数的Changed信号

signals:
    /* 环境参数 */
    void gpsTypeChanged(int gpsType);                   //GPS类型更新信号
    void gpsxChanged(float gpsx);                       //纬度更新信号
    void gpsyChanged(float gpsy);                       //经度更新信号
    void gpszChanged(float gpsz);                       //海拔更新信号
    void utcChanged(unsigned long utc);                 //UTC时间（年月日）更新信号
    void sutcChanged(unsigned long sutc);               //UTC时间（秒）更新信号
    void incxChanged(float incx);                       //倾角仪x轴更新信号
    void incyChanged(float incy);                       //倾角仪y轴更新信号
    void tempAChanged(float tempA);                     //温度传感器A更新信号
    void tempBChanged(float tempB);                     //温度传感器B更新信号
    void hemiAChanged(float hemiA);                     //湿度传感器A更新信号
    void hemiBChanged(float hemiB);                     //湿度传感器B更新信号
    void altitudeChanged(short altitude);               //气压高度更新信号
    void airspeedChanged(unsigned short airspeed);      //空速更新信号
    /* 设备状态报告 */
    void rangMinChanged(float rangMin);                 //距离最小值更新信号
    void rangMaxChanged(float rangMax);                 //距离最大值更新信号
    void refMinChanged(float refMin);                   //强度最小值更新信号
    void refMaxChanged(float refMax);                   //强度最大值更新信号
    void dataSpeedChanged(float dataSpeed);             //速率更新信号
    void dataTotalChanged(float dataTotal);             //数据总量更新信号
    void impSizeChanged(float impSize);                 //当前IMP大小更新信号
    /* PALM相机反馈 */
    void f1Changed(unsigned int f1);                    //相机1反馈个数更新信号
    void f2Changed(unsigned int f2);                    //相机2反馈个数更新信号
    void f3Changed(unsigned int f3);                    //相机3反馈个数更新信号
    void f4Changed(unsigned int f4);                    //相机4反馈个数更新信号
    void f5Changed(unsigned int f5);                    //相机5反馈个数更新信号
    void f6Changed(unsigned int f6);                    //相机6反馈个数更新信号
    void tcChanged(unsigned int tc);                    //相机触发个数更新信号
    /* PALM数据传输 */
    void dmiCountChanged(unsigned long dmiCount);       //dmi里程数更新信号
    void sateChanged(unsigned short sate);              //卫星数更新信号
    void ppsChanged(bool pps);                          //PPS同步更新信号
    void imuChanged(bool imu);                          //imu时间同步和数据传输状态更新信号
    void gpsDataChanged(bool gpsData);                  //GPS数据传输状态更新信号
    /* 故障状态查询（适用于所有设备） */
    void stateChanged(QString state);                   //故障状态更新信号

private:
    /* 环境参数 */
    bool gpsTypeReady;                                  //GPS类型更新标志
    int gpsType;                                        //GPS类型
    bool gpsxReady;                                     //纬度更新标志
    float gpsx;                                         //纬度
    bool gpsyReady;                                     //经度更新标志
    float gpsy;                                         //经度
    bool gpszReady;                                     //海拔更新标志
    float gpsz;                                         //海拔
    bool utcReady;                                      //UTC时间（年月日）更新标志
    unsigned long utc;                                  //UTC时间（年月日）
    bool sutcReady;                                     //UTC时间（秒）更新标志
    unsigned int sutc;                                  //UTC时间（秒）
    bool incxReady;                                     //倾角仪x轴更新标志
    float incx;                                         //倾角仪x轴
    bool incyReady;                                     //倾角仪y轴更新标志
    float incy;                                         //倾角仪y轴
    bool tempAReady;                                    //温度传感器A更新标志
    float tempA;                                        //温度传感器A
    bool tempBReady;                                    //温度传感器B更新标志
    float tempB;                                        //温度传感器B
    bool hemiAReady;                                    //湿度传感器A更新标志
    float hemiA;                                        //湿度传感器A
    bool hemiBReady;                                    //湿度传感器B更新标志
    float hemiB;                                        //湿度传感器B
    bool altitudeReady;                                 //气压高度更新标志
    short altitude;                                     //气压高度
    bool airspeedReady;                                 //空速更新标志
    unsigned short airspeed;                            //空速
    /* 设备状态报告 */
    bool rangMinReady;                                  //距离最小值更新标志
    float rangMin;                                      //距离最小值
    bool rangMaxReady;                                  //距离最大值更新标志
    float rangMax;                                      //距离最大值
    bool refMinReady;                                   //强度最小值更新标志
    int refMin;                                         //强度最小值
    bool refMaxReady;                                   //强度最大值更新标志
    int refMax;                                         //强度最大值
    bool dataSpeedReady;                                //速率更新标志
    float dataSpeed;                                    //速率
    bool dataTotalReady;                                //数据总量更新标志
    float dataTotal;                                    //数据总量
    bool impSizeReady;                                  //当前IMP大小更新标志
    float impSize;                                      //当前IMP大小
    bool mechStateReady;                                //状态信息更新标志
    QString mechState;                                  //状态信息
    /* PALM相机反馈 */
    bool f1Ready;                                       //相机1反馈个数更新标志
    unsigned int f1;                                    //相机1反馈个数
    bool f2Ready;                                       //相机2反馈个数更新标志
    unsigned int f2;                                    //相机2反馈个数
    bool f3Ready;                                       //相机3反馈个数更新标志
    unsigned int f3;                                    //相机3反馈个数
    bool f4Ready;                                       //相机4反馈个数更新标志
    unsigned int f4;                                    //相机4反馈个数
    bool f5Ready;                                       //相机5反馈个数更新标志
    unsigned int f5;                                    //相机5反馈个数
    bool f6Ready;                                       //相机6反馈个数更新标志
    unsigned int f6;                                    //相机6反馈个数
    bool tcReady;                                       //相机触发个数更新标志
    unsigned int tc;                                    //相机触发个数
    /* PALM数据传输 */
    bool dmiCountReady;                                 //dmi里程数更新标志
    unsigned long dmiCount;                             //dmi里程数
    bool sateReady;                                     //卫星数更新标志
    unsigned short sate;                                //卫星数
    bool ppsReady;                                      //PPS同步更新标志
    bool pps;                                           //PPS同步
    bool imuReady;                                      //imu时间同步和数据传输状态更新标志
    bool imu;                                           //imu时间同步和数据传输状态
    bool gpsDataReady;                                  //GPS数据传输状态更新标志
    unsigned short gpsData;                             //GPS数据传输状态
    //故障状态查询（适用于所有设备）
    bool stateReady;                                    //故障状态更新标志
    QString state;                                      //故障状态
};

#endif // ACTIONRPT_H
