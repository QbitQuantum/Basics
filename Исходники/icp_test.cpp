void getTestDataFromBag(PointCloudPtr cloud_source, PointCloudPtr cloud_target,
		PointCloudPtr featureCloudSource, std::vector<int> &indicesSource,
		PointCloudPtr featureCloudTarget, std::vector<int> &indicesTarget,
		Eigen::Matrix4f &initialTransform, int rosMessageNumber)
{
	sensor_msgs::PointCloud2::Ptr cloud_source_filtered (new sensor_msgs::PointCloud2 ());
	sensor_msgs::PointCloud2::Ptr cloud_target_filtered (new sensor_msgs::PointCloud2 ());
	PointCloudPtr cloud_ransac_estimation (new PointCloud);

  	pcl::PCDWriter writer;
  	std::stringstream filename;

	rosbag::Bag bag;
	bag.open("/media/burg/data/bagfiles/bench1-ManySweeps4-lowfeatureThresNode2.bag", rosbag::bagmode::Read);

	std::vector<std::string> topics;
	topics.push_back(std::string("/feature_match_out_topic"));

	rosbag::View view(bag, rosbag::TopicQuery(topics));

	int i = 1;
	BOOST_FOREACH(rosbag::MessageInstance const m, view)
	{
		if(( i == rosMessageNumber) || (rosMessageNumber==0))
		{
			pcl_tutorial::featureMatch::ConstPtr fm = m.instantiate<pcl_tutorial::featureMatch>();

			ROS_INFO("Converting point cloud message to local pcl clouds");

			sensor_msgs::PointCloud2::Ptr cloud_source_temp_Ptr (new sensor_msgs::PointCloud2 (fm->sourcePointcloud));
			sensor_msgs::PointCloud2::Ptr cloud_target_temp_Ptr (new sensor_msgs::PointCloud2 (fm->targetPointcloud));

			voxFilterPointCloud(cloud_source_temp_Ptr, cloud_source_filtered);
			voxFilterPointCloud(cloud_target_temp_Ptr, cloud_target_filtered);
			ROS_INFO("Converting dense clouds");
			pcl::fromROSMsg(*cloud_source_filtered, *cloud_source);
			pcl::fromROSMsg(*cloud_target_filtered, *cloud_target);
			ROS_INFO("Converting sparse clouds");
			pcl::fromROSMsg(fm->sourceFeatureLocations, *featureCloudSource);
			pcl::fromROSMsg(fm->targetFeatureLocations, *featureCloudTarget);

			ROS_INFO("Converting geometry message to eigen4f");
		    tf::Transform trans;
		    tf::transformMsgToTF(fm->featureTransform,trans);
		    initialTransform = EigenfromTf(trans);
		    ROS_INFO_STREAM("transform from ransac: " << "\n"  << initialTransform << "\n");

		    ROS_INFO("Extracting corresponding indices");
		    //int j = 1;
		    indicesSource.clear();
		    indicesTarget.clear();
		  	for(std::vector<pcl_tutorial::match>::const_iterator iterator_ = fm->matches.begin(); iterator_ != fm->matches.end(); ++iterator_)
		  	{
		  		indicesSource.push_back(iterator_->trainId);
		  		indicesTarget.push_back(iterator_->queryId);
		  	//	ROS_INFO_STREAM("source point " << j << ": "   << featureCloudSource->points[iterator_->queryId].x << ", " << featureCloudSource->points[iterator_->queryId].y << ", " << featureCloudSource->points[iterator_->queryId].z);
		  	//	ROS_INFO_STREAM("target point " << j++ << ": " << featureCloudTarget->points[iterator_->trainId].x << ", " << featureCloudTarget->points[iterator_->trainId].y << ", " << featureCloudTarget->points[iterator_->trainId].z);
		  	//	ROS_INFO("qidx: %d tidx: %d iidx: %d dist: %f", iterator_->queryId, iterator_->trainId, iterator_->imgId, iterator_->distance);
		  	}
		    /*for (size_t cloudId = 0; cloudId < featureCloudSource->points.size (); ++cloudId)
		    {
		    	ROS_INFO_STREAM("feature cloud: " << cloudId << ": " << featureCloudSource->points[cloudId].x << "; " << featureCloudSource->points[cloudId].y << "; " << featureCloudSource->points[cloudId].z);
		    }*/

		  	Eigen::Matrix4f ransacInverse = initialTransform.inverse();
		  	transformPointCloud (*cloud_source, *cloud_ransac_estimation, ransacInverse);

		    ROS_INFO("Writing point clouds");
		  	filename << "cloud" << i << "DenseSource.pcd";
		  	writer.write (filename.str(), *cloud_source, false);
		  	filename.str("");
		  	filename << "cloud" << i << "DenseTarget.pcd";
		  	writer.write (filename.str(), *cloud_target, true);
		  	filename.str("");
		  	filename << "cloud" << i << "RANSAC-" << (int)indicesSource.size() << "-inliers.pcd";
		  	writer.write (filename.str(), *cloud_ransac_estimation, true);
		  	filename.str("");
		  	filename << "cloud" << i << "SparseSource.pcd";
		  	writer.write (filename.str(), *featureCloudSource, false);
		  	filename.str("");
		  	filename << "cloud" << i << "SparseTarget.pcd";
		    writer.write (filename.str(), *featureCloudTarget, false);
		    filename.str("");
		  	i++;

		  //  for(std::vector<int>::iterator iterator_ = indicesSource.begin(); iterator_ != indicesSource.end(); ++iterator_) {
		  //  	ROS_INFO("source indice: %d", *iterator_);
		  //  }
		}
		else
			i++;
	}
	bag.close();
}