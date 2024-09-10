ON_NurbsSurface
FittingCylinder::initNurbsPCACylinder (int order, NurbsDataSurface *data)
{
  Eigen::Vector3d mean;
  Eigen::Matrix3d eigenvectors;
  Eigen::Vector3d eigenvalues;

  unsigned s = unsigned (data->interior.size ());

  NurbsTools::pca (data->interior, mean, eigenvectors, eigenvalues);

  data->mean = mean;
  data->eigenvectors = eigenvectors;

  eigenvalues = eigenvalues / s; // seems that the eigenvalues are dependent on the number of points (???)

  Eigen::Vector3d v_max (0.0, 0.0, 0.0);
  Eigen::Vector3d v_min (DBL_MAX, DBL_MAX, DBL_MAX);
  for (unsigned i = 0; i < s; i++)
  {
    Eigen::Vector3d p (eigenvectors.inverse () * (data->interior[i] - mean));

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

  int ncpsU (order);
  int ncpsV (2 * order + 4);
  ON_NurbsSurface nurbs (3, false, order, order, ncpsU, ncpsV);
  nurbs.MakeClampedUniformKnotVector (0, 1.0);
  nurbs.MakePeriodicUniformKnotVector (1, 1.0 / (ncpsV - order + 1));

  double dcu = (v_max (0) - v_min (0)) / (ncpsU - 1);
  double dcv = (2.0 * M_PI) / (ncpsV - order + 1);

  double ry = std::max<double> (std::fabs (v_min (1)), std::fabs (v_max (1)));
  double rz = std::max<double> (std::fabs (v_min (2)), std::fabs (v_max (2)));

  Eigen::Vector3d cv_t, cv;
  for (int i = 0; i < ncpsU; i++)
  {
    for (int j = 0; j < ncpsV; j++)
    {
      cv (0) = v_min (0) + dcu * i;
      cv (1) = ry * sin (dcv * j);
      cv (2) = rz * cos (dcv * j);
      cv_t = eigenvectors * cv + mean;
      nurbs.SetCV (i, j, ON_3dPoint (cv_t (0), cv_t (1), cv_t (2)));
    }
  }

  return nurbs;
}