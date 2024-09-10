kinematic_constraints::ConstraintEvaluationResult kinematic_constraints::OrientationConstraint::decide(const robot_state::RobotState &state, bool verbose) const
{
  if (!link_model_)
    return ConstraintEvaluationResult(true, 0.0);

  const robot_state::LinkState *link_state = state.getLinkState(link_model_->getName());

  if (!link_state)
  {
    logWarn("No link in state with name '%s'", link_model_->getName().c_str());
    return ConstraintEvaluationResult(false, 0.0);
  }

  Eigen::Vector3d xyz;
  if (mobile_frame_)
  {
    Eigen::Matrix3d tmp;
    tf_->transformRotationMatrix(state, desired_rotation_frame_id_, desired_rotation_matrix_, tmp);
    Eigen::Affine3d diff(tmp.inverse() * link_state->getGlobalLinkTransform().rotation());
    xyz = diff.rotation().eulerAngles(0, 1, 2);
    // 0,1,2 corresponds to ZXZ, the convention used in sampling constraints
  }
  else
  {
    Eigen::Affine3d diff(desired_rotation_matrix_inv_ * link_state->getGlobalLinkTransform().rotation());
    xyz = diff.rotation().eulerAngles(0, 1, 2); // 0,1,2 corresponds to ZXZ, the convention used in sampling constraints
  }

  xyz(0) = std::min(fabs(xyz(0)), boost::math::constants::pi<double>() - fabs(xyz(0)));
  xyz(1) = std::min(fabs(xyz(1)), boost::math::constants::pi<double>() - fabs(xyz(1)));
  xyz(2) = std::min(fabs(xyz(2)), boost::math::constants::pi<double>() - fabs(xyz(2)));
  bool result = xyz(2) < absolute_z_axis_tolerance_+std::numeric_limits<double>::epsilon()
    && xyz(1) < absolute_y_axis_tolerance_+std::numeric_limits<double>::epsilon()
    && xyz(0) < absolute_x_axis_tolerance_+std::numeric_limits<double>::epsilon();

  if (verbose)
  {
    Eigen::Quaterniond q_act(link_state->getGlobalLinkTransform().rotation());
    Eigen::Quaterniond q_des(desired_rotation_matrix_);
    logInform("Orientation constraint %s for link '%s'. Quaternion desired: %f %f %f %f, quaternion actual: %f %f %f %f, error: x=%f, y=%f, z=%f, tolerance: x=%f, y=%f, z=%f",
             result ? "satisfied" : "violated", link_model_->getName().c_str(),
             q_des.x(), q_des.y(), q_des.z(), q_des.w(),
             q_act.x(), q_act.y(), q_act.z(), q_act.w(), xyz(0), xyz(1), xyz(2),
             absolute_x_axis_tolerance_, absolute_y_axis_tolerance_, absolute_z_axis_tolerance_);
  }

  return ConstraintEvaluationResult(result, constraint_weight_ * (xyz(0) + xyz(1) + xyz(2)));
}