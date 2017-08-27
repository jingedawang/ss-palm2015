/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: messagereceiveservice.h
 * Description: MessageReceiveService类的头文件。该类在设备连接后
 * 后台启动消息接收服务，用于接收来自Lidar的消息，处理后发信号通知界面。
 * Version: 1.0
 ************************************************************/
#ifndef MESSAGERECEIVESERVICE_H
#define MESSAGERECEIVESERVICE_H

#include <QObject>

class MessageReceiveService : public QObject
{
    Q_OBJECT
public:
    explicit MessageReceiveService(QObject *parent = 0);//构造函数
    ~MessageReceiveService();                           //析构函数

    Q_INVOKABLE void enable();                          //使能消息接收服务
    Q_INVOKABLE void disable();                         //禁用消息接收服务

signals:
    /* 环境参数 */
    void envGpsTypeChanged(int gpsType);                //GPS类型更新信号
    void envGpsxChanged(float gpsx);                    //纬度更新信号
    void envGpsyChanged(float gpsy);                    //经度更新信号
    void envGpszChanged(float gpsz);                    //海拔更新信号
    void envUtcChanged(unsigned long utc);              //UTC时间（年月日）更新信号
    void envSutcChanged(unsigned long sutc);            //UTC时间（秒）更新信号
    void envIncxChanged(float incx);                    //倾角仪x轴更新信号
    void envIncyChanged(float incy);                    //倾角仪y轴更新信号
    void envTempAChanged(float tempA);                  //温度传感器A更新信号
    void envTempBChanged(float tempB);                  //温度传感器B更新信号
    void envHemiAChanged(float hemiA);                  //湿度传感器A更新信号
    void envHemiBChanged(float hemiB);                  //湿度传感器B更新信号
    void envAltitudeChanged(short altitude);            //气压高度更新信号
    void envAirspeedChanged(unsigned short airspeed);   //空速更新信号
    /* 设备状态报告 */
    void ldrRangMinChanged(float rangMin);              //距离最小值更新信号
    void ldrRangMaxChanged(float rangMax);              //距离最大值更新信号
    void ldrRefMinChanged(float refMin);                //强度最小值更新信号
    void ldrRefMaxChanged(float refMax);                //强度最大值更新信号
    void ldrDataSpeedChanged(float dataSpeed);          //速率更新信号
    void ldrDataTotalChanged(float dataTotal);          //数据总量更新信号
    void ldrImpSizeChanged(float impSize);              //当前IMP大小更新信号
    /* PALM相机反馈 */
    void pcmF1Changed(unsigned int f1);                 //相机1反馈个数更新信号
    void pcmF2Changed(unsigned int f2);                 //相机2反馈个数更新信号
    void pcmF3Changed(unsigned int f3);                 //相机3反馈个数更新信号
    void pcmF4Changed(unsigned int f4);                 //相机4反馈个数更新信号
    void pcmF5Changed(unsigned int f5);                 //相机5反馈个数更新信号
    void pcmF6Changed(unsigned int f6);                 //相机6反馈个数更新信号
    void pcmTcChanged(unsigned int tc);                 //相机触发个数更新信号
    /* PALM数据传输 */
    void pdtDmiCountChanged(unsigned long dmiCount);    //dmi里程数更新信号
    void pdtGpsTypeChanged(int gpsType);                //GPS类型更新信号
    void pdtSutcChanged(unsigned long sutc);            //UTC时间（秒）更新信号
    void pdtSateChanged(unsigned short sate);           //卫星数更新信号
    void pdtPpsChanged(bool pps);                       //PPS同步更新信号
    void pdtImuChanged(bool imu);                       //imu时间同步和数据传输状态更新信号
    void pdtGpsDataChanged(bool gpsData);               //GPS数据传输状态更新信号
    /* 故障状态查询（适用于所有设备） */
    void tskStateChanged(QString state);                //数据采集作业故障状态更新信号
    void cmrStateChanged(QString state);                //外置相机故障状态更新信号
    void stgStateChanged(QString state);                //转台电机故障状态更新信号
    void scnStateChanged(QString state);                //扫描电机故障状态更新信号
    void lsrStateChanged(QString state);                //激光器故障状态更新信号
    void ucmStateChanged(QString state);                //USB相机故障状态更新信号
    void pcmStateChanged(QString state);                //PALM相机故障状态更新信号
    void pdtStateChanged(QString state);                //PALM数据传输故障状态更新信号

public slots:
    void messageReceived(QString message);              //接收到消息字符串
};

#endif // MESSAGERECEIVESERVICE_H
