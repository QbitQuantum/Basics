  SMRLaserNode(ros::NodeHandle& nh) :
    nh_(nh),
    scan_publisher_(nh_.advertise<sensor_msgs::LaserScan> ("/base_scan", 1)),
    conn( 3500 )
  {
    ROS_INFO("Started SMR Laser Node");

    bool result = conn.connect("192.38.66.85",24919);
    ROS_INFO("Connect %i", result);

    // todo: read all this from server
    laser_data.header.frame_id="/laser";
    //laser_data.angle_min = -120.0 / 180.0 * PI;
    //laser_data.angle_max =  120.0 / 180.0 * PI;
    //laser_data.angle_increment = (240.0 / 180.0 * PI) / 682;
    laser_data.scan_time = 0.1;
    laser_data.time_increment = 0.0;
    laser_data.range_min = 0.0;
    laser_data.range_max = 5.0;
  }