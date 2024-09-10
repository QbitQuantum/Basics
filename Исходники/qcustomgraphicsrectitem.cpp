    virtual void operator()(QGraphicsItem* item, const QRectF& rect)
    {
        QGraphicsRectItem* rectItem =
                dynamic_cast<QGraphicsRectItem*>(item);

        if (rectItem)
        {
            rectItem->setRect(rect);
        }
    }