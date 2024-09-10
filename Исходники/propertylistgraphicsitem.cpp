PropertyListGraphicsItem::PropertyListGraphicsItem(PropertyOwnerGraphicsItem* parent)
    : NWEBaseGraphicsItem(parent->getNetworkEditor())
    , parent_(parent)
    , currentHeaderMode_(NO_HEADER)
    , currentPropertyMode_(SHOW_LINKED_PROPERTIES)
    , currentPropertyModifier_(HIDE_NO_PROPERTIES)
    , currentLinkArrowMode_(SHOW_NO_ARROWS)
    , friendList_(0)
    , isVisibleInEditor_(false)
    , currentHeight_(0.f)
    , currentWidth_(0.f)
{
    tgtAssert(parent != 0, "passed null pointer");
    setZValue(ZValuesPropertyListGraphicsItem);
    setParent(parent);

    parent->getNetworkEditor()->scene()->addItem(this);

    parentLabel_ = new QGraphicsTextItem(this);
    parentLabel_->setParentItem(this);
    currentWidth_ = getParentLabel()->boundingRect().width();
    paint(0,0,0);
    createChildItems();
}