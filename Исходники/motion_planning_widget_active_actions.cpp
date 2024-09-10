    void MotionPlanningFrame::snapStateToFrame(robot_state::RobotState& state,
                                               const Eigen::Affine3d& T_frame_world,
                                               const std::string& link,
                                               const Eigen::Affine3d& T_frame_link,
                                               const std::string& group)
    {
        ROS_DEBUG_FUNCTION;

        // std::cout << "T_frame_world:\n" << T_frame_world.matrix() << std::endl;
        // std::cout << "T_frame_link:\n" << T_frame_link.matrix() << std::endl;

        // Back out the desired link transform in global coordinates.
        Eigen::Affine3d T_link_world = T_frame_world * T_frame_link.inverse();
        // Snap to the frame using IK.
        const moveit::core::JointModelGroup* jmg = state.getJointModelGroup(group);

        // std::cout << "group: " << group << std::endl;

        state.update();
        trajectory_msgs::JointTrajectoryPoint point;
        state.copyJointGroupPositions(jmg, point.positions);
        ROS_DEBUG_STREAM("pre-ik positions:\n" << point);

        geometry_msgs::Pose pose;
        tf::poseEigenToMsg(T_link_world, pose);
        state.setFromIK(jmg, pose, link);
        state.update();

        state.copyJointGroupPositions(jmg, point.positions);
        ROS_DEBUG_STREAM("post-ik positions:\n" << point);

        ROS_DEBUG_FUNCTION;
    }