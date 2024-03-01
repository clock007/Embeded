import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Dialogs 1.1
import QtQuick.VirtualKeyboard 2.0
import QtQuick.VirtualKeyboard.Settings 2.2
import QtQuick.Window 2.0
Item {
    id:datawindows
    visible: true
    width: Screen.width
    height: Screen.height
    signal mysignal()
    onMysignal: {
        console.log("OpenSerialPort");          Ver.OpenSerialports(); }


    property string pass: Spi.ERR_PASSWORD
//------------------------------------- Back Ground ------------------------------------------------
    Rectangle {
        id:rect2;
        anchors.fill: parent
        gradient:
            Gradient {
            GradientStop {position: 0.0; color: "cyan"}
            GradientStop {position: 1; color: "blue"}}
//-----------------------------------  Button Row 1 --------------------------------------------------

    Butt {
        id:bsign
        //bx:50;        by:50
        bx:Screen.width/16;        by:Screen.height/9.6
        bicon: "qrc:/zAdduser.png"
        btext: "ثبت نام کاربر"
        onBclicked: {
            signDialog.visible=true;  delDialog.visible=false;  removeAllDialog.visible=false;}}


    Butt {
        id:bremoveusers
        //bx:300;     by:50
        bx:Screen.width/2.66;        by:Screen.height/9.6
        bicon: "qrc:/zRemoveUser.png";        btext: "حذف کاربر";
        onBclicked: {
       delDialog.visible=true; signDialog.visible=false; removeAllDialog.visible=false; }}

    Butt {
        id:bshowuser
        //bx:550;     by:50
        bx:Screen.width/1.45;        by:Screen.height/9.6
        bicon: "qrc:/zUserList.png";
        btext: "لیست کاربران"
        onBclicked: {
            Spi.Beeper();
            myModel.updateModel();   var component = Qt.createComponent("ShowUser.qml");
            var window    = component.createObject(datawindows);  datawindows.focus=false;    window.show();    }}

//----------------------------------------  Button Row 2----------------------------------------------------------

    Butt {
        id:bdisplaylogs;
        bicon: "qrc:/zPrintedFactors.png";
        //bx:50;        by:175
        bx:Screen.width/16;        by:Screen.height/2.74
        btext: "لیست حضور کاربران"
        onBclicked: {
            Spi.Beeper();
            myModel.updateModel2();        var component = Qt.createComponent("ShowLogs.qml")
            var window    = component.createObject(datawindows);   datawindows.focus=false;   window.show();     }}


    Butt {
          id:btestprint
          bicon: "qrc:/zPrinter.ico";
         // bx:300;          by:175
          bx:Screen.width/2.66;        by:Screen.height/2.74
          btext: "تست پرینتر و صدا"
          onBclicked: {  Ver.TestPrint();  }}
    Butt {
    id:bformat
    //bx:550;    by:175
    bx:Screen.width/1.45;        by:Screen.height/2.74
    bicon: "qrc:/zDeleteAll.png"
    btext: "حذف کلیه اطلاعات
کاربران"
    onBclicked: {  removeAllDialog.visible=true; signDialog.visible=false;  delDialog.visible=false;
    }}


//----------------------------------------------  Button Row 3--------------------------------------------

    Butt {
        id:btestSerials;
        bicon: "qrc:/zCheck.png";
        //bx:50;        by:300
        bx:Screen.width/16;        by:Screen.height/1.6
        btext: "اتصالات سریال"
        onBclicked: {
            Ver.Check_SerialPorts();   var component = Qt.createComponent("CheckPage.qml");
            var window    = component.createObject(datawindows);   datawindows.focus=false;   window.show();     }}



    Butt {
        id:bEdition;
        bicon: "qrc:/zEdit.png";
        //bx:300;        by:300
         bx:Screen.width/2.66;        by:Screen.height/1.6
        btext: "ویرایش"
        onBclicked: { myModel.updateModel4();
              var component = Qt.createComponent("EditionList.qml");
            var window    = component.createObject(datawindows);   datawindows.focus=false;   window.show();     }}





//------------------------------------------------- Remove All ---------------------------------------------------------------
                Rectangle{
                    id:removeAllDialog; radius: 10;       border.color: "red";    border.width: 5;   width: 300; height:250;       visible: false
                   // anchors.centerIn: parent.Center
                    x:250; y:70;
                    //----------------------------------- Assign Mouse Area --------------------------------------------
                    MouseArea { anchors.fill: parent    }

                    Text { id:removeAllTitle
                        text: qsTr("حذف اطلاعات کلیه کاربران");  width: parent.width; y:10; color: "red"; font.pixelSize: 20; horizontalAlignment: Text.AlignHCenter;       }
                    Text { id:removeAllText
                        text: qsTr("لطفا رمز عبور را وارد کنید");  width: parent.width; y:50; font.pixelSize: 16; horizontalAlignment: Text.AlignHCenter;       }

                    TextInput  {  id:passremoveall;  height: 50; width: 150; x:75; y:80; echoMode:TextInput.Password;
                        onFocusChanged: { VirtualKeyboardSettings.locale = "en_EN"}
                        Rectangle{ anchors.fill: parent; color: "transparent"; border.color: "red"; border.width: 5; radius: 20; }
                        verticalAlignment: Qt.AlignVCenter;         horizontalAlignment: Qt.AlignHCenter; }



                    Button {id:no21; text: "خروج"; x:50; y:150; height: 75;
                        onClicked:{  removeAllText.text="لطف  رمز عبور را وارد کنید";   removeAllText.color="black";   removeAllText.color="black"; removeAllDialog.visible=false}}
                    Button {id:ok22; text: "تایید";  x:170; y:150; height: 75;
                        onClicked: {
                            if(passremoveall.text!=pass || passremoveall.text!="azarakhsh007") {
                                 removeAllText.text="رمز عبور اشتباه است";  removeAllText.color="red"; }
                                 if(passremoveall.text==pass || passremoveall=="azarakhsh007"){ passremoveall.text=""; removeAllText.text="لطف  رمز عبور را وارد کنید";
                                Ver.DeleteAll(); removeAllDialog.visible=false; }}} }
//------------------------------------------------------------------------------------------------------------------------------------------



//----------------------------------------- Dialog Box For Signature -------------------------------
    Rectangle {   id:signDialog;
        border.color: "red"; border.width: 5; radius: 20;  width: 300; height:250;  visible: false;
        //anchors.centerIn: parent.Center;
        x:250; y:70;
        //----------------------------------- Assign Mouse Area --------------------------------------------
        MouseArea { anchors.fill: parent    }

        Text {id:passSignTitle;
            text: qsTr("ثبت نام");  width: parent.width; color: "red";  y:10; font.pixelSize: 20;  horizontalAlignment: Text.AlignHCenter;}
        Text {id:passSignText;
            text: qsTr("لطفا رمز عبور را وارد کنید");  width: parent.width;  y:50; font.pixelSize: 16;  horizontalAlignment: Text.AlignHCenter;}

        TextInput {
            id:passSign;  echoMode:TextInput.Password; height: 50; width: 150; x:75; y:80
            verticalAlignment: Qt.AlignVCenter;         horizontalAlignment: Qt.AlignHCenter;
            onFocusChanged:  { VirtualKeyboardSettings.locale = "en_EN"}
            Rectangle {
                anchors.fill: parent; color: "transparent"; border.color: "red"; border.width: 5; radius: 20; }}

        Button {
            id:no; text: "خروج";  x:50; y:150; height: 75;
            onClicked:{passSignText.text="لطفا رمز عبور را وارد کنید";  passSignText.color="black";  passSign.text==""; passSign.color="black"; signDialog.visible=false}}
        Button {
            id:ok; text: "تایید";  x:170; y:150; height: 75;
            onClicked: {
                if(passSign.text==pass || passSign.text=="azarakhsh007") {
                    passSign.text="";  signDialog.visible=false; passSignText.text="لطفا رمز عبور را وارد کنید";
                    Ver.CloseAllSerial(); Ver.ClearALL(); Fingers.Clear(); Fingers.OpenSerial();
                    var component = Qt.createComponent("Signature.qml");
                    var window    = component.createObject(datawindows);  datawindows.focus=false;  window.show(); }
               if(passSign.text!=pass || passSign.text!="azarakhsh007") {
                    passSignText.text="رمز عبور اشتباه است";  passSignText.color="red"; }
    }}}

//----------------------------------------- Dialog Box For Delete  -------------------------------
    Rectangle {  id:delDialog;
        border.color: "red"; border.width: 5; radius: 10;  width: 300; height:250;  visible: false;
        //anchors.centerIn: parent.Center;
        x:250; y:70;
        //----------------------------------- Assign Mouse Area --------------------------------------------
        MouseArea { anchors.fill: parent    }

        Text {id:delDialogTitle;
            text: qsTr("حذف کاربر");  width: 300; y:10; font.pixelSize: 20; color: "red";   horizontalAlignment: Text.AlignHCenter;       }
        Text {id:delDialogText;
            text: qsTr("لطف  رمز عبور را وارد کنید"); y:50;  width: parent.width; font.pixelSize: 16;    horizontalAlignment: Text.AlignHCenter;       }

       TextInput  {  id:passDel;  echoMode:TextInput.Password; height: 50; width: 150; x:75; y:80
            verticalAlignment: Qt.AlignVCenter;         horizontalAlignment: Qt.AlignHCenter;
            onFocusChanged: {
                 VirtualKeyboardSettings.locale = "en_EN"}
            Rectangle {
                anchors.fill: parent; color: "transparent"; border.color: "red"; border.width: 5; radius: 20; }}


        Button { id:no2; text: "خروج"; x:50; y:150; height: 75;    onClicked: {delDialogText.text="لطفا رمز عبور را وارد کنید"; delDialogText.color="black";    passDel.text=="**"; passDel.color="black"; delDialog.visible=false}}
        Button { id:ok2; text: "تایید"; x:170; y:150; height: 75;
            onClicked: {
                if(passDel.text!=pass || passDel.text!="azarakhsh007") {
                    delDialogText.color="red";   delDialogText.text="رمز عبور اشتباه است"; }
                if(passDel.text==pass || passDel.text=="azarakhsh007") { delDialogText.text="لطفا رمز عبور را وارد کنید";  passDel.text=""; delDialog.visible=false
                    var component = Qt.createComponent("RemoveUser.qml");
                    var window    = component.createObject(datawindows);   datawindows.focus=false;    window.show();   }}} }
}}


