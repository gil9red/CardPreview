#ifndef QTROUNDEDRECTITEM_H
#define QTROUNDEDRECTITEM_H

#include <QGraphicsRectItem>

class QtRoundedRectItem : public QGraphicsRectItem
{
public:
    QtRoundedRectItem( QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    void paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * widget );

    // /Get the rounded rect corner x radius
    double getRadiusX() const { return m_radius_x; }

    // /Get the rounded rect corner y radius
    double getRadiusY() const { return m_radius_y; }

    // /Set the rounded rect corner x radius
    void setRadiusX( const double radius_x) { m_radius_x = radius_x; }

    // /Set the rounded rect corner y radius
    void setRadiusY( const double radius_y) { m_radius_y = radius_y; }

    // /Set the rounded rect
    void setRoundedRect( const QRectF rect, const double radius_x, const double radius_y);

private:
    // /The rounded rect corner x radius
    double m_radius_x;

    // /The rounded rect corner y radius
    double m_radius_y;
};

#endif // QTROUNDEDRECTITEM_H
