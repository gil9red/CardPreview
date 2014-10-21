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
