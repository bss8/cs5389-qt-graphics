/**
* @author Borislav S. Sabotinov
* Defines a radio and the functions that will be used to create it's components.
*/

#ifndef RADIO_H
#define RADIO_H

#include <QWidget>
#include <QLCDNumber>
#include "waveform.h"

QT_BEGIN_NAMESPACE
class QGroupBox;
QT_END_NAMESPACE

/**
* @author: Borislav S. Sabotinov
* Defines a software radion UI
*/
class Radio : public QWidget
{
    Q_OBJECT

public:
    Radio();

    WaveForm* getWaveForm();

private:
    QGroupBox *createModulationGroup();
    QGroupBox *createBassGroup();
    QGroupBox *createTrebleGroup();
    QGroupBox *createVolumeGroup();
    QGroupBox *createStationGroup();
    QGroupBox *createExitCtlGroup();

    WaveForm *waveForm;
};


#endif
