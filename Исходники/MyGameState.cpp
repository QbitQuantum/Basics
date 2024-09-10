bool TestIntersionPlane(const Plane& plane, const TVector& position, const TVector& direction, double& lambda, TVector& pNormal) {
    double DotProduct = direction.dot(plane.normal);
    double l2;

    // determine if ray parallel to plane
    if (DotProduct < ZERO  && DotProduct > -ZERO){
        return false;
    }

    l2 = plane.normal.dot(plane.position - position) / DotProduct;

    if (l2 < -ZERO) {
        return false;
    }

    pNormal = plane.normal;
    lambda = l2;

    return true;
}