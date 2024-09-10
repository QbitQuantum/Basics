template <typename PointT, typename PointNT> void
pcl::SampleConsensusModelCone<PointT, PointNT>::projectPoints (
      const std::vector<int> &inliers, const Eigen::VectorXf &model_coefficients, PointCloud &projected_points, bool copy_data_fields)
{
  // Needs a valid set of model coefficients
  if (model_coefficients.size () != 7)
  {
    PCL_ERROR ("[pcl::SampleConsensusModelCone::projectPoints] Invalid number of model coefficients given (%lu)!\n", model_coefficients.size ());
    return;
  }

  projected_points.header = input_->header;
  projected_points.is_dense = input_->is_dense;

  Eigen::Vector4f apex  (model_coefficients[0], model_coefficients[1], model_coefficients[2], 0);
  Eigen::Vector4f axis_dir (model_coefficients[3], model_coefficients[4], model_coefficients[5], 0);
  float opening_angle = model_coefficients[6];

  float apexdotdir = apex.dot (axis_dir);
  float dirdotdir = 1.0f / axis_dir.dot (axis_dir);

  // Copy all the data fields from the input cloud to the projected one?
  if (copy_data_fields)
  {
    // Allocate enough space and copy the basics
    projected_points.points.resize (input_->points.size ());
    projected_points.width    = input_->width;
    projected_points.height   = input_->height;

    typedef typename pcl::traits::fieldList<PointT>::type FieldList;
    // Iterate over each point
    for (size_t i = 0; i < projected_points.points.size (); ++i)
      // Iterate over each dimension
      pcl::for_each_type <FieldList> (NdConcatenateFunctor <PointT, PointT> (input_->points[i], projected_points.points[i]));

    // Iterate through the 3d points and calculate the distances from them to the cone
    for (size_t i = 0; i < inliers.size (); ++i)
    {
      Eigen::Vector4f pt (input_->points[inliers[i]].x, 
                          input_->points[inliers[i]].y, 
                          input_->points[inliers[i]].z, 
                          1);

      float k = (pt.dot (axis_dir) - apexdotdir) * dirdotdir;

      pcl::Vector4fMap pp = projected_points.points[inliers[i]].getVector4fMap ();
      pp.matrix () = apex + k * axis_dir;

      Eigen::Vector4f dir = pt - pp;
      dir.normalize ();

      // Calculate the actual radius of the cone at the level of the projected point
      Eigen::Vector4f height = apex - pp;
      float actual_cone_radius = tanf (opening_angle) * height.norm ();

      // Calculate the projection of the point onto the cone
      pp += dir * actual_cone_radius;
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

    // Iterate through the 3d points and calculate the distances from them to the cone
    for (size_t i = 0; i < inliers.size (); ++i)
    {
      pcl::Vector4fMap pp = projected_points.points[i].getVector4fMap ();
      pcl::Vector4fMapConst pt = input_->points[inliers[i]].getVector4fMap ();

      float k = (pt.dot (axis_dir) - apexdotdir) * dirdotdir;
      // Calculate the projection of the point on the line
      pp.matrix () = apex + k * axis_dir;

      Eigen::Vector4f dir = pt - pp;
      dir.normalize ();

      // Calculate the actual radius of the cone at the level of the projected point
      Eigen::Vector4f height = apex - pp;
      float actual_cone_radius = tanf (opening_angle) * height.norm ();

      // Calculate the projection of the point onto the cone
      pp += dir * actual_cone_radius;
    }
  }
}