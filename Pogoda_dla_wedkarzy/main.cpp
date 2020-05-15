#include "glowneokno.h"

#include <QApplication>
/*! \mainpage Dokumentacja aplikacji Pogoda dla wędkarzy
 * \section Wprowadzenie
 * Dokumentacja została wygenerowana za pomocą aplikacji Doxygen.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GlowneOkno w;
    w.show();
    return a.exec();
}
