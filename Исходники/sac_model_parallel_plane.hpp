template <typename PointT> bool
pcl::SampleConsensusModelParallelPlane<PointT>::isModelValid (const Eigen::VectorXf &model_coefficients)
{
  // Needs a valid model coefficients
  if (model_coefficients.size () != 4)
  {
    PCL_ERROR ("[pcl::SampleConsensusModelParallelPlane::isModelValid] Invalid number of model coefficients given (%lu)!\n", (unsigned long)model_coefficients.size ());
    return (false);
  }

  // Check against template, if given
  if (eps_angle_ > 0.0)
  {
    // Obtain the plane normal
    Eigen::Vector4f coeff = model_coefficients;
    coeff[3] = 0;
    coeff.normalize ();

    Eigen::Vector4f axis (axis_[0], axis_[1], axis_[2], 0);
    if (fabs (axis.dot (coeff)) < cos_angle_)
      return  (false);
  }

  return (true);
}