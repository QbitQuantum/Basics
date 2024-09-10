int main(int argc, char **argv)
{
ros::init(argc, argv, "openni_tracker");
ros::NodeHandle nh, nh_private("~");
ROS_INFO_STREAM("Initialising OpenNI tracker ...");

default_user =  0;
available_tracked_users_pub = nh_private.advertise<std_msgs::UInt16MultiArray>("available_users", 10, true);
default_user_pub = nh_private.advertise<std_msgs::UInt16>("tracked_user", 10, true);
user_chooser_sub = nh_private.subscribe("user_chooser", 10, userChooserCallback);

string configFilename = ros::package::getPath("openni_tracker") + "/openni_tracker.xml";
ROS_INFO_STREAM("Setting up configuration from XML file '" << configFilename << "'");
XnStatus nRetVal = g_Context.InitFromXmlFile(configFilename.c_str());
CHECK_RC(nRetVal, "InitFromXml");

ROS_INFO_STREAM("Looking for existing depth generators ...");
nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
CHECK_RC(nRetVal, "Find depth generator");
ROS_INFO_STREAM("nRetVal: " << xnGetStatusString(nRetVal));

ROS_INFO_STREAM("Looking for existing user generators ...");
nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);
ROS_INFO_STREAM("nRetVal: " << xnGetStatusString(nRetVal));

if (nRetVal != XN_STATUS_OK)
{
  nRetVal = g_UserGenerator.Create(g_Context);
  CHECK_RC(nRetVal, "Find user generator");
  ROS_INFO_STREAM("No existing user generators found. Created new one.");
  ROS_INFO_STREAM("nRetVal: " << xnGetStatusString(nRetVal));
}

if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON))
{
  ROS_INFO_STREAM("Supplied user generator doesn't support skeleton");
  return 1;
}

ROS_INFO_STREAM("Registering user callbacks ...");
XnCallbackHandle hUserCallbacks;
g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, hUserCallbacks);

ROS_INFO_STREAM("Registering calibration callbacks ...");
XnCallbackHandle hCalibrationCallbacks;
g_UserGenerator.GetSkeletonCap().RegisterCalibrationCallbacks(UserCalibration_CalibrationStart,
                                                              UserCalibration_CalibrationEnd, NULL,
                                                              hCalibrationCallbacks);

ROS_INFO_STREAM("Checking pose detection capability ...");
if (g_UserGenerator.GetSkeletonCap().NeedPoseForCalibration())
{
  g_bNeedPose = TRUE;
  if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION))
  {
    ROS_INFO_STREAM("Pose required, but not supported");
    return 1;
  }

  ROS_INFO_STREAM("Registering pose callbacks ...");
  XnCallbackHandle hPoseCallbacks;
  g_UserGenerator.GetPoseDetectionCap().RegisterToPoseCallbacks(UserPose_PoseDetected, NULL, NULL, hPoseCallbacks);

  ROS_INFO_STREAM("Getting calibration pose ...");
  g_UserGenerator.GetSkeletonCap().GetCalibrationPose(g_strPose);
}

ROS_INFO_STREAM("Setting skeleton profile ...");
g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

//g_Context.Release();

ROS_INFO_STREAM("Starting to generate everything ...");
nRetVal = g_Context.StartGeneratingAll();
CHECK_RC(nRetVal, "StartGenerating");
ROS_INFO_STREAM("nRetVal: " << xnGetStatusString(nRetVal));

ROS_INFO_STREAM("Stopping to generate everything ...");
nRetVal = g_Context.StopGeneratingAll();
ROS_INFO_STREAM("nRetVal: " << xnGetStatusString(nRetVal));

ROS_INFO_STREAM("Starting to generate everything ...");
nRetVal = g_Context.StartGeneratingAll();
ROS_INFO_STREAM("nRetVal: " << xnGetStatusString(nRetVal));

ROS_INFO_STREAM("Setting up ROS node ...");
ros::Rate r(30);
ros::NodeHandle pnh("~");
string frame_id("openni_depth_frame");
pnh.getParam("camera_frame_id", frame_id);

nRetVal = g_Context.GetGlobalErrorState();
ROS_INFO_STREAM("nRetVal: " << xnGetStatusString(nRetVal));

ROS_INFO_STREAM("And go!");

while (ros::ok())
{
  ros::spinOnce();
  nRetVal = g_Context.WaitAndUpdateAll();
  CHECK_RC(nRetVal, "WaitAndUpdateAll");
  publishTransforms(frame_id);
  r.sleep();
}

g_Context.StopGeneratingAll();
g_Context.Release();
g_Context.Shutdown();
return 0;
}