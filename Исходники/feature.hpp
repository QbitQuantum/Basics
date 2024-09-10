template <typename PointT> inline void
pcl::compute3DCentroid (const pcl::PointCloud<PointT> &cloud, const std::vector<int> &indices,
                        Eigen::Vector4f &centroid)
{
  // Initialize to 0
  centroid.setZero ();
  if (indices.empty ()) 
    return;
  // For each point in the cloud
  int cp = 0;

  // If the data is dense, we don't need to check for NaN
  if (cloud.is_dense)
  {
    for (size_t i = 0; i < indices.size (); ++i)
      centroid += cloud.points[indices[i]].getVector4fMap ();
    centroid[3] = 0;
    centroid /= indices.size ();
  }
  // NaN or Inf values could exist => check for them
  else
  {
    for (size_t i = 0; i < indices.size (); ++i)
    {
      // Check if the point is invalid
      if (!pcl_isfinite (cloud.points[indices[i]].x) || 
          !pcl_isfinite (cloud.points[indices[i]].y) || 
          !pcl_isfinite (cloud.points[indices[i]].z))
        continue;

      centroid += cloud.points[indices[i]].getVector4fMap ();
      cp++;
    }
    centroid[3] = 0;
    centroid /= cp;
  }
}