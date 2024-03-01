import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.VirtualKeyboard 2.2
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.0
import "Clock3" as Clock2

ApplicationWindow {
    id: window
    visible: true
    width: Screen.width
    height: Screen.height
   // visibility: "FullScreen"
    title: qsTr("Tabs")



    Component.onCompleted: {  name.visible=false; cardno.visible=false; text1.visible=false;
       text2.visible=false;
       Spi.SpiCheck();  treseter.start(); Spi.hwclockToSys(); }
   property int hours
   property  int resetTime:Ver.ERR_DELAY
   property string rFIDstring:Ver.VERR_READRFID;
   property string fingerNumber:Ver.VERR_READFINGER;
   property int plugin: Spi.plug
   property int stream1: Ver.ERR_STREAM1
   property int stream2: Ver.ERR_STREAM2
   property int val:Ver.VALUE
   property int sid: Ver.ERR_ID
   property string sname:Ver.ERR_NAME
   property int scardno: Ver.ERR_CARDNO
   property string ssecurity: Ver.ERR_SECURITY
   property string efood: Ver.ERR_EFood
   property string foodname1: Ver.ERR_FoodName1
   property string foodname2: Ver.ERR_FoodName2
   property string foodname3: Ver.ERR_FoodName3
   property string foodcount1: Ver.ERR_FoodCount1
   property string foodcount2: Ver.ERR_FoodCount2
   property string foodcount3: Ver.ERR_FoodCount3
   //only RFIF Excited (No Id Activated)
   onRFIDstringChanged: {// Ver.CloseAllSerial();
       cardno.text=Ver.VERR_READRFID; treseter.start();}
   onSnameChanged:  {     }
   onValChanged: { treseter.start(); }
       //treseter.start();    }
    onStream1Changed: {  }
    onStream2Changed: { console.log("+++++"); name.text=sname; cardno.text=sid; errorfood.text=efood;
        name.visible=true; cardno.visible=true; text1.visible=true; errostate.visible=true;
        text2.visible=true; personal_Pic.source=  "image://ID2//image"; //persdonal_Pic_Margin.visible=true;
        Ver.CloseAllSerial();
        if(name.text!="یافت نشد"){ treseter.start();  }
        if(name.text=="یافت نشد"){ treseter.start();  }
    }
    onPluginChanged: {console.log(plugin);
                   if (plugin==48)   {plug.source="qrc:/unpluged2.png"; console.log(plugin);}
                    if (plugin==49)  {plug.source="qrc:/pluged.png";  console.log("plugggged"); }}

       Rectangle {

            id:back
            anchors.fill: parent
            gradient:
            Gradient {
                GradientStop {position: 0.0; color: "cyan"}
                GradientStop {position: 1; color: "blue"} }

  Image {id: plug;  x:Screen.width/6.15; y:Screen.height/48; width: Screen.width/16; height:Screen.height/9.6;   }

//----------------------------------------- ProgressBar  (Battery)--------------------------------------------------
   ProgressBar { id: battery;      value:Spi.battery;        from:750; to:830;
       x:10; y:10;         height: Screen.width/40;        clip: true
       background: Rectangle { implicitWidth: Screen.width/8;  implicitHeight: Screen.height/80;
           border.color: "#999999";     radius: 5;   }
       contentItem: Item {  implicitWidth: Screen.width/8;    implicitHeight: Screen.height/120;
           Rectangle { id: bar;   width: battery.visualPosition * parent.width;
               height: parent.height;  radius: 5;
           }

           LinearGradient {  anchors.fill: bar;    start: Qt.point(0, 0)
               end: Qt.point(bar.width, 0);                source: bar;
               gradient: Gradient {
                   GradientStop { position: 0.0; color: "#17a81a" }
                   GradientStop { id: grad; position: 0.5; color: Qt.lighter("#17a81a", 2) }
                   GradientStop { position: 1.0; color: "#17a81a" }     }     }    }    }

 Text { id:battext; width:Screen.width/10;     height: Screen.height/12.9;   x:Screen.width/35;y:Screen.height/48; text:"Battery";  font.italic: true; font.pointSize: 14;color: "black"; font.family: "Times"}

//Text { id:vertext; width:250;     height: 37;    font.pointSize: 14; text:"Version 1.0";   x:10; y:40; color: "black"; font.family: "Times"}
//-------------------------------------------------------------------------------------------------------------------------
 Text { id:vertext; width:250;     height: 37;    font.pointSize: 12; text:"Version 1.0.0";   x:10; y:30; color: "black"; font.family: "Times";font.italic: true}
 //-------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------ Clock ------------------------------------------------------------------

 Clock2.Clock {   x:Screen.width/2.28;  y:Screen.height/8; width:100; height:100   }
 //Spiner {   x:280;  y:0   }
//---------------------------------------- RFID & FingerPrint Icon---------------------------------------------------------
   Image { id: rfid2
       source: "qrc:/RFID.png"
       width:Screen.width/15
       height: Screen.width/15
       x:Screen.width/1.1
       y:Screen.height/9.6 }

   Image {id: finger2
       source: "qrc:/finger-2.png"
       width:Screen.width/15
       height: Screen.width/15
       x:Screen.width/1.23
       y:Screen.height/9.6}
 //---------------------------------------------------------------------------------------------------------------------------


  ///////////////////////////////////////  Error Part /////////////////////////////////////////////////////////
    Rectangle {id:recerror;        width: Screen.width/3.2;        height:Screen.height/4;        color: "transparent"
               radius: 30;       x:420;  y:150;
  Text { id:errorfood;  font.pointSize: 20; text:Ver.ERR_EFood; color: "red";  //x:Screen.width/40; y:Screen.height/3.2;
      width:Screen.width/2.66; height:Screen.height/3.2;
  wrapMode:"WordWrap";     //anchors.centerIn: parent;   anchors.horizontalCenter: recerror.horizontalCenter
  }   }
    Text { id:errostate;  font.pointSize: 20; text:Ver.ERR_STATE; color: "red";
        x:50; y:300;
        width:Screen.width/2.66; height:Screen.height/3.2;
    wrapMode:"WordWrap";     //anchors.centerIn: parent;   anchors.horizontalCenter: recerror.horizontalCenter
    }


       }




   // Image {id: marketPic
    //   source: "qrc:/Market.png"
   //    width:85
     //  height: 85
    //   x:620
     //  y:20}


/////////////////////////////////   Personal Picture ///////////////////////////////////////////


    Image {
        id: personal_Pic
        //source: "qrc:/RFID.png"
       cache: false;
        width:160
        height: 160
        x:150
        y:150
       // Rectangle{
         //   id:persdonal_Pic_Margin
          //  visible: false
           // anchors.fill: parent
           // color:"transparent"; border.color: "red"; border.width:3;  radius:10; }
    }
//-----------------------------------------------------------------------------------------------
    Text {
        id: name
        x:Screen.width/2.162
        y:Screen.height/1.92
        width:Screen.width/3.2
        height: Screen.height/16


        text: Ver.ERR_NAME
        //font.italic: true
        font.pointSize: 18
       // font.family: "‌B nazanin"
        color: "red"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        focus: true

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.color: "black"
            radius: 30  }
    }


    Text {
        id: cardno
        x:Screen.width/2.162
        y:Screen.height/1.68
        width:Screen.width/3.2
        height:Screen.height/16

        text: Ver.VERR_READRFID
        //font.italic: true
        font.pointSize: 14
        color: "red"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
         font.family: "‌B nazanin"
        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.color: "black"
            radius: 30
        }
    }


    Text {
        id: text1
        x:Screen.width/1.2698
        y:Screen.height/1.92
        width:Screen.width/5.33
        height:Screen.height/12.30
        // width:Screen.width/3.2
        // height:Screen.height/16
        // x: 630
        //  y: 250

        color: "white"
        text: "نام و خانوادگی"
        //font.bold: true
         font.family: "‌B nazanin"
        renderType: Text.NativeRendering
        elide: Text.ElideRight
        font.pixelSize: 22 }

    Text {
        id: text2
        x: Screen.width/1.26
        y:Screen.height/1.68
        width:Screen.width/5.33
        height:Screen.height/12.97

        color: "white"
        text: "شماره شناسه"
         font.family: "‌B nazanin"
       // font.bold: true
        font.pixelSize: 22
    }







    Rectangle {
     width:Screen.width/2.66
     height:Screen.height/2.4
     x:250
     y:120
     color: "transparent"
      MouseArea {
          anchors.fill: parent
          onClicked: Spi.TurnOnDisplay()
         // onDragChanged: Spi.SetPowerSaver(0);
         // onPressedChanged: Spi.SetPowerSaver(0);
          onPressed: Spi.TurnOnDisplay();
      }
    }





Timer {
    id:tpower
    interval: 1000
    running: true
    repeat: true
    onTriggered:{if(tabBar.currentIndex==0){ Spi.DisplayBackLightCheck()}
        }}


 Timer {
      id:tbattary
      interval: 6000
      running: true
      repeat: true
      onTriggered:{ Spi.SpiCheck();  Ver.WriteController();      }}



 Timer {
     id:tfinger
     interval: 1000
     running: true
     repeat: true
     onTriggered:{ Ver.readdata11(); console.log("on Finger Read");}}

Timer {
   id:treseter
   interval: window.resetTime*1000
   running: true
   repeat: false
   onTriggered:{
   personal_Pic.source="";
   Ver.WriteController();
   Ver.OpenAllSerial();
   Ver.ClearImage(); errostate.visible=false
   personal_Pic.source=  ""; //persdonal_Pic_Margin.visible=false;
   name.visible=false; cardno.visible=false; text1.visible=false; text2.visible=false;
   console.log("Reset"); name.text=""; cardno.text="";  errorfood.text=""; }}
//Timer {
//   id:treseter2
 //  interval: 2000
 //  running: true
 //  repeat: false
 //  onTriggered:{
 //  Ver.WriteController();
 //  Ver.OpenAllSerial();
 //  foodc1.visible=false; foodc2.visible=false; foodc3.visible=false; name.visible=false; cardno.visible=false; text1.visible=false; text2.visible=false; text3.visible=false;
 //  text4.visible=false; text5.visible=false; text6.visible=false; text7.visible=false; text8.visible=false;       foodn1.visible=false; foodn2.visible=false; foodn3.visible=false;
  //  console.log("Reset"); name.text=""; cardno.text=""; foodn1.text=""; foodn2.text=""; foodn3.text="";   foodc1.text=""; foodc2.text=""; foodc3.text="";   errorfood.text=""; }}

Timer {
     id:treboot
     interval: 300000000
     running: true
     repeat: true
     onTriggered:{ var date = new Date;
         hours = date.getHours()
         if (hours==5) {Spi.Reboot() }    }}
// ------------ Set Time and Persian Calender -----------------

Timer {
     id:tTime
     interval: 10000
     running: true
     repeat: false
     onTriggered:{ Spi.hwclockToSys();  }}


Timer {
     id:tclockSync
     interval: 12000
     running: true
     repeat: false
     onTriggered:{ DateConvert.Shamsi() }}


//end of MaininRectangle

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }

        Page2 {
        }

        Page3 {
        }


    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        onCurrentIndexChanged: {
            if(tabBar.currentIndex==0) {tfinger.start() }
            if(tabBar.currentIndex!=0) {tfinger.stop() }
             Spi.TurnOnDisplay();
        }
        TabButton {
            text: qsTr("حضور غیاب")
        }
        TabButton {
            text: qsTr("‍‍داده ها")
        }

        TabButton {
            text: qsTr("تنظیمات")
        }

    }

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
    }
}
