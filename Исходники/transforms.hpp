template <typename PointT, typename Scalar> double
pcl::getPrincipalTransformation (const pcl::PointCloud<PointT> &cloud, 
                                 Eigen::Transform<Scalar, 3, Eigen::Affine> &transform)
{
  EIGEN_ALIGN16 Eigen::Matrix<Scalar, 3, 3> covariance_matrix;
  Eigen::Matrix<Scalar, 4, 1> centroid;
  
  pcl::computeMeanAndCovarianceMatrix (cloud, covariance_matrix, centroid);

  EIGEN_ALIGN16 Eigen::Matrix<Scalar, 3, 3> eigen_vects;
  Eigen::Matrix<Scalar, 3, 1> eigen_vals;
  pcl::eigen33 (covariance_matrix, eigen_vects, eigen_vals);

  double rel1 = eigen_vals.coeff (0) / eigen_vals.coeff (1);
  double rel2 = eigen_vals.coeff (1) / eigen_vals.coeff (2);
  
  transform.translation () = centroid.head (3);
  transform.linear () = eigen_vects;
  
  return (std::min (rel1, rel2));
}