void KoPatternBackground::paint(QPainter &painter, const KoViewConverter &converter, KoShapePaintingContext &/*context*/, const QPainterPath &fillPath) const
{
    Q_D(const KoPatternBackground);
    if (! d->imageData)
        return;

    painter.save();

    if (d->repeat == Tiled) {
        // calculate scaling of pixmap
        QSizeF targetSize = d->targetSize();
        QSizeF imageSize = d->imageData->imageSize();
        qreal scaleX = targetSize.width() / imageSize.width();
        qreal scaleY = targetSize.height() / imageSize.height();

        QRectF targetRect = fillPath.boundingRect();
        // undo scaling on target rectangle
        targetRect.setWidth(targetRect.width() / scaleX);
        targetRect.setHeight(targetRect.height() / scaleY);

        // determine pattern offset
        QPointF offset = d->offsetFromRect(targetRect, imageSize);

        // create matrix for pixmap scaling
        QTransform matrix;
        matrix.scale(scaleX, scaleY);

        painter.setClipPath(fillPath);
        painter.setWorldTransform(matrix, true);
        painter.drawTiledPixmap(targetRect, d->imageData->pixmap(imageSize.toSize()), -offset);
    } else if (d->repeat == Original) {
        QRectF sourceRect(QPointF(0, 0), d->imageData->imageSize());
        QRectF targetRect(QPoint(0, 0), d->targetSize());
        targetRect.moveCenter(fillPath.boundingRect().center());
        painter.setClipPath(fillPath);
        painter.drawPixmap(targetRect, d->imageData->pixmap(sourceRect.size().toSize()), sourceRect);
    } else if (d->repeat == Stretched) {
        painter.setClipPath(fillPath);
        // undo conversion of the scaling so that we can use a nicely scaled image of the correct size
        qreal zoomX, zoomY;
        converter.zoom(&zoomX, &zoomY);
        zoomX = zoomX ? 1 / zoomX : zoomX;
        zoomY = zoomY ? 1 / zoomY : zoomY;
        painter.scale(zoomX, zoomY);

        QRectF targetRect = converter.documentToView(fillPath.boundingRect());
        painter.drawPixmap(targetRect.topLeft(), d->imageData->pixmap(targetRect.size().toSize()));
    }

    painter.restore();
}