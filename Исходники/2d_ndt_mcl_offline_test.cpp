/**
 * This is where the localization is done... not really callback in the offline version
 */ 
void callback(const sensor_msgs::LaserScan &scan, tf::Transform odo_pose, tf::Transform state_pose)
{
	static int counter = 0;
	counter++;
	
	static tf::TransformListener tf_listener;
	
	double looptime = TT.Tac();
	TT.Tic();
	fprintf(stderr,"Lt( %.1lfms %.1lfHz seq:%d) -",looptime*1000,1.0/looptime,scan.header.seq);
	
	if(has_sensor_offset_set == false) return;
	
	double gx,gy,gyaw,x,y,yaw;
	
	///Get the ground truth
	gyaw = tf::getYaw(state_pose.getRotation());  
	gx = state_pose.getOrigin().x();
	gy = state_pose.getOrigin().y();
	
	///Get the odometry
	yaw = tf::getYaw(odo_pose.getRotation());  
	x = odo_pose.getOrigin().x();
	y = odo_pose.getOrigin().y();
		
	mrpt::utils::CTicTac	tictac;
	tictac.Tic();

	int N =(scan.angle_max - scan.angle_min)/scan.angle_increment; ///< number of scan lines
	
	/////
	/// Pose conversions
	////
	
	Eigen::Affine3d T = getAsAffine(x,y,yaw);
	Eigen::Affine3d Tgt = getAsAffine(gx,gy,gyaw);
	
	/**
	 * We are now using the information from the ground truth to initialize the filter
	 */ 
	if(isFirstLoad){
		fprintf(stderr,"Initializing to (%lf, %lf, %lf)\n",gx,gy,gyaw);
		///Initialize the filter with 1m^2 variance in position and 20deg in heading
		ndtmcl->initializeFilter(gx, gy,gyaw,1.0, 1.0, 20.0*M_PI/180.0, 450);
		Told = T;
		Todo = Tgt;
	}
	
	///Compute the differential motion between two time steps 
	Eigen::Affine3d Tmotion = Told.inverse() * T;
	Todo = Todo*Tmotion;
	Told = T;
	
	///Get the laser pose with respect to the base
	float dy =offy;
	float dx = offx;
	float alpha = atan2(dy,dx);
	float L = sqrt(dx*dx+dy*dy);
	
	///Laser pose in base frame
	float lpx = L * cos(alpha);
	float lpy = L * sin(alpha);
	float lpa = offa;
	
	
	
	///Laser scan to PointCloud transformed with respect to the base
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);	
	for (int j=0;j<N;j++){
		double r  = scan.ranges[j];
		if(r>=scan.range_min && r<scan.range_max && r>0.3 && r<20.0){
			double a  = scan.angle_min + j*scan.angle_increment;
			pcl::PointXYZ pt;
			pt.x = r*cos(a+lpa)+lpx;
			pt.y = r*sin(a+lpa)+lpy;
			pt.z = 0.1+0.02 * (double)rand()/(double)RAND_MAX;
			cloud->push_back(pt);
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Now we have the differential motion and pointcloud -- Lets do MCL
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ndtmcl->updateAndPredict(Tmotion, *cloud); ///< does the prediction, update and resampling steps (see ndt_mcl.hpp)
	
	Eigen::Vector3d dm = ndtmcl->getMean(); ///<Maximum aposteriori estimate of the pose
	Eigen::Matrix3d cov = ndtmcl->pf.getDistributionVariances(); ///distribution variances
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double Time = tictac.Tac();
	fprintf(stderr,"Time elapsed %.1lfms (%lf %lf %lf) \n",Time*1000,dm[0],dm[1],dm[2]);
	isFirstLoad = false;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//If visualization desired
#ifdef USE_VISUALIZATION_DEBUG
	///The sensor pose in the global frame for visualization
	Eigen::Vector3d origin(dm[0] + L * cos(dm[2]+alpha),dm[1] + L * sin(dm[2]+alpha),0.1);

	Eigen::Affine3d ppos = getAsAffine(dm[0],dm[1],dm[2]);
	
	//lslgeneric::transformPointCloudInPlace(Tgt, *cloud);
	lslgeneric::transformPointCloudInPlace(ppos, *cloud);
	mrpt::opengl::COpenGLScenePtr &scene = win3D.get3DSceneAndLock();	
	win3D.setCameraPointingToPoint(gx,gy,1);
	if(counter%2000==0) gl_points->clear();
	scene->clear();
	scene->insert(plane);
	
	addMap2Scene(ndtmcl->map, origin, scene);
	addPoseCovariance(dm[0],dm[1],cov,scene);
	addScanToScene(scene, origin, cloud);
	addParticlesToWorld(ndtmcl->pf,Tgt.translation(),dm, Todo.translation());
	scene->insert(gl_points);
	scene->insert(gl_particles);
	win3D.unlockAccess3DScene();
	win3D.repaint();

	if (win3D.keyHit())
	{
		mrpt::gui::mrptKeyModifier kmods;
		int key = win3D.getPushedKey(&kmods);
	}
#endif
	
	

}