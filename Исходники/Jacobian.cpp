double Jacobian::getManipulabilityMeasure(const Eigen::VectorXd& joint_values)
{
  ROS_ASSERT(initialized_);

  Eigen::MatrixXd jac;

  getJacobian(joint_values, jac);

  Eigen::MatrixXd JJT = jac * jac.transpose();
  return sqrt(JJT.determinant());

}