template <typename PointSource, typename PointTarget, typename NormalT, typename Scalar> int
pcl::registration::FPCSInitialAlignment <PointSource, PointTarget, NormalT, Scalar>::selectBaseTriangle (std::vector <int> &base_indices)
{
  int nr_points = static_cast <int> (target_indices_->size ());
  float best_t = 0.f;

  // choose random first point
  base_indices[0] = (*target_indices_)[rand () % nr_points];
  int *index1 = &base_indices[0];

  // random search for 2 other points (as far away as overlap allows)
  for (int i = 0; i < ransac_iterations_; i++)
  {
    int *index2 = &(*target_indices_)[rand () % nr_points];
    int *index3 = &(*target_indices_)[rand () % nr_points];

    Eigen::Vector3f u = target_->points[*index2].getVector3fMap () - target_->points[*index1].getVector3fMap ();
    Eigen::Vector3f v = target_->points[*index3].getVector3fMap () - target_->points[*index1].getVector3fMap ();
    float t = u.cross (v).squaredNorm (); // triangle area (0.5 * sqrt(t)) should be maximal

    // check for most suitable point triple
    if (t > best_t && u.squaredNorm () < max_base_diameter_sqr_ && v.squaredNorm () < max_base_diameter_sqr_)
    {
      best_t = t;
      base_indices[1] = *index2;
      base_indices[2] = *index3;
    }
  }

  // return if a triplet could be selected
  return (best_t == 0.f ? -1 : 0);
}