#ifndef DESIGNTITEM_H
#define DESIGNTITEM_H


#include <QGraphicsScene>
#include <QDebug>
#include "fullcardid1.h"


namespace TypeDesignItem {
    const int TEXT_DESIGN_ITEM  = 0;
    const int IMAGE_DESIGN_ITEM = 1;
}


class DesigntTextItem: public QGraphicsSimpleTextItem
{
public:
    enum CardSide
    {
        Front_Side,
        Back_Side,
        None_Side
    };

public:
    DesigntTextItem(QGraphicsItem * parent = 0);
    virtual int type() const {
        return TypeDesignItem::TEXT_DESIGN_ITEM;
    }

    void setCard(FullCardID1 * c);

    void setTextSize(qreal size);
    qreal textSize() const;

    QPointF pos() const;
    qreal x() const;
    qreal y() const;

    void setPos(const QPointF & pos);
    void setX(qreal x);
    void setY(qreal y);

    QString str_side() const;
    CardSide side() const;
    CardID1 * side_card() const;

private:
    FullCardID1 * card;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};


class DesigntImageItem: public QGraphicsPixmapItem
{
public:
    DesigntImageItem(QGraphicsItem * parent = 0)
        : QGraphicsPixmapItem(parent),
          card(0) {

        setFlags(QGraphicsItem::ItemIsMovable
                 | QGraphicsItem::ItemIsSelectable
                 | QGraphicsItem::ItemSendsGeometryChanges);

        setTransformationMode(Qt::SmoothTransformation);
    }

    virtual int type() const {
        return TypeDesignItem::IMAGE_DESIGN_ITEM;
    }

    void setCard(FullCardID1 * c) {
        card = c;
    }

    void setImage(const QString & path) {
        imagePath = path;
        originalPixmap.load(imagePath);
    }
    QString getImagePath() const {
        return imagePath;
    }

    void setImageSize(qreal width, qreal height) {
        setPixmap(originalPixmap.scaled(width, height,
                                        Qt::IgnoreAspectRatio,
                                        Qt::SmoothTransformation));
    }
    QSizeF imageSize() const {
        return pixmap().size();
    }

private:
    FullCardID1 * card;
    QPixmap originalPixmap;
    QString imagePath;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) {
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
};

#endif // DESIGNTITEM_H
