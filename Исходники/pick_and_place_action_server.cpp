 void sendGoalFromTopic(const geometry_msgs::PoseArrayConstPtr& msg)
 {
   ROS_INFO("[pick and place] Got goal from topic! %s", goal_->topic.c_str());
   pickAndPlace(msg->poses[0], msg->poses[1]);
   pick_and_place_sub_.shutdown();
 }