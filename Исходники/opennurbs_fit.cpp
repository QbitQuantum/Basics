ON_NurbsSurface
FittingSurface::initNurbsPCABoundingBox (int order, NurbsDataSurface *m_data, ON_3dVector z)
{
  ON_3dVector mean;
  Eigen::Matrix3d eigenvectors;
  Eigen::Vector3d eigenvalues;

  unsigned s = m_data->interior.size ();
  m_data->interior_param.clear ();

  NurbsTools::pca (m_data->interior, mean, eigenvectors, eigenvalues);

  m_data->mean = mean;
  //m_data->eigenvectors = (*eigenvectors);

  bool flip (false);
  Eigen::Vector3d ez(z[0],z[1],z[2]);
  if (eigenvectors.col (2).dot (ez) < 0.0)
    flip = true;

  eigenvalues = eigenvalues / s; // seems that the eigenvalues are dependent on the number of points (???)
  Eigen::Matrix3d eigenvectors_inv = eigenvectors.inverse ();

  ON_3dVector v_max(0.0, 0.0, 0.0);
  ON_3dVector v_min(DBL_MAX, DBL_MAX, DBL_MAX);
  Eigen::Vector3d emean(mean[0], mean[1], mean[2]);
  for (unsigned i = 0; i < s; i++)
  {
    Eigen::Vector3d eint(m_data->interior[i][0], m_data->interior[i][1], m_data->interior[i][2]);
    Eigen::Vector3d ep = eigenvectors_inv * (eint - emean);
    ON_3dPoint p(ep (0), ep (1), ep(2));
    m_data->interior_param.push_back (ON_2dPoint(p[0], p[1]));

    if (p[0] > v_max[0])
      v_max[0] = p[0];
    if (p[1] > v_max[1])
      v_max[1] = p[1];
    if (p[2] > v_max[2])
      v_max[2] = p[2];

    if (p[0] < v_min[0])
      v_min[0] = p[0];
    if (p[1] < v_min[1])
      v_min[1] = p[1];
    if (p[2] < v_min[2])
      v_min[2] = p[2];
  }

  for (unsigned i = 0; i < s; i++)
  {
    ON_2dVector &p = m_data->interior_param[i];
    if (v_max[0] > v_min[0] && v_max[0] > v_min[0])
    {
      p[0] = (p[0] - v_min[0]) / (v_max[0] - v_min[0]);
      p[1] = (p[1] - v_min[1]) / (v_max[1] - v_min[1]);
    }
    else
    {
      throw std::runtime_error ("[NurbsTools::initNurbsPCABoundingBox] Error: v_max <= v_min");
    }
  }

  ON_NurbsSurface nurbs (3, false, order, order, order, order);

  nurbs.MakeClampedUniformKnotVector (0, 1.0);
  nurbs.MakeClampedUniformKnotVector (1, 1.0);

  double dcu = (v_max[0] - v_min[0]) / (nurbs.Order (0) - 1);
  double dcv = (v_max[1] - v_min[1]) / (nurbs.Order (1) - 1);

  ON_3dPoint cv_t, cv;
  Eigen::Vector3d ecv_t2, ecv2;
  Eigen::Vector3d emean2(mean[0],mean[1],mean[2]);
  for (int i = 0; i < nurbs.Order (0); i++)
  {
    for (int j = 0; j < nurbs.Order (1); j++)
    {
      cv[0] = v_min[0] + dcu * i;
      cv[1] = v_min[1] + dcv * j;
      cv[2] = 0.0;
      ecv2 (0) = cv[0];
      ecv2 (1) = cv[1];
      ecv2 (2) = cv[2];
      ecv_t2 = eigenvectors * ecv2 + emean2;
      if (flip)
	nurbs.SetCV (nurbs.Order (0) - 1 - i, j, cv_t);
      else
	nurbs.SetCV (i, j, cv_t);
    }
  }
  return nurbs;
}