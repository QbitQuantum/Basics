void
pcl::CropBox<pcl::PCLPointCloud2>::applyFilter (PCLPointCloud2 &output)
{
  // Resize output cloud to sample size
  output.data.resize (input_->data.size ());
  removed_indices_->resize (input_->data.size ());

  // Copy the common fields
  output.fields = input_->fields;
  output.is_bigendian = input_->is_bigendian;
  output.row_step = input_->row_step;
  output.point_step = input_->point_step;
  output.height = 1;

  int indices_count = 0;
  int removed_indices_count = 0;

  Eigen::Affine3f transform = Eigen::Affine3f::Identity();
  Eigen::Affine3f inverse_transform = Eigen::Affine3f::Identity();

  if (rotation_ != Eigen::Vector3f::Zero ())
  {
    pcl::getTransformation (0, 0, 0,
                            rotation_ (0), rotation_ (1), rotation_ (2),
                            transform);
    inverse_transform = transform.inverse();
  }

  //PointXYZ local_pt;
  Eigen::Vector3f local_pt (Eigen::Vector3f::Zero ());

  for (size_t index = 0; index < indices_->size (); ++index)
  {
    // Get local point
    int point_offset = ((*indices_)[index] * input_->point_step);
    int offset = point_offset + input_->fields[x_idx_].offset;
    memcpy (&local_pt, &input_->data[offset], sizeof (float)*3);

    // Check if the point is invalid
    if (!pcl_isfinite (local_pt.x ()) ||
        !pcl_isfinite (local_pt.y ()) ||
        !pcl_isfinite (local_pt.z ()))
      continue;

    // Transform point to world space
    if (!(transform_.matrix().isIdentity()))
      local_pt = transform_ * local_pt;

    if (translation_ != Eigen::Vector3f::Zero ())
    {
      local_pt.x () = local_pt.x () - translation_ (0);
      local_pt.y () = local_pt.y () - translation_ (1);
      local_pt.z () = local_pt.z () - translation_ (2);
    }

    // Transform point to local space of crop box
    if (!(inverse_transform.matrix ().isIdentity ()))
      local_pt = inverse_transform * local_pt;

    // If outside the cropbox
    if ( (local_pt.x () < min_pt_[0] || local_pt.y () < min_pt_[1] || local_pt.z () < min_pt_[2]) ||
         (local_pt.x () > max_pt_[0] || local_pt.y () > max_pt_[1] || local_pt.z () > max_pt_[2]))
    {
      if (negative_)
      {
        memcpy (&output.data[indices_count++ * output.point_step],
                &input_->data[index * output.point_step], output.point_step);
      }
      else if (extract_removed_indices_)
      {
        (*removed_indices_)[removed_indices_count++] = static_cast<int> (index);
      }
    }
    // If inside the cropbox
    else
    {
      if (negative_ && extract_removed_indices_)
      {
        (*removed_indices_)[removed_indices_count++] = static_cast<int> (index);
      }
      else if (!negative_) {
        memcpy (&output.data[indices_count++ * output.point_step],
                &input_->data[index * output.point_step], output.point_step);
      }
    }
  }
  output.width = indices_count;
  output.row_step = output.point_step * output.width;
  output.data.resize (output.width * output.height * output.point_step);

  removed_indices_->resize (removed_indices_count);
}