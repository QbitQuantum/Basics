bool ArmMotionInterface::unpack_goal_pose(void) {
    geometry_msgs::PoseStamped poseStamped_goal = request_.poseStamped_goal;
    Eigen::Vector3d goal_origin;
    goal_origin[0] = poseStamped_goal.pose.position.x;
    goal_origin[1] = poseStamped_goal.pose.position.y;
    goal_origin[2] = poseStamped_goal.pose.position.z;
    a_tool_end_.translation() = goal_origin;

    Eigen::Quaterniond quat;
    quat.x() = poseStamped_goal.pose.orientation.x;
    quat.y() = poseStamped_goal.pose.orientation.y;
    quat.z() = poseStamped_goal.pose.orientation.z;
    quat.w() = poseStamped_goal.pose.orientation.w;
    Eigen::Matrix3d R_goal(quat);
    a_tool_end_.linear() = R_goal;
    a_flange_end_ = a_tool_end_ * A_tool_wrt_flange_.inverse();


    return true;
}