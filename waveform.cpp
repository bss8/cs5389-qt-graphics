#include "waveform.h"

#include <QtGui/QtGui>
#include <QtOpenGL/QtOpenGL>
#include <QOpenGLWidget>

#include <math.h>

#define PI 3.14159265358979

WaveForm::WaveForm(QWidget *parent)
    : QGLWidget(parent)
{

}


WaveForm::~WaveForm()
{

}


/**
 *Initialize the GL settings
 * @brief GL_Graphic_Objects::initializeGL
 */
void WaveForm::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClearDepth(1.0f);
    f->glEnable(GL_DEPTH_TEST);
    f->glDepthFunc(GL_LEQUAL);
    f->glLineWidth(4.0);
    glPointSize(2.0);
}

/**
 *Set up the viewport based on the screen dimentions
 *Function is called implicitly by initializeGL and when screen is resized
 * @brief GL_Graphic_Objects::resizeGL
 * @param w
 * @param h
 */
void WaveForm::resizeGL( int w, int h )
{
    //algorithm to keep scene "square" (preserve aspect ratio)
    //even if screen is streached
    if(w>h)
        glViewport((w-h)/2, 0, h, h);
    else
        glViewport(0, (h-w)/2, w, w);

    //setup the projection and switch to model view for transformations
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);

    //implicit call to paintGL after resized
}

void WaveForm::drawCosGraph()
{
    double c = 0.0;
    glLoadIdentity();
    glColor3f(0.5, 0.5, 0.0);
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);

    for (double i = -16 * M_PI; i <= 16 * M_PI; i += 0.1)
    {
        c = (double) this->volume * cos(2.0 * M_PI * this->frequency * i);
        glVertex2f(i, c);
    }

    glEnd();
    glFlush();
}

void WaveForm::updateFre(int fre)
{
    this->frequency = fre;
    updateGL();
}

void WaveForm::updateVol(int vol)
{
    this->volume = vol;
    updateGL();
}

void WaveForm::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    drawCosGraph();
}

















