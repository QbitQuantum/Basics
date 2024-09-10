void boxFilter(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud, Pose pose){		
	//Transform the cloud
	//convert the tranform from our fiducial markers to the Eigen
    Eigen::Matrix<float, 3, 3> R;
    Eigen::Vector3f T;
    cv::cv2eigen(pose.getT(), T);
    cv::cv2eigen(pose.getR(), R);
    //get the inverse transform to bring the point cloud's into the
    //same coordinate frame
    Eigen::Affine3f transform;
    transform = Eigen::AngleAxisf(R.transpose());
    transform *= Eigen::Translation3f(-T);
    //transform the cloud in place
    pcl::transformPointCloud(*cloud, *cloud, transform);
	
	//Define the box
	float box = 200.00;
	pcl::PassThrough<pcl::PointXYZRGB> pass_z, pass_x, pass_y;
	//Filters in x
	pass_x.setFilterFieldName("x");
	pass_x.setFilterLimits(-box, box);
	pass_x.setInputCloud(cloud);
	pass_x.filter(*cloud);
	//Filters in y
	pass_y.setFilterFieldName("y");
	pass_y.setFilterLimits(-box, box);
	pass_y.setInputCloud(cloud);
	pass_y.filter(*cloud);
	//Filters in z
	pass_z.setFilterFieldName("z");
	pass_z.setFilterLimits(0,box);
	pass_z.setInputCloud(cloud);
	pass_z.filter(*cloud);	
}