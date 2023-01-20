# JUCE x Qt

Example of how to use Qt for the UI of a JUCE plugin.

Read more here: https://www.qt.io/blog/juce-x-qt

Tested on macOS. Requires Qt 6.5 with a few tweaks:

https://gist.github.com/torarnv/7bbd31d9879c390071d5aa0e9a1f2af1

## Building

`cmake ~/src/jucexqt -DCMAKE_PREFIX_PATH="~/install/juce;~/install/qt/6.5-static/qtbase"`

## License

BSD-3-Clause
