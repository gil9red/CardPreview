#include "cardid1.h"

#include <QBrush>
#include <QPen>

CardID1::CardID1(QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsItemGroup(parent, scene)
{
    const QSizeF sizePlate(85.60, 53.98);
    const QColor colorPlate("#FFFFF0"); // Слоновая кость

    const QPointF posChip(9.0, 18.0);
    const QSizeF sizeChip(13, 12);
    const QColor colorChip("#D4AF37"); // Золотой металлик

    const float roundRect = 2.2;
    const QPen pen(Qt::black, 0.7);

    plate = new QtRoundedRectItem();
    plate->setRoundedRect(QRectF(QPointF(0, 0), sizePlate), roundRect, roundRect);
    plate->setBrush(colorPlate);
    plate->setPen(pen);

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

    addToGroup(plate);
    addToGroup(chip);
    addToGroup(magstripe);

    setVisibleChip(false);
    setVisibleMagstripe(false);
}

QRectF CardID1::boundingRect () const {
    return plate->boundingRect();
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
