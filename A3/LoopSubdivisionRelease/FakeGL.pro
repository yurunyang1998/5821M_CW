######################################################################
# Automatically generated by qmake (3.1) Fri Dec 4 10:41:30 2020
######################################################################

QT+=opengl
TEMPLATE = app
TARGET = fakegl
INCLUDEPATH += .


INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10240.0/ucrt"
LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10240.0/ucrt/x64"
DEFINES += QT_DEPRECATED_WARNINGS


# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
LIBS += -lopengl32

# Input
HEADERS += ArcBall.h \
           ArcBallWidget.h \
           Cartesian3.h \
           DirectedEdgeSurface.h \
           Homogeneous4.h \
           Matrix4.h \
           Quaternion.h \
           RenderController.h \
           RenderWidget.h \
           RenderWindow.h \
           RGBAImage.h \
           RGBAValue.h \
           SphereVertices.h \
           RenderParameters.h \
           SubDivisionTools.h


SOURCES += ArcBall.cpp\
           ArcBallWidget.cpp \
           Cartesian3.cpp \
           DirectedEdgeSurface.cpp \
           Homogeneous4.cpp \
           Matrix4.cpp \
           Quaternion.cpp \
           RenderController.cpp \
           RenderWidget.cpp \
           RenderWindow.cpp \
           RGBAImage.cpp \
           RGBAValue.cpp \
           SphereVertices.cpp \
           SubDivisionTools.cpp \
           main.cpp



