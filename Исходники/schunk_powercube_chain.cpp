  /*!
   * \brief Gets parameters from the ROS parameter server and configures the powercube_chain.
   */
  void getROSParameters()
  {

    /// get CanModule
    std::string CanModule;
    if (n_.hasParam("can_module"))
    {
    	n_.getParam("can_module", CanModule);
    }

    else
    {
    	ROS_ERROR("Parameter can_module not set, shutting down node...");
		n_.shutdown();
    }

    /// get CanDevice
    std::string CanDevice;
    if (n_.hasParam("can_device"))
    {
    	n_.getParam("can_device", CanDevice);
    }

    else
    {
    	ROS_ERROR("Parameter can_device not set, shutting down node...");
		  n_.shutdown();
    }

    /// get CanBaudrate
    int CanBaudrate;
    if (n_.hasParam("can_baudrate"))
    {
    	n_.getParam("can_baudrate", CanBaudrate);
    }
    else
    {
    	ROS_ERROR("Parameter can_baudrate not set, shutting down node...");
    	n_.shutdown();
    }

    /// get Modul IDs
    XmlRpc::XmlRpcValue ModulIDsXmlRpc;
    std::vector<int> ModulIDs;
    if (n_.hasParam("modul_ids"))
    {
    	n_.getParam("modul_ids", ModulIDsXmlRpc);
    }

    else
    {
    	ROS_ERROR("Parameter modul_ids not set, shutting down node...");
    	n_.shutdown();
    }

    /// get force_use_movevel
    bool UseMoveVel;
    if (n_.hasParam("force_use_movevel"))
    {
    	n_.getParam("force_use_movevel", UseMoveVel);
		ROS_INFO("Parameter force_use_movevel set, using moveVel");
    }
    else
    {
    	ROS_INFO("Parameter force_use_movevel not set, using moveStep");
		UseMoveVel = false;
    }
	pc_params_->SetUseMoveVel(UseMoveVel);

    /// Resize and assign of values to the ModulIDs
    ModulIDs.resize(ModulIDsXmlRpc.size());
    for (int i = 0; i < ModulIDsXmlRpc.size(); i++)
    {
    	ModulIDs[i] = (int)ModulIDsXmlRpc[i];
    }

    /// Initialize parameters
    pc_params_->Init(CanModule, CanDevice, CanBaudrate, ModulIDs);

    /// Get joint names
    XmlRpc::XmlRpcValue JointNamesXmlRpc;
    std::vector<std::string> JointNames;
    if (n_.hasParam("joint_names"))
    {
    	n_.getParam("joint_names", JointNamesXmlRpc);
    }

    else
    {
    	ROS_ERROR("Parameter joint_names not set, shutting down node...");
    	n_.shutdown();
    }

    /// Resize and assign of values to the JointNames
    JointNames.resize(JointNamesXmlRpc.size());
    for (int i = 0; i < JointNamesXmlRpc.size(); i++)
    {
    	JointNames[i] = (std::string)JointNamesXmlRpc[i];
    }

    /// Check dimension with with DOF
    if ((int)JointNames.size() != pc_params_->GetDOF())
    {
    	ROS_ERROR("Wrong dimensions of parameter joint_names, shutting down node...");
    	n_.shutdown();
    }
    pc_params_->SetJointNames(JointNames);

    /// Get max accelerations
    XmlRpc::XmlRpcValue MaxAccelerationsXmlRpc;
    std::vector<double> MaxAccelerations;
    if (n_.hasParam("max_accelerations"))
    {
    	n_.getParam("max_accelerations", MaxAccelerationsXmlRpc);
    }

    else
    {
    	ROS_ERROR("Parameter max_accelerations not set, shutting down node...");
    	n_.shutdown();
    }

    /// Resize and assign of values to the MaxAccelerations
    MaxAccelerations.resize(MaxAccelerationsXmlRpc.size());
    for (int i = 0; i < MaxAccelerationsXmlRpc.size(); i++)
    {
    	MaxAccelerations[i] = (double)MaxAccelerationsXmlRpc[i];
    }

    /// Check dimension with with DOF
    if ((int)MaxAccelerations.size() != pc_params_->GetDOF())
    {
    	ROS_ERROR("Wrong dimensions of parameter max_accelerations, shutting down node...");
    	n_.shutdown();
    }
    pc_params_->SetMaxAcc(MaxAccelerations);

    /// Get horizon
    double Horizon;
    if (n_.hasParam("horizon"))
    {
    	n_.getParam("horizon", Horizon);
    }

    else
    {
    	/// Horizon in sec
    	Horizon = 0.05;
    	ROS_WARN("Parameter horizon not available, setting to default value: %f sec", Horizon);
    }
    pc_ctrl_->setHorizon(Horizon);
  }