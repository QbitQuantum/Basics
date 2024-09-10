template <typename PointInT, typename PointNT, typename PointOutT> bool
pcl::FPFHEstimation<PointInT, PointNT, PointOutT>::computePairFeatures (
      const pcl::PointCloud<PointInT> &cloud, const pcl::PointCloud<PointNT> &normals,
      int p_idx, int q_idx, float &f1, float &f2, float &f3, float &f4)
{
  // Compute the Cartesian difference between the two points
  Eigen::Vector4f delta = cloud.points[q_idx].getVector4fMap () - cloud.points[p_idx].getVector4fMap ();
  delta[3] = 0;

  // Compute the Euclidean norm = || p_idx - q_idx ||
  float distance_sqr = delta.squaredNorm ();

  if (distance_sqr == 0)
  {
    ROS_ERROR ("Euclidean distance between points %d and %d is 0!", p_idx, q_idx);
    f1 = f2 = f3 = f4 = 0;
    return (false);
  }

  // Estimate f4 = || delta ||
  f4 = sqrt (distance_sqr);

  // Create a Darboux frame coordinate system u-v-w
  // u = n1; v = (p_idx - q_idx) x u / || (p_idx - q_idx) x u ||; w = u x v
  pcl::Vector4fMapConst u = normals.points[p_idx].getNormalVector4fMap ();

  // Estimate f3 = u * delta / || delta ||
  // delta[3] = 0 (line 59)
  f3 = u.dot (delta) / f4;

  // v = delta * u
  Eigen::Vector4f v = Eigen::Vector4f::Zero ();
  v = delta.cross3 (u);

  distance_sqr = v.squaredNorm ();
  if (distance_sqr == 0)
  {
    ROS_ERROR ("Norm of Delta x U is 0 for point %d and %d!", p_idx, q_idx);
    f1 = f2 = f3 = f4 = 0;
    return (false);
  }

  // Copy the q_idx normal
  Eigen::Vector4f nq (normals.points[q_idx].normal_x,
                      normals.points[q_idx].normal_y,
                      normals.points[q_idx].normal_z,
                      0);

  // Normalize the vector
  v /= sqrt (distance_sqr);

  // Compute delta (w) = u x v
  delta = u.cross3 (v);

  // Compute f2 = v * n2;
  // v[3] = 0 (line 82)
  f2 = v.dot (nq);

  // Compute f1 = arctan (w * n2, u * n2) i.e. angle of n2 in the x=u, y=w coordinate system
  // delta[3] = 0 (line 59), nq[3] = 0 (line 97)
  f1 = atan2f (delta.dot (nq), u.dot (nq));       // @todo: optimize this

  return (true);
}