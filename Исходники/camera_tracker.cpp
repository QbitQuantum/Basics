    bool
    start (camera_srv_definitions::start_tracker::Request & req,
           camera_srv_definitions::start_tracker::Response & response)
    {
        cameras_.clear();
        keyframes_.clear();
        saved_clouds_ = 0;
        conf_=0;
        pose_ = Eigen::Matrix4f::Identity();

        initializeVisualizationMarkers();

#ifdef USE_PCL_GRABBER
        try
        {
            interface.reset( new pcl::io::OpenNI2Grabber() );
        }
        catch (pcl::IOException e)
        {
            std::cout << "PCL threw error " << e.what()
                      << ". Could not start camera..." << std::endl;
            return false;
        }

        cv::Mat_<double> distCoeffs;
        cv::Mat_<double> intrinsic = cv::Mat::zeros(3, 3, CV_64F);
        intrinsic.at<double>(0,0) = 525.f;
        intrinsic.at<double>(1,1) = 525.f;
        intrinsic.at<double>(0,2) = 320.f;
        intrinsic.at<double>(1,2) = 240.f;
        intrinsic.at<double>(2,2) = 1.f;
        std::cout << intrinsic << std::endl << std::endl;

        camtracker.reset( new v4r::KeypointSlamRGBD2(param) );
        camtracker->setCameraParameter(intrinsic,distCoeffs);

        boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f =
          boost::bind (&CamTracker::cloud_cb_, this, _1);
        interface->registerCallback (f);
        interface->start ();

        std::cout << "Camera started..." << std::endl;
#else
        camera_info_subscriber_ = n_->subscribe(camera_topic_ +"/camera_info", 1, &CamTracker::camera_info_cb, this);

        ROS_INFO_STREAM("Wating for camera info...topic=" << camera_topic_ << "/camera_info...");
        while (!got_camera_info_) {
            ros::Duration(0.1).sleep();
            ros::spinOnce();
        }
        ROS_INFO("got it.");
        camera_info_subscriber_.shutdown();

        cv::Mat_<double> distCoeffs = cv::Mat(4, 1, CV_64F, camera_info_.D.data());
        cv::Mat_<double> intrinsic = cv::Mat(3, 3, CV_64F, camera_info_.K.data());

        camtracker.reset( new v4r::KeypointSlamRGBD2(param) );
        camtracker->setCameraParameter(intrinsic,distCoeffs);

        confidence_publisher_ = n_->advertise<std_msgs::Float32>("cam_tracker_confidence", 1);
        camera_topic_subscriber_ = n_->subscribe(camera_topic_ +"/points", 1, &CamTracker::getCloud, this);
#endif
        last_cloud_ = boost::posix_time::microsec_clock::local_time ();
        last_cloud_ros_time_ = ros::Time::now();
        return true;
    }