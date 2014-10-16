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

//    ui->splitter->setSizes(QList <int> () << 1 << 1);

//    front_card = new CardID1();
//    back_card = new CardID1();

//    QGraphicsItemGroup * group = new QGraphicsItemGroup();
//    group->addToGroup(front_card);
//    group->addToGroup(back_card);
//    back_card->setY(front_card->boundingRect().height() + 10);

//    front_card->setVisibleChip(ui->cb_chip->isChecked());
//    back_card->setVisible(ui->cb_back_side->isChecked());
//    back_card->setVisibleMagstripe(ui->cb_magstripe->isChecked());

    card = new FullCardID1();
    scene.addItem(card);
    model.setScene(&scene, card);

    QObject::connect(ui->table->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     SLOT(tableSelectionChanged(QItemSelection,QItemSelection)));

    tableSelectionChanged(QItemSelection(), QItemSelection());

    // TODO: нажатием на кнопку текущий выделенный в таблице элемент должен быть выделен на сцене

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
    ui->tb_rem->setEnabled(ui->table->selectionModel()->hasSelection());
}
void Window::on_cb_chip_clicked(bool checked)
{
    card->setVisibleChip(checked);
}
void Window::on_cb_magstripe_clicked(bool checked)
{
    card->setVisibleMagstripe(checked);
}
void Window::on_cb_back_side_clicked(bool checked)
{
    card->backCard()->setVisible(checked);
}

void Window::closeEvent(QCloseEvent *event) {
    QSettings ini("settings.ini", QSettings::IniFormat);
    ini.setValue("geometry", saveGeometry());
    ini.setValue("splitter", ui->splitter->saveState());
    ini.sync();

    QWidget::closeEvent(event);
}
