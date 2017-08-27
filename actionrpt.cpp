#include <QStringList>
#include <QDebug>
#include "actionrpt.h"

ActionRPT::ActionRPT()
{
    //环境参数
    gpsTypeReady = false;
    gpsxReady = false;
    gpsyReady = false;
    gpszReady = false;
    utcReady = false;
    sutcReady = false;
    incxReady = false;
    incyReady = false;
    tempAReady = false;
    tempBReady = false;
    hemiAReady = false;
    hemiBReady = false;
    altitudeReady = false;
    airspeedReady = false;
    //设备状态报告
    rangMinReady = false;
    rangMaxReady = false;
    refMinReady = false;
    refMaxReady = false;
    dataSpeedReady = false;
    dataTotalReady = false;
    impSizeReady = false;
    mechStateReady = false;
    //PALM相机反馈
    f1Ready = false;
    f2Ready = false;
    f3Ready = false;
    f4Ready = false;
    f5Ready = false;
    f6Ready = false;
    tcReady = false;
    //PALM数据传输
    dmiCountReady = false;
    sateReady = false;
    ppsReady = false;
    imuReady = false;
    gpsDataReady = false;
    //故障状态查询（适用于所有设备）
    stateReady = false;
}

ActionRPT::~ActionRPT()
{

}

void ActionRPT::setFromQString(QList<QString> list)
{
    for(int i=0; i<list.length(); i++)
    {
        QString str = list.at(i);
        QStringList strList = str.split("=");
        QString argName = strList.at(0).mid(1);
        //环境参数
        if(argName == "gpsType")
        {
            gpsType = strList.at(1).toInt();
            gpsTypeReady = true;
        }
        else if(argName == "gpsx")
        {
            gpsx = strList.at(1).toFloat();
            gpsxReady = true;
        }
        else if(argName == "gpsy")
        {
            gpsy = strList.at(1).toFloat();
            gpsyReady = true;
        }
        else if(argName == "gpsz")
        {
            gpsz = strList.at(1).toFloat();
            gpszReady = true;
        }
        else if(argName == "utc")
        {
            utc = strList.at(1).toULong();
            utcReady = true;
        }
        else if(argName == "sutc")
        {
            sutc = strList.at(1).toULong();
            sutcReady = true;
        }
        else if(argName == "incx")
        {
            incx = strList.at(1).toFloat();
            incxReady = true;
        }
        else if(argName == "incy")
        {
            incy = strList.at(1).toFloat();
            incyReady = true;
        }
        else if(argName == "tempA")
        {
            tempA = strList.at(1).toFloat();
            tempAReady = true;
        }
        else if(argName == "tempB")
        {
            tempB = strList.at(1).toFloat();
            tempBReady = true;
        }
        else if(argName == "hemiA")
        {
            hemiA = strList.at(1).toFloat();
            hemiAReady = true;
        }
        else if(argName == "hemiB")
        {
            hemiB = strList.at(1).toFloat();
            hemiBReady = true;
        }
        else if(argName == "altitude")
        {
            altitude = strList.at(1).toShort();
            altitudeReady = true;
        }
        else if(argName == "airspeed")
        {
            airspeed = strList.at(1).toUShort();
            airspeedReady = true;
        }
        //设备状态报告
        else if(argName == "rangMin")
        {
            rangMin = strList.at(1).toFloat();
            rangMinReady = true;
        }
        else if(argName == "rangMax")
        {
            rangMax = strList.at(1).toFloat();
            rangMaxReady = true;
        }
        else if(argName == "refMin")
        {
            refMin = strList.at(1).toInt();
            refMinReady = true;
        }
        else if(argName == "refMax")
        {
            refMax = strList.at(1).toInt();
            refMaxReady = true;
        }
        else if(argName == "dataSpeed")
        {
            dataSpeed = strList.at(1).toFloat();
            dataSpeedReady = true;
        }
        else if(argName == "dataTotal")
        {
            dataTotal = strList.at(1).toFloat();
            dataTotalReady = true;
        }
        else if(argName == "impSize")
        {
            impSize = strList.at(1).toFloat();
            impSizeReady = true;
        }
        //PALM相机反馈
        else if(argName == "f1")
        {
            f1 = strList.at(1).toUInt();
            f1Ready = true;
        }
        else if(argName == "f2")
        {
            f2 = strList.at(1).toUInt();
            f2Ready = true;
        }
        else if(argName == "f3")
        {
            f3 = strList.at(1).toUInt();
            f3Ready = true;
        }
        else if(argName == "f4")
        {
            f4 = strList.at(1).toUInt();
            f4Ready = true;
        }
        else if(argName == "f5")
        {
            f5 = strList.at(1).toUInt();
            f5Ready = true;
        }
        else if(argName == "f6")
        {
            f6 = strList.at(1).toUInt();
            f6Ready = true;
        }
        else if(argName == "tc")
        {
            tc = strList.at(1).toUInt();
            tcReady = true;
        }
        //PALM数据传输
        else if(argName == "dmiCount")
        {
            dmiCount = strList.at(1).toULong();
            dmiCountReady = true;
        }
        else if(argName == "sate")
        {
            sate = strList.at(1).toUShort();
            sateReady = true;
        }
        else if(argName == "pps")
        {
            pps = true;
            ppsReady = true;
        }
        else if(argName == "imuSync")
        {
            imu = true;
            imuReady = true;
        }
        else if(argName == "imuData")
        {
            imu = true;
            imuReady = true;
        }
        else if(argName == "gpsData")
        {
            gpsData = true;
            gpsDataReady = true;
        }
        //故障状态查询（适用于所有设备）
        else if(argName == "ready")
        {
            state = "ready";
            stateReady = true;
        }
        else if(argName == "working")
        {
            state = "working";
            stateReady = true;
        }
        else if(argName == "error")
        {
            state = "error";
            stateReady = true;
        }
    }
}

