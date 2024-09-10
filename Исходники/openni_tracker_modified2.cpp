int main(int argc, char **argv) {
    ros::init(argc, argv, "tracker_2");
    ros::NodeHandle nh;

    string configFilename = ros::package::getPath("openni_tracker_multi") + "/openni_tracker.xml";
    XnStatus nRetVal = g_Context.InitFromXmlFile(configFilename.c_str());
    CHECK_RC(nRetVal, "InitFromXml");

//    XnStatus nRetVal = XN_STATUS_OK;

    //xnLogInitFromXmlFile(csXmlFile);

    nRetVal = g_Context.Init();
    XN_IS_STATUS_OK(nRetVal);


   // SELECTION OF THE DEVICE
    xn::EnumerationErrors errors;
    xn::Device g_Device;
        // find devices
    xn::NodeInfoList list;
    xn::NodeInfoList list_depth;
        nRetVal = g_Context.EnumerateProductionTrees(XN_NODE_TYPE_DEVICE, NULL, list, &errors);
    XN_IS_STATUS_OK(nRetVal);

    printf("The following devices were found:\n");
        int i = 1;
        for (xn::NodeInfoList::Iterator it = list.Begin(); it != list.End(); ++it, ++i)
        {
            xn::NodeInfo deviceNodeInfo = *it;

            xn::Device deviceNode;
            deviceNodeInfo.GetInstance(deviceNode);
            XnBool bExists = deviceNode.IsValid();
            if (!bExists)
            {
                g_Context.CreateProductionTree(deviceNodeInfo, deviceNode);
                // this might fail.
            }

            if (deviceNode.IsValid() && deviceNode.IsCapabilitySupported(XN_CAPABILITY_DEVICE_IDENTIFICATION))
            {
                const XnUInt32 nStringBufferSize = 200;
                XnChar strDeviceName[nStringBufferSize];
                XnChar strSerialNumber[nStringBufferSize];

                XnUInt32 nLength = nStringBufferSize;
                deviceNode.GetIdentificationCap().GetDeviceName(strDeviceName, nLength);
                nLength = nStringBufferSize;
                deviceNode.GetIdentificationCap().GetSerialNumber(strSerialNumber, nLength);
                printf("[%d] %s (%s)\n", i, strDeviceName, strSerialNumber);
            }
            else
            {
                printf("[%d] %s\n", i, deviceNodeInfo.GetCreationInfo());
            }

            // release the device if we created it
            if (!bExists && deviceNode.IsValid())
            {
                deviceNode.Release();
            }
        }
        printf("\n");
        printf("Choose device to open (1): ");

        int chosen=0;
        if (argc != 2)
        {
            printf("Choose device to open (1): ");
            int nRetval = scanf("%d", &chosen);
        }
        else
        {
        chosen = atoi(argv[1]);
        }

            // create it
            xn::NodeInfoList::Iterator it = list.Begin();
            for (i = 1; i < chosen; ++i)
            {
                it++;
            }

        xn::NodeInfo deviceNode = *it;
        nRetVal = g_Context.CreateProductionTree(deviceNode, g_Device);
        printf("Production tree of the device created.\n");

    // SELECTION OF THE DEPTH GENERATOR
        nRetVal = g_Context.EnumerateProductionTrees(XN_NODE_TYPE_DEPTH, NULL, list_depth, &errors);
        XN_IS_STATUS_OK(nRetVal);

        printf("The following devices were found:\n");
            int i_depth = 1;
            for (xn::NodeInfoList::Iterator it_depth = list_depth.Begin(); it_depth != list_depth.End(); ++it_depth, ++i_depth)
            {
                xn::NodeInfo depthNodeInfo = *it_depth;

                xn::Device depthNode;
                depthNodeInfo.GetInstance(depthNode);
                XnBool bExists_depth = depthNode.IsValid();
                if (!bExists_depth)
                {
                    g_Context.CreateProductionTree(depthNodeInfo, depthNode);
                    // this might fail.
                }

                if (depthNode.IsValid() && depthNode.IsCapabilitySupported(XN_CAPABILITY_DEVICE_IDENTIFICATION))
                {
                    const XnUInt32 nStringBufferSize = 200;
                    XnChar strDeviceName[nStringBufferSize];
                    XnChar strSerialNumber[nStringBufferSize];

                    XnUInt32 nLength = nStringBufferSize;
                    depthNode.GetIdentificationCap().GetDeviceName(strDeviceName, nLength);
                    nLength = nStringBufferSize;
                    depthNode.GetIdentificationCap().GetSerialNumber(strSerialNumber, nLength);
                    printf("[%d] %s (%s)\n", i, strDeviceName, strSerialNumber);
                }
                else
                {
                    printf("[%d] %s\n", i, depthNodeInfo.GetCreationInfo());
                }

                // release the device if we created it
                if (!bExists_depth && depthNode.IsValid())
                {
                    depthNode.Release();
                }
            }
            printf("\n");
        printf("Choose device to open (1): ");

        int chosen_depth = 1;
        /*if (argc != 2)
        {
            printf("Choose device to open (1): ");
            int nRetval_depth = scanf("%d", &chosen_depth);
        }
        else
        {
        chosen_depth = atoi(argv[1]);
        }*/


            // create it
            xn::NodeInfoList::Iterator it_depth = list_depth.Begin();
            for (i = 1; i < chosen_depth; ++i)
            {
                it_depth++;
            }

        xn::NodeInfo depthNode = *it_depth;
        nRetVal = g_Context.CreateProductionTree(depthNode, g_DepthGenerator);
        printf("Production tree of the DepthGenerator created.\n");

        nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
        printf("Production tree of the depth generator created.\n");
        XN_IS_STATUS_OK(nRetVal);
        printf("XN_IS_STATUS_OK(nRetVal).\n");



    CHECK_RC(nRetVal, "Find depth generator");
     printf("CHECK_RC(nRetVal, Find depth generator);\n");

    nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);
    printf("User generator found.\n");
    if (nRetVal != XN_STATUS_OK) {
        nRetVal = g_UserGenerator.Create(g_Context);
        printf("User generator created.\n");
        CHECK_RC(nRetVal, "Find user generator");
    }

    if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON)) {
        printf("Supplied user generator doesn't support skeleton.\n");
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
        string frame_id("/kinect2_depth_frame");
        pnh.getParam("camera_frame_id", frame_id);

    while (ros::ok()) {
        g_Context.WaitAndUpdateAll();
        publishTransforms(frame_id);
        r.sleep();
    }

    g_Context.Shutdown();
    return 0;
}