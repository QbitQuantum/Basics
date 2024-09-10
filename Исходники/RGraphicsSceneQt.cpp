void RGraphicsSceneQt::exportPolylineFill(const RPolyline& polyline) {
    if (currentBrush!=Qt::NoBrush) {
        bool created = beginPath();

        // TODO: support arc segments for filling:
        QPolygonF qpolygon;
        QList<RVector> points = polyline.getVertices();
        for (int i = 0; i < points.size(); ++i) {
            RVector v = points.at(i);
            qpolygon << QPointF(v.x, v.y);
        }
        currentPainterPath.setBrush(currentBrush);
        currentPainterPath.addPolygon(qpolygon);

        if (created) {
            endPath();
        }
    }
}