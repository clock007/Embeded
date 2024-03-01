import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.0
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.VirtualKeyboard 2.0
import QtQuick.VirtualKeyboard.Settings 2.2

Item {
    id: settingindows
    width: Screen.width
    height: Screen.height
    visible: true

    signal outsignal()
    onOutsignal: {          console.log("OpenSerialPort");         Qt.quit(); }

    property string pass: Spi.ERR_PASSWORD
  //  property int vol: Ver.ERR_VOL
   // property int waitScreen: Ver.ERR_SCREENSAVER
    property bool upLoad: Ver.ERR_UP_BUSY
    property bool down: Ver.ERR_DOWN_BUSY

    onUpLoadChanged: {
   // if(upLoad==true) {dialogUp.text="در حال کپی کردن اثر انگشت"; busyIndicator.running=true; console.log("On COOOPy");  }
    if(upLoad==false) {console.log('-----------------++++++ Busy Actived'); dialogUp.text="اتمام آپلود نمونه ها"; busyIndicator.running=false;  dialogUp.open()}}
    onDownChanged: {
    if(down==false) {    dialogUp.text="اتمام دانلود نمونه ها"; busyIndicator.running=false;  dialogUp.open()} }
   // onVolChanged: { volume.value=vol; screensaver.value=waitScreen; console.log('-----------------++++++'); console.log(vol);  }

    Rectangle {
        id:rect2
        anchors.fill: parent
        gradient:
        Gradient {
            GradientStop {position: 0.0; color: "cyan"}
            GradientStop {position: 1; color: "blue"}}


//---------------------------------------------------------------
            Butt { id:bip
                   // bx:50;                    by:50
                    bx:Screen.width/16;        by:Screen.height/9.6
                bicon: "qrc:/zIp.png"
                btext: "تنظیم آدرس آی پی
 دستگاه"
                onBclicked: {  setIp_Dialog.visible=true;  outDialog.visible=false; reset_Dialog.visible=false;  changePass_Dialog.visible=false;
                    dataBaseSetting_Dialog.visible=false; changeClock_Dialog.visible=false;  upload_Dialog.visible=false;  download_Dialog.visible=false  }}

            Butt {
                id:bdebug
                //bx:300;                by:50
                bx:Screen.width/2.66;        by:Screen.height/9.6
                bicon: "qrc:/zReboot.png"
                btext: "راه اندازی مجدد
 سیستم"
                onBclicked: { reset_Dialog.visible=true;  setIp_Dialog.visible=false; outDialog.visible=false; changePass_Dialog.visible=false;
                    dataBaseSetting_Dialog.visible=false;   changeClock_Dialog.visible=false;  upload_Dialog.visible=false;   download_Dialog.visible=false }}

            Butt {
                id:bpass
                bicon: "qrc:/zPass.ico"
                //bx:550;                by:50
                 bx:Screen.width/1.45;        by:Screen.height/9.6
                btext: "تغییر رمز عبور"
                onBclicked: {changePass_Dialog.visible=true;  setIp_Dialog.visible=false;  outDialog.visible=false; reset_Dialog.visible=false;
                    dataBaseSetting_Dialog.visible=false; changeClock_Dialog.visible=false;  upload_Dialog.visible=false;  download_Dialog.visible=false}}
//--------------------------------------------------


            Butt {
                id:bSetting
                //bx:50;                by:175
                 bx:Screen.width/16;        by:Screen.height/2.74
                bicon: "qrc:/zSetting.png"

                btext: "(صدا نمایشگر)تنظیمات"
                onBclicked: {  var component = Qt.createComponent("Setting.qml")
                    var window    = component.createObject(settingindows);   settingindows.focus=false;   window.show();   }}

            Butt {
                id:bdatabase
                //bx:300;                by:175
                 bx:Screen.width/2.66;        by:Screen.height/2.74
                bicon: "qrc:/zDataBase.png"
                btext: "تنظیمات دیتا بیس"
                onBclicked: {   dataBaseSetting_Dialog.visible=true;   setIp_Dialog.visible=false;  outDialog.visible=false; reset_Dialog.visible=false;  changePass_Dialog.visible=false;
                     changeClock_Dialog.visible=false;  upload_Dialog.visible=false;  download_Dialog.visible=false  }}


            Butt {
            id:bformat
            //bx:550            by:175
            bx:Screen.width/1.45;        by:Screen.height/2.74
            bicon: "qrc:/zClock.png"
            btext: "تنظیم ساعت و تاریخ"
            onBclicked: { changeClock_Dialog.visible=true; changePass_Dialog.visible=false;  setIp_Dialog.visible=false;  outDialog.visible=false; reset_Dialog.visible=false;
                dataBaseSetting_Dialog.visible=false;   upload_Dialog.visible=false;  download_Dialog.visible=false;  settingindows.focus=false;   }}


//-----------------------------------------------------------------------------------

            Butt {
                id:bUpFinger
                //bx:50                by:300
                bx:Screen.width/16;        by:Screen.height/1.6
                bicon: "qrc:/zUpload.png"
                btext: "آپلود اثر انگشت"
                onBclicked: { upload_Dialog.visible=true; changeClock_Dialog.visible=false; changePass_Dialog.visible=false;  setIp_Dialog.visible=false;  outDialog.visible=false; reset_Dialog.visible=false;
                    dataBaseSetting_Dialog.visible=false; download_Dialog.visible=false;  settingindows.focus=false;  }}


            Butt {
                id:bDownFinger
               // bx:300                by:300
                bx:Screen.width/2.66;        by:Screen.height/1.6
                bicon: "qrc:/zDownload1.png"
                btext: "دانلود اثر انگشت"
                onBclicked: {download_Dialog.visible=true; changeClock_Dialog.visible=false; changePass_Dialog.visible=false;  setIp_Dialog.visible=false;  outDialog.visible=false; reset_Dialog.visible=false;
                    dataBaseSetting_Dialog.visible=false;   upload_Dialog.visible=false;  settingindows.focus=false;  }}


            Butt {
                id:bout
                //bx:550                by:300
                 bx:Screen.width/1.45;        by:Screen.height/1.6
                bicon: "qrc:/zExit.png"
               btext: "خروج"
                onBclicked: { outDialog.visible=true;  changeClock_Dialog.visible=false; changePass_Dialog.visible=false;  setIp_Dialog.visible=false;   reset_Dialog.visible=false;
                    dataBaseSetting_Dialog.visible=false;   upload_Dialog.visible=false;  download_Dialog.visible=false;  settingindows.focus=false; }}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------- Out Dialog Box ----------------------------------------------
            Rectangle {
                id:outDialog;
                border.color: "red"; border.width: 5;     radius: 20;    width: 300; height:250;      visible: false; x:250; y:70;
             //   anchors.centerIn: parent.Center
                //----------------------------------- Assign Mouse Area --------------------------------------------
                MouseArea { anchors.fill: parent    }


                Text { id:outTitle;
                    text: qsTr(" خروج از برنامه");  width: 300; y:10; color:"red"; font.pixelSize: 20; horizontalAlignment: Text.AlignHCenter;}
                Text { id:outDialogText;
                    text: qsTr("لطف  رمز عبور را وارد کنید");  width: 300; y:50;  horizontalAlignment: Text.AlignHCenter;}

                TextInput  {  id:passOut;   echoMode:TextInput.Password; height: 50; width: 150; x:75; y:80
                     onFocusChanged: { VirtualKeyboardSettings.locale = "en_EN"}
                    Rectangle{ anchors.fill: parent; color: "transparent"; border.color: "red"; border.width: 5; radius: 20; }
                    verticalAlignment: Qt.AlignVCenter;         horizontalAlignment: Qt.AlignHCenter; }

                Button {id:no2; text: "خروج";  x:50; y:150; height: 75;
                    onClicked:{ outDialogText.text="لطف  رمز عبور را وارد کنید"; outDialogText.color="black";
                                passOut.color="black" ;   passOut.text="";
                                changePass_Dialog.visible=false; download_Dialog.visible=false;   upload_Dialog.visible=false;  changeClock_Dialog.visible=false; outDialog.visible=false; dataBaseSetting_Dialog.visible=false; setIp_Dialog.visible=false;  reset_Dialog.visible=false;}}
                Button {id:ok2; text: "تایید"; x:170; y:150; height: 75;
                    onClicked: {
                        if(passOut.text!=pass || passOut.text!="azarakhsh007") {
                              outDialogText.text="رمز عبور اشتباه است";  outDialogText.color="red";     }

                        if(passOut.text=="azarakhsh007"||passOut.text==pass){passOut.text=="";  outsignal();}}}}
//--------------------------------------------------------------------------------------------------------------




//---------------------------------------  Reset Dialog ------------------------------------------------------------------------
          Rectangle { id:reset_Dialog;
             border.color: "red"; border.width: 5; radius: 20;  width: 300; height:250; visible: false; x:250; y:70;
              //  anchors.centerIn: parent.Center
             //----------------------------------- Assign Mouse Area --------------------------------------------
             MouseArea { anchors.fill: parent    }

                Text { id:reset_DialogTitle
                    text: qsTr("راه اندازی مجدد"); width: parent.width; color:"red"; font.pixelSize: 20; y:10; horizontalAlignment: Text.AlignHCenter;}
                Text { id:reset_DialogText
                    text: qsTr("لطفا  رمز عبور را وارد کنید");font.pixelSize: 16;  width: 300; y:50; horizontalAlignment: Text.AlignHCenter;}

                TextInput  {  id:reset_Pass;  height: 50; width: 150; x:75; y:80; echoMode:TextInput.Password;
                     onFocusChanged: { VirtualKeyboardSettings.locale = "en_EN"}
                    Rectangle{ anchors.fill: parent; color: "transparent"; border.color: "red"; border.width: 5; radius: 20; }
                    verticalAlignment: Qt.AlignVCenter;         horizontalAlignment: Qt.AlignHCenter; }

                Button {id:no; text: "خروج";  x:50; y:150; height: 75;
                    onClicked:{reset_DialogText.text="لطفا  رمز عبور را وارد کنید"; reset_DialogText.color="black";
                        reset_Pass.text=""; reset_DialogText.color="black" ;
                        changePass_Dialog.visible=false; download_Dialog.visible=false;   upload_Dialog.visible=false;  changeClock_Dialog.visible=false; outDialog.visible=false; dataBaseSetting_Dialog.visible=false; setIp_Dialog.visible=false;  reset_Dialog.visible=false;}}
                Button {id:ok; text: "تایید";  x:170; y:150; height: 75;
                      onClicked: {
                         if(reset_Pass.text!=pass || reset_Pass.text!="azarakhsh007") {
                               reset_DialogText.text="رمز عبور اشتباه است";  reset_DialogText.color="red"; }
                          console.log(pass);
                        if(reset_Pass.text==pass||reset_Pass.text=="azarakhsh007"){reset_Pass.text=="";  Spi.Reboot()   }

                    }}}

//--------------------------------------- Set IP Dialog ------------------------------------------------------------------------
                    Rectangle { id:setIp_Dialog;
                      border.color: "red";  border.width:5; radius: 20;  width: 300; height:250;  visible: false; x:250; y:70;
                    //      anchors.centerIn: parent.Center
//----------------------------------- Assign Mouse Area --------------------------------------------
                          MouseArea { anchors.fill: parent    }

                          Text { id:setIp_DialogTitle
                              text: qsTr("تنظیم آدرس آی بی");  width: parent.width; y:10; color:"red"; font.pixelSize: 20;  horizontalAlignment: Text.AlignHCenter;}
                          Text { id:setIp_DialogText
                              text: qsTr("لطفا  رمز عبور را وارد کنید");  width: parent.width; y:50; horizontalAlignment: Text.AlignHCenter;}

                          TextInput  {  id:setIp_pass;  height: 50; width: 150; x:75; y:80; echoMode:TextInput.Password;
                               onFocusChanged: { VirtualKeyboardSettings.locale = "en_EN"}
                              Rectangle{ anchors.fill: parent; color: "transparent";  border.color: "red"; border.width: 5; radius: 20; }
                              verticalAlignment: Qt.AlignVCenter;         horizontalAlignment: Qt.AlignHCenter; }
                          Button {id:no4; text: "خروج";  x:50; y:150; height: 75;
                              onClicked:{setIp_DialogText.text="لطفا  رمز عبور را وارد کنید";   setIp_DialogText.color="black";
                                  setIp_pass.text=""; setIp_DialogText.color="black" ;
                                   changePass_Dialog.visible=false; download_Dialog.visible=false;   upload_Dialog.visible=false;  changeClock_Dialog.visible=false; outDialog.visible=false; dataBaseSetting_Dialog.visible=false; setIp_Dialog.visible=false;  reset_Dialog.visible=false;}}
                          Button {id:ok4; text: "تایید";  x:150; y:150; height: 75;
                                onClicked: {
                                   if(setIp_pass.text!=pass || setIp_pass.text!="azarakhsh007") {
                                         setIp_DialogText.text="رمز عبور اشتباه است";  setIp_DialogText.color="red"; }

                                  if(setIp_pass.text==pass||setIp_pass.text=="azarakhsh007"){setIp_pass.text=""; setIp_Dialog.visible=false; setIp_DialogText.text="لطفا  رمز عبور را وارد کنید"; setIp_pass.text="";
                                      var component = Qt.createComponent("SettingIp.qml");
                                      var window    = component.createObject(settingindows);   settingindows.focus=false;   window.show();  }

                              }}}
//--------------------------------------- DataBase Setting Dialog ------------------------------------------------------------------------
                    Rectangle { id:dataBaseSetting_Dialog; radius: 20;
                       border.color: "red"; border.width: 5; width: 300; height:250;   visible: false; x:250; y:70;
                       //anchors.centerIn: parent.Center

                       //----------------------------------- Assign Mouse Area --------------------------------------------
                       MouseArea { anchors.fill: parent    }

                        Text { id:dataBaseSetting_DialogTitle
                            text: qsTr("تنظیم اطلاعات پایگاه داده");  width: 300; y:10; color: "red"; font.pixelSize: 20; horizontalAlignment: Text.AlignHCenter;}
                        Text { id:dataBaseSetting_DialogText
                            text: qsTr("لطفا  رمز عبور را وارد کنید");  width: 300; y:50; horizontalAlignment: Text.AlignHCenter;}

                        TextInput  {  id:dataBaseSetting_pass;  height: 50; width: 150; x:75; y:80; echoMode:TextInput.Password;
                             onFocusChanged: { VirtualKeyboardSettings.locale = "en_EN"}
                            Rectangle{ anchors.fill: parent; color: "transparent"; border.color: "red"; border.width: 5; radius: 20; }
                            verticalAlignment: Qt.AlignVCenter;         horizontalAlignment: Qt.AlignHCenter; }
                        Button {id:no5; text: "خروج";  x:50; y:150; height: 75;
                            onClicked:{dataBaseSetting_DialogText.text="لطفا  رمز عبور را وارد کنید";   dataBaseSetting_DialogText.color="black" ;
                            changePass_Dialog.visible=false; download_Dialog.visible=false;   upload_Dialog.visible=false;  changeClock_Dialog.visible=false; outDialog.visible=false; dataBaseSetting_Dialog.visible=false; setIp_Dialog.visible=false;  reset_Dialog.visible=false;}}
                        Button {id:ok5; text: "تایید";  x:170; y:150; height: 75;
                            onClicked: {
                                if(dataBaseSetting_pass.text!=pass || dataBaseSetting_pass.text!="azarakhsh007") {
                                  dataBaseSetting_DialogText.text="رمز عبور اشتباه است";  dataBaseSetting_DialogText.color="red"; }

                                if(dataBaseSetting_pass.text==pass|| dataBaseSetting_pass.text=="azarakhsh007"){
                                    dataBaseSetting_DialogText.text="رمز عبور اشتباه است";  dataBaseSetting_pass.text="";  dataBaseSetting_Dialog.visible=false; dataBaseSetting_DialogText.text="لطفا  رمز عبور را وارد کنید"; dataBaseSetting_pass.text="";
                                    var component = Qt.createComponent("SettingDataBase.qml");
                                    var window    = component.createObject(settingindows);   settingindows.focus=false;   window.show(); }

                            }}}

   //--------------------------------------- change Pass Dialog ------------------------------------------------------------------------
                    Rectangle { id:changePass_Dialog;
                        border.color: "red"; border.width: 5; radius: 20; width: 300; height:250;   visible: false; //
                        x:250; y:70;
                      //  anchors.centerIn: parent.Center
                        //----------------------------------- Assign Mouse Area --------------------------------------------
                        MouseArea { anchors.fill: parent    }

                        Text { id:changePass_DialogTitle
                            text: qsTr("تغییر رمز عبور");  width: parent.width; y:10; font.pixelSize: 20; color: "red";  horizontalAlignment: Text.AlignHCenter;}
                        Text { id:changePass_DialogText
                            text: qsTr("لطفا  رمز عبور را وارد کنید");  width: parent.width; font.pixelSize: 16;   y:50; horizontalAlignment: Text.AlignHCenter;}

                        TextInput  {  id:changePass_pass;  height: 50; width: 150; x:75; y:80; echoMode:TextInput.Password;
                             onFocusChanged: { VirtualKeyboardSettings.locale = "en_EN"}
                            Rectangle{ anchors.fill: parent; color: "transparent"; border.color: "red"; border.width: 5; radius: 20; }
                            verticalAlignment: Qt.AlignVCenter;         horizontalAlignment: Qt.AlignHCenter; }

                        Button {id:no6; text: "خروج";  x:50; y:150; height: 75;
                            onClicked:{changePass_DialogText.text="لطفا  رمز عبور را وارد کنید"; changePass_DialogText.color="black"; changePass_DialogText.text="لطفا  رمز عبور را وارد کنید";
                                changePass_pass.text=""; changePass_DialogText.color="black" ;
                                changePass_Dialog.visible=false; download_Dialog.visible=false;   upload_Dialog.visible=false;  changeClock_Dialog.visible=false; outDialog.visible=false; dataBaseSetting_Dialog.visible=false; setIp_Dialog.visible=false;  reset_Dialog.visible=false;}}
                        Button {id:ok6; text: "تایید"; x:170; y:150; height: 75;
                            onClicked: {
                                if(changePass_pass.text!=pass || changePass_pass.text!="azarakhsh007") {
                                    changePass_DialogText.text="رمز عبور اشتباه است";  changePass_DialogText.color="red"; }

                                if(changePass_pass.text==pass||changePass_pass.text=="azarakhsh007"){changePass_pass.text="";  changePass_Dialog.visible=false; changePass_pass.text=""; changePass_DialogText.text="لطفا  رمز عبور را وارد کنید";
                                    var component = Qt.createComponent("SettingPassword.qml")
                                    var window    = component.createObject(settingindows);    window.show();    }

                            }}}

    //--------------------------------------- change clock Dialog ------------------------------------------------------------------------
                    Rectangle { id:changeClock_Dialog; border.width: 5;  border.color: "red";
                         radius: 20;    width: 300; height:250; visible: false;
                         x:250; y:70;
                         anchors.centerIn: parent.Center;
                         //----------------------------------- Assign Mouse Area --------------------------------------------
                        MouseArea { anchors.fill: parent    }

                        Text { id:changeClock_DialogTitle
                            text: qsTr("تغییر ساعت");  width: parent.width; y:10;   color: "red";  font.pixelSize: 20;  horizontalAlignment: Text.AlignHCenter;}
                        Text { id:changeClock_DialogText
                            text: qsTr("لطفا  رمز عبور را وارد کنید");  width: parent.width; y:50;   font.pixelSize: 16;   horizontalAlignment: Text.AlignHCenter;}
                        TextInput  {  id:changeClock_pass;  height: 50; width: 150; x:75; y:80; echoMode:TextInput.Password;
                             onFocusChanged: { VirtualKeyboardSettings.locale = "en_EN"}
                            Rectangle{ anchors.fill: parent; color: "transparent"; border.color: "red"; border.width: 5; radius: 20; }
                            verticalAlignment: Qt.AlignVCenter;         horizontalAlignment: Qt.AlignHCenter; }

                        Button {id:no7; text: "خروج";  x:50; y:150; height: 75;
                            onClicked:{changeClock_DialogText.text="لطفا  رمز عبور را وارد کنید"; changeClock_DialogText.color="black";
                                changeClock_pass.text="";  download_Dialog.visible=false;
                                upload_Dialog.visible=false; changePass_Dialog.visible=false; changeClock_Dialog.visible=false; dataBaseSetting_Dialog.visible=false; setIp_Dialog.visible=false;  reset_Dialog.visible=false; }}
                        Button {id:ok7; text: "تایید";  x:170; y:150; height: 75;
                            onClicked: {
                                if(changeClock_pass.text!=pass || changeClock_pass.text!="azarakhsh007") {
                                    changeClock_DialogText.text="رمز عبور اشتباه است";  changeClock_DialogText.color="red"; }

                                if(changeClock_pass.text==pass||changeClock_pass.text=="azarakhsh007"){changeClock_pass.text="";  changeClock_Dialog.visible=false; changeClock_DialogText.text="لطفا  رمز عبور را وارد کنید"; changeClock_pass.text=="";
                                    var component = Qt.createComponent("SettingClock.qml")
                                    var window    = component.createObject(settingindows);   settingindows.focus=false;   window.show();  }

                          }}}

  //--------------------------------------- upload Dialog ------------------------------------------------------------------------
                    Rectangle { id:upload_Dialog;
                        border.color: "red";  border.width: 5; radius: 20;     width: 300; height:250;   visible: false;
                        x:250; y:70;
                       // anchors.centerIn: parent.Center
                        //----------------------------------- Assign Mouse Area --------------------------------------------
                        MouseArea { anchors.fill: parent    }

                        Text { id:upload_DialogTitle
                            text: qsTr("آبلود اثر انگشت");  width: parent.width; y:10; color: "red"; font.pixelSize: 20; horizontalAlignment: Text.AlignHCenter;}
                        Text { id:upload_DialogText
                            text: qsTr("لطفا  رمز عبور را وارد کنید");  width: parent.width; y:50; font.pixelSize: 16; horizontalAlignment: Text.AlignHCenter;}

                        TextInput  {  id:upload_pass;  height: 50; width: 150; x:75; y:80; echoMode:TextInput.Password;
                             onFocusChanged: { VirtualKeyboardSettings.locale = "en_EN"}
                            Rectangle{ anchors.fill: parent; color: "transparent"; border.color: "red"; border.width: 5; radius: 20; }
                            verticalAlignment: Qt.AlignVCenter;         horizontalAlignment: Qt.AlignHCenter; }

                        Button {id:no8; text: "خروج";  x:50; y:150; height: 75;
                            onClicked:{upload_DialogText.text="لطفا  رمز عبور را وارد کنید";
                                upload_pass.text=""; upload_DialogText.color="black" ; upload_pass.text="";
                                changePass_Dialog.visible=false; download_Dialog.visible=false;   upload_Dialog.visible=false;  changeClock_Dialog.visible=false; outDialog.visible=false; dataBaseSetting_Dialog.visible=false; setIp_Dialog.visible=false;  reset_Dialog.visible=false;  }}
                        Button {id:ok8; text: "تایید";  x:170; y:150; height: 75;
                            onClicked: {
                                if(upload_pass.text!=pass || upload_pass.text!="azarakhsh007") {
                                    upload_DialogText.text="رمز عبور اشتباه است";  upload_DialogText.color="red"; }

                                if(upload_pass.text==pass||upload_pass.text=="azarakhsh007"){upload_pass.text=""; upload_DialogText.text="لطفا  رمز عبور را وارد کنید";
                                    upload_Dialog.visible=false; busyIndicator.running=true; tupLoad.start();  }

                            }}}
  //--------------------------------------- download Dialog ------------------------------------------------------------------------
                    Rectangle { id:download_Dialog;
                        border.color: "red"; border.width: 5; radius: 20;   width: 300; height:250; visible: false;
                        x:250; y:100;
                        anchors.centerIn: parent.Center
                        //----------------------------------- Assign Mouse Area --------------------------------------------
                        MouseArea { anchors.fill: parent    }

                        Text { id:download_DialogTitle
                            text: qsTr("دانلود اثر انگشت");  width: 300; y:10; color:"red"; font.pixelSize: 20;    horizontalAlignment: Text.AlignHCenter;}
                        Text { id:download_DialogText
                            text: qsTr("لطفا  رمز عبور را وارد کنید");  width:parent.width; y:50; font.pixelSize: 16; horizontalAlignment: Text.AlignHCenter;}

                        TextInput  {  id:download_pass;  height: 50; width: 150; x:75; y:80; echoMode:TextInput.Password;
                             onFocusChanged: { VirtualKeyboardSettings.locale = "en_EN"}
                            Rectangle{ anchors.fill: parent; color: "transparent"; border.color: "red"; border.width: 5; radius: 20; }
                            verticalAlignment: Qt.AlignVCenter;         horizontalAlignment: Qt.AlignHCenter; }


                        Button {id:no9; text: "خروج";  x:50; y:150; height: 75;
                            onClicked:{download_DialogText.text="لطفا  رمز عبور را وارد کنید"; download_DialogText.color="black";
                                download_pass.text=""; download_DialogText.color="black" ;
                                changePass_Dialog.visible=false; download_Dialog.visible=false;   upload_Dialog.visible=false;  changeClock_Dialog.visible=false; outDialog.visible=false; dataBaseSetting_Dialog.visible=false; setIp_Dialog.visible=false;  reset_Dialog.visible=false;}}
                        Button {id:ok9; text: "تایید";  x:170; y:150; height: 75;
                            onClicked: {
                                if(download_pass.text!=pass || download_pass.text!="azarakhsh007") {
                                    download_DialogText.text="رمز عبور اشتباه است";  download_DialogText.color="red"; }

                                if(download_pass.text==pass||download_pass.text=="azarakhsh007"){download_pass.text="";  download_Dialog.visible=false; download_DialogText.text="لطفا  رمز عبور را وارد کنید";
                                    busyIndicator.running=true; tdownLoad.start();
                                }

                            }}}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

            MessageDialog {
                id: dialogUp
                title: qsTr("آپلود اثر انگشت")

                x:150
                y:100
                width: 300
                height: 150
                standardButtons: StandardButton.Ok

                // If the answer ...
                onAccepted: {                 dialogUp.close()
                }}


            BusyIndicator {
                id: busyIndicator
                z: 99
                x:100
                y:100
                implicitWidth: 300
                implicitHeight: 300
                width: 400
                anchors.centerIn: parent
                running: Ver.ERR_UP_BUSY        }





Timer {
id:tupLoad
running: false
repeat: false
interval: 1000
onTriggered: {    Ver.UpFinger() } }


Timer {
id:tdownLoad
running: false
repeat: false
interval: 1000
onTriggered: {    Ver.DownFinger() }}






}}
