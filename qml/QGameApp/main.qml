
import QtQuick 2.0

import QGameModule 1.0

Rectangle {
    width: 350
    height: 700
    QSnake {
        id: aSnake
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent
            property int startX;
            property int startY;

            onPressed: {
                startX = mouse.x;
                startY = mouse.y;
            }

            onReleased: {
                var deltax = mouse.x - startX;
                var deltay = mouse.y - startY;
                //var angle = Math.atan2(deltay,deltax) * 180 / Math.PI;

                if (Math.abs(deltax) > 30 || Math.abs(deltay) > 30) {
                    var angle = Math.atan2(deltay,deltax) * 180 / Math.PI;
                    if (angle > -45 && angle < 45) {
                        // swipe right
                        aSnake.slot_rightPressed();
                    } else if (angle < -135 && angle > -180) {
                        // swipe left
                        aSnake.slot_leftPressed();
                    }
                    else if (angle > 135 && angle < 180) {
                        // swipe left
                        aSnake.slot_leftPressed();
                    }else if (angle > 45 && angle < 135) {
                        // swipe down
                        aSnake.slot_downPressed();
                    } else if (angle > -135 && angle < -45) {
                        // swipe up
                        aSnake.slot_upPressed();
                    }
                }
            }
        }
        Rectangle {
            id: startButton
            x: 0
            y: 0
            width: startText.contentWidth + 20
            height: startText.contentHeight + 10
            visible: true
            objectName: "startButton";
            color: "gray"
            MouseArea {
                anchors.fill: parent
                onClicked: aSnake.slot_start()
            }
            Text {
                id:startText
                anchors.fill: parent
                text: "Start"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        focus: true
        Keys.onUpPressed: aSnake.slot_upPressed()
        Keys.onDownPressed: aSnake.slot_downPressed()
        Keys.onLeftPressed: aSnake.slot_leftPressed()
        Keys.onRightPressed: aSnake.slot_rightPressed()

    }
}
