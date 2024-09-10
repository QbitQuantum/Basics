//static void velodyne_callback(const pcl::PointCloud<velodyne_pointcloud::PointXYZIR>::ConstPtr& input)
static void map_callback(const sensor_msgs::PointCloud2::ConstPtr& input)
{

  if (map_loaded == 0) {
    std::cout << "Loading map data... ";
    map.header.frame_id = "/pointcloud_map_frame";
    
    // Convert the data type(from sensor_msgs to pcl).
    pcl::fromROSMsg(*input, map);
    
    pcl::PointCloud<pcl::PointXYZI>::Ptr map_ptr(new pcl::PointCloud<pcl::PointXYZI>(map));
    // Setting point cloud to be aligned to.
    ndt.setInputTarget(map_ptr);
	
    // Setting NDT parameters to default values
    ndt.setMaximumIterations(iter);
    ndt.setResolution(ndt_res);
    ndt.setStepSize(step_size);
    ndt.setTransformationEpsilon(trans_eps);
    
    map_loaded = 1;
    std::cout << "Map Loaded." << std::endl;
  }



    if (map_loaded == 1 && init_pos_set == 1) {
        callback_start = ros::Time::now();

        static tf::TransformBroadcaster br;
        tf::Transform transform;
        tf::Quaternion q;

        tf::Quaternion q_control;

        // 1 scan
	/*
        pcl::PointCloud<pcl::PointXYZI> scan;
        pcl::PointXYZI p;
        scan.header = input->header;
        scan.header.frame_id = "velodyne_scan_frame";
	*/

        ros::Time scan_time;
        scan_time.sec = additional_map.header.stamp / 1000000.0;
        scan_time.nsec = (additional_map.header.stamp - scan_time.sec * 1000000.0) * 1000.0;

        /*
         std::cout << "scan.header.stamp: " << scan.header.stamp << std::endl;
         std::cout << "scan_time: " << scan_time << std::endl;
         std::cout << "scan_time.sec: " << scan_time.sec << std::endl;
         std::cout << "scan_time.nsec: " << scan_time.nsec << std::endl;
         */

        t1_start = ros::Time::now();
	/*
        for (pcl::PointCloud<velodyne_pointcloud::PointXYZIR>::const_iterator item = input->begin(); item != input->end(); item++) {
            p.x = (double) item->x;
            p.y = (double) item->y;
            p.z = (double) item->z;

            scan.points.push_back(p);
        }
	*/
	//	pcl::fromROSMsg(*input, scan);
        t1_end = ros::Time::now();
        d1 = t1_end - t1_start;

        Eigen::Matrix4f t(Eigen::Matrix4f::Identity());

	//        pcl::PointCloud<pcl::PointXYZI>::Ptr scan_ptr(new pcl::PointCloud<pcl::PointXYZI>(scan));
        pcl::PointCloud<pcl::PointXYZI>::Ptr filtered_additional_map_ptr(new pcl::PointCloud<pcl::PointXYZI>);

        // Downsampling the velodyne scan using VoxelGrid filter
        t2_start = ros::Time::now();
        pcl::VoxelGrid<pcl::PointXYZI> voxel_grid_filter;
        voxel_grid_filter.setLeafSize(voxel_leaf_size, voxel_leaf_size, voxel_leaf_size);
        voxel_grid_filter.setInputCloud(additional_map_ptr);
        voxel_grid_filter.filter(*filtered_additional_map_ptr);
        t2_end = ros::Time::now();
        d2 = t2_end - t2_start;

        // Setting point cloud to be aligned.
        ndt.setInputSource(filtered_additional_map_ptr);

        // Guess the initial gross estimation of the transformation
        t3_start = ros::Time::now();
        tf::Matrix3x3 init_rotation;

        guess_pos.x = previous_pos.x + offset_x;
        guess_pos.y = previous_pos.y + offset_y;
        guess_pos.z = previous_pos.z + offset_z;
        guess_pos.roll = previous_pos.roll;
        guess_pos.pitch = previous_pos.pitch;
        guess_pos.yaw = previous_pos.yaw + offset_yaw;

        Eigen::AngleAxisf init_rotation_x(guess_pos.roll, Eigen::Vector3f::UnitX());
        Eigen::AngleAxisf init_rotation_y(guess_pos.pitch, Eigen::Vector3f::UnitY());
        Eigen::AngleAxisf init_rotation_z(guess_pos.yaw, Eigen::Vector3f::UnitZ());

        Eigen::Translation3f init_translation(guess_pos.x, guess_pos.y, guess_pos.z);

        Eigen::Matrix4f init_guess = (init_translation * init_rotation_z * init_rotation_y * init_rotation_x).matrix();

        t3_end = ros::Time::now();
        d3 = t3_end - t3_start;

        t4_start = ros::Time::now();
        pcl::PointCloud<pcl::PointXYZI>::Ptr output_cloud(new pcl::PointCloud<pcl::PointXYZI>);
        ndt.align(*output_cloud, init_guess);

        t = ndt.getFinalTransformation();
	pcl::PointCloud<pcl::PointXYZI>::Ptr transformed_additional_map_ptr (new pcl::PointCloud<pcl::PointXYZI>());
	transformed_additional_map_ptr->header.frame_id = "/map";
	pcl::transformPointCloud(*additional_map_ptr, *transformed_additional_map_ptr, t);
	sensor_msgs::PointCloud2::Ptr msg_ptr(new sensor_msgs::PointCloud2);

	pcl::toROSMsg(*transformed_additional_map_ptr, *msg_ptr);
	msg_ptr->header.frame_id = "/map";
	ndt_map_pub.publish(*msg_ptr);

	// Writing Point Cloud data to PCD file
	pcl::io::savePCDFileASCII("global_map.pcd", *transformed_additional_map_ptr);
	std::cout << "Saved " << transformed_additional_map_ptr->points.size() << " data points to global_map.pcd." << std::endl;

	pcl::PointCloud<pcl::PointXYZRGB> output;
	output.width = transformed_additional_map_ptr->width;
	output.height = transformed_additional_map_ptr->height;
	output.points.resize(output.width * output.height);

	for(size_t i = 0; i < output.points.size(); i++){
	  output.points[i].x = transformed_additional_map_ptr->points[i].x;
	  output.points[i].y = transformed_additional_map_ptr->points[i].y;
	  output.points[i].z = transformed_additional_map_ptr->points[i].z;
	  output.points[i].rgb = 255 << 8;
	}

	pcl::io::savePCDFileASCII("global_map_rgb.pcd", output);
	std::cout << "Saved " << output.points.size() << " data points to global_map_rgb.pcd." << std::endl;

        t4_end = ros::Time::now();
        d4 = t4_end - t4_start;

        t5_start = ros::Time::now();
        /*
         tf::Vector3 origin;
         origin.setValue(static_cast<double>(t(0,3)), static_cast<double>(t(1,3)), static_cast<double>(t(2,3)));
         */

        tf::Matrix3x3 tf3d;

        tf3d.setValue(static_cast<double>(t(0, 0)), static_cast<double>(t(0, 1)), static_cast<double>(t(0, 2)), static_cast<double>(t(1, 0)), static_cast<double>(t(1, 1)), static_cast<double>(t(1, 2)), static_cast<double>(t(2, 0)), static_cast<double>(t(2, 1)), static_cast<double>(t(2, 2)));

        // Update current_pos.
        current_pos.x = t(0, 3);
        current_pos.y = t(1, 3);
        current_pos.z = t(2, 3);
        tf3d.getRPY(current_pos.roll, current_pos.pitch, current_pos.yaw, 1);

	// control_pose
	current_pos_control.roll = current_pos.roll;
	current_pos_control.pitch = current_pos.pitch;
	current_pos_control.yaw = current_pos.yaw - angle / 180.0 * M_PI;
	double theta = current_pos_control.yaw;
	current_pos_control.x = cos(theta) * (-control_shift_x) + sin(theta) * (-control_shift_y) + current_pos.x;
	current_pos_control.y = -sin(theta) * (-control_shift_x) + cos(theta) * (-control_shift_y) + current_pos.y;
	current_pos_control.z = current_pos.z - control_shift_z;

        // transform "/velodyne" to "/map"
#if 0
        transform.setOrigin(tf::Vector3(current_pos.x, current_pos.y, current_pos.z));
        q.setRPY(current_pos.roll, current_pos.pitch, current_pos.yaw);
        transform.setRotation(q);
#else
	//
	// FIXME:
	// We corrected the angle of "/velodyne" so that pure_pursuit
	// can read this frame for the control.
	// However, this is not what we want because the scan of Velodyne
	// looks unmatched for the 3-D map on Rviz.
	// What we really want is to make another TF transforming "/velodyne"
	// to a new "/ndt_points" frame and modify pure_pursuit to
	// read this frame instead of "/velodyne".
	// Otherwise, can pure_pursuit just use "/ndt_frame"?
	//
        transform.setOrigin(tf::Vector3(current_pos_control.x, current_pos_control.y, current_pos_control.z));
        q.setRPY(current_pos_control.roll, current_pos_control.pitch, current_pos_control.yaw);
        transform.setRotation(q);
#endif

	q_control.setRPY(current_pos_control.roll, current_pos_control.pitch, current_pos_control.yaw);

        /*
         std::cout << "ros::Time::now(): " << ros::Time::now() << std::endl;
         std::cout << "ros::Time::now().sec: " << ros::Time::now().sec << std::endl;
         std::cout << "ros::Time::now().nsec: " << ros::Time::now().nsec << std::endl;
         */

	//        br.sendTransform(tf::StampedTransform(transform, scan_time, "map", "velodyne"));

        static tf::TransformBroadcaster pose_broadcaster;
        tf::Transform pose_transform;
        tf::Quaternion pose_q;

/*        pose_transform.setOrigin(tf::Vector3(0, 0, 0));
        pose_q.setRPY(0, 0, 0);
        pose_transform.setRotation(pose_q);
        pose_broadcaster.sendTransform(tf::StampedTransform(pose_transform, scan_time, "map", "ndt_frame"));
*/
        // publish the position
       // ndt_pose_msg.header.frame_id = "/ndt_frame";
        ndt_pose_msg.header.frame_id = "/map";
        ndt_pose_msg.header.stamp = scan_time;
        ndt_pose_msg.pose.position.x = current_pos.x;
        ndt_pose_msg.pose.position.y = current_pos.y;
        ndt_pose_msg.pose.position.z = current_pos.z;
        ndt_pose_msg.pose.orientation.x = q.x();
        ndt_pose_msg.pose.orientation.y = q.y();
        ndt_pose_msg.pose.orientation.z = q.z();
        ndt_pose_msg.pose.orientation.w = q.w();

        static tf::TransformBroadcaster pose_broadcaster_control;
        tf::Transform pose_transform_control;
        tf::Quaternion pose_q_control;

     /*   pose_transform_control.setOrigin(tf::Vector3(0, 0, 0));
        pose_q_control.setRPY(0, 0, 0);
        pose_transform_control.setRotation(pose_q_control);
        pose_broadcaster_control.sendTransform(tf::StampedTransform(pose_transform_control, scan_time, "map", "ndt_frame"));
*/
        // publish the position
     //   control_pose_msg.header.frame_id = "/ndt_frame";
        control_pose_msg.header.frame_id = "/map";
        control_pose_msg.header.stamp = scan_time;
        control_pose_msg.pose.position.x = current_pos_control.x;
        control_pose_msg.pose.position.y = current_pos_control.y;
        control_pose_msg.pose.position.z = current_pos_control.z;
        control_pose_msg.pose.orientation.x = q_control.x();
        control_pose_msg.pose.orientation.y = q_control.y();
        control_pose_msg.pose.orientation.z = q_control.z();
        control_pose_msg.pose.orientation.w = q_control.w();

        /*
         std::cout << "ros::Time::now(): " << ros::Time::now() << std::endl;
         std::cout << "ros::Time::now().sec: " << ros::Time::now().sec << std::endl;
         std::cout << "ros::Time::now().nsec: " << ros::Time::now().nsec << std::endl;
         */

        ndt_pose_pub.publish(ndt_pose_msg);
        control_pose_pub.publish(control_pose_msg);

        t5_end = ros::Time::now();
        d5 = t5_end - t5_start;

#ifdef OUTPUT
        // Writing position to position_log.txt
        std::ofstream ofs("position_log.txt", std::ios::app);
        if (ofs == NULL) {
            std::cerr << "Could not open 'position_log.txt'." << std::endl;
            exit(1);
        }
        ofs << current_pos.x << " " << current_pos.y << " " << current_pos.z << " " << current_pos.roll << " " << current_pos.pitch << " " << current_pos.yaw << std::endl;
#endif

        // Calculate the offset (curren_pos - previous_pos)
        offset_x = current_pos.x - previous_pos.x;
        offset_y = current_pos.y - previous_pos.y;
        offset_z = current_pos.z - previous_pos.z;
        offset_yaw = current_pos.yaw - previous_pos.yaw;

        // Update position and posture. current_pos -> previous_pos
        previous_pos.x = current_pos.x;
        previous_pos.y = current_pos.y;
        previous_pos.z = current_pos.z;
        previous_pos.roll = current_pos.roll;
        previous_pos.pitch = current_pos.pitch;
        previous_pos.yaw = current_pos.yaw;

        callback_end = ros::Time::now();
        d_callback = callback_end - callback_start;

        std::cout << "-----------------------------------------------------------------" << std::endl;
        std::cout << "Sequence number: " << input->header.seq << std::endl;
        std::cout << "Number of scan points: " << additional_map_ptr->size() << " points." << std::endl;
        std::cout << "Number of filtered scan points: " << filtered_additional_map_ptr->size() << " points." << std::endl;
        std::cout << "NDT has converged: " << ndt.hasConverged() << std::endl;
        std::cout << "Fitness score: " << ndt.getFitnessScore() << std::endl;
        std::cout << "Number of iteration: " << ndt.getFinalNumIteration() << std::endl;
        std::cout << "(x,y,z,roll,pitch,yaw):" << std::endl;
        std::cout << "(" << current_pos.x << ", " << current_pos.y << ", " << current_pos.z << ", " << current_pos.roll << ", " << current_pos.pitch << ", " << current_pos.yaw << ")" << std::endl;
        std::cout << "Transformation Matrix:" << std::endl;
        std::cout << t << std::endl;
#ifdef VIEW_TIME
        std::cout << "Duration of velodyne_callback: " << d_callback.toSec() << " secs." << std::endl;
        std::cout << "Adding scan points: " << d1.toSec() << " secs." << std::endl;
        std::cout << "VoxelGrid Filter: " << d2.toSec() << " secs." << std::endl;
        std::cout << "Guessing the initial gross estimation: " << d3.toSec() << " secs." << std::endl;
        std::cout << "NDT: " << d4.toSec() << " secs." << std::endl;
        std::cout << "tf: " << d5.toSec() << " secs." << std::endl;
#endif
        std::cout << "-----------------------------------------------------------------" << std::endl;
    }
}