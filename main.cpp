/**
* @author Borislav S. Sabotinov
* A simple driver to launch the main window.
*/

#include <QApplication>
#include <QDesktopWidget>

#include "mainwindow.h"

/**
 * @brief qMain
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.resize( 800, 600 );
    window.show();
    return app.exec();
}
