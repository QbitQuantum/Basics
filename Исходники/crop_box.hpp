template<typename PointT> void
pcl::CropBox<PointT>::applyFilter (std::vector<int> &indices)
{
  indices.resize (input_->points.size ());
  int indice_count = 0;

  Eigen::Affine3f transform = Eigen::Affine3f::Identity ();
  Eigen::Affine3f inverse_transform = Eigen::Affine3f::Identity ();

  if (rotation_ != Eigen::Vector3f::Zero ())
  {
    pcl::getTransformation (0, 0, 0,
                            rotation_ (0), rotation_ (1), rotation_ (2),
                            transform);
    inverse_transform = transform.inverse ();
  }

  for (size_t index = 0; index < indices_->size (); ++index)
  {
    if (!input_->is_dense)
      // Check if the point is invalid
      if (!isFinite (input_->points[index]))
        continue;

    // Get local point
    PointT local_pt = input_->points[(*indices_)[index]];

    // Transform point to world space
    if (!(transform_.matrix ().isIdentity ()))
      local_pt = pcl::transformPoint<PointT> (local_pt, transform_);

    if (translation_ != Eigen::Vector3f::Zero ())
    {
      local_pt.x -= translation_ (0);
      local_pt.y -= translation_ (1);
      local_pt.z -= translation_ (2);
    }

    // Transform point to local space of crop box
    if (!(inverse_transform.matrix ().isIdentity ()))
      local_pt = pcl::transformPoint<PointT> (local_pt, inverse_transform);

    if (local_pt.x < min_pt_[0] || local_pt.y < min_pt_[1] || local_pt.z < min_pt_[2])
      continue;
    if (local_pt.x > max_pt_[0] || local_pt.y > max_pt_[1] || local_pt.z > max_pt_[2])
      continue;

    indices[indice_count++] = (*indices_)[index];
  }
  indices.resize (indice_count);
}