int main(int argc, char **argv){
  ros::init(argc, argv, "pplTracker");
  ros::NodeHandle nh;

  std::string configFilename = ros::package::getPath("people_tracker_denbyk") + "/init/openni_tracker.xml";
  genericUserCalibrationFileName = ros::package::getPath("people_tracker_denbyk") + "/init/GenericUserCalibration.bin";

  ros::Rate loop_rate(1);

  //valore di ritorno Xn
  XnStatus nRetVal;

  //while (ros::ok())
  while (nh.ok())
  {
    //inizializzo contesto openni
    //ROS_INFO(configFilename.c_str(),xnGetStatusString(nRetVal));
    nRetVal = g_Context.InitFromXmlFile(configFilename.c_str());

    //TODO: remove
    nRetVal = XN_STATUS_OK;

    //riprovo tra un po'
    if(nRetVal != XN_STATUS_OK)
    {
      ROS_INFO("InitFromXml failed: %s Retrying in 3 seconds...", xnGetStatusString(nRetVal));
      ros::Duration(3).sleep();

    }
    else
    {
      break;
    }
  }


  //std::string frame_id;

  nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);


  if(nRetVal != XN_STATUS_OK)
  {
    ROS_ERROR("Find depth generator failed: %s", xnGetStatusString(nRetVal));
  }

  //cerca nodo ti tipo user generator e lo salva in g_UserGenerator
  nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);


  if (nRetVal != XN_STATUS_OK)
  {
    //crea lo userGenerator del g_context. SE non riesce probabilmente manca NITE
    nRetVal = g_UserGenerator.Create(g_Context);

    if (nRetVal != XN_STATUS_OK)
    {
      ROS_ERROR("NITE is likely missing: Please install NITE >= 1.5.2.21. Check the readme for download information. Error Info: User generator failed: %s", xnGetStatusString(nRetVal));
      return nRetVal;
    }
  }
  //veriica che lo userGenerator creato supporti SKELETON
  if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON))
  {
    ROS_INFO("Supplied user generator doesn't support skeleton");
    return EXIT_FAILURE;
  }

  //imposto la modalità dello skeleton, quali giunzioni rilevare e quali no.
  //in questo caso upper è il torso/la testa
  g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_UPPER);

  //setto varie callbacks per entrata, uscita e rientro user nello UserGenerator
  XnCallbackHandle hUserCallbacks;
  g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, hUserCallbacks);
  g_UserGenerator.RegisterToUserExit(User_OutOfScene, NULL, hUserCallbacks);
  g_UserGenerator.RegisterToUserReEnter(User_BackIntoScene, NULL, hUserCallbacks);

  //attivo la generazione dei vari generators
  nRetVal = g_Context.StartGeneratingAll();

  if(nRetVal != XN_STATUS_OK)
  {
    ROS_ERROR("StartGenerating failed: %s", xnGetStatusString(nRetVal));
  }

  //recupera un parametro passato al nodo dal server dei parametri ROS.
  //usando la chiave camera_frame_id e lo memorizza nella variabile frame_id
  std::string frame_id("camera_depth_frame");
  nh.getParam("camera_frame_id", frame_id);


  std::cout << "init ok\n";
  //ciclo principale.
  while(nh.ok())
  {
    //aggiorna il contesto e aspetta
    g_Context.WaitAndUpdateAll();
    //pubblica le trasformazioni su frame_id
    publishTransforms(frame_id);
    //dormi per un tot.
    ros::Rate(30).sleep();
  }

  //rilascia risorse e esci.
  g_Context.Shutdown();
  return EXIT_SUCCESS;
}