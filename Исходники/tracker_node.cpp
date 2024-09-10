        // The real initialization is being done after receiving the camerainfo.
        void cam_info_callback(const sensor_msgs::CameraInfo &msg)
        {
            if(parent_->tracker == 0)
            {
                ROS_INFO("Camera parameters received, ready to run.");
                cam_info_sub.shutdown();
                parent_->tracker = new blort_ros::GLTracker(msg, parent_->root_, true);

                image_sub = parent_->it_.subscribe("/blort_image", 10, &TrackerNode::imageCb, parent_);
                parent_->control_service = parent_->nh_.advertiseService("tracker_control", &TrackerNode::trackerControlServiceCb, parent_);
                parent_->server_ = std::auto_ptr<dynamic_reconfigure::Server<blort_ros::TrackerConfig> >
                                   (new dynamic_reconfigure::Server<blort_ros::TrackerConfig>());
                parent_->f_ = boost::bind(&TrackerNode::TrackingMode::reconf_callback, this, _1, _2);
                parent_->server_->setCallback(parent_->f_);
                parent_->recovery_client = parent_->nh_.serviceClient<blort_ros::RecoveryCall>("/blort_detector/pose_service");
            }
        }