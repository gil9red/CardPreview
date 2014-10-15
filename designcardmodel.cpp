#include "designcardmodel.h"

DesignCardModel::DesignCardModel(QObject *parent) :
    QAbstractItemModel(parent),
    scene(0) {

}

void DesignCardModel::setScene(QGraphicsScene * s) {
    scene = s;
}

int DesignCardModel::rowCount(const QModelIndex &) const {
    return elements.length();
}
int DesignCardModel::columnCount(const QModelIndex &) const {
    return 3; // x, y и text
}

QModelIndex DesignCardModel::index(int row, int column, const QModelIndex &) const {
    if (!hasIndex(row, column))
        return QModelIndex();

    return createIndex(row, column, item(row));
}
QModelIndex DesignCardModel::parent(const QModelIndex &) const {
    return QModelIndex();
}
QVariant DesignCardModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        QGraphicsSimpleTextItem * item = static_cast <QGraphicsSimpleTextItem *> (index.internalPointer());
        switch (index.column()) {
        case 0:
            return item->x();

        case 1:
            return item->y();

        case 2:
            return item->text();

        default:
            return QVariant();
        }

    } else
        return QVariant();
}

Qt::ItemFlags DesignCardModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant DesignCardModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return "x";

        case 1:
            return "y";

        case 2:
            return "text";
        }
    }

    return QVariant();
}

void DesignCardModel::add() {
    const int row = rowCount();
    beginInsertRows(QModelIndex(), row, row);

    QGraphicsSimpleTextItem * item = new QGraphicsSimpleTextItem();
    item->setPos(0.0, 0.0);
    item->setText("empty");
    item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

    elements.append(item);
    scene->addItem(item);

    endInsertRows();
}
void DesignCardModel::remove(int row) {
    beginRemoveRows(QModelIndex(), row, row);

    QGraphicsSimpleTextItem * item = elements.takeAt(row);
    scene->removeItem(item);
    scene->deleteLater();

    endRemoveRows();
}
QGraphicsSimpleTextItem * DesignCardModel::item(int row) const {
    return elements.at(row);
}
