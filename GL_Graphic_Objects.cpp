/**
* @author Borislav S. Sabotinov
* Implementation of the GL_Graphic_Objects header.
* I experiment with drawing shapes, manually placing them, and using the glTranslatef() function
* in combination with the provided ngon() function.
*
* Note: one trick about converting RGB colors in range [0,255] is to take the value and divide by 255.
* The result I use in the glColor3f function.
*/

#include <QtGui/QtGui>
#include <QtOpenGL/QtOpenGL>
#include <QOpenGLWidget>

#include <math.h>
#include "GL_Graphic_Objects.h"

#define PI 3.141592653589793

/**
 * @brief GL_Graphic_Objects::GL_Graphic_Objects
 * @param parent
 */
GL_Graphic_Objects::GL_Graphic_Objects(QWidget *parent)
    : QGLWidget(parent)
{

}

/**
 * @brief GL_Graphic_Objects::~GL_Graphic_Objects
 */
GL_Graphic_Objects::~GL_Graphic_Objects()
{

}

/**
 *Initialize the GL settings
 * @brief GL_Graphic_Objects::initializeGL
 */
void GL_Graphic_Objects::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.6117f, 0.7607f, 1.0f, 0.0f);
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
void GL_Graphic_Objects::resizeGL( int w, int h )
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

/**
 * Manually paint some shapes.
 * Based on an example project I found here:
 * https://github.com/kevin-funderburg/qt-opengl-graphics-ui
 * @brief GL_Graphic_Objects::paintShapes
 */
void GL_Graphic_Objects::paintShapes()
{
    glLoadIdentity();
    double radius = 0.5;

    // White points
    glRotatef(50, 1, 0, 0);
    glBegin(GL_POINTS);
        glColor3f ( 1.0, 1.0, 1.0);
        glVertex3f(-4.0, 4.0, 0.0);
        glVertex3f(-3.0, 4.0, 0.0);
        glVertex3f(-2.0, 4.0, 0.0);
        glVertex3f(-1.0, 4.0, 0.0);
        glVertex3f(-0.0, 4.0, 0.0);
        glVertex3f( 1.0, 4.0, 0.0);
        glVertex3f( 2.0, 4.0, 0.0);
        glVertex3f( 3.0, 4.0, 0.0);
        glVertex3f( 4.0, 4.0, 0.0);
    glEnd();
    glFlush();
    glLoadIdentity();

    // Gradient line from gray to white
    glRotatef(75, 1, 0, 0);
    glScalef(.75, .75, .75);
    glTranslatef(0, 1.75, 0);
    glBegin(GL_LINES);
        glColor3f ( 0.5, 0.5, 0.5);
        glVertex2f(-3.5, 3.5);
        glColor3f ( 1.0, 1.0, 1.0);
        glVertex2f( 3.5, 3.5);
    glEnd();
    glFlush();
    glLoadIdentity();

    // Orange Line strip zig-zagging pattern
    glRotatef(-95, 0, -1, 0);
    glScalef(.75, .75, .75);
    glBegin(GL_LINE_STRIP);
        glColor3f ( 1.0, 0.5, 0.0);
        glVertex3f(-3.0, 3.0, 0.0);
        glVertex3f(3.0, 3.0, 0.0);
        glVertex3f(-2.5, 2.5, 0.0);
        glVertex3f(2.5, 2.5, 0.0);
        glVertex3f(-2.0, 2.0, 0.0);
    glEnd();
    glFlush();
    glLoadIdentity();

    //Triangle above square
    glRotatef(75, 1, 0, 0);
    glScalef(.75, .75, .75);
    glTranslatef(0, 2, 0);
    glBegin(GL_TRIANGLES);
        glColor3f ( 1.0, 0.6, 0.8);
        glVertex3f(-2.0, 2.0, 0.0);
        glVertex3f( 2.0, 2.0, 0.0);
        glVertex3f( 0.0, 0.5, 0.0);
    glEnd();
    glFlush();
    glLoadIdentity();

    //Left Triangle strip
    glRotatef(75, 1, 0, 0);
    glScalef(0.75, 1.25, 0);
    glTranslatef(-1,0,0);
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f ( 1.0,  0.0, 0.0);
        glVertex3f(-0.5,  0.5, 0.0);
        glVertex3f(-3.0,  1.5, 0.0);
        glVertex3f(-3.0, -1.5, 0.0);
        glVertex3f(-4.5,  -0.5, 0.0);
    glEnd();
    glFlush();
    glLoadIdentity();

    //Right polygon, just some shape, I tried making it look
    //like pacman or some beetle
    glRotatef(75, 1, 0, 0);
    glScalef(.75, .75, .75);
    glBegin(GL_TRIANGLE_STRIP);
        glColor3f (2.0,  0.0, 0.5);
        glVertex3f(0.5,  0.0, 0.0);
        glVertex3f(1.5, 0.5, 0.0);
        glVertex3f(3.0, 1.5, 0.0);
        glVertex3f(4.5, 0.0, 0.0);
        glVertex3f(3.0, -1.5, 0.0);
        glVertex3f(1.5, -0.5, 0.0);
        glVertex3f(0.5,  0.0, 0.0);
    glEnd();
    glFlush();
    glLoadIdentity();

    // Yellow square in the center
    glRotatef(125, -21, 0, 0);
    glBegin(GL_QUADS);
        glColor3f (1.0, 1.0, 0.0);
        glVertex3f(-radius, radius, 0);
        glVertex3f(radius, radius, 0);
        glVertex3f(radius, -radius, 0);
        glVertex3f(-radius, -radius, 0);
    glEnd();
    glFlush();
    glLoadIdentity();

    //Black bottom polygon
    glTranslatef(0, -2, 0);
    glRotatef(75, 1, -1, 0);
    glBegin(GL_POLYGON);
        glColor3f ( 0.0,  0.0, 0.0);
        glVertex3f( 0.0, -0.5, radius);
        glVertex3f(-1.0, -1.5, radius);
        glVertex3f(-1.0, -2.5, radius);
        glVertex3f(-1.0, -3.5, radius);
        glVertex3f( 0.0, -4.5, radius);
        glVertex3f( 1.0, -3.5, radius);
        glVertex3f( 1.0, -2.5, radius);
        glVertex3f( 1.0, -1.5, radius);
    glEnd();
    glFlush();
    glLoadIdentity();
}

