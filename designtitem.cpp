#include "designtitem.h"

DesigntTextItem::DesigntTextItem(QGraphicsItem * parent)
    : QGraphicsSimpleTextItem(parent) {

    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemSendsGeometryChanges);

    setTextSize(4.0);
}

void DesigntTextItem::setCard(CardID1 * c) {
    cardID1 = c;
}

void DesigntTextItem::setTextSize(qreal size) {
    setFont(QFont("Arial", size));
}
qreal DesigntTextItem::textSize() {
    return font().pointSizeF();
}

QVariant DesigntTextItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionChange && cardID1) {
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
