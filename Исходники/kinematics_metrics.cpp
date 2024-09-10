bool KinematicsMetrics::getManipulabilityIndex(const robot_state::RobotState &state,
                                               const robot_model::JointModelGroup *joint_model_group,
                                               double &manipulability_index,
                                               bool translation) const
{
  // state.getJacobian() only works for chain groups.
  if(!joint_model_group->isChain())
  {
    return false;
  }

  Eigen::MatrixXd jacobian = state.getJacobian(joint_model_group);
  // Get joint limits penalty
  double penalty = getJointLimitsPenalty(state, joint_model_group);
  if (translation)
  {
    Eigen::MatrixXd jacobian_2 = jacobian.topLeftCorner(3,jacobian.cols());
    Eigen::MatrixXd matrix = jacobian_2*jacobian_2.transpose();
    // Get manipulability index
    manipulability_index = penalty * sqrt(matrix.determinant());
  }
  else
  {
    Eigen::MatrixXd matrix = jacobian*jacobian.transpose();
    // Get manipulability index
    manipulability_index = penalty * sqrt(matrix.determinant());
  }
  return true;
}