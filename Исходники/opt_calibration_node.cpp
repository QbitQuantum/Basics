bool OPTCalibrationNode::save()
{
  // Save tfs between sensors and world coordinate system (last checherboard) to file
  std::string file_name = ros::package::getPath("opt_calibration") + "/conf/camera_poses.yaml";
  std::ofstream file;
  file.open(file_name.c_str());

  if (file.is_open())
  {
    ros::Time time = ros::Time::now();
    file << "# Auto generated file." << std::endl;
    file << "calibration_id: " << time.sec << std::endl << std::endl;

    Pose new_world_pose = Pose::Identity();

    if (world_computation_ == LAST_CHECKERBOARD)
    {
      new_world_pose = calibration_->getLastCheckerboardPose().inverse();
      for (size_t i = 0; i < sensor_vec_.size(); ++i)
      {
        const Sensor::Ptr & sensor = sensor_vec_[i];
        Pose pose = new_world_pose * sensor->pose();
        if(pose.translation().z() < 0)
        {
          ROS_INFO_STREAM("[" << sensor->frameId() << "] z < 0. Flipping /world orientation.");
          AngleAxis rotation(M_PI, Vector3(1.0, 1.0, 0.0).normalized());
          new_world_pose = rotation * calibration_->getLastCheckerboardPose().inverse();
          break;
        }
      }
    }
    else if (world_computation_ == UPDATE)
    {
      new_world_pose = fixed_sensor_pose_ * fixed_sensor_->pose().inverse();
    }

    // Write TF transforms between cameras and world frame
    file << "# Poses w.r.t. the \"world\" reference frame" << std::endl;
    file << "poses:" << std::endl;
    for (size_t i = 0; i < sensor_vec_.size(); ++i)
    {
      const Sensor::Ptr & sensor = sensor_vec_[i];

      Pose pose = new_world_pose * sensor->pose();

      file << "  " << sensor->frameId().substr(1) << ":" << std::endl;

      file << "    translation:" << std::endl
           << "      x: " << pose.translation().x() << std::endl
           << "      y: " << pose.translation().y() << std::endl
           << "      z: " << pose.translation().z() << std::endl;

      Quaternion rotation(pose.rotation());
      file << "    rotation:" << std::endl
           << "      x: " << rotation.x() << std::endl
           << "      y: " << rotation.y() << std::endl
           << "      z: " << rotation.z() << std::endl
           << "      w: " << rotation.w() << std::endl;

    }

    file << std::endl << "# Inverse poses" << std::endl;
    file << "inverse_poses:" << std::endl;
    for (size_t i = 0; i < sensor_vec_.size(); ++i)
    {
      const Sensor::Ptr & sensor = sensor_vec_[i];

      Pose pose = new_world_pose * sensor->pose();
      pose = pose.inverse();

      file << "  " << sensor->frameId().substr(1) << ":" << std::endl;

      file << "    translation:" << std::endl
           << "      x: " << pose.translation().x() << std::endl
           << "      y: " << pose.translation().y() << std::endl
           << "      z: " << pose.translation().z() << std::endl;

      Quaternion rotation(pose.rotation());
      file << "    rotation:" << std::endl
           << "      x: " << rotation.x() << std::endl
           << "      y: " << rotation.y() << std::endl
           << "      z: " << rotation.z() << std::endl
           << "      w: " << rotation.w() << std::endl;

    }

  }
  file.close();

  ROS_INFO_STREAM(file_name << " created!");

  return true;

}