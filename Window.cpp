#include "Window.h"
#include "ui_Window.h"

#include "cardid1.h"
#include "designtitem.h"

#include <QGraphicsLinearLayout>
#include <QSettings>
#include <QDebug>

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

//    DesigntImageItem * item = new DesigntImageItem();
//    item->setCard(card);
//    item->setImage("index.jpg");
//    item->setImageSize(25, 30);
//    scene.addItem(item);


    QSettings ini("settings.ini", QSettings::IniFormat);
    ui->splitter->restoreState(ini.value("splitter").toByteArray());
    restoreGeometry(ini.value("geometry").toByteArray());
}

Window::~Window()
{
    delete ui;
}

void Window::on_tb_add_clicked()
{
    model.add(ui->cb_front->isChecked());
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
    DesigntTextItem * item = model.item(index);
    item->setSelected(true);
}