void ActionRPT::notify()
{
    //环境参数
    if(gpsTypeReady)
    {
        emit gpsTypeChanged(gpsType);
        gpsTypeReady = false;
    }
    if(gpsxReady)
    {
        emit gpsxChanged(gpsx);
        gpsxReady = false;
    }
    if(gpsyReady)
    {
        emit gpsyChanged(gpsy);
        gpsyReady = false;
    }
    if(gpszReady)
    {
        emit gpszChanged(gpsz);
        gpszReady = false;
    }
    if(utcReady)
    {
        emit utcChanged(utc);
        utcReady = false;
    }
    if(sutcReady)
    {
        emit sutcChanged(sutc);
        sutcReady = false;
    }
    if(incxReady)
    {
        emit incxChanged(incx);
        incxReady = false;
    }
    if(incyReady)
    {
        emit incyChanged(incy);
        incyReady = false;
    }
    if(tempAReady)
    {
        emit tempAChanged(tempA);
        tempAReady = false;
    }
    if(tempBReady)
    {
        emit tempBChanged(tempB);
        tempBReady = false;
    }
    if(hemiAReady)
    {
        emit hemiAChanged(hemiA);
        hemiAReady = false;
    }
    if(hemiBReady)
    {
        emit hemiBChanged(hemiB);
        hemiBReady = false;
    }
    if(altitudeReady)
    {
        emit altitudeChanged(altitude);
        altitudeReady = false;
    }
    if(airspeedReady)
    {
        emit airspeedChanged(airspeed);
        airspeedReady = false;
    }
    //设备状态报告
    if(rangMinReady)
    {
        emit rangMinChanged(rangMin);
        rangMinReady = false;
    }
    if(rangMaxReady)
    {
        emit rangMaxChanged(rangMax);
        rangMaxReady = false;
    }
    if(refMinReady)
    {
        emit refMinChanged(refMin);
        refMinReady = false;
    }
    if(refMaxReady)
    {
        emit refMaxChanged(refMax);
        refMaxReady = false;
    }
    if(dataSpeedReady)
    {
        emit dataSpeedChanged(dataSpeed);
        dataSpeedReady = false;
    }
    if(dataTotalReady)
    {
        emit dataTotalChanged(dataTotal);
        dataTotalReady = false;
    }
    if(impSizeReady)
    {
        emit impSizeChanged(impSize);
        impSizeReady = false;
    }
    //PALM相机反馈
    if(f1Ready)
    {
        emit f1Changed(f1);
        f1Ready = false;
    }
    if(f2Ready)
    {
        emit f2Changed(f2);
        f2Ready = false;
    }
    if(f3Ready)
    {
        emit f3Changed(f3);
        f3Ready = false;
    }
    if(f4Ready)
    {
        emit f4Changed(f4);
        f4Ready = false;
    }
    if(f5Ready)
    {
        emit f5Changed(f5);
        f5Ready = false;
    }
    if(f6Ready)
    {
        emit f6Changed(f6);
        f6Ready = false;
    }
    if(tcReady)
    {
        emit tcChanged(tc);
        tcReady = false;
    }
    //PALM数据传输
    if(dmiCountReady)
    {
        emit dmiCountChanged(dmiCount);
        dmiCountReady = false;
    }
    if(sateReady)
    {
        emit sateChanged(sate);
        sateReady = false;
    }
    if(ppsReady)
    {
        emit ppsChanged(pps);
        ppsReady = false;
    }
    if(imuReady)
    {
        emit imuChanged(imu);
        imuReady = false;
    }
    if(gpsDataReady)
    {
        emit gpsDataChanged(gpsData);
        gpsDataReady = false;
    }
    //故障状态查询（适用于所有设备）
    if(stateReady)
    {
        emit stateChanged(state);
        stateReady = false;
    }
}
