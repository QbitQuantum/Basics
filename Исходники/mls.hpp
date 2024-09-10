pcl::MLSResult::MLSProjectionResults
pcl::MLSResult::projectPointOrthogonalToPolynomialSurface (const double u, const double v, const double w) const
{
  double gu = u;
  double gv = v;
  double gw = 0;

  MLSProjectionResults result;
  result.normal = plane_normal;
  if (order > 1 && c_vec.size () >= (order + 1) * (order + 2) / 2 && pcl_isfinite (c_vec[0]))
  {
    PolynomialPartialDerivative d = getPolynomialPartialDerivative (gu, gv);
    gw = d.z;
    double err_total;
    double dist1 = std::abs (gw - w);
    double dist2;
    do
    {
      double e1 = (gu - u) + d.z_u * gw - d.z_u * w;
      double e2 = (gv - v) + d.z_v * gw - d.z_v * w;

      double F1u = 1 + d.z_uu * gw + d.z_u * d.z_u - d.z_uu * w;
      double F1v = d.z_uv * gw + d.z_u * d.z_v - d.z_uv * w;

      double F2u = d.z_uv * gw + d.z_v * d.z_u - d.z_uv * w;
      double F2v = 1 + d.z_vv * gw + d.z_v * d.z_v - d.z_vv * w;

      Eigen::MatrixXd J (2, 2);
      J (0, 0) = F1u;
      J (0, 1) = F1v;
      J (1, 0) = F2u;
      J (1, 1) = F2v;

      Eigen::Vector2d err (e1, e2);
      Eigen::Vector2d update = J.inverse () * err;
      gu -= update (0);
      gv -= update (1);

      d = getPolynomialPartialDerivative (gu, gv);
      gw = d.z;
      dist2 = std::sqrt ((gu - u) * (gu - u) + (gv - v) * (gv - v) + (gw - w) * (gw - w));

      err_total = std::sqrt (e1 * e1 + e2 * e2);

    } while (err_total > 1e-8 && dist2 < dist1);

    if (dist2 > dist1) // the optimization was diverging reset the coordinates for simple projection
    {
      gu = u;
      gv = v;
      d = getPolynomialPartialDerivative (u, v);
      gw = d.z;
    }

    result.u = gu;
    result.v = gv;
    result.normal -= (d.z_u * u_axis + d.z_v * v_axis);
    result.normal.normalize ();
  }

  result.point = mean + gu * u_axis + gv * v_axis + gw * plane_normal;

  return (result);
}