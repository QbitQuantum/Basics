  void scannerSignalCallback(const sensor_msgs::JointStateConstPtr& js)
  {

    double ang = fmod(js->position[0], 2 * M_PI);
    // ROS_DEBUG("ang = %lf, prev_angle = %lf, %lf", ang, prev_angle_, prev_signal_.toSec());

    if ( prev_angle_ < 0 ) {
      prev_angle_ = ang;
      return;
    }
    if ((ang - prev_angle_) >= - M_PI) {
      prev_angle_ = ang;
      return;
    }

    if (prev_signal_.toSec() == 0.0) {
      first_time_ = true;
    }

    ros::Time stmp = js->header.stamp;
    if (first_time_)
    {
      prev_signal_ = stmp;
      first_time_ = false;
    }
    else
    {
      if (num_skips_ > 0)
      {
        if (num_skips_left_ > 0)
        {
          num_skips_left_ -= 1;
          return;
        }
        else
        {
          num_skips_left_ = num_skips_;
        }
      }

      laser_assembler::AssembleScans2::Request req;
      laser_assembler::AssembleScans2::Response res;

      req.begin = prev_signal_;
      req.end   = stmp;

      if (!ros::service::call("assemble_scans2", req, res))
        ROS_ERROR("Failed to call service on point cloud assembler or laser scan assembler.");

      pub_.publish(res.cloud);
      ROS_INFO("Snapshotter::Published Cloud size=%u", res.cloud.width * res.cloud.height);

      prev_signal_ = stmp;
      prev_angle_ = -1;
    }
  }