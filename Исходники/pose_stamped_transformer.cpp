 void callback(const geometry_msgs::PoseStamped::ConstPtr& in_msg)
 {
   try
   {
     geometry_msgs::PoseStamped out_msg;
     buffer_->transform(*in_msg, out_msg, frame_id_, ros::Duration(0.1));
     pub_.publish(out_msg);
   }
   catch(tf2::TransformException& ex)
   {
     ROS_ERROR("Could not transform PoseStamped. Error: %s", ex.what());
   }
 }