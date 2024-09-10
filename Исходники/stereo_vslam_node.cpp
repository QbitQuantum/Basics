  void imageCb(const sensor_msgs::ImageConstPtr& l_image,
               const sensor_msgs::CameraInfoConstPtr& l_cam_info,
               const sensor_msgs::ImageConstPtr& r_image,
               const sensor_msgs::CameraInfoConstPtr& r_cam_info)
  {
    ROS_INFO("In callback, seq = %u", l_cam_info->header.seq);
    
    // Convert ROS messages for use with OpenCV
    cv::Mat left, right;
    try {
      left  = l_bridge_.imgMsgToCv(l_image, "mono8");
      right = r_bridge_.imgMsgToCv(r_image, "mono8");
    }
    catch (sensor_msgs::CvBridgeException& e) {
      ROS_ERROR("Conversion error: %s", e.what());
      return;
    }
    cam_model_.fromCameraInfo(l_cam_info, r_cam_info);

    frame_common::CamParams cam_params;
    cam_params.fx = cam_model_.left().fx();
    cam_params.fy = cam_model_.left().fy();
    cam_params.cx = cam_model_.left().cx();
    cam_params.cy = cam_model_.left().cy();
    cam_params.tx = cam_model_.baseline();

    if (vslam_system_.addFrame(cam_params, left, right)) {
      /// @todo Not rely on broken encapsulation of VslamSystem here
      int size = vslam_system_.sba_.nodes.size();
      if (size % 2 == 0) {
        // publish markers
        sba::drawGraph(vslam_system_.sba_, cam_marker_pub_, point_marker_pub_);
      }

      // Publish VO tracks
      if (vo_tracks_pub_.getNumSubscribers() > 0) {
        frame_common::drawVOtracks(left, vslam_system_.vo_.frames, vo_display_);
        IplImage ipl = vo_display_;
        sensor_msgs::ImagePtr msg = sensor_msgs::CvBridge::cvToImgMsg(&ipl);
        msg->header = l_cam_info->header;
        vo_tracks_pub_.publish(msg, l_cam_info);
      }
      
      // Refine large-scale SBA.
      const int LARGE_SBA_INTERVAL = 10;
      if (size > 4 && size % LARGE_SBA_INTERVAL == 0) {
        ROS_INFO("Running large SBA on %d nodes", size);
        vslam_system_.refine();
      }
      
      if (pointcloud_pub_.getNumSubscribers() > 0 && size % 2 == 0)
        publishRegisteredPointclouds(vslam_system_.sba_, vslam_system_.frames_, pointcloud_pub_);
      
      // Publish odometry data to tf.
      if (0) // TODO: Change this to parameter.
      {
        ros::Time stamp = l_cam_info->header.stamp;
        std::string image_frame = l_cam_info->header.frame_id;
        Eigen::Vector4d trans = -vslam_system_.sba_.nodes.back().trans;
        Eigen::Quaterniond rot = vslam_system_.sba_.nodes.back().qrot.conjugate();
        
        trans.head<3>() = rot.toRotationMatrix()*trans.head<3>(); 
        
        tf_transform_.setOrigin(tf::Vector3(trans(0), trans(1), trans(2)));
        tf_transform_.setRotation(tf::Quaternion(rot.x(), rot.y(), rot.z(), rot.w()) );
        
        tf::Transform simple_transform;
        simple_transform.setOrigin(tf::Vector3(0, 0, 0));
        simple_transform.setRotation(tf::Quaternion(.5, -.5, .5, .5));
        
        tf_broadcast_.sendTransform(tf::StampedTransform(tf_transform_, stamp, image_frame, "visual_odom"));
        tf_broadcast_.sendTransform(tf::StampedTransform(simple_transform, stamp, "visual_odom", "pgraph"));
      
      
        // Publish odometry data on topic.
        if (odom_pub_.getNumSubscribers() > 0)
        {
          tf::StampedTransform base_to_image;
          tf::Transform base_to_visodom;
         
          try
          {
            tf_listener_.lookupTransform(image_frame, "/base_footprint",
                                 stamp, base_to_image);
          }
          catch (tf::TransformException ex)
          {
              ROS_WARN("%s",ex.what());
              return;
          }
                                 
          base_to_visodom = tf_transform_.inverse() * base_to_image;
          
          geometry_msgs::PoseStamped pose;
          nav_msgs::Odometry odom;
          pose.header.frame_id = "/visual_odom";
          pose.pose.position.x = base_to_visodom.getOrigin().x();
          pose.pose.position.y = base_to_visodom.getOrigin().y();
          pose.pose.position.z = base_to_visodom.getOrigin().z();
          pose.pose.orientation.x = base_to_visodom.getRotation().x();
          pose.pose.orientation.y = base_to_visodom.getRotation().y();
          pose.pose.orientation.z = base_to_visodom.getRotation().z();
          pose.pose.orientation.w = base_to_visodom.getRotation().w();
          
          odom.header.stamp = stamp;
          odom.header.frame_id = "/visual_odom";
          odom.child_frame_id = "/base_footprint";
          odom.pose.pose = pose.pose;
          /* odom.pose.covariance[0] = 1;
          odom.pose.covariance[7] = 1;
          odom.pose.covariance[14] = 1;
          odom.pose.covariance[21] = 1;
          odom.pose.covariance[28] = 1;
          odom.pose.covariance[35] = 1; */
          odom_pub_.publish(odom);
        }
      }
    }
  }