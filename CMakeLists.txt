# Copyright (C) 2023 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.15)
project(JUCExQt VERSION 0.0.1)

find_package(JUCE CONFIG REQUIRED)
find_package(Qt6
    REQUIRED COMPONENTS Core Gui
    OPTIONAL_COMPONENTS Quick
)

qt_standard_project_setup()

juce_add_plugin(JUCExQt
    PLUGIN_MANUFACTURER_CODE TQtC
    COMPANY_NAME "The Qt Company"
    PRODUCT_NAME "JUCE x Qt"
    PLUGIN_CODE Qtxj
    BUNDLE_ID "io.qt.jucexqt"
    FORMATS AU VST3 Standalone
    COPY_PLUGIN_AFTER_BUILD TRUE
)

target_sources(JUCExQt
    PRIVATE
        PluginProcessor.cpp
        PluginEditor.cpp
        QtComponent.cpp
)

target_compile_definitions(JUCExQt
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(JUCExQt
    PRIVATE
        juce::juce_audio_utils
        Qt6::Core
        Qt6::Gui
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# Ease up on juce_recommended_warning_flags a bit
target_compile_options(juce_recommended_warning_flags INTERFACE
    -Wno-gnu-zero-variadic-macro-arguments
    -Wno-switch-enum
    -Wno-missing-prototypes
)

if(TARGET Qt6::Quick)
    qt_add_resources(JUCExQt "qml" FILES main.qml)
    qt_import_qml_plugins(JUCExQt)
    target_link_libraries(JUCExQt PRIVATE Qt6::Quick)
endif()
