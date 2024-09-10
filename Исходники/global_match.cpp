void laser_callback(const global_matching::GlocCloud& glocCloud) 
{

	//TODO: Map needs to be centered around with starting point at (0,0)

#ifdef ONLY_ONCE
	if(glocCloud.id > 1) {
		stop_matching = true;
		return;
	}
#endif

	if(glocCloud.id <= node_index) {
		ROS_DEBUG_STREAM("Skipping node: " << glocCloud.id);
		return;
	}
	ROS_DEBUG_STREAM("Processing node: " << glocCloud.id);
	bool match_found = false;
    pcl::fromROSMsg(glocCloud.cloud, *cloud_in);

	#ifdef VOXEL_FILTER
		sor.setInputCloud (cloud_in);
		sor.filter(*cloud_in_filt);
	#else
		cloud_in_filt = cloud_in;
		cloud_map_filt = cloud_map;
	#endif

	float cur_x = glocCloud.pose.pose.position.x;
	float cur_y =  glocCloud.pose.pose.position.y;
    float cur_yaw = tf::getYaw(glocCloud.pose.pose.orientation);

	//LOOP FOR RANDOM GUESSES
	for(int i = 0; i < ITERATIONS; i++) {
		//ROS_DEBUG_STREAM("Itertation " << i);
		//Give random initial conditions
		float dx,dy,dth;
		if(i == 0) {
			//try current pose first
			dx = cur_x; 
			dy = cur_y;
			dth = cur_yaw;
		} else {
			dx = (float)rand()/RAND_MAX*2*GUESS_DIST_RNG-GUESS_DIST_RNG + cur_x; 
			dy = (float)rand()/RAND_MAX*2*GUESS_DIST_RNG-GUESS_DIST_RNG + cur_y;
			dth = (float)rand()/RAND_MAX*GUESS_ANGLE_RNG;
		}
		trans_init << cos(dth) , -sin(dth), 0, dx,
			  sin(dth), cos(dth), 0, dy,
			  0, 0, 1, 0,
			  0, 0, 0, 1;
		pcl::transformPointCloud(*cloud_in_filt, *cloud_in_trans, trans_init);

		//Calculate gicp
		gicp.setInputCloud(cloud_in_trans);
		gicp.setInputTarget(cloud_map_filt);

		gicp.align(*cloud_final);

		float score = gicp.getFitnessScore();
		float normScore = score / cloud_in_trans->size();
		ROS_DEBUG_STREAM(" Score: " << score << " : " << normScore);

		transformation =  gicp.getFinalTransformation();
		trans_init = transformation*trans_init;

		pcl::transformPointCloud(*cloud_in, *cloud_final, trans_init);

		pcl::toROSMsg(*cloud_map_filt,ros_map);
		//pcl::toROSMsg(*cloud_in_trans,ros_guess);
		pcl::toROSMsg(*cloud_final,ros_match);
		ros_map.header.frame_id = "/nasa";
		ros_guess.header.frame_id = "/nasa";
		ros_match.header.frame_id = "/nasa";

		pub_map.publish(ros_map);
		//pub_guess.publish(ros_guess);
		pub_match.publish(ros_match);

		if(normScore < MAX_SCORE) {
			ROS_INFO_STREAM("Global Match successful");
			ROS_DEBUG_STREAM("initial: " << trans_init);

			//refine match
			gicp.setInputCloud(cloud_final);
			gicp.setInputTarget(cloud_map);

			gicp.align(*cloud_refined);

			transformation =  gicp.getFinalTransformation();
			trans_init = transformation*trans_init;

			ROS_DEBUG_STREAM("refined: " << trans_init);

			pcl::transformPointCloud(*cloud_in, *cloud_refined, trans_init);
			pcl::toROSMsg(*cloud_refined,ros_guess);
			pub_guess.publish(ros_guess);

			match_found = true;
			break;
		}

	}//END RANDOM GUESSES


	if(match_found) {
		//publish edge
		try_count = 0;
		double yaw,pitch,roll;
		graph_slam::Edge gEdge;
		gEdge.delta.x = trans_init(0,3);
		gEdge.delta.y = trans_init(1,3);
		tf::Matrix3x3 mat;
		mat[0][0] = trans_init(0,0); mat[0][1] = trans_init(0,1); mat[0][2] = trans_init(0,2);
		mat[1][0] = trans_init(1,0); mat[1][1] = trans_init(0,1); mat[1][2] = trans_init(1,2);
		mat[2][0] = trans_init(2,0); mat[2][1] = trans_init(0,1); mat[2][2] = trans_init(2,2);
    	mat.getEulerYPR(yaw, pitch, roll,1);

		gEdge.delta.theta = yaw;
		gEdge.to = glocCloud.id;
		gEdge.from = 0;
		gEdge.covariance[0] = COV_XY; gEdge.covariance[1] = 0; gEdge.covariance[2] = 0; 
		gEdge.covariance[3] = 0; gEdge.covariance[4] = COV_XY; gEdge.covariance[5] = 0; 
		gEdge.covariance[6] = 0; gEdge.covariance[7] = 0; gEdge.covariance[8] = COV_YAW; 

    	edgePub.publish(gEdge);
    	node_index = glocCloud.id;
	} else {
		try_count++;
		ROS_DEBUG_STREAM("No match found :(");
	}

	if(try_count >= MAX_TRIES) {
		//matching failed return initial guess
		ROS_WARN_STREAM("");
		graph_slam::Edge gEdge;
		gEdge.delta.x = glocCloud.pose.pose.position.x;
		gEdge.delta.y =  glocCloud.pose.pose.position.y;
    	gEdge.delta.theta = tf::getYaw(glocCloud.pose.pose.orientation);

    	gEdge.to = glocCloud.id;
		gEdge.from = 0;
		
		gEdge.covariance[0] = COV_XY; gEdge.covariance[1] = 0; gEdge.covariance[2] = 0; 
		gEdge.covariance[3] = 0; gEdge.covariance[4] = COV_XY; gEdge.covariance[5] = 0; 
		gEdge.covariance[6] = 0; gEdge.covariance[7] = 0; gEdge.covariance[8] = COV_YAW; 

    	edgePub.publish(gEdge);
    	node_index = glocCloud.id;
	}

}