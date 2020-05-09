#ifndef OKRESYOCHRONNE_H
#define OKRESYOCHRONNE_H

#include <QDialog>

namespace Ui {
class OkresyOchronne;
}

class OkresyOchronne : public QDialog
{
    Q_OBJECT

public:
    explicit OkresyOchronne(QWidget *parent = nullptr);
    ~OkresyOchronne();

private:
    Ui::OkresyOchronne *ui;
};

#endif // OKRESYOCHRONNE_H
