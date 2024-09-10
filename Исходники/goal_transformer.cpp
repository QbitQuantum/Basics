    void callback(const giskard_msgs::WholeBodyCommand::ConstPtr& in_msg)
    {
      giskard_msgs::WholeBodyCommand out_msg;

      try
      {
        buffer_->transform(in_msg->left_ee.goal_pose, out_msg.left_ee.goal_pose, frame_id_);
      }
      catch(tf2::TransformException& ex)
      {
        ROS_ERROR("Could not transform goal for left EE. Error: %s", ex.what());
        return;
      }

      try
      {
        buffer_->transform(in_msg->right_ee.goal_pose, out_msg.right_ee.goal_pose, frame_id_);
      }
      catch(tf2::TransformException& ex)
      {
        ROS_ERROR("Could not transform goal for right EE. Error: %s", ex.what());
        return;
      }

      pub_.publish(out_msg);
    }