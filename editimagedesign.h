#ifndef EDITIMAGEDESIGN_H
#define EDITIMAGEDESIGN_H

#include <QDialog>

namespace Ui {
    class EditImageDesign;
}

#include "designtitem.h"

class EditImageDesign : public QDialog
{
    Q_OBJECT

public:
    explicit EditImageDesign(QWidget *parent = 0);
    ~EditImageDesign();

    void setDesignItem(DesigntImageItem * dti);

private:
    Ui::EditImageDesign *ui;
    DesigntImageItem * item;

public slots:
    void accept();

private slots:
    void on_tb_select_path_clicked();
};

#endif // EDITIMAGEDESIGN_H
