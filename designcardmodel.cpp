#include "designcardmodel.h"

DesignCardModel::DesignCardModel(QObject *parent) :
    QAbstractItemModel(parent),
    scene(0) {

}

void DesignCardModel::setScene(QGraphicsScene * s, CardID1 * c) {
    scene = s;
    cardID1 = c;
    QObject::connect(scene, SIGNAL(changed(QList<QRectF>)), SLOT(sceneChanged(QList<QRectF>)));
}

int DesignCardModel::rowCount(const QModelIndex &) const {
    return elements.length();
}
int DesignCardModel::columnCount(const QModelIndex &) const {
    return COLUMN_COUNTS;
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

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        DesigntTextItem * item = static_cast <DesigntTextItem *> (index.internalPointer());
        switch (index.column()) {
        case POS_X:
            return item->x();

        case POS_Y:
            return item->y();

        case TEXT:
            return item->text();

        case TEXT_SIZE:
            return item->textSize();

        default:
            return QVariant();
        }

    } else
        return QVariant();
}
bool DesignCardModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    Q_UNUSED(role)

    if (!index.isValid())
        return false;

    DesigntTextItem * item = static_cast <DesigntTextItem *> (index.internalPointer());
    switch (index.column()) {
    case POS_X:
        item->setX(value.toDouble());
        break;

    case POS_Y:
        item->setY(value.toDouble());
        break;

    case TEXT:
        item->setText(value.toString());
        break;

    case TEXT_SIZE:
        item->setTextSize(value.toReal());
        break;

    }
    return false;
}

Qt::ItemFlags DesignCardModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant DesignCardModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case POS_X:
            return "x";

        case POS_Y:
            return "y";

        case TEXT:
            return "text";

        case TEXT_SIZE:
            return "text_size";
        }
    }

    return QVariant();
}

void DesignCardModel::add() {
    const int row = rowCount();
    beginInsertRows(QModelIndex(), row, row);

    DesigntTextItem * item = new DesigntTextItem();
    item->setCard(cardID1);
    item->setPos(0.0, 0.0);
    item->setText("empty");

    elements.append(item);
    scene->addItem(item);

    endInsertRows();
}
void DesignCardModel::remove(int row) {
    if (elements.isEmpty() || elements.length() <= row)
        return;

    beginRemoveRows(QModelIndex(), row, row);

    DesigntTextItem * item = elements.takeAt(row);
    scene->removeItem(item);

    endRemoveRows();
}

DesigntTextItem * DesignCardModel::item(int row) const {
    return elements.at(row);
}

int DesignCardModel::getRow(DesigntTextItem * item) const {
    return elements.indexOf(item);
}

void DesignCardModel::sceneChanged (const QList<QRectF> & region) {
    if (region.length() == 2) {
        QList <QGraphicsItem *> items = scene->items(region[0]);
        if (items.isEmpty())
            return;

        DesigntTextItem * item = static_cast <DesigntTextItem *> (items[0]);
        if (!item)
            return;

        const int row = getRow(item);
        emit dataChanged(index(row, 0), index(row, columnCount()));
    }
}