/**
 * Create a cube, rotated so 3 faces are visible
 * @brief GL_Graphic_Objects::paintCube
 */
void GL_Graphic_Objects::paintCube()
{
    glRotatef(75, 0, -1, -1);
    glTranslatef(1, -4.2, 0);

    glBegin(GL_QUADS);
        // Set color to white
        glColor3f(1.0f,1.0f,1.0f);
        glVertex3f( 1.0f, 1.0f,-1.0f);
        glVertex3f(-1.0f, 1.0f,-1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f( 1.0f, 1.0f, 1.0f);
        // Set color to Orange
        glColor3f(1.0f,0.5f,0.0f);
        glVertex3f( 1.0f,-1.0f, 1.0f);
        glVertex3f(-1.0f,-1.0f, 1.0f);
        glVertex3f(-1.0f,-1.0f,-1.0f);
        glVertex3f( 1.0f,-1.0f,-1.0f);
        // Set color to Brown
        glColor3f(0.8235f,0.4117f,0.1176f);
        glVertex3f( 1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f,-1.0f, 1.0f);
        glVertex3f( 1.0f,-1.0f, 1.0f);
        // Set color to Yellow
        glColor3f (1.0f,1.0f,0.0f);
        glVertex3f( 1.0f,-1.0f,-1.0f);
        glVertex3f(-1.0f,-1.0f,-1.0f);
        glVertex3f(-1.0f, 1.0f,-1.0f);
        glVertex3f( 1.0f, 1.0f,-1.0f);
        // Set The Color To Blue
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-1.0f, 1.0f,-1.0f);
        glVertex3f(-1.0f,-1.0f,-1.0f);
        glVertex3f(-1.0f,-1.0f, 1.0f);
         // Set color to dark blue
        glColor3f(0.2f,0.432f,0.872f);
        glVertex3f( 1.0f, 1.0f,-1.0f);
        glVertex3f( 1.0f, 1.0f, 1.0f);
        glVertex3f( 1.0f,-1.0f, 1.0f);
        glVertex3f( 1.0f,-1.0f,-1.0f);
     glEnd();
     glFlush();
}

/**
 * Create a circle using an algorithm that deterimines the direction/angle and distance from the center, t
 * then plots a line loop.
 * @brief GL_Graphic_Objects::paintCircle
 */
void GL_Graphic_Objects::paintCircle()
{
    glTranslatef(3, -3.8, 0);
    glRotatef(-145, 0, -1, -1);
    glScaled(1.5,1.5,0);
    glColor3f(0.5f,0.2f,0.2f);  // splash of color, seems like brown
    int pieces = 100;
    int radius = 1;

    glBegin(GL_LINE_LOOP);
    for (int angle = 0; angle < 360; angle += 360 / pieces)
    {
        double direction = angle * PI / 180;
        double x = cos(direction) * radius;
        double y = sin(direction) * radius;

        glVertex2d(x, y);
    }
    glEnd();
    glFlush();
}

/**
 * This function was provided along with the assignment.
 * @brief GL_Graphic_Objects::ngon
 * @param n
 */
void GL_Graphic_Objects::ngon(int n)
{
    float degree, vertx, verty, rotate, degToRad;
    rotate = 360.0/n;//Vertex rotation increment
    degree = rotate/2 + 180;//Current degree of vertex (starts rotated to make object upright)
    degToRad = 180/3.14159; //Conversion factor from degrees to radians

    glBegin(GL_POLYGON);
    for(int i = 0; i < n; i++, degree += rotate)
    {
        vertx = 0.5 * sin(degree/degToRad); //next vertex's x coordinate
        verty = 0.5 * sin((90 - degree)/degToRad); //next vertex's y coordinate
        glVertex3f(vertx, verty, 0);
    }
    glEnd();
    glFlush();
}


/**
 * Paint the GL scene
 * @brief GL_Graphic_Objects::paintGL
 */
void GL_Graphic_Objects::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    paintCircle();
    paintShapes();
    glFlush();
    paintCube();

    // create a hexagon
    glTranslatef(4,6,0);
    glRotatef(-95,1,-1,-1);
    ngon(6);
    glFlush();
    glLoadIdentity();

    // create a circle by creating an ngon with more than 29 sides
    glColor3f(0.1, 0.6, 0.4);
    glTranslatef(1.5, -1.0, 0);
    glRotatef(-90, 0, -1, -1);
    ngon(40);

    // reset our matrix, otherwise rotation would still be off from
    // previous calls to glRotate. I invoke it at a late stage because it made
    // positioning the circles easier.
    glLoadIdentity();

    // create an octagon
    glColor3f(0.615, 0.964, 0.78);  // light green
    glTranslatef(-1.5, -1.5, 0);
    glRotatef(-105, 0, -1, -1);
    ngon(8);

}
