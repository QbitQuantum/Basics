    void XYOriginCallback(const topic_tools::ShapeShifter::ConstPtr msg)
    {
      try
      {
        const gps_common::GPSFixConstPtr origin = msg->instantiate<gps_common::GPSFix>();
        xy_wgs84_util_.reset(
            new swri_transform_util::LocalXyWgs84Util(
                origin->latitude,
                origin->longitude,
                origin->track,
                origin->altitude));
        origin_sub_.shutdown();
        return;
      }
      catch (...) {}

      try
      {
        const geometry_msgs::PoseStampedConstPtr origin = msg->instantiate<geometry_msgs::PoseStamped>();
        xy_wgs84_util_.reset(
            new swri_transform_util::LocalXyWgs84Util(
                origin->pose.position.y,    // Latitude
                origin->pose.position.x,    // Longitude
                0.0,                        // Heading
                origin->pose.position.z));  // Altitude
        origin_sub_.shutdown();
        return;
      }
      catch(...) {}

      try
      {
        const geographic_msgs::GeoPoseConstPtr origin = msg->instantiate<geographic_msgs::GeoPose>();
        xy_wgs84_util_.reset(
            new swri_transform_util::LocalXyWgs84Util(
                origin->position.latitude,
                origin->position.longitude,
                tf::getYaw(origin->orientation),
                origin->position.altitude));
        origin_sub_.shutdown();
        return;
      }
      catch(...) {}

      ROS_ERROR_THROTTLE(1.0, "Unsupported message type received for local_xy_origin.");
    }