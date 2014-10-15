#ifndef DESIGNCARDMODEL_H
#define DESIGNCARDMODEL_H

#include <QAbstractItemModel>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>

class DesignCardModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit DesignCardModel(QObject *parent = 0);
    void setScene(QGraphicsScene * s);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QModelIndex index(int row, int column, const QModelIndex &) const;
    QModelIndex parent(const QModelIndex &) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role) {
        if (!index.isValid())
            return false;

        QGraphicsSimpleTextItem * item = static_cast <QGraphicsSimpleTextItem *> (index.internalPointer());
        switch (index.column()) {
        case 0:
            item->setX(value.toDouble());
            break;

        case 1:
            item->setY(value.toDouble());
            break;

        case 2:
            item->setText(value.toString());
            break;
        }
        return false;
    }

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public slots:
    void add();
    void remove(int row);
    QGraphicsSimpleTextItem * item(int row) const;

private:
    QList <QGraphicsSimpleTextItem *> elements;
    QGraphicsScene * scene;
};

#endif // DESIGNCARDMODEL_H
