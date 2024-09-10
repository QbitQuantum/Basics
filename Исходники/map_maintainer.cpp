// Point cloud processing
void MapMaintener::processCloud(DP newPointCloud, const TP TScannerToMap)
{
	string reason;
	timer t;
	
	// Convert point cloud
	const size_t goodCount(newPointCloud.features.cols());
	if (goodCount == 0)
	{
		ROS_ERROR("I found no good points in the cloud");
		return;
	}
	
	ROS_INFO("Processing new point cloud");
	{
		timer t; // Print how long take the algo
		
		// Apply filters to incoming cloud, in scanner coordinates
		inputFilters.apply(newPointCloud);
		
		ROS_INFO_STREAM("Input filters took " << t.elapsed() << " [s]");
	}
	
	
	// Correct new points using ICP result and move them in their own frame
	//cout << "TObjectToMap: " << endl << TObjectToMap << endl;
	//cout << "TScannerToMap: " << endl << TScannerToMap << endl;
	//cout << "concat: " << endl << TObjectToMap.inverse() * TScannerToMap << endl;
	newPointCloud = transformation->compute(newPointCloud, transformation->correctParameters(TObjectToMap.inverse() * TScannerToMap)); 
	
	// Preparation of cloud for inclusion in map
	mapPreFilters.apply(newPointCloud);
	
	// FIXME put that as parameter
	if(newPointCloud.features.cols() < 400)
		return;

	// Generate first map
	if(!mapPointCloud.features.rows())	
	{
		mapPointCloud = newPointCloud;
		return;
	}
	

	// Check dimension
	if (newPointCloud.features.rows() != mapPointCloud.features.rows())
	{
		ROS_ERROR_STREAM("Dimensionality missmatch: incoming cloud is " << newPointCloud.features.rows()-1 << " while map is " << mapPointCloud.features.rows()-1);
		return;
	}


	PM::TransformationParameters Tcorr;
	try
	{
		Tcorr = icp(newPointCloud, mapPointCloud);
		TObjectToMap = TObjectToMap * Tcorr.inverse();
	}
	catch (PM::ConvergenceError error)
	{
		ROS_WARN_STREAM("ICP failed to converge: " << error.what());
		return;
	}


	const double estimatedOverlap = icp.errorMinimizer->getOverlap();
	if(estimatedOverlap < 0.40)
	{
		ROS_WARN_STREAM("Estimated overlap too small: " << estimatedOverlap);
		return;
	}

	ROS_DEBUG_STREAM("Tcorr:\n" << Tcorr);

	cout << "Tcorr: " << endl << Tcorr << endl;
	newPointCloud = transformation->compute(newPointCloud, Tcorr); 
	// Merge point clouds to map
	mapPointCloud.concatenate(newPointCloud);

	// Map maintenance
	mapPostFilters.apply(mapPointCloud);
	
	ROS_INFO_STREAM("New map available (" << mapPointCloud.features.cols() << " pts), update took " << t.elapsed() << " [s]");

	// Publish map point cloud
	// FIXME this crash when used without descriptor
	if (mapPub.getNumSubscribers())
		mapPub.publish(PointMatcher_ros::pointMatcherCloudToRosMsg<float>(mapPointCloud, objectFrame, ros::Time::now()));

	ROS_INFO_STREAM("Total map merging: " << t.elapsed() << " [s]");

	//ros::Rate r(2);
	//r.sleep();
}