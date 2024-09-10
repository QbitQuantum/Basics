  /*!
   * \brief Gets parameters from the ROS parameter server and configures the powercube_chain.
   */
  void getROSParameters()
  {
    // get CanModule
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

    // get CanDevice
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

    // get CanBaudrate
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

    // get modul ids
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
    ModulIDs.resize(ModulIDsXmlRpc.size());
    for (int i = 0; i < ModulIDsXmlRpc.size(); i++)
    {
      ModulIDs[i] = (int)ModulIDsXmlRpc[i];
    }

    // init parameters
    pc_params_->Init(CanModule, CanDevice, CanBaudrate, ModulIDs);

    // get joint names
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
    JointNames.resize(JointNamesXmlRpc.size());
    for (int i = 0; i < JointNamesXmlRpc.size(); i++)
    {
      JointNames[i] = (std::string)JointNamesXmlRpc[i];
    }
    // check dimension with with DOF
    if ((int)JointNames.size() != pc_params_->GetDOF())
    {
      ROS_ERROR("Wrong dimensions of parameter joint_names, shutting down node...");
      n_.shutdown();
    }
    pc_params_->SetJointNames(JointNames);

    // get max accelerations
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
    MaxAccelerations.resize(MaxAccelerationsXmlRpc.size());
    for (int i = 0; i < MaxAccelerationsXmlRpc.size(); i++)
    {
      MaxAccelerations[i] = (double)MaxAccelerationsXmlRpc[i];
    }
    // check dimension with with DOF
    if ((int)MaxAccelerations.size() != pc_params_->GetDOF())
    {
      ROS_ERROR("Wrong dimensions of parameter max_accelerations, shutting down node...");
      n_.shutdown();
    }
    pc_params_->SetMaxAcc(MaxAccelerations);

    // get horizon
    double Horizon;
    if (n_.hasParam("horizon"))
    {
      n_.getParam("horizon", Horizon);
    }
    else
    {
      Horizon = 0.025; //Hz
      ROS_WARN("Parameter horizon not available, setting to default value: %f sec", Horizon);
    }
    pc_ctrl_->setHorizon(Horizon);
  }