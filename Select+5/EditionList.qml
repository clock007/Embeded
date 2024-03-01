import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
Item {
id:editionList
visible: true
width: 800
height: 480
Component.onCompleted: tableView.update();


signal mysignal()
onMysignal: {
    console.log("OpenSerialPort");          Ver.OpenSerialports();  }
property int sort_Type: 1
RowLayout {

    id: rowLayout
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 5
    spacing: 10
    width: 50


    Label { text: "لطفا رکورد مورد نظر برای ویرایش را انتخاب کنید"    }
   // Text {text: qsTr("شماره شناسه برای حذف");  color: "white" }
   // TextField { id: idremove;  onTextChanged: { }  }

   // Button {   text: qsTr("ویرایش")     }}
    Button {text: qsTr("خروج")
    onClicked: { editionList.visible=false; }  }

    Button {text: qsTr("مرتب سازی بانام")
    onClicked: { myModel.updateModel4(); sort_Type=2;     }  }
    Button {text: qsTr("مرتب سازی با شناسه")
    onClicked: { myModel.updateModel3();  sort_Type=1;  }  }
}




TableView {

//onClicked: {
          //    Sp.Edit_Loader(tableView.currentRow,sort_Type);

  //  console.log(myModel.getId(tableView.currentRow))

//}

    id: tableView
    anchors.top: rowLayout.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.margins: 5

    TableViewColumn {
        role: "id"
        title: "شناسه"
        width: 120


    }
    TableViewColumn {
        role: "FullName"
        title: "نام کامل"
        width: 300


    }


    TableViewColumn {
        role: "CardNo"
        title: "شماره کارت"
        width: 200
    }
    TableViewColumn {
        role: "AccessType"
        title: "سطح دسترسی"
        width: 130

    }


    model: myModel
    itemDelegate: Item {
                            Text {
                              horizontalAlignment: Text.AlignHCenter
                              verticalAlignment: Text.AlignVCenter
                              anchors.verticalCenter: parent.verticalCenter
                              color: "blue"
                              elide: styleData.elideMode
                              text: styleData.value
                              font.pixelSize: 18
                            }
                     }




 //   MouseArea {
 //   anchors.fill: parent

  //  onClicked: {
    //    editionList.visible=false;
      //      var component = Qt.createComponent("EditionList.qml");    var window    = component.createObject(editionList);  editionList.visible=false;
        //    window.show();


    onDoubleClicked: {
        Ver.CloseAllSerial(); Ver.ClearALL();
        console.log("Clicked");  console.log(tableView.currentRow); console.log(sort_Type);
        Sp.OpenSerial(); Fingers.init_Detector();
        Sp.Edit_Loader(tableView.currentRow,sort_Type);
        var component = Qt.createComponent("Edit.qml");    var window    = component.createObject(editionList);  editionList.focus=false;
        window.show();


editionList.visible=false;
   // }
   }

  //  rowDelegate: Rectangle {
   //     Layout.preferredHeight: 300
    //    width: childrenRect.width
    //    height: 40
     //   anchors.fill: parent
     //   color: styleData.selected ? 'skyblue' : (styleData.alternate ? 'whitesmoke' : 'white');
     //   MouseArea {
      //      anchors.fill: parent
       //     acceptedButtons: Qt.RightButton | Qt.LeftButton
       //     onClicked: {
         //       tableView.selection.clear()
          //      tableView.selection.select(styleData.row)
            //    tableView.currentRow = styleData.row
            //    tableView.focus = true

         //       switch(mouse.button) {
          //      case Qt.RightButton:
           //         contextMenu.popup() // Call the context menu
            //        break
             //   default:
               //     break
               // }
          //  }
        //}
   // }


}





MessageDialog {
    id: dialogDelete
    title: qsTr("حذف رکورد")
    text: qsTr("آیا درخواست جاری را تایید میکنید؟")
    icon: StandardIcon.Warning
    standardButtons: StandardButton.Ok | StandardButton.Cancel

    // If the answer ...
    onAccepted: {
        /* ... remove the line by id, which is taken from the data model
         * on the line number in the presentation
         * */
         message.text=Ver.Deleteone(idremove.text);     myModel.updateModel();  tableView.model=myModel;   tableView.update(); dialogDelete.close()

        //database.removeRecord(myModel.getId(tableView.currentRow))
        //myModel.updateModel();
    }
}
}


