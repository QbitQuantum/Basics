void KisCanvasWidgetBase::drawDecorations(QPainter & gc, const QRect &updateWidgetRect) const
{
    gc.save();
    if (!m_d->canvas) {
        dbgFile<<"canvas doesn't exist, in canvas widget base!";
    }
    // Setup the painter to take care of the offset; all that the
    // classes that do painting need to keep track of is resolution
    gc.setRenderHint(QPainter::Antialiasing);
    gc.setRenderHint(QPainter::TextAntialiasing);

    // This option does not do anything anymore with Qt4.6, so don't reenable it since it seems to break display
    // http://www.archivum.info/[email protected]/2010-01/00481/Re:-(Qt-interest)-Is-QPainter::HighQualityAntialiasing-render-hint-broken-in-Qt-4.6.html
    // gc.setRenderHint(QPainter::HighQualityAntialiasing);

    gc.setRenderHint(QPainter::SmoothPixmapTransform);


    gc.save();
    gc.setClipRect(updateWidgetRect);

    QTransform transform = m_d->coordinatesConverter->flakeToWidgetTransform();
    gc.setTransform(transform);

    // Paint the shapes (other than the layers)
    m_d->canvas->globalShapeManager()->paint(gc, *m_d->viewConverter, false);

    // draw green selection outlines around text shapes that are edited, so the user sees where they end
    gc.save();
    QTransform worldTransform = gc.worldTransform();
    gc.setPen( Qt::green );

    Q_FOREACH (KoShape *shape, canvas()->shapeManager()->selection()->selectedShapes()) {
        if (shape->shapeId() == "ArtisticText" || shape->shapeId() == "TextShapeID") {
            gc.setWorldTransform(shape->absoluteTransformation(m_d->viewConverter) * worldTransform);
            KoShape::applyConversion(gc, *m_d->viewConverter);
            gc.drawRect(QRectF(QPointF(), shape->size()));
        }
    }
    gc.restore();

    // Draw text shape over canvas while editing it, that's needs to show the text selection correctly
    QString toolId = KoToolManager::instance()->activeToolId();
    if (toolId == "ArtisticTextTool" || toolId == "TextTool") {
        gc.save();
        gc.setPen(Qt::NoPen);
        gc.setBrush(Qt::NoBrush);
        Q_FOREACH (KoShape *shape, canvas()->shapeManager()->selection()->selectedShapes()) {
            if (shape->shapeId() == "ArtisticText" || shape->shapeId() == "TextShapeID") {
                KoShapePaintingContext  paintContext(canvas(), false);
                gc.save();
                gc.setTransform(shape->absoluteTransformation(m_d->viewConverter) * gc.transform());
                canvas()->shapeManager()->paintShape(shape, gc, *m_d->viewConverter, paintContext);
                gc.restore();
            }
        }
        gc.restore();
    }