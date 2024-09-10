double
FittingCurve2d::inverseMapping (const ON_NurbsCurve &nurbs, const Eigen::Vector2d &pt, const double &hint,
                                double &error, Eigen::Vector2d &p, Eigen::Vector2d &t, double rScale, int maxSteps,
                                double accuracy, bool quiet)
{
  if (nurbs.Order () == 2)
    return inverseMappingO2 (nurbs, pt, error, p, t);

  int cp_red = (nurbs.m_order - 2);
  int ncpj = (nurbs.m_cv_count - 2 * cp_red);
  double pointAndTangents[4];

  double current, delta;
  Eigen::Vector2d r;
  std::vector<double> elements = getElementVector (nurbs);
  double minU = elements[0];
  double maxU = elements[elements.size () - 1];

  current = hint;

  for (int k = 0; k < maxSteps; k++)
  {

    nurbs.Evaluate (current, 1, 2, pointAndTangents);

    p (0) = pointAndTangents[0];
    p (1) = pointAndTangents[1];

    t (0) = pointAndTangents[2];
    t (1) = pointAndTangents[3];

    r = p - pt;

    // step width control
    int E = findElement (current, elements);
    double e = elements[E + 1] - elements[E];

    delta = -(0.5 * e * rScale) * r.dot (t) / t.norm (); //  A.ldlt().solve(b);

    //    e = 0.5 * std::abs<double> (e);
    //    if (delta > e)
    //      delta = e;
    //    if (delta < -e)
    //      delta = -e;

    if (std::abs<double> (delta) < accuracy)
    {

      error = r.norm ();
      return current;

    }
    else
    {
      current = current + delta;

      if (current < minU)
        current = maxU - (minU - current);
      else if (current > maxU)
        current = minU + (current - maxU);

    }

  }

  error = r.norm ();

  if (!quiet)
  {
    printf ("[FittingCurve2d::inverseMapping] Warning: Method did not converge (%e %d).\n", accuracy, maxSteps);
    printf ("[FittingCurve2d::inverseMapping] hint: %f current: %f delta: %f error: %f\n", hint, current, delta, error);
  }

  return current;
}