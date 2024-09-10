IMPALGEBRA_BEGIN_NAMESPACE

Eigen::Matrix3d get_covariance(const Gaussian3D &g) {
  Transformation3D trans = g.get_reference_frame().get_transformation_to();
  Vector3D center = trans.get_translation();
  Vector4D iq = trans.get_rotation().get_quaternion();
  Eigen::Quaterniond q(iq[0], iq[1], iq[2], iq[3]);
  Eigen::Matrix3d rot = q.toRotationMatrix();
  Vector3D variances = g.get_variances();
  Eigen::Matrix3d rad = Eigen::Vector3d(variances[0], variances[1],
                                                variances[2]).asDiagonal();
  Eigen::Matrix3d covar = rot * (rad * rot.transpose());
  return covar;
}