void ConnectionTool::paint(QPainter &painter, const KoViewConverter &converter)
{
    // get the correctly sized rect for painting handles
    QRectF handleRect = handlePaintRect(QPointF());

    painter.setRenderHint(QPainter::Antialiasing, true);

    if (m_currentStrategy) {
        painter.save();
        m_currentStrategy->paint(painter, converter);
        painter.restore();
    }

    QList<KoShape*> shapes = canvas()->shapeManager()->shapes();
    for (QList<KoShape*>::const_iterator end = shapes.constBegin(); end !=  shapes.constEnd(); ++end) {
        KoShape* shape = *end;
        if (!dynamic_cast<KoConnectionShape*>(shape)) {
            // only paint connection points of textShapes not inside a tos container and other shapes
            if (shape->shapeId() == TextShape_SHAPEID && dynamic_cast<KoTosContainer*>(shape->parent())) continue;

            painter.save();
            painter.setPen(Qt::black);
            QTransform transform = shape->absoluteTransformation(0);
            KoShape::applyConversion(painter, converter);
            // Draw all the connection points of the shape
            KoConnectionPoints connectionPoints = shape->connectionPoints();
            KoConnectionPoints::const_iterator cp = connectionPoints.constBegin();
            KoConnectionPoints::const_iterator lastCp = connectionPoints.constEnd();
            for(; cp != lastCp; ++cp) {
                if (shape == findNonConnectionShapeAtPosition(transform.map(cp.value().position)) ) {
                    handleRect.moveCenter(transform.map(cp.value().position));
                    painter.setBrush(cp.key() == m_activeHandle && shape == m_currentShape ?
                                     Qt::red : Qt::white);
                    painter.drawRect(handleRect);
                }
            }
            painter.restore();
        }
    }
    // paint connection points or connection handles depending
    // on the shape the mouse is currently
    if (m_currentShape && m_editMode == EditConnection) {
        KoConnectionShape *connectionShape = dynamic_cast<KoConnectionShape*>(m_currentShape);
        if (connectionShape) {
            int radius = handleRadius()+1;
            int handleCount = connectionShape->handleCount();
            for(int i = 0; i < handleCount; ++i) {
                painter.save();
                painter.setPen(Qt::blue);
                painter.setBrush(i == m_activeHandle ? Qt::red : Qt::white);
                painter.setTransform(connectionShape->absoluteTransformation(&converter) * painter.transform());
                connectionShape->paintHandle(painter, converter, i, radius);
                painter.restore();
            }
        }
    }
}