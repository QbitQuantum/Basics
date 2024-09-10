void UpperBodyPlanner::pose_moveTo2(const std::string &link_name,
                                    const Eigen::Affine3d& current_pose,
                                    const Eigen::Affine3d& desired_pose, const int &step_num,
                                    std::vector<geometry_msgs::Pose> &pose_sequence) {
    //Eigen::Affine3d current_pose = kinematic_state->getGlobalLinkTransform(link_name);
    Eigen::Quaterniond current_q = Rmat2Quaternion(current_pose.rotation());
    Eigen::Quaterniond desired_q = Rmat2Quaternion(desired_pose.rotation());
    Eigen::Quaterniond step_q;

    std::cout << "**********************************" << std::endl;
    std::cout << "end_effector_name is: " << link_name << std::endl;
    std::cout << "Current translation is: " << current_pose.translation().transpose() << std::endl;
    std::cout << "current rotation is: " << std::endl;
    std::cout << current_pose.rotation() << std::endl;
    std::cout << "current quaternion is: "<< std::endl;
    std::cout << "w = " << current_q.w() << ", x = " << current_q.x() << ", y = " << current_q.y() << ", z = " << current_q.z() << std::endl;
    std::cout << "Desired translation is: " << desired_pose.translation().transpose() << std::endl;
    std::cout << "Desired rotation is: " << std::endl;
    std::cout << desired_pose.rotation() << std::endl;
    std::cout << "Desired quaternion is: " << std::endl;
    std::cout << "w = " << desired_q.w() << ", x = " << desired_q.x() << ", y = " << desired_q.y() << ", z = " << desired_q.z() << std::endl;
    std::cout << "**********************************" << std::endl;

    Eigen::Vector3d step_translation_movement = (desired_pose.translation() - current_pose.translation()) / step_num;
    for (int i = 0; i < step_num; i++) {
        Eigen::Affine3d step_target;
        step_target.translation() = current_pose.translation() + (i + 1) * step_translation_movement;
        step_q = current_q.slerp((i + 1.0) / step_num, desired_q);
        geometry_msgs::Pose target_pose = Eigen2msgPose(step_target.translation(), step_q);
        pose_sequence.push_back(target_pose);
    }
}