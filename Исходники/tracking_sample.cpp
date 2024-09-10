int
main (int argc, char** argv)
{
  if (argc < 3)
    {
      PCL_WARN("Please set device_id pcd_filename(e.g. $ %s '#1' sample.pcd)\n", argv[0]);
      exit (1);
    }

  //read pcd file
  target_cloud.reset(new Cloud());
  if(pcl::io::loadPCDFile (argv[2], *target_cloud) == -1){
    std::cout << "pcd file not found" << std::endl;
    exit(-1);
  }

  std::string device_id = std::string (argv[1]);  

  counter = 0;

  //Set parameters
  new_cloud_  = false;
  downsampling_grid_size_ =  0.002;

  std::vector<double> default_step_covariance = std::vector<double> (6, 0.015 * 0.015);
  default_step_covariance[3] *= 40.0;
  default_step_covariance[4] *= 40.0;
  default_step_covariance[5] *= 40.0;

  std::vector<double> initial_noise_covariance = std::vector<double> (6, 0.00001);
  std::vector<double> default_initial_mean = std::vector<double> (6, 0.0);

  KLDAdaptiveParticleFilterOMPTracker<RefPointType, ParticleT>::Ptr tracker
    (new KLDAdaptiveParticleFilterOMPTracker<RefPointType, ParticleT> (8));

  ParticleT bin_size;
  bin_size.x = 0.1f;
  bin_size.y = 0.1f;
  bin_size.z = 0.1f;
  bin_size.roll = 0.1f;
  bin_size.pitch = 0.1f;
  bin_size.yaw = 0.1f;


  //Set all parameters for  KLDAdaptiveParticleFilterOMPTracker
  tracker->setMaximumParticleNum (1000);
  tracker->setDelta (0.99);
  tracker->setEpsilon (0.2);
  tracker->setBinSize (bin_size);

  //Set all parameters for  ParticleFilter
  tracker_ = tracker;
  tracker_->setTrans (Eigen::Affine3f::Identity ());
  tracker_->setStepNoiseCovariance (default_step_covariance);
  tracker_->setInitialNoiseCovariance (initial_noise_covariance);
  tracker_->setInitialNoiseMean (default_initial_mean);
  tracker_->setIterationNum (1);
  tracker_->setParticleNum (600);
  tracker_->setResampleLikelihoodThr(0.00);
  tracker_->setUseNormal (false);


  //Setup coherence object for tracking
  ApproxNearestPairPointCloudCoherence<RefPointType>::Ptr coherence
    (new ApproxNearestPairPointCloudCoherence<RefPointType>);

  DistanceCoherence<RefPointType>::Ptr distance_coherence
    (new DistanceCoherence<RefPointType>);
  coherence->addPointCoherence (distance_coherence);

  pcl::search::Octree<RefPointType>::Ptr search (new pcl::search::Octree<RefPointType> (0.01));
  coherence->setSearchMethod (search);
  coherence->setMaximumDistance (0.01);

  tracker_->setCloudCoherence (coherence);

  //prepare the model of tracker's target
  Eigen::Vector4f c;
  Eigen::Affine3f trans = Eigen::Affine3f::Identity ();
  CloudPtr transed_ref (new Cloud);
  CloudPtr transed_ref_downsampled (new Cloud);

  pcl::compute3DCentroid<RefPointType> (*target_cloud, c);
  trans.translation ().matrix () = Eigen::Vector3f (c[0], c[1], c[2]);
  pcl::transformPointCloud<RefPointType> (*target_cloud, *transed_ref, trans.inverse());
  gridSampleApprox (transed_ref, *transed_ref_downsampled, downsampling_grid_size_);

  //set reference model and trans
  tracker_->setReferenceCloud (transed_ref_downsampled);
  tracker_->setTrans (trans);

  //Setup OpenNIGrabber and viewer
  pcl::visualization::CloudViewer* viewer_ = new pcl::visualization::CloudViewer("PCL OpenNI Tracking Viewer");
  pcl::Grabber* interface = new pcl::OpenNIGrabber (device_id);
  boost::function<void (const CloudConstPtr&)> f =
    boost::bind (&cloud_cb, _1);
  interface->registerCallback (f);
    
  viewer_->runOnVisualizationThread (boost::bind(&viz_cb, _1), "viz_cb");

  //Start viewer and object tracking
  interface->start();
  while (!viewer_->wasStopped ())
    std::this_thread::sleep_for(1s);
  interface->stop();
}