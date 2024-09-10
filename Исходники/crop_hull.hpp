template<typename PointT> bool
pcl::CropHull<PointT>::rayTriangleIntersect (const PointT& point,
                                             const Eigen::Vector3f& ray,
                                             const Vertices& verts,
                                             const PointCloud& cloud)
{
  // Algorithm here is adapted from:
  // http://softsurfer.com/Archive/algorithm_0105/algorithm_0105.htm#intersect_RayTriangle()
  //
  // Original copyright notice:
  // Copyright 2001, softSurfer (www.softsurfer.com)
  // This code may be freely used and modified for any purpose
  // providing that this copyright notice is included with it.
  //
  assert (verts.vertices.size () == 3);

  const Eigen::Vector3f p = point.getVector3fMap ();
  const Eigen::Vector3f a = cloud[verts.vertices[0]].getVector3fMap ();
  const Eigen::Vector3f b = cloud[verts.vertices[1]].getVector3fMap ();
  const Eigen::Vector3f c = cloud[verts.vertices[2]].getVector3fMap ();
  const Eigen::Vector3f u = b - a;
  const Eigen::Vector3f v = c - a;
  const Eigen::Vector3f n = u.cross (v);
  const float n_dot_ray = n.dot (ray);

  if (std::fabs (n_dot_ray) < 1e-9)
    return (false);

  const float r = n.dot (a - p) / n_dot_ray;

  if (r < 0)
    return (false);

  const Eigen::Vector3f w = p + r * ray - a;
  const float denominator = u.dot (v) * u.dot (v) - u.dot (u) * v.dot (v);
  const float s_numerator = u.dot (v) * w.dot (v) - v.dot (v) * w.dot (u);
  const float s = s_numerator / denominator;
  if (s < 0 || s > 1)
    return (false);

  const float t_numerator = u.dot (v) * w.dot (u) - u.dot (u) * w.dot (v);
  const float t = t_numerator / denominator;
  if (t < 0 || s+t > 1)
    return (false);
  
  return (true);
}