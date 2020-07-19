/**
* Implementation of Sphere class
*/

#include "Sphere.h"
#include <QtCore/QDebug>

/**
 * @brief Sphere::Sphere
 * @param rootEntity
 */
Sphere::Sphere(Qt3DCore::QEntity *rootEntity)
    : m_rootEntity(rootEntity)
{
    // Sphere shape data
    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh();
    sphereMesh->setRings(20);
    sphereMesh->setSlices(20);
    sphereMesh->setRadius(2);

    // Sphere mesh transform
    Qt3DCore::QTransform *sphereTransform = new Qt3DCore::QTransform();

    sphereTransform->setScale(1.3f);
    sphereTransform->setTranslation(QVector3D(-5.0f, -4.0f, 0.0f));

    Qt3DExtras::QPhongMaterial *sphereMaterial = new Qt3DExtras::QPhongMaterial();
    sphereMaterial->setDiffuse(QColor(QRgb(0xafeeee)));

    // Sphere
    sphereObj = new Qt3DCore::QEntity(m_rootEntity);
    sphereObj->addComponent(sphereMesh);
    sphereObj->addComponent(sphereMaterial);
    sphereObj->addComponent(sphereTransform);
}

/**
 * @brief Sphere::~Sphere
 */
Sphere::~Sphere()
{
}

/**
 * Allows us to toggle the sphere on and off.
 * @brief Sphere::enableSphere
 * @param enabled
 */
void Sphere::enableSphere(bool enabled)
{
    sphereObj->setEnabled(enabled);
}
