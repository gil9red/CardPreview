#include "qtroundedrectitem.h"

#include <cassert>
#include <sstream>
#include <QGraphicsScene>
#include <QPainter>

QtRoundedRectItem::QtRoundedRectItem( QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsRectItem(parent,scene)
{
    this->setFlags( QGraphicsItem::ItemIsFocusable
                    | QGraphicsItem::ItemIsMovable
                    | QGraphicsItem::ItemIsSelectable);
}

void QtRoundedRectItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(this->brush());
    painter->setPen(this->pen());
    painter->drawRoundedRect(this->rect(),m_radius_x,m_radius_y);
}

void QtRoundedRectItem::setRoundedRect( const QRectF rect, const double radius_x, const double radius_y)
{
    this->setRect(rect);
    this->setRadiusX(radius_x);
    this->setRadiusY(radius_y);
}
