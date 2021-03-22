<a href="#">
    <img width="192px" height="192px" src="doc/icon.svg" align="right" />
</a>

# MySQLDatabaseEngine

Contains a static compilation of the `QMYSQL` driver and its respective dependencies for each platform. The goal of this project is to reduce setup, development & deployment time for Qt apps that need to communicate with a MySQL database.

Additionaly, this repo comes with a simple `QObject` class for usage within QML applications.

### Supported platforms & compilers

For the moment, this repo only supports macOS. Support for other platforms will be eventualy added.

**Todo:**

- [ ] GNU/Linux (64 bit)
- [ ] Windows (MinGW 32 bit)
- [ ] Windows (MinGW 64 bit)
- [ ] Windows (MSVC 32 bit)
- [ ] Windows (MSVC 64 bit) 

### Qt version

This library has been compiled for use with Qt 5.12.2.

### Usage

1. Clone this repository (or download as zip).
2. Integrate the `MySQLDatabaseEngine.pri` file in your project by using the [`include()`](https://doc.qt.io/qt-5/qmake-test-function-reference.html#include-filename) qmake function.
