// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class QWindow;

class QtComponent : public juce::Component
{
public:
    QtComponent();
    ~QtComponent() override;

    void setWindow(QWindow *window);
    QWindow *getWindow() const;

private:
    class Pimpl;
    std::unique_ptr<Pimpl> pimpl;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(QtComponent)
};
