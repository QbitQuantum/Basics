template <typename PointT> void
pcl::ExtractPolygonalPrismData<PointT>::segment (pcl::PointIndices &output)
{
  output.header = input_->header;

  if (!initCompute ())
  {
    output.indices.clear ();
    return;
  }

  if (static_cast<int> (planar_hull_->points.size ()) < min_pts_hull_)
  {
    PCL_ERROR ("[pcl::%s::segment] Not enough points (%zu) in the hull!\n", getClassName ().c_str (), planar_hull_->points.size ());
    output.indices.clear ();
    return;
  }

  // Compute the plane coefficients
  Eigen::Vector4f model_coefficients;
  EIGEN_ALIGN16 Eigen::Matrix3f covariance_matrix;
  Eigen::Vector4f xyz_centroid;

  computeMeanAndCovarianceMatrix (*planar_hull_, covariance_matrix, xyz_centroid);

  // Compute the model coefficients
  EIGEN_ALIGN16 Eigen::Vector3f::Scalar eigen_value;
  EIGEN_ALIGN16 Eigen::Vector3f eigen_vector;
  eigen33 (covariance_matrix, eigen_value, eigen_vector);

  model_coefficients[0] = eigen_vector [0];
  model_coefficients[1] = eigen_vector [1];
  model_coefficients[2] = eigen_vector [2];
  model_coefficients[3] = 0;

  // Hessian form (D = nc . p_plane (centroid here) + p)
  model_coefficients[3] = -1 * model_coefficients.dot (xyz_centroid);

  // Need to flip the plane normal towards the viewpoint
  Eigen::Vector4f vp (vpx_, vpy_, vpz_, 0);
  // See if we need to flip any plane normals
  vp -= planar_hull_->points[0].getVector4fMap ();
  vp[3] = 0;
  // Dot product between the (viewpoint - point) and the plane normal
  float cos_theta = vp.dot (model_coefficients);
  // Flip the plane normal
  if (cos_theta < 0)
  {
    model_coefficients *= -1;
    model_coefficients[3] = 0;
    // Hessian form (D = nc . p_plane (centroid here) + p)
    model_coefficients[3] = -1 * (model_coefficients.dot (planar_hull_->points[0].getVector4fMap ()));
  }

  // Project all points
  PointCloud projected_points;
  SampleConsensusModelPlane<PointT> sacmodel (input_);
  sacmodel.projectPoints (*indices_, model_coefficients, projected_points, false);

  // Create a X-Y projected representation for within bounds polygonal checking
  int k0, k1, k2;
  // Determine the best plane to project points onto
  k0 = (fabs (model_coefficients[0] ) > fabs (model_coefficients[1])) ? 0  : 1;
  k0 = (fabs (model_coefficients[k0]) > fabs (model_coefficients[2])) ? k0 : 2;
  k1 = (k0 + 1) % 3;
  k2 = (k0 + 2) % 3;
  // Project the convex hull
  pcl::PointCloud<PointT> polygon;
  polygon.points.resize (planar_hull_->points.size ());
  for (size_t i = 0; i < planar_hull_->points.size (); ++i)
  {
    Eigen::Vector4f pt (planar_hull_->points[i].x, planar_hull_->points[i].y, planar_hull_->points[i].z, 0);
    polygon.points[i].x = pt[k1];
    polygon.points[i].y = pt[k2];
    polygon.points[i].z = 0;
  }

  PointT pt_xy;
  pt_xy.z = 0;

  output.indices.resize (indices_->size ());
  int l = 0;
  for (size_t i = 0; i < projected_points.points.size (); ++i)
  {
    // Check the distance to the user imposed limits from the table planar model
    double distance = pointToPlaneDistanceSigned (input_->points[(*indices_)[i]], model_coefficients);
    if (distance < height_limit_min_ || distance > height_limit_max_)
      continue;

    // Check what points are inside the hull
    Eigen::Vector4f pt (projected_points.points[i].x,
                         projected_points.points[i].y,
                         projected_points.points[i].z, 0);
    pt_xy.x = pt[k1];
    pt_xy.y = pt[k2];

    if (!pcl::isXYPointIn2DXYPolygon (pt_xy, polygon))
      continue;

    output.indices[l++] = (*indices_)[i];
  }
  output.indices.resize (l);

  deinitCompute ();
}