void sptam::sptam_node::fixOdomFrame(const CameraPose& cameraPose, const tf::StampedTransform& camera_to_odom, const ros::Time& t)
{
  tf::Pose camera_to_map;
  CameraPose2TFPose( cameraPose, camera_to_map );

  // compute the new difference between map and odom
  tf::Transform odom_to_map = camera_to_map * camera_to_odom.inverse();

  std::lock_guard<std::mutex> lock( odom_to_map_mutex_ );
  odom_to_map_ = odom_to_map;
}