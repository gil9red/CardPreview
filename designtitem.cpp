#include "designtitem.h"

DesigntTextItem::DesigntTextItem(QGraphicsItem * parent)
    : QGraphicsSimpleTextItem(parent),
      card(0)
//      front_card(0),
//      back_card(0)
{
    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemSendsGeometryChanges);

    setTextSize(4.0);
//    setFrontMode(true);
}

void DesigntTextItem::setCard(FullCardID1 * c) {
    card = c;
}

//void DesigntTextItem::setFrontMode(bool front_mode) {
//    front = front_mode;
//}
//bool DesigntTextItem::isFrontMode() const {
//    return front;
//}

void DesigntTextItem::setTextSize(qreal size) {
    setFont(QFont("Arial", size));
}
qreal DesigntTextItem::textSize() {
    return font().pointSizeF();
}

QVariant DesigntTextItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionChange) {
        // value это новое положение.
        QPointF newPos = value.toPointF();
        const QRectF rect = card->boundingRect();
//        const QRectF rect = isFrontMode() ? front_card->boundingRect() : back_card->boundingRect();
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
