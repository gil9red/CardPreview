#include "dialog.h"
#include "ui_dialog.h"
#include "qtroundedrectitem.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);

    ui->splitter->setSizes(QList <int> () << 1);

    QtRoundedRectItem * roundedRectItem = new QtRoundedRectItem();
    roundedRectItem->setPos(0, 0);
    roundedRectItem->setRoundedRect(QRectF(0, 0, 85.60, 53.98), 3.0, 3.0);
    roundedRectItem->setBrush(Qt::red);
    roundedRectItem->setPen(QPen(Qt::black, 2.0));
    scene.addItem(roundedRectItem);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_tb_add_clicked()
{
    const int index = ui->table->rowCount();
    ui->table->setRowCount(index + 1);
    ui->table->setItem(index, 0, new QTableWidgetItem("0"));
    ui->table->setItem(index, 1, new QTableWidgetItem("0"));
    ui->table->setItem(index, 2, new QTableWidgetItem("null"));

//    QtRoundedRectItem * roundedRectItem = new QtRoundedRectItem();
//    roundedRectItem->setPos(0, 0);
//    roundedRectItem->setRoundedRect(QRectF(0, 0, 85.60, 53.98), 3.0, 3.0);
//    roundedRectItem->setBrush(Qt::red);
//    roundedRectItem->setPen(QPen(Qt::black, 2.0));
//    scene.addItem(roundedRectItem);
}
void Dialog::on_tb_rem_clicked()
{
    if (!ui->table->rowCount())
        return;

    const int index = ui->table->currentRow();
    ui->table->removeRow(index);
}
void Dialog::on_tb_upd_scene_clicked()
{

}
