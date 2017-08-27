/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: Status.qml
 * Description: “状态信息”界面。
 * Version: 1.0
 ************************************************************/
import QtQuick 2.0
import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3
import QtQuick.Window 2.0

Rectangle {
    property real dpi: Screen.pixelDensity.toFixed(2);
    property string fontWeiruanyahei: "微软雅黑";
    property string lightgreen: "#80c342";
    Rectangle {
        id: rectHeader;
        width: parent.width;
        anchors.top: parent.top;
        anchors.bottom: tableStatus.top;
        color: lightgreen;
        Text {
            anchors.centerIn: parent;
            text: "状态信息列表";
            font.family: fontWeiruanyahei;
        }
    }
    TableView {
        id: tableStatus;
        anchors.fill: parent;
        anchors.topMargin: 30 * dpi;
        selectionMode: SelectionMode.NoSelection;
        TableViewColumn {
            role: "name";
            title: "Name";
            width: parent.width / 2;
            elideMode: Text.ElideRight;
            resizable: false;
        }
        TableViewColumn {
            role: "value";
            title: "Value";
            width: parent.width / 2;
            elideMode: Text.ElideRight;
            resizable: false;
        }
        headerDelegate: Rectangle {
            height: 0;
        }
        model: ListModel {
            id: modelStatus;
            function getIndexFromId(id)
            {
                for(var i=0; i<count; i++)
                    if(id === get(i).id)
                    {
                        return i;
                    }
                return -1;
            }
            //环境参数
            ListElement {
                name: "环境参数";
                value: "";
            }
            ListElement {
                property string id: "envGpsType";
                name: "GPS类型";
                value: "";
            }
            ListElement {
                property string id: "envGpsx";
                name: "纬度";
                value: "";
            }
            ListElement {
                property string id: "envGpsy";
                name: "经度";
                value: "";
            }
            ListElement {
                property string id: "envGpsz";
                name: "海拔";
                value: "";
            }
            ListElement {
                property string id: "envUtc";
                name: "utc时间";
                value: "";
            }
            ListElement {
                property string id: "envIncx";
                name: "倾角仪x轴";
                value: "";
            }
            ListElement {
                property string id: "envIncy";
                name: "倾角仪y轴";
                value: "";
            }
            ListElement {
                property string id: "envTempA";
                name: "温度传感器A";
                value: "";
            }
            ListElement {
                property string id: "envTempB";
                name: "温度传感器B";
                value: "";
            }
            ListElement {
                property string id: "envHemiA";
                name: "湿度传感器A";
                value: "";
            }
            ListElement {
                property string id: "envHemiB";
                name: "湿度传感器B";
                value: "";
            }
            ListElement {
                property string id: "envAltitude";
                name: "气压高度";
                value: "";
            }
            ListElement {
                property string id: "envAirspeed";
                name: "空速";
                value: "";
            }
            //设备状态报告
            ListElement {
                property string id: "ldrRangMin";
                name: "距离最小值";
                value: "";
            }
            ListElement {
                property string id: "ldrRangMax";
                name: "距离最大值";
                value: "";
            }
            ListElement {
                property string id: "ldrRefMin";
                name: "强度最小值";
                value: "";
            }
            ListElement {
                property string id: "ldrRefMax";
                name: "强度最大值";
                value: "";
            }
            ListElement {
                property string id: "ldrDataSpeed";
                name: "速率";
                value: "";
            }
            ListElement {
                property string id: "ldrDataTotal";
                name: "数据总量";
                value: "";
            }
            ListElement {
                property string id: "ldrImpSize";
                name: "当前IMP大小";
                value: "";
            }
            //PALM相机反馈
            ListElement {
                property string id: "pcmF1";
                name: "相机1反馈个数";
                value: "";
            }
            ListElement {
                property string id: "pcmF2";
                name: "相机2反馈个数";
                value: "";
            }
            ListElement {
                property string id: "pcmF3";
                name: "相机3反馈个数";
                value: "";
            }
            ListElement {
                property string id: "pcmF4";
                name: "相机4反馈个数";
                value: "";
            }
            ListElement {
                property string id: "pcmF5";
                name: "相机5反馈个数";
                value: "";
            }
            ListElement {
                property string id: "pcmF6";
                name: "相机6反馈个数";
                value: "";
            }
            ListElement {
                property string id: "pcmTc";
                name: "相机触发个数";
                value: "";
            }
            //PALM数据传输
            ListElement {
                property string id: "pdtDmiCount";
                name: "dmi里程数";
                value: "";
            }
            ListElement {
                property string id: "pdtGpsType";
                name: "GPS类型";
                value: "";
            }
            ListElement {
                property string id: "pdtSutc";
                name: "UTC时间（周秒）";
                value: "";
            }
            ListElement {
                property string id: "pdtSate";
                name: "卫星数";
                value: "";
            }
            ListElement {
                property string id: "pdtPps";
                name: "PPS同步";
                value: "";
            }
            ListElement {
                property string id: "pdtImu";
                name: "IMU同步";
                value: "";
            }
            ListElement {
                property string id: "pdtGpsData";
                name: "GPS状态";
                value: "";
            }
        }
    }

    Connections {
        target: messageReceiveService;
        ////环境参数
        onEnvGpsTypeChanged: {
            if(modelStatus.getIndexFromId("envGpsType") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envGpsType"), "value", getGpsType(gpsType));
        }
        onEnvGpsxChanged: {
            if(modelStatus.getIndexFromId("envGpsx") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envGpsx"), "value", gpsx.toFixed(2));
        }
        onEnvGpsyChanged: {
            if(modelStatus.getIndexFromId("envGpsy") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envGpsy"), "value", gpsy.toFixed(2));
        }
        onEnvGpszChanged: {
            if(modelStatus.getIndexFromId("envGpsz") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envGpsz"), "value", gpsz.toFixed(2));
        }
        onEnvUtcChanged: {
            if(modelStatus.getIndexFromId("envUtc") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envUtc"), "value", utc.toString());
        }
        onEnvSutcChanged: {
            if(modelStatus.getIndexFromId("envSutc") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envSutc"), "value", sutc.toString());
        }
        onEnvIncxChanged: {
            if(modelStatus.getIndexFromId("envIncx") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envIncx"), "value", incx.toFixed(2));
        }
        onEnvIncyChanged: {
            if(modelStatus.getIndexFromId("envIncy") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envIncy"), "value", incy.toFixed(2));
        }
        onEnvTempAChanged: {
            if(modelStatus.getIndexFromId("envTempA") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envTempA"), "value", tempA.toFixed(2));
        }
        onEnvTempBChanged: {
            if(modelStatus.getIndexFromId("envTempB") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envTempB"), "value", tempB.toFixed(2));
        }
        onEnvHemiAChanged: {
            if(modelStatus.getIndexFromId("envHemiA") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envHemiA"), "value", hemiA.toFixed(2));
        }
        onEnvHemiBChanged: {
            if(modelStatus.getIndexFromId("envHemiB") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envHemiB"), "value", hemiB.toFixed(2));
        }
        onEnvAltitudeChanged: {
            if(modelStatus.getIndexFromId("envAltitude") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envAltitude"), "value", altitude.toString());
        }
        onEnvAirspeedChanged: {
            if(modelStatus.getIndexFromId("envAirspeed") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("envAirspeed"), "value", airspeed.toString());
        }
        //设备状态报告
        onLdrRangMinChanged: {
            if(modelStatus.getIndexFromId("ldrRangMin") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("ldrRangMin"), "value", rangMin.toFixed(2));
        }
        onLdrRangMaxChanged: {
            if(modelStatus.getIndexFromId("ldrRangMax") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("ldrRangMax"), "value", rangMax.toFixed(2));
        }
        onLdrRefMinChanged: {
            if(modelStatus.getIndexFromId("ldrRefMin") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("ldrRefMin"), "value", refMin.toFixed(2));
        }
        onLdrRefMaxChanged: {
            if(modelStatus.getIndexFromId("ldrRefMax") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("ldrRefMax"), "value", refMax.toFixed(2));
        }
        onLdrDataSpeedChanged: {
            if(modelStatus.getIndexFromId("ldrDataSpeed") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("ldrDataSpeed"), "value", dataSpeed.toFixed(2));
        }
        onLdrDataTotalChanged: {
            if(modelStatus.getIndexFromId("ldrDataTotal") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("ldrDataTotal"), "value", dataTotal.toFixed(2));
        }
        onLdrImpSizeChanged: {
            if(modelStatus.getIndexFromId("ldrImpSize") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("ldrImpSize"), "value", impSize.toFixed(2));
        }
        //PALM相机反馈
        onPcmF1Changed: {
            if(modelStatus.getIndexFromId("pcmF1") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pcmF1"), "value", f1.toString());
        }
        onPcmF2Changed: {
            if(modelStatus.getIndexFromId("pcmF2") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pcmF2"), "value", f2.toString());
        }
        onPcmF3Changed: {
            if(modelStatus.getIndexFromId("pcmF3") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pcmF3"), "value", f3.toString());
        }
        onPcmF4Changed: {
            if(modelStatus.getIndexFromId("pcmF4") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pcmF4"), "value", f4.toString());
        }
        onPcmF5Changed: {
            if(modelStatus.getIndexFromId("pcmF5") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pcmF5"), "value", f5.toString());
        }
        onPcmF6Changed: {
            if(modelStatus.getIndexFromId("pcmF6") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pcmF6"), "value", f6.toString());
        }
        onPcmTcChanged: {
            if(modelStatus.getIndexFromId("pcmTc") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pcmTc"), "value", tc.toString());
        }
        //PALM数据传输
        onPdtDmiCountChanged: {
            if(modelStatus.getIndexFromId("pdtDmiCount") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pdtDmiCount"), "value", dmiCount.toString());
        }
        onPdtGpsTypeChanged: {
            if(modelStatus.getIndexFromId("pdtGpsType") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pdtGpsType"), "value", getGpsType(gpsType));
        }
        onPdtSutcChanged: {
            if(modelStatus.getIndexFromId("pdtSutc") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pdtSutc"), "value", sutc.toString());
        }
        onPdtSateChanged: {
            if(modelStatus.getIndexFromId("pdtSate") !== -1)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pdtSate"), "value", sate.toString());
        }
        onPdtPpsChanged: {
            if(pps === true)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pdtPps"), "value", "正常");
            else
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pdtPps"), "value", "不正常");
        }
        onPdtImuChanged: {
            if(imu === true)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pdtImu"), "value", "正常");
            else
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pdtImu"), "value", "不正常");
        }
        onPdtGpsDataChanged: {
            if(gpsData === true)
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pdtGpsData"), "value", "正常");
            else
                tableStatus.model.setProperty(modelStatus.getIndexFromId("pdtGpsData"), "value", "不正常");
        }
    }
    function getGpsType(gpsType)
    {
        switch (gpsType)
        {
        case 0:
            return "applanix";
        case 1:
            return "trimble";
        case 2:
            return "noval";
        case 3:
            return "javat";
        case 4:
            return "nmea";
        case 5:
            return "Gsof";
        case 6:
            return "Inpps";
        }
    }
}

