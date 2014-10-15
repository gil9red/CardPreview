#ifndef DESIGNTITEM_H
#define DESIGNTITEM_H

#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>
#include <QDebug>
#include "cardid1.h"

class DesigntTextItem: public QGraphicsSimpleTextItem
{
public:
    DesigntTextItem(QGraphicsItem * parent = 0);
    void setCard(CardID1 * c);

    void setTextSize(qreal size);
    qreal textSize();

private:
    CardID1 * cardID1;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};


#endif // DESIGNTITEM_H
