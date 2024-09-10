template <typename PointSource, typename PointTarget, typename Scalar> inline void
pcl::registration::TransformationEstimationPointToPlaneLLSWeighted<PointSource, PointTarget, Scalar>::
estimateRigidTransformation (ConstCloudIterator<PointSource>& source_it,
                             ConstCloudIterator<PointTarget>& target_it,
                             typename std::vector<Scalar>::const_iterator& weights_it,
                             Matrix4 &transformation_matrix) const
{
  typedef Eigen::Matrix<double, 6, 1> Vector6d;
  typedef Eigen::Matrix<double, 6, 6> Matrix6d;

  Matrix6d ATA;
  Vector6d ATb;
  ATA.setZero ();
  ATb.setZero ();

  while (source_it.isValid () && target_it.isValid ())
  {
    if (!pcl_isfinite (source_it->x) ||
        !pcl_isfinite (source_it->y) ||
        !pcl_isfinite (source_it->z) ||
        !pcl_isfinite (target_it->x) ||
        !pcl_isfinite (target_it->y) ||
        !pcl_isfinite (target_it->z) ||
        !pcl_isfinite (target_it->normal_x) ||
        !pcl_isfinite (target_it->normal_y) ||
        !pcl_isfinite (target_it->normal_z))
    {
      ++ source_it;
      ++ target_it;
      ++ weights_it;
      continue;
    }

    const float & sx = source_it->x;
    const float & sy = source_it->y;
    const float & sz = source_it->z;
    const float & dx = target_it->x;
    const float & dy = target_it->y;
    const float & dz = target_it->z;
    const float & nx = target_it->normal[0] * (*weights_it);
    const float & ny = target_it->normal[1] * (*weights_it);
    const float & nz = target_it->normal[2] * (*weights_it);

    double a = nz*sy - ny*sz;
    double b = nx*sz - nz*sx;
    double c = ny*sx - nx*sy;

    //    0  1  2  3  4  5
    //    6  7  8  9 10 11
    //   12 13 14 15 16 17
    //   18 19 20 21 22 23
    //   24 25 26 27 28 29
    //   30 31 32 33 34 35

    ATA.coeffRef (0) += a * a;
    ATA.coeffRef (1) += a * b;
    ATA.coeffRef (2) += a * c;
    ATA.coeffRef (3) += a * nx;
    ATA.coeffRef (4) += a * ny;
    ATA.coeffRef (5) += a * nz;
    ATA.coeffRef (7) += b * b;
    ATA.coeffRef (8) += b * c;
    ATA.coeffRef (9) += b * nx;
    ATA.coeffRef (10) += b * ny;
    ATA.coeffRef (11) += b * nz;
    ATA.coeffRef (14) += c * c;
    ATA.coeffRef (15) += c * nx;
    ATA.coeffRef (16) += c * ny;
    ATA.coeffRef (17) += c * nz;
    ATA.coeffRef (21) += nx * nx;
    ATA.coeffRef (22) += nx * ny;
    ATA.coeffRef (23) += nx * nz;
    ATA.coeffRef (28) += ny * ny;
    ATA.coeffRef (29) += ny * nz;
    ATA.coeffRef (35) += nz * nz;

    double d = nx*dx + ny*dy + nz*dz - nx*sx - ny*sy - nz*sz;
    ATb.coeffRef (0) += a * d;
    ATb.coeffRef (1) += b * d;
    ATb.coeffRef (2) += c * d;
    ATb.coeffRef (3) += nx * d;
    ATb.coeffRef (4) += ny * d;
    ATb.coeffRef (5) += nz * d;

    ++ source_it;
    ++ target_it;
    ++ weights_it;
  }

  ATA.coeffRef (6) = ATA.coeff (1);
  ATA.coeffRef (12) = ATA.coeff (2);
  ATA.coeffRef (13) = ATA.coeff (8);
  ATA.coeffRef (18) = ATA.coeff (3);
  ATA.coeffRef (19) = ATA.coeff (9);
  ATA.coeffRef (20) = ATA.coeff (15);
  ATA.coeffRef (24) = ATA.coeff (4);
  ATA.coeffRef (25) = ATA.coeff (10);
  ATA.coeffRef (26) = ATA.coeff (16);
  ATA.coeffRef (27) = ATA.coeff (22);
  ATA.coeffRef (30) = ATA.coeff (5);
  ATA.coeffRef (31) = ATA.coeff (11);
  ATA.coeffRef (32) = ATA.coeff (17);
  ATA.coeffRef (33) = ATA.coeff (23);
  ATA.coeffRef (34) = ATA.coeff (29);

  // Solve A*x = b
  Vector6d x = static_cast<Vector6d> (ATA.inverse () * ATb);

  // Construct the transformation matrix from x
  constructTransformationMatrix (x (0), x (1), x (2), x (3), x (4), x (5), transformation_matrix);
}