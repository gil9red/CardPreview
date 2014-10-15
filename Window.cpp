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
    ui->table->setModel(&model);
    model.setScene(&scene);

    ui->splitter->setSizes(QList <int> () << 1);

    CardID1 * card = new CardID1();
    scene.addItem(card);
}

Window::~Window()
{
    delete ui;
}

void Window::on_tb_add_clicked()
{
    model.add();

//    const int index = ui->table->rowCount();
//    ui->table->setRowCount(index + 1);
//    ui->table->setItem(index, 0, new DesigntItem("0", &scene));
//    ui->table->setItem(index, 1, new DesigntItem("0", &scene));
//    ui->table->setItem(index, 2, new DesigntItem("null", &scene));
}
void Window::on_tb_rem_clicked()
{
    const int index = ui->table->currentIndex().row();
    model.remove(index);

//    if (!ui->table->rowCount())
//        return;

//    const int index = ui->table->currentRow();
//    ui->table->removeRow(index);
}
