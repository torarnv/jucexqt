// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: BSD-3-Clause

import QtQuick

Rectangle {
    id: window

    width: 400
    height: 200

    gradient: "DustyGrass"

    Text {
        id: rotatingText
        text: "Hello Qt 🥳"
        font.pointSize: 36
        anchors.centerIn: parent

        RotationAnimator on rotation {
            from: 0;
            to: 360;
            duration: 5000
            loops: Animation.Infinite
        }
    }
}
