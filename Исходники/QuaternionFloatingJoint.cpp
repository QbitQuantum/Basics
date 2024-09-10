void QuaternionFloatingJoint::qdot2v(const Eigen::Ref<const VectorXd>& q, Eigen::MatrixXd& qdot_to_v, Eigen::MatrixXd* dqdot_to_v) const
{
  qdot_to_v.resize(getNumVelocities(), getNumPositions());

  auto quat = q.middleRows<QUAT_SIZE>(SPACE_DIMENSION);
  Matrix3d R = quat2rotmat(quat);

  Vector4d quattilde;
  Matrix<double, SPACE_DIMENSION, QUAT_SIZE> M;
  Matrix<double, SPACE_DIMENSION, QUAT_SIZE> RTransposeM;
  Gradient<Vector4d, QUAT_SIZE, 1>::type dquattildedquat;
  if (dqdot_to_v) {
    Gradient<Vector4d, QUAT_SIZE, 2>::type ddquattildedquat;
    normalizeVec(quat, quattilde, &dquattildedquat, &ddquattildedquat);
    auto dR = dquat2rotmat(quat);
    Gradient<Matrix<double, SPACE_DIMENSION, QUAT_SIZE>, QUAT_SIZE, 1>::type dM;
    quatdot2angularvelMatrix(quat, M, &dM);

    RTransposeM.noalias() = R.transpose() * M;
    auto dRTranspose = transposeGrad(dR, R.rows());
    auto dRTransposeM = matGradMultMat(R.transpose(), M, dRTranspose, dM);
    auto dRTransposeMdquattildedquat = matGradMultMat(RTransposeM, dquattildedquat, dRTransposeM, ddquattildedquat);
    dqdot_to_v->setZero(qdot_to_v.size(), getNumPositions());
    setSubMatrixGradient<4>(*dqdot_to_v, dRTranspose, intRange<3>(3), intRange<3>(0), qdot_to_v.rows(), 3);
    setSubMatrixGradient<4>(*dqdot_to_v, dRTransposeMdquattildedquat, intRange<3>(0), intRange<4>(3), qdot_to_v.rows(), 3);
  }
  else {
    normalizeVec(quat, quattilde, &dquattildedquat);
    quatdot2angularvelMatrix(quat, M);
    RTransposeM.noalias() = R.transpose() * M;
  }
  qdot_to_v.block<3, 3>(0, 0).setZero();
  qdot_to_v.block<3, 4>(0, 3).noalias() = RTransposeM * dquattildedquat;
  qdot_to_v.block<3, 3>(3, 0) = R.transpose();
  qdot_to_v.block<3, 4>(3, 3).setZero();
}