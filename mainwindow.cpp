/**
* This code is from a QT guide on 3D objects.
* It is the implementation of the Sphere header.
*/

#include <QtGui>
#include <QDockWidget>
#include <QtWidgets>
#include "radio.h"
#include "GL_Graphic_Objects.h"
#include "mainwindow.h"
#include "waveform.h"

// All of the below are just for the Sphere
#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtGui/QScreen>
#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>
#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

MainWindow::MainWindow()
{

    gl_graphic_objects = new GL_Graphic_Objects(this);
    setCentralWidget(gl_graphic_objects);

    createRadioDockWindow();
    createSphereDockWindow();
    createCosGraphWindow();
    createMenus();


    setWindowTitle(tr("Boris' Software Radio"));
    resize(1024, 800);
}

/**
 * Creates dock widget object that loads the Radio widget
 * created previously
 * @brief MainWindow::createDockWindows
 */
void MainWindow::createRadioDockWindow()
{
    QDockWidget *dock = new QDockWidget(tr("Radio Interface: "), this);
    radio = new Radio;
    dock->setWidget(radio);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
}

/**
 * @brief MainWindow::createMenus
 */
void MainWindow::createMenus()
{
    QMenu *fileMenu;
    QAction *exitAct;

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);

    QMenu *shapeMenu;
    QAction *sphereAct;

    sphereAct = new QAction(tr("&Toggle Sphere"), this);
    sphereAct->setShortcuts(QKeySequence::Quit);
    sphereAct->setStatusTip(tr("Toggle the sphere visible or invisible"));
    sphereAct->setCheckable(true);
    sphereAct->setChecked(true);
    sphereAct->connect(sphereAct, &QAction::triggered, modifier, &Sphere::enableSphere);
    shapeMenu = menuBar()->addMenu(tr("&Shapes"));
    shapeMenu->addAction(sphereAct);
}

/**
 * This method:
 * 1. creates a Sphere object and checkbox to toggle it on and off
 * 2. creates a dock window and adds the Sphere to it.
 * TODO: decompose into two methods
 * @brief MainWindow::createSphereDockWindow
 */
void MainWindow::createSphereDockWindow()
{
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x7a7f80)));
    QWidget *container = QWidget::createWindowContainer(view);
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(250, 150));
    container->setMaximumSize(screenSize);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    QDockWidget *dock = new QDockWidget(tr("A 3D sphere: "), this);

    dock->setWidget(widget);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    widget->setWindowTitle(QStringLiteral("Basic shapes"));

    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();

    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(12, 6, 5.0f));
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    // Scenemodifier
    modifier = new Sphere(rootEntity);

    // Set root object of the scene
    view->setRootEntity(rootEntity);

    // Create control widgets
    QCommandLinkButton *info = new QCommandLinkButton();
    info->setText(QStringLiteral("Qt3D Sphere Mesh"));
    info->setDescription(QString::fromLatin1("A 3D sphere. Click and hold down the left mouse button to move. Roll mouse wheel to zoom in or out."));
    info->setIconSize(QSize(0,0));

    QCheckBox *sphereCB = new QCheckBox(widget);
    sphereCB->setChecked(true);
    sphereCB->setText(QStringLiteral("Enable Sphere"));

    vLayout->addWidget(info);
    vLayout->addWidget(sphereCB);

    QObject::connect(sphereCB, &QCheckBox::stateChanged,
                     modifier, &Sphere::enableSphere);

    sphereCB->setChecked(true);
}

void MainWindow::createCosGraphWindow()
{
    waveForm = radio->getWaveForm();

    QDockWidget *dock = new QDockWidget(tr("AM Wave Form: "), this);
    dock->setWidget(waveForm);
    waveForm->setMinimumSize(QSize(400, 300));
    addDockWidget(Qt::LeftDockWidgetArea, dock);
}
