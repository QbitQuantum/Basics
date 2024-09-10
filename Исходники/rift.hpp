template <typename PointInT, typename GradientT, typename PointOutT> void
pcl::RIFTEstimation<PointInT, GradientT, PointOutT>::computeRIFT (
      const PointCloudIn &cloud, const PointCloudGradient &gradient, 
      int p_idx, float radius, const std::vector<int> &indices, 
      const std::vector<float> &sqr_distances, Eigen::MatrixXf &rift_descriptor)
{
  if (indices.empty ())
  {
    PCL_ERROR ("[pcl::RIFTEstimation] Null indices points passed!\n");
    return;
  }

  // Determine the number of bins to use based on the size of rift_descriptor
  int nr_distance_bins = static_cast<int> (rift_descriptor.rows ());
  int nr_gradient_bins = static_cast<int> (rift_descriptor.cols ());

  // Get the center point
  pcl::Vector3fMapConst p0 = cloud.points[p_idx].getVector3fMap ();

  // Compute the RIFT descriptor
  rift_descriptor.setZero ();
  for (size_t idx = 0; idx < indices.size (); ++idx)
  {
    // Compute the gradient magnitude and orientation (relative to the center point)
    pcl::Vector3fMapConst point = cloud.points[indices[idx]].getVector3fMap ();
    Eigen::Map<const Eigen::Vector3f> gradient_vector (& (gradient.points[indices[idx]].gradient[0]));

    float gradient_magnitude = gradient_vector.norm ();
    float gradient_angle_from_center = acosf (gradient_vector.dot ((point - p0).normalized ()) / gradient_magnitude);
    if (!pcl_isfinite (gradient_angle_from_center))
      gradient_angle_from_center = 0.0;

    // Normalize distance and angle values to: 0.0 <= d,g < nr_distances_bins,nr_gradient_bins
    const float eps = std::numeric_limits<float>::epsilon ();
    float d = static_cast<float> (nr_distance_bins) * sqrtf (sqr_distances[idx]) / (radius + eps);
    float g = static_cast<float> (nr_gradient_bins) * gradient_angle_from_center / (static_cast<float> (M_PI) + eps);

    // Compute the bin indices that need to be updated
    int d_idx_min = (std::max)(static_cast<int> (ceil (d - 1)), 0);
    int d_idx_max = (std::min)(static_cast<int> (floor (d + 1)), nr_distance_bins - 1);
    int g_idx_min = static_cast<int> (ceil (g - 1));
    int g_idx_max = static_cast<int> (floor (g + 1));

    // Update the appropriate bins of the histogram 
    for (int g_idx = g_idx_min; g_idx <= g_idx_max; ++g_idx)  
    {
      // Because gradient orientation is cyclical, out-of-bounds values must wrap around
      int g_idx_wrapped = ((g_idx + nr_gradient_bins) % nr_gradient_bins); 

      for (int d_idx = d_idx_min; d_idx <= d_idx_max; ++d_idx)
      {
        // To avoid boundary effects, use linear interpolation when updating each bin 
        float w = (1.0f - fabsf (d - static_cast<float> (d_idx))) * (1.0f - fabsf (g - static_cast<float> (g_idx)));

        rift_descriptor (d_idx, g_idx_wrapped) += w * gradient_magnitude;
      }
    }
  }

  // Normalize the RIFT descriptor to unit magnitude
  rift_descriptor.normalize ();
}