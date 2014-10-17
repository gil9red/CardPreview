#include "edittextdesign.h"
#include "ui_edittextdesign.h"

EditTextDesign::EditTextDesign(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTextDesign),
    item(0)
{
    ui->setupUi(this);
}

EditTextDesign::~EditTextDesign()
{
    delete ui;
}

void EditTextDesign::setDesignTextItem(DesigntTextItem * dti)
{
    item = dti;

    ui->cb_included->setChecked(item->isVisible());
    ui->sb_x->setValue(item->x());
    ui->sb_y->setValue(item->y());
    ui->sb_size_text->setValue((int) item->textSize());
    ui->le_hex_rgb->setText(item->brush().color().name());
    ui->cb_bold->setChecked(item->font().bold());
    ui->cb_italic->setChecked(item->font().italic());
    ui->le_text->setText(item->text());
}

void EditTextDesign::accept() {
    if (item)
    {
        QFont font(item->font());
        font.setBold(ui->cb_bold->isChecked());
        font.setItalic(ui->cb_italic->isChecked());

        item->setVisible(ui->cb_included->isChecked());
        item->setPos(QPointF(ui->sb_x->value(), ui->sb_y->value()));
        item->setTextSize(ui->sb_size_text->value());
        item->setBrush(QColor(ui->le_hex_rgb->text()));
        item->setFont(font);
        item->setText(ui->le_text->text());
    }

    QDialog::accept();
}
