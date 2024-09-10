int main(int argc, char *argv[])
{
	ros::init (argc, argv, "marker_detect");
	ros::NodeHandle n, pn("~");
	
	if(argc < 7){
		std::cout << std::endl;
		cout << "Not enough arguments provided." << endl;
		cout << "Usage: ./individualMarkersNoKinect <marker size in cm> <max new marker error> "
		     << "<max track error> <cam image topic> <cam info topic> <output frame> [ <max frequency> ]";
		std::cout << std::endl;
		return 0;
	}

	// Get params from command line
	marker_size = atof(argv[1]);
	max_new_marker_error = atof(argv[2]);
	max_track_error = atof(argv[3]);
	cam_image_topic = argv[4];
	cam_info_topic = argv[5];
    output_frame = argv[6];
	marker_detector.SetMarkerSize(marker_size);

  if (argc > 7)
    max_frequency = atof(argv[7]);

  // Set dynamically configurable parameters so they don't get replaced by default values
  pn.setParam("marker_size", marker_size);
  pn.setParam("max_new_marker_error", max_new_marker_error);
  pn.setParam("max_track_error", max_track_error);

  if (argc > 7)
    pn.setParam("max_frequency", max_frequency);

	cam = new Camera(n, cam_info_topic);
	tf_listener = new tf::TransformListener(n);
	tf_broadcaster = new tf::TransformBroadcaster();
	arMarkerPub_ = n.advertise < ar_track_alvar_msgs::AlvarMarkers > ("ar_pose_marker", 0);
	rvizMarkerPub_ = n.advertise < visualization_msgs::Marker > ("visualization_marker", 0);
	
  // Prepare dynamic reconfiguration
  dynamic_reconfigure::Server < ar_track_alvar::ParamsConfig > server;
  dynamic_reconfigure::Server<ar_track_alvar::ParamsConfig>::CallbackType f;

  f = boost::bind(&configCallback, _1, _2);
  server.setCallback(f);

	//Give tf a chance to catch up before the camera callback starts asking for transforms
  // It will also reconfigure parameters for the first time, setting the default values
	ros::Duration(1.0).sleep();
	ros::spinOnce();	
	 
	image_transport::ImageTransport it_(n);

  if (enabled == true)
  {
    // This always happens, as enable is true by default
    ROS_INFO("Subscribing to image topic");
    	cam_sub_ = it_.subscribe (cam_image_topic, 1, &getCapCallback);
  }

  // Run at the configured rate, discarding pointcloud msgs if necessary
  ros::Rate rate(max_frequency);

  while (ros::ok())
  {
    ros::spinOnce();
    rate.sleep();

    if (std::abs((rate.expectedCycleTime() - ros::Duration(1.0 / max_frequency)).toSec()) > 0.001)
    {
      // Change rate dynamically; if must be above 0, as 0 will provoke a segfault on next spinOnce
      ROS_DEBUG("Changing frequency from %.2f to %.2f", 1.0 / rate.expectedCycleTime().toSec(), max_frequency);
      rate = ros::Rate(max_frequency);
    }

    if (enableSwitched == true)
    {
      // Enable/disable switch: subscribe/unsubscribe to make use of pointcloud processing nodelet
      // lazy publishing policy; in CPU-scarce computer as TurtleBot's laptop this is a huge saving
      if (enabled == false)
        cam_sub_.shutdown();
      else
        cam_sub_ = it_.subscribe(cam_image_topic, 1, &getCapCallback);
      enableSwitched = false;
    }
  }

    return 0;
}