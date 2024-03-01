import QtQuick 2.5
import QtQuick.Layouts 1.1
//import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.VirtualKeyboard 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
Item {
id:setting_IP
visible: true
width: Screen.width
height:Screen.height

//Component.onCompleted: { Spi.Re_Load_IpSettings()}
MouseArea{ anchors.fill: parent    }

Rectangle {

// width: 800; height: 480
 anchors.fill: parent
 gradient:
 Gradient {
     GradientStop {position: 0.0; color: "black"}
     GradientStop {position: 1; color: "blue"} }

//--------------------------------  1  DB address----------------------------

 ColumnLayout {
        x:0; y:0
        id: mainLayout
        //anchors.fill: parent
        spacing: 10

        //anchors.margins: margin

//---------------------  Begin of Secound Group Box -----------------------------------------------------------------------------------
        GroupBox {

            id: gridBox
            title: "اطلاعات آدرس آی پی"
            Layout.fillWidth: true


            GridLayout {
                //Layout.minimumHeight: 300;
                id: gridLayout
                rows: 4
                rowSpacing: 5;
                flow: GridLayout.TopToBottom
                anchors.fill: parent

                Label { text: "IP Address:  "; height: 80;  color: "yellow"; font.family: "‌Times News Romans"; font.bold: true;  font.pixelSize: 18}
                Label { text: "Domain name(DNS):   "; height:70; color: "yellow";  font.family: "‌Times News Romans"; font.bold: true;  font.pixelSize: 18}
                Label { text: "Gate Way:   "; height: 80; color: "yellow"; font.family: "‌Times News Romans"; font.bold: true;  font.pixelSize: 18}
                Label { text: "NetMask:   "; height: 80; color: "yellow"; font.family: "‌Times News Romans"; font.bold: true;  font.pixelSize: 18 }



               TextField { id:ipaddress; width: 400;    text:Spi.ERR_IPADDRESS; height: 50; inputMethodHints: Qt.ImhDigitsOnly
                   // style: TextFieldStyle {  Font.family: "Times New Roman"; Font.pointSize: 17; Font.bold: true;     }
                    background: Rectangle{color: "yellow"; anchors.fill: parent; implicitWidth: 400; implicitHeight: 50; radius: 8 }   }
                TextField { id:dns; width: 400; text: Spi.ERR_DNS; height: 50 ;inputMethodHints: Qt.ImhDigitsOnly
                   // style: TextFieldStyle {  Font.family: "Times New Roman"; Font.pointSize: 17; Font.bold: true;     }
                    background: Rectangle{color: "yellow"; anchors.fill: parent; implicitWidth: 400; implicitHeight: 50; radius: 8 }   }
                TextField { id:gateway; width: 400;  text:Spi.ERR_GATEWAY; height: 50; inputMethodHints: Qt.ImhDigitsOnly
                   // style: TextFieldStyle {  Font.family: "Times New Roman"; Font.pointSize: 17; Font.bold: true;     }
                    background: Rectangle{color: "yellow"; anchors.fill: parent; implicitWidth: 400; implicitHeight: 50; radius: 8 }   }
                TextField { id:mask; width: 400; text:Spi.ERR_NETADDRESS; height: 50; inputMethodHints: Qt.ImhDigitsOnly
                   // style: TextFieldStyle {  Font.family: "Times New Roman"; Font.pointSize: 17; Font.bold: true;     }
                    background: Rectangle{color: "yellow"; anchors.fill: parent; implicitWidth: 400; implicitHeight: 50; radius: 8 }   }

        }// GridLayout

      } // First GroupBox

        GroupBox {

            id: rowBox
            spacing: 10
            // title: "اطلاعات پایگاه داده"

        //    title: "ذخیره خروج"
            Layout.fillWidth: true
            RowLayout {

                id: rowLayout
                anchors.fill: parent

                Button {
                    id:bsign;        width: 130;     height: 80
                   text: "خروج"
                   onClicked: { Ver.Get_Current_IP();
                       setting_IP.visible=false; }}

                Button {
                    id:bsign2;    width: 130;   height: 80
                    text: "ذخیره"
                     onClicked: { // t3.text="تغییرات اعمال شد";
                         dialogInsert.open()
                     }}
            } /// First Layout
        } //Secound Group Box

        MessageDialog {
            id: dialogInsert
            text: qsTr("آیا درخواست جاری را تایید میکنید؟")

            icon: StandardIcon.Warning
            standardButtons: StandardButton.Ok | StandardButton.Cancel

            // If the answer ...
            onAccepted: { Spi.Insert_Into_Setting_Ip(ipaddress.text,dns.text,gateway.text,mask.text);
            dialogInsert.close();  }}




      //  TextArea {
        //   id: t3
       //  text: "لطفا اطلاعات آدرس آی پی را وارد کنید\n"
        //        + "در انتها دگمه ذخیره را کلیک کنید."
          //  Font.pixelSize: 30
       //     Layout.minimumHeight: 30
        //    Layout.fillHeight: true
         //   Layout.fillWidth: true        }

    } //Column Layout

  } //Rectangle

//End Of Rectangle
 }
//End of Item

