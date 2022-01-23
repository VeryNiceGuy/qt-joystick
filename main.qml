
import QtQuick 2.3
import JoystickComponent 1.0

Item {

    width: 320
    height: 640

    JoystickPoint {
        id: joystickPoint
    }

    Rectangle {
        id: buttonUp
        x: 120
        y: 459
        width: 80
        height: 80

        Timer {
            id: buttonUpTimer
               interval: 50
               repeat:true
               onTriggered:
                   joystickPoint.verticalPosition = joystickPoint.verticalPosition + 5.0
           }

        Image {
            id: buttonUpIcon
            anchors.fill: parent
            source: "icons/buttonUp.png"
            fillMode: Image.PreserveAspectCrop
            visible: true
        }

        Image {
            id: buttonUpPressedIcon
            anchors.fill: parent
            source: "icons/buttonUpPressed.png"
            fillMode: Image.PreserveAspectCrop
            visible: false
        }

        MouseArea{
            id: buttonUpMouseArea
            anchors.fill: parent

            onPressed: {
                buttonUpTimer.start();
                buttonUpIcon.visible = false
                buttonUpPressedIcon.visible = true
            }
            onReleased: {
                buttonUpTimer.stop();
                buttonUpIcon.visible = true
                buttonUpPressedIcon.visible = false
            }
        }
    }

    Rectangle {
        id: buttonLeft
        width: 80
        height: 80
        x: 40
        y: 499

        Timer {
            id: buttonLeftTimer
               interval: 50
               repeat:true
               onTriggered:
                   joystickPoint.horizontalPosition = joystickPoint.horizontalPosition - 5.0
           }

        Image {
            id: buttonLeftIcon
            anchors.fill: parent
            source: "icons/buttonLeft.png"
            fillMode: Image.PreserveAspectCrop
            visible: true
        }

        Image {
            id: buttonLeftPressedIcon
            anchors.fill: parent
            source: "icons/buttonLeftPressed.png"
            fillMode: Image.PreserveAspectCrop
            visible: false
        }

        MouseArea{
            id: buttonLeftMouseArea
            anchors.fill: parent
            onPressed: {
                buttonLeftTimer.start()
                buttonLeftIcon.visible = false
                buttonLeftPressedIcon.visible = true
            }
            onReleased: {
                buttonLeftTimer.stop()
                buttonLeftIcon.visible = true
                buttonLeftPressedIcon.visible = false
            }
        }
    }

    Rectangle {
        id: buttonRight
        width: 80
        height: 80
        x: 200
        y: 499

        Timer {
            id: buttonRightTimer
               interval: 50
               repeat:true
               onTriggered:
                   joystickPoint.horizontalPosition = joystickPoint.horizontalPosition + 5.0
           }

        Image {
            id: buttonRightIcon
            anchors.fill: parent
            source: "icons/buttonRight.png"
            fillMode: Image.PreserveAspectCrop
            visible: true
        }

        Image {
            id: buttonRightPressedIcon
            anchors.fill: parent
            source: "icons/buttonRightPressed.png"
            fillMode: Image.PreserveAspectCrop
            visible: false
        }

        MouseArea{
            id: buttonRightMouseArea
            anchors.fill: parent
            onPressed: {
                buttonRightTimer.start()
                buttonRightIcon.visible = false
                buttonRightPressedIcon.visible = true
            }
            onReleased: {
                buttonRightTimer.stop()
                buttonRightIcon.visible = true
                buttonRightPressedIcon.visible = false
            }
        }
    }

    Rectangle {
        id: buttonDown
        width: 80
        height: 80
        x: 120
        y: 539

        Timer {
            id: buttonDownTimer
               interval: 50
               repeat:true
               onTriggered:
                   joystickPoint.verticalPosition = joystickPoint.verticalPosition - 5.0
           }

        Image {
            id: buttonDownIcon
            anchors.fill: parent
            source: "icons/buttonDown.png"
            fillMode: Image.PreserveAspectCrop
            visible: true
        }

        Image {
            id: buttonDownPressedIcon
            anchors.fill: parent
            source: "icons/buttonDownPressed.png"
            fillMode: Image.PreserveAspectCrop
            visible: false
        }

        MouseArea{
            id: buttonDownMouseArea
            anchors.fill: parent
            onPressed: {
                buttonDownTimer.start()
                buttonDownIcon.visible = false
                buttonDownPressedIcon.visible = true
            }
            onReleased: {
                buttonDownTimer.stop()
                buttonDownIcon.visible = true
                buttonDownPressedIcon.visible = false
            }
        }
    }
}
