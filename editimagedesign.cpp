#include "editimagedesign.h"
#include "ui_editimagedesign.h"

#include <QFileDialog>
#include <QImageReader>

EditImageDesign::EditImageDesign(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditImageDesign),
    item(0)
{
    ui->setupUi(this);
}
EditImageDesign::~EditImageDesign()
{
    delete ui;
}

void EditImageDesign::setDesignItem(DesigntImageItem * dti)
{
    item = dti;

    ui->cb_included->setChecked(item->isVisible());
    ui->sb_x->setValue(item->x());
    ui->sb_y->setValue(item->y());
    ui->sb_width->setValue(item->imageSize().width());
    ui->sb_height->setValue(item->imageSize().height());
    ui->le_image_path->setText(item->getImagePath());
}

void EditImageDesign::accept() {
    if (item)
    {
        item->setVisible(ui->cb_included->isChecked());
        item->setPos(QPointF(ui->sb_x->value(), ui->sb_y->value()));
        item->setImage(ui->le_image_path->text());
        item->setImageSize(ui->sb_width->value(), ui->sb_height->value());
    }

    QDialog::accept();
}

void EditImageDesign::on_tb_select_path_clicked()
{
    QString filters = tr( "Images" );
    filters += " (";
    foreach (const QByteArray & format, QImageReader::supportedImageFormats())
        filters += QString( " *.%1" ).arg(QString(format.toLower()));
    filters += " )";
    filters += "\n" + tr("All files ") + "(*.*)";

    const QString & path = QFileDialog::getOpenFileName(this, QString(), QString(), filters);
    if (path.isEmpty())
        return;

    ui->le_image_path->setText(path);
}
