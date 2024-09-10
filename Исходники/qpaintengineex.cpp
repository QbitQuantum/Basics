void QPaintEngineEx::stroke(const QVectorPath &path, const QPen &pen)
{
#ifdef QT_DEBUG_DRAW
    qDebug() << "QPaintEngineEx::stroke()" << pen;
#endif

    Q_D(QPaintEngineEx);

    if (path.isEmpty())
        return;

    if (!d->strokeHandler) {
        d->strokeHandler = new StrokeHandler(path.elementCount()+4);
        d->stroker.setMoveToHook(qpaintengineex_moveTo);
        d->stroker.setLineToHook(qpaintengineex_lineTo);
        d->stroker.setCubicToHook(qpaintengineex_cubicTo);
    }

    if (!qpen_fast_equals(pen, d->strokerPen)) {
        d->strokerPen = pen;
        d->stroker.setJoinStyle(pen.joinStyle());
        d->stroker.setCapStyle(pen.capStyle());
        d->stroker.setMiterLimit(pen.miterLimit());
        qreal penWidth = pen.widthF();
        if (penWidth == 0)
            d->stroker.setStrokeWidth(1);
        else
            d->stroker.setStrokeWidth(penWidth);

        Qt::PenStyle style = pen.style();
        if (style == Qt::SolidLine) {
            d->activeStroker = &d->stroker;
        } else if (style == Qt::NoPen) {
            d->activeStroker = 0;
        } else {
            d->dasher.setDashPattern(pen.dashPattern());
            d->dasher.setDashOffset(pen.dashOffset());
            d->activeStroker = &d->dasher;
        }
    }

    if (!d->activeStroker) {
        return;
    }

    if (pen.style() > Qt::SolidLine) {
        if (pen.isCosmetic()) {
            d->activeStroker->setClipRect(d->exDeviceRect);
        } else {
            QRectF clipRect = state()->matrix.inverted().mapRect(QRectF(d->exDeviceRect));
            d->activeStroker->setClipRect(clipRect);
        }
    }

    const QPainterPath::ElementType *types = path.elements();
    const qreal *points = path.points();
    int pointCount = path.elementCount();

    const qreal *lastPoint = points + (pointCount<<1);

    d->strokeHandler->types.reset();
    d->strokeHandler->pts.reset();

    // Some engines might decide to optimize for the non-shape hint later on...
    uint flags = QVectorPath::WindingFill;

    if (path.elementCount() > 2)
        flags |= QVectorPath::NonConvexShapeMask;

    if (d->stroker.capStyle() == Qt::RoundCap || d->stroker.joinStyle() == Qt::RoundJoin)
        flags |= QVectorPath::CurvedShapeMask;

    // ### Perspective Xforms are currently not supported...
    if (!pen.isCosmetic()) {
        // We include cosmetic pens in this case to avoid having to
        // change the current transform. Normal transformed,
        // non-cosmetic pens will be transformed as part of fill
        // later, so they are also covered here..
        d->activeStroker->setCurveThresholdFromTransform(state()->matrix);
        d->activeStroker->begin(d->strokeHandler);
        if (types) {
            while (points < lastPoint) {
                switch (*types) {
                case QPainterPath::MoveToElement:
                    d->activeStroker->moveTo(points[0], points[1]);
                    points += 2;
                    ++types;
                    break;
                case QPainterPath::LineToElement:
                    d->activeStroker->lineTo(points[0], points[1]);
                    points += 2;
                    ++types;
                    break;
                case QPainterPath::CurveToElement:
                    d->activeStroker->cubicTo(points[0], points[1],
                                              points[2], points[3],
                                              points[4], points[5]);
                    points += 6;
                    types += 3;
                    flags |= QVectorPath::CurvedShapeMask;
                    break;
                default:
                    break;
                }
            }
            if (path.hasImplicitClose())
                d->activeStroker->lineTo(path.points()[0], path.points()[1]);

        } else {
            d->activeStroker->moveTo(points[0], points[1]);
            points += 2;
            while (points < lastPoint) {
                d->activeStroker->lineTo(points[0], points[1]);
                points += 2;
            }
            if (path.hasImplicitClose())
                d->activeStroker->lineTo(path.points()[0], path.points()[1]);
        }
        d->activeStroker->end();

        if (!d->strokeHandler->types.size()) // an empty path...
            return;

        QVectorPath strokePath(d->strokeHandler->pts.data(),
                               d->strokeHandler->types.size(),
                               d->strokeHandler->types.data(),
                               flags);
        fill(strokePath, pen.brush());
    } else {
        // For cosmetic pens we need a bit of trickery... We to process xform the input points
        if (state()->matrix.type() >= QTransform::TxProject) {
            QPainterPath painterPath = state()->matrix.map(path.convertToPainterPath());
            d->activeStroker->strokePath(painterPath, d->strokeHandler, QTransform());
        } else {
            d->activeStroker->setCurveThresholdFromTransform(QTransform());
            d->activeStroker->begin(d->strokeHandler);
            if (types) {
                while (points < lastPoint) {
                    switch (*types) {
                    case QPainterPath::MoveToElement: {
                        QPointF pt = (*(QPointF *) points) * state()->matrix;
                        d->activeStroker->moveTo(pt.x(), pt.y());
                        points += 2;
                        ++types;
                        break;
                    }
                    case QPainterPath::LineToElement: {
                        QPointF pt = (*(QPointF *) points) * state()->matrix;
                        d->activeStroker->lineTo(pt.x(), pt.y());
                        points += 2;
                        ++types;
                        break;
                    }
                    case QPainterPath::CurveToElement: {
                        QPointF c1 = ((QPointF *) points)[0] * state()->matrix;
                        QPointF c2 = ((QPointF *) points)[1] * state()->matrix;
                        QPointF e =  ((QPointF *) points)[2] * state()->matrix;
                        d->activeStroker->cubicTo(c1.x(), c1.y(), c2.x(), c2.y(), e.x(), e.y());
                        points += 6;
                        types += 3;
                        flags |= QVectorPath::CurvedShapeMask;
                        break;
                    }
                    default:
                        break;
                    }
                }
                if (path.hasImplicitClose()) {
                    QPointF pt = * ((QPointF *) path.points()) * state()->matrix;
                    d->activeStroker->lineTo(pt.x(), pt.y());
                }

            } else {
                QPointF p = ((QPointF *)points)[0] * state()->matrix;
                d->activeStroker->moveTo(p.x(), p.y());
                points += 2;
                while (points < lastPoint) {
                    QPointF p = ((QPointF *)points)[0] * state()->matrix;
                    d->activeStroker->lineTo(p.x(), p.y());
                    points += 2;
                }
                if (path.hasImplicitClose())
                    d->activeStroker->lineTo(p.x(), p.y());
            }
            d->activeStroker->end();
        }

        QVectorPath strokePath(d->strokeHandler->pts.data(),
                               d->strokeHandler->types.size(),
                               d->strokeHandler->types.data(),
                               flags);

        QTransform xform = state()->matrix;
        state()->matrix = QTransform();
        transformChanged();

        QBrush brush = pen.brush();
        if (qbrush_style(brush) != Qt::SolidPattern)
            brush.setTransform(brush.transform() * xform);

        fill(strokePath, brush);

        state()->matrix = xform;
        transformChanged();
    }
}