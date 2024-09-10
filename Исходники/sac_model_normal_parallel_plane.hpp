template <typename PointT, typename PointNT> int
pcl::SampleConsensusModelNormalParallelPlane<PointT, PointNT>::countWithinDistance (
      const Eigen::VectorXf &model_coefficients, const double threshold)
{
  if (!normals_)
  {
    PCL_ERROR ("[pcl::SampleConsensusModelNormalParallelPlane::countWithinDistance] No input dataset containing normals was given!\n");
    return (0);
  }

  // Check if the model is valid given the user constraints
  if (!isModelValid (model_coefficients))
    return (0);

  // Obtain the plane normal
  Eigen::Vector4f coeff = model_coefficients;
  coeff[3] = 0;

  int nr_p = 0;

  // Iterate through the 3d points and calculate the distances from them to the plane
  for (size_t i = 0; i < indices_->size (); ++i)
  {
    // Calculate the distance from the point to the plane normal as the dot product
    // D = (P-A).N/|N|
    Eigen::Vector4f p (input_->points[(*indices_)[i]].x, input_->points[(*indices_)[i]].y, input_->points[(*indices_)[i]].z, 0);
    Eigen::Vector4f n (normals_->points[(*indices_)[i]].normal[0], normals_->points[(*indices_)[i]].normal[1], normals_->points[(*indices_)[i]].normal[2], 0);
    double d_euclid = fabs (coeff.dot (p) + model_coefficients[3]);

    // Calculate the angular distance between the point normal and the plane normal
    double d_normal = fabs (getAngle3D (n, coeff));
    d_normal = (std::min) (d_normal, M_PI - d_normal);

    if (fabs (normal_distance_weight_ * d_normal + (1 - normal_distance_weight_) * d_euclid) < threshold)
      nr_p++;
  }
  return (nr_p);
}