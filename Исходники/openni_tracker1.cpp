int main(int argc, char **argv) {
    ros::init(argc, argv, "openni_tracker1");
    ros::NodeHandle nh;
/*
    string configFilename = ros::package::getPath("openni_tracker1") + "/openni_tracker1.xml";
    XnStatus nRetVal = g_Context.InitFromXmlFile(configFilename.c_str());
    CHECK_RC(nRetVal, "InitFromXml"); */


XnStatus nRetVal = g_Context.Init();
    CHECK_RC(nRetVal, "Init");
    nRetVal = g_Context.OpenFileRecording("/home/latifanjum/Downloads/OpenNI-master/Platform/Linux/Bin/x86-Release/Dataset/Wave2/wave25.oni", g_Player);
    g_Player.SetRepeat( false );
    if (nRetVal != XN_STATUS_OK)
    {
    printf("Can't open recording %s\n", xnGetStatusString(nRetVal));
    return 1;
    }


    nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
    CHECK_RC(nRetVal, "Find depth generator");

	nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);
	if (nRetVal != XN_STATUS_OK) {
		nRetVal = g_UserGenerator.Create(g_Context);
		CHECK_RC(nRetVal, "Find user generator");
	}

	if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON)) {
		ROS_INFO("Supplied user generator doesn't support skeleton");
		return 1;
	}

    XnCallbackHandle hUserCallbacks;
	g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, hUserCallbacks);

	XnCallbackHandle hCalibrationCallbacks;
	g_UserGenerator.GetSkeletonCap().RegisterCalibrationCallbacks(UserCalibration_CalibrationStart, UserCalibration_CalibrationEnd, NULL, hCalibrationCallbacks);

	if (g_UserGenerator.GetSkeletonCap().NeedPoseForCalibration()) {
		g_bNeedPose = TRUE;
		if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION)) {
			ROS_INFO("Pose required, but not supported");
			return 1;
		}

		XnCallbackHandle hPoseCallbacks;
		g_UserGenerator.GetPoseDetectionCap().RegisterToPoseCallbacks(UserPose_PoseDetected, NULL, NULL, hPoseCallbacks);

		g_UserGenerator.GetSkeletonCap().GetCalibrationPose(g_strPose);
	}

	g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

	nRetVal = g_Context.StartGeneratingAll();
	CHECK_RC(nRetVal, "StartGenerating");

	ros::Rate r(30);

        
        ros::NodeHandle pnh("~");
        string frame_id("openni_depth_frame");
        pnh.getParam("camera_frame_id", frame_id);
                
	while (ros::ok()) {
		g_Context.WaitAndUpdateAll();
		publishTransforms(frame_id);
		r.sleep();
	}

	g_Context.Shutdown();
	return 0;
}