void QBlitterPaintEngine::fillRect(const QRectF &rect, const QBrush &brush)
{
    if (rect.size().isEmpty())
        return;

    Q_D(QBlitterPaintEngine);

    if (qbrush_style(brush) == Qt::SolidPattern
        && d->caps.canBlitterAlphaFillRect()) {
        d->fillRect(rect, qbrush_color(brush), true);
    } else if (qbrush_style(brush) == Qt::SolidPattern
        && qbrush_color(brush).alpha() == 0xff
        && d->caps.canBlitterFillRect()) {
        d->fillRect(rect, qbrush_color(brush), false);
    } else if ((brush.style() == Qt::TexturePattern) &&
               (brush.transform().type() <= QTransform::TxTranslate) &&
                ((d->caps.canBlitterDrawPixmapOpacity(brush.texture())) ||
                 (d->caps.canBlitterDrawPixmap(rect, brush.texture(), rect)))) {
        bool rectIsFilled = false;
        QRectF transformedRect = state()->matrix.mapRect(rect);
        qreal x = transformedRect.x();
        qreal y = transformedRect.y();
        QPixmap pm = brush.texture();
        d->unlock();
        int srcX = int(rect.x() - state()->brushOrigin.x() - brush.transform().dx()) % pm.width();
        if (srcX < 0)
            srcX = pm.width() + srcX;
        const int startX = srcX;
        int srcY = int(rect.y() - state()->brushOrigin.y() - brush.transform().dy()) % pm.height();
        if (srcY < 0)
            srcY = pm.height() + srcY;
        while (!rectIsFilled) {
            qreal blitWidth = (pm.width() ) - srcX;
            qreal blitHeight = (pm.height() ) - srcY;
            if (x + blitWidth > transformedRect.right())
                blitWidth = transformedRect.right() -x;
            if (y + blitHeight > transformedRect.bottom())
                blitHeight = transformedRect.bottom() - y;
            const QClipData *clipData = d->clip();
            if (clipData->hasRectClip) {
                QRect targetRect = QRect(x, y, blitWidth, blitHeight).intersected(clipData->clipRect);
                if (targetRect.isValid()) {
                    int tmpSrcX  = srcX + (targetRect.x() - x);
                    int tmpSrcY = srcY + (targetRect.y() - y);
                    QRect srcRect(tmpSrcX, tmpSrcY, targetRect.width(), targetRect.height());
                    d->pmData->blittable()->drawPixmap(targetRect, pm, srcRect);
                }
            } else if (clipData->hasRegionClip) {
                QVector<QRect> clipRects = clipData->clipRegion.rects();
                QRect unclippedTargetRect(x, y, blitWidth, blitHeight);
                QRegion intersectedRects = clipData->clipRegion.intersected(unclippedTargetRect);

                for (int i = 0; i < intersectedRects.rects().size(); ++i) {
                    QRect targetRect = intersectedRects.rects().at(i);
                    if (!targetRect.isValid() || targetRect.isEmpty())
                        continue;
                    int tmpSrcX = srcX + (targetRect.x() - x);
                    int tmpSrcY = srcY + (targetRect.y() - y);
                    QRect srcRect(tmpSrcX, tmpSrcY, targetRect.width(), targetRect.height());
                    d->pmData->blittable()->drawPixmap(targetRect, pm, srcRect);
                }
            }
            x+=blitWidth;
            if (qFuzzyCompare(x, transformedRect.right())) {
                x = transformedRect.x();
                srcX = startX;
                srcY = 0;
                y += blitHeight;
                if (qFuzzyCompare(y, transformedRect.bottom()))
                    rectIsFilled = true;
            } else
                srcX = 0;
        }
    } else {
        d->lock();
        d->pmData->markRasterOverlay(rect);
        QRasterPaintEngine::fillRect(rect, brush);
    }

}