#include "cardid1.h"

#include <QBrush>
#include <QPen>

CardID1::CardID1(QGraphicsItem *parent, QGraphicsScene *scene)
    : QtRoundedRectItem(parent, scene)
{
// TODO: указывать размер в миллиметрах.
// Пример:
//    int PixelWidthDimension = myWidget->logicalDpiX(); //width dots per inch
//    int PixelHeightDimesion = myWidget->logicalDpiY(); //width dots per inch
//    double inch = (double)myWidthInPixel / (double)PixelWidthDimension;
//
//double x_fromMMtoPixels(double mm) {
//    final double dm = mm / 25.4; // Миллиметры в дюймы
//    final double pixels = dm * QApplication.desktop().logicalDpiX();
//    return pixels;
//}
//double y_fromMMtoPixels(double mm) {
//    final double dm = mm / 25.4; // Миллиметры в дюймы
//    final double pixels = dm * QApplication.desktop().logicalDpiY();
//    return pixels;
//}
//QPointF fromMMtoPixels(double x, double y) {
//    x = x_fromMMtoPixels(x);
//    y = y_fromMMtoPixels(y);
//    return new QPointF(x, y);
//}
//QPointF fromMMtoPixels(QPointF pos_mm) {
//    return fromMMtoPixels(pos_mm.x(), pos_mm.y());
//}

//QRectF fromMMtoPixels(double x, double y, double w, double h) {
//    x = x_fromMMtoPixels(x);
//    y = y_fromMMtoPixels(y);
//    w = x_fromMMtoPixels(w);
//    h = y_fromMMtoPixels(h);
//    return new QRectF(x, y, w, h);
//}
//QRectF fromMMtoPixels(QRectF rect) {
//    final double x = rect.x();
//    final double y = rect.y();
//    final double w = rect.width();
//    final double h = rect.height();
//    return fromMMtoPixels(x, y, w, h);
//}
//QSize fromMMtoPixels(QSize size) {
//    final double w = (double) size.width();
//    final double h = (double) size.height();
//    final int x = (int) x_fromMMtoPixels(w);
//    final int y = (int) y_fromMMtoPixels(h);
//    return new QSize(x, y);
//}
//
//
// https://en.wikipedia.org/wiki/ISO/IEC_7810 :
// "The ID-1 format specifies a size of 85.60 × 53.98 mm (3.370 × 2.125 in) and rounded corners with a radius of 2.88–3.48 mm."
//
// https://ru.wikipedia.org/wiki/Карта_с_магнитной_полосой :
// "Магнитная полоса располагается на расстоянии 5,66 мм от края карты и имеет 9,52 мм в ширину"


    const QSizeF sizePlate(85.60, 53.98);
    const QColor colorPlate("#FFFFF0"); // Слоновая кость

    const QPointF posChip(9.0, 18.0);
    const QSizeF sizeChip(13, 12);
    const QColor colorChip("#D4AF37"); // Золотой металлик

    const float roundRect = 2.2;
    const QPen pen(Qt::black, 0.7);

    setRoundedRect(QRectF(QPointF(0, 0), sizePlate), roundRect, roundRect);
    setBrush(colorPlate);
    setPen(pen);

    chip = new QtRoundedRectItem();
    chip->setPos(posChip);
    chip->setRoundedRect(QRectF(QPointF(0, 0), sizeChip), roundRect, roundRect);
    chip->setBrush(colorChip); // Золотой металлик (#D4AF37)
    chip->setPen(pen);

    magstripe = new QGraphicsRectItem();
    magstripe->setPos(0, 5.0);
    magstripe->setRect(0, 0, sizePlate.width(), 13.0);
    magstripe->setBrush(Qt::black);
    magstripe->setPen(Qt::NoPen);

    group = new QGraphicsItemGroup();
    group->addToGroup(chip);
    group->addToGroup(magstripe);
    group->setParentItem(this);

    setVisibleChip(false);
    setVisibleMagstripe(false);
}

void CardID1::setVisibleChip(bool v) {
    chip->setVisible(v);
}
bool CardID1::isVisibleChip() const {
    return chip->isVisible();
}

void CardID1::setVisibleMagstripe(bool v) {
    magstripe->setVisible(v);
}
bool CardID1::isVisibleMagstripe() const {
    return magstripe->isVisible();
}
