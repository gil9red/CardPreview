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
    virtual int type() const;

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
    DesigntImageItem(QGraphicsItem * parent = 0);
    virtual int type() const;

    void setCard(FullCardID1 * c);

    void setImage(const QPixmap & pixmap);
    void setImage(const QString & path);
    QString getImagePath() const;
    void setImageSize(qreal width, qreal height);
    QSizeF imageSize() const;

private:
    FullCardID1 * card;
    QPixmap originalPixmap;
    QString imagePath;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // DESIGNTITEM_H
