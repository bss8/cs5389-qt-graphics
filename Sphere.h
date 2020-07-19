/**
* @author Borislav S. Sabotinov
* This is based on an example project I found on the QT website, so I can
* play around with 3D objects.
* Here is the documentation and project I used:
* https://doc.qt.io/qt-5/qt3d-basicshapes-cpp-example.html
*/


#ifndef SPHERE_H
#define SPHERE_H

#include <QtCore/QObject>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>

#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>

class Sphere : public QObject
{
    Q_OBJECT

public:
    explicit Sphere(Qt3DCore::QEntity *rootEntity);
    ~Sphere();

public slots:
    void enableSphere(bool enabled);

private:
    Qt3DCore::QEntity *m_rootEntity;
    Qt3DCore::QEntity *sphereObj;
};

#endif // SPHERE_H
