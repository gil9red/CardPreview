#ifndef DESIGNTITEM_H
#define DESIGNTITEM_H

#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>
#include <QDebug>
#include "cardid1.h"

class DesigntTextItem: public QGraphicsSimpleTextItem
{
public:
    DesigntTextItem(QGraphicsItem * parent = 0)
        : QGraphicsSimpleTextItem(parent) {
        setFlags(QGraphicsItem::ItemIsMovable
                 | QGraphicsItem::ItemIsSelectable
                 | QGraphicsItem::ItemSendsGeometryChanges);
    }

    void setCard(CardID1 * c) {
        cardID1 = c;
    }

private:
    CardID1 * cardID1;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) {
        if (change == QGraphicsItem::ItemPositionChange && scene()) {
            // value это новое положение.
            QPointF newPos = value.toPointF();
            const QRectF rect = cardID1->boundingRect();
            const QRectF area(newPos, boundingRect().size());

            if (!rect.contains(area)) {
                // Сохраняем элемент внутри прямоугольника сцены.
                const qreal width = boundingRect().size().width();
                const qreal height = boundingRect().size().height();
                newPos.setX(qMin(rect.right() - width, qMax(newPos.x(), rect.left())));
                newPos.setY(qMin(rect.bottom() - height, qMax(newPos.y(), rect.top())));
                return newPos;
            }
        }
        return QGraphicsSimpleTextItem::itemChange(change, value);
    }
};


#endif // DESIGNTITEM_H
