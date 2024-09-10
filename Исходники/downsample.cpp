	void point_cb(const sensor_msgs::PointCloud2ConstPtr& cloud_msg){

		pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2;
		pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);
		pcl::PCLPointCloud2 cloud_filtered;

		pcl_conversions::toPCL(*cloud_msg, *cloud);

		pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
		sor.setInputCloud(cloudPtr);

		float leaf = 0.005;
		sor.setLeafSize(leaf, leaf, leaf);
		sor.filter(cloud_filtered);

		sensor_msgs::PointCloud2 sensor_pcl;


		pcl_conversions::moveFromPCL(cloud_filtered, sensor_pcl);
		//publish pcl data 
		pub_voxel.publish(sensor_pcl);
		global_counter++;


		if((theta == 0.0 && y_offset == 0.0) || global_counter < 800 ){

		// part for planar segmentation starts here  ..
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1(new pcl::PointCloud<pcl::PointXYZ>), cloud_p(new pcl::PointCloud<pcl::PointXYZ>), cloud_seg(new pcl::PointCloud<pcl::PointXYZ>); 
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_p_rotated(new pcl::PointCloud<pcl::PointXYZ>);
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_p_transformed(new pcl::PointCloud<pcl::PointXYZ>);
			pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_transformed(new pcl::PointCloud<pcl::PointXYZ>);

			sensor_msgs::PointCloud2  plane_sensor, plane_transf_sensor;

			//convert sen
			pcl::fromROSMsg(*cloud_msg, *cloud1);
			pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
			pcl::PointIndices::Ptr inliers(new pcl::PointIndices);

			pcl::SACSegmentation<pcl::PointXYZ> seg;

			seg.setOptimizeCoefficients(true);
			seg.setModelType (pcl::SACMODEL_PLANE);
	  		seg.setMethodType (pcl::SAC_RANSAC);
	  		seg.setMaxIterations (100);
			seg.setDistanceThreshold (0.01);

			seg.setInputCloud(cloud1);
			seg.segment (*inliers, *coefficients);

			Eigen::Matrix<float, 1, 3> surface_normal;
			Eigen::Matrix<float, 1, 3> floor_normal;
			surface_normal[0] = coefficients->values[0];
			surface_normal[1] = coefficients->values[1];
			surface_normal[2] = coefficients->values[2];
			std::cout << surface_normal[0] << "\n" << surface_normal[1] << "\n" << surface_normal[2];

			floor_normal[0] = 0.0;
			floor_normal[1] = 1.0;
			floor_normal[2] = 0.0;

			theta = acos(surface_normal.dot(floor_normal));
			//extract the inliers - copied from tutorials...

			pcl::ExtractIndices<pcl::PointXYZ> extract;
			extract.setInputCloud(cloud1);
	    	extract.setIndices (inliers);
	    	extract.setNegative(true);
	    	extract.filter(*cloud_p);

	    	ROS_INFO("print cloud info %d",  cloud_p->height);
	    	pcl::toROSMsg(*cloud_p, plane_sensor);
	    	pub_plane_simple.publish(plane_sensor);

	    	// anti rotate the point cloud by first finding the angle of rotation 

	    	Eigen::Affine3f transform_1 = Eigen::Affine3f::Identity();
	        transform_1.translation() << 0.0, 0.0, 0.0;
	        transform_1.rotate (Eigen::AngleAxisf (theta, Eigen::Vector3f::UnitX()));

	        pcl::transformPointCloud(*cloud_p, *cloud_p_rotated, transform_1);
			double y_sum = 0;
			// int num_points = 
			for (int i = 0; i < 20; i++){
				y_sum = cloud_p_rotated->points[i].y;
			}


			y_offset = y_sum / 20;

			Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();
	        transform_2.translation() << 0.0, -y_offset, 0.0;
	        transform_2.rotate (Eigen::AngleAxisf (theta, Eigen::Vector3f::UnitX()));

			pcl::transformPointCloud(*cloud_p, *cloud_p_transformed, transform_2);
	        pcl::transformPointCloud(*cloud1, *cloud_transformed, transform_2);

	        //now remove the y offset because of the camera rotation 

	        pcl::toROSMsg(*cloud_p_transformed, plane_transf_sensor);
	        // pcl::toROSMsg(*cloud_transformed, plane_transf_sensor);
	        // pcl::toROSMsg(*cloud1, plane_transf_sensor);
	        pub_plane_transf.publish(plane_transf_sensor);


		}


		ras_msgs::Cam_transform cft;

		cft.theta = theta;
		cft.y_offset = y_offset;	
		pub_ctf.publish(cft);	
		// pub_tf.publish();

	}