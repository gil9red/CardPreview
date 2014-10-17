#include "designcardmodel.h"

DesignCardModel::DesignCardModel(QObject *parent) :
    QAbstractItemModel(parent),
    scene(0),
    card(0)
{

}

void DesignCardModel::setScene(QGraphicsScene * s, FullCardID1 * c) {
    scene = s;
    card = c;
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
            return (int) item->x();

        case POS_Y:
            return (int) item->y();

        case TEXT:
            return item->text();

        case TEXT_SIZE:
            return (int) item->textSize();

        case FRONT_SIDE:
            return item->isFrontMode();

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
        item->setX(value.toInt());
        break;

    case POS_Y:
        item->setY(value.toInt());
        break;

    case TEXT:
        item->setText(value.toString());
        break;

    case TEXT_SIZE:
        item->setTextSize(value.toInt());
        break;

    case FRONT_SIDE:
        item->setFrontMode(value.toBool());
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

        case FRONT_SIDE:
            return "front_side";
        }
    }

    return QVariant();
}

void DesignCardModel::add(bool front) {
    const int row = rowCount();
    beginInsertRows(QModelIndex(), row, row);

    CardID1 * cur_card = front ? card->frontCard() : card->backCard();

    DesigntTextItem * item = new DesigntTextItem();
    item->setCard(card);
    item->setPos(cur_card->rect().width() / 2.0, cur_card->rect().height() / 2.0);
    item->setText("empty");
    item->setFrontMode(front);

    scene->addItem(item);
    elements.append(item);

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
