void Irp6pInverseKinematic::updateHook() {

  if (port_input_wrist_pose_.read(wrist_pose_) == RTT::NewData) {

    Eigen::Affine3d trans;
    tf::poseMsgToEigen(wrist_pose_, trans);

    port_current_joint_position_.read(local_current_joints_);

    inverse_kinematics_single_iteration(local_current_joints_, trans,
                                        &local_desired_joints_);

    port_output_joint_position_.write(local_desired_joints_);

  } else if (port_input_end_effector_pose_.read(end_effector_pose_)
      == RTT::NewData) {

    port_tool_.read(tool_msgs_);

    Eigen::Affine3d tool;
    Eigen::Affine3d trans;
    Eigen::Affine3d wrist_pose;
    tf::poseMsgToEigen(end_effector_pose_, trans);
    tf::poseMsgToEigen(tool_msgs_, tool);

    wrist_pose = trans * tool.inverse();

    port_current_joint_position_.read(local_current_joints_);

    inverse_kinematics_single_iteration(local_current_joints_, wrist_pose,
                                        &local_desired_joints_);

    port_output_joint_position_.write(local_desired_joints_);
  }
}