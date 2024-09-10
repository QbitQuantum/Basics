Position
GeomHelper::crossPoint(const Boundary& b, const PositionVector& v) {
    if (v.intersects(Position(b.xmin(), b.ymin()), Position(b.xmin(), b.ymax()))) {
        return v.intersectsAtPoint(
                   Position(b.xmin(), b.ymin()),
                   Position(b.xmin(), b.ymax()));
    }
    if (v.intersects(Position(b.xmax(), b.ymin()), Position(b.xmax(), b.ymax()))) {
        return v.intersectsAtPoint(
                   Position(b.xmax(), b.ymin()),
                   Position(b.xmax(), b.ymax()));
    }
    if (v.intersects(Position(b.xmin(), b.ymin()), Position(b.xmax(), b.ymin()))) {
        return v.intersectsAtPoint(
                   Position(b.xmin(), b.ymin()),
                   Position(b.xmax(), b.ymin()));
    }
    if (v.intersects(Position(b.xmin(), b.ymax()), Position(b.xmax(), b.ymax()))) {
        return v.intersectsAtPoint(
                   Position(b.xmin(), b.ymax()),
                   Position(b.xmax(), b.ymax()));
    }
    throw 1;
}