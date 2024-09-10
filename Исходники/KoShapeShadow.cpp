void KoShapeShadow::paint(KoShape *shape, QPainter &painter, const KoViewConverter &converter)
{
    if (! d->visible)
        return;

    // So the approach we are taking here is to draw into a buffer image the size of boundingRect
    // We offset by the shadow offset at the time we draw into the buffer
    // Then we filter the image and draw it at the position of the bounding rect on canvas

    //the boundingRect of the shape or the KoSelection boundingRect of the group
    QRectF shadowRect = shape->boundingRect();
    QRectF zoomedClipRegion = converter.documentToView(shadowRect);

    // Init the buffer image
    QImage sourceGraphic(zoomedClipRegion.size().toSize(), QImage::Format_ARGB32_Premultiplied);
    sourceGraphic.fill(qRgba(0,0,0,0));
    // Init the buffer painter
    QPainter imagePainter(&sourceGraphic);
    imagePainter.setPen(Qt::NoPen);
    imagePainter.setBrush(Qt::NoBrush);
    imagePainter.setRenderHint(QPainter::Antialiasing, painter.testRenderHint(QPainter::Antialiasing));
    // Since our imagebuffer and the canvas don't align we need to offset our drawings
    imagePainter.translate(-1.0f*converter.documentToView(shadowRect.topLeft()));

    // Handle the shadow offset
    imagePainter.translate(converter.documentToView(offset()));

    KoShapeGroup *group = dynamic_cast<KoShapeGroup*>(shape);
    if (group) {
        d->paintGroupShadow(group, imagePainter, converter);
    } else {
        //apply shape's transformation
        imagePainter.setTransform(shape->absoluteTransformation(&converter), true);

        d->paintShadow(shape, imagePainter, converter);
    }
    imagePainter.end();

    // Blur the shadow (well the entire buffer)
    d->blurShadow(sourceGraphic, converter.documentToViewX(d->blur), d->color);

    // Paint the result
    painter.save();
    // The painter is initialized for us with canvas transform 'plus' shape transform
    // we are only interested in the canvas transform so 'subtract' the shape transform part
    painter.setTransform(shape->absoluteTransformation(&converter).inverted() * painter.transform());
    painter.drawImage(zoomedClipRegion.topLeft(), sourceGraphic);
    painter.restore();
}