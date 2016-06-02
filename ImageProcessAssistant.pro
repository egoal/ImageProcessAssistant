QT  +=  widgets

CONFIG  +=  c++11

INCLUDEPATH +=  D:/opencv3/build/include/

LIBS    +=  -LD:/opencv3/build/x64/vc12/lib/
LIBS    +=  opencv_world310.lib

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    MacroData.cpp \
    ImageUtility.cpp \
    SliderInput.cpp \
    ContoursDisplayer.cpp \
    opencv_func.cpp

FORMS += \
    MainWindow.ui \
    ContoursDisplayer.ui

HEADERS += \
    MainWindow.h \
    MacroData.h \
    ImageUtility.h \
    SliderInput.h \
    ContoursDisplayer.h \
    opencv_func.hpp

