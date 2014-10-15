#include "Window.h"
#include "ui_Window.h"

#include "cardid1.h"
#include "designtitem.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->scale(3.0, 3.0);
    ui->table->setModel(&model);

    ui->splitter->setSizes(QList <int> () << 1);

    CardID1 * card = new CardID1();
    scene.addItem(card);
    model.setScene(&scene, card);

    QObject::connect(ui->table->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     SLOT(tableSelectionChanged(QItemSelection,QItemSelection)));

    tableSelectionChanged(QItemSelection(), QItemSelection());
}

Window::~Window()
{
    delete ui;
}

void Window::on_tb_add_clicked()
{
    model.add();
}
void Window::on_tb_rem_clicked()
{
    const int index = ui->table->currentIndex().row();
    model.remove(index);
}

void Window::tableSelectionChanged(const QItemSelection &, const QItemSelection &) {
    ui->tb_rem->setEnabled(ui->table->selectionModel()->hasSelection());
}
