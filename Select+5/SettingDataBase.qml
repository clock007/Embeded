import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
Item {
id:databasesetting
visible: true
width: Screen.width
height:Screen.height


//Component.onCompleted: { Ver.Reload_Server_Setting();}
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
        id: mainLayout
        //anchors.fill: parent
        //anchors.margins: margin

//---------------------  Begin of Secound Group Box -----------------------------------------------------------------------------------
        GroupBox {
           id: gridBox
         //  title: "اطلاعات پایگاه داده"
            Layout.fillWidth: true


            GridLayout {
                Layout.minimumHeight: 300;
                id: gridLayout
                rows: 6
                rowSpacing: 10;
                flow: GridLayout.TopToBottom
                anchors.fill: parent



                Label { text: "Server Address:  "; height: 80;  color: "yellow"; font.family: "‌Times News Romans"; font.bold: true;  font.pixelSize: 15}
                Label { text: "DataBase Name:   "; height:80; color: "yellow";  font.family: "‌Times News Romans"; font.bold: true;  font.pixelSize: 15}
                Label { text: "User Name:   "; height: 80; color: "yellow"; font.family: "‌Times News Romans"; font.bold: true;  font.pixelSize: 15}
                Label { text: "PassWord:   "; height: 80; color: "yellow"; font.family: "‌Times News Romans"; font.bold: true;  font.pixelSize: 15 }
                Label { text: "Driver Ver:   "; height:50; color: "yellow"; font.family: "‌Times News Romans"; font.bold: true;  font.pixelSize: 15 }
                Label { text: "Port:   "; height: 50; color: "yellow"; font.family: "‌Times News Romans"; font.bold: true;  font.pixelSize: 15  }


                TextField { id:servername; width: 600; text: Ver.ERR_ServerAddress
                   // style: TextFieldStyle {  Font.family: "Times New Roman"; Font.pointSize: 17; Font.bold: true;     }
                    background: Rectangle{color: "yellow"; anchors.fill: parent; implicitWidth: 600; implicitHeight: 30; radius: 8 }   }
                TextField { id:dbname; width: 600; text: Ver.ERR_DBName
                   // style: TextFieldStyle {  Font.family: "Times New Roman"; Font.pointSize: 17; Font.bold: true;     }
                    background: Rectangle{color: "yellow"; anchors.fill: parent; implicitWidth: 600; implicitHeight: 30; radius: 8 }   }
                TextField { id:username; width: 600; text:Ver.ERR_UID
                   // style: TextFieldStyle {  Font.family: "Times New Roman"; Font.pointSize: 17; Font.bold: true;     }
                    background: Rectangle{color: "yellow"; anchors.fill: parent; implicitWidth: 600; implicitHeight: 30; radius: 8 }   }
                TextField { id:password; width: 600; text: Ver.ERR_DBPassword
                   // style: TextFieldStyle {  Font.family: "Times New Roman"; Font.pointSize: 17; Font.bold: true;     }
                    background: Rectangle{color: "yellow"; anchors.fill: parent; implicitWidth: 600; implicitHeight: 30; radius: 8 }   }
                TextField { id:ver; width: 150; text:"7.2";// text:Ver.ERR_TDS_Version
                   // style: TextFieldStyle {  Font.family: "Times New Roman"; Font.pointSize: 17; Font.bold: true;     }
                    background: Rectangle{color: "yellow"; anchors.fill: parent; implicitWidth: 600; implicitHeight: 30; radius: 8 }   }
                TextField { id:port; width: 150; text:"1433"; //text: Ver.ERR_port
                   // style: TextFieldStyle {  Font.family: "Times New Roman"; Font.pointSize: 17; Font.bold: true;     }
                    background: Rectangle{color: "yellow"; anchors.fill: parent; implicitWidth: 600; implicitHeight: 30; radius: 8 }   }



               // TextField { background: "blue"; color: "white"; length: 200;     }
               // TextInput { id:servername; length:500; font.pointSize: 17; color: "white"; font.bold: true; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter ; text:"\\Azarakhsh.com";     Rectangle { color:"transparent"; width: 500 ; height: 35; border.color: "blue";  radius: 10   } }
              //  TextInput { id:dbname; font.pointSize: 17; color: "white"; font.bold: true; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter ; text:"\\Azarakhsh.com";   width: 500 ; height: 35;  Rectangle { color:"transparent"; width: 500 ; height: 35; border.color: "blue";  radius: 10   }}
              //  TextInput { id:username;     width: 300 ; height: 50;  Rectangle { color:"transparent"; border.color: "white"; anchors.fill: parent; radius: 10   }     }
              //  TextInput { id:password;     width: 300 ; height: 50;  Rectangle {color:"transparent"; border.color: "white"; anchors.fill: parent; radius: 10   }     }
               // TextInput { id:dver;     width: 300; height: 50;  Rectangle { color: "transparent"; border.color: "white";  anchors.fill: parent; radius: 10   }     }
              //  TextInput { id:port;     width: 300; height: 50;  Rectangle { color: "transparent"; border.color: "white";  anchors.fill: parent; radius: 10   }     }
             }
       }

        GroupBox {
            id: rowBox
        //    title: "ذخیره خروج"
            Layout.fillWidth: true
            RowLayout {
                id: rowLayout
                anchors.fill: parent

                Button {
                    id:bsign;        width: 75;     height: 40
                   text: "خروج"
                   onClicked: { databasesetting.visible=false; databasesetting.deleteLater();   }}

                Button {
                    id:bsign2;    width: 75;                    height: 40
                    text: "ذخیره"
                     onClicked: {  //Ver.Initialize_ServerSetting();
                         dialogInsert.open();
                     }}
            } /// First Layout
        } //Secound Group Box

        MessageDialog {
            id: dialogInsert
            title: qsTr("حذف رکورد")
            text: qsTr("آیا درخواست جاری را تایید میکنید؟")

            icon: StandardIcon.Warning
            standardButtons: StandardButton.Ok | StandardButton.Cancel

            // If the answer ...
            onAccepted: {
            message.text= Ver.Insert_Into_ServerSetting(servername.text,dbname.text,username.text,password.text,ver.text,port.text); dialogInsert.close();  }}
              Text {id:message; text: qsTr("پیام");         color: "yellow";   font.pixelSize: 20;  }

      } //Column Layout

  } //Rectangle

//End Of Rectangle
 }
//End of Item

