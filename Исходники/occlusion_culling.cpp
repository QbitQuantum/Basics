pcl::PointCloud<pcl::PointXYZ> OcclusionCulling::extractVisibleSurface(geometry_msgs::Pose location)
{
    // >>>>>>>>>>>>>>>>>>>>
    // 1. Frustum Culling
    // >>>>>>>>>>>>>>>>>>>>
    pcl::PointCloud <pcl::PointXYZ>::Ptr output (new pcl::PointCloud <pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr occlusionFreeCloud_local(new pcl::PointCloud<pcl::PointXYZ>);

    Eigen::Matrix4f camera_pose;
    Eigen::Matrix3d Rd;
    Eigen::Matrix3f Rf;

    camera_pose.setZero ();


    // Convert quaterion orientation to XYZ angles (?)
    tf::Quaternion qt;
    qt.setX(location.orientation.x);
    qt.setY(location.orientation.y);
    qt.setZ(location.orientation.z);
    qt.setW(location.orientation.w);
    tf::Matrix3x3 R_tf(qt);
    tf::matrixTFToEigen(R_tf,Rd);
    Rf = Rd.cast<float>();

    camera_pose.block (0, 0, 3, 3) = Rf;

    // Set position
    Eigen::Vector3f T;
    T (0) = location.position.x;
    T (1) = location.position.y;
    T (2) = location.position.z;
    camera_pose.block (0, 3, 3, 1) = T;

    // Set pose
    camera_pose (3, 3) = 1;
    fc.setCameraPose (camera_pose);

    // Perform culling
    ros::Time tic = ros::Time::now();
    fc.filter (*output);
    ros::Time toc = ros::Time::now();

    //std::cout<<"\nFrustum Filter took:"<< toc.toSec() - tic.toSec();
    FrustumCloud->points= output->points;



    // >>>>>>>>>>>>>>>>>>>>
    // 2. Voxel grid occlusion estimation
    // >>>>>>>>>>>>>>>>>>>>
    Eigen::Quaternionf quat(qt.w(),qt.x(),qt.y(),qt.z());
    output->sensor_origin_  = Eigen::Vector4f(T[0],T[1],T[2],0);
    output->sensor_orientation_= quat;
    pcl::VoxelGridOcclusionEstimationT voxelFilter;
    voxelFilter.setInputCloud (output);
    voxelFilter.setLeafSize (voxelRes, voxelRes, voxelRes);
    voxelFilter.initializeVoxelGrid();

    int state,ret;

    pcl::PointXYZ pt,p1,p2;
    pcl::PointXYZRGB point;
    std::vector<Eigen::Vector3i, Eigen::aligned_allocator<Eigen::Vector3i> > out_ray;
    //std::vector<geometry_msgs::Point> lineSegments;
    geometry_msgs::Point linePoint;

    // iterate over the entire frustum points
    for ( int i = 0; i < (int)output->points.size(); i ++ )
    {
        // Get voxel centroid corresponding to selected point
        pcl::PointXYZ ptest = output->points[i];
        Eigen::Vector3i ijk = voxelFilter.getGridCoordinates( ptest.x, ptest.y, ptest.z);
        
        if(voxelFilter.getCentroidIndexAt(ijk) == -1 ) {
			// Voxel is out of bounds
            continue;
        }

        Eigen::Vector4f centroid = voxelFilter.getCentroidCoordinate (ijk);
        point = pcl::PointXYZRGB(0,244,0);
        point.x = centroid[0];
        point.y = centroid[1];
        point.z = centroid[2];

		// >>>>>>>>>>>>>>>>>>>>
		// 2.1 Perform occlusion estimation
		// >>>>>>>>>>>>>>>>>>>>
		
		/*
		 * The way this works is it traces a line to the point and finds
		 * the distance to the first occupied voxel in its path (t_min).
		 * It then determines if the distance between the target point and
		 * the collided voxel are close (within voxelRes).
		 * 
		 * If they are, the point is visible. Otherwise, the point is behind
		 * an occluding point
		 * 
		 * 
		 * This is the expected function of the following command:
		 *   ret = voxelFilter.occlusionEstimation( state,out_ray, ijk);
		 * 
		 * However, it sometimes shows occluded points on the edge of the cloud
		 */
		
		// Direction to target voxel
		Eigen::Vector4f direction = centroid - output->sensor_origin_;
		direction.normalize ();
		
		// Estimate entry point into the voxel grid
		float tmin = voxelFilter.rayBoxIntersection (output->sensor_origin_, direction,p1,p2); //where did this 4-input syntax come from?
		
		if(tmin == -1){
			// ray does not intersect with the bounding box
			continue;
		}
		
		// Calculate coordinate of the boundary of the voxel grid
		Eigen::Vector4f start = output->sensor_origin_ + tmin * direction;
		
		// Determine distance between boundary and target voxel centroid
		Eigen::Vector4f dist_vector = centroid-start;
		float distance = (dist_vector).dot(dist_vector);

		if (distance > voxelRes*1.414){ // voxelRes/sqrt(2)
			// ray does not correspond to this point
			continue;
		}
		
		// Save point
		occlusionFreeCloud_local->points.push_back(ptest);
		occlusionFreeCloud->points.push_back(ptest);
		

		// >>>>>>>>>>>>>>>>>>>>
		// 2.2 Save line segment for visualization
		// >>>>>>>>>>>>>>>>>>>>

		linePoint.x = output->sensor_origin_[0];
		linePoint.y = output->sensor_origin_[1];
		linePoint.z = output->sensor_origin_[2];
		lineSegments.push_back(linePoint);

		linePoint.x = start[0];
		linePoint.y = start[1];
		linePoint.z = start[2];
		lineSegments.push_back(linePoint);

		occupancyGrid->points.push_back(point);
    }
    FreeCloud.points = occlusionFreeCloud_local->points;

    return FreeCloud;
}