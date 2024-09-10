template <typename PointFeature> bool
pcl::PyramidFeatureHistogram<PointFeature>::initializeHistogram ()
{
  // a few consistency checks before starting the computations
  if (!PCLBase<PointFeature>::initCompute ())
  {
    PCL_ERROR ("[pcl::PyramidFeatureHistogram::initializeHistogram] PCLBase initCompute failed\n");
    return false;
  }

  if (dimension_range_input_.size () == 0)
  {
    PCL_ERROR ("[pcl::PyramidFeatureHistogram::initializeHistogram] Input dimension range was not set\n");
    return false;
  }

  if (dimension_range_target_.size () == 0)
  {
    PCL_ERROR ("[pcl::PyramidFeatureHistogram::initializeHistogram] Target dimension range was not set\n");
    return false;
  }

  if (dimension_range_input_.size () != dimension_range_target_.size ())
  {
    PCL_ERROR ("[pcl::PyramidFeatureHistogram::initializeHistogram] Input and target dimension ranges do not agree in size: %u vs %u\n",
               dimension_range_input_.size (), dimension_range_target_.size ());
    return false;
  }


  nr_dimensions = dimension_range_target_.size ();
  nr_features = input_->points.size ();
  float D = 0.0f;
  for (std::vector<std::pair<float, float> >::iterator range_it = dimension_range_target_.begin (); range_it != dimension_range_target_.end (); ++range_it)
  {
    float aux = range_it->first - range_it->second;
    D += aux * aux;
  }
  D = sqrtf (D);
  nr_levels = static_cast<size_t> (ceilf (log2f (D)));
  PCL_DEBUG ("[pcl::PyramidFeatureHistogram::initializeHistogram] Pyramid will have %u levels with a hyper-parallelepiped diagonal size of %f\n", nr_levels, D);


  hist_levels.resize (nr_levels);
  for (size_t level_i = 0; level_i < nr_levels; ++level_i)
  {
    std::vector<size_t> bins_per_dimension (nr_dimensions);
    std::vector<float> bin_step (nr_dimensions);
    for (size_t dim_i = 0; dim_i < nr_dimensions; ++dim_i) 
    {
      bins_per_dimension[dim_i] = 
        static_cast<size_t> (ceilf ((dimension_range_target_[dim_i].second - dimension_range_target_[dim_i].first) / (powf (2.0f, static_cast<float> (level_i)) * sqrtf (static_cast<float> (nr_dimensions)))));
      bin_step[dim_i] = powf (2.0f, static_cast<float> (level_i)) * sqrtf (static_cast<float> (nr_dimensions));
    }
    hist_levels[level_i] = PyramidFeatureHistogramLevel (bins_per_dimension, bin_step);

    PCL_DEBUG ("[pcl::PyramidFeatureHistogram::initializeHistogram] Created vector of size %u at level %u\nwith #bins per dimension:", hist_levels.back ().hist.size (), level_i);
    for (size_t dim_i = 0; dim_i < nr_dimensions; ++dim_i)
      PCL_DEBUG ("%u ", bins_per_dimension[dim_i]);
    PCL_DEBUG ("\n");
  }

  return true;
}