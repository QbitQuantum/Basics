template <typename PointInT, typename PointNT, typename PointOutT> void
pcl::PFHEstimation<PointInT, PointNT, PointOutT>::computePointPFHSignature (
      const pcl::PointCloud<PointInT> &cloud, const pcl::PointCloud<PointNT> &normals,
      const std::vector<int> &indices, int nr_split, Eigen::VectorXf &pfh_histogram)
{
  int h_index, h_p;

  // Clear the resultant point histogram
  pfh_histogram.setZero ();

  // Factorization constant
  float hist_incr = 100.0f / static_cast<float> (indices.size () * (indices.size () - 1) / 2);

  std::pair<int, int> key;
  bool key_found = false;

  // Iterate over all the points in the neighborhood
  for (size_t i_idx = 0; i_idx < indices.size (); ++i_idx)
  {
    for (size_t j_idx = 0; j_idx < i_idx; ++j_idx)
    {
      // If the 3D points are invalid, don't bother estimating, just continue
      if (!isFinite (cloud.points[indices[i_idx]]) || !isFinite (cloud.points[indices[j_idx]]))
        continue;

      if (use_cache_)
      {
        // In order to create the key, always use the smaller index as the first key pair member
        int p1, p2;
  //      if (indices[i_idx] >= indices[j_idx])
  //      {
          p1 = indices[i_idx];
          p2 = indices[j_idx];
  //      }
  //      else
  //      {
  //        p1 = indices[j_idx];
  //        p2 = indices[i_idx];
  //      }
        key = std::pair<int, int> (p1, p2);

        // Check to see if we already estimated this pair in the global hashmap
        std::map<std::pair<int, int>, Eigen::Vector4f, std::less<std::pair<int, int> >, Eigen::aligned_allocator<std::pair<const std::pair<int, int>, Eigen::Vector4f> > >::iterator fm_it = feature_map_.find (key);
        if (fm_it != feature_map_.end ())
        {
          pfh_tuple_ = fm_it->second;
          key_found = true;
        }
        else
        {
          // Compute the pair NNi to NNj
          if (!computePairFeatures (cloud, normals, indices[i_idx], indices[j_idx],
                                    pfh_tuple_[0], pfh_tuple_[1], pfh_tuple_[2], pfh_tuple_[3]))
            continue;

          key_found = false;
        }
      }
      else
        if (!computePairFeatures (cloud, normals, indices[i_idx], indices[j_idx],
                                  pfh_tuple_[0], pfh_tuple_[1], pfh_tuple_[2], pfh_tuple_[3]))
          continue;

      // Normalize the f1, f2, f3 features and push them in the histogram
      f_index_[0] = static_cast<int> (floor (nr_split * ((pfh_tuple_[0] + M_PI) * d_pi_)));
      if (f_index_[0] < 0)         f_index_[0] = 0;
      if (f_index_[0] >= nr_split) f_index_[0] = nr_split - 1;

      f_index_[1] = static_cast<int> (floor (nr_split * ((pfh_tuple_[1] + 1.0) * 0.5)));
      if (f_index_[1] < 0)         f_index_[1] = 0;
      if (f_index_[1] >= nr_split) f_index_[1] = nr_split - 1;

      f_index_[2] = static_cast<int> (floor (nr_split * ((pfh_tuple_[2] + 1.0) * 0.5)));
      if (f_index_[2] < 0)         f_index_[2] = 0;
      if (f_index_[2] >= nr_split) f_index_[2] = nr_split - 1;

      // Copy into the histogram
      h_index = 0;
      h_p     = 1;
      for (int d = 0; d < 3; ++d)
      {
        h_index += h_p * f_index_[d];
        h_p     *= nr_split;
      }
      pfh_histogram[h_index] += hist_incr;

      if (use_cache_ && !key_found)
      {
        // Save the value in the hashmap
        feature_map_[key] = pfh_tuple_;

        // Use a maximum cache so that we don't go overboard on RAM usage
        key_list_.push (key);
        // Check to see if we need to remove an element due to exceeding max_size
        if (key_list_.size () > max_cache_size_)
        {
          // Remove the oldest element.
          feature_map_.erase (key_list_.front ());
          key_list_.pop ();
        }
      }
    }
  }
}