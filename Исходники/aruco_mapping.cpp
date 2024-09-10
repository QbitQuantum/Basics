bool
ArucoMapping::processImage(cv::Mat input_image,cv::Mat output_image)
{
  aruco::MarkerDetector Detector;
  std::vector<aruco::Marker> temp_markers;

  //Set visibility flag to false for all markers
  for(size_t i = 0; i < num_of_markers_; i++)
      markers_[i].visible = false;

  // Save previous marker count
  marker_counter_previous_ = marker_counter_;

  // Detect markers
  Detector.detect(input_image,temp_markers,aruco_calib_params_,marker_size_);
    
  // If no marker found, print statement
  if(temp_markers.size() == 0)
    ROS_DEBUG("No marker found!");

  //------------------------------------------------------
  // FIRST MARKER DETECTED
  //------------------------------------------------------
  if((temp_markers.size() > 0) && (first_marker_detected_ == false))
  {
    //Set flag
    first_marker_detected_=true;

    // Detect lowest marker ID
    lowest_marker_id_ = temp_markers[0].id;
    for(size_t i = 0; i < temp_markers.size();i++)
    {
      if(temp_markers[i].id < lowest_marker_id_)
        lowest_marker_id_ = temp_markers[i].id;
    }


    ROS_DEBUG_STREAM("The lowest Id marker " << lowest_marker_id_ );

    // Identify lowest marker ID with world's origin
    markers_[0].marker_id = lowest_marker_id_;

    markers_[0].geometry_msg_to_world.position.x = 0;
    markers_[0].geometry_msg_to_world.position.y = 0;
    markers_[0].geometry_msg_to_world.position.z = 0;

    markers_[0].geometry_msg_to_world.orientation.x = 0;
    markers_[0].geometry_msg_to_world.orientation.y = 0;
    markers_[0].geometry_msg_to_world.orientation.z = 0;
    markers_[0].geometry_msg_to_world.orientation.w = 1;

    // Relative position and Global position
    markers_[0].geometry_msg_to_previous.position.x = 0;
    markers_[0].geometry_msg_to_previous.position.y = 0;
    markers_[0].geometry_msg_to_previous.position.z = 0;

    markers_[0].geometry_msg_to_previous.orientation.x = 0;
    markers_[0].geometry_msg_to_previous.orientation.y = 0;
    markers_[0].geometry_msg_to_previous.orientation.z = 0;
    markers_[0].geometry_msg_to_previous.orientation.w = 1;

    // Transformation Pose to TF
    tf::Vector3 position;
    position.setX(0);
    position.setY(0);
    position.setZ(0);

    tf::Quaternion rotation;
    rotation.setX(0);
    rotation.setY(0);
    rotation.setZ(0);
    rotation.setW(1);

    markers_[0].tf_to_previous.setOrigin(position);
    markers_[0].tf_to_previous.setRotation(rotation);

    // Relative position of first marker equals Global position
    markers_[0].tf_to_world=markers_[0].tf_to_previous;

    // Increase count
    marker_counter_++;

    // Set sign of visibility of first marker
    markers_[0].visible=true;

    ROS_INFO_STREAM("First marker with ID: " << markers_[0].marker_id << " detected");

    //First marker does not have any previous marker
    markers_[0].previous_marker_id = THIS_IS_FIRST_MARKER;
  }

  //------------------------------------------------------
  // FOR EVERY MARKER DO
  //------------------------------------------------------
  for(size_t i = 0; i < temp_markers.size();i++)
  {
    int index;
    int current_marker_id = temp_markers[i].id;

    //Draw marker convex, ID, cube and axis
    temp_markers[i].draw(output_image, cv::Scalar(0,0,255),2);
    aruco::CvDrawingUtils::draw3dCube(output_image,temp_markers[i], aruco_calib_params_);
    aruco::CvDrawingUtils::draw3dAxis(output_image,temp_markers[i], aruco_calib_params_);

    // Existing marker ?
    bool existing = false;
    int temp_counter = 0;

    while((existing == false) && (temp_counter < marker_counter_))
    {
      if(markers_[temp_counter].marker_id == current_marker_id)
      {
        index = temp_counter;
        existing = true;
        ROS_DEBUG_STREAM("Existing marker with ID: " << current_marker_id << "found");
      }
        temp_counter++;
    }

    //New marker ?
    if(existing == false)
    {
      index = marker_counter_;
      markers_[index].marker_id = current_marker_id;
      existing = true;
      ROS_DEBUG_STREAM("New marker with ID: " << current_marker_id << " found");
    }

    // Change visibility flag of new marker
    for(size_t j = 0;j < marker_counter_; j++)
    {
      for(size_t k = 0;k < temp_markers.size(); k++)
      {
        if(markers_[j].marker_id == temp_markers[k].id)
          markers_[j].visible = true;
      }
    }

    //------------------------------------------------------
    // For existing marker do
    //------------------------------------------------------
    if((index < marker_counter_) && (first_marker_detected_ == true))
    {
      markers_[index].current_camera_tf = arucoMarker2Tf(temp_markers[i]);
      markers_[index].current_camera_tf = markers_[index].current_camera_tf.inverse();

      const tf::Vector3 marker_origin = markers_[index].current_camera_tf.getOrigin();
      markers_[index].current_camera_pose.position.x = marker_origin.getX();
      markers_[index].current_camera_pose.position.y = marker_origin.getY();
      markers_[index].current_camera_pose.position.z = marker_origin.getZ();

      const tf::Quaternion marker_quaternion = markers_[index].current_camera_tf.getRotation();
      markers_[index].current_camera_pose.orientation.x = marker_quaternion.getX();
      markers_[index].current_camera_pose.orientation.y = marker_quaternion.getY();
      markers_[index].current_camera_pose.orientation.z = marker_quaternion.getZ();
      markers_[index].current_camera_pose.orientation.w = marker_quaternion.getW();
    }

    //------------------------------------------------------
    // For new marker do
    //------------------------------------------------------
    if((index == marker_counter_) && (first_marker_detected_ == true))
    {
      markers_[index].current_camera_tf=arucoMarker2Tf(temp_markers[i]);

      tf::Vector3 marker_origin = markers_[index].current_camera_tf.getOrigin();
      markers_[index].current_camera_pose.position.x = marker_origin.getX();
      markers_[index].current_camera_pose.position.y = marker_origin.getY();
      markers_[index].current_camera_pose.position.z = marker_origin.getZ();

      tf::Quaternion marker_quaternion = markers_[index].current_camera_tf.getRotation();
      markers_[index].current_camera_pose.orientation.x = marker_quaternion.getX();
      markers_[index].current_camera_pose.orientation.y = marker_quaternion.getY();
      markers_[index].current_camera_pose.orientation.z = marker_quaternion.getZ();
      markers_[index].current_camera_pose.orientation.w = marker_quaternion.getW();

      // Naming - TFs
      std::stringstream camera_tf_id;
      std::stringstream camera_tf_id_old;
      std::stringstream marker_tf_id_old;

      camera_tf_id << "camera_" << index;

      // Flag to keep info if any_known marker_visible in actual image
      bool any_known_marker_visible = false;

      // Array ID of markers, which position of new marker is calculated
      int last_marker_id;

      // Testing, if is possible calculate position of a new marker to old known marker
      for(int k = 0; k < index; k++)
      {
        if((markers_[k].visible == true) && (any_known_marker_visible == false))
        {
          if(markers_[k].previous_marker_id != -1)
          {
            any_known_marker_visible = true;
            camera_tf_id_old << "camera_" << k;
            marker_tf_id_old << "marker_" << k;
            markers_[index].previous_marker_id = k;
            last_marker_id = k;
           }
         }
       }

     // New position can be calculated
     if(any_known_marker_visible == true)
     {
       // Generating TFs for listener
       for(char k = 0; k < 10; k++)
       {
         // TF from old marker and its camera
         broadcaster_.sendTransform(tf::StampedTransform(markers_[last_marker_id].current_camera_tf,ros::Time::now(),
                                                         marker_tf_id_old.str(),camera_tf_id_old.str()));

         // TF from old camera to new camera
         broadcaster_.sendTransform(tf::StampedTransform(markers_[index].current_camera_tf,ros::Time::now(),
                                                         camera_tf_id_old.str(),camera_tf_id.str()));

         ros::Duration(BROADCAST_WAIT_INTERVAL).sleep();
       }

        // Calculate TF between two markers
        listener_->waitForTransform(marker_tf_id_old.str(),camera_tf_id.str(),ros::Time(0),
                                    ros::Duration(WAIT_FOR_TRANSFORM_INTERVAL));
        try
        {
          broadcaster_.sendTransform(tf::StampedTransform(markers_[last_marker_id].current_camera_tf,ros::Time::now(),
                                                          marker_tf_id_old.str(),camera_tf_id_old.str()));

          broadcaster_.sendTransform(tf::StampedTransform(markers_[index].current_camera_tf,ros::Time::now(),
                                                          camera_tf_id_old.str(),camera_tf_id.str()));

          listener_->lookupTransform(marker_tf_id_old.str(),camera_tf_id.str(),ros::Time(0),
                                     markers_[index].tf_to_previous);
        }
        catch(tf::TransformException &e)
        {
          ROS_ERROR("Not able to lookup transform");
        }

        // Save origin and quaternion of calculated TF
        marker_origin = markers_[index].tf_to_previous.getOrigin();
        marker_quaternion = markers_[index].tf_to_previous.getRotation();

        // If plane type selected roll, pitch and Z axis are zero
        if(space_type_ == "plane")
        {
          double roll, pitch, yaw;
          tf::Matrix3x3(marker_quaternion).getRPY(roll,pitch,yaw);
          roll = 0;
          pitch = 0;
          marker_origin.setZ(0);
          marker_quaternion.setRPY(pitch,roll,yaw);
        }

        markers_[index].tf_to_previous.setRotation(marker_quaternion);
        markers_[index].tf_to_previous.setOrigin(marker_origin);

        marker_origin = markers_[index].tf_to_previous.getOrigin();
        markers_[index].geometry_msg_to_previous.position.x = marker_origin.getX();
        markers_[index].geometry_msg_to_previous.position.y = marker_origin.getY();
        markers_[index].geometry_msg_to_previous.position.z = marker_origin.getZ();

        marker_quaternion = markers_[index].tf_to_previous.getRotation();
        markers_[index].geometry_msg_to_previous.orientation.x = marker_quaternion.getX();
        markers_[index].geometry_msg_to_previous.orientation.y = marker_quaternion.getY();
        markers_[index].geometry_msg_to_previous.orientation.z = marker_quaternion.getZ();
        markers_[index].geometry_msg_to_previous.orientation.w = marker_quaternion.getW();

        // increase marker count
        marker_counter_++;

        // Invert and position of new marker to compute camera pose above it
        markers_[index].current_camera_tf = markers_[index].current_camera_tf.inverse();

        marker_origin = markers_[index].current_camera_tf.getOrigin();
        markers_[index].current_camera_pose.position.x = marker_origin.getX();
        markers_[index].current_camera_pose.position.y = marker_origin.getY();
        markers_[index].current_camera_pose.position.z = marker_origin.getZ();

        marker_quaternion = markers_[index].current_camera_tf.getRotation();
        markers_[index].current_camera_pose.orientation.x = marker_quaternion.getX();
        markers_[index].current_camera_pose.orientation.y = marker_quaternion.getY();
        markers_[index].current_camera_pose.orientation.z = marker_quaternion.getZ();
        markers_[index].current_camera_pose.orientation.w = marker_quaternion.getW();

        // Publish all TFs and markers
        publishTfs(false);
      }
    }

    //------------------------------------------------------
    // Compute global position of new marker
    //------------------------------------------------------
    if((marker_counter_previous_ < marker_counter_) && (first_marker_detected_ == true))
    {
      // Publish all TF five times for listener
      for(char k = 0; k < 5; k++)
        publishTfs(false);

      std::stringstream marker_tf_name;
      marker_tf_name << "marker_" << index;

      listener_->waitForTransform("world",marker_tf_name.str(),ros::Time(0),
                                  ros::Duration(WAIT_FOR_TRANSFORM_INTERVAL));
      try
      {
        listener_->lookupTransform("world",marker_tf_name.str(),ros::Time(0),
                                   markers_[index].tf_to_world);
      }
      catch(tf::TransformException &e)
      {
        ROS_ERROR("Not able to lookup transform");
      }

      // Saving TF to Pose
      const tf::Vector3 marker_origin = markers_[index].tf_to_world.getOrigin();
      markers_[index].geometry_msg_to_world.position.x = marker_origin.getX();
      markers_[index].geometry_msg_to_world.position.y = marker_origin.getY();
      markers_[index].geometry_msg_to_world.position.z = marker_origin.getZ();

      tf::Quaternion marker_quaternion=markers_[index].tf_to_world.getRotation();
      markers_[index].geometry_msg_to_world.orientation.x = marker_quaternion.getX();
      markers_[index].geometry_msg_to_world.orientation.y = marker_quaternion.getY();
      markers_[index].geometry_msg_to_world.orientation.z = marker_quaternion.getZ();
      markers_[index].geometry_msg_to_world.orientation.w = marker_quaternion.getW();
    }
  }

  //------------------------------------------------------
  // Compute which of visible markers is the closest to the camera
  //------------------------------------------------------
  bool any_markers_visible=false;
  int num_of_visible_markers=0;

  if(first_marker_detected_ == true)
  {
    double minimal_distance = INIT_MIN_SIZE_VALUE;
    for(int k = 0; k < num_of_markers_; k++)
    {
      double a,b,c,size;

      // If marker is visible, distance is calculated
      if(markers_[k].visible==true)
      {
        a = markers_[k].current_camera_pose.position.x;
        b = markers_[k].current_camera_pose.position.y;
        c = markers_[k].current_camera_pose.position.z;
        size = std::sqrt((a * a) + (b * b) + (c * c));
        if(size < minimal_distance)
        {
          minimal_distance = size;
          closest_camera_index_ = k;
        }

        any_markers_visible = true;
        num_of_visible_markers++;
      }
    }
  }

  //------------------------------------------------------
  // Publish all known markers
  //------------------------------------------------------
  if(first_marker_detected_ == true)
    publishTfs(true);

  //------------------------------------------------------
  // Compute global camera pose
  //------------------------------------------------------
  if((first_marker_detected_ == true) && (any_markers_visible == true))
  {
    std::stringstream closest_camera_tf_name;
    closest_camera_tf_name << "camera_" << closest_camera_index_;

    listener_->waitForTransform("world",closest_camera_tf_name.str(),ros::Time(0),
                                ros::Duration(WAIT_FOR_TRANSFORM_INTERVAL));
    try
    {
      listener_->lookupTransform("world",closest_camera_tf_name.str(),ros::Time(0),
                                 world_position_transform_);
    }
    catch(tf::TransformException &ex)
    {
      ROS_ERROR("Not able to lookup transform");
    }

    // Saving TF to Pose
    const tf::Vector3 marker_origin = world_position_transform_.getOrigin();
    world_position_geometry_msg_.position.x = marker_origin.getX();
    world_position_geometry_msg_.position.y = marker_origin.getY();
    world_position_geometry_msg_.position.z = marker_origin.getZ();

    tf::Quaternion marker_quaternion = world_position_transform_.getRotation();
    world_position_geometry_msg_.orientation.x = marker_quaternion.getX();
    world_position_geometry_msg_.orientation.y = marker_quaternion.getY();
    world_position_geometry_msg_.orientation.z = marker_quaternion.getZ();
    world_position_geometry_msg_.orientation.w = marker_quaternion.getW();
  }

  //------------------------------------------------------
  // Publish all known markers
  //------------------------------------------------------
  if(first_marker_detected_ == true)
    publishTfs(true);

  //------------------------------------------------------
  // Publish custom marker message
  //------------------------------------------------------
  aruco_mapping::ArucoMarker marker_msg;

  if((any_markers_visible == true))
  {
    marker_msg.header.stamp = ros::Time::now();
    marker_msg.header.frame_id = "world";
    marker_msg.marker_visibile = true;
    marker_msg.num_of_visible_markers = num_of_visible_markers;
    marker_msg.global_camera_pose = world_position_geometry_msg_;
    marker_msg.marker_ids.clear();
    marker_msg.global_marker_poses.clear();
    for(size_t j = 0; j < marker_counter_; j++)
    {
      if(markers_[j].visible == true)
      {
        marker_msg.marker_ids.push_back(markers_[j].marker_id);
        marker_msg.global_marker_poses.push_back(markers_[j].geometry_msg_to_world);       
      }
    }
  }
  else
  {
    marker_msg.header.stamp = ros::Time::now();
    marker_msg.header.frame_id = "world";
    marker_msg.num_of_visible_markers = num_of_visible_markers;
    marker_msg.marker_visibile = false;
    marker_msg.marker_ids.clear();
    marker_msg.global_marker_poses.clear();
  }

  // Publish custom marker msg
  marker_msg_pub_.publish(marker_msg);

  return true;
}