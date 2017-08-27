/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: Advance.qml
 * Description: “高级选项”界面。
 * Version: 1.0
 ************************************************************/
import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtQuick.Layouts 1.1

Rectangle {
    property real dpi: Screen.pixelDensity.toFixed(2);
    property string fontWeiruanyahei: "微软雅黑";
    property string lightgreen: "#80c342";
    signal ucmStarted();
    signal ucmStopped();
    Rectangle {
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.right: parent.right;
        anchors.bottom: flick.top;
        color: lightgreen;
        Text {
            anchors.centerIn: parent;
            text: "请设置参数并右滑启动相应设备";
            font.family: fontWeiruanyahei;
        }
        z: 1;
    }
    MyToast
    {
        id:myToast
        z:10//显示在其他控件之上，保证能看见，无需设置其高度和宽度
        interval:1000//显示时间
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 30 * dpi;
    }
    Flickable {
        id: flick;
        width: Qt.platform.os === "android" ? Screen.width : 800;
        height: 80 * dpi - 1;
        anchors.bottom: parent.bottom;
        contentWidth: column.width;
        contentHeight: column.height;

        Column {
            id: column;
            width: parent.width;
            Flickable {
                id: flickPst;
                property string state: "enable";
                width: parent.width;
                contentWidth: rectPst.width;
                height: 20 * dpi;
                Rectangle {
                    id: rectPst;
                    width: flickPst.width + 1;
                    height: 20 * dpi;
                    Image {
                        id: imagePst;
                        width: 20 * dpi;
                        height: 20 * dpi;
                        Label {
                            text: "palm转台";
                            anchors.centerIn: parent;
                            font.family: fontWeiruanyahei;
                        }
                    }
                    Row {
                        anchors.left: imagePst.right;
                        anchors.right: parent.right;
                        anchors.verticalCenter: parent.verticalCenter;
                        Label {
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: qsTr("转台模式");
                        }
                        ComboBox {
                            id: cboPstMode;
                            width: 20 * dpi;
                            model: ListModel {
                                ListElement {
                                    text: "速度模式"
                                }
                                ListElement {
                                    text: "角度模式"
                                }
                            }
                        }
                        Label {
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: qsTr("速度[dps]");
                        }
                        TextField {
                            id: txtPstFreq;
                            width: 20 * dpi;
                            text: "1.0";
                        }
                        Button {
                            id: rotationVelocityAdd;
                            width: 10 * dpi;
                            text: qsTr("+");
                            onClicked: {
                                var str = txtPstFreq.text.toString();
                                var number = parseFloat(str);
                                number = number + 1;
                                txtPstFreq.text = number.toString();
                            }
                        }
                        Button {
                            id: rotationVelocityMinus;
                            width: 10 * dpi;
                            text: qsTr("-");
                            onClicked: {
                                var str = txtPstFreq.text.toString();
                                var number = parseFloat(str);
                                if(number < 1)
                                {
                                    return;
                                }
                                number = number - 1;
                                txtPstFreq.text = number.toString();
                            }
                        }
                        Label {
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: "每个脉冲对应的角度";
                        }
                        TextField {
                            id: txtPstRes;
                            width: 20 * dpi;
                            text: "0";
                        }
                        Label {
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: "方向";
                        }
                        ComboBox {
                            id: cboPstDirection;
                            width: 20 * dpi;
                            model: ListModel {
                                id: cbItems
                                ListElement { text: "正方向"; color: "Yellow" }
                                ListElement { text: "反方向"; color: "Green" }
                            }
                        }
                    }
                }
                onFlickStarted: {
                    if(Math.abs(contentX) > 50 * dpi)
                    {
                        if(contentX > 0)
                        {
                            if(state == "running")
                                state = "enable";
                        }
                        else
                        {
                            if(state == "enable")
                                state = "running";
                        }
                    }
                }
                onStateChanged: {
                    switch (state)
                    {
                    case "enable":
                        rectPst.enabled = true;
                        uiAdapter.stopPst();
                        break;
                    case "running":
                        rectPst.enabled = false;
                        uiAdapter.setPst(parseFloat(txtPstFreq.text), cboPstMode.currentIndex, parseInt(txtPstRes.text), cboPstDirection.currentIndex);
                        break;
                    }
                }
            }
            Rectangle {
                width: parent.width;
                height: 1;
                color: "lightgray";
            }
            Flickable {
                id: flickPcm;
                property string state: "enable";
                width: parent.width;
                contentWidth: rectPcm.width;
                height: 20 * dpi;
                Rectangle {
                    id: rectPcm;
                    width: flickPcm.width + 1;
                    height: 20 * dpi;
                    Image {
                        id: imagePcm;
                        width: 20 * dpi;
                        height: 20 * dpi;
                        Label {
                            text: "palm相机";
                            anchors.centerIn: parent;
                            font.family: fontWeiruanyahei;
                        }
                    }
                    Row {
                        anchors.left: imagePcm.right;
                        anchors.right: parent.right;
                        anchors.verticalCenter: parent.verticalCenter;
                        Label {
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: qsTr("曝光距离");
                        }
                        TextField {
                            id: txtPcmFreq;
                            width: 20 * dpi;
                            text: "20";
                        }
                        Label {
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: qsTr("相机模式");
                        }
                        ComboBox {
                            id: cboPcmMode;
                            width: 20 * dpi;
                            model: ListModel {
                                ListElement { text: "时间曝光, 无零位触发"; color: "Yellow" }
                                ListElement { text: "时间曝光, 有零位触发"; color: "Green" }
                                ListElement { text: "角度曝光, 无零位触发"; color: "Brown" }
                                ListElement { text: "角度曝光, 有零位触发"; color: "Yellow" }
                                ListElement { text: "距离曝光, 无零位触发"; color: "Green" }
                                ListElement { text: "距离曝光, 有零位触发"; color: "Brown" }
                            }
                        }
                    }
                }
                onFlickStarted: {
                    if(Math.abs(contentX) > 50 * dpi)
                    {
                        if(contentX > 0)
                        {
                            if(state == "running")
                                state = "enable";
                        }
                        else
                        {
                            if(state == "enable")
                                state = "running";
                        }
                    }
                }
                onStateChanged: {
                    switch (state)
                    {
                    case "enable":
                        rectPcm.enabled = true;
                        uiAdapter.stopPcm();
                        break;
                    case "running":
                        rectPcm.enabled = false;
                        uiAdapter.setPcm(parseInt(txtPcmFreq.text), cboPcmModeSelected());
                        break;
                    }
                }
            }
            Rectangle {
                width: parent.width;
                height: 1;
                color: "lightgray";
            }
            Flickable {
                id: flickUcm;
                property string state: "enable";
                property bool isTskRunning: false;
                width: parent.width;
                contentWidth: rectUcm.width;
                height: 20 * dpi;
                Rectangle {
                    id: rectUcm;
                    width: flickPcm.width + 1;
                    height: 20 * dpi;
                    Image {
                        id: imageUcm;
                        width: 20 * dpi;
                        height: 20 * dpi;
                        Label {
                            text: "USB相机";
                            anchors.centerIn: parent;
                            font.family: fontWeiruanyahei;
                        }
                    }
                    Row {
                        anchors.left: imageUcm.right;
                        anchors.right: parent.right;
                        anchors.verticalCenter: parent.verticalCenter;
                        Label {
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: qsTr("模式");
                        }
                        ComboBox {
                            id: cboUcmMode;
                            width: 20 * dpi;
                            model: ListModel {
                                ListElement { text: "当前位置拍照"; color: "Yellow" }
                                ListElement { text: "角度模式曝光"; color: "Green" }
                            }
                        }
                        Label {
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: "角度";
                        }
                        TextField {
                            id: txtUcmRoitStart;
                            width: 20 * dpi;
                            text: "0";
                        }
                        Label {
                            width: 2 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: "~";
                        }
                        TextField {
                            id: txtUcmRoitEnd;
                            width: 20 * dpi;
                            text: "360";
                        }
                        CheckBox {
                            id: chkUcmCmra;
                            anchors.verticalCenter: parent.verticalCenter;
                            text: "相机A使能";
                        }
                        CheckBox {
                            id: chkUcmCmrb;
                            anchors.verticalCenter: parent.verticalCenter;
                            text: "相机B使能";
                        }
                        Label {
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: "角度间隔";
                        }
                        TextField {
                            id: txtUcmFreq;
                            width: 20 * dpi;
                            text: "20";
                        }
                    }
                }
                onFlickStarted: {
                    if(Math.abs(contentX) > 50 * dpi)
                    {
                        if(contentX > 0)
                        {
                            if(state == "running")
                            {
                                state = "enable";
                                uiAdapter.stopUcm();
                                //通知Tsk
                                ucmStopped();
                            }
                        }
                        else
                        {
                            if(state == "enable")
                            {
                                if(chkUcmCmra.checked || chkUcmCmrb.checked)
                                {
                                    if(isTskRunning)
                                    {
                                        myToast.showToast("请先停止数据采集作业");
                                        return;
                                    }
                                    state = "running";
                                }
                                else
                                    myToast.showToast("请使能一个相机");
                            }
                        }
                    }
                }
                onStateChanged: {
                    switch (state)
                    {
                    case "disable":
                        rectUcm.enabled = false;
                        break;
                    case "enable":
                        rectUcm.enabled = true;
                        break;
                    case "running":
                        rectUcm.enabled = false;
                        uiAdapter.setUcm(cboUcmMode.currentIndex, parseInt(txtUcmRoitStart.text), parseInt(txtUcmRoitEnd.text), chkUcmCmra.checked, chkUcmCmrb.checked, parseInt(txtUcmFreq.text));
                        //通知Tsk
                        ucmStarted();
                        break;
                    }
                }
            }
            Rectangle {
                width: parent.width;
                height: 1;
                color: "lightgray";
            }
            Flickable {
                id: flickDmi;
                property string state: "enable";
                width: parent.width;
                contentWidth: rectDmi.width;
                height: 20 * dpi;
                Rectangle {
                    id: rectDmi;
                    width: flickDmi.width + 1;
                    height: 20 * dpi;
                    Image {
                        id: imageDmi;
                        width: 20 * dpi;
                        height: 20 * dpi;
                        Label {
                            text: "DMI参数";
                            anchors.centerIn: parent;
                            font.family: fontWeiruanyahei;
                        }
                    }
                    Row {
                        anchors.left: imageDmi.right;
                        anchors.right: parent.right;
                        anchors.verticalCenter: parent.verticalCenter;
                        Label {
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: "编码器线数";
                        }
                        TextField {
                            id: txtDmiCode;
                            width: 20 * dpi;
                            text: "512";
                        }
                        Label {
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: "车轮周长";
                        }
                        TextField {
                            id: txtDmiCirc;
                            width: 20 * dpi;
                            text: "2";
                        }
                    }
                }
                onFlickStarted: {
                    if(Math.abs(contentX) > 50 * dpi)
                    {
                        if(contentX > 0)
                        {
                            if(state == "running")
                                state = "enable";
                        }
                        else
                        {
                            if(state == "enable")
                                state = "running";
                        }
                    }
                }
                onStateChanged: {
                    switch (state)
                    {
                    case "running":
                        uiAdapter.setDmi(parseInt(txtDmiCode.text), parseFloat(txtDmiCirc.text));
                        state = "enable";
                        break;
                    }
                }
            }
        }
    }
    function cboPcmModeSelected()
    {
        switch (cboPcmMode.currentIndex)
        {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 6;
        case 5:
            return 7;
        }
    }
    function setTskRunning(value)
    {
        flickUcm.isTskRunning = value;
    }
}
