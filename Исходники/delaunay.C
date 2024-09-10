bool Delaunay :: isInsideCC(const FloatArray &iP, const FloatArray &iP1, const FloatArray &iP2, const FloatArray &iP3) const
{
    Triangle tr(iP1, iP2, iP3);
    double r = tr.getRadiusOfCircumCircle();
    FloatArray circumCenter;
    tr.computeCenterOfCircumCircle(circumCenter);
    double distance = circumCenter.distance(iP);
    if ( distance < r ) {
        return true;
    } else {
        return false;
    }
}