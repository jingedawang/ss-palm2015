/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: main.qml
 * Description: 软件主界面，使用TabView布局，共有5个Tab。
 * Version: 1.0
 ************************************************************/
import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1

Window {
    visible: true
    width: 800
    height: 500
    property real dpi: Screen.pixelDensity.toFixed(2);
    property string lightgreen: "#80c342";

    TabView {
        id: tabView;
        property var icons1: ["images/images/DeviceConnect1.png", "images/images/Settings1.png", "images/images/Status1.png", "images/images/Advance1.png", "images/images/Diagnosis1.png"];
        property var icons2: ["images/images/DeviceConnect2.png", "images/images/Settings2.png", "images/images/Status2.png", "images/images/Advance2.png", "images/images/Diagnosis2.png"];
        anchors.centerIn: parent;
        anchors.fill: parent;
        tabPosition: Qt.BottomEdge;
        style: TabViewStyle {
            tab: Item {
                implicitWidth: tabView.width / tabView.count;
                implicitHeight: 50;

                Rectangle {
                    //顶部分隔线
                    width: (styleData.index < control.count - 1) ? (parent.width - 1) : parent.width;
                    height: 1;
                    anchors.top: parent.top;
                    anchors.left: parent.left;
                    visible: !styleData.selected;
                    color: "lightgray";
                }
                Rectangle {
                    //tab实体
                    id: rectaaa;
                    width: (styleData.index < control.count - 1) ? (parent.width - 1) : parent.width;
                    height: parent.height - 3;
                    anchors.top: parent.top;
                    anchors.left: parent.left;
                    anchors.topMargin: 1;
                    anchors.leftMargin: 1;
                    color: "white";
                    Column {
                        anchors.centerIn: parent;
                        Image {
                            anchors.horizontalCenter: parent.horizontalCenter;
                            height: rectaaa.height / 2;
                            width: height;
                            source: styleData.selected ? tabView.icons2[styleData.index] : tabView.icons1[styleData.index];
                        }
                        Text {
                            anchors.top: ;
                            anchors.horizontalCenter: parent.horizontalCenter;
                            text: styleData.title;
                            color: styleData.selected ? lightgreen : "black";
                        }
                    }
                }
                Rectangle {
                    //右侧分隔线
                    width: 1;
                    height: parent.height;
                    anchors.top: parent.top;
                    anchors.right: parent.right;
                    visible: styleData.index < control.count - 1;
                    color: "lightgray";
                }
                Rectangle {
                    //底部颜色线
                    width: (styleData.index < control.count - 1) ? (parent.width - 1) : parent.width;
                    height: 2;
                    anchors.bottom: parent.bottom;
                    anchors.left: parent.left;
                    color: "green";
                    visible: styleData.selected;
                }
            }
            tabBar: Rectangle {
                id: tabBarId;
                height: 50;
                color: "white";
            }
        }
        Tab {
            id: tabDeviceConnect;
            title: "连接设备";
            active: true;
            anchors.fill: parent;
            anchors.centerIn: parent;
            source: "DeviceConnect.qml";
        }
        Connections {
            target: tabDeviceConnect.item;
            onDeviceConnected: {
                tabSettings.enabled = true;
                tabStatus.enabled = true;
                tabAdvance.enabled = true;
                tabDiagnosis.enabled = true;
            }
            onDeviceDisconnected: {
                tabSettings.enabled = false;
                tabStatus.enabled = false;
                tabAdvance.enabled = false;
                tabDiagnosis.enabled = false;
            }
        }

        Tab {
            id: tabSettings;
            active: true;
            title: "启动设置";
            anchors.fill: parent;
            anchors.centerIn: parent;
            source: "Settings.qml";
            enabled: false;
        }
        Connections {
            target: tabSettings.item;
            onTskStarted: {
                tabAdvance.item.setTskRunning(true);
            }
            onTskStopped: {
                tabAdvance.item.setTskRunning(false);
            }
        }
        Tab {
            id: tabStatus;
            title: "状态信息";
            active: true;
            anchors.fill: parent;
            anchors.centerIn: parent;
            source: "Status.qml";
            enabled: false;
        }
        Tab {
            id: tabAdvance;
            title: "高级选项";
            active: true;
            anchors.fill: parent;
            anchors.centerIn: parent;
            source: "Advance.qml";
            enabled: false;
        }
        Connections {
            target: tabAdvance.item;
            onUcmStarted: {
                tabSettings.item.setUcmRunning(true);
            }
            onUcmStopped: {
                tabSettings.item.setUcmRunning(false);
            }
        }
        Tab {
            id: tabDiagnosis;
            title: "故障诊断";
            active: true;
            anchors.fill: parent;
            anchors.centerIn: parent;
            source: "Diagnosis.qml";
            enabled: false;
        }
    }

}
