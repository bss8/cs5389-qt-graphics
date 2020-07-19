/**
* @author Borislav S. Sabotinov
* Defines a main UI window and the functions that will be used.
* The intent is to place all components (radio, GL objects, etc.) in this main window.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QWidget>
#include <QCheckBox>
#include "Sphere.h"
#include "waveform.h"
#include "radio.h"
#include <QtOpenGL/QGLWidget>

class QAction;
class QListWidget;
class QMenu;
class QTextEdit;

class GL_Graphic_Objects;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    GL_Graphic_Objects *gl_graphic_objects;


private:
    void createActions();
    void createMenus();
    void createStatusBar();
    void createRadioDockWindow();
    void createSphereDockWindow();
    void createCosGraphWindow();

    Sphere *modifier;
    Radio *radio;
    WaveForm *waveForm;
};

#endif
