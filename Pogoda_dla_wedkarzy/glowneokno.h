#ifndef GLOWNEOKNO_H
#define GLOWNEOKNO_H

#include <QMainWindow>
#include "pomoc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GlowneOkno; }
QT_END_NAMESPACE

class GlowneOkno : public QMainWindow
{
    Q_OBJECT

public:
    GlowneOkno(QWidget *parent = nullptr);
    ~GlowneOkno();

private slots:

    void on_actionWy_wietl_pomoc_triggered();

private:
    Ui::GlowneOkno *ui;
    Pomoc *pomoc;
};
#endif // GLOWNEOKNO_H
