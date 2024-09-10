void
FittingCurve2dSDM::assembleInterior (double wInt, double sigma2, unsigned &row)
{
  unsigned nInt = m_data->interior.size ();
  bool wFunction (true);
  double ds = 1.0 / (2.0 * sigma2);
  m_data->interior_line_start.clear ();
  m_data->interior_line_end.clear ();
  m_data->interior_error.clear ();
  m_data->interior_normals.clear ();

  unsigned updateTNR (false);
  if (m_data->interior_ncps_prev != m_nurbs.CVCount ())
  {
    if (!m_quiet)
      printf ("[FittingCurve2dSDM::assembleInterior] updating T, N, rho\n");
    m_data->interior_tangents.clear ();
    m_data->interior_normals.clear ();
    m_data->interior_rho.clear ();
    m_data->interior_ncps_prev = m_nurbs.CVCount ();
    updateTNR = true;
  }

  unsigned i1 (0);
  unsigned i2 (0);

  for (unsigned p = 0; p < nInt; p++)
  {
    Eigen::Vector2d &pcp = m_data->interior[p];

    // inverse mapping
    double param;
    Eigen::Vector2d pt, t, n;
    double error;
    if (p < m_data->interior_param.size ())
    {
      param = inverseMapping (m_nurbs, pcp, m_data->interior_param[p], error, pt, t, in_max_steps, in_accuracy);
      m_data->interior_param[p] = param;
    }
    else
    {
      param = findClosestElementMidPoint (m_nurbs, pcp);
      param = inverseMapping (m_nurbs, pcp, param, error, pt, t, in_max_steps, in_accuracy);
      m_data->interior_param.push_back (param);
    }

    m_data->interior_error.push_back (error);

    double dt, kappa, rho, rho_prev;
    Eigen::Vector2d n_prev, t_prev;

    double pointAndTangents[6];
    m_nurbs.Evaluate (param, 2, 2, pointAndTangents);
    pt (0) = pointAndTangents[0];
    pt (1) = pointAndTangents[1];
    t (0) = pointAndTangents[2];
    t (1) = pointAndTangents[3];
    n (0) = pointAndTangents[4];
    n (1) = pointAndTangents[5];

    dt = t.norm ();
    t /= dt;
    Eigen::Vector2d in (t (1), -t (0));
    n /= dt; // TODO something is wrong with the normal from nurbs.Evaluate(...)
    n = in * in.dot (n);

    kappa = n.norm ();
    rho = (1.0 / kappa);
    n *= rho;

    if (!updateTNR)
    {
      if (m_data->interior_rho.size () != nInt)
      {
        printf ("[FittingCurve2dSDM::assembleInterior] ERROR: size does not match\n");
      }
      else
      {
        n_prev = m_data->interior_normals[p];
        t_prev = m_data->interior_tangents[p];
        rho_prev = m_data->interior_rho[p];
        //        m_data->interior_normals[p] = n;
        //        m_data->interior_tangents[p] = t;
        //        m_data->interior_rho[p] = rho;
      }
    }
    else
    {
      m_data->interior_tangents.push_back (t);
      m_data->interior_normals.push_back (n);
      m_data->interior_rho.push_back (rho);
      n_prev = n;
      t_prev = t;
      rho_prev = rho;
    }

    double d;
    if ((pcp - pt).dot (n) >= 0.0)
    {
      d = (pcp - pt).norm ();
      i1++;
    }
    else
    {
      d = -(pcp - pt).norm ();
      i2++;
    }

    // evaluate if point lies inside or outside the closed curve
    Eigen::Vector3d a (pcp (0) - pt (0), pcp (1) - pt (1), 0.0);
    Eigen::Vector3d b (t (0), t (1), 0.0);
    Eigen::Vector3d z = a.cross (b);

    if (p < m_data->interior_weight.size ())
      wInt = m_data->interior_weight[p];

    if (p < m_data->interior_weight_function.size ())
      wFunction = m_data->interior_weight_function[p];

    m_data->interior_line_start.push_back (pt);
    m_data->interior_line_end.push_back (pcp);

    double w (wInt);
    if (z (2) > 0.0 && wFunction)
      w = wInt * exp (-(error * error) * ds);

    if (w > 1e-6) // avoids ill-conditioned matrix
      addPointConstraint (m_data->interior_param[p], m_data->interior[p], n_prev, t_prev, rho_prev, d, w, row);
  }

  //  printf("[FittingCurve2dSDM::assembleInterior] d>0: %d d<0: %d\n", i1, i2);
}