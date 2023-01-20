// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: BSD-3-Clause

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <QtCore/qloggingcategory.h>
#include <QtGui/qguiapplication.h>

Q_LOGGING_CATEGORY(qtEditor, "juce.qt.editor")

#if defined(QT_QUICK_LIB)

#include <QtQuick/qquickview.h>

class EditorWindow : public QQuickView
{
public:
    EditorWindow()
    {
        setSource(QUrl("qrc:/main.qml"));
        setResizeMode(QQuickView::SizeRootObjectToView);
    }
};

#else // Plain QRasterWindow

#include <QtGui/qrasterwindow.h>
#include <QtGui/qpainter.h>
#include <QtGui/qfont.h>

class EditorWindow : public QRasterWindow
{
public:
    EditorWindow()
    {
        resize(400, 200);
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.fillRect(QRect(0, 0, width(), height()), QGradient::DustyGrass);
        QFont font;
        font.setPointSize(36);
        p.setFont(font);
        p.drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, QStringLiteral("Hello Qt 🥳"));
    }
};

#endif

using namespace juce;

PluginEditor::PluginEditor(AudioProcessor& p)
    : AudioProcessorEditor(p)
{
    qCDebug(qtEditor) << "Creating editor" << this;

    setResizable(true, false);
    setWantsKeyboardFocus(true);

    if (!qGuiApp) {
        QCoreApplication::setAttribute(Qt::AA_PluginApplication);
        static int argc = 1; static char *argv[] = { const_cast<char*>("") };
        new QGuiApplication(argc, argv); // FIXME: Ref-count and dispose
    }

    m_qtComponent.setWindow(new EditorWindow);
    addAndMakeVisible(m_qtComponent);
    childBoundsChanged(&m_qtComponent);
}

PluginEditor::~PluginEditor()
{
    qCDebug(qtEditor) << "Deleting editor" << this;
}

void PluginEditor::resized()
{
    qCDebug(qtEditor) << "Editor" << this << "resized";
    m_qtComponent.setBounds(getLocalBounds());
}

void PluginEditor::childBoundsChanged(Component*)
{
    qCDebug(qtEditor) << "Editor" << this << "child bounds changed";
    setSize(m_qtComponent.getWidth(), m_qtComponent.getHeight());
}

void PluginEditor::paint(juce::Graphics&)
{
    // FIXME: We're still being asked to paint by JUCE. Ideally
    // there would be a way to tell JUCE to skip this component.
    qCDebug(qtEditor) << "Editor" << this << "asked to paint";
}
