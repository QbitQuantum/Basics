//line triangle intersections
Eigen::Vector3d Triangle::shortestDistanceTo(Eigen::Vector3d line_segment_start, Eigen::Vector3d line_segment_end, Eigen::Vector3d& mesh_closest_point)
{
  Eigen::Vector3d shortest_dist(BIG_DOUBLE,BIG_DOUBLE,BIG_DOUBLE);

  //line intersection with all of the edges
  Eigen::Vector3d normal = ((points[1]-points[0]).cross(points[2]-points[1])).normalized();
  float d = points[1].dot(normal);
  Eigen::Vector3d p = line_segment_start - (line_segment_start.dot(normal) -d)*normal;
  Eigen::Vector3d r = (line_segment_end - (line_segment_end.dot(normal)-d)*normal) - p;

  for (int i = 0; i < 3; ++i)
  {
    Eigen::Vector3d q = points[i];
    Eigen::Vector3d s = points[(i+1)%3] - q;

    double u = ((q-p).cross(r)).norm()/(r.cross(s)).norm();
    double t = ((q-p).cross(s)).norm()/(r.cross(s)).norm();

    if (u > -EPISILON && u < 1+ EPISILON && t > -EPISILON && t < 1+EPISILON)
    {
      Eigen::Vector3d closest_point = q + u*s;
      Eigen::Vector3d mesh_close_point = (line_segment_start*(1-t) + line_segment_end*t);
      Eigen::Vector3d short_distance = mesh_close_point - closest_point;

      if (short_distance.norm() < shortest_dist.norm())
      {
        shortest_dist = short_distance;
        mesh_closest_point = mesh_close_point;
      }
    }

  }
  return shortest_dist;
}