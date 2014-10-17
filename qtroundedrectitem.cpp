#include "qtroundedrectitem.h"

#include <QPainter>

QtRoundedRectItem::QtRoundedRectItem( QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsRectItem(parent,scene)
{
    setFlags( QGraphicsItem::ItemIsFocusable
              | QGraphicsItem::ItemIsMovable
              | QGraphicsItem::ItemIsSelectable);
}

void QtRoundedRectItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(brush());
    painter->setPen(pen());
    painter->drawRoundedRect(rect(),m_radius_x,m_radius_y);
}

void QtRoundedRectItem::setRoundedRect( const QRectF rect, const double radius_x, const double radius_y)
{
    setRect(rect);
    setRadiusX(radius_x);
    setRadiusY(radius_y);
}
