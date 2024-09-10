void RightToLeftPaintingStrategy::paint(KoShape *shape, QPainter &painter,
                                        const KoViewConverter &converter, bool forPrint)
{
    painter.save();
    const double width = d->canvas->canvasWidget()->width();
//    const double offsetX = d->canvas->canvasController()->canvasOffsetX();
    painter.translate(/*-2 * offsetX*/ + width, 0);
//     painter.scale(-1, 1);

    painter.setTransform(shape->absoluteTransformation(&converter) * painter.transform());

    if (shapeManager()) {
        shapeManager()->paintShape(shape, painter, converter, forPrint);
    }

    painter.restore();  // for the matrix
}