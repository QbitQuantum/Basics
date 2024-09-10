template <typename PointT> void
pcl::SampleConsensusModelPlane<PointT>::projectPoints (
      const std::vector<int> &inliers, const Eigen::VectorXf &model_coefficients, PointCloud &projected_points, bool copy_data_fields)
{
  // Needs a valid set of model coefficients
  if (model_coefficients.size () != 4)
  {
    PCL_ERROR ("[pcl::SampleConsensusModelPlane::projectPoints] Invalid number of model coefficients given (%zu)!\n", model_coefficients.size ());
    return;
  }

  projected_points.header = input_->header;
  projected_points.is_dense = input_->is_dense;

  Eigen::Vector4f mc (model_coefficients[0], model_coefficients[1], model_coefficients[2], 0);

  // normalize the vector perpendicular to the plane...
  mc.normalize ();
  // ... and store the resulting normal as a local copy of the model coefficients
  Eigen::Vector4f tmp_mc = model_coefficients;
  tmp_mc[0] = mc[0];
  tmp_mc[1] = mc[1];
  tmp_mc[2] = mc[2];

  // Copy all the data fields from the input cloud to the projected one?
  if (copy_data_fields)
  {
    // Allocate enough space and copy the basics
    projected_points.points.resize (input_->points.size ());
    projected_points.width    = input_->width;
    projected_points.height   = input_->height;

    typedef typename pcl::traits::fieldList<PointT>::type FieldList;
    // Iterate over each point
    for (size_t i = 0; i < input_->points.size (); ++i)
      // Iterate over each dimension
      pcl::for_each_type <FieldList> (NdConcatenateFunctor <PointT, PointT> (input_->points[i], projected_points.points[i]));

    // Iterate through the 3d points and calculate the distances from them to the plane
    for (size_t i = 0; i < inliers.size (); ++i)
    {
      // Calculate the distance from the point to the plane
      Eigen::Vector4f p (input_->points[inliers[i]].x,
                         input_->points[inliers[i]].y,
                         input_->points[inliers[i]].z,
                         1);
      // use normalized coefficients to calculate the scalar projection
      float distance_to_plane = tmp_mc.dot (p);

      pcl::Vector4fMap pp = projected_points.points[inliers[i]].getVector4fMap ();
      pp.matrix () = p - mc * distance_to_plane;        // mc[3] = 0, therefore the 3rd coordinate is safe
    }
  }
  else
  {
    // Allocate enough space and copy the basics
    projected_points.points.resize (inliers.size ());
    projected_points.width    = static_cast<uint32_t> (inliers.size ());
    projected_points.height   = 1;

    typedef typename pcl::traits::fieldList<PointT>::type FieldList;
    // Iterate over each point
    for (size_t i = 0; i < inliers.size (); ++i)
      // Iterate over each dimension
      pcl::for_each_type <FieldList> (NdConcatenateFunctor <PointT, PointT> (input_->points[inliers[i]], projected_points.points[i]));

    // Iterate through the 3d points and calculate the distances from them to the plane
    for (size_t i = 0; i < inliers.size (); ++i)
    {
      // Calculate the distance from the point to the plane
      Eigen::Vector4f p (input_->points[inliers[i]].x,
                         input_->points[inliers[i]].y,
                         input_->points[inliers[i]].z,
                         1);
      // use normalized coefficients to calculate the scalar projection
      float distance_to_plane = tmp_mc.dot (p);

      pcl::Vector4fMap pp = projected_points.points[i].getVector4fMap ();
      pp.matrix () = p - mc * distance_to_plane;        // mc[3] = 0, therefore the 3rd coordinate is safe
    }
  }
}