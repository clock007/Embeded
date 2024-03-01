import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.VirtualKeyboard 2.0
import QtQuick.VirtualKeyboard.Settings 2.0
import QtQuick.VirtualKeyboard.Styles 2.0
import QtMultimedia 5.3
import QtQuick.Dialogs 1.2
Item {
    id: edit
    width: Screen.width
    height:Screen.height
    x:0
    y:0
    visible: true


MouseArea{ anchors.fill: parent    }

EditionList {
    id:editionList}


Rectangle {
        id:back
        anchors.fill: parent
        gradient:
        Gradient {
            GradientStop {position: 0.0; color: "cyan"}
            GradientStop {position: 1; color: "blue"} }

        property string statusresult:Sp.ERR_STATUS
        property string checkuser:Sp.ERR_ChekDuplicateId;
        property string emptyidresult:Sp.ERR_GetEmptyId
        property string image1result:Sp.ERR_Image1
        property string image2result:Sp.ERR_Image2
        property string image3result:Sp.ERR_Image3
        property string generateresult1:Sp.ERR_Generate1
        property string generateresult2:Sp.ERR_Generate2
        property string generateresult3:Sp.ERR_Generate3
        property string mergeresult:Sp.ERR_MERGE
        property string storeresult:Sp.ERR_STORE
        property string rfid: Sp.ERR_RFID
        property int fingerIdL: Sp.ERR_FingerIdL
        property int fingerIdH: Sp.ERR_FingerIdH
        //property int stat: Ver.ERR_STATE
        property int state: 0
        property int stored: 0
        property  string checkDuplicateCardno: Sp.ERR_ChekDuplicateCardNo
       // onRfidChanged: { cardno.text="000"}



        TextInput {
            id: name
            text:Sp.ERR_EDIT_NAME
            x:350
            y:10
            width:250
            height: 37
            font.pointSize: 17
            color: "red"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            Component.onCompleted:   {
            VirtualKeyboardSettings.locale = "fa_IR";  VirtualKeyboardSettings.customLayoutsOnly = true}
            onTextChanged: {  VirtualKeyboardSettings.locale = "fa_IR";  VirtualKeyboardSettings.customLayoutsOnly = true}


            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: "blue"
                radius: 30   }   }



        ComboBox {
            id:accesstype
            x: 0
            y:7
            width: 150

            model: [ "کاربر", "ادمین", "سایر" ]

        background: Rectangle {
        implicitWidth: 200
        implicitHeight: 25
        color: "#FFFFFF"
        border.width: 1
        border.color: !accesstype.enabled ? "#DADAD9" : accesstype.activeFocus ? "#3C3C3B" : "#9D9C9C"
          }}


        TextInput {
            id: cardno
            text: Sp.ERR_EDIT_CARDNO
            x:350
            y:60
            width:250
            height: 37
            font.pointSize: 16
            color: "red"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            inputMethodHints: Qt.ImhDigitsOnly
           // focus: true
           Component.onCompleted:   { VirtualKeyboardSettings.locale = "en_EN" }
           onFocusChanged: {VirtualKeyboardSettings.locale = "en_EN" }
               // {console.log("fgfgd");   VirtualKeyboardSettings.locale = "en_EN"}
          //onTextChanged: {console.log("fgfgd");   VirtualKeyboardSettings.locale = "en_EN"}
            Rectangle {
                anchors.fill: parent
                color: "transparent"
                border.color: "blue"
                radius: 30

                } }

        TextInput {
            id: id
            text: Sp.ERR_EDIT_ID
            x:0
            y:60
            width:130
            height: 37
            font.pointSize: 17
            color: "red"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            //focus: true
           inputMethodHints: Qt.ImhDigitsOnly

           onTextChanged:
             {   VirtualKeyboardSettings.locale = "en_EN"}
            Rectangle { anchors.fill: parent;   color: "transparent";  border.color: "blue"; radius: 30     }}


      Text {id:nametxt
          text:"نام و  خانوادگی"
          //color: "white"
          font.pointSize: 17
          font.bold: true
          x:610
          y:10}

      Text {id:accesstypetxt;      text:"سطح دسترسی";  font.pointSize: 17;   font.bold: true;   x:150;  y:10 }


      Text {

          id:rftext
          text:"شماره کارت"
          //color: "white"
          font.pointSize: 17
          font.bold: true
          x:610
          y:50
      }

      Text {

          id:idtext
          text:"شناسه"
          //color: "white"
          font.pointSize: 17
          font.bold: true
          x: 150
          y:50
      }





  Butt2 {
   id:capture
   btext: "ثبت اثر انگشت"
   bheight:50;    bwidth: 150
   x:0;   y:110
         onBclicked:  {

          Sp.Delete_Current_Finger();
          back.state=0; state=0;
          //   back.statusresult
          //   back.statusresult=""; back.checkuser=""; back.emptyidresult="";   back.image1result=""; back.image2result=""; back.image3result="";
           //  back.generateresult1=""; back.generateresult2=""; back.generateresult3=""; back.mergeresult=""; back.storeresult="";
         Sp.Clear2();
         //back.chekuser="";  back.statusresult=""; back.emptyidresult=""; bac0k.image1result=""; back.image1result=""; back.image2result=""; back.image3result=""; back.generateresult1=""; back.generateresult2=""; back.generateresult3=""; back.storeresult=""; back.mergeresult=""; back.rfid="";
         //fingerIdL=0; fingerIdH=0; stat=0;
         please2.text=""; please3.text="";
         Sp.CheckDuplicateId(id.text);      }
      }


Butt2 {
     id:takePicture
     btext: "ثبت تصویر"
     bheight:50;      bwidth: 150
     x:0;      y:200
     onBclicked: {myFace.visible=true;  timagestream.start();}}




Butt2 {
    id:save
    bheight: 50;    bwidth:150
    x:0;     y:290
    btext: "ذخیره";
    onBclicked:  {
        // Again Check id Number
       Fingers.Reset_CardnoChecker(); Sp.CheckDuplicateCardNo(cardno.text,id.text);   }}


Butt2 {
id:exit
btext: "خروج"
bheight: 50; bwidth:150
bx:0;  by:380
onBclicked:  {
    console.log("-----------------------------------")
    console.log("Detailes ERR_STORE and Stored:     ")
    console.log(Sp.ERR_STORE)

   if (Sp.ERR_STORE=="با موفقیت ذخیره شد" && (back.stored==0) ) { dialog_incompleteSignature.text="رکورد شما ذخیره نشده است. آیا رکورد جاری حذف شود";  dialog_incompleteSignature.open()  }
   if ((Sp.ERR_STORE=="با موفقیت ذخیره شد" && (back.stored==1))|| Sp.ERR_STORE!="با موفقیت ذخیره شد" ) {
   Sp.Clear(); trwimage.stop(); terrorreset.stop();   tprocess2.stop(); tprocess3.stop(); trwimage.stop();
   Sp.CloseSerial();  edit.visible=false; editionList.mysignal(); VirtualKeyboardSettings.locale = "fa_IR";
   back.statusresult="";back.checkuser="";  emptyidresult=""; image1result=""; image1result=""; image2result=""; image3result=""; generateresult1=""; generateresult2=""; generateresult3=""; storeresult=""; mergeresult=""; rfid="";  fingerIdL=0; fingerIdH=0; //stat=0;
   back.stored=0;
   Sp.Delete_Captured();
   please1.text="";  please2.text=""; please3.text=""; edit.deleteLater();}}}




Component.onCompleted: {   state=0;           }

onCheckuserChanged: { console.log("Check User Duplicate Completed"); if(checkuser=="شناسه معتبر است" && state==0) { state=1; Sp.GetEmptyId();    } }
onEmptyidresultChanged: {console.log("Empty id Assigned"); if (emptyidresult!="" && emptyidresult!="حافظه تکمیل است" && state==1 ) {state=2; trwimage.restart(); please1.text="لطفا برای بار اول انگشت خود را روی سنسور بگذارید"; }   }

onImage1resultChanged: {if (image1result!="" && state==2 ) {state=3;console.log("image1 Changed");  trwimage.stop();     }  }
onGenerateresult1Changed: { if (generateresult1!="" && state==3  ) {state=4;  console.log("Step1 Done");  tprocess2.start();     }  }

onImage2resultChanged: {if (image2result!="" && state==4 ) { state=5; console.log("image2 Changed");    trwimage.stop();  }    }
onGenerateresult2Changed: { if (generateresult2!="" && state==5 ) { state=6; console.log("Step2 Done");  tprocess3.start(); } }

onImage3resultChanged: {if (image3result!="" && state==6 ) { state=7; console.log("image3 Changed");  trwimage.stop();  }  }
onGenerateresult3Changed: {if (generateresult3!=""&& state==7  ){ state=8; console.log("Step3 Done"); Sp.f_Merge(); }  }

onMergeresultChanged: { if (mergeresult!="" && mergeresult=="خطا در تلفیق") terrorreset.restart();
if (mergeresult!="" && mergeresult!="خطا در تلفیق" && state==8) {state=9; console.log("Merge Done"); Sp.f_Store();}  }
onStoreresultChanged: { if (storeresult!="" && storeresult!="این انگشت قبلا ذخیره شده است" && state==9 ) { state=10; console.log("Store Done"); }}

onRfidChanged: { cardno.text=Sp.ERR_RFID  }



onCheckDuplicateCardnoChanged: {   // if card Used Before, dialogSign WARNS!
                                  if(checkDuplicateCardno=="card"){ dialogSign.text="این کارت قبلا مورد استفاده قرار گرفته است"; dialogSign.open();// Sp.Reset_CardnoChecker();
                                  }
                                  if(checkDuplicateCardno=="id"){ dialogSign.text="این شناسه مورد استفاده قرار گرفته است"; dialogSign.open();// Sp.Reset_CardnoChecker();
                                  }

                                  if(checkDuplicateCardno=="no"){
                                       console.log("Checked Duplicate Cardno");
                                       if(name.text=="")  { console.log("Empty name");   dialogSign.text="لطفا نام و نام خانوادگی خود را وارد کنید";  dialogSign.open();// Sp.Reset_CardnoChecker();
                                       }
                                       if((id.text=="0" && name.text!="") || (id.text==""&& name.text!="" ))  {   console.log("Empty id");   dialogSign.text="لطفا شناسه  خود را وارد کنید";  dialogSign.open();// Sp.Reset_CardnoChecker();
                                       }


                                       //--------------------------------------------------------------------------------
                                       //----------------if card and Id Doesnot used before, it Saves--------------------
                                       if(id.text!="0" && name.text!="" && accesstype.currentText!="" ) {
                                        stored=1; back.stored=1;    dialogSign.text="رکورد با موفقیت ثبت شد";  dialogSign.open();
                                        Sp.Updater(id.text, name.text, cardno.text,accesstype.currentText)
                                        myModel.updateModel();       Ver.UpdateModel(id.text);        }
                                       // Sp.TestPrint;
                                        }
}//end

////////   incomplete Dialog ///////////////////////////
//----------------Text--------------------------------------

Text {
 id : connectionTest
 text: Sp.ERR_ChekDuplicateId
 x:300; y:120
 font.pointSize: 14
 color: "black"}

Text {
 id : assignid
 text: Sp.ERR_GetEmptyId
 x:300
 y:140
 font.pointSize: 14
 color: "black"
}
//---------
Text {
 id : please1

 x:540
 y:170
 font.pointSize: 14
 color: "black"
}
Text {
 id : readimage1
 text: Sp.ERR_Image1
 x:350
 y:170
 font.pointSize: 14
 color: "black"
}


Text {
 id : generator1
 text: Sp.ERR_Generate1
 x:120
 y:170
 font.pointSize: 14
 color: "black"
}

//---------
Text {
  id : please2

  x:540
  y:210
  font.pointSize: 14
  color: "black"
}
Text {
  id : readimage2
  text: Sp.ERR_Image2
  x:350
  y:210
  font.pointSize: 14
  color: "black"
}


Text {
  id : generator2
  text: Sp.ERR_Generate2
  x:120
  y:210
  font.pointSize: 14
  color: "black"
}

//---------
Text {
   id : please3

   x:540
   y:250
   font.pointSize: 14
   color: "black"
}
Text {
   id : readimage3
   text: Sp.ERR_Image3
   x:350
   y:250
   font.pointSize: 14
   color: "black"
}


Text {
   id : generator3
   text: Sp.ERR_Generate3
   x:120
   y:250
   font.pointSize: 14
   color: "black"}

Text {
   id:merge
   text:Sp.ERR_MERGE
   x:300
   y:300
   font.pointSize: 14
   color: "black"}

Text {
   id:store
   text:Sp.ERR_STORE
   x:300
   y:335
   font.pointSize: 14
   color: "black"}
//------------------------------------ incomplete Signature Dialogues (Rectangle) ------------------------------------------------------
Rectangle {
    id:incompleteSignature;
    radius: 20;    width: 350; height:200;
    visible: false; x:320; y:100;
    anchors.centerIn: parent.Center
    Text { id:incompleteSignature_Text;  width: parent.width; color: "red"; font.pixelSize: 18;
        text: qsTr("رکوزد ثبت نام شده ذخیره نشده است");  horizontalAlignment: Text.AlignHCenter; }
    Button {id:out; text: "خروج";  x:20; y:125; width: 80;
        onClicked:{incompleteSignature_Text.text="رکوزد ثبت نام شده ذخیره نشده است";incompleteSignature.visible=false ;  }}
    Button {id:del; text: "حذف داده ها";  x:230; y:125; width: 80
        onClicked:{ Sp.Delete_Unwanted_Finger(); back.state=0; state=0;
            back.statusresult=""; back.checkuser=""; back.emptyidresult="";   back.image1result=""; back.image2result=""; back.image3result="";  back.generateresult1="";
            back.generateresult2=""; back.generateresult3=""; back.mergeresult=""; back.storeresult=""; please1.text=""; please2.text=""; please3.text="";
           Sp.Clear2(); incompleteSignature.text="رکورد ثبت شده حذف شد";        }}}
//------------------------------------------  incomplete Signature Dialogues -------------------------------------------------
    MessageDialog {
        id: dialogSign
        title: qsTr("ثبت نام")
        //x:150        y:100

       standardButtons: StandardButton.Ok

       onAccepted: { dialogSign.close()      }
       onDiscard:  {  dialogSign.close()    }}

    MessageDialog {
        id: dialog_incompleteSignature
        title: qsTr("رکورد شما ذخیره نشده است. آیا رکورد جاری حذف شود")
        standardButtons: StandardButton.Ok | StandardButton.No

        onAccepted: {  console.log("Current record Delete");
            Sp.Delete_Unwanted_Finger(); state=0;
            back.statusresult=""; back.checkuser=""; back.emptyidresult="";   back.image1result=""; back.image2result=""; back.image3result="";  back.generateresult1="";
            back.generateresult2=""; back.generateresult3=""; back.mergeresult=""; back.storeresult=""; please1.text=""; please2.text=""; please3.text="";
           Sp.Clear2();         }
        onDiscard:  {  console.log("Current record Doesnot Delete");   dialogSign.close()    }}

//----------------------  Personal Picture Capture ------------------------------
//-------------------------------------------------------------------------------



    Rectangle {
    id:myFace
    x:200; y:20
    width: 400
    height: 400
    color: "blue"
    visible: false

    Image {  id: myFace_Pic
            fillMode: Image.PreserveAspectFit
            cache: false;
            x:10;     y:0;
             width: 384; height:288;}
             //Rectangle {x:45;     y:20;  width: 180; height: 180; color: "transparent" ; border.color: "green"; border.width: 5;    }}
    Butt2 {
    x:150; y:300
    bheight: 50;  bwidth:100
    btext: "خروج";
    onBclicked: { timagestream.stop(); timagestream.repeat=false;   myFace.visible=false;   }}
    Text {x:100; y:350;  text:Fingers.ERR_SAVEDPIC; }}


    Timer {
     id:timagestream
     running: false
     repeat: true
     interval: 200
     onTriggered: { console.log("---------------on Capturing---------------")
         timagestream.repeat=true; Fingers.Detector();   myFace_Pic.source= ""; myFace_Pic.source= "image://ID1//image"
     }}



Timer {
 id:trwimage

    interval: 300;
    repeat: true
    onTriggered: {console.log("Error Timer 1"); Sp.f_RW_Image(); }
}

Timer {
 id:tprocess2
    interval: 3000;
    repeat: false
    running:false
    onTriggered: {console.log("Error Timer 2 "); please2.text= "لطفا برای بار دوم انگشت خود را روی سنسور بگذارید"; trwimage.restart();    }
}



Timer {
 id:tprocess3
    running: false
    interval: 3000;
    repeat: false
    onTriggered: { console.log("Error Timer 3"); please3.text= "لطفا برای بار سوم انگشت خود را روی سنسور بگذارید";  trwimage.restart();    }
}




Timer{
   id:terrorreset
   interval: 3000;
   repeat: false
   onTriggered: { console.log("Error Timer 4"); edit.state=0; Sp.Clear2(); please1.text="";  please2.text=""; please3.text=""; }

}




} //Rectangle







//----------------------------------

InputPanel {
    id: inputPanel
    z: 99
    x: 0
    y: window.height
    width: window.width

    states: State {
        name: "visible"
        when: inputPanel.active
        PropertyChanges {
            target: inputPanel
            y: window.height - inputPanel.height
        }
    }
    transitions: Transition {
        from: ""
        to: "visible"
        reversible: true
        ParallelAnimation {
            NumberAnimation {
                properties: "y"
                duration: 250
                easing.type: Easing.InOutQuad
            }
        }
    }
    Component.onCompleted: {    console.log("locales available: " + VirtualKeyboardSettings.availableLocales)
        console.log("Locale before changing it: " + VirtualKeyboardSettings.locale)
        //VirtualKeyboardSettings.locale = "fa_IR"
        console.log("Locale after changing it: " + VirtualKeyboardSettings.locale) }
} /// ّInputPanel



}

