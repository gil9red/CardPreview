#ifndef DESIGNTITEM_H
#define DESIGNTITEM_H

#include <QTableWidgetItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>

class DesigntItem : public QTableWidgetItem
{
public:
    DesigntItem(const QString &text, QGraphicsScene * scene);

public:
    QGraphicsSimpleTextItem * gstItem;
};

#endif // DESIGNTITEM_H
