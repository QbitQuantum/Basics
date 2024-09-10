template <typename PointT, typename PointNT> void
pcl::SampleConsensusModelCylinder<PointT, PointNT>::getDistancesToModel (
      const Eigen::VectorXf &model_coefficients, std::vector<double> &distances)
{
  // Check if the model is valid given the user constraints
  if (!isModelValid (model_coefficients))
  {
    distances.clear ();
    return;
  }

  distances.resize (indices_->size ());

  Eigen::Vector4f line_pt  (model_coefficients[0], model_coefficients[1], model_coefficients[2], 0);
  Eigen::Vector4f line_dir (model_coefficients[3], model_coefficients[4], model_coefficients[5], 0);
  float ptdotdir = line_pt.dot (line_dir);
  float dirdotdir = 1.0f / line_dir.dot (line_dir);
  // Iterate through the 3d points and calculate the distances from them to the sphere
  for (size_t i = 0; i < indices_->size (); ++i)
  {
    // Aproximate the distance from the point to the cylinder as the difference between
    // dist(point,cylinder_axis) and cylinder radius
    // @note need to revise this.
    Eigen::Vector4f pt (input_->points[(*indices_)[i]].x, input_->points[(*indices_)[i]].y, input_->points[(*indices_)[i]].z, 0);
    Eigen::Vector4f n  (normals_->points[(*indices_)[i]].normal[0], normals_->points[(*indices_)[i]].normal[1], normals_->points[(*indices_)[i]].normal[2], 0);

    double d_euclid = fabs (pointToLineDistance (pt, model_coefficients) - model_coefficients[6]);

    // Calculate the point's projection on the cylinder axis
    float k = (pt.dot (line_dir) - ptdotdir) * dirdotdir;
    Eigen::Vector4f pt_proj = line_pt + k * line_dir;
    Eigen::Vector4f dir = pt - pt_proj;
    dir.normalize ();

    // Calculate the angular distance between the point normal and the (dir=pt_proj->pt) vector
    double d_normal = fabs (getAngle3D (n, dir));
    d_normal = (std::min) (d_normal, M_PI - d_normal);

    distances[i] = fabs (normal_distance_weight_ * d_normal + (1 - normal_distance_weight_) * d_euclid);
  }
}