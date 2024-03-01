import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
Item {
    id:settingpassword
    visible: true
    width: Screen.width
    height:Screen.height
MouseArea{ anchors.fill: parent    }
     Rectangle {
     anchors.fill: parent
     gradient:
     Gradient {
         GradientStop {position: 0.0; color: "black"}
         GradientStop {position: 1; color: "blue"} }
  Component.onCompleted: {  confirmPassword.visible=true }
  property string pass: Spi.ERR_PASSWORD
  //onPassChanged: {dialogPass.text="رمز عبور با موفیت تغییر کرد";      dialogPass.open(); }
    //--------------------------------  1  DB address----------------------------

     ColumnLayout {
            id: mainLayout
            anchors.fill: parent
            //anchors.margins: margin

   //---------------------  Begin of Secound Group Box -----------------------------------------------------------------------------------
            GroupBox {
               id: gridBox
               title: "تغییر رمز عبور"
                Layout.fillWidth: true


                GridLayout {
                    Layout.minimumHeight: 400;
                    id: gridLayout
                    rows: 3;                    rowSpacing: 30;
                    flow: GridLayout.TopToBottom
                    anchors.fill: parent


                    TextField { id:oldPass; width: 300; height: 50;
                       background: Rectangle{color: "yellow"; anchors.fill: parent; implicitHeight: 40; implicitWidth: 300; radius: 8 }   }

                    TextField { id:newPass; width: 300; height: 50
                       // style: TextFieldStyle {  Font.family: "Times New Roman"; Font.pointSize: 17; Font.bold: true;     }
                     background: Rectangle{color: "yellow"; anchors.fill: parent; implicitHeight: 40; implicitWidth: 300; radius: 8 }   }

                    TextField { id:newPass2; width: 300; height: 50;
                       // style: TextFieldStyle {  Font.family: "Times New Roman"; Font.pointSize: 17; Font.bold: true;     }
                       background: Rectangle{color: "yellow"; anchors.fill: parent; implicitHeight: 40; implicitWidth: 300; radius: 8 }   }


                    Label { text: "گذر واژه قدیم:  "; height: 80;  color: "yellow"; font.family: "‌Times News Romans"; font.bold: true;  font.pixelSize: 15}
                    Label { text: "گذرواژه جدید:   "; height:80; color: "yellow";  font.family: "‌Times News Romans"; font.bold: true;  font.pixelSize: 15}
                    Label { text: " تکرار گذرواژه جدید:   "; height:80; color: "yellow";  font.family: "‌Times News Romans"; font.bold: true;  font.pixelSize: 15}
                 }
           }

            //  Begin of first GroupBox
            //---------------------------------------------------------------------------------------------------------------------------------------
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
                                   onClicked: { settingpassword.visible=false; settingpassword.deleteLater()  }}

                                Button {
                                    id:bsign2;    width: 75;                    height: 40
                                    text: "ذخیره"
                                    onClicked: {
                                        if(newPass.text==newPass2.text)    {dialog.open();  }
                                        if(newPass.text!=newPass2.text)     {dialogError.open(); }



                                    }}
                            } /// First Layout
                        } //First Group Box

                        MessageDialog {
                            id: dialog
                            title: qsTr("در خواست تایید تغییر رمز")
                            text: qsTr("آیا از تغییر رمز عبور اطمینان دارید؟")

                            icon: StandardIcon.Warning
                            standardButtons: StandardButton.Ok | StandardButton.Cancel

                            // If the answer ...
                            onAccepted: { Spi.Insert_Into_Setting_Password(oldPass.text,newPass.text);  } }

                        MessageDialog {
                            id: dialogError
                            title: qsTr("خطا")
                            text: qsTr("رمز عبور و تکرار آن یکی نیستند")

                            icon: StandardIcon.Warning
                            standardButtons: StandardButton.Ok | StandardButton.Cancel

                            // If the answer ...
                            onAccepted: { dialogError.close();  } }




          //  TextArea {
          //    id: answer
         //   text: "لطفا اطلاعات گذرواژه را وارد کنید\n"
             //      + "در انتها دگمه ذخیره را کلیک کنید."
           //    Layout.minimumHeight: 30
             // Layout.fillHeight: true
             //  Layout.fillWidth: true}
//        } //Column Layout

   //  MessageDialog {
   //      id: dialogPass

     //    title: qsTr("تغییر رمز عبور")
     //    text: "--"
     //    x:150
      //   y:50
      //   width: 200
       //  height: 200
       //  standardButtons: StandardButton.Ok

         // If the answer ...
       //  onAccepted: {                 dialogUp.close()
       //  }}

     //Rectangle {
    //     id:confirmPassword; radius: 20;
      //   width: 300; height:180;   visible: false; x:320; y:100;
      //  anchors.centerIn: parent.Center
        // Text { id:confirmPasswordText;
        //     text: qsTr("رمز عبور با موفقیت تغییر کرد");  width: 300; horizontalAlignment: Text.AlignHCenter;}
       //  Button {id:exit; text: "خروج";  x:50; y:125; onClicked: {  confirmPassword.visible=false }
      //    } }
      } //Rectangle
    //End Of Rectangle

 //-------------------------------------------------------------------------------------------------
 //------------------------------------------------------------------------------------------------

      //--------------------------------------------------------------------------------------------------------------


     }
    //End of Item


}



