TEST (PCL, GeneralizedIterativeClosestPoint)
{
  typedef PointXYZ PointT;
  PointCloud<PointT>::Ptr src (new PointCloud<PointT>);
  copyPointCloud (cloud_source, *src);
  PointCloud<PointT>::Ptr tgt (new PointCloud<PointT>);
  copyPointCloud (cloud_target, *tgt);
  PointCloud<PointT> output;

  GeneralizedIterativeClosestPoint<PointT, PointT> reg;
  reg.setInputSource (src);
  reg.setInputTarget (tgt);
  reg.setMaximumIterations (50);
  reg.setTransformationEpsilon (1e-8);

  // Register
  reg.align (output);
  EXPECT_EQ (int (output.points.size ()), int (cloud_source.points.size ()));
  EXPECT_LT (reg.getFitnessScore (), 0.0001);

  // Check again, for all possible caching schemes
  for (int iter = 0; iter < 4; iter++)
  {
    bool force_cache = (bool) iter/2;
    bool force_cache_reciprocal = (bool) iter%2;
    pcl::search::KdTree<PointT>::Ptr tree(new pcl::search::KdTree<PointT>);
    // Ensure that, when force_cache is not set, we are robust to the wrong input
    if (force_cache)
      tree->setInputCloud (tgt);
    reg.setSearchMethodTarget (tree, force_cache);

    pcl::search::KdTree<PointT>::Ptr tree_recip (new pcl::search::KdTree<PointT>);
    if (force_cache_reciprocal)
      tree_recip->setInputCloud (src);
    reg.setSearchMethodSource (tree_recip, force_cache_reciprocal);

    // Register
    reg.align (output);
    EXPECT_EQ (int (output.points.size ()), int (cloud_source.points.size ()));
    EXPECT_LT (reg.getFitnessScore (), 0.001);
  }

  // Test guess matrix
  Eigen::Isometry3f transform = Eigen::Isometry3f (Eigen::AngleAxisf (0.25 * M_PI, Eigen::Vector3f::UnitX ())
                                                 * Eigen::AngleAxisf (0.50 * M_PI, Eigen::Vector3f::UnitY ())
                                                 * Eigen::AngleAxisf (0.33 * M_PI, Eigen::Vector3f::UnitZ ()));
  transform.translation () = Eigen::Vector3f (0.1, 0.2, 0.3);
  PointCloud<PointT>::Ptr transformed_tgt (new PointCloud<PointT>);
  pcl::transformPointCloud (*tgt, *transformed_tgt, transform.matrix ()); // transformed_tgt is now a copy of tgt with a transformation matrix applied

  GeneralizedIterativeClosestPoint<PointT, PointT> reg_guess;
  reg_guess.setInputSource (src);
  reg_guess.setInputTarget (transformed_tgt);
  reg_guess.setMaximumIterations (50);
  reg_guess.setTransformationEpsilon (1e-8);
  reg_guess.align (output, transform.matrix ());
  EXPECT_EQ (int (output.points.size ()), int (cloud_source.points.size ()));
  EXPECT_LT (reg.getFitnessScore (), 0.0001);
}