/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: DeviceConnect.qml
 * Description: “连接设备”界面。
 * Version: 1.0
 ************************************************************/
import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: deviceConnect;
    implicitHeight: 100;
    implicitWidth: 300;
    property string fontWeiruanyahei: "微软雅黑";
    property real dpi: Screen.pixelDensity.toFixed(2);
    property string lightgreen: "#80c342";
    property string lightgreenTransparent: "#ff80c342";
    signal deviceConnected();
    signal deviceDisconnected();
    Image {
        source: "images/images/background.png"
        anchors.fill: parent;
    }
    Image {
        width: 120 * dpi;
        fillMode: Image.PreserveAspectFit
        anchors.centerIn: parent;
        source: "images/images/ss-palm2015.png";
    }
    Text {
        anchors.top: parent.top;
        anchors.topMargin: 30 * dpi;
        anchors.horizontalCenter: parent.horizontalCenter;
        font.family: fontWeiruanyahei;
        font.pixelSize: 10 * dpi;
        color: "white";
        text: "激光雷达控制诊断及处理系统";
    }

    MyToast {
        id:myToast
        z:10//显示在其他控件之上，保证能看见，无需设置其高度和宽度
        interval:1000//显示时间
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 30 * dpi;
    }
    TextField {
        id: txtinputLidarName;
        anchors.right: chkIsRemote.left;
        anchors.verticalCenter: chkIsRemote.verticalCenter;
        width: 40 * dpi;
        placeholderText: "Lidar名称";
    }
    TextField {
        id: txtinputLidarPassword;
        anchors.top: txtinputLidarName.bottom;
        anchors.horizontalCenter: txtinputLidarName.horizontalCenter;
        width: 40 * dpi;
        placeholderText: "密码";
    }

    CheckBox {
        id: chkIsRemote;
        anchors.right: rectConnect.left;
        anchors.rightMargin: 5 * dpi;
        anchors.verticalCenter: rectConnect.verticalCenter;
        style: CheckBoxStyle {
            label: Text {
                text: "远程模式";
                color: "white";
            }
        }
    }

    ColorAnimation {
        id: animation
    }
    Rectangle {
        id: rectLidar;
        width: 20 * dpi;
        height: 20 * dpi;
        anchors.right: rectGps.left;
        anchors.rightMargin: 1 * dpi;
        anchors.bottom: rectImu.bottom;
        radius: 10 * dpi;
        state: "ready";
        border.width: 1 * dpi;
        states: [
            State {
                name: "ready";
                PropertyChanges {
                    target: rectLidar;
                    color: "lightgray";
                    border.color: "lightgray";
                    enabled: false;
                }
            },
            State {
                name: "connected";
                PropertyChanges {
                    target: rectLidar;
                    color: lightgreen;
                    border.color: lightgreen;
                    enabled: true;
                }
            }
        ]
        MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onHoveredChanged: {
                if(containsMouse === true)
                {
                    deviceConnect.rectColorToTransparent(rectLidar);
                }
                else
                {
                    deviceConnect.rectColorToLightgreen(rectLidar);
                }
            }
            Text {
                anchors.centerIn: parent;
                font.family: fontWeiruanyahei;
                color: "white";
                text: "Lidar";
            }
        }
    }
    Rectangle {
        id: rectGps;
        width: 20 * dpi;
        height: 20 * dpi;
        anchors.right: rectImu.left;
        anchors.rightMargin: 1 * dpi;
        anchors.bottom: rectImu.bottom;
        radius: 10 * dpi;
        border.width: 1 * dpi;
        state: "ready";
        states: [
            State {
                name: "ready";
                PropertyChanges {
                    target: rectGps;
                    color: "lightgray";
                    border.color: "lightgray";
                    enabled: false;
                }
            },
            State {
                name: "connected";
                PropertyChanges {
                    target: rectGps;
                    color: lightgreen;
                    border.color: lightgreen;
                    enabled: true;
                }
            }
        ]
        MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onHoveredChanged: {
                if(containsMouse === true)
                {
                    deviceConnect.rectColorToTransparent(rectGps);
                }
                else
                {
                    deviceConnect.rectColorToLightgreen(rectGps);
                }
            }
            Text {
                anchors.centerIn: parent;
                font.family: fontWeiruanyahei;
                color: "white";
                text: "GPS";
            }
        }
    }
    Rectangle {
        id: rectImu;
        width: 20 * dpi;
        height: 20 * dpi;
        anchors.right: parent.right;
        anchors.rightMargin: 10 * dpi;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5 * dpi;
        radius: 10 * dpi;
        border.width: 1 * dpi;
        state: "ready";
        states: [
            State {
                name: "ready";
                PropertyChanges {
                    target: rectImu;
                    color: "lightgray";
                    border.color: "lightgray";
                    enabled: false;
                }
            },
            State {
                name: "connected";
                PropertyChanges {
                    target: rectImu;
                    color: lightgreen;
                    border.color: lightgreen;
                    enabled: true;
                }
            }
        ]
        MouseArea {
            anchors.fill: parent;
            hoverEnabled: true;
            onHoveredChanged: {
                if(containsMouse === true)
                {
                    deviceConnect.rectColorToTransparent(rectImu);
                }
                else
                {
                    deviceConnect.rectColorToLightgreen(rectImu);
                }
            }
            Text {
                anchors.centerIn: parent;
                font.family: fontWeiruanyahei;
                color: "white";
                text: "IMU";
            }
        }
    }

    Connections {
        target: uiAdapter;
        onConnectToServerFailed: {
            myToast.showToast("连接服务器失败，请重试");
        }
        onConnectToServerSucceed: {
            myToast.showToast("成功连接服务器");
        }
    }
    ColorAnimation {
        id: colorAnimationToTransparent;
        property: "color";
        to: "#00ffffff";
        duration: 200;
    }
    ColorAnimation {
        id: colorAnimationToLightgreen;
        property: "color";
        to: lightgreen;
        duration: 200;
    }
    function rectColorToTransparent(target)
    {
        colorAnimationToTransparent.target = target;
        colorAnimationToTransparent.start();
    }
    function rectColorToLightgreen(target)
    {
        colorAnimationToLightgreen.target = target;
        colorAnimationToLightgreen.start();
    }
    Rectangle {
        id: rectConnect;
        width: 60 * dpi;
        height: 20 * dpi;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 20 * dpi;
        anchors.horizontalCenter: parent.horizontalCenter;
        color: lightgreen;
        border.color: lightgreen;
        border.width: 1 * dpi;
        radius: 15 * dpi;
        state: "ready";
        states: [
            State {
                name: "connected";
                PropertyChanges {
                    target: txtConnect;
                    text: "断开设备";
                }
            },
            State {
                name: "ready";
                PropertyChanges {
                    target: txtConnect;
                    text: "连接设备";
                }
            }
        ]
        MouseArea {
            id: mouseArea;
            hoverEnabled: true;
            anchors.fill: parent;
            Text {
                id: txtConnect;
                text: "连接设备";
                color: mouseArea.containsMouse ? lightgreen : "white";
                font.family: fontWeiruanyahei;
                anchors.centerIn: parent;
            }
            onClicked: {
                if(rectConnect.state === "ready")
                {
                    rectConnect.state = "connected";
                    rectLidar.state = "connected";
                    rectGps.state = "connected";
                    rectImu.state = "connected";
                    deviceConnected();                              //通知主界面
                    uiAdapter.identify(txtinputLidarName.text);
                    uiAdapter.connectDevice(chkIsRemote.checked);
                    messageReceiveService.enable();
                    chkIsRemote.enabled = false;
                }
                else if(rectConnect.state === "connected")
                {
                    rectConnect.state = "ready";
                    rectLidar.state = "ready";
                    rectGps.state = "ready";
                    rectImu.state = "ready";
                    deviceDisconnected();                           //通知主界面
                    messageReceiveService.disable();
                    uiAdapter.disconnectDevice(chkIsRemote.checked);
                    chkIsRemote.enabled = true;
                }
            }
            onHoveredChanged: {
                if(containsMouse === true)
                {
                    deviceConnect.rectColorToTransparent(rectConnect);
                }
                else
                {
                    deviceConnect.rectColorToLightgreen(rectConnect);
                }
            }
        }

    }
}

