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
    opencv_func.cpp \
    SliderWidget.cpp \
    SpriteSettingWidget.cpp \
    MorMatInputDialog.cpp \
    SizeInputDialog.cpp

FORMS += \
    MainWindow.ui \
    ContoursDisplayer.ui \
    SpriteSettingWidget.ui \
    MorMatInputDialog.ui \
    SizeInputDialog.ui

HEADERS += \
    MainWindow.h \
    MacroData.h \
    ImageUtility.h \
    SliderInput.h \
    ContoursDisplayer.h \
    opencv_func.hpp \
    SliderWidget.h \
    SpriteSettingWidget.h \
    MorMatInputDialog.h \
    SizeInputDialog.h

