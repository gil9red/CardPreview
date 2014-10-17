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

    DesigntTextItem * item = static_cast <DesigntTextItem *> (index.internalPointer());

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case POS_X:
            return (int) item->x();

        case POS_Y:
            return (int) item->y();

        case TEXT:
            return item->text();

        case TEXT_SIZE:
            return (int) item->textSize();

        case SIDE:
            return item->str_side();

        default:
            return QVariant();
        }

    } else if (role == Qt::BackgroundRole) {
        // Если текущая сторона элемента None (т.е. не передняя и не задняя), выделяем этот элемент в таблице
        if (index.column() == SIDE && item->side() == DesigntTextItem::None_Side)
            return Qt::red;

    } else
        return QVariant();

    return QVariant();
}
bool DesignCardModel::setData(const QModelIndex& index, const QVariant& value, int) {
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
    }
    return false;
}

Qt::ItemFlags DesignCardModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return 0;

    // Столбец SIDE только для чтения
    if (index.column() == SIDE)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    else
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

        case SIDE:
            return "side";
        }
    }

    return QVariant();
}

void DesignCardModel::add() {
    const int row = rowCount();
    beginInsertRows(QModelIndex(), row, row);

    CardID1 * cur_card = card->frontCard();

    DesigntTextItem * item = new DesigntTextItem();
    item->setCard(card);
    item->setPos(cur_card->rect().width() / 2.0, cur_card->rect().height() / 2.0);
    item->setText("empty");

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
    // Алгоритм для определения какой элемент на сцене перемещается
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
