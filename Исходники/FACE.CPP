double Face::distance(const Eigen::Vector3d& origin, const Eigen::Vector3d& direction) const
{
    // check for false intersection with the outside of the mesh
    if (!sameDirection(direction, normal().normalized())) {
        return INFINITY;
    }

    // Möller–Trumbore intersection algorithm
    const Eigen::Vector3d& p1(he->vertex->position);
    const Eigen::Vector3d& p2(he->next->vertex->position);
    const Eigen::Vector3d& p3(he->next->next->vertex->position);
    
    Eigen::Vector3d e1 = p2 - p1;
    Eigen::Vector3d e2 = p3 - p1;
    Eigen::Vector3d n = direction.cross(e2);
    
    double det = e1.dot(n);
    // ray does not lie in the plane
    if (det > -EPSILON && det < EPSILON) {
        return INFINITY;
    }
    
    double invDet = 1.0 / det;
    Eigen::Vector3d t = origin - p1;
    double u = t.dot(n) * invDet;
    
    // ray lies outside triangle
    if (u < 0.0 || u > 1.0) {
        return INFINITY;
    }
    
    Eigen::Vector3d q = t.cross(e1);
    double v = direction.dot(q) * invDet;
    // ray lies outside the triangle
    if (v < 0.0 || v + u > 1.0) {
        return INFINITY;
    }
    
    double s = e2.dot(q) * invDet;
    // intersection
    if (s > EPSILON) {
        return s;
    }
    
    // no hit
    return INFINITY;
}