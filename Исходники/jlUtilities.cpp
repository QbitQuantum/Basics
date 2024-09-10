 void tfToPose(tf::Transform &trans, geometry_msgs::PoseStamped &msg)
 {
   tf::quaternionTFToMsg(trans.getRotation(), msg.pose.orientation);
   msg.pose.position.x = trans.getOrigin().x();
   msg.pose.position.y = trans.getOrigin().y();
   msg.pose.position.z = trans.getOrigin().z();
 }