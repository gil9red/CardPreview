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
    setFrontMode(true);
}

void DesigntTextItem::setCard(FullCardID1 * c) {
    card = c;
}

void DesigntTextItem::setFrontMode(bool front_mode) {
    if (front == front_mode)
        return;

    // Координаты относительно стороны карты (зависит от front)
    QPointF p(x(), y());

    front = front_mode;

    if (card) {
        // В связи с сменой сторой, сделаем пересчет координат
        CardID1 * cur_card = front ? card->frontCard() : card->backCard();
        QGraphicsSimpleTextItem::setPos(cur_card->mapToScene(p));
    }
}
bool DesigntTextItem::isFrontMode() const {
    return front;
}

void DesigntTextItem::setTextSize(qreal size) {
    setFont(QFont("Arial", size));
}
qreal DesigntTextItem::textSize() const {
    return font().pointSizeF();
}

void DesigntTextItem::setX(qreal x) {
    // Установка в координаты относительно сцены

    if (card) {
        CardID1 * cur_card = front ? card->frontCard() : card->backCard();
        QGraphicsSimpleTextItem::setX(cur_card->mapToScene(QPointF(x, this->y())).x());
    } else
        QGraphicsSimpleTextItem::setX(x);
}
void DesigntTextItem::setY(qreal y) {
    // Установка в координаты относительно сцены

    if (card) {
        CardID1 * cur_card = front ? card->frontCard() : card->backCard();
        QGraphicsSimpleTextItem::setY(cur_card->mapToScene(QPointF(this->x(), y)).y());
    } else
        QGraphicsSimpleTextItem::setY(y);
}

qreal DesigntTextItem::x() const {
    // Возврат в координатах от текущей стороны карточки

    if (card) {
        CardID1 * cur_card = front ? card->frontCard() : card->backCard();
        return cur_card->mapFromScene(pos()).x();
    } else
        return QGraphicsSimpleTextItem::x();
}
qreal DesigntTextItem::y() const {
    // Возврат в координатах от текущей стороны карточки

    if (card) {
        CardID1 * cur_card = front ? card->frontCard() : card->backCard();
        return cur_card->mapFromScene(pos()).y();
    } else
        return QGraphicsSimpleTextItem::y();
}

QVariant DesigntTextItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionChange) {
        CardID1 * cur_card = front ? card->frontCard() : card->backCard();

        // value это новое положение.
        QPointF newPos = value.toPointF();
//        qDebug() << newPos << cur_card->mapFromScene(newPos);
        newPos = cur_card->mapFromScene(newPos);

        const QRectF rect = cur_card->boundingRect();
        const QRectF area(newPos, boundingRect().size());

//        qDebug() << rect << area;

        if (!rect.contains(area)) {
            // Сохраняем элемент внутри прямоугольника сцены.
            const qreal width = boundingRect().size().width();
            const qreal height = boundingRect().size().height();

            newPos.setX(qMin(rect.right() - width, qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom() - height, qMax(newPos.y(), rect.top())));
            newPos = cur_card->mapToScene(newPos);
            return newPos;
        }
    }
    return QGraphicsSimpleTextItem::itemChange(change, value);
}
