template <typename PointInT, typename PointOutT, typename PointRFT> void
pcl::UniqueShapeContext<PointInT, PointOutT, PointRFT>::computePointDescriptor (size_t index, /*float rf[9],*/ std::vector<float> &desc)
{
  pcl::Vector3fMapConst origin = input_->points[(*indices_)[index]].getVector3fMap ();

  const Eigen::Vector3f x_axis (frames_->points[index].x_axis[0],
                                frames_->points[index].x_axis[1],
                                frames_->points[index].x_axis[2]);
  //const Eigen::Vector3f& y_axis = frames_->points[index].y_axis.getNormalVector3fMap ();
  const Eigen::Vector3f normal (frames_->points[index].z_axis[0],
                                frames_->points[index].z_axis[1],
                                frames_->points[index].z_axis[2]);

  // Find every point within specified search_radius_
  std::vector<int> nn_indices;
  std::vector<float> nn_dists;
  const size_t neighb_cnt = searchForNeighbors ((*indices_)[index], search_radius_, nn_indices, nn_dists);
  // For each point within radius
  for (size_t ne = 0; ne < neighb_cnt; ne++)
  {
    if (pcl::utils::equal(nn_dists[ne], 0.0f))
      continue;
    // Get neighbours coordinates
    Eigen::Vector3f neighbour = surface_->points[nn_indices[ne]].getVector3fMap ();

    // ----- Compute current neighbour polar coordinates -----

    // Get distance between the neighbour and the origin
    float r = std::sqrt (nn_dists[ne]);

    // Project point into the tangent plane
    Eigen::Vector3f proj;
    pcl::geometry::project (neighbour, origin, normal, proj);
    proj -= origin;

    // Normalize to compute the dot product
    proj.normalize ();

    // Compute the angle between the projection and the x axis in the interval [0,360]
    Eigen::Vector3f cross = x_axis.cross (proj);
    float phi = rad2deg (std::atan2 (cross.norm (), x_axis.dot (proj)));
    phi = cross.dot (normal) < 0.f ? (360.0f - phi) : phi;
    /// Compute the angle between the neighbour and the z axis (normal) in the interval [0, 180]
    Eigen::Vector3f no = neighbour - origin;
    no.normalize ();
    float theta = normal.dot (no);
    theta = pcl::rad2deg (acosf (std::min (1.0f, std::max (-1.0f, theta))));

    /// Bin (j, k, l)
    size_t j = 0;
    size_t k = 0;
    size_t l = 0;

    /// Compute the Bin(j, k, l) coordinates of current neighbour
    for (size_t rad = 1; rad < radius_bins_ + 1; rad++)
    {
      if (r <= radii_interval_[rad])
      {
        j = rad - 1;
        break;
      }
    }

    for (size_t ang = 1; ang < elevation_bins_ + 1; ang++)
    {
      if (theta <= theta_divisions_[ang])
      {
        k = ang - 1;
        break;
      }
    }

    for (size_t ang = 1; ang < azimuth_bins_ + 1; ang++)
    {
      if (phi <= phi_divisions_[ang])
      {
        l = ang - 1;
        break;
      }
    }

    /// Local point density = number of points in a sphere of radius "point_density_radius_" around the current neighbour
    std::vector<int> neighbour_indices;
    std::vector<float> neighbour_didtances;
    float point_density = static_cast<float> (searchForNeighbors (*surface_, nn_indices[ne], point_density_radius_, neighbour_indices, neighbour_didtances));
    /// point_density is always bigger than 0 because FindPointsWithinRadius returns at least the point itself
    float w = (1.0f / point_density) * volume_lut_[(l*elevation_bins_*radius_bins_) +
                                                   (k*radius_bins_) +
                                                   j];

    assert (w >= 0.0);
    if (w == std::numeric_limits<float>::infinity ())
      PCL_ERROR ("Shape Context Error INF!\n");
    if (w != w)
      PCL_ERROR ("Shape Context Error IND!\n");
    /// Accumulate w into correspondant Bin(j,k,l)
    desc[(l*elevation_bins_*radius_bins_) + (k*radius_bins_) + j] += w;

    assert (desc[(l*elevation_bins_*radius_bins_) + (k*radius_bins_) + j] >= 0);
  } // end for each neighbour
}