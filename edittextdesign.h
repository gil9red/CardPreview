#ifndef EDITTEXTDESIGN_H
#define EDITTEXTDESIGN_H

#include <QDialog>

namespace Ui {
    class EditTextDesign;
}

#include "designtitem.h"

class EditTextDesign : public QDialog
{
    Q_OBJECT

public:
    explicit EditTextDesign(QWidget *parent = 0);
    ~EditTextDesign();

    void setDesignTextItem(DesigntTextItem * dti);

private:
    Ui::EditTextDesign * ui;
    DesigntTextItem * item;

public slots:
    void accept();
};

#endif // EDITTEXTDESIGN_H
