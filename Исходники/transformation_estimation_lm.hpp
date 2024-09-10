template <typename PointSource, typename PointTarget, typename MatScalar> void
pcl::registration::TransformationEstimationLM<PointSource, PointTarget, MatScalar>::estimateRigidTransformation (
    const pcl::PointCloud<PointSource> &cloud_src,
    const pcl::PointCloud<PointTarget> &cloud_tgt,
    Matrix4 &transformation_matrix) const
{

  // <cloud_src,cloud_src> is the source dataset
  if (cloud_src.points.size () != cloud_tgt.points.size ())
  {
    PCL_ERROR ("[pcl::registration::TransformationEstimationLM::estimateRigidTransformation] ");
    PCL_ERROR ("Number or points in source (%lu) differs than target (%lu)!\n", 
               cloud_src.points.size (), cloud_tgt.points.size ());
    return;
  }
  if (cloud_src.points.size () < 4)     // need at least 4 samples
  {
    PCL_ERROR ("[pcl::registration::TransformationEstimationLM::estimateRigidTransformation] ");
    PCL_ERROR ("Need at least 4 points to estimate a transform! Source and target have %lu points!\n", 
               cloud_src.points.size ());
    return;
  }

  int n_unknowns = warp_point_->getDimension ();
  VectorX x (n_unknowns);
  x.setZero ();
  
  // Set temporary pointers
  tmp_src_ = &cloud_src;
  tmp_tgt_ = &cloud_tgt;

  OptimizationFunctor functor (static_cast<int> (cloud_src.points.size ()), this);
  Eigen::NumericalDiff<OptimizationFunctor> num_diff (functor);
  //Eigen::LevenbergMarquardt<Eigen::NumericalDiff<OptimizationFunctor>, double> lm (num_diff);
  Eigen::LevenbergMarquardt<Eigen::NumericalDiff<OptimizationFunctor>, MatScalar> lm (num_diff);
  int info = lm.minimize (x);

  // Compute the norm of the residuals
  PCL_DEBUG ("[pcl::registration::TransformationEstimationLM::estimateRigidTransformation]");
  PCL_DEBUG ("LM solver finished with exit code %i, having a residual norm of %g. \n", info, lm.fvec.norm ());
  PCL_DEBUG ("Final solution: [%f", x[0]);
  for (int i = 1; i < n_unknowns; ++i) 
    PCL_DEBUG (" %f", x[i]);
  PCL_DEBUG ("]\n");

  // Return the correct transformation
  warp_point_->setParam (x);
  transformation_matrix = warp_point_->getTransform ();

  tmp_src_ = NULL;
  tmp_tgt_ = NULL;
}