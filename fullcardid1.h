#ifndef FULLCARDID1_H
#define FULLCARDID1_H

#include <QGraphicsItemGroup>
#include "cardid1.h"

// TODO: переименовать в CardID1
class FullCardID1 : public QGraphicsItemGroup
{
public:
    FullCardID1(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    CardID1 * frontCard() const;
    CardID1 * backCard() const;

    void setVisibleChip(bool v);
    bool isVisibleChip() const;

    void setVisibleMagstripe(bool v);
    bool isVisibleMagstripe() const;

    QRectF boundingRect() const;

private:
    CardID1 * front_card;
    CardID1 * back_card;
};

#endif // FULLCARDID1_H
