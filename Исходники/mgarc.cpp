void MgArc::_output(MgPath& path) const
{
    float r = getRadius();
    float sweepAngle = getSweepAngle();
    Point2d points[16];
    
    if (r < _MGZERO || fabsf(sweepAngle) < _MGZERO)
        return;
    
    int count = mgcurv::arcToBezier(points, getCenter(), r, r,
                                    getStartAngle(), sweepAngle);
    
    if (_subtype > 0) {
        path.moveTo(getCenter());
        path.lineTo(points[0]);
        path.beziersTo(count - 1, points + 1);
        path.closeFigure();
    } else {
        path.moveTo(points[0]);
        path.beziersTo(count - 1, points + 1);
    }
}