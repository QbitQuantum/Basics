bool
pcl::lineWithLineIntersection (const Eigen::VectorXf &line_a, 
                               const Eigen::VectorXf &line_b, 
                               Eigen::Vector4f &point, double sqr_eps)
{
  Eigen::Vector4f p1, p2;
  lineToLineSegment (line_a, line_b, p1, p2);

  // If the segment size is smaller than a pre-given epsilon...
  double sqr_dist = (p1 - p2).squaredNorm ();
  if (sqr_dist < sqr_eps)
  {
    point = p1;
    return (true);
  }
  point.setZero ();
  return (false);
}