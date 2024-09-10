// IMPORTANT:  We need to receive the point clouds in local coordinates (scanner or robot)
void Mapper::processCloud(unique_ptr<DP> newPointCloud, const std::string& scannerFrame, const ros::Time& stamp, uint32_t seq)
{

	

	// if the future has completed, use the new map
	processNewMapIfAvailable(); // This call lock the tf publication
	cerr << "received new map" << endl;
	
	timer t;

  processingNewCloud = true;
	BoolSetter stopProcessingSetter(processingNewCloud, false);
	
	
	// Convert point cloud
	const size_t goodCount(newPointCloud->features.cols());
	if (goodCount == 0)
	{
		ROS_ERROR("I found no good points in the cloud");
		return;
	}
	
	// Dimension of the point cloud, important since we handle 2D and 3D
	const int dimp1(newPointCloud->features.rows());

	if(!(newPointCloud->descriptorExists("stamps_Msec") && newPointCloud->descriptorExists("stamps_sec") && newPointCloud->descriptorExists("stamps_nsec")))
	{
		const float Msec = round(stamp.sec/1e6);
		const float sec = round(stamp.sec - Msec*1e6);
		const float nsec = round(stamp.nsec);

		const PM::Matrix desc_Msec = PM::Matrix::Constant(1, goodCount, Msec);
		const PM::Matrix desc_sec = PM::Matrix::Constant(1, goodCount, sec);
		const PM::Matrix desc_nsec = PM::Matrix::Constant(1, goodCount, nsec);
		newPointCloud->addDescriptor("stamps_Msec", desc_Msec);
		newPointCloud->addDescriptor("stamps_sec", desc_sec);
		newPointCloud->addDescriptor("stamps_nsec", desc_nsec);

		cout << "Adding time" << endl;
		
	}

	ROS_INFO("Processing new point cloud");
	{
		timer t; // Print how long take the algo
		
		// Apply filters to incoming cloud, in scanner coordinates
		inputFilters.apply(*newPointCloud);
    
    
		ROS_INFO_STREAM("Input filters took " << t.elapsed() << " [s]");
	}
	
	string reason;
	// Initialize the transformation to identity if empty
 	if(!icp.hasMap())
 	{
		// we need to know the dimensionality of the point cloud to initialize properly
		publishLock.lock();
		TOdomToMap = PM::TransformationParameters::Identity(dimp1, dimp1);
		TOdomToMap(2,3) = mapElevation;
		publishLock.unlock();
	}

 
	// Fetch transformation from scanner to odom
	// Note: we don't need to wait for transform. It is already called in transformListenerToEigenMatrix()
	PM::TransformationParameters TOdomToScanner;
	try
	{
		TOdomToScanner = PointMatcher_ros::eigenMatrixToDim<float>(
				PointMatcher_ros::transformListenerToEigenMatrix<float>(
				tfListener,
				scannerFrame,
				odomFrame,
				stamp
			), dimp1);
	}
	catch(tf::ExtrapolationException e)
	{
		ROS_ERROR_STREAM("Extrapolation Exception. stamp = "<< stamp << " now = " << ros::Time::now() << " delta = " << ros::Time::now() - stamp << endl << e.what() );
		return;
	}


	ROS_DEBUG_STREAM("TOdomToScanner(" << odomFrame<< " to " << scannerFrame << "):\n" << TOdomToScanner);
	ROS_DEBUG_STREAM("TOdomToMap(" << odomFrame<< " to " << mapFrame << "):\n" << TOdomToMap);
		
	const PM::TransformationParameters TscannerToMap = TOdomToMap * TOdomToScanner.inverse();
	ROS_DEBUG_STREAM("TscannerToMap (" << scannerFrame << " to " << mapFrame << "):\n" << TscannerToMap);
	
	// Ensure a minimum amount of point after filtering
	const int ptsCount = newPointCloud->features.cols();
	if(ptsCount < minReadingPointCount)
	{
		ROS_ERROR_STREAM("Not enough points in newPointCloud: only " << ptsCount << " pts.");
		return;
	}

	// Initialize the map if empty
 	if(!icp.hasMap())
 	{
		ROS_INFO_STREAM("Creating an initial map");
		mapCreationTime = stamp;
		setMap(updateMap(newPointCloud.release(), TscannerToMap, false));
		// we must not delete newPointCloud because we just stored it in the mapPointCloud
		return;
	}
	
	// Check dimension
	if (newPointCloud->features.rows() != icp.getInternalMap().features.rows())
	{
		ROS_ERROR_STREAM("Dimensionality missmatch: incoming cloud is " << newPointCloud->features.rows()-1 << " while map is " << icp.getInternalMap().features.rows()-1);
		return;
	}
	
	try 
	{
		// Apply ICP
		PM::TransformationParameters Ticp;
		Ticp = icp(*newPointCloud, TscannerToMap);
    Ticp = transformation->correctParameters(Ticp);

    // extract corrections
    PM::TransformationParameters Tdelta = Ticp * TscannerToMap.inverse();
     
		// ISER
		//{
    //  // remove roll and pitch
    //  Tdelta(2,0) = 0; 
    //  Tdelta(2,1) = 0; 
    //  Tdelta(2,2) = 1; 
    //  Tdelta(0,2) = 0; 
    //  Tdelta(1,2) = 0;
    //  Tdelta(2,3) = 0; //z
    //  Tdelta.block(0,0,3,3) = transformation->correctParameters(Tdelta.block(0,0,3,3));

    //  Ticp = Tdelta*TscannerToMap;

    //  ROS_DEBUG_STREAM("Ticp:\n" << Ticp);
		//}

		
		// Ensure minimum overlap between scans
		const double estimatedOverlap = icp.errorMinimizer->getOverlap();
		ROS_INFO_STREAM("Overlap: " << estimatedOverlap);
		if (estimatedOverlap < minOverlap)
		{
			ROS_ERROR_STREAM("Estimated overlap too small, ignoring ICP correction!");
			return;
		}

    // Compute tf
		publishStamp = stamp;
		publishLock.lock();
		TOdomToMap = Ticp * TOdomToScanner;

    PM::TransformationParameters Terror = TscannerToMap.inverse() * Ticp;

    cerr << "Correcting translation error of " << Terror.block(0,3, 3,1).norm() << " m" << endl;

    // Add transformation to path
    path.push_back(Ticp);
    errors.push_back(Terror);

		// Publish tf
		if(publishMapTf == true)
		{
			tfBroadcaster.sendTransform(PointMatcher_ros::eigenMatrixToStampedTransform<float>(TOdomToMap, mapFrame, odomFrame, stamp));
		}

		publishLock.unlock();
		processingNewCloud = false;
		
		ROS_DEBUG_STREAM("TOdomToMap:\n" << TOdomToMap);

		// Publish odometry
		if (odomPub.getNumSubscribers())
			odomPub.publish(PointMatcher_ros::eigenMatrixToOdomMsg<float>(Tdelta, mapFrame, stamp));
	
    // TODO: check that, might be wrong....
		// Publish error on odometry
		if (odomErrorPub.getNumSubscribers())
			odomErrorPub.publish(PointMatcher_ros::eigenMatrixToOdomMsg<float>(TOdomToMap, mapFrame, stamp));

		// ***Debug:
    //debugPub.publish(PointMatcher_ros::pointMatcherCloudToRosMsg<float>(transformation->compute(*newPointCloud, Ticp), mapFrame, mapCreationTime));
		// ***


		// check if news points should be added to the map
		if (
			mapping &&
			((estimatedOverlap < maxOverlapToMerge) || (icp.getInternalMap().features.cols() < minMapPointCount)) &&
			(!mapBuildingInProgress)
    )
		{
			cout << "map Creation..." << endl;
			// make sure we process the last available map
			mapCreationTime = stamp;
			ROS_INFO("Adding new points to the map in background");
			mapBuildingTask = MapBuildingTask(boost::bind(&Mapper::updateMap, this, newPointCloud.release(), Ticp, true));
			mapBuildingFuture = mapBuildingTask.get_future();
			mapBuildingThread = boost::thread(boost::move(boost::ref(mapBuildingTask)));
			mapBuildingInProgress = true;
    }
	}
	catch (PM::ConvergenceError error)
	{
		ROS_ERROR_STREAM("ICP failed to converge: " << error.what());
		return;
	}
	
	//Statistics about time and real-time capability
	int realTimeRatio = 100*t.elapsed() / (stamp.toSec()-lastPoinCloudTime.toSec());
	ROS_INFO_STREAM("[TIME] Total ICP took: " << t.elapsed() << " [s]");
	if(realTimeRatio < 80)
		ROS_INFO_STREAM("[TIME] Real-time capability: " << realTimeRatio << "%");
	else
		ROS_WARN_STREAM("[TIME] Real-time capability: " << realTimeRatio << "%");

	lastPoinCloudTime = stamp;
}