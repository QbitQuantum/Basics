    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value){
        if(change == ItemPositionHasChanged){
            QGraphicsEllipseItem *item = qgraphicsitem_cast<QGraphicsEllipseItem *>(parentItem());

            qreal diff = qSqrt(x()*x() + y()*y());
            item->setRect(MakeCircleRect(diff - kCropItemControlPointRadius));
        }

        return QGraphicsEllipseItem::itemChange(change, value);
    }