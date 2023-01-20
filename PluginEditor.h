// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include "QtComponent.h"

class PluginEditor  : public juce::AudioProcessorEditor
{
public:
    explicit PluginEditor(juce::AudioProcessor&);
    ~PluginEditor() override;

    void resized() override;
    void childBoundsChanged(Component *child) override;

    void paint(juce::Graphics&) override;

private:
    QtComponent m_qtComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
