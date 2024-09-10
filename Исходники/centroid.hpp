template <typename PointT> inline unsigned int
pcl::compute3DCentroid (const pcl::PointCloud<PointT> &cloud, Eigen::Vector4f &centroid)
{
  if (cloud.points.empty ())
    return (0);

  // Initialize to 0
  centroid.setZero ();
  // For each point in the cloud
  // If the data is dense, we don't need to check for NaN
  if (cloud.is_dense)
  {
    for (size_t i = 0; i < cloud.points.size (); ++i)
      centroid += cloud.points[i].getVector4fMap ();
    centroid[3] = 0;
    centroid /= static_cast<float> (cloud.points.size ());

    return (static_cast<unsigned int> (cloud.points.size ()));
  }
  // NaN or Inf values could exist => check for them
  else
  {
    unsigned cp = 0;
    for (size_t i = 0; i < cloud.points.size (); ++i)
    {
      // Check if the point is invalid
      if (!isFinite (cloud [i]))
        continue;

      centroid += cloud[i].getVector4fMap ();
      ++cp;
    }
    centroid[3] = 0;
    centroid /= static_cast<float> (cp);

    return (cp);
  }
}