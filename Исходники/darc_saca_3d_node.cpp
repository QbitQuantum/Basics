int main(int argc, char* argv[]) {
	ros::init(argc, argv, "darc_saca_3d_node");
	ros::NodeHandle nh;
	ros::Rate loop_rate(50);
	
	// desired_u and desired_yaw comes from input mapping node
	ros::Subscriber u_sub = nh.subscribe("desired_u", 1, u_callback);
	ros::Subscriber yaw_sub = nh.subscribe("desired_yaw", 1, yaw_callback);

	// laser_scan comes from vrep_lidar which reads the lidar data from vrep
	// and outputs it at the frequency of the true hardware
	//ros::Subscriber laser_scan = nh.subscribe("laser_scan",1,laser_callback);
	ros::Subscriber laser_scan = nh.subscribe("scan",1,laser_callback);

	// read the top and bottom sonar readings which will be ADC on hardware
	ros::Subscriber top_sonar = nh.subscribe("/vrep/top_sonar",1,
																					 top_sonar_callback);
	ros::Subscriber bottom_sonar = nh.subscribe("/vrep/bottom_sonar",1,
																							bottom_sonar_callback);
	
	// Publishes the quadrotor pose to the vrep visualizer
	ros::Publisher pos_pub =
		nh.advertise<geometry_msgs::Vector3>("/vrep/position", 1);
	ros::Publisher quat_pub =
		nh.advertise<geometry_msgs::Quaternion>("/vrep/quaternion", 1);
	
	// RVIZ publishers
	ros::Publisher quad_pub =
		nh.advertise<visualization_msgs::Marker>("quad_dummy_vis", 0);
	ros::Publisher init_traj_pub =
		nh.advertise<visualization_msgs::Marker>("init_traj_vis", 0);
	ros::Publisher fin_traj_pub =
		nh.advertise<visualization_msgs::Marker>("final_traj_vis", 0);
	ros::Publisher full_point_pub =
		nh.advertise<visualization_msgs::Marker>("laser_full_points_vis", 0);
	ros::Publisher seg_point_pub =
		nh.advertise<visualization_msgs::Marker>("laser_seg_points_vis", 0);
	ros::Publisher line_pub =
		nh.advertise<visualization_msgs::Marker>("laser_lines_vis",0);
	ros::Publisher mink_point_pub =
		nh.advertise<visualization_msgs::Marker>("mink_point_vis", 0);
	ros::Publisher mink_line_pub =
		nh.advertise<visualization_msgs::Marker>("mink_line_vis", 0);

	// Read in the value of hte time horizon from the launch file
	double time_horizon;
	if (nh.getParam("/time_horizon", time_horizon)) {;}
	else {
		ROS_ERROR("Set Time Horizon");
		return 0;
	}
	
	// Read in the distance threshold for the obstacle segmentation from
	// the launch file
	double distance_threshold;
	if (nh.getParam("/dist_thresh", distance_threshold)) {;}
	else {
		ROS_ERROR("Set Distance Threshold");
		return 0;
	}

	// Read in if collision avoidance or full manual
	double pca_enabled;
	if (nh.getParam("/pca_on", pca_enabled)) {;}
	else {
		ROS_ERROR("Set collision avoidance flag");
		return 0;
	}
	
	visualization_msgs::Marker quad_dummy;
	SetupQuadVisualization(quad_dummy, 0);
	visualization_msgs::Marker initial_trajectory_lines;
	SetupInitialTrajectoryVisualization(initial_trajectory_lines, 1);
	visualization_msgs::Marker final_trajectory_lines;
	SetupFinalTrajectoryVisualization(final_trajectory_lines, 2);
	visualization_msgs::Marker full_laser_points;
	SetupFullLaserVisualization(full_laser_points, 3);
	visualization_msgs::Marker seg_laser_points;
	SetupSegmentedLaserVisualization(seg_laser_points, 4);
	visualization_msgs::Marker laser_lines;
	SetupSegmentedLinesVisualization(laser_lines, 5);
	visualization_msgs::Marker mink_points;
	SetupMinkowskiPointsVisualization(mink_points, 6);
	visualization_msgs::Marker mink_lines;
	SetupMinkowskiLinesVisualization(mink_lines, 7);

	// Setup the class instance of the quadrotor for collision avoidance
	QuadrotorACA3d quad(time_horizon);
	
	QuadrotorACA3d::State x0 = QuadrotorACA3d::State::Zero();
	x0[0] = -0.3;
	x0[1] = -0.3;
	x0[2] = -2.1;
	quad.set_x(x0);
	
	std::vector<Vertex> v(9);
	std::vector<Eigen::Vector3f> n(9);
	buildObstacles(v, n, 1, 1);

	srand(time(NULL));
	ROS_ERROR("STARTING LOOP");

	float radius = quad.radius();

	std::vector<Obstacle3d> obstacle_list;
	while(ros::ok()) {
		ros::spinOnce();

		// Only process the lidar vertices if new data is received from
		// the lidar node, preventing extra computation
		if (new_data) {
			new_data = false;  // Clear data flag to prevent repeated calculations

			// Full 2d points of the laser for split-and-merge
			std::vector<Eigen::Vector2f> full_point_list; //(laser_in.ranges.size());

			// Full list of distances for clustering 
			std::vector<float> range_list; //laser_in.ranges.size());
			
			full_laser_points.points.clear();
			//float theta_rel = M_PI/4.0;
			float theta_rel = laser_in.angle_min;// - quad.est_yaw();
			
			Eigen::Vector2f tmp_point;
			for (int data_index = 0; data_index < laser_in.ranges.size();
					 ++data_index) {
			  if (laser_in.ranges[data_index] <= 3.75)
			  {
  				range_list.push_back(laser_in.ranges[data_index]);
				  
				  tmp_point[0] =  range_list.back()*cos(theta_rel);
  				tmp_point[1] = -range_list.back()*sin(theta_rel);
  				full_point_list.push_back(tmp_point);
  
  				geometry_msgs::Point laser_point;
  				laser_point.x = tmp_point[0];
  				laser_point.y = tmp_point[1];
  				laser_point.z = 0.02;
  				full_laser_points.points.push_back(laser_point);
        }
				theta_rel += laser_in.angle_increment;
			}
      //std:reverse(range_list.begin(), range_list.end());
      //std::reverse(full_laser_points.points.begin(), full_laser_points.points.end());
			// Perform the segmentation algorithm to get the reduced vertex list
			LidarSegment2d lidar_full_points(full_point_list,
																			 range_list,
																			 distance_threshold);
			std::vector<Eigen::Vector2f> lidar_segmented_points =
				lidar_full_points.segmented_points();
			
			MinkowskiSum2d minkowski_points(lidar_segmented_points, radius);
			std::vector<Eigen::Vector2f> minkowski_point_list =
				minkowski_points.ReturnMinkowskiSum();

			// Store the segmented points for rviz visualization
			seg_laser_points.points.clear();
			laser_lines.points.clear();
			mink_points.points.clear();
			mink_lines.points.clear();
			geometry_msgs::Point rviz_point;
			for (int index = 0; index < lidar_segmented_points.size(); ++index) {
				rviz_point.x = lidar_segmented_points[index][0];
				rviz_point.y = lidar_segmented_points[index][1];
				rviz_point.z = 0.05;
				seg_laser_points.points.push_back(rviz_point);
				rviz_point.z = 0.0;
				laser_lines.points.push_back(rviz_point);
			}

			for (int index = 0; index < minkowski_point_list.size(); ++index) {
				rviz_point.x = minkowski_point_list[index][0];
				rviz_point.y = minkowski_point_list[index][1];
				rviz_point.z = 0.05;
				mink_points.points.push_back(rviz_point);
				rviz_point.z = 0.0;
				mink_lines.points.push_back(rviz_point);
			}
			
#ifdef ONBOARD_SENSING
			obstacle_list.clear();
			top_sonar_dist = 2.4 - quad.true_position()[2] - quad.radius();
			bottom_sonar_dist = -quad.true_position()[2] + quad.radius();
			for (int index = 1; index < minkowski_point_list.size(); ++index) {
				// Store segmented lines as obstacles for collision avoidance
				Eigen::Vector3f tr, br, tl, bl;
				tr << minkowski_point_list[index][0],
					    minkowski_point_list[index][1],
					    top_sonar_dist;
				br << minkowski_point_list[index][0],
					    minkowski_point_list[index][1],
					    bottom_sonar_dist;
				tl << minkowski_point_list[index - 1][0],
					    minkowski_point_list[index - 1][1],
    					top_sonar_dist;
				bl << minkowski_point_list[index - 1][0],
					    minkowski_point_list[index - 1][1],
					    bottom_sonar_dist;
				Eigen::Vector3f normal = ((tr - br).cross(bl - br)).normalized();
				Obstacle3d w_a(tr, br, bl, normal);
				Obstacle3d w_b(tr, tl, bl, normal);
				obstacle_list.push_back(w_a);
				obstacle_list.push_back(w_b);
			}

			bottom_sonar_dist += radius;
			top_sonar_dist -= radius;
      // also store the "floor" and "ceiling" as a large obstacles
			Eigen::Vector3f tr; tr <<  50.0, -50.0, bottom_sonar_dist;
			Eigen::Vector3f br; br << -50.0, -50.0, bottom_sonar_dist;
			Eigen::Vector3f tl; tl <<  50.0,  50.0, bottom_sonar_dist;
			Eigen::Vector3f bl; bl << -50.0,  50.0, bottom_sonar_dist;
      Eigen::Vector3f normal;
      normal << 0,0,1;
			Obstacle3d floor_a(tr, br, bl, normal);
			Obstacle3d floor_b(tr, tl, bl, normal);
			obstacle_list.push_back(floor_a);
			obstacle_list.push_back(floor_b);
			tr <<  50.0,  50.0, top_sonar_dist - radius;
			br << -50.0,  50.0, top_sonar_dist - radius;
			tl <<  50.0, -50.0, top_sonar_dist - radius;
			bl << -50.0, -50.0, top_sonar_dist - radius;
      normal << 0,0,-1;
			Obstacle3d ceil_a(tr, br, bl, normal);
			Obstacle3d ceil_b(tr, tl, bl, normal);
			obstacle_list.push_back(ceil_a);
			obstacle_list.push_back(ceil_b);
#endif
			
      // Publish the rviz variables for the lidar
			quad_pub.publish(quad_dummy);
			full_laser_points.header.stamp = ros::Time();
			full_point_pub.publish(full_laser_points);
			seg_laser_points.header.stamp = ros::Time();
			seg_point_pub.publish(seg_laser_points);
			laser_lines.header.stamp = ros::Time();
			line_pub.publish(laser_lines);
			mink_point_pub.publish(mink_points);
			mink_line_pub.publish(mink_lines);
		}

#ifndef ONBOARD_SENSING
	  obstacle_list.clear();
		Eigen::VectorXf p = quad.true_position();
		for (int i = 0; i < 5; ++i) {
			Eigen::Vector3f noise = quad.sensing_noise();
			Eigen::Vector3f tr = v[i].tr -p + quad.sensing_noise();
			Eigen::Vector3f br = v[i].br -p + quad.sensing_noise();
			Eigen::Vector3f tl = v[i].tl -p + quad.sensing_noise();
			Eigen::Vector3f bl = v[i].bl -p + quad.sensing_noise();
			Obstacle3d w_a(tr, br, bl);
			Obstacle3d w_b(bl, tl, tr);
			obstacle_list.push_back(w_a);
			obstacle_list.push_back(w_b);
		}
#endif
		
		Eigen::Vector4f u_curr(u_goal[0], u_goal[1], u_goal[2], yaw_input);
		//Eigen::Vector4f u_curr(0.0, 0.0, 0.0, 0.0);
		nh.getParam("/pca_on", pca_enabled);
		quad.AvoidCollisions(u_curr, obstacle_list, pca_enabled);
		quad.ApplyInput();

		// Visualization trajectories
		geometry_msgs::Point tmp_point;
		std::vector<Eigen::Vector3f> init_trajectory = quad.InitialDesiredTrajectory();
		initial_trajectory_lines.points.clear();
		for (int i = 0; i < init_trajectory.size(); ++i) {
			tmp_point.x = init_trajectory[i][0];
			tmp_point.y = init_trajectory[i][1];
			tmp_point.z = init_trajectory[i][2];
			initial_trajectory_lines.points.push_back(tmp_point);
		}
		initial_trajectory_lines.header.stamp = ros::Time();
		init_traj_pub.publish(initial_trajectory_lines);

		std::vector<Eigen::Vector3f> final_trajectory = quad.FinalDesiredTrajectory();
		final_trajectory_lines.points.clear();
		for (int i = 0; i < final_trajectory.size(); ++i) {
			tmp_point.x = final_trajectory[i][0];
			tmp_point.y = final_trajectory[i][1];
			tmp_point.z = final_trajectory[i][2];
			final_trajectory_lines.points.push_back(tmp_point);
		}
		final_trajectory_lines.header.stamp = ros::Time();
		fin_traj_pub.publish(final_trajectory_lines);
			
		Eigen::Vector3f pos_curr = quad.true_position();
		geometry_msgs::Vector3 pos_out;
		pos_out.x = pos_curr[0];
		pos_out.y = pos_curr[1];
		pos_out.z = pos_curr[2];
		pos_pub.publish(pos_out);
		
		Eigen::Quaternionf q_curr = quad.true_quaternion();
		geometry_msgs::Quaternion quat_out;
		quat_out.w = q_curr.w();
		quat_out.x = q_curr.x();
		quat_out.y = q_curr.y();
		quat_out.z = q_curr.z();
		quat_pub.publish(quat_out);
		
		loop_rate.sleep();
	}
	return 0;
}