/** Get edge closest to a specified point.
 * The point must be within an imaginery line segment parallel to
 * the edge, that is a line perpendicular to the edge must go
 * through the point and a point on the edge line segment.
 * @param pos_x X coordinate in global (map) frame of point
 * @param pos_y X coordinate in global (map) frame of point
 * @return edge closest to the given point, or invalid edge if
 * such an edge does not exist.
 */
NavGraphEdge
NavGraph::closest_edge(float pos_x, float pos_y) const
{
  float min_dist = std::numeric_limits<float>::max();

  NavGraphEdge rv;

  Eigen::Vector2f point(pos_x, pos_y);
  for (const NavGraphEdge &edge : edges_) {
    const Eigen::Vector2f origin(edge.from_node().x(), edge.from_node().y());
    const Eigen::Vector2f target(edge.to_node().x(), edge.to_node().y());
    const Eigen::Vector2f direction(target - origin);
    const Eigen::Vector2f direction_norm = direction.normalized();
    const Eigen::Vector2f diff = point - origin;
    const float t = direction.dot(diff) / direction.squaredNorm();

    if (t >= 0.0 && t <= 1.0) {
      // projection of the point onto the edge is within the line segment
      float distance = (diff - direction_norm.dot(diff) * direction_norm).norm();
      if (distance < min_dist) {
	min_dist = distance;
	rv = edge;
      }
    }
  }

  return rv;
}