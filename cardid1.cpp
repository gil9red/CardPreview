#include "cardid1.h"

#include <QBrush>
#include <QPen>

CardID1::CardID1(QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsItemGroup(parent, scene)
{
    plate = new QtRoundedRectItem();
    chip = new QtRoundedRectItem();

    addToGroup(plate);
    addToGroup(chip);

    const QSizeF sizePlate(85.60, 53.98);
    const QColor colorPlate("#FFFFF0"); // Слоновая кость

    const QPointF posChip(9.0, 18.0);
    const QSizeF sizeChip(14, 11);
    const QColor colorChip("#D4AF37"); // Золотой металлик

    const float roundRect = 2.2;
    const QPen pen(Qt::black, 0.7);

    plate->setRoundedRect(QRectF(QPointF(0, 0), sizePlate), roundRect, roundRect);
    plate->setBrush(colorPlate);
    plate->setPen(pen);

    chip->setPos(posChip);
    chip->setRoundedRect(QRectF(QPointF(0, 0), sizeChip), roundRect, roundRect);
    chip->setBrush(colorChip); // Золотой металлик (#D4AF37)
    chip->setPen(pen);
}

QRectF CardID1::boundingRect () const {
    return plate->boundingRect();
}
