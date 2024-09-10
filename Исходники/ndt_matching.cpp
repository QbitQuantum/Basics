static void scan_callback(const sensor_msgs::PointCloud2::ConstPtr& input)
{
	if (map_loaded == 1 && init_pos_set == 1) {
		matching_start = std::chrono::system_clock::now();

		static tf::TransformBroadcaster br;
		tf::Transform transform;
		tf::Quaternion predict_q, ndt_q, current_q, control_q, localizer_q;

		pcl::PointXYZ p;
		pcl::PointCloud<pcl::PointXYZ> scan;

		current_scan_time = input->header.stamp;

		pcl::fromROSMsg(*input, scan);

		if(_localizer == "velodyne"){
			pcl::PointCloud<velodyne_pointcloud::PointXYZIR> tmp;
			pcl::fromROSMsg(*input, tmp);
			scan.points.clear();

			for (pcl::PointCloud<velodyne_pointcloud::PointXYZIR>::const_iterator item = tmp.begin(); item != tmp.end(); item++) {
				p.x = (double) item->x;
				p.y = (double) item->y;
				p.z = (double) item->z;
				if(item->ring >= min && item->ring <= max && item->ring % layer == 0 ){
					scan.points.push_back(p);
				}
			}
		}

		pcl::PointCloud<pcl::PointXYZ>::Ptr scan_ptr(new pcl::PointCloud<pcl::PointXYZ>(scan));
		pcl::PointCloud<pcl::PointXYZ>::Ptr filtered_scan_ptr(new pcl::PointCloud<pcl::PointXYZ>());

		Eigen::Matrix4f t(Eigen::Matrix4f::Identity()); // base_link
		Eigen::Matrix4f t2(Eigen::Matrix4f::Identity()); // localizer

		// Downsampling the velodyne scan using VoxelGrid filter
		pcl::VoxelGrid<pcl::PointXYZ> voxel_grid_filter;
		voxel_grid_filter.setLeafSize(voxel_leaf_size, voxel_leaf_size, voxel_leaf_size);
		voxel_grid_filter.setInputCloud(scan_ptr);
		voxel_grid_filter.filter(*filtered_scan_ptr);

		// Setting point cloud to be aligned.
		ndt.setInputSource(filtered_scan_ptr);

		// Guess the initial gross estimation of the transformation
		predict_pose.x = previous_pose.x + offset_x;
		predict_pose.y = previous_pose.y + offset_y;
		predict_pose.z = previous_pose.z + offset_z;
		predict_pose.roll = previous_pose.roll;
		predict_pose.pitch = previous_pose.pitch;
		predict_pose.yaw = previous_pose.yaw + offset_yaw;

		Eigen::Translation3f init_translation(predict_pose.x, predict_pose.y, predict_pose.z);
		Eigen::AngleAxisf init_rotation_x(predict_pose.roll, Eigen::Vector3f::UnitX());
		Eigen::AngleAxisf init_rotation_y(predict_pose.pitch, Eigen::Vector3f::UnitY());
		Eigen::AngleAxisf init_rotation_z(predict_pose.yaw, Eigen::Vector3f::UnitZ());
		Eigen::Matrix4f init_guess = (init_translation * init_rotation_z * init_rotation_y * init_rotation_x) * tf_btol;

		pcl::PointCloud<pcl::PointXYZ>::Ptr output_cloud(new pcl::PointCloud<pcl::PointXYZ>);
		ndt.align(*output_cloud, init_guess);

		t = ndt.getFinalTransformation(); // localizer
		t2 = t * tf_ltob; // base_link

		iteration = ndt.getFinalNumIteration();
		score = ndt.getFitnessScore();
		trans_probability = ndt.getTransformationProbability();

		tf::Matrix3x3 mat_l; // localizer
		mat_l.setValue(static_cast<double>(t(0, 0)), static_cast<double>(t(0, 1)), static_cast<double>(t(0, 2)),
				static_cast<double>(t(1, 0)), static_cast<double>(t(1, 1)), static_cast<double>(t(1, 2)),
				static_cast<double>(t(2, 0)), static_cast<double>(t(2, 1)), static_cast<double>(t(2, 2)));

		// Update ndt_pose
		localizer_pose.x = t(0, 3);
		localizer_pose.y = t(1, 3);
		localizer_pose.z = t(2, 3);
		mat_l.getRPY(localizer_pose.roll, localizer_pose.pitch, localizer_pose.yaw, 1);

		tf::Matrix3x3 mat_b; // base_link
		mat_b.setValue(static_cast<double>(t2(0, 0)), static_cast<double>(t2(0, 1)), static_cast<double>(t2(0, 2)),
				static_cast<double>(t2(1, 0)), static_cast<double>(t2(1, 1)), static_cast<double>(t2(1, 2)),
				static_cast<double>(t2(2, 0)), static_cast<double>(t2(2, 1)), static_cast<double>(t2(2, 2)));

		// Update ndt_pose
		ndt_pose.x = t2(0, 3);
		ndt_pose.y = t2(1, 3);
		ndt_pose.z = t2(2, 3);
		mat_b.getRPY(ndt_pose.roll, ndt_pose.pitch, ndt_pose.yaw, 1);

		// Compute the velocity
		scan_duration = current_scan_time - previous_scan_time;
		double secs = scan_duration.toSec();
		double distance = sqrt((ndt_pose.x - previous_pose.x) * (ndt_pose.x - previous_pose.x) +
				(ndt_pose.y - previous_pose.y) * (ndt_pose.y - previous_pose.y) +
				(ndt_pose.z - previous_pose.z) * (ndt_pose.z - previous_pose.z));

		predict_pose_error = sqrt((ndt_pose.x - predict_pose.x) * (ndt_pose.x - predict_pose.x) +
				(ndt_pose.y - predict_pose.y) * (ndt_pose.y - predict_pose.y) +
				(ndt_pose.z - predict_pose.z) * (ndt_pose.z - predict_pose.z));

		current_velocity = distance / secs;
		current_velocity_smooth = (current_velocity + previous_velocity + second_previous_velocity) / 3.0;
		if(current_velocity_smooth < 0.2){
			current_velocity_smooth = 0.0;
		}
		current_acceleration = (current_velocity - previous_velocity) / secs;

		estimated_vel_mps.data = current_velocity;
		estimated_vel_kmph.data = current_velocity * 3.6;

		estimated_vel_mps_pub.publish(estimated_vel_mps);
		estimated_vel_kmph_pub.publish(estimated_vel_kmph);

		if(predict_pose_error <= PREDICT_POSE_THRESHOLD){
			use_predict_pose = 0;
		}else{
			use_predict_pose = 1;
		}
		use_predict_pose = 0;

		if(use_predict_pose == 0){
			current_pose.x = ndt_pose.x;
			current_pose.y = ndt_pose.y;
			current_pose.z = ndt_pose.z;
			current_pose.roll = ndt_pose.roll;
			current_pose.pitch = ndt_pose.pitch;
			current_pose.yaw = ndt_pose.yaw;
		}else{
			current_pose.x = predict_pose.x;
			current_pose.y = predict_pose.y;
			current_pose.z = predict_pose.z;
			current_pose.roll = predict_pose.roll;
			current_pose.pitch = predict_pose.pitch;
			current_pose.yaw = predict_pose.yaw;
		}

		control_pose.roll = current_pose.roll;
		control_pose.pitch = current_pose.pitch;
		control_pose.yaw = current_pose.yaw - angle / 180.0 * M_PI;
		double theta = control_pose.yaw;
		control_pose.x = cos(theta) * (-control_shift_x) + sin(theta) * (-control_shift_y) + current_pose.x;
		control_pose.y = -sin(theta) * (-control_shift_x) + cos(theta) * (-control_shift_y) + current_pose.y;
		control_pose.z = current_pose.z - control_shift_z;

		// Set values for publishing pose
		predict_q.setRPY(predict_pose.roll, predict_pose.pitch, predict_pose.yaw);
		predict_pose_msg.header.frame_id = "/map";
		predict_pose_msg.header.stamp = current_scan_time;
		predict_pose_msg.pose.position.x = predict_pose.x;
		predict_pose_msg.pose.position.y = predict_pose.y;
		predict_pose_msg.pose.position.z = predict_pose.z;
		predict_pose_msg.pose.orientation.x = predict_q.x();
		predict_pose_msg.pose.orientation.y = predict_q.y();
		predict_pose_msg.pose.orientation.z = predict_q.z();
		predict_pose_msg.pose.orientation.w = predict_q.w();

		ndt_q.setRPY(ndt_pose.roll, ndt_pose.pitch, ndt_pose.yaw);
		ndt_pose_msg.header.frame_id = "/map";
		ndt_pose_msg.header.stamp = current_scan_time;
		ndt_pose_msg.pose.position.x = ndt_pose.x;
		ndt_pose_msg.pose.position.y = ndt_pose.y;
		ndt_pose_msg.pose.position.z = ndt_pose.z;
		ndt_pose_msg.pose.orientation.x = ndt_q.x();
		ndt_pose_msg.pose.orientation.y = ndt_q.y();
		ndt_pose_msg.pose.orientation.z = ndt_q.z();
		ndt_pose_msg.pose.orientation.w = ndt_q.w();

		current_q.setRPY(current_pose.roll, current_pose.pitch, current_pose.yaw);
		current_pose_msg.header.frame_id = "/map";
		current_pose_msg.header.stamp = current_scan_time;
		current_pose_msg.pose.position.x = current_pose.x;
		current_pose_msg.pose.position.y = current_pose.y;
		current_pose_msg.pose.position.z = current_pose.z;
		current_pose_msg.pose.orientation.x = current_q.x();
		current_pose_msg.pose.orientation.y = current_q.y();
		current_pose_msg.pose.orientation.z = current_q.z();
		current_pose_msg.pose.orientation.w = current_q.w();

		control_q.setRPY(control_pose.roll, control_pose.pitch, control_pose.yaw);
		control_pose_msg.header.frame_id = "/map";
		control_pose_msg.header.stamp = current_scan_time;
		control_pose_msg.pose.position.x = control_pose.x;
		control_pose_msg.pose.position.y = control_pose.y;
		control_pose_msg.pose.position.z = control_pose.z;
		control_pose_msg.pose.orientation.x = control_q.x();
		control_pose_msg.pose.orientation.y = control_q.y();
		control_pose_msg.pose.orientation.z = control_q.z();
		control_pose_msg.pose.orientation.w = control_q.w();

		localizer_q.setRPY(localizer_pose.roll, localizer_pose.pitch, localizer_pose.yaw);
		localizer_pose_msg.header.frame_id = "/map";
		localizer_pose_msg.header.stamp = current_scan_time;
		localizer_pose_msg.pose.position.x = localizer_pose.x;
		localizer_pose_msg.pose.position.y = localizer_pose.y;
		localizer_pose_msg.pose.position.z = localizer_pose.z;
		localizer_pose_msg.pose.orientation.x = localizer_q.x();
		localizer_pose_msg.pose.orientation.y = localizer_q.y();
		localizer_pose_msg.pose.orientation.z = localizer_q.z();
		localizer_pose_msg.pose.orientation.w = localizer_q.w();

		predict_pose_pub.publish(predict_pose_msg);
		ndt_pose_pub.publish(ndt_pose_msg);
		current_pose_pub.publish(current_pose_msg);
		control_pose_pub.publish(control_pose_msg);
		localizer_pose_pub.publish(localizer_pose_msg);

		// Send TF "/base_link" to "/map"
		transform.setOrigin(tf::Vector3(current_pose.x, current_pose.y, current_pose.z));
		transform.setRotation(current_q);
		br.sendTransform(tf::StampedTransform(transform, current_scan_time, "/map", "/base_link"));

		matching_end = std::chrono::system_clock::now();
		exe_time = std::chrono::duration_cast<std::chrono::microseconds>(matching_end-matching_start).count()/1000.0;
		time_ndt_matching.data = exe_time;
		time_ndt_matching_pub.publish(time_ndt_matching);

		// Set values for /estimate_twist
		angular_velocity = (current_pose.yaw - previous_pose.yaw) / secs;

		estimate_twist_msg.header.stamp = current_scan_time;
		estimate_twist_msg.twist.linear.x = current_velocity;
		estimate_twist_msg.twist.linear.y = 0.0;
		estimate_twist_msg.twist.linear.z = 0.0;
		estimate_twist_msg.twist.angular.x = 0.0;
		estimate_twist_msg.twist.angular.y = 0.0;
		estimate_twist_msg.twist.angular.z = angular_velocity;

		estimate_twist_pub.publish(estimate_twist_msg);

		geometry_msgs::Vector3Stamped estimate_vel_msg;
		estimate_vel_msg.header.stamp = current_scan_time;
		estimate_vel_msg.vector.x = current_velocity;
		estimated_vel_pub.publish(estimate_vel_msg);

		// Set values for /ndt_stat
		ndt_stat_msg.header.stamp = current_scan_time;
		ndt_stat_msg.exe_time = time_ndt_matching.data;
		ndt_stat_msg.iteration = iteration;
		ndt_stat_msg.score = score;
		ndt_stat_msg.velocity = current_velocity;
		ndt_stat_msg.acceleration = current_acceleration;
		ndt_stat_msg.use_predict_pose = 0;

		ndt_stat_pub.publish(ndt_stat_msg);

		/* Compute NDT_Reliability */
		ndt_reliability.data = Wa * (exe_time/100.0) * 100.0 + Wb * (iteration/10.0) * 100.0 + Wc * ((2.0-trans_probability)/2.0) * 100.0;
		ndt_reliability_pub.publish(ndt_reliability);

#ifdef OUTPUT
		// Output log.csv
		std::ofstream ofs_log("log.csv", std::ios::app);
		if (ofs_log == NULL) {
			std::cerr << "Could not open 'log.csv'." << std::endl;
			exit(1);
		}
		ofs_log << input->header.seq << ","
				<< step_size << ","
				<< trans_eps << ","
				<< voxel_leaf_size << ","
				<< current_pose.x << ","
				<< current_pose.y << ","
				<< current_pose.z << ","
				<< current_pose.roll << ","
				<< current_pose.pitch << ","
				<< current_pose.yaw << ","
				<< predict_pose.x << ","
				<< predict_pose.y << ","
				<< predict_pose.z << ","
				<< predict_pose.roll << ","
				<< predict_pose.pitch << ","
				<< predict_pose.yaw << ","
				<< current_pose.x - predict_pose.x << ","
				<< current_pose.y - predict_pose.y << ","
				<< current_pose.z - predict_pose.z << ","
				<< current_pose.roll - predict_pose.roll << ","
				<< current_pose.pitch - predict_pose.pitch << ","
				<< current_pose.yaw - predict_pose.yaw << ","
				<< predict_pose_error << ","
				<< iteration << ","
				<< score << ","
				<< trans_probability << ","
				<< ndt_reliability.data << ","
				<< current_velocity << ","
				<< current_velocity_smooth << ","
				<< current_acceleration << ","
				<< angular_velocity << ","
				<< time_ndt_matching.data << ","
				<< std::endl;
#endif

		std::cout << "-----------------------------------------------------------------" << std::endl;
		std::cout << "Sequence: " << input->header.seq << std::endl;
		std::cout << "Timestamp: " << input->header.stamp << std::endl;
		std::cout << "Frame ID: " << input->header.frame_id << std::endl;
		std::cout << "Number of Scan Points: " << scan_ptr->size() << " points." << std::endl;
		std::cout << "Number of Filtered Scan Points: " << filtered_scan_ptr->size() << " points." << std::endl;
		std::cout << "Leaf Size: " << voxel_leaf_size << std::endl;
		std::cout << "NDT has converged: " << ndt.hasConverged() << std::endl;
		std::cout << "Fitness Score: " << ndt.getFitnessScore() << std::endl;
		std::cout << "Transformation Probability: " << ndt.getTransformationProbability() << std::endl;
		std::cout << "Execution Time: " << exe_time << " ms." << std::endl;
		std::cout << "Number of Iterations: " << ndt.getFinalNumIteration() << std::endl;
		std::cout << "NDT Reliability: " << ndt_reliability.data << std::endl;
		std::cout << "(x,y,z,roll,pitch,yaw): " << std::endl;
		std::cout << "(" << current_pose.x << ", " << current_pose.y << ", " << current_pose.z
				<< ", " << current_pose.roll << ", " << current_pose.pitch << ", " << current_pose.yaw << ")" << std::endl;
		std::cout << "Transformation Matrix: " << std::endl;
		std::cout << t << std::endl;
		std::cout << "-----------------------------------------------------------------" << std::endl;

		// Update previous_***
		offset_x = current_pose.x - previous_pose.x;
		offset_y = current_pose.y - previous_pose.y;
		offset_z = current_pose.z - previous_pose.z;
		offset_yaw = current_pose.yaw - previous_pose.yaw;

		previous_pose.x = current_pose.x;
		previous_pose.y = current_pose.y;
		previous_pose.z = current_pose.z;
		previous_pose.roll = current_pose.roll;
		previous_pose.pitch = current_pose.pitch;
		previous_pose.yaw = current_pose.yaw;

		previous_scan_time.sec = current_scan_time.sec;
		previous_scan_time.nsec = current_scan_time.nsec;

		second_previous_velocity = previous_velocity;
		previous_velocity = current_velocity;
		previous_acceleration = current_acceleration;
		previous_estimated_vel_kmph.data = estimated_vel_kmph.data;
	}
}