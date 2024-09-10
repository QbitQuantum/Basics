ON_NurbsSurface
FittingSurface::initNurbsPCABoundingBox (int order, NurbsDataSurface *m_data, Eigen::Vector3d z)
{
  Eigen::Vector3d mean;
  Eigen::Matrix3d eigenvectors;
  Eigen::Vector3d eigenvalues;

  unsigned s = m_data->interior.size ();
  m_data->interior_param.clear ();

  NurbsTools::pca (m_data->interior, mean, eigenvectors, eigenvalues);

  m_data->mean = mean;
  m_data->eigenvectors = eigenvectors;

  bool flip (false);
  if (eigenvectors.col (2).dot (z) < 0.0)
    flip = true;

  eigenvalues = eigenvalues / s; // seems that the eigenvalues are dependent on the number of points (???)
  Eigen::Matrix3d eigenvectors_inv = eigenvectors.inverse ();

  Eigen::Vector3d v_max (0.0, 0.0, 0.0);
  Eigen::Vector3d v_min (DBL_MAX, DBL_MAX, DBL_MAX);
  for (unsigned i = 0; i < s; i++)
  {
    Eigen::Vector3d p = eigenvectors_inv * (m_data->interior[i] - mean);
    m_data->interior_param.push_back (Eigen::Vector2d (p (0), p (1)));

    if (p (0) > v_max (0))
      v_max (0) = p (0);
    if (p (1) > v_max (1))
      v_max (1) = p (1);
    if (p (2) > v_max (2))
      v_max (2) = p (2);

    if (p (0) < v_min (0))
      v_min (0) = p (0);
    if (p (1) < v_min (1))
      v_min (1) = p (1);
    if (p (2) < v_min (2))
      v_min (2) = p (2);
  }

  for (unsigned i = 0; i < s; i++)
  {
    Eigen::Vector2d &p = m_data->interior_param[i];
    if (v_max (0) > v_min (0) && v_max (0) > v_min (0))
    {
      p (0) = (p (0) - v_min (0)) / (v_max (0) - v_min (0));
      p (1) = (p (1) - v_min (1)) / (v_max (1) - v_min (1));
    }
    else
    {
      throw std::runtime_error ("[NurbsTools::initNurbsPCABoundingBox] Error: v_max <= v_min");
    }
  }

  ON_NurbsSurface nurbs (3, false, order, order, order, order);
  nurbs.MakeClampedUniformKnotVector (0, 1.0);
  nurbs.MakeClampedUniformKnotVector (1, 1.0);

  double dcu = (v_max (0) - v_min (0)) / (nurbs.Order (0) - 1);
  double dcv = (v_max (1) - v_min (1)) / (nurbs.Order (1) - 1);

  Eigen::Vector3d cv_t, cv;
  for (int i = 0; i < nurbs.Order (0); i++)
  {
    for (int j = 0; j < nurbs.Order (1); j++)
    {
      cv (0) = v_min (0) + dcu * i;
      cv (1) = v_min (1) + dcv * j;
      cv (2) = 0.0;
      cv_t = eigenvectors * cv + mean;
      if (flip)
        nurbs.SetCV (nurbs.Order (0) - 1 - i, j, ON_3dPoint (cv_t (0), cv_t (1), cv_t (2)));
      else
        nurbs.SetCV (i, j, ON_3dPoint (cv_t (0), cv_t (1), cv_t (2)));
    }
  }
  return nurbs;
}