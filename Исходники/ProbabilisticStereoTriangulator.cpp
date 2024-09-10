void ProbabilisticStereoTriangulator<CAMERA_GEOMETRY_T>::getUncertainty(
    size_t keypointIdxA, size_t keypointIdxB,
    const Eigen::Vector4d& homogeneousPoint_A,
    Eigen::Matrix3d& outPointUOplus_A, bool& outCanBeInitialized) const {
  OKVIS_ASSERT_TRUE_DBG(Exception,frameA_&&frameB_,"initialize with frames before use!");

  // also get the point in the other coordinate representation
  //Eigen::Vector4d& homogeneousPoint_B=_T_BA*homogeneousPoint_A;
  Eigen::Vector4d hPA = homogeneousPoint_A;

  // calculate point uncertainty by constructing the lhs of the Gauss-Newton equation system.
  // note: the transformation T_WA is assumed constant and identity w.l.o.g.
  Eigen::Matrix<double, 9, 9> H = H_;

  //	keypointA_t& kptA = _frameA_ptr->keypoint(keypointIdxA);
  //	keypointB_t& kptB = _frameB_ptr->keypoint(keypointIdxB);
  Eigen::Vector2d kptA, kptB;
  frameA_->getKeypoint(camIdA_, keypointIdxA, kptA);
  frameB_->getKeypoint(camIdB_, keypointIdxB, kptB);

  // assemble the stuff from the reprojection errors
  double keypointStdDev;
  frameA_->getKeypointSize(camIdA_, keypointIdxA, keypointStdDev);
  keypointStdDev = 0.8 * keypointStdDev / 12.0;
  Eigen::Matrix2d inverseMeasurementCovariance = Eigen::Matrix2d::Identity()
      * (1.0 / (keypointStdDev * keypointStdDev));
  ::okvis::ceres::ReprojectionError<CAMERA_GEOMETRY_T> reprojectionErrorA(
      frameA_->geometryAs<CAMERA_GEOMETRY_T>(camIdA_), 0, kptA,
      inverseMeasurementCovariance);
  //typename keypointA_t::measurement_t residualA;
  Eigen::Matrix<double, 2, 1> residualA;
  Eigen::Matrix<double, 2, 4, Eigen::RowMajor> J_hpA;
  Eigen::Matrix<double, 2, 3, Eigen::RowMajor> J_hpA_min;
  double* jacobiansA[3];
  jacobiansA[0] = 0;  // do not calculate, T_WA is fixed identity transform
  jacobiansA[1] = J_hpA.data();
  jacobiansA[2] = 0;  // fixed extrinsics
  double* jacobiansA_min[3];
  jacobiansA_min[0] = 0;  // do not calculate, T_WA is fixed identity transform
  jacobiansA_min[1] = J_hpA_min.data();
  jacobiansA_min[2] = 0;  // fixed extrinsics
  const double* parametersA[3];
  //const double* test = _poseA.parameters();
  parametersA[0] = poseA_.parameters();
  parametersA[1] = hPA.data();
  parametersA[2] = extrinsics_.parameters();
  reprojectionErrorA.EvaluateWithMinimalJacobians(parametersA, residualA.data(),
                                                  jacobiansA, jacobiansA_min);

  inverseMeasurementCovariance.setIdentity();
  frameB_->getKeypointSize(camIdB_, keypointIdxB, keypointStdDev);
  keypointStdDev = 0.8 * keypointStdDev / 12.0;
  inverseMeasurementCovariance *= 1.0 / (keypointStdDev * keypointStdDev);

  ::okvis::ceres::ReprojectionError<CAMERA_GEOMETRY_T> reprojectionErrorB(
      frameB_->geometryAs<CAMERA_GEOMETRY_T>(camIdB_), 0, kptB,
      inverseMeasurementCovariance);
  Eigen::Matrix<double, 2, 1> residualB;
  Eigen::Matrix<double, 2, 7, Eigen::RowMajor> J_TB;
  Eigen::Matrix<double, 2, 6, Eigen::RowMajor> J_TB_min;
  Eigen::Matrix<double, 2, 4, Eigen::RowMajor> J_hpB;
  Eigen::Matrix<double, 2, 3, Eigen::RowMajor> J_hpB_min;
  double* jacobiansB[3];
  jacobiansB[0] = J_TB.data();
  jacobiansB[1] = J_hpB.data();
  jacobiansB[2] = 0;  // fixed extrinsics
  double* jacobiansB_min[3];
  jacobiansB_min[0] = J_TB_min.data();
  jacobiansB_min[1] = J_hpB_min.data();
  jacobiansB_min[2] = 0;  // fixed extrinsics
  const double* parametersB[3];
  parametersB[0] = poseB_.parameters();
  parametersB[1] = hPA.data();
  parametersB[2] = extrinsics_.parameters();
  reprojectionErrorB.EvaluateWithMinimalJacobians(parametersB, residualB.data(),
                                                  jacobiansB, jacobiansB_min);

  // evaluate again closer:
  hPA.head<3>() = 0.8 * (hPA.head<3>() - T_AB_.r() / 2.0 * hPA[3])
      + T_AB_.r() / 2.0 * hPA[3];
  reprojectionErrorB.EvaluateWithMinimalJacobians(parametersB, residualB.data(),
                                                  jacobiansB, jacobiansB_min);
  if (residualB.transpose() * residualB < 4.0)
    outCanBeInitialized = false;
  else
    outCanBeInitialized = true;

  // now add to H:
  H.bottomRightCorner<3, 3>() += J_hpA_min.transpose() * J_hpA_min;
  H.topLeftCorner<6, 6>() += J_TB_min.transpose() * J_TB_min;
  H.topRightCorner<6, 3>() += J_TB_min.transpose() * J_hpB_min;
  H.bottomLeftCorner<3, 6>() += J_hpB_min.transpose() * J_TB_min;
  H.bottomRightCorner<3, 3>() += J_hpB_min.transpose() * J_hpB_min;

  // invert (if invertible) to get covariance:
  Eigen::Matrix<double, 9, 9> cov;
  if (H.colPivHouseholderQr().rank() < 9) {
    outCanBeInitialized = false;
    return;
  }
  cov = H.inverse();  // FIXME: use the QR decomposition for this...
  outPointUOplus_A = cov.bottomRightCorner<3, 3>();
}