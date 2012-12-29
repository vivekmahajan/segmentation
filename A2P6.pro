# The simplest application example: 20 lines of code and yet all the power !
# A Viewer class is derived from QGLViewer and its <code>draw()</code> function is overloaded to
# specify the user defined OpenGL orders that describe the scene.
# This is the first example you should try, as it explains some of the default keyboard shortcuts
# and the mouse behavior of the viewer.
# This example can be cut and pasted to start the development of a new application.
TEMPLATE = app
TARGET = mcaq
HEADERS = simpleViewer.h \
    viewerUI.h \
    dataStructures.h
SOURCES = simpleViewer.cpp \
    main.cpp \
    viewerUI.cpp
QT *= xml \
    opengl
CONFIG += qt \
    opengl

# --------------------------------------------------------------------------------------
# The remaining of this configuration tries to automatically detect the library paths.
# In your applications, you can probably simply use (see doc/compilation.html for details) :
# INCLUDEPATH *= C:/Users/debunne/Documents/libQGLViewer-2.3.11
# LIBS *= -LC:/Users/debunne/Documents/libQGLViewer-2.3.11/QGLViewer -lQGLViewer2
# Change these paths according to your configuration.
# --------------------------------------------------------------------------------------
INCLUDEPATH *= ./usr/include
 LIBS *= -L./usr/lib  -ligraph -lqglviewer-qt4

