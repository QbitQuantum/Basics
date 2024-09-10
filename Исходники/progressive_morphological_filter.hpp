template <typename PointT> void
pcl::ProgressiveMorphologicalFilter<PointT>::extract (std::vector<int>& ground)
{
  bool segmentation_is_possible = initCompute ();
  if (!segmentation_is_possible)
  {
    deinitCompute ();
    return;
  }

  // Compute the series of window sizes and height thresholds
  std::vector<float> height_thresholds;
  std::vector<float> window_sizes;
  int iteration = 0;
  float window_size = 0.0f;
  float height_threshold = 0.0f;

  while (window_size < max_window_size_)
  {
    // Determine the initial window size.
    if (exponential_)
      window_size = cell_size_ * (2.0f * std::pow (base_, iteration) + 1.0f);
    else
      window_size = cell_size_ * (2.0f * (iteration+1) * base_ + 1.0f);

    // Calculate the height threshold to be used in the next iteration.
    if (iteration == 0)
      height_threshold = initial_distance_;
    else
      height_threshold = slope_ * (window_size - window_sizes[iteration-1]) * cell_size_ + initial_distance_;

    // Enforce max distance on height threshold
    if (height_threshold > max_distance_)
      height_threshold = max_distance_;

    window_sizes.push_back (window_size);
    height_thresholds.push_back (height_threshold);

    iteration++;
  }

  // Ground indices are initially limited to those points in the input cloud we
  // wish to process
  ground = *indices_;

  // Progressively filter ground returns using morphological open
  for (int i = 0; i < window_sizes.size (); ++i)
  {
    PCL_DEBUG ("      Iteration %d (height threshold = %f, window size = %f)...",
               i, height_thresholds[i], window_sizes[i]);

    // Limit filtering to those points currently considered ground returns
    typename pcl::PointCloud<PointT>::Ptr cloud (new pcl::PointCloud<PointT>);
    pcl::copyPointCloud<PointT> (*input_, ground, *cloud);

    // Create new cloud to hold the filtered results. Apply the morphological
    // opening operation at the current window size.
    typename pcl::PointCloud<PointT>::Ptr cloud_f (new pcl::PointCloud<PointT>);
    pcl::applyMorphologicalOperator<PointT> (cloud, window_sizes[i], MORPH_OPEN, *cloud_f);

    // Find indices of the points whose difference between the source and
    // filtered point clouds is less than the current height threshold.
    std::vector<int> pt_indices;
    for (boost::int32_t p_idx = 0; p_idx < ground.size (); ++p_idx)
    {
      float diff = cloud->points[p_idx].z - cloud_f->points[p_idx].z;
      if (diff < height_thresholds[i])
        pt_indices.push_back (ground[p_idx]);
    }

    // Ground is now limited to pt_indices
    ground.swap (pt_indices);

    PCL_DEBUG ("ground now has %d points\n", ground.size ());
  }

  deinitCompute ();
}