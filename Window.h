#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Window;
}

#include <QGraphicsScene>
#include <QItemSelection>
#include "designcardmodel.h"
#include "fullcardid1.h"

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    void on_tb_add_clicked();
    void on_tb_rem_clicked();
    void tableSelectionChanged(const QItemSelection & selected, const QItemSelection & deselected);
    void on_cb_chip_clicked(bool checked);
    void on_cb_magstripe_clicked(bool checked);
    void on_cb_back_side_clicked(bool checked);

private:
    Ui::Window *ui;
    QGraphicsScene scene;
    DesignCardModel model;
    FullCardID1 * card;

protected:
    void closeEvent(QCloseEvent * event);
};

#endif // DIALOG_H
