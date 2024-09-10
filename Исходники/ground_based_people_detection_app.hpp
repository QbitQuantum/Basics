template <typename PointT> void
pcl::people::GroundBasedPeopleDetectionApp<PointT>::applyTransformationGround ()
{
  if (transformation_set_ && ground_coeffs_set_)
  {
    Eigen::Transform<float, 3, Eigen::Affine> transform;
    transform = transformation_;
    ground_coeffs_transformed_ = transform.matrix() * ground_coeffs_;
  }
  else
  {
    ground_coeffs_transformed_ = ground_coeffs_;
  }
}