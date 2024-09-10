template <typename PointInT, typename PointNT, typename PointOutT> bool
pcl::ShapeContext3DEstimation<PointInT, PointNT, PointOutT>::computePoint (
    size_t index, const pcl::PointCloud<PointNT> &normals, float rf[9], std::vector<float> &desc)
{
  // The RF is formed as this x_axis | y_axis | normal
  Eigen::Map<Eigen::Vector3f> x_axis (rf);
  Eigen::Map<Eigen::Vector3f> y_axis (rf + 3);
  Eigen::Map<Eigen::Vector3f> normal (rf + 6);

  // Find every point within specified search_radius_
  std::vector<int> nn_indices;
  std::vector<float> nn_dists;
  const size_t neighb_cnt = searchForNeighbors ((*indices_)[index], search_radius_, nn_indices, nn_dists);
  if (neighb_cnt == 0)
  {
    for (size_t i = 0; i < desc.size (); ++i)
      desc[i] = std::numeric_limits<float>::quiet_NaN ();

    memset (rf, 0, sizeof (rf[0]) * 9);
    return (false);
  }

  float minDist = std::numeric_limits<float>::max ();
  int minIndex = -1;
  for (size_t i = 0; i < nn_indices.size (); i++)
  {
	  if (nn_dists[i] < minDist)
	  {
      minDist = nn_dists[i];
      minIndex = nn_indices[i];
	  }
  }
  
  // Get origin point
  Vector3fMapConst origin = input_->points[(*indices_)[index]].getVector3fMap ();
  // Get origin normal
  // Use pre-computed normals
  normal = normals[minIndex].getNormalVector3fMap ();

  // Compute and store the RF direction
  x_axis[0] = static_cast<float> (rnd ());
  x_axis[1] = static_cast<float> (rnd ());
  x_axis[2] = static_cast<float> (rnd ());
  if (!pcl::utils::equal (normal[2], 0.0f))
    x_axis[2] = - (normal[0]*x_axis[0] + normal[1]*x_axis[1]) / normal[2];
  else if (!pcl::utils::equal (normal[1], 0.0f))
    x_axis[1] = - (normal[0]*x_axis[0] + normal[2]*x_axis[2]) / normal[1];
  else if (!pcl::utils::equal (normal[0], 0.0f))
    x_axis[0] = - (normal[1]*x_axis[1] + normal[2]*x_axis[2]) / normal[0];

  x_axis.normalize ();

  // Check if the computed x axis is orthogonal to the normal
  assert (pcl::utils::equal (x_axis[0]*normal[0] + x_axis[1]*normal[1] + x_axis[2]*normal[2], 0.0f, 1E-6f));

  // Store the 3rd frame vector
  y_axis = normal.cross (x_axis);

  // For each point within radius
  for (size_t ne = 0; ne < neighb_cnt; ne++)
  {
    if (pcl::utils::equal (nn_dists[ne], 0.0f))
		  continue;
    // Get neighbours coordinates
    Eigen::Vector3f neighbour = surface_->points[nn_indices[ne]].getVector3fMap ();

    /// ----- Compute current neighbour polar coordinates -----
    /// Get distance between the neighbour and the origin
    float r = sqrt (nn_dists[ne]); 
    
    /// Project point into the tangent plane
    Eigen::Vector3f proj;
    pcl::geometry::project (neighbour, origin, normal, proj);
    proj -= origin;

    /// Normalize to compute the dot product
    proj.normalize ();
    
    /// Compute the angle between the projection and the x axis in the interval [0,360] 
    Eigen::Vector3f cross = x_axis.cross (proj);
    float phi = pcl::rad2deg (std::atan2 (cross.norm (), x_axis.dot (proj)));
    phi = cross.dot (normal) < 0.f ? (360.0f - phi) : phi;
    /// Compute the angle between the neighbour and the z axis (normal) in the interval [0, 180]
    Eigen::Vector3f no = neighbour - origin;
    no.normalize ();
    float theta = normal.dot (no);
    theta = pcl::rad2deg (acosf (std::min (1.0f, std::max (-1.0f, theta))));

    // Bin (j, k, l)
    size_t j = 0;
    size_t k = 0;
    size_t l = 0;

    // Compute the Bin(j, k, l) coordinates of current neighbour
    for (size_t rad = 1; rad < radius_bins_+1; rad++) 
    {
      if (r <= radii_interval_[rad]) 
      {
        j = rad-1;
        break;
      }
    }

    for (size_t ang = 1; ang < elevation_bins_+1; ang++) 
    {
      if (theta <= theta_divisions_[ang]) 
      {
        k = ang-1;
        break;
      }
    }

    for (size_t ang = 1; ang < azimuth_bins_+1; ang++) 
    {
      if (phi <= phi_divisions_[ang]) 
      {
        l = ang-1;
        break;
      }
    }

    // Local point density = number of points in a sphere of radius "point_density_radius_" around the current neighbour
    std::vector<int> neighbour_indices;
    std::vector<float> neighbour_distances;
    int point_density = searchForNeighbors (*surface_, nn_indices[ne], point_density_radius_, neighbour_indices, neighbour_distances);
    // point_density is NOT always bigger than 0 (on error, searchForNeighbors returns 0), so we must check for that
    if (point_density == 0)
      continue;

    float w = (1.0f / static_cast<float> (point_density)) * 
              volume_lut_[(l*elevation_bins_*radius_bins_) +  (k*radius_bins_) + j];
      
    assert (w >= 0.0);
    if (w == std::numeric_limits<float>::infinity ())
      PCL_ERROR ("Shape Context Error INF!\n");
    if (w != w)
      PCL_ERROR ("Shape Context Error IND!\n");
    /// Accumulate w into correspondant Bin(j,k,l)
    desc[(l*elevation_bins_*radius_bins_) + (k*radius_bins_) + j] += w;

    assert (desc[(l*elevation_bins_*radius_bins_) + (k*radius_bins_) + j] >= 0);
  } // end for each neighbour

  // 3DSC does not define a repeatable local RF, we set it to zero to signal it to the user 
  memset (rf, 0, sizeof (rf[0]) * 9);
  return (true);
}