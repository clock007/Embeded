import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.VirtualKeyboard 2.0
import FingerSign 1.0

Item {
    id: finger
    width: 800
    height:480
    x:0
    y:0
    visible: true
    FingerSign {id:fi }

    property string idresult:fi.ERR_ID
    property string statusresult:fi.ERR_STATUS
    property string image1result:fi.ERR_Image1
    property string image2result:fi.ERR_Image2
    property string image3result:fi.ERR_Image3
    property string generateresult1:fi.ERR_Generate1
    property string generateresult2:fi.ERR_Generate2
    property string generateresult3:fi.ERR_Generate3
    property string mergeresult:fi.ERR_MERGE
    property string storeresult:fi.ERR_STORE




 Component.onCompleted: {   fi.Openserial32(); tassignid.restart();            }
 onIdresultChanged: { tassignid.stop(); fi.GETStatus();  console.log("dsdsfdsfd"); }

 onStatusresultChanged: { twriteimage.restart(); treadimage.restart();  }
onImage1resultChanged: {twriteimage.stop(); treadimage.stop(); fi.f_Write_Generate1();   }

 onGenerateresult1Changed: { console.log("Step1 Done"); twriteimage.restart();  treadimage.restart();   }

 onImage2resultChanged: {twriteimage.stop(); treadimage.stop(); fi.f_Write_Generate2()    }
 onGenerateresult2Changed: { console.log("Step2 Done"); twriteimage.restart(); treadimage.restart();    }

 onImage3resultChanged: { twriteimage.stop(); treadimage.stop(); fi.f_Write_Generate3();  }
 onGenerateresult3Changed: {console.log("Step3 Done"); fi.f_Write_Merge();   }

onMergeresultChanged: { console.log("Merge Done");fi.f_Write_Store();  }
onStoreresultChanged: {  console.log("Store Done"); }






    Rectangle {
        anchors.fill: parent
        gradient:
        Gradient {
            GradientStop {position: 0.0; color: "black"}
            GradientStop {position: 1; color: "blue"}          }

//----------------Text--------------------------------------


Rectangle {
    width:300
    height:300
    visible: false
    Image {
        width: 200
        height: 200
        source:"image://ID//image"

    }


}

 Text {
     id : assignid
     text: fi.ERR_ID
     x:300
     y:10
     color: "white"
 }
 Text {
     id : status
     text: fi.ERR_STATUS
     x:300
     y:50
     color: "white"
 }
//---------
 Text {
     id : please1
     text: "please Put Finger For 1th"
     x:550
     y:100
     color: "white"
 }
 Text {
     id : readimage1
     text: fi.ERR_Image1
     x:300
     y:100
     color: "white"
 }


 Text {
     id : generator1
     text: fi.ERR_Generate1
     x:50
     y:100
     color: "white"
 }

 //---------
  Text {
      id : please2
      text: "please Put Finger For 2th"
      x:550
      y:175
      color: "white"
  }
  Text {
      id : readimage2
      text: fi.ERR_Image2
      x:300
      y:175
      color: "white"
  }


  Text {
      id : generator2
      text: fi.ERR_Generate2
      x:50
      y:175
      color: "white"
  }

  //---------
   Text {
       id : please3
       text: "please Put Finger For 3th"
       x:550
       y:250
       color: "white"
   }
   Text {
       id : readimage3
       text: fi.ERR_Image3
       x:300
       y:250
       color: "white"
   }


   Text {
       id : generator3
       text: fi.ERR_Generate3
       x:50
       y:250
       color: "white"
   }

   Text {
       id:merge
       text:fi.ERR_MERGE
       x:300
       y:300
       color: "white"
   }

   Text {
       id:store
       text:fi.ERR_STORE
       x:300
       y:350
       color: "white"
   }





//----------------------Timers------------------------------


 Timer {
     id:tassignid

        interval: 500;
        repeat: true
        onTriggered: fi.GETId();
    }

 Timer {
     id:twriteimage

        interval: 3000;
         repeat: true
        onTriggered: fi.f_Write_Image()
    }

 Timer {
     id:treadimage

        interval: 1000;
        repeat: true
        onTriggered: fi.f_Read_Image();
    }






 //----------------------------------
Butt {

    btext: "exit"
    bx:50
    by:360
   onBclicked: { fi.Closeserial32(); finger.visible=false; twriteimage.stop(); treadimage.stop();  }
}








    }}
