/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: uiadapter.h
 * Description: 用于QML界面与C++程序的适配，该类的方法都可以在QML中
 * 调用，以实现控制命令发送。
 * Version: 1.0
 ************************************************************/
#ifndef UIADAPTER_H
#define UIADAPTER_H

#include <QObject>
#include "communicationmanager.h"
#include "commandmanager.h"
#include "datareceiveservice.h"
#include "queryservice.h"

class UIAdapter : public QObject
{
    Q_OBJECT

public:
    explicit UIAdapter(QObject *parent = 0);            //构造函数
    ~UIAdapter();                                       //析构函数

    Q_INVOKABLE void identify(QString name);            //ss-palm2015请求认证Lidar
    Q_INVOKABLE void connectDevice(bool remoteMode);    //连接设备（远程模式或本地模式）
    Q_INVOKABLE void disconnectDevice(bool remoteMode); //断开设备
    Q_INVOKABLE void setGPSConnected(bool value);       //连接GPS
    Q_INVOKABLE void setIMUConnected(bool value);       //连接IMU
    /*
     * 激光器
     */
    Q_INVOKABLE void setLaser(int frequency, int percent, bool isSimulate);
                                                        //以设置的参数启动激光器
    Q_INVOKABLE void askLsr();                          //查询激光器
    /*
     * 扫描电机
     */
    Q_INVOKABLE void setScanner(float speed);           //以设置的参数启动扫描电机
    Q_INVOKABLE void askScn();                          //查询扫描电机
    Q_INVOKABLE void stopScn();                         //停止扫描电机
    /*
     * 转台电机
     */
    Q_INVOKABLE void setStage(int speed, int mode, int roitStart, int roitEnd);
                                                        //以设置的参数启动转台电机
    Q_INVOKABLE void askStg();                          //查询转台电机
    Q_INVOKABLE void stopStg();                         //停止转台电机
    /*
     * 数据采集作业
     */
    Q_INVOKABLE void setTsk(int min, int max, int echoMode, bool mp, bool netflow, int roisStart, int roisEnd, int roitStart, int roitEnd);
                                                        //以设置的参数启动数据采集作业
    Q_INVOKABLE void tskBreak();                        //暂停数据采集作业
    Q_INVOKABLE void tskContinue();                     //继续数据采集作业
    Q_INVOKABLE void askTsk();                          //查询数据采集作业
    Q_INVOKABLE void stop();                            //停止数据采集作业
    /*
     * 外置相机
     */
    Q_INVOKABLE void setCmr(int freq, int cmrMode, int roitStart, int roitEnd);
                                                        //以设置的参数启动外置相机
    Q_INVOKABLE void askCmr();                          //查询外置相机
    Q_INVOKABLE void stopCmr();                         //停止外置相机
    /*
     * USB相机
     */
    Q_INVOKABLE void setUcm(bool mode, int roitStart, int roitEnd, bool cmra, bool cmrb, int freq);
                                                        //以设置的参数启动USB相机
    Q_INVOKABLE void askUcm();                          //查询USB相机
    Q_INVOKABLE void stopUcm();                         //停止USB相机
    /*
     * DMI参数
     */
    Q_INVOKABLE void setDmi(unsigned int code, float circ);
                                                        //设置DMI参数
    /*
     *PALM RT转台
     */
    Q_INVOKABLE void setPst(float freq, bool m, int res, bool direction);
                                                        //以设置的参数启动PALM转台
    Q_INVOKABLE void askPst();                          //查询PALM转台
    Q_INVOKABLE void stopPst();                         //停止PALM转台
    /*
     * PALM相机
     */
    Q_INVOKABLE void setPcm(int freq, int mode);        //以设置的参数启动PALM相机
    Q_INVOKABLE void askPcm();                          //查询PALM相机
    Q_INVOKABLE void stopPcm();                         //停止PALM相机
    /*
     * PALM数据传输
     */
    Q_INVOKABLE void askPdt();                          //查询PALM数据传输
    /*
     * 设备配置信息
     */
    Q_INVOKABLE void askCfg();                          //查询设备配置信息

    Q_INVOKABLE void enterRemoteMode();                 //进入远程模式
    Q_INVOKABLE void quitRemoteMode();                  //退出远程模式

signals:
    void connectToServerFailed();                       //连接TURN服务器失败信号
    void connectToServerSucceed();                      //连接TURN服务器成功信号

private:
    CommunicationManager *communicationManager;         //CommunicationManager对象
    CommandManager *commandManager;                     //CommandManager对象
    QueryService *queryService;                         //QueryService对象
    DataReceiveService *dataReceiveService;             //DataReceiveService对象
    QString lidarIP;                                    //Lidar地址
};

#endif // UIADAPTER_H
