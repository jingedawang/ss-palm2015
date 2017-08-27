/************************************************************
 * Copyright: IECAS
 * Author: WangJinge
 * Date: 2015-05-22
 * Filename: Settings.qml
 * Description: “启动设置”界面。
 * Version: 1.0
 ************************************************************/
import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Window 2.0
import QtGraphicalEffects 1.0

Rectangle {
    property real dpi: Screen.pixelDensity.toFixed(2);
    property string fontWeiruanyahei: "微软雅黑";
    property string lightgreen: "#80c342";
    signal btnCmrRunClickedWithAngleMode();
    signal btnCmrStopClicked();
    signal tskStarted();
    signal tskStopped();
    Rectangle {
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.right: parent.right;
        anchors.bottom: flick.top;
        color: lightgreen;
        Column {
            anchors.centerIn: parent;
            Text {
                anchors.horizontalCenter: parent.horizontalCenter;
                text: "请设置参数并右滑启动相应设备";
                font.family: fontWeiruanyahei;
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter;
                text: "左滑停止";
                font.family: fontWeiruanyahei;
            }
        }
        z: 1;
    }
    MyToast {
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
        height: 100 * dpi - 1;
        anchors.bottom: parent.bottom;
        contentWidth: column.width;
        contentHeight: column.height;

        Column {
            id: column;
            width: parent.width;
            Gradient {
                id: gradientLightgreen;
                GradientStop {
                    position: 0.0; color: lightgreen;
                }
                GradientStop {
                    position: 0.5; color: "white";
                }
                GradientStop {
                    position: 1.0; color: lightgreen;
                }
            }Gradient {
                id: gradientLightgray;
                GradientStop {
                    position: 0.0; color: "lightgray";
                }
                GradientStop {
                    position: 0.5; color: "white";
                }
                GradientStop {
                    position: 1.0; color: "lightgray";
                }
            }
            Flickable {
                id: flickLsr;
                property string state: "enable";
                width: parent.width;
                contentWidth: rectLsr.width;
                height: 20 * dpi;
                Rectangle {
                    id: rectLsr;
                    width: flickLsr.width + 1;
                    height: 20 * dpi;
                    Image {
                        id: image;
                        width: 20 * dpi;
                        height: 20 * dpi;
                        Label {
                            text: "激光器";
                            anchors.centerIn: parent;
                            font.family: fontWeiruanyahei;
                        }
                    }
                    Row {
                        anchors.left: image.right;
                        anchors.right: parent.right;
                        anchors.verticalCenter: parent.verticalCenter;
                        Label {
                            id:lblLaserFrequency;
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: qsTr("频率[KHz]");
                        }
                        TextField {
                            id: txtLaserFrequency;
                            width: 20 * dpi;
                            text: qsTr("200");
                            validator: RegExpValidator {
                                regExp: /[0-9]+/;
                            }
                        }
                        Button {
                            id: btnLaserFrequencyAdd;
                            width: 10 * dpi;
                            text: qsTr("+");
                            onClicked: {
                                var str = txtLaserFrequency.text.toString();
                                var number = parseInt(str);
                                number = number + 1;
                                txtLaserFrequency.text = number.toString();
                            }
                        }
                        Button {
                            id: btnLaserFrequencySubtract;
                            width: 10 * dpi;
                            text: qsTr("-")
                            onClicked: {
                                var str = txtLaserFrequency.text.toString();
                                var number = parseInt(str);
                                if(number <= 0)
                                {
                                    return;
                                }
                                number = number - 1;
                                txtLaserFrequency.text = number.toString();
                            }
                        }

                        Label {
                            id:lblLaserPower;
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: qsTr("功率[%]");
                        }
                        TextField {
                            id: txtLaserPower
                            width: 20 * dpi;
                            text: qsTr("100")
                            validator: RegExpValidator {
                                regExp: /[0-9]+/;
                            }
                        }
                        Button {
                            id: btnLaserPowerAdd
                            width: 10 * dpi;
                            text: qsTr("+");
                            onClicked: {
                                var str = txtLaserPower.text.toString();
                                var number = parseInt(str);
                                number = number + 1;
                                txtLaserPower.text = number.toString();
                            }
                        }
                        Button {
                            id: btnLaserPowerSubtract;
                            width: 10 * dpi;
                            text: qsTr("-");
                            onClicked: {
                                var str = txtLaserPower.text.toString();
                                var number = parseInt(str);
                                if(number <= 0)
                                {
                                    return;
                                }
                                number = number - 1;
                                txtLaserPower.text = number.toString();
                            }
                        }
                        CheckBox {
                            id: chkLaserSimulate;
                            anchors.verticalCenter: parent.verticalCenter;
                            text: "仿真";
                        }
                    }
                }
                onFlickStarted: {
                    if(Math.abs(contentX) > 50 * dpi)
                    {
                        if(flickTsk.state == "running")
                        {
                            return;
                        }
                        if(contentX > 0)
                        {
                            state = "disable";
                        }
                        else
                        {
                            state = "enable";
                        }
                    }
                }
                onStateChanged: {
                    switch (state)
                    {
                    case "disable":
                        rectLsr.gradient = gradientLightgray;
                        rectLsr.enabled = false;
                        break;
                    case "enable":
                        rectLsr.gradient = null;
                        rectLsr.enabled = true;
                        break;
                    case "running":
                        rectLsr.gradient = gradientLightgreen;
                        rectLsr.enabled = false;
                        startLsr();
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
                id: flickScn;
                property string state: "enable";
                width: parent.width;
                contentWidth: rectScn.width;
                height: 20 * dpi;
                Rectangle {
                    id: rectScn;
                    width: flickScn.width + 1;
                    height: 20 * dpi;
                    Image {
                        id: image2;
                        width: 20 * dpi;
                        height: 20 * dpi;
                        Label {
                            text: "扫描仪";
                            anchors.centerIn: parent;
                            font.family: fontWeiruanyahei;
                        }
                    }
                    Row {
                        anchors.left: image2.right;
                        anchors.right: parent.right;
                        anchors.verticalCenter: parent.verticalCenter;
                        Label {
                            id:lblScannerSpeed;
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: qsTr("转速[rpm]");
                        }
                        TextField {
                            id: txtScannerSpeed
                            width: 20 * dpi;
                            text: qsTr("1200")
                            validator: RegExpValidator {
                                regExp: /[0-9]+/;
                            }
                        }
                        Button {
                            id: btnScannerSpeedAdd;
                            width: 10 * dpi;
                            text: qsTr("+");
                            onClicked: {
                                var str = txtScannerSpeed.text.toString();
                                var number = parseInt(str);
                                number = number + 1;
                                txtScannerSpeed.text = number.toString();
                            }
                        }
                        Button {
                            id: btnScannerSpeedSubtract
                            width: 10 * dpi;
                            text: qsTr("-");
                            onClicked: {
                                var str = txtScannerSpeed.text.toString();
                                var number = parseInt(str);
                                if(number <= 0)
                                {
                                    return;
                                }
                                number = number - 1;
                                txtScannerSpeed.text = number.toString();
                            }
                        }
                        ExclusiveGroup {
                            id: rdogrpScannerMode;
                        }
                        }
                }
                onFlickStarted: {
                    if(Math.abs(contentX) > 50 * dpi)
                    {
                        if(flickTsk.state == "running")
                        {
                            return;
                        }
                        if(contentX > 0)
                        {
                            if(state == "running")
                            {
                                uiAdapter.stopScn();
                                state = "enable";
                            }
                            else if(state == "enable")
                                state = "disable";
                        }
                        else
                        {
                            if(state == "disable")
                            {
                                state = "enable"
                            }
                            else if(state == "enable")
                            {
                                state = "running";
                            }
                        }
                    }
                }
                onStateChanged: {
                    switch (state)
                    {
                    case "disable":
                        rectScn.gradient = gradientLightgray;
                        rectScn.enabled = false;
                        break;
                    case "enable":
                        rectScn.gradient = null;
                        rectScn.enabled = true;
                        break;
                    case "running":
                        rectScn.gradient = gradientLightgreen;
                        rectScn.enabled = false;
                        startScn();
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
                id: flickStg;
                property string state: "enable";
                width: parent.width;
                contentWidth: rectStg.width;
                height: 20 * dpi;
                Rectangle {
                    id: rectStg;
                    width: flickStg.width + 1;
                    height: 20 * dpi;
                    Image {
                        id: image3;
                        width: 20 * dpi;
                        height: 20 * dpi;
                        Label {
                            text: "转台";
                            anchors.centerIn: parent;
                            font.family: fontWeiruanyahei;
                        }
                    }
                    Row {
                        anchors.left: image3.right;
                        anchors.right: parent.right;
                        anchors.verticalCenter: parent.verticalCenter;
                        Label {
                            id:lblStageSpeed;
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: qsTr("转速[dps]");
                        }
                        TextField {
                            id: txtStageSpeed;
                            width: 20 * dpi;
                            text: qsTr("1");
                            validator: RegExpValidator {
                                regExp: /[0-9]+/;
                            }
                        }
                        Button {
                            id: btnStageSpeedAdd;
                            width: 10 * dpi;
                            text: qsTr("+");
                            onClicked: {
                                var str = txtStageSpeed.text.toString();
                                var number = parseInt(str);
                                number = number + 1;
                                txtStageSpeed.text = number.toString();
                            }
                        }
                        Button {
                            id: btnStageSpeedSubtract;
                            width: 10 * dpi;
                            text: qsTr("-");
                            onClicked: {
                                var str = txtStageSpeed.text.toString();
                                var number = parseInt(str);
                                if(number <= 0)
                                {
                                    return;
                                }
                                number = number - 1;
                                txtStageSpeed.text = number.toString();
                            }
                        }
                        Label {
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: qsTr("模式");
                        }
                        ComboBox {
                            id: cboStageMode;
                            width: 20 * dpi;
                            model: ListModel {
                                ListElement {
                                    text: "连续模式"
                                }
                                ListElement {
                                    text: "区域模式"
                                }
                                ListElement {
                                    text: "位置模式"
                                }
                                ListElement {
                                    text: "重置"
                                }
                            }
                        }
                        Label {
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: qsTr("起止角度");
                        }
                        TextField {
                            id: txtStgRoitStart;
                            width: 10 * dpi;
                            text: "0";
                        }
                        Label {
                            width: 2 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: "~";
                        }
                        TextField {
                            id: txtStgRoitEnd;
                            width: 10 * dpi;
                            text: "360";
                        }
                    }
                }
                onFlickStarted: {
                    if(Math.abs(contentX) > 50 * dpi)
                    {
                        if(flickTsk.state == "running")
                        {
                            return;
                        }
                        if(contentX > 0)
                        {
                            if(state == "running")
                            {
                                state = "enable";
                                uiAdapter.stopStg();
                            }
                            else if(state == "enable")
                                state = "disable";
                        }
                        else
                        {
                            if(state == "disable")
                            {
                                state = "enable"
                            }
                            else if(state == "enable")
                            {
                                state = "running";
                            }
                        }
                    }
                }
                onStateChanged: {
                    switch (state)
                    {
                    case "disable":
                        rectStg.gradient = gradientLightgray;
                        rectStg.enabled = false;
                        break;
                    case "enable":
                        rectStg.gradient = null;
                        rectStg.enabled = true;
                        break;
                    case "running":
                        rectStg.gradient = gradientLightgreen;
                        rectStg.enabled = false;
                        startStg();
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
                id: flickCmr;
                property string state: "enable";
                property bool isCmrAngleMode: false;
                width: parent.width;
                contentWidth: rectCmr.width;
                height: 20 * dpi;
                Rectangle {
                    id: rectCmr;
                    width: flickCmr.width + 1;
                    height: 20 * dpi;
                    Image {
                        id: image4;
                        width: 20 * dpi;
                        height: 20 * dpi;
                        Label {
                            text: "相机";
                            anchors.centerIn: parent;
                            font.family: fontWeiruanyahei;
                        }
                    }
                    Row {
                        anchors.left: image4.right;
                        anchors.right: parent.right;
                        anchors.verticalCenter: parent.verticalCenter;
                        Label {
                            id:lblCameraInterval;
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: qsTr("间隔[ms]");
                        }
                        TextField {
                            id: txtCameraInterval;
                            width: 20 * dpi;
                            text: qsTr("1000");
                            validator: RegExpValidator {
                                regExp: /[0-9]+/;
                            }
                        }
                        Button {
                            id: btnCameraIntervalAdd;
                            width: 10 * dpi;
                            text: qsTr("+");
                            onClicked: {
                                var str = txtCameraInterval.text.toString();
                                var number = parseInt(str);
                                number = number + 1;
                                txtCameraInterval.text = number.toString();
                            }
                        }
                        Button {
                            id: btnCameraIntervalSubtract;
                            width: 10 * dpi;
                            text: qsTr("-");
                            onClicked: {
                                var str = txtCameraInterval.text.toString();
                                var number = parseInt(str);
                                if(number <= 0)
                                {
                                    return;
                                }
                                number = number - 1;
                                txtCameraInterval.text = number.toString();
                            }
                        }
                        Label {
                            id: lblCameraMode;
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: qsTr("相机模式");
                        }
                        ComboBox {
                            id: cboCameraMode;
                            width: 20 * dpi;
                            model: ListModel {
                                ListElement { text: "时间曝光, 无零位触发"; color: "Yellow" }
                                ListElement { text: "时间曝光, 有零位触发"; color: "Green" }
                                ListElement { text: "角度曝光, 无零位触发"; color: "Brown" }
                                ListElement { text: "角度曝光, 有零位触发"; color: "Yellow" }
                                ListElement { text: "位置曝光, 无零位触发"; color: "Green" }
                                ListElement { text: "位置曝光, 有零位触发"; color: "Brown" }
                                ListElement { text: "距离曝光, 无零位触发"; color: "Yellow" }
                                ListElement { text: "距离曝光, 有零位触发"; color: "Green" }
                            }
                            onCurrentIndexChanged: {
                                if(currentIndex == 2 || currentIndex == 3)
                                {
                                    flickCmr.isCmrAngleMode = true;
                                }
                                else
                                {
                                    flickCmr.isCmrAngleMode = false;
                                }
                            }
                        }
                        Label {
                            width: 20 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: "起止角度";
                        }
                        TextField {
                            id: txtCmrRoitStart;
                            width: 10 * dpi;
                            text: "0";
                        }
                        Label {
                            width: 2 * dpi;
                            anchors.verticalCenter: parent.verticalCenter;
                            horizontalAlignment: Text.AlignRight;
                            text: "~";
                        }
                        TextField {
                            id: txtCmrRoitEnd;
                            width: 10 * dpi;
                            text: "360";
                        }
                    }
                }
                onFlickStarted: {
                    if(Math.abs(contentX) > 50 * dpi)
                    {
                        if(flickTsk.state == "running")
                        {
                            return;
                        }
                        if(contentX < 0)
                        {
                            if(state == "disable")
                            {
                                state = "enable";
                            }
                            else if(state == "enable")
                            {
                                if(flickTsk.state == "running" && flickCmr.isCmrAngleMode)
                                {
                                        myToast.showToast("请先停止数据采集");
                                        return;
                                }
                                state = "running";
                            }
                        }
                        else
                        {
                            if(state == "running")
                            {
                                uiAdapter.stopCmr();
                                state = "enable";
                            }
                            else if(state == "enable")
                            {
                                state = "disable";
                            }
                        }
                    }
                }
                onStateChanged: {
                    switch (state)
                    {
                    case "disable":
                        rectCmr.gradient = gradientLightgray;
                        rectCmr.enabled = false;
                        break;
                    case "enable":
                        rectCmr.gradient = null;
                        rectCmr.enabled = true;
                        break;
                    case "running":
                        rectCmr.gradient = gradientLightgreen;
                        rectCmr.enabled = false;
                        startCmr();
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
                id: flickTsk;
                property string state: "enable";
                property bool isUcmRunning: false;
                width: parent.width;
                contentWidth: rectTsk.width;
                height: 20 * dpi;
                Rectangle {
                    id: rectTsk;
                    width: flickTsk.width + 1;
                    height: 20 * dpi;
                    Image {
                        id: image5;
                        width: 20 * dpi;
                        height: 20 * dpi;
                        Label {
                            text: "数据采集";
                            anchors.centerIn: parent;
                            font.family: fontWeiruanyahei;
                        }
                    }
                    Column {
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.left: image5.right;
                        anchors.right: parent.right;
                        Row {
                            Label {
                                width: 20 * dpi;
                                anchors.verticalCenter: parent.verticalCenter;
                                horizontalAlignment: Text.AlignRight;
                                text: qsTr("最小测距[m]");
                            }
                            TextField {
                                id: txtTskMin
                                width: 20 * dpi;
                                text: qsTr("1")
                                validator: RegExpValidator {
                                    regExp: /[0-9]+/;
                                }
                            }
                            Button {
                                id: btnTskMinAdd;
                                width: 10 * dpi;
                                text: qsTr("+");
                                onClicked: {
                                    var str = txtTskMin.text.toString();
                                    var number = parseInt(str);
                                    number = number + 1;
                                    txtTskMin.text = number.toString();
                                }
                            }
                            Button {
                                id: btnTskMinSubtract
                                width: 10 * dpi;
                                text: qsTr("-");
                                onClicked: {
                                    var str = txtTskMin.text.toString();
                                    var number = parseInt(str);
                                    if(number <= 0)
                                    {
                                        return;
                                    }
                                    number = number - 1;
                                    txtTskMin.text = number.toString();
                                }
                            }
                            Label {
                                width: 25 * dpi;
                                anchors.verticalCenter: parent.verticalCenter;
                                horizontalAlignment: Text.AlignRight;
                                text: "ROI扫描方向";
                            }
                            TextField {
                                id: txtTskRoisStart;
                                width: 10 * dpi;
                                text: "0";
                            }
                            Label {
                                width: 2 * dpi;
                                anchors.verticalCenter: parent.verticalCenter;
                                horizontalAlignment: Text.AlignRight;
                                text: "~";
                            }
                            TextField {
                                id: txtTskRoisEnd;
                                width: 10 * dpi;
                                text: "360";
                            }

                            Label {
                                id:lblTskEchoMode;
                                width: 25 * dpi;
                                anchors.verticalCenter: parent.verticalCenter;
                                horizontalAlignment: Text.AlignRight;
                                text: qsTr("回波类型：");
                            }
                            ExclusiveGroup {
                                id: rdogrpTskEcho;
                            }
                            RadioButton {
                                id: rdoTskEchoMode1;
                                anchors.verticalCenter: parent.verticalCenter;
                                text: "1";
                                checked: true;
                                exclusiveGroup: rdogrpTskEcho;
                            }
                            RadioButton {
                                id: rdoTskEchoMode2;
                                anchors.verticalCenter: parent.verticalCenter;
                                text: "2";
                                exclusiveGroup: rdogrpTskEcho;
                            }
                            RadioButton {
                                id: rdoTskEchoMode3;
                                anchors.verticalCenter: parent.verticalCenter;
                                text: "3";
                                exclusiveGroup: rdogrpTskEcho;
                            }
                            RadioButton {
                                id: rdoTskEchoMode4;
                                anchors.verticalCenter: parent.verticalCenter;
                                text: "4";
                                exclusiveGroup: rdogrpTskEcho;
                            }
                        }
                        Row {
                            Label {
                                width: 20 * dpi;
                                anchors.verticalCenter: parent.verticalCenter;
                                horizontalAlignment: Text.AlignRight;
                                text: qsTr("最大测距[m]");
                            }
                            TextField {
                                id: txtTskMax;
                                width: 20 * dpi;
                                text: qsTr("300");
                                validator: RegExpValidator {
                                    regExp: /[0-9]+/;
                                }
                            }
                            Button {
                                id: btnTskMaxAdd;
                                width: 10 * dpi;
                                text: qsTr("+");
                                onClicked: {
                                    var str = txtTskMax.text.toString();
                                    var number = parseInt(str);
                                    number = number + 1;
                                    txtTskMax.text = number.toString();
                                }
                            }
                            Button {
                                id: btnTskMaxSubtract;
                                width: 10 * dpi;
                                text: qsTr("-");
                                onClicked: {
                                    var str = txtTskMax.text.toString();
                                    var number = parseInt(str);
                                    if(number <= 0)
                                    {
                                        return;
                                    }
                                    number = number - 1;
                                    txtTskMax.text = number.toString();
                                }
                            }

                            Label {
                                width: 25 * dpi;
                                anchors.verticalCenter: parent.verticalCenter;
                                horizontalAlignment: Text.AlignRight;
                                text: "ROI转台方向";
                            }
                            TextField {
                                id: txtTskRoitStart;
                                width: 10 * dpi;
                                text: "0";
                            }
                            Label {
                                width: 2 * dpi;
                                anchors.verticalCenter: parent.verticalCenter;
                                horizontalAlignment: Text.AlignRight;
                                text: "~";
                            }
                            TextField {
                                id: txtTskRoitEnd;
                                width: 10 * dpi;
                                text: "360";
                            }
                            Label {
                                width: 20 * dpi;
                                anchors.verticalCenter: parent.verticalCenter;
                                horizontalAlignment: Text.AlignRight;
                                text: "网络数据流";
                            }
                            ComboBox {
                                id: cboTskNetFlow;
                                width: 20 * dpi;
                                model: ListModel {
                                        ListElement { text: "Local"; color: "Green" }
                                        ListElement { text: "Remote"; color: "Yellow" }
                                    }
                            }
                            CheckBox {
                                anchors.verticalCenter: parent.verticalCenter;
                                id: chkTskMP;
                                text: "MP模式";
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
                            {
                                uiAdapter.stop();
                                //通知UCM
                                tskStopped();
                                state = "enable";
                                flickLsr.state = "enable";
                                flickScn.state = "enable";
                                flickStg.state = "enable";
                                flickCmr.state = "enable";
                            }
                        }
                        else
                        {
                            if(state == "enable")
                            {
                                if(flickCmr.isCmrAngleMode)
                                {
                                    myToast.showToast("外置相机角度模式不能与数据采集同时工作");
                                    return;
                                }
                                else if(isUcmRunning)
                                {
                                    myToast.showToast("请先关闭USB相机");
                                    return;
                                }
                                uiAdapter.askCfg();
                                if(flickScn.state == "enable")
                                    flickScn.state = "running";
                                if(flickStg.state == "enable")
                                    flickStg.state = "running";
                                if(flickCmr.state == "enable")
                                    flickCmr.state = "running";
                                if(flickLsr.state == "enable")
                                    flickLsr.state = "running";
                                state = "running";
                            }
                        }
                    }
                }
                onStateChanged: {
                    switch (state)
                    {
                    case "disable":
                        rectTsk.gradient = gradientLightgray;
                        rectTsk.enabled = false;
                        break;
                    case "enable":
                        rectTsk.gradient = null;
                        rectTsk.enabled = true;
                        break;
                    case "running":
                        rectTsk.gradient = gradientLightgreen;
                        rectTsk.enabled = false;
                        startTsk();
                        //通知UCM
                        tskStarted();
                        break;
                    }
                }
            }
            move: Transition {
                    NumberAnimation { properties: "x,y"; duration: 1000 }
                }
        }
    }
    function setCompleted()
    {
        uiAdapter.askCfg();
        if(flickScn.state == "enable")
            startScn();
        if(flickStg.state == "enable")
            startStg();
        if(flickCmr.state == "enable")
            startCmr();
        if(flickLsr.state == "enable")
            startLsr();
        if(flickTsk.state == "enable")
            startTsk();
    }
    function startScn()
    {
        uiAdapter.setScanner(parseFloat(txtScannerSpeed.text));
    }
    function startStg()
    {
        uiAdapter.setStage(parseFloat(txtStageSpeed.text), cboStageModeSelected(), parseInt(txtStgRoitStart.text), parseInt(txtStgRoitEnd.text));
    }
    function startCmr()
    {
        uiAdapter.setCmr(parseInt(txtCameraInterval.text), cboCameraMode.currentIndex, parseInt(txtCmrRoitStart.text), parseInt(txtCmrRoitEnd.text));
    }
    function startLsr()
    {
        uiAdapter.setLaser(parseInt(txtLaserFrequency.text), parseInt(txtLaserPower.text), chkLaserSimulate.checked);
    }
    function startTsk()
    {
        uiAdapter.setTsk(parseInt(txtTskMin.text), parseInt(txtTskMax.text), rdoEchoModeSelected(), chkTskMP.checked, cboTskNetFlow.currentIndex, parseInt(txtTskRoisStart.text), parseInt(txtTskRoisEnd.text), parseInt(txtTskRoitStart.text), parseInt(txtTskRoitEnd.text));
    }
    function setEnabled(setEnable)
    {
        settings.enabled = setEnable;
    }
    function rdoEchoModeSelected()
    {
        if(rdoTskEchoMode1.checked)
        {
            return 1;
        }
        if(rdoTskEchoMode2.checked)
        {
            return 2;
        }
        if(rdoTskEchoMode3.checked)
        {
            return 4;
        }
        if(rdoTskEchoMode4.checked)
        {
            return 8;
        }
    }
    function cboStageModeSelected()
    {
        switch (cboStageMode.currentIndex)
        {
        case 0:
            return 3;
        case 1:
            return 5;
        case 2:
            return 6;
        case 3:
            return 8;
        }
    }
    function onCameraStarted()
    {
        txtCameraInterval.enabled = false;
        btnCameraIntervalAdd.enabled = false;
        btnCameraIntervalSubtract.enabled = false;
        cboCameraMode.enabled = false;
        txtCmrRoitStart.enabled = false;
        txtCmrRoitEnd.enabled = false;
        btnCmrRun.enabled = false;
        btnCmrStop.enabled = true;
    }
    function onCameraStopped()
    {
        txtCameraInterval.enabled = true;
        btnCameraIntervalAdd.enabled = true;
        btnCameraIntervalSubtract.enabled = true;
        cboCameraMode.enabled = true;
        txtCmrRoitStart.enabled = true;
        txtCmrRoitEnd.enabled = true;
        btnCmrRun.enabled = true;
        btnCmrStop.enabled = false;
    }
    function setUcmRunning(value)
    {
        flickTsk.isUcmRunning = value;
    }

}

