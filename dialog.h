#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

#include <QGraphicsScene>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_tb_add_clicked();
    void on_tb_rem_clicked();

    void on_tb_upd_scene_clicked();

private:
    Ui::Dialog *ui;
    QGraphicsScene scene;
};

#endif // DIALOG_H
