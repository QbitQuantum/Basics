QGraphicsItem * EnvelopeClient::createGraphicsItem()
{
    int padding = 4;
    QGraphicsRectItem *item = new QGraphicsRectItem();
    ParameterGraphicsItem *parameterItem = new ParameterGraphicsItem(this);
    QRectF rect = QRect(0, 0, 1200, 420);
    rect = rect.translated(parameterItem->boundingRect().width() + 2 * padding, padding);
    parameterItem->setPos(padding, padding);
    parameterItem->setParentItem(item);
    EnvelopeGraphicsItem *ourItem = new EnvelopeGraphicsItem(rect, this, item);
    item->setRect((rect | parameterItem->boundingRect().translated(parameterItem->pos())).adjusted(-padding, -padding, padding, padding));
    item->setPen(QPen(QBrush(Qt::black), 1));
    item->setBrush(QBrush(Qt::white));
    QObject::connect(this, SIGNAL(changedYSteps(int)), ourItem, SLOT(setHorizontalSlices(int)));
    return item;
}