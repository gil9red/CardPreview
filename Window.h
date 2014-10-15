#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Window;
}

#include <QGraphicsScene>
#include "designcardmodel.h"


class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    void on_tb_add_clicked();
    void on_tb_rem_clicked();

private:
    Ui::Window *ui;
    QGraphicsScene scene;
    DesignCardModel model;
};

#endif // DIALOG_H
