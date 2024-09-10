//-----------------------------------------------------------------------------
bool CollisionPredicates::_collides_triangle_point_3d(const Point& p0,
                                                      const Point& p1,
                                                      const Point& p2,
                                                      const Point& point)
{
  if (p0 == point or p1 == point or p2 == point)
    return true;

  const double tet_det = orient3d(p0, p1, p2, point);

  if (tet_det < 0.0 or tet_det > 0.0)
    return false;

  // Use normal
  const Point n = GeometryTools::cross_product(p0, p1, p2);

  return !(n.dot(GeometryTools::cross_product(point, p0, p1)) < 0.0 or
	   n.dot(GeometryTools::cross_product(point, p2, p0)) < 0.0 or
	   n.dot(GeometryTools::cross_product(point, p1, p2)) < 0.0);
}