    void NDTFuserHMT::initialize(Eigen::Affine3d initPos, pcl::PointCloud<pcl::PointXYZ> &cloud, bool preLoad)
    {
	///Set the cloud to sensor frame with respect to base
	lslgeneric::transformPointCloudInPlace(sensor_pose, cloud);
	lslgeneric::transformPointCloudInPlace(initPos, cloud);
	Tnow = initPos;
	//#ifdef BASELINE
	//#else
	if(beHMT) {
	    map = new lslgeneric::NDTMapHMT(resolution,
		    Tnow.translation()(0),Tnow.translation()(1),Tnow.translation()(2),
		    map_size_x,map_size_y,map_size_z,sensor_range,hmt_map_dir,true);
	    if(preLoad) {
		lslgeneric::NDTMapHMT *map_hmt = dynamic_cast<lslgeneric::NDTMapHMT*> (map);
		std::cout<<"Trying to pre-load maps at "<<initPos.translation()<<std::endl;
		map_hmt->tryLoadPosition(initPos.translation());
	    }
	} else {
	    map = new lslgeneric::NDTMap(new lslgeneric::LazyGrid(resolution));
	    if(preLoad) {
		char fname[1000];
		snprintf(fname,999,"%s/%s_map.jff",hmt_map_dir.c_str(),prefix.c_str());
		std::cerr<<"Loading "<<fname<<std::endl;
		map->loadFromJFF(fname);
	    } else {
		map = new lslgeneric::NDTMap(new lslgeneric::LazyGrid(resolution));
		map->initialize(Tnow.translation()(0),Tnow.translation()(1),Tnow.translation()(2),map_size_x,map_size_y,map_size_z);
	    }
	}
	//#endif
	map->addPointCloud(Tnow.translation(),cloud, 0.1, 100.0, 0.1);
	//map->addPointCloudMeanUpdate(Tnow.translation(),cloud,localMapSize, 1e5, 1250, map_size_z/2, 0.06);
	//map->addPointCloudMeanUpdate(Tnow.translation(),cloud,localMapSize, 0.1, 100.0, 0.1);
	map->computeNDTCells(CELL_UPDATE_MODE_SAMPLE_VARIANCE, 1e5, 255, Tnow.translation(), 0.1);
	isInit = true;
	Tlast_fuse = Tnow;
	Todom = Tnow;
	if(visualize) 
	{
#ifndef NO_NDT_VIZ
      //      # error compiling with visualization
	    viewer->plotNDTSAccordingToOccupancy(-1,map); 
	    //viewer->plotLocalNDTMap(cloud,resolution);
	    viewer->addTrajectoryPoint(Tnow.translation()(0),Tnow.translation()(1),Tnow.translation()(2)+0.5,1,0,0);
	    viewer->addTrajectoryPoint(Todom.translation()(0),Todom.translation()(1),Todom.translation()(2)+0.5,0,1,0);
	    viewer->displayTrajectory();
	    viewer->setCameraPointing(Tnow.translation()(0),Tnow.translation()(1),Tnow.translation()(2)+3);
	    viewer->repaint();	
#endif
        }
    }