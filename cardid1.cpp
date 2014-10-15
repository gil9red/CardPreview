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

    plate->setRoundedRect(QRectF(0, 0, 85.60, 53.98), 3.0, 3.0);
    plate->setBrush(QColor("#FFFFF0")); // Слоновая кость #FFFFF0
    plate->setPen(QPen(Qt::black, 0.5));

    chip->setPos(9.0, 18.0);
    chip->setRoundedRect(QRectF(0, 0, 14, 11), 2.0, 2.0);
    chip->setBrush(QColor("#D4AF37")); // Золотой металлик (#D4AF37)
    chip->setPen(QPen(Qt::black, 0.5));

    setScale(3.0);
}
