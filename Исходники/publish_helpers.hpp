void toGeometryMsg(geometry_msgs::Transform& out, const Eigen::Transform<double, 3, TransformType>& pose) {
    // convert accumulated_pose_ to transformStamped
    Eigen::Quaterniond rot_quat(pose.rotation());

    out.translation.x = pose.translation().x();
    out.translation.y = pose.translation().y();
    out.translation.z = pose.translation().z();

    out.rotation.x = rot_quat.x();
    out.rotation.y = rot_quat.y();
    out.rotation.z = rot_quat.z();
    out.rotation.w = rot_quat.w();
}