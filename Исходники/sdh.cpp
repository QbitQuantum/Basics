		/*!
		* \brief Initializes node to get parameters, subscribe and publish to topics.
		*/
		bool init()
		{
			// initialize member variables
			isInitialized_ = false;
			isDSAInitialized_ = false;
			hasNewGoal_ = false;

			// implementation of topics to publish
			topicPub_JointState_ = nh_.advertise<sensor_msgs::JointState>("/joint_states", 1);
			topicPub_ControllerState_ = nh_.advertise<pr2_controllers_msgs::JointTrajectoryControllerState>("state", 1);
			topicPub_TactileSensor_ = nh_.advertise<schunk_sdh::TactileSensor>("tactile_data", 1);

			// pointer to sdh
			sdh_ = new SDH::cSDH(false, false, 0); //(_use_radians=false, bool _use_fahrenheit=false, int _debug_level=0)

			// implementation of service servers
			srvServer_Init_ = nh_.advertiseService("init", &SdhNode::srvCallback_Init, this);
			srvServer_Stop_ = nh_.advertiseService("stop", &SdhNode::srvCallback_Stop, this);
			srvServer_Recover_ = nh_.advertiseService("recover", &SdhNode::srvCallback_Recover, this);
			srvServer_SetOperationMode_ = nh_.advertiseService("set_operation_mode", &SdhNode::srvCallback_SetOperationMode, this);

			// getting hardware parameters from parameter server
			nh_.param("sdhdevicetype", sdhdevicetype_, std::string("PCAN"));
			nh_.param("sdhdevicestring", sdhdevicestring_, std::string("/dev/pcan0"));
			nh_.param("sdhdevicenum", sdhdevicenum_, 0);
			
			nh_.param("dsadevicestring", dsadevicestring_, std::string("/dev/ttyS0"));
			nh_.param("dsadevicenum", dsadevicenum_, 0);
			
			nh_.param("baudrate", baudrate_, 1000000);
			nh_.param("timeout", timeout_, (double)0.04);
			nh_.param("id_read", id_read_, 43);
			nh_.param("id_write", id_write_, 42);

			// get joint_names from parameter server
			ROS_INFO("getting joint_names from parameter server");
			XmlRpc::XmlRpcValue joint_names_param;
			if (nh_.hasParam("joint_names"))
			{
				nh_.getParam("joint_names", joint_names_param);
			}
			else
			{
				ROS_ERROR("Parameter joint_names not set, shutting down node...");
				nh_.shutdown();
				return false;
			}
			DOF_ = joint_names_param.size();
			joint_names_.resize(DOF_);
			for (int i = 0; i<DOF_; i++ )
			{
				joint_names_[i] = (std::string)joint_names_param[i];
			}
			std::cout << "joint_names = " << joint_names_param << std::endl;
			
			// define axes to send to sdh
			axes_.resize(DOF_);
			for(int i=0; i<DOF_; i++)
			{
				axes_[i] = i;
			}
			ROS_INFO("DOF = %d",DOF_);
			
			state_.resize(axes_.size());
			
			return true;
		}