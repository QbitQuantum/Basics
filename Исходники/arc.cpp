void Arc::setProperties() {
    // arc properties
    Point vs = (p1 - c).xyPerp();
    Point ve = (p2 - c).xyPerp();
    radius = vs.xyNorm();
    vs.normalize();
    ve.normalize();
    length = fabs(xyIncludedAngle(vs, ve, dir)) * radius;
}