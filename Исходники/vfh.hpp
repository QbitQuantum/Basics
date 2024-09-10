template <typename PointInT, typename PointNT, typename PointOutT> void
pcl::VFHEstimation<PointInT, PointNT, PointOutT>::computeFeature (PointCloudOut &output)
{
  // ---[ Step 1a : compute the centroid in XYZ space
  Eigen::Vector4f xyz_centroid;

  if (use_given_centroid_) 
    xyz_centroid = centroid_to_use_;
  else
    compute3DCentroid (*surface_, *indices_, xyz_centroid);          // Estimate the XYZ centroid

  // ---[ Step 1b : compute the centroid in normal space
  Eigen::Vector4f normal_centroid = Eigen::Vector4f::Zero ();
  int cp = 0;

  // If the data is dense, we don't need to check for NaN

  if (use_given_normal_)
    normal_centroid = normal_to_use_;
  else
  {
    if (normals_->is_dense)
    {
      for (size_t i = 0; i < indices_->size (); ++i)
      {
        normal_centroid += normals_->points[(*indices_)[i]].getNormalVector4fMap ();
        cp++;
      }
    }
    // NaN or Inf values could exist => check for them
    else
    {
      for (size_t i = 0; i < indices_->size (); ++i)
      {
        if (!pcl_isfinite (normals_->points[(*indices_)[i]].normal[0])
            ||
            !pcl_isfinite (normals_->points[(*indices_)[i]].normal[1])
            ||
            !pcl_isfinite (normals_->points[(*indices_)[i]].normal[2]))
          continue;
        normal_centroid += normals_->points[(*indices_)[i]].getNormalVector4fMap ();
        cp++;
      }
    }
    normal_centroid /= cp;
  }

  // Compute the direction of view from the viewpoint to the centroid
  Eigen::Vector4f viewpoint (vpx_, vpy_, vpz_, 0);
  Eigen::Vector4f d_vp_p = viewpoint - xyz_centroid;
  d_vp_p.normalize ();

  // Estimate the SPFH at nn_indices[0] using the entire cloud
  computePointSPFHSignature (xyz_centroid, normal_centroid, *surface_, *normals_, *indices_);

  // We only output _1_ signature
  output.points.resize (1);
  output.width = 1;
  output.height = 1;

  // Estimate the FPFH at nn_indices[0] using the entire cloud and copy the resultant signature
  for (int d = 0; d < hist_f1_.size (); ++d)
    output.points[0].histogram[d + 0] = hist_f1_[d];

  size_t data_size = hist_f1_.size ();
  for (int d = 0; d < hist_f2_.size (); ++d)
    output.points[0].histogram[d + data_size] = hist_f2_[d];

  data_size += hist_f2_.size ();
  for (int d = 0; d < hist_f3_.size (); ++d)
    output.points[0].histogram[d + data_size] = hist_f3_[d];

  data_size += hist_f3_.size ();
  for (int d = 0; d < hist_f4_.size (); ++d)
    output.points[0].histogram[d + data_size] = hist_f4_[d];

  // ---[ Step 2 : obtain the viewpoint component
  hist_vp_.setZero (nr_bins_vp_);

  double hist_incr;
  if (normalize_bins_)
    hist_incr = 100.0 / (double)(indices_->size ());
  else
    hist_incr = 1.0;

  for (size_t i = 0; i < indices_->size (); ++i)
  {
    Eigen::Vector4f normal (normals_->points[(*indices_)[i]].normal[0],
                            normals_->points[(*indices_)[i]].normal[1],
                            normals_->points[(*indices_)[i]].normal[2], 0);
    // Normalize
    double alpha = (normal.dot (d_vp_p) + 1.0) * 0.5;
    int fi = floor (alpha * hist_vp_.size ());
    if (fi < 0)
      fi = 0;
    if (fi > ((int)hist_vp_.size () - 1))
      fi = hist_vp_.size () - 1;
    // Bin into the histogram
    hist_vp_ [fi] += hist_incr;
  }
  data_size += hist_f4_.size ();
  // Copy the resultant signature
  for (int d = 0; d < hist_vp_.size (); ++d)
    output.points[0].histogram[d + data_size] = hist_vp_[d];
}