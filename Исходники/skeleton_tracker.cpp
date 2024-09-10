int main(int argc, char **argv) {
    ros::init(argc, argv, "skeleton_tracker");
    ros::NodeHandle nh;
    // Added by Igor
    ros::Duration time(2.0);
    time.sleep();
    ROS_INFO("******************************* KINECT CALIBRATION ************************************");
    ROS_INFO("- Do initial calibration pose");

    string configFilename = ros::package::getPath("skeleton_tracker") + "/skeleton_tracker.xml";
    XnStatus nRetVal = g_Context.InitFromXmlFile(configFilename.c_str());
    CHECK_RC(nRetVal, "InitFromXml");

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


    //ros::NodeHandle pnh("~");
    ros::NodeHandle pnh("~");
    string frame_id("openni_depth_frame");
    pnh.getParam("camera_frame_id", frame_id);

    //Added by IGOR
    skeleton_pub = nh.advertise<skeleton_tracker::Skeleton>("skeleton", 1000);

    while (ros::ok()) {

        g_Context.WaitAndUpdateAll();
        publishTransforms(frame_id);

        //ROS_INFO("Lx: %f, Ly: %f, Lz: %f", msg.left_hand_x, msg.left_hand_y, msg.left_hand_z);
        //ROS_INFO("Rx: %f, Ry: %f, Rz: %f", msg.right_hand_x, msg.right_hand_y, msg.right_hand_z);
        skeleton_pub.publish(skelMsg);
        ros::spinOnce();

        r.sleep();
    }

    g_Context.Shutdown();
    return 0;
}