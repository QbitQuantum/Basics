Types::Transform PointOnPlaneCalibration::estimateTransform(const std::vector<PointPlanePair> & pair_vector)
{
  const int size = pair_vector.size();

  // Point-Plane Constraints

  // Initial system (Eq. 10)

  Eigen::MatrixXd system(size, 13);
  for (int i = 0; i < size; ++i)
  {
    const double d = pair_vector[i].plane_.offset();
    const Eigen::Vector3d n = pair_vector[i].plane_.normal();

    const Types::Point3 & x = pair_vector[i].point_;

    system.row(i) <<  d + n[0] * x[0] + n[1] * x[1] + n[2] * x[2],  // q_0^2
                      2 * n[2] * x[1] - 2 * n[1] * x[2],            // q_0 * q_1
                      2 * n[0] * x[2] - 2 * n[2] * x[0],            // q_0 * q_2
                      2 * n[1] * x[0] - 2 * n[0] * x[1],            // q_0 * q_3
                      d + n[0] * x[0] - n[1] * x[1] - n[2] * x[2],  // q_1^2
                      2 * n[0] * x[1] + 2 * n[1] * x[0],            // q_1 * q_2
                      2 * n[0] * x[2] + 2 * n[2] * x[0],            // q_1 * q_3
                      d - n[0] * x[0] + n[1] * x[1] - n[2] * x[2],  // q_2^2
                      2 * n[1] * x[2] + 2 * n[2] * x[1],            // q_2 * q_3
                      d - n[0] * x[0] - n[1] * x[1] + n[2] * x[2],  // q_3^2
                      n[0], n[1], n[2]; // q'*q*t

  }

  // Gaussian reduction
  for (int k = 0; k < 3; ++k)
    for (int i = k + 1; i < size; ++i)
      system.row(i) = system.row(i) - system.row(k) * system.row(i)[10 + k] / system.row(k)[10 + k];

  // Quaternion q
  Eigen::Vector4d q;

  // Transform to inhomogeneous (Eq. 13)
  bool P_is_ok(false);
  while (not P_is_ok)
  {
    Eigen::Matrix4d P(Eigen::Matrix4d::Random());
    while (P.determinant() < 1e-5)
      P = Eigen::Matrix4d::Random();

    Eigen::MatrixXd reduced_system(size - 3, 10);
    for (int i = 3; i < size; ++i)
    {
      const Eigen::VectorXd & row = system.row(i);
      Eigen::Matrix4d Mi_tilde;

      Mi_tilde << row[0]    , row[1] / 2, row[2] / 2, row[3] / 2,
                  row[1] / 2, row[4]    , row[5] / 2, row[6] / 2,
                  row[2] / 2, row[5] / 2, row[7]    , row[8] / 2,
                  row[3] / 2, row[6] / 2, row[8] / 2, row[9]    ;

      Eigen::Matrix4d Mi_bar(P.transpose() * Mi_tilde * P);

      reduced_system.row(i - 3) << Mi_bar(0, 0),
                                   Mi_bar(0, 1) + Mi_bar(1, 0),
                                   Mi_bar(0, 2) + Mi_bar(2, 0),
                                   Mi_bar(0, 3) + Mi_bar(3, 0),
                                   Mi_bar(1, 1),
                                   Mi_bar(1, 2) + Mi_bar(2, 1),
                                   Mi_bar(1, 3) + Mi_bar(3, 1),
                                   Mi_bar(2, 2),
                                   Mi_bar(2, 3) + Mi_bar(3, 2),
                                   Mi_bar(3, 3);
    }

    // Solve  A m* = b
    Eigen::MatrixXd A = reduced_system.rightCols<9>();
    Eigen::VectorXd b = - reduced_system.leftCols<1>();
    Eigen::VectorXd m_star = A.jacobiSvd(Eigen::ComputeFullU | Eigen::ComputeFullV).solve(b);

    Eigen::Vector4d q_bar(1, m_star[0], m_star[1], m_star[2]);

    Eigen::VectorXd err(6);
    err << q_bar[1] * q_bar[1],
           q_bar[1] * q_bar[2],
           q_bar[1] * q_bar[3],
           q_bar[2] * q_bar[2],
           q_bar[2] * q_bar[3],
           q_bar[3] * q_bar[3];
    err -= m_star.tail<6>();

    //if (err.norm() < 0.1) // P is not ok?
      P_is_ok = true;

    //std::cout << m_star.transpose() << std::endl;
    //std::cout << q_bar[1] * q_bar[1] << " " << q_bar[1] * q_bar[2] << " " << q_bar[1] * q_bar[3] << " "
    //<< q_bar[2] * q_bar[2] << " " << q_bar[2] * q_bar[3] << " " << q_bar[3] * q_bar[3] << std::endl;

    q = P * q_bar;
  }

  // We want q.w > 0 (Why?)
  //if (q[0] < 0)
  //  q = -q;

  Eigen::Vector4d tmp_q(q.normalized());
  Eigen::Quaterniond rotation(tmp_q[0], tmp_q[1], tmp_q[2], tmp_q[3]);

  Eigen::VectorXd m(10);
  m << q[0] * q[0],
       q[0] * q[1],
       q[0] * q[2],
       q[0] * q[3],
       q[1] * q[1],
       q[1] * q[2],
       q[1] * q[3],
       q[2] * q[2],
       q[2] * q[3],
       q[3] * q[3];

  // Solve A (q^T q t) = b

  Eigen::Matrix3d A = system.topRightCorner<3, 3>();
  Eigen::Vector3d b = - system.topLeftCorner<3, 10>() * m;
  Eigen::Translation3d translation(A.colPivHouseholderQr().solve(b) / q.squaredNorm());

//  Eigen::Quaterniond tmp(pose.linear());
//  Eigen::Translation3d tmp2(pose.translation());
//  std::cout << "Prev: " << tmp.normalized().coeffs().transpose() << " " << tmp2.vector().transpose() << std::endl;
  //std::cout << "PoP : " << rotation.coeffs().transpose() << " " << translation.vector().transpose() << std::endl;

  return translation * rotation;
}