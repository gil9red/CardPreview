#ifndef CARDID1_H
#define CARDID1_H

#include <QGraphicsItemGroup>
#include "qtroundedrectitem.h"

//class CardID1 : public QGraphicsItemGroup
class CardID1 : public QtRoundedRectItem
{
public:
    CardID1(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
//    QRectF boundingRect () const;

    void setVisibleChip(bool v);
    bool isVisibleChip() const;

    void setVisibleMagstripe(bool v);
    bool isVisibleMagstripe() const;

private:
//    QtRoundedRectItem * plate;
    QtRoundedRectItem * chip;
    QGraphicsRectItem * magstripe;

    QGraphicsItemGroup * group;
};

#endif // CARDID1_H
