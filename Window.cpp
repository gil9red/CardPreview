#include "Window.h"
#include "ui_Window.h"

#include "cardid1.h"
#include "designtitem.h"
#include "edittextdesign.h"

#include <QGraphicsLinearLayout>
#include <QSettings>
#include <QDebug>


#define WARNING( msg ) qWarning( "\"%s\": in file \"%s\", func \"%s\", line %i", qPrintable( msg ), __FILE__, __FUNCTION__, __LINE__ );


Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->scale(3.0, 3.0);
    ui->table->setModel(&model);

    card = new FullCardID1();
    scene.addItem(card);
    model.setScene(&scene, card);

    QObject::connect(ui->table->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     SLOT(tableSelectionChanged(QItemSelection,QItemSelection)));

    tableSelectionChanged(QItemSelection(), QItemSelection());

    QSettings ini("settings.ini", QSettings::IniFormat);
    ui->splitter->restoreState(ini.value("splitter").toByteArray());
    restoreGeometry(ini.value("geometry").toByteArray());
}

Window::~Window()
{
    delete ui;
}

void Window::on_tb_add_text_clicked()
{
    model.add_text();
}
void Window::on_tb_add_image_clicked()
{
    model.add_image();
}
void Window::on_tb_rem_clicked()
{
    const int index = ui->table->currentIndex().row();
    model.remove(index);
}
void Window::tableSelectionChanged(const QItemSelection &, const QItemSelection &) {
    const bool has_selection = ui->table->selectionModel()->hasSelection();

    ui->tb_rem->setEnabled(has_selection);
    ui->tb_select_item->setEnabled(has_selection);
    ui->tb_edit->setEnabled(has_selection);
}
void Window::on_cb_chip_clicked(bool checked)
{
    card->setVisibleChip(checked);
}
void Window::on_cb_magstripe_clicked(bool checked)
{
    card->setVisibleMagstripe(checked);
}

void Window::closeEvent(QCloseEvent *event)
{
    QSettings ini("settings.ini", QSettings::IniFormat);
    ini.setValue("geometry", saveGeometry());
    ini.setValue("splitter", ui->splitter->saveState());
    ini.sync();

    QWidget::closeEvent(event);
}

void Window::on_tb_select_item_clicked()
{
    const int index = ui->table->currentIndex().row();

    // Убираем выделение всех элементов
    foreach (QGraphicsItem * gi, scene.selectedItems())
        gi->setSelected(false);

    // Выделяем текущий элемент таблицы
    QGraphicsItem * item = model.item(index);
    item->setSelected(true);
}
void Window::on_tb_edit_clicked()
{
    const int index = ui->table->currentIndex().row();

    QGraphicsItem * item = model.item(index);
    switch (item->type())
    {
        case TypeDesignItem::TEXT_DESIGN_ITEM:
        {
            DesigntTextItem * dti = dynamic_cast <DesigntTextItem *> (item);
            if (!dti)
            {
                WARNING("Pointer on DesigntTextItem is null!");
                return;
            }

            EditTextDesign etd;
            etd.setDesignTextItem(dti);
            etd.exec();
            break;
        }

        case TypeDesignItem::IMAGE_DESIGN_ITEM:
        {
            DesigntImageItem * dii = dynamic_cast <DesigntImageItem *> (item);
            if (!dii)
            {
                WARNING("Pointer on DesigntImageItem is null!");
                return;
            }

            // TODO: добавить редактор для изображений.

            break;
        }

        default:
            WARNING("Unknown item design type!");
    }
}
