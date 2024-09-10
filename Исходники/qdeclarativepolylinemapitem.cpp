/*!
    \internal
*/
void QGeoMapPolylineGeometry::updateScreenPoints(const QGeoMap &map,
                                                 qreal strokeWidth)
{
    if (!screenDirty_)
        return;

    QPointF origin = map.coordinateToScreenPosition(srcOrigin_, false).toPointF();

    if (!qIsFinite(origin.x()) || !qIsFinite(origin.y())) {
        clear();
        return;
    }

    // Create the viewport rect in the same coordinate system
    // as the actual points
    QRectF viewport(0, 0, map.width(), map.height());
    viewport.adjust(-strokeWidth, -strokeWidth, strokeWidth, strokeWidth);
    viewport.translate(-1 * origin);

    // Perform clipping to the viewport limits
    QVector<qreal> points;
    QVector<QPainterPath::ElementType> types;

    if (clipToViewport_) {
        clipPathToRect(srcPoints_, srcPointTypes_, viewport, points, types);
    } else {
        points = srcPoints_;
        types = srcPointTypes_;
    }

    QVectorPath vp(points.data(), types.size(), types.data());
    QTriangulatingStroker ts;
    ts.process(vp, QPen(QBrush(Qt::black), strokeWidth), viewport, QPainter::Qt4CompatiblePainting);

    clear();

    // Nothing is on the screen
    if (ts.vertexCount() == 0)
        return;

    // QTriangulatingStroker#vertexCount is actually the length of the array,
    // not the number of vertices
    screenVertices_.reserve(ts.vertexCount());

    screenOutline_ = QPainterPath();

    QPolygonF tri;
    const float *vs = ts.vertices();
    for (int i = 0; i < (ts.vertexCount()/2*2); i += 2) {
        screenVertices_ << QPointF(vs[i], vs[i + 1]);

        if (!qIsFinite(vs[i]) || !qIsFinite(vs[i + 1]))
            break;

        tri << QPointF(vs[i], vs[i + 1]);
        if (tri.size() == 4) {
            tri.remove(0);
            screenOutline_.addPolygon(tri);
        }
    }

    QRectF bb = screenOutline_.boundingRect();
    screenBounds_ = bb;
    this->translate( -1 * sourceBounds_.topLeft());
}