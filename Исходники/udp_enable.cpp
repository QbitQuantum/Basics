int main( int argc, char* argv[] )
{
  // Program options
  
  std::string HostName = "192.168.10.1:801";
  int startup_delay = 10;

  ros::init(argc, argv, "udp_enable");
  ros::NodeHandle n;
  ros::Rate loop_rate(1);

  // log contains:
  // version number
  // log of framerate over time
  // --multicast
  // kill off internal app
  std::string LogFile = "";
  std::string MulticastAddress = "224.0.0.0:44801";
  bool ConnectToMultiCast = false;
  bool EnableMultiCast = true;
  bool EnableHapticTest = false;
  bool bReadCentroids = false;
  std::vector<std::string> HapticOnList(0);

  std::ofstream ofs;

  // ROS parameters
  std::string s;
  // mutlicast address
  if (n.getParam("vicon_multicast_address", s)) {
    MulticastAddress = s;
    //std::cout << "Got multicast " << MulticastAddress << " from parameter." << std::endl;
  }
  // own hostname
  if (n.getParam("vicon_server_hostname", s)) {
    HostName = s;
    //std::cout << "Got hostname " << HostName << " from parameter." << std::endl;
  }
  // tracking object (this one is private as unique to each node)
  // try the private thing using the "bare" method
  if (ros::param::has("~startup_delay")) {
     ros::param::get("~startup_delay", startup_delay);
  }

  ROS_INFO("Waiting for start-up delay of %d s", startup_delay);
  sleep(startup_delay);

  // Make a new client
  Client MyClient;

  // Connect to a server
  ROS_INFO("Connecting to server %s", HostName.c_str());
  while( !MyClient.IsConnected().Connected )
    {
      // Direct connection

      bool ok = false;
      if(ConnectToMultiCast)
      {
        // Multicast connection
        ok = ( MyClient.ConnectToMulticast( HostName, MulticastAddress ).Result == Result::Success );

      }
      else
      {
        ok =( MyClient.Connect( HostName ).Result == Result::Success );
      }
      if(!ok)
      {
        std::cout << "Warning - connect failed..." << std::endl;
      }


      std::cout << ".";
      sleep(1);
    }
    std::cout << std::endl;

    // Enable some different data types
    MyClient.EnableSegmentData();
    MyClient.EnableMarkerData();
    MyClient.EnableUnlabeledMarkerData();
    MyClient.EnableDeviceData();

    // Set the streaming mode
    // MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ClientPull );
    // MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ClientPullPreFetch );
    MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ServerPush );

    // Set the global up axis
    MyClient.SetAxisMapping( Direction::Forward, 
                             Direction::Left, 
                             Direction::Up ); // Z-up
    // MyClient.SetGlobalUpAxis( Direction::Forward, 
    //                           Direction::Up, 
    //                           Direction::Right ); // Y-up

    Output_GetAxisMapping _Output_GetAxisMapping = MyClient.GetAxisMapping();
    std::cout << "Axis Mapping: X-" << Adapt( _Output_GetAxisMapping.XAxis ) 
                           << " Y-" << Adapt( _Output_GetAxisMapping.YAxis ) 
                           << " Z-" << Adapt( _Output_GetAxisMapping.ZAxis ) << std::endl;

    // Discover the version number
    Output_GetVersion _Output_GetVersion = MyClient.GetVersion();
    std::cout << "Version: " << _Output_GetVersion.Major << "." 
                             << _Output_GetVersion.Minor << "." 
                             << _Output_GetVersion.Point << std::endl;

    if( EnableMultiCast )
    {
      assert( MyClient.IsConnected().Connected );
      MyClient.StopTransmittingMulticast();
      sleep(1);
      MyClient.StartTransmittingMulticast( HostName, MulticastAddress );
    }

    ROS_INFO("Starting multicast on address %s", MulticastAddress.c_str());

    // wait for a key to be pressed
    std::cout << "Multicast has been started" << std::endl;
    std::cout << "Press Ctrl+C to stop" << std::endl;
    
    while( ros::ok() )
    {
		
      // get ROS stuff done first
      ros::spinOnce();

      // a pause
      loop_rate.sleep();

    }

    // shutting down again
    if( EnableMultiCast )
    {
      MyClient.StopTransmittingMulticast();
    }
    MyClient.DisableSegmentData();
    MyClient.DisableMarkerData();
    MyClient.DisableUnlabeledMarkerData();
    MyClient.DisableDeviceData();
    if( bReadCentroids )
    {
      MyClient.DisableCentroidData();
    }

    // Disconnect and dispose
    int t = clock();
    std::cout << " Disconnecting..." << std::endl;
    MyClient.Disconnect();
    int dt = clock() - t;
    double secs = (double) (dt)/(double)CLOCKS_PER_SEC;
    std::cout << " Disconnect time = " << secs << " secs" << std::endl;

}