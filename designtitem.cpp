#include "designtitem.h"

DesigntTextItem::DesigntTextItem(QGraphicsItem * parent)
    : QGraphicsSimpleTextItem(parent),
      card(0)
{
    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemSendsGeometryChanges);

    QFont f = font();
    f.setFamily("Arial");
    setTextSize(4.0);
}
int DesigntTextItem::type() const {
    return TypeDesignItem::TEXT_DESIGN_ITEM;
}

void DesigntTextItem::setCard(FullCardID1 * c) {
    card = c;
}

void DesigntTextItem::setTextSize(qreal size) {
    // TODO: не меняет размер шрифта
    qDebug() << size;
    QFont f = font();
    f.setPointSizeF(size);
    setFont(f);
}
qreal DesigntTextItem::textSize() const {
    return font().pointSizeF();
}

QPointF DesigntTextItem::pos() const {
    CardID1 * card = side_card();
    if (!card)
        return QGraphicsSimpleTextItem::pos();

    return card->mapFromScene(QGraphicsSimpleTextItem::pos());
}
qreal DesigntTextItem::x() const {
    return pos().x();
}
qreal DesigntTextItem::y() const {
    return pos().y();
}

void DesigntTextItem::setPos(const QPointF & _pos) {
    CardID1 * card = side_card();
    QPointF new_pos = _pos;
    if (card)
        new_pos = card->mapToScene(_pos);

    QGraphicsSimpleTextItem::setPos(new_pos);
}
void DesigntTextItem::setX(qreal x) {
    setPos(QPointF(x, this->y()));
}
void DesigntTextItem::setY(qreal y) {
    setPos(QPointF(this->x(), y));
}

QString DesigntTextItem::str_side() const {
    switch (side())
    {
        case Front_Side:
            return "front";

        case Back_Side:
            return "back";

        case None_Side:
            return "none";
    }

    return "none";
}
DesigntTextItem::CardSide DesigntTextItem::side() const {
    CardSide s = None_Side;

    CardID1 * frontCard = card->frontCard();
    CardID1 * backCard = card->backCard();

    const QRectF area(scenePos(), boundingRect().size());

    if (frontCard->mapToScene(frontCard->rect()).boundingRect().contains(area))
        return Front_Side;

    else if (backCard->mapToScene(frontCard->rect()).boundingRect().contains(area))
        return Back_Side;

    return s;
}
CardID1 * DesigntTextItem::side_card() const {
    switch (side()) {
        case Front_Side:
            return card->frontCard();

        case Back_Side:
            return card->backCard();

        case None_Side:
            return 0;
    }

    return 0;
}

QVariant DesigntTextItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionChange) {
        // value это новое положение.
        QPointF newPos = value.toPointF();
        const QRectF rect = card->boundingRect();
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




DesigntImageItem::DesigntImageItem(QGraphicsItem * parent)
    : QGraphicsPixmapItem(parent),
      card(0) {

    setFlags(QGraphicsItem::ItemIsMovable
             | QGraphicsItem::ItemIsSelectable
             | QGraphicsItem::ItemSendsGeometryChanges);

    setTransformationMode(Qt::SmoothTransformation);
}
int DesigntImageItem::type() const {
    return TypeDesignItem::IMAGE_DESIGN_ITEM;
}

void DesigntImageItem::setCard(FullCardID1 * c) {
    card = c;
}

void DesigntImageItem::setImage(const QPixmap & pixmap) {
    imagePath = QString();
    originalPixmap = pixmap;
}
void DesigntImageItem::setImage(const QString & path) {
    imagePath = path;
    originalPixmap.load(imagePath);
}
QString DesigntImageItem::getImagePath() const {
    return imagePath;
}
void DesigntImageItem::setImageSize(qreal width, qreal height) {
    setPixmap(originalPixmap.scaled(width, height,
                                    Qt::IgnoreAspectRatio,
                                    Qt::SmoothTransformation));
}
QSizeF DesigntImageItem::imageSize() const {
    return pixmap().size();
}

QVariant DesigntImageItem::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == QGraphicsItem::ItemPositionChange) {
        // value это новое положение.
        QPointF newPos = value.toPointF();
        const QRectF rect = card->boundingRect();
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
    return QGraphicsPixmapItem::itemChange(change, value);
}
