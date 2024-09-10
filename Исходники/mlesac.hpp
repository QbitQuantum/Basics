template <typename PointT> void
pcl::MaximumLikelihoodSampleConsensus<PointT>::getMinMax (
    const PointCloudConstPtr &cloud, 
    const boost::shared_ptr <std::vector<int> > &indices, 
    Eigen::Vector4f &min_p, 
    Eigen::Vector4f &max_p)
{
  min_p.setConstant (FLT_MAX);
  max_p.setConstant (-FLT_MAX);
  min_p[3] = max_p[3] = 0;

  for (size_t i = 0; i < indices->size (); ++i)
  {
    if (cloud->points[(*indices)[i]].x < min_p[0]) min_p[0] = cloud->points[(*indices)[i]].x;
    if (cloud->points[(*indices)[i]].y < min_p[1]) min_p[1] = cloud->points[(*indices)[i]].y;
    if (cloud->points[(*indices)[i]].z < min_p[2]) min_p[2] = cloud->points[(*indices)[i]].z;

    if (cloud->points[(*indices)[i]].x > max_p[0]) max_p[0] = cloud->points[(*indices)[i]].x;
    if (cloud->points[(*indices)[i]].y > max_p[1]) max_p[1] = cloud->points[(*indices)[i]].y;
    if (cloud->points[(*indices)[i]].z > max_p[2]) max_p[2] = cloud->points[(*indices)[i]].z;
  }
}