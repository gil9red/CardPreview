#include "fullcardid1.h"

FullCardID1::FullCardID1(QGraphicsItem *parent, QGraphicsScene *scene) :
    QGraphicsItemGroup(parent, scene)
{
    front_card = new CardID1();
    back_card = new CardID1();

    addToGroup(front_card);
    addToGroup(back_card);

//    front_design = new QGraphicsItemGroup();
//    front_design->setParentItem(this);

//    back_design = new QGraphicsItemGroup();
//    back_design->setParentItem(this);

////    addToGroup(front_design);
////    addToGroup(back_design);

    back_card->setY(front_card->boundingRect().height() + 10);

    front_card->setVisibleChip(true);
    front_card->setVisibleMagstripe(false);

    back_card->setVisibleChip(false);
    back_card->setVisibleMagstripe(true);
}

CardID1 * FullCardID1::frontCard() const {
    return front_card;
}
CardID1 * FullCardID1::backCard() const {
    return back_card;
}

void FullCardID1::setVisibleChip(bool v) {
    front_card->setVisibleChip(v);
}
bool FullCardID1::isVisibleChip() const {
    return front_card->isVisibleChip();
}

void FullCardID1::setVisibleMagstripe(bool v) {
    back_card->setVisibleMagstripe(v);
}
bool FullCardID1::isVisibleMagstripe() const {
    return back_card->isVisibleMagstripe();
}

//void FullCardID1::addDesignElement(QGraphicsItem * item, bool front) {
//    addToGroup(item);

//    if (front)
//        item->setPos(item->mapFromItem(front_card), item->pos());
//    else
//        item->setPos(item->mapFromItem(back_card), item->pos());

//    if (front)
//        front_design->addToGroup(item);
//    else
//        back_design->addToGroup(item);
//}

QRectF FullCardID1::boundingRect() const {
    return QRectF(0, 0, front_card->rect().width(), front_card->rect().height() + back_card->rect().height() + 10);
}
