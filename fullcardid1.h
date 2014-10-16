#ifndef FULLCARDID1_H
#define FULLCARDID1_H

#include <QGraphicsItemGroup>
#include "cardid1.h"

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

//    void addDesignElement(QGraphicsItem * item, bool front);

    QRectF boundingRect() const;

private:
    CardID1 * front_card;
    CardID1 * back_card;

//    QGraphicsItemGroup * front_design;
//    QGraphicsItemGroup * back_design;
};

#endif // FULLCARDID1_H
