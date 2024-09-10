//Receive encoder ticks and send 'odom' and 'tf'
void robotDataCallback(std::string * data){ 
   
    if (confirm_communication){
      //ROS_INFO("Robot -- Communication OK! Received: \"%s\"", data->c_str());
      ROS_INFO("Traxbot is Streaming Data.");
      confirm_communication = false;
    }
    
    int first_at = data->find_first_of("@", 0);
    int second_at = data->find_first_of("@", first_at+1);    
    int first_comma = data->find_first_of(",", 0);
    int second_comma = data->find_first_of(",", first_comma+1);    

    //protection against broken msgs from the buffer (e.g., '@6,425@6,4250,6430e')
    if ( second_at > -1 || second_comma == -1){
      ROS_WARN("%s ::: ENCODER MSG IGNORED", data->c_str());
      return; 
    }    
    
    int left_encoder_count, right_encoder_count;	
    sscanf(data->c_str(), "@6,%d,%de", &right_encoder_count, &left_encoder_count);   //encoder msg parsing

    //protection against broken msgs from the buffer (e.g., '@6,425@6,4250,6430e')
    if ( abs(right_encoder_count) > MAX_ENCODER_COUNT || abs(left_encoder_count) > MAX_ENCODER_COUNT){
      ROS_WARN("Encoders > MAX_ENCODER_COUNT");
      return; 
    }
        
    double last_x = odometry_x_;
    double last_y = odometry_y_;
    double last_yaw = odometry_yaw_;           
    
    // It is not necessary to reset the encoders:    
    int right_enc_dif = 0, left_enc_dif = 0;    
    
    if ( right_encoder_prev >= (0.75*MAX_ENCODER_COUNT) && signof (right_encoder_count) == 0 && signof(right_encoder_prev) == 1 ){
      right_enc_dif = (MAX_ENCODER_COUNT-right_encoder_prev) + (MAX_ENCODER_COUNT+right_encoder_count);
          
    }else if (right_encoder_prev <= (-0.75*MAX_ENCODER_COUNT) && signof (right_encoder_count) == 1 && signof(right_encoder_prev) == 0){
      right_enc_dif = -(MAX_ENCODER_COUNT+right_encoder_prev) + (right_encoder_count-MAX_ENCODER_COUNT);
      
    }else{
      right_enc_dif = right_encoder_count - right_encoder_prev;
    }
    
    
    if ( left_encoder_prev >= (0.75*MAX_ENCODER_COUNT) && signof (left_encoder_count) == 0 && signof(left_encoder_prev) == 1){
      left_enc_dif = (MAX_ENCODER_COUNT-left_encoder_prev) + (MAX_ENCODER_COUNT+left_encoder_count);
      
    }else if (left_encoder_prev <= (-0.75*MAX_ENCODER_COUNT) && signof (left_encoder_count) == 1 && signof(left_encoder_prev) == 0){
      left_enc_dif = -(MAX_ENCODER_COUNT+left_encoder_prev) + (left_encoder_count-MAX_ENCODER_COUNT);
      
    }else{
      left_enc_dif = left_encoder_count - left_encoder_prev;
    }      
  
    //calulate Odometry: 
    double dist = (right_enc_dif*PULSES_TO_M + left_enc_dif*PULSES_TO_M) / 2.0; 
    double ang = (right_enc_dif*PULSES_TO_M - left_enc_dif*PULSES_TO_M) / AXLE_LENGTH;
    bool publish_info = true;

    if (right_encoder_prev == right_encoder_count && left_encoder_prev == left_encoder_count){
	publish_info = false;
    }
    
    // update previous encoder counts:
    left_encoder_prev = left_encoder_count;
    right_encoder_prev = right_encoder_count;

    // Update odometry
    odometry_yaw_ = NORMALIZE(odometry_yaw_ + ang);		// rad
    odometry_x_ = odometry_x_ + dist*cos(odometry_yaw_);	// m
    odometry_y_ = odometry_y_ + dist*sin(odometry_yaw_);	// m   
    
    last_time = current_time;
    current_time = ros::Time::now();      

    // Calculate the robot speed 
    double dt = (current_time - last_time).toSec();
    double vel_x = (odometry_x_ - last_x)/dt;
    double vel_y = (odometry_y_ - last_y)/dt;
    double vel_yaw = (odometry_yaw_ - last_yaw)/dt;    

    //Publish at least at most at 75Hz
    /*if (current_time.toSec() - 0.013 >= last_time_pub){
	publish_info = true;
    }*/
    
    //if(publish_info){

	last_time_pub = current_time.toSec();
    
	// Since all odometry is 6DOF we'll need a quaternion created from yaw    
	geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(odometry_yaw_);

	// First, we'll publish the transform over tf
	geometry_msgs::TransformStamped odom_trans;
	odom_trans.header.stamp = current_time;
	odom_trans.header.frame_id = "odom";
	odom_trans.child_frame_id = "base_link";
	    
	odom_trans.transform.translation.x = odometry_x_;
	odom_trans.transform.translation.y = odometry_y_;
	odom_trans.transform.translation.z = 0.0;
	odom_trans.transform.rotation = odom_quat;
	    
	// Send the transform
	odom_broadcaster_ptr->sendTransform(odom_trans); 		// odom->base_link transform
		
	    
	// Next, we'll publish the odometry message over ROS
	nav_msgs::Odometry odom;
	odom.header.stamp = current_time;
	odom.header.frame_id = "odom";
	    
	// Set the position
	odom.pose.pose.position.x = odometry_x_;
	odom.pose.pose.position.y = odometry_y_;
	odom.pose.pose.position.z = 0.0;
	odom.pose.pose.orientation = odom_quat;
	    
	// Set the velocity
	odom.child_frame_id = "base_link";
	odom.twist.twist.linear.x = vel_x;
	odom.twist.twist.linear.y = vel_y;
	odom.twist.twist.angular.z = vel_yaw;
	    
	// Publish the message
	odom_pub_ptr->publish(odom);		// odometry publisher 
    //} 
}