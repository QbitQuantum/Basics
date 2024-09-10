bool Polygon::isPointWithinPolygonForEdge(
                                          const Point3D& p,
                                          const Point3D& p1,
                                          const Point3D& p2)
{
    Vector3D v = p1 - p2;
    Vector3D edgeNormal = v.cross(m_plane.m_plane_normal);
    
    return edgeNormal.dot(p - p1) < SMALL_EPSILON;
}