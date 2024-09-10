QSGNode *QQuickRectangle::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
{
    Q_UNUSED(data);
    Q_D(QQuickRectangle);

    if (width() <= 0 || height() <= 0
            || (d->color.alpha() == 0 && (!d->pen || d->pen->width() == 0 || d->pen->color().alpha() == 0))) {
        delete oldNode;
        return 0;
    }

    QSGRectangleNode *rectangle = static_cast<QSGRectangleNode *>(oldNode);
    if (!rectangle) rectangle = d->sceneGraphContext()->createRectangleNode();

    rectangle->setRect(QRectF(0, 0, width(), height()));
    rectangle->setColor(d->color);

    if (d->pen && d->pen->isValid()) {
        rectangle->setPenColor(d->pen->color());
        rectangle->setPenWidth(d->pen->width());
        rectangle->setAligned(d->pen->pixelAligned());
    } else {
        rectangle->setPenWidth(0);
    }

    rectangle->setRadius(d->radius);
    rectangle->setAntialiasing(antialiasing());

    QGradientStops stops;
    if (d->gradient) {
        stops = d->gradient->gradientStops();
    }
    rectangle->setGradientStops(stops);

    rectangle->update();

    return rectangle;
}