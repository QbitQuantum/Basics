void SymbolDataEditor::correctLimits()
{
    if (limits.height() < 0)
    {
        qreal top = limits.top();
        limits.setTop(limits.bottom());
        limits.setBottom(top);
    }

    if (limits.width() < 0)
    {
        qreal left = limits.left();
        limits.setLeft(limits.right());
        limits.setRight(left);
    }

    if (scene->items().size() > Item::LimitsRect)
    {
        QGraphicsRectItem* limitsRectItem = static_cast<QGraphicsRectItem *>(scene->items(Qt::AscendingOrder).at(Item::LimitsRect));
        limitsRectItem->setRect(limits);
    }

}