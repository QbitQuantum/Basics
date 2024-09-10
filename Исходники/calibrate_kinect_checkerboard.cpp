 CalibrateKinectCheckerboard()
   : nh_("~"), it_(nh_), calibrated(false)
 {
   // Load parameters from the server.
   nh_.param<std::string>("fixed_frame", fixed_frame, "/base_link");
   nh_.param<std::string>("camera_frame", camera_frame, "/camera_link");
   nh_.param<std::string>("target_frame", target_frame, "/calibration_pattern");
   nh_.param<std::string>("tip_frame", tip_frame, "/gripper_link");
   
   nh_.param<int>("checkerboard_width", checkerboard_width, 6);
   nh_.param<int>("checkerboard_height", checkerboard_height, 7);
   nh_.param<double>("checkerboard_grid", checkerboard_grid, 0.027);
   
   // Set pattern detector sizes
   pattern_detector_.setPattern(cv::Size(checkerboard_width, checkerboard_height), checkerboard_grid, CHESSBOARD);
   
   transform_.translation().setZero();
   transform_.matrix().topLeftCorner<3, 3>() = Quaternionf().setIdentity().toRotationMatrix();
   
   // Create subscriptions
   info_sub_ = nh_.subscribe("/camera/rgb/camera_info", 1, &CalibrateKinectCheckerboard::infoCallback, this);
   
   // Also publishers
   pub_ = it_.advertise("calibration_pattern_out", 1);
   detector_pub_ = nh_.advertise<pcl::PointCloud<pcl::PointXYZ> >("detector_cloud", 1);
   physical_pub_ = nh_.advertise<pcl::PointCloud<pcl::PointXYZ> >("physical_points_cloud", 1);
   
   // Create ideal points
   ideal_points_.push_back( pcl::PointXYZ(0, 0, 0) );
   ideal_points_.push_back( pcl::PointXYZ((checkerboard_width-1)*checkerboard_grid, 0, 0) );
   ideal_points_.push_back( pcl::PointXYZ(0, (checkerboard_height-1)*checkerboard_grid, 0) );
   ideal_points_.push_back( pcl::PointXYZ((checkerboard_width-1)*checkerboard_grid, (checkerboard_height-1)*checkerboard_grid, 0) );
   
   // Create proper gripper tip point
   nh_.param<double>("gripper_tip_x", gripper_tip.point.x, 0.0);
   nh_.param<double>("gripper_tip_y", gripper_tip.point.y, 0.0);
   nh_.param<double>("gripper_tip_z", gripper_tip.point.z, 0.0);
   gripper_tip.header.frame_id = tip_frame;
   
   ROS_INFO("[calibrate] Initialized.");
 }