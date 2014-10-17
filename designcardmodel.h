#ifndef DESIGNCARDMODEL_H
#define DESIGNCARDMODEL_H

#include <QAbstractItemModel>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QDebug>

#include "designtitem.h"
#include "fullcardid1.h"

class DesignCardModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    enum Columns {
        POS_X,
        POS_Y,
        TEXT,
        TEXT_SIZE,
        SIDE,

        COLUMN_COUNTS
    };

public:
    DesignCardModel(QObject *parent = 0);
    void setScene(QGraphicsScene * s, FullCardID1 * c);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public slots:
    void add();
    void remove(int row);
    DesigntTextItem * item(int row) const;
    int getRow(DesigntTextItem * item) const;

    void sceneChanged (const QList<QRectF> & region);

private:
    QList <DesigntTextItem *> elements;
    QGraphicsScene * scene;

    FullCardID1 * card;
};

#endif // DESIGNCARDMODEL_H
