bool BoundingPolyhedron::intersects (BoundingSphere &bs) {
    return bs.intersects (*this);
}