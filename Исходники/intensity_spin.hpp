template <typename PointInT, typename PointOutT> void
pcl::IntensitySpinEstimation<PointInT, PointOutT>::computeIntensitySpinImage (
      const PointCloudIn &cloud, float radius, float sigma, 
      int k,
      const std::vector<int> &indices, 
      const std::vector<float> &squared_distances, 
      Eigen::MatrixXf &intensity_spin_image)
{
  // Determine the number of bins to use based on the size of intensity_spin_image
  int nr_distance_bins = static_cast<int> (intensity_spin_image.cols ());
  int nr_intensity_bins = static_cast<int> (intensity_spin_image.rows ());

  // Find the min and max intensity values in the given neighborhood
  float min_intensity = std::numeric_limits<float>::max ();
  float max_intensity = -std::numeric_limits<float>::max ();
  for (int idx = 0; idx < k; ++idx)
  {
    min_intensity = (std::min) (min_intensity, cloud.points[indices[idx]].intensity);
    max_intensity = (std::max) (max_intensity, cloud.points[indices[idx]].intensity);
  }

  float constant = 1.0f / (2.0f * sigma_ * sigma_);
  // Compute the intensity spin image
  intensity_spin_image.setZero ();
  for (int idx = 0; idx < k; ++idx)
  {
    // Normalize distance and intensity values to: 0.0 <= d,i < nr_distance_bins,nr_intensity_bins
    const float eps = std::numeric_limits<float>::epsilon ();
    float d = static_cast<float> (nr_distance_bins) * std::sqrt (squared_distances[idx]) / (radius + eps);
    float i = static_cast<float> (nr_intensity_bins) * 
              (cloud.points[indices[idx]].intensity - min_intensity) / (max_intensity - min_intensity + eps);

    if (sigma == 0)
    {
      // If sigma is zero, update the histogram with no smoothing kernel
      int d_idx = static_cast<int> (d);
      int i_idx = static_cast<int> (i);
      intensity_spin_image (i_idx, d_idx) += 1;
    }
    else
    {
      // Compute the bin indices that need to be updated (+/- 3 standard deviations)
      int d_idx_min = (std::max)(static_cast<int> (floor (d - 3*sigma)), 0);
      int d_idx_max = (std::min)(static_cast<int> (ceil  (d + 3*sigma)), nr_distance_bins - 1);
      int i_idx_min = (std::max)(static_cast<int> (floor (i - 3*sigma)), 0);
      int i_idx_max = (std::min)(static_cast<int> (ceil  (i + 3*sigma)), nr_intensity_bins - 1);
   
      // Update the appropriate bins of the histogram 
      for (int i_idx = i_idx_min; i_idx <= i_idx_max; ++i_idx)  
      {
        for (int d_idx = d_idx_min; d_idx <= d_idx_max; ++d_idx)
        {
          // Compute a "soft" update weight based on the distance between the point and the bin
          float w = expf (-powf (d - static_cast<float> (d_idx), 2.0f) * constant - powf (i - static_cast<float> (i_idx), 2.0f) * constant);
          intensity_spin_image (i_idx, d_idx) += w;
        }
      }
    }
  }
}