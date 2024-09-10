QImage DesignerSupport::renderImageForItem(QQuickItem *referencedItem, const QRectF &boundingRect, const QSize &imageSize)
{
    if (referencedItem == 0 || referencedItem->parentItem() == 0) {
        qDebug() << __FILE__ << __LINE__ << "Warning: Item can be rendered.";
        return QImage();
    }

    QSGLayer *renderTexture = m_itemTextureHash.value(referencedItem);

    Q_ASSERT(renderTexture);
    if (renderTexture == 0)
         return QImage();
    renderTexture->setRect(boundingRect);
    renderTexture->setSize(imageSize);
    renderTexture->setItem(QQuickItemPrivate::get(referencedItem)->rootNode());
    renderTexture->markDirtyTexture();
    renderTexture->updateTexture();

    QImage renderImage = renderTexture->toImage();
    renderImage = renderImage.mirrored(false, true);

    if (renderImage.size().isEmpty())
        qDebug() << __FILE__ << __LINE__ << "Warning: Image is empty.";

    return renderImage;
}