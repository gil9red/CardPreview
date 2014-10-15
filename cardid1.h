#ifndef CARDID1_H
#define CARDID1_H

#include <QGraphicsItemGroup>
#include "qtroundedrectitem.h"

class CardID1 : public QGraphicsItemGroup
{
public:
    CardID1(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

private:
    QtRoundedRectItem * plate;
    QtRoundedRectItem * chip;
};

#endif // CARDID1_H
