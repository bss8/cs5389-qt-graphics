/**
* @author Borislav S. Sabotinov
* Defines a class for GL graphical objects and associated functions.
* Some I decided to create manually based on an example I saw.
* For others, I used the ngon() function provided in the assignment.
*/

#ifndef GLobj_H
#define GLobj_H

#include <QtOpenGL/QGLWidget>

class GL_Graphic_Objects : public QGLWidget  {
    Q_OBJECT

public:
    GL_Graphic_Objects(QWidget *parent = 0);
    ~GL_Graphic_Objects();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void paintShapes();
    void paintCube();
    void paintCircle();
    void ngon(int n);
};

#endif
