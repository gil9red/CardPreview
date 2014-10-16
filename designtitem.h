#ifndef DESIGNTITEM_H
#define DESIGNTITEM_H

#include <QGraphicsScene>
#include <QDebug>
#include "fullcardid1.h"


class DesigntTextItem: public QGraphicsSimpleTextItem
{
public:
    DesigntTextItem(QGraphicsItem * parent = 0);
    void setCard(FullCardID1 * c);

    void setFrontMode(bool front_mode);
    bool isFrontMode() const;

    void setTextSize(qreal size);
    qreal textSize() const;

    void setX(qreal x);
    void setY(qreal y);

    qreal x() const;
    qreal y() const;

private:
    FullCardID1 * card;
    bool front;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};


//class DesigntImageItem: public QGraphicsPixmapItem
//{
//public:
//    DesigntImageItem(QGraphicsItem * parent = 0)
//        : QGraphicsPixmapItem(parent),
//          cardID1(0) {

//        setFlags(QGraphicsItem::ItemIsMovable
//                 | QGraphicsItem::ItemIsSelectable
//                 | QGraphicsItem::ItemSendsGeometryChanges);

//        setTransformationMode(Qt::SmoothTransformation);
//    }

//    void setCard(CardID1 * c) {
//        cardID1 = c;
//    }

//    void setImage(const QString & path) {
//        imagePath = path;
//        originalPixmap.load(imagePath);
//    }
//    QString getImagePath() const {
//        return imagePath;
//    }

//    void setImageSize(qreal width, qreal height) {
//        setPixmap(originalPixmap.scaled(width, height,
//                                        Qt::IgnoreAspectRatio,
//                                        Qt::SmoothTransformation));
//    }
//    QSizeF imageSize() const {
//        return pixmap().size();
//    }

//private:
//    CardID1 * cardID1;
//    QPixmap originalPixmap;
//    QString imagePath;

//protected:
//    QVariant itemChange(GraphicsItemChange change, const QVariant &value) {
//        if (change == QGraphicsItem::ItemPositionChange && cardID1) {
//            // value это новое положение.
//            QPointF newPos = value.toPointF();
//            const QRectF rect = cardID1->boundingRect();
//            const QRectF area(newPos, boundingRect().size());

//            if (!rect.contains(area)) {
//                // Сохраняем элемент внутри прямоугольника сцены.
//                const qreal width = boundingRect().size().width();
//                const qreal height = boundingRect().size().height();
//                newPos.setX(qMin(rect.right() - width, qMax(newPos.x(), rect.left())));
//                newPos.setY(qMin(rect.bottom() - height, qMax(newPos.y(), rect.top())));
//                return newPos;
//            }
//        }
//        return QGraphicsPixmapItem::itemChange(change, value);
//    }
//};

#endif // DESIGNTITEM_H
