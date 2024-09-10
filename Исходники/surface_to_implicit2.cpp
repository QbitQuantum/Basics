double SurfaceToImplicit2::signedDistanceLocal(
    const Vector2D& otherPoint) const {
    Vector2D x = _surface->closestPoint(otherPoint);
    Vector2D n = _surface->closestNormal(otherPoint);
    n = (isNormalFlipped) ? -n : n;
    if (n.dot(otherPoint - x) < 0.0) {
        return -x.distanceTo(otherPoint);
    } else {
        return x.distanceTo(otherPoint);
    }
}