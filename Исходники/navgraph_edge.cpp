/** Get the point on edge closest to a given point.
 * The method determines a line perpendicular to the edge which goes through
 * the given point, i.e. the point must be within the imaginary line segment.
 * Then the point on the edge which crosses with that perpendicular line
 * is returned.
 * @param x X coordinate of point to get point on edge for
 * @param y Y coordinate of point to get point on edge for
 * @return coordinate of point on edge closest to given point
 * @throw Exception thrown if the point is out of the line segment and
 * no line perpendicular to the edge going through the given point can
 * be found.
 */
cart_coord_2d_t
NavGraphEdge::closest_point_on_edge(float x, float y) const
{
  const Eigen::Vector2f point(x, y);
  const Eigen::Vector2f origin(from_node_.x(), from_node_.y());
  const Eigen::Vector2f target(to_node_.x(), to_node_.y());
  const Eigen::Vector2f direction(target - origin);
  const Eigen::Vector2f direction_norm = direction.normalized();
  const Eigen::Vector2f diff = point - origin;
  const float t = direction.dot(diff) / direction.squaredNorm();

  if (t >= 0.0 && t <= 1.0) {
    // projection of the point onto the edge is within the line segment
    Eigen::Vector2f point_on_line = origin + direction_norm.dot(diff) * direction_norm;
    return cart_coord_2d_t(point_on_line[0], point_on_line[1]);
  }

  throw Exception("Point (%f,%f) is not on edge %s--%s", x, y,
		  from_.c_str(), to_.c_str());
}