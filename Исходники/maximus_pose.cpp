void TeleopMaximus::get_value_and_do_computation(void) {
	float rotation = 0.0;

	if(ser_fd != -1) {
		my_maximus_pose.pose.position.x = ((float)TeleopMaximus::read_serial_port('x')) / 10000.0;
		my_maximus_pose.pose.position.y = ((float)TeleopMaximus::read_serial_port('y')) / 10000.0;
		rotation =  TeleopMaximus::read_serial_port('t');
		TeleopMaximus::rotate(0, (( (float)rotation) / 10000.0 ), 0, &my_maximus_pose);

		// reset laser scan
		//                      my_laser_scan.ranges.std::vector<float>::clear();
		// set the new values
		//my_laser_scan.ranges.std::vector<float>::push_back(((float)read_serial_port('l')) / 1000.0);
		//my_laser_scan.ranges.std::vector<float>::push_back(((float)read_serial_port('m')) / 1000.0);
		//my_laser_scan.ranges.std::vector<float>::push_back(((float)read_serial_port('r')) / 1000.0);

	}
	else {
		//TeleopMaximus::rotate(0, ((i)*3.1415/180), 0, &my_maximus_pose);
		//rotation = -((i)*3.1415/180) *10000;
		//my_maximus_pose.pose.position.y = ((float)i)/40;
		heading -= (angular_value / 120000 );
		rotation = heading *10000;
		TeleopMaximus::rotate(0, -(heading), 0, &my_maximus_pose);

		my_maximus_pose.pose.position.x += (linear_value * cos(-heading) / 100000);
		my_maximus_pose.pose.position.y += (linear_value * sin(-heading) / 100000);

	}

	// Actualize Robot's position
	my_maximus_pose.header.stamp = ros::Time::now();

	// Actualize Robot's path
	my_maximus_path.header.stamp = ros::Time::now();
	if(my_maximus_path.poses.std::vector<geometry_msgs::PoseStamped>::size() > (my_maximus_path.poses.std::vector<geometry_msgs::PoseStamped>::max_size()-2)) {
		my_maximus_path.poses.std::vector<geometry_msgs::PoseStamped>::pop_back();
	}
	my_maximus_path.poses.std::vector<geometry_msgs::PoseStamped>::push_back(my_maximus_pose);

	marker.lifetime = ros::Duration();

	// Publish the marker
	//marker.header.stamp = ros::Time::now();
	//marker_pub.publish(marker);

	transform.setOrigin( tf::Vector3(my_maximus_pose.pose.position.x, my_maximus_pose.pose.position.y, 0.0) );
	transform.setRotation( tf::Quaternion((( (float)rotation) / 10000.0 ), 0, 0) );
	br.sendTransform(tf::StampedTransform(transform, my_maximus_pose.header.stamp, "/map", "/maximus_robot_tf"));

	marker.header.stamp = ros::Time::now();

	my_laser_scan.header.stamp = ros::Time::now();

	i = i + 5;
	if( i > 180)
		i = -180;
	ROS_INFO("X=%f /Y=%f /T=%f /L=%f", my_maximus_pose.pose.position.x, my_maximus_pose.pose.position.y, my_maximus_pose.pose.orientation.z*180/3.1415, linear_value);

}