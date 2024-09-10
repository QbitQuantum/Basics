QSGNode *QQuickMouseArea::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data)
{
    Q_UNUSED(data);
    Q_D(QQuickMouseArea);

    if (!qmlVisualTouchDebugging())
        return 0;

    QSGRectangleNode *rectangle = static_cast<QSGRectangleNode *>(oldNode);
    if (!rectangle) rectangle = d->sceneGraphContext()->createRectangleNode();

    rectangle->setRect(QRectF(0, 0, width(), height()));
    rectangle->setColor(QColor(255, 0, 0, 50));
    rectangle->update();
    return rectangle;
}