MulticamFusion::MulticamFusion(){
	cloud_viewer_.setBackgroundColor (0, 0, 0);
	cloud_viewer_.setPointCloudRenderingProperties (visualization::PCL_VISUALIZER_POINT_SIZE, 1);    
	cloud_viewer_.addCoordinateSystem (1.0);
	cloud_viewer_.initCameraParameters ();
	cloud_viewer_.camera_.clip[0] = 0.01;
	cloud_viewer_.camera_.clip[1] = 10.01;

	cloud_viewer_.addText ("H: print help", 2, 15, 20, 34, 135, 246);      
	
	//Initialize TSDF Volume
	volume_size = Vector3f::Constant (4.4f);
	volume_resolution = Vector3i(512, 512, 512);

	tsdf_volume_ = TsdfVolume::Ptr( new TsdfVolume(volume_resolution) );
	tsdf_volume_->setSize(volume_size);

	image_viewer_.registerKeyboardCallback(keyboard_callback, (void*)this);

	raycaster_ptr_ = RayCaster::Ptr( new RayCaster(480, 640) );

	cloud_viewer_.addCube(volume_size*0.5, Eigen::Quaternionf::Identity(), volume_size(0), volume_size(1), volume_size(2));
	cloud_viewer_.registerKeyboardCallback(keyboard_callback, (void*)this);

	//init_tcam = volume_size * 0.5f - Vector3f (0, 0, volume_size (2) / 2 * 1.2f);
	
	Eigen::Affine3f default_pose;
	default_pose.linear() = Eigen::Matrix3f::Identity ();
	default_pose.translation() = Vector3f(1.5f, 1.5f, -0.3f);
	cout << default_pose.translation() << endl;

	setViewerPose(cloud_viewer_, default_pose);
	rows = 480; cols = 640;
	cloud_device_ = new DeviceArray2D<PointXYZ>(rows, cols);
	cloud_ptr_ = PointCloud<PointXYZ>::Ptr (new PointCloud<PointXYZ>);
}