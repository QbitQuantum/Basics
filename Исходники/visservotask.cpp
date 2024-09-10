Eigen::Vector3d VisuoServoTask::get_desired_rotation_range(){
    Eigen::Vector3d des;
    des.setZero();
    des = desired_pose_range;
    return des;
}