    QRectF itemToViewportRect(const QRectF & rect, QWidget * widget)
    {
        QGraphicsView *view = 0;
        if (widget)
            view = qobject_cast<QGraphicsView *>(widget->parentWidget());

        if (view)
            return item->mapRectToScene(view->transform().inverted().mapRect(rect));

        return rect;
    }