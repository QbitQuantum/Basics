static QLineF preciselyMap( const QTransform& transform, const QLineF& line )
{
    qreal fx1 = line.x1();
    qreal fy1 = line.y1();
    qreal fx2 = line.x2();
    qreal fy2 = line.y2();

    qreal x1 = transform.m11() * fx1 + transform.m21() * fy1 + transform.dx();
    qreal y1 = transform.m12() * fx1 + transform.m22() * fy1 + transform.dy();
    qreal x2 = transform.m11() * fx2 + transform.m21() * fy2 + transform.dx();
    qreal y2 = transform.m12() * fx2 + transform.m22() * fy2 + transform.dy();

    return QLineF( x1, y1, x2, y2 );
}