template<typename PointInT, typename PointNT, typename PointOutT> bool
pcl::OURCVFHEstimation<PointInT, PointNT, PointOutT>::sgurf (Eigen::Vector3f & centroid, Eigen::Vector3f & normal_centroid,
                                                               PointInTPtr & processed, std::vector<Eigen::Matrix4f, Eigen::aligned_allocator<Eigen::Matrix4f> > & transformations,
                                                               PointInTPtr & grid, pcl::PointIndices & indices)
{

  Eigen::Vector3f plane_normal;
  plane_normal[0] = -centroid[0];
  plane_normal[1] = -centroid[1];
  plane_normal[2] = -centroid[2];
  Eigen::Vector3f z_vector = Eigen::Vector3f::UnitZ ();
  plane_normal.normalize ();
  Eigen::Vector3f axis = plane_normal.cross (z_vector);
  double rotation = -asin (axis.norm ());
  axis.normalize ();

  Eigen::Affine3f transformPC (Eigen::AngleAxisf (static_cast<float> (rotation), axis));

  grid->points.resize (processed->points.size ());
  for (size_t k = 0; k < processed->points.size (); k++)
    grid->points[k].getVector4fMap () = processed->points[k].getVector4fMap ();

  pcl::transformPointCloud (*grid, *grid, transformPC);

  Eigen::Vector4f centroid4f (centroid[0], centroid[1], centroid[2], 0);
  Eigen::Vector4f normal_centroid4f (normal_centroid[0], normal_centroid[1], normal_centroid[2], 0);

  centroid4f = transformPC * centroid4f;
  normal_centroid4f = transformPC * normal_centroid4f;

  Eigen::Vector3f centroid3f (centroid4f[0], centroid4f[1], centroid4f[2]);

  Eigen::Vector4f farthest_away;
  pcl::getMaxDistance (*grid, indices.indices, centroid4f, farthest_away);
  farthest_away[3] = 0;

  float max_dist = (farthest_away - centroid4f).norm ();

  pcl::demeanPointCloud (*grid, centroid4f, *grid);

  Eigen::Matrix4f center_mat;
  center_mat.setIdentity (4, 4);
  center_mat (0, 3) = -centroid4f[0];
  center_mat (1, 3) = -centroid4f[1];
  center_mat (2, 3) = -centroid4f[2];

  Eigen::Matrix3f scatter;
  scatter.setZero ();
  float sum_w = 0.f;

  //for (int k = 0; k < static_cast<intgrid->points[k].getVector3fMap ();> (grid->points.size ()); k++)
  for (int k = 0; k < static_cast<int> (indices.indices.size ()); k++)
  {
    Eigen::Vector3f pvector = grid->points[indices.indices[k]].getVector3fMap ();
    float d_k = (pvector).norm ();
    float w = (max_dist - d_k);
    Eigen::Vector3f diff = (pvector);
    Eigen::Matrix3f mat = diff * diff.transpose ();
    scatter = scatter + mat * w;
    sum_w += w;
  }

  scatter /= sum_w;

  Eigen::JacobiSVD <Eigen::MatrixXf> svd (scatter, Eigen::ComputeFullV);
  Eigen::Vector3f evx = svd.matrixV ().col (0);
  Eigen::Vector3f evy = svd.matrixV ().col (1);
  Eigen::Vector3f evz = svd.matrixV ().col (2);
  Eigen::Vector3f evxminus = evx * -1;
  Eigen::Vector3f evyminus = evy * -1;
  Eigen::Vector3f evzminus = evz * -1;

  float s_xplus, s_xminus, s_yplus, s_yminus;
  s_xplus = s_xminus = s_yplus = s_yminus = 0.f;

  //disambiguate rf using all points
  for (int k = 0; k < static_cast<int> (grid->points.size ()); k++)
  {
    Eigen::Vector3f pvector = grid->points[k].getVector3fMap ();
    float dist_x, dist_y;
    dist_x = std::abs (evx.dot (pvector));
    dist_y = std::abs (evy.dot (pvector));

    if ((pvector).dot (evx) >= 0)
      s_xplus += dist_x;
    else
      s_xminus += dist_x;

    if ((pvector).dot (evy) >= 0)
      s_yplus += dist_y;
    else
      s_yminus += dist_y;

  }

  if (s_xplus < s_xminus)
    evx = evxminus;

  if (s_yplus < s_yminus)
    evy = evyminus;

  //select the axis that could be disambiguated more easily
  float fx, fy;
  float max_x = static_cast<float> (std::max (s_xplus, s_xminus));
  float min_x = static_cast<float> (std::min (s_xplus, s_xminus));
  float max_y = static_cast<float> (std::max (s_yplus, s_yminus));
  float min_y = static_cast<float> (std::min (s_yplus, s_yminus));

  fx = (min_x / max_x);
  fy = (min_y / max_y);

  Eigen::Vector3f normal3f = Eigen::Vector3f (normal_centroid4f[0], normal_centroid4f[1], normal_centroid4f[2]);
  if (normal3f.dot (evz) < 0)
    evz = evzminus;

  //if fx/y close to 1, it was hard to disambiguate
  //what if both are equally easy or difficult to disambiguate, namely fy == fx or very close

  float max_axis = std::max (fx, fy);
  float min_axis = std::min (fx, fy);

  if ((min_axis / max_axis) > axis_ratio_)
  {
    PCL_WARN("Both axis are equally easy/difficult to disambiguate\n");

    Eigen::Vector3f evy_copy = evy;
    Eigen::Vector3f evxminus = evx * -1;
    Eigen::Vector3f evyminus = evy * -1;

    if (min_axis > min_axis_value_)
    {
      //combination of all possibilities
      evy = evx.cross (evz);
      Eigen::Matrix4f trans = createTransFromAxes (evx, evy, evz, transformPC, center_mat);
      transformations.push_back (trans);

      evx = evxminus;
      evy = evx.cross (evz);
      trans = createTransFromAxes (evx, evy, evz, transformPC, center_mat);
      transformations.push_back (trans);

      evx = evy_copy;
      evy = evx.cross (evz);
      trans = createTransFromAxes (evx, evy, evz, transformPC, center_mat);
      transformations.push_back (trans);

      evx = evyminus;
      evy = evx.cross (evz);
      trans = createTransFromAxes (evx, evy, evz, transformPC, center_mat);
      transformations.push_back (trans);

    }
    else
    {
      //1-st case (evx selected)
      evy = evx.cross (evz);
      Eigen::Matrix4f trans = createTransFromAxes (evx, evy, evz, transformPC, center_mat);
      transformations.push_back (trans);

      //2-nd case (evy selected)
      evx = evy_copy;
      evy = evx.cross (evz);
      trans = createTransFromAxes (evx, evy, evz, transformPC, center_mat);
      transformations.push_back (trans);
    }
  }
  else
  {
    if (fy < fx)
    {
      evx = evy;
      fx = fy;
    }

    evy = evx.cross (evz);
    Eigen::Matrix4f trans = createTransFromAxes (evx, evy, evz, transformPC, center_mat);
    transformations.push_back (trans);

  }

  return true;
}