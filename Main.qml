import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "Image Classifier"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        Component.onCompleted: {
            console.log("QML is ready. Backend available?", backend !== null)
        }

        TextField {
            id: imagePathField
            placeholderText: "Enter full image path here"
            Layout.preferredWidth: 500
        }

        Button {
            text: "Load Image"
            onClicked: {
                if (backend)
                    backend.imagePath = imagePathField.text
            }
        }

     Image {
    source: "file:///" + backend.imagePath
    width: 400
    height: 300
    fillMode: Image.PreserveAspectFit
    visible: backend.imagePath !== ""
}


        Button {
            text: "Classify"
            onClicked: {
                if (backend)
                    backend.classifyImage()
            }
        }

        Text {
            text: backend ? backend.result : ""
            font.pointSize: 16
            wrapMode: Text.Wrap
        }
    }
}
