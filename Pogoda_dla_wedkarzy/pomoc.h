#ifndef POMOC_H
#define POMOC_H

#include <QDialog>

namespace Ui {
class Pomoc;
}
/*!
 * \brief Klasa Pomoc
 * Klasa implementuje okno pomocnicze pomoc.
 */
class Pomoc : public QDialog
{
    Q_OBJECT

public:
    explicit Pomoc(QWidget *parent = nullptr);
    ~Pomoc();

private:
    Ui::Pomoc *ui;
};

#endif // POMOC_H
