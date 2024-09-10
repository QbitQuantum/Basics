void TonavRos::imuCallback(const sensor_msgs::ImuConstPtr &msg) {
    ROS_INFO_STREAM("Imu Seq: [" << msg->header.seq << "]");
    const std_msgs::Header header = msg->header;
    double timestamp = getMessageTime(header.stamp);
    
    Eigen::Vector3d angular_velocity;
    angular_velocity << msg->angular_velocity.x, msg->angular_velocity.y, msg->angular_velocity.z;
    Eigen::Vector3d linear_acceleration;
    linear_acceleration << msg->linear_acceleration.x, msg->linear_acceleration.y, msg->linear_acceleration.z;
    
    tonav_->updateAccelerationAndRotationRate(timestamp, angular_velocity, linear_acceleration);
}