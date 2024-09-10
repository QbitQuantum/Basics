void OriginSlaveWSCallback(const geometry_msgs::PoseStamped& msg){
  
  Tso.setOrigin(tf::Vector3(msg.pose.position.x, msg.pose.position.y, msg.pose.position.z));
  Tso.setRotation(tf::Quaternion(msg.pose.orientation.x, msg.pose.orientation.y, msg.pose.orientation.z, msg.pose.orientation.w));
  
  // Increments absoluts 
  Toffset = Tmo.inverse() * Tso;
  Toffset.setOrigin(tf::Vector3(0., 0., 0.));
}