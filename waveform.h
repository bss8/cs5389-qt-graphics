#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <QObject>
#include <QWidget>
#include <QtOpenGL/QGLWidget>

class WaveForm : public QGLWidget
{
    Q_OBJECT
public:
    WaveForm(QWidget *parent = 0);
    ~WaveForm();
    void drawCosGraph();

public slots:
    void updateVol(int volume);
    void updateFre(int frequency);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    int volume = 5;
    int frequency = 1.0;
};

#endif // WAVEFORM_H
