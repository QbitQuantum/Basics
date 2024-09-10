    SimObjectListener(std::string pr2_label)
    {
      pr2_transform.model_name = pr2_label;
      sim_manipulator.getModelPose(pr2_transform);
      pr2_gz_tf.setOrigin(tf::Vector3(
            pr2_transform.pose.position.x,
            pr2_transform.pose.position.y,
            pr2_transform.pose.position.z
            ));
      pr2_gz_tf.setRotation(tf::Quaternion(
          pr2_transform.pose.orientation.x,
          pr2_transform.pose.orientation.y,
          pr2_transform.pose.orientation.z,
          pr2_transform.pose.orientation.w
          ));

      ROS_INFO("%s at: [%4.2f,%4.2f,%4.2f,%4.2f,%4.2f,%4.2f,%4.2f]",
          pr2_transform.model_name.c_str(),
          pr2_transform.pose.position.x,
          pr2_transform.pose.position.y,
          pr2_transform.pose.position.z,
          pr2_transform.pose.orientation.x,
          pr2_transform.pose.orientation.y,
          pr2_transform.pose.orientation.z,
          pr2_transform.pose.orientation.w
      );
    }