/**
* @author Borislav S. Sabotinov
* A software radio user interface. I used widgets and a grid layout.
* Here is a guide I followed:
* https://doc.qt.io/qt-5/qtwidgets-widgets-groupbox-example.html
*/

#include "radio.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QMenu>
#include <QPushButton>
#include <QRadioButton>

#include <QVBoxLayout>
#include <QSlider>
#include <QSpinBox>

#include <QDial>
#include <QVBoxLayout>
#include <QLCDNumber>

/**
 * Initialize the software radio interface and give it an initial size
 * @brief Radio::Radio
 */
Radio::Radio()
{
    QGridLayout *grid = new QGridLayout;

    waveForm = new WaveForm(this);

    grid->addWidget(createModulationGroup(), 0, 0);
    grid->addWidget(createBassGroup(), 1, 0);
    grid->addWidget(createTrebleGroup(), 0, 1);
    grid->addWidget(createVolumeGroup(), 1, 1);
    grid->addWidget(createStationGroup(), 2, 0);
    grid->addWidget(createExitCtlGroup(), 2, 1);
    setLayout(grid);


}


/**
 * Three radio buttons for modulation. Can be either AM, FM, or XM Satellite.
 * Only one may be active at a time.
 * @brief Radio::createModulationGroup
 * @return
 */
QGroupBox *Radio::createModulationGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Modulation: "));

    QRadioButton *amRadio = new QRadioButton(tr("&AM"));
    QRadioButton *fmRadio = new QRadioButton(tr("F&M"));
    QRadioButton *xmRadio = new QRadioButton(tr("XM &Satelite"));

    amRadio->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(amRadio);
    vbox->addWidget(fmRadio);
    vbox->addWidget(xmRadio);
    // add a zero-width spacer-item that expands vertically from the
    // top of the layout downwards. I use this to prevent the radio buttons from
    // stretching dynamically if the window is resized. They would be very far apart
    // if the window is made full size, for example.
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

/**
 * Uses a dial that can be turned by clicking and holding the left mouse button.
 * Connected to an LCD, which displays the value.
 * @brief Radio::createBassGroup
 * @return
 */
QGroupBox *Radio::createBassGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("B&ass: "));

    QDial *dial;
    QLCDNumber *lcd;

    dial = new QDial;
    lcd = new QLCDNumber;
    lcd->setPalette(QColor(155,185,40,255));  // a splash of color for fun
    lcd->setMinimumHeight(50);
    dial->setFocusPolicy(Qt::StrongFocus);
    dial->setMinimum(0);
    dial->setMaximum(100);
    // connect the dial to the LCD
    connect(dial, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(dial);
    vbox->addWidget(lcd);
    groupBox->setLayout(vbox);
    return groupBox;
}


/**
 * SpinBox is connected to a Slider and an LCD.
 * The value may be manipulated either through the SpinBox or Slider.
 * The LCD is there just to display the value.
 * @brief Radio::createTrebleGroup
 * @return
 */
QGroupBox *Radio::createTrebleGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Treble: "));
    groupBox->setFlat(true);

    QSpinBox *spinBox = new QSpinBox;
    QSlider *slider = new QSlider(Qt::Vertical);
    spinBox->setRange(0, 100);
    slider->setRange(0, 100);
    QObject::connect(spinBox, SIGNAL(valueChanged(int)),
    slider, SLOT(setValue(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)),
    spinBox, SLOT(setValue(int)));
    spinBox->setValue(55);  // initial value
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(spinBox);
    layout->addWidget(slider);

    QLCDNumber *lcd;
    lcd = new QLCDNumber;
    lcd->setPalette(QColor(255,165,0,255));  // a splash of color for fun
    lcd->setMinimumWidth(150);
    lcd->display(55);
    // connect the spinBox to the LCD
    connect(spinBox, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));

    // Using horizontal layout so LCD may be on the right side.
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(spinBox);
    hbox->addWidget(slider);
    hbox->addWidget(lcd);
    hbox->addStretch(1);
    groupBox->setLayout(hbox);

    return groupBox;
}

/**
 * SpinBox is connected to a Slider. Both may be used to change the volume value.
 * @brief Radio::createVolumeGroup
 * @return
 */
QGroupBox *Radio::createVolumeGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("&Volume: "));
    groupBox->setCheckable(false);

    QSpinBox *spinBox = new QSpinBox;
    QSlider *slider = new QSlider(Qt::Horizontal);
    spinBox->setRange(0, 5);
    slider->setRange(0, 5);
    QObject::connect(spinBox, SIGNAL(valueChanged(int)),
    slider, SLOT(setValue(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)),
    spinBox, SLOT(setValue(int)));
    spinBox->setValue(35);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(spinBox);
    layout->addWidget(slider);

    // connect spin box and slider to update the Cosine graph
    connect(spinBox, SIGNAL(valueChanged(int)),
                waveForm, SLOT(updateVol(int)));


    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(spinBox);
    vbox->addWidget(slider);

    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

WaveForm* Radio::getWaveForm()
{
    return this->waveForm;
}

/**
 * QDoubleSpinBox, which holds double values, to change the station.
 * Precision is set to 1 so we can simulate actual channel values (eg. 102.7 or 96.7 FM)
 * @brief Radio::createStationGroup
 * @return
 */
QGroupBox *Radio::createStationGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("&Station: "));
    groupBox->setCheckable(false);

    QSpinBox *spinBox = new QSpinBox;
    spinBox->setRange(0, 100);
//    spinBox->setDecimals(1);
    spinBox->setValue(1);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(spinBox);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(spinBox);

    // connect spin box and slider to update the Cosine graph
    connect(spinBox, SIGNAL(valueChanged(int)),
                waveForm, SLOT(updateFre(int)));

    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

/**
 * Creates a push button that may be used to exit the program.
 * @brief Radio::createExitCtlGroup
 * @return
 */
QGroupBox *Radio::createExitCtlGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr(""));
    QPushButton *closeButton = new QPushButton(tr("&E&x&i&t"));
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(closeButton);
    // connect a click action on the button to trigger close(), which exits the program.
    QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    groupBox->setLayout(hbox);
    return groupBox;
}
