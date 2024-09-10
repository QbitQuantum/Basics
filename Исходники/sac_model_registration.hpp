template <typename PointT> void
pcl::SampleConsensusModelRegistration<PointT>::estimateRigidTransformationSVD (
    const pcl::PointCloud<PointT> &cloud_src, 
    const std::vector<int> &indices_src, 
    const pcl::PointCloud<PointT> &cloud_tgt,
    const std::vector<int> &indices_tgt, 
    Eigen::VectorXf &transform)
{
  transform.resize (16);
  Eigen::Vector4f centroid_src, centroid_tgt;
  // Estimate the centroids of source, target
  compute3DCentroid (cloud_src, indices_src, centroid_src);
  compute3DCentroid (cloud_tgt, indices_tgt, centroid_tgt);

  // Subtract the centroids from source, target
  Eigen::MatrixXf cloud_src_demean;
  demeanPointCloud (cloud_src, indices_src, centroid_src, cloud_src_demean);

  Eigen::MatrixXf cloud_tgt_demean;
  demeanPointCloud (cloud_tgt, indices_tgt, centroid_tgt, cloud_tgt_demean);

  // Assemble the correlation matrix H = source * target'
  Eigen::Matrix3f H = (cloud_src_demean * cloud_tgt_demean.transpose ()).topLeftCorner<3, 3>();

  // Compute the Singular Value Decomposition
  Eigen::JacobiSVD<Eigen::Matrix3f> svd (H, Eigen::ComputeFullU | Eigen::ComputeFullV);
  Eigen::Matrix3f u = svd.matrixU ();
  Eigen::Matrix3f v = svd.matrixV ();

  // Compute R = V * U'
  if (u.determinant () * v.determinant () < 0)
  {
    for (int x = 0; x < 3; ++x)
      v (x, 2) *= -1;
  }

  Eigen::Matrix3f R = v * u.transpose ();

  // Return the correct transformation
  transform.segment<3> (0) = R.row (0); transform[12]  = 0;
  transform.segment<3> (4) = R.row (1); transform[13]  = 0;
  transform.segment<3> (8) = R.row (2); transform[14] = 0;

  Eigen::Vector3f t = centroid_tgt.head<3> () - R * centroid_src.head<3> ();
  transform[3] = t[0]; transform[7] = t[1]; transform[11] = t[2]; transform[15] = 1.0;
}