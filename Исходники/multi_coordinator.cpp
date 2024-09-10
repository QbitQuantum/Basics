    // This function is responsible for converting the data from the
    // kinect into an odometry message, and tranforming it to the same
    // frame that the ekf uses    
    void send_kinect_estimate(geometry_msgs::PointStamped pt,
			      geometry_msgs::PointStamped ptlast,
			      int index, int op)
	{
	    ROS_DEBUG("send_kinect_estimate triggered");

	    Eigen::Affine3d gwo;
	    Eigen::Vector3d tmp_point; 
	    tf::Transform transform;
	    geometry_msgs::PointStamped transpt, transptlast;
	    ros::Time tstamp = pt.header.stamp;
	    

	    // set transform parameters
	    transform.setOrigin(tf::Vector3(cal_pos(0),
					    cal_pos(1), cal_pos(2)));
	    transform.setRotation(tf::Quaternion(0,0,0,1));

	    // convert to Eigen:
	    tf::TransformTFToEigen(transform, gwo);
	    gwo = gwo.inverse();

	    tmp_point << pt.point.x, pt.point.y, pt.point.z;
	    tmp_point = gwo*tmp_point;
	    transpt.header.frame_id = "optimization_frame";
	    transpt.header.stamp = tstamp;
	    transpt.point.x = tmp_point(0);
	    transpt.point.y = tmp_point(1);
	    transpt.point.z = tmp_point(2);

	    tmp_point << ptlast.point.x, ptlast.point.y, ptlast.point.z;
	    tmp_point = gwo*tmp_point;
	    transptlast.header.frame_id = "optimization_frame";
	    transptlast.header.stamp = tstamp;
	    transptlast.point.x = tmp_point(0);
	    transptlast.point.y = tmp_point(1);
	    transptlast.point.z = tmp_point(2);
	    
	    ROS_DEBUG("Done transforming PointStamped messages");
	    // Let's first get the transform from /optimization_frame
	    // to /map
	    tf::StampedTransform trans_stamped;
	    geometry_msgs::PointStamped tmp;
	    try{
	    	tf.lookupTransform(
	    	    "map", "optimization_frame",
	    	    tstamp, trans_stamped);
	    	tf.transformPoint("map", transpt, tmp);

	    }
	    catch(tf::TransformException& ex){
	    	ROS_ERROR(
	    	    "Error trying to lookupTransform from /map "
	    	    "to /optimization_frame: %s", ex.what());
	    	return;
	    }
	    
	    // Now we can publish the Kinect's estimate of the robot's
	    // pose
	    std::stringstream ss;
	    ss << "base_footprint_kinect_robot_" << index;
	    kin_pose[index].header.stamp = ros::Time::now();
	    kin_pose[index].header.frame_id = "map";
	    kin_pose[index].child_frame_id = ss.str();
	    tmp.point.z = 0.0;
	    kin_pose[index].pose.pose.position = tmp.point;
	    double theta = 0.0;
	    if (op == 2)
	    {
	    	theta = atan2(transpt.point.x-
	    			     transptlast.point.x,
	    			     transpt.point.z-
	    			     transptlast.point.z);
	    	theta = clamp_angle(theta-M_PI/2.0);
		ROS_DEBUG("Calculated angle = %f",theta);					  
	    }
	    else
	    {
	    	theta = robot_start_ori[index];
	    	theta = clamp_angle(-theta);
		ROS_DEBUG("predetermined angle = %f",theta);
	    }
	    geometry_msgs::Quaternion quat = tf::createQuaternionMsgFromYaw(theta);
	    kin_pose[index].pose.pose.orientation = quat;

	    // Let's check if this is a "bad" point
	    if (bad_array[index])
	    {
		boost::array<double,36ul> tmpcov;
		for (int i=0; i<36; i++)
		    tmpcov[i] = kincov[i]*1000.0;
		kin_pose[index].pose.covariance = tmpcov;
	    }
	    else
		kin_pose[index].pose.covariance = kincov;
	    
	    ROS_DEBUG("Done filling in Odometry message");

	    // Now let's publish the estimated pose as a
	    // nav_msgs/Odometry message on a topic called /vo
	    ROS_DEBUG("publishing /vo for robot %d", index+1);
	    robots_pub[index].publish(kin_pose[index]);

	    // now, let's publish the transforms that goes along with it
	    geometry_msgs::TransformStamped kin_trans;
	    tf::Quaternion q1, q2;
	    q1 = tf::createQuaternionFromYaw(theta);
	    q2 = tf::Quaternion(1.0,0,0,0);
	    q1 = q1*q2;
	    tf::quaternionTFToMsg(q1, quat);

	    kin_trans.header.stamp = tstamp;
	    kin_trans.header.frame_id = kin_pose[index].header.frame_id;
	    kin_trans.child_frame_id = kin_pose[index].child_frame_id;
	    kin_trans.transform.translation.x = kin_pose[index].pose.pose.position.x;
	    kin_trans.transform.translation.y = kin_pose[index].pose.pose.position.y;
	    kin_trans.transform.translation.z = kin_pose[index].pose.pose.position.z;
	    kin_trans.transform.rotation = quat;

	    ROS_DEBUG("Sending transform for output of estimator node");
	    br.sendTransform(kin_trans);
	    
	    return;
	}