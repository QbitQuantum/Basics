int main(int argc, char **argv) {
	ros::init(argc, argv, "PersonTracker");
	ros::NodeHandle nh;
	ros::Rate loop_rate(10);
    ROS_INFO("Initalizing Arm Connection....");
    ros::Publisher leftArmPublisher = nh.advertise<prlite_kinematics::SphereCoordinate>("/armik/n0/position", 1000);
    ros::Publisher rightArmPublisher = nh.advertise<prlite_kinematics::SphereCoordinate>("/armik/n1/position", 1000);
	yourmom = nh.advertise<prlite_kinematics::some_status_thing>("kinect_hack_status", 1000);
    ros::Duration(2.0).sleep();
    prlite_kinematics::SphereCoordinate coord;
	prlite_kinematics::some_status_thing status;
    coord.radius = 35.0;
    coord.phi = 0.0;
    coord.theta = 0.0;
	status.lulz = 0;	//initialized/reset
	yourmom.publish(status);
    leftArmPublisher.publish(coord);
    rightArmPublisher.publish(coord);
	ROS_INFO("Initalizing Kinect + NITE....");
	XnStatus nRetVal = XN_STATUS_OK;
	xn::EnumerationErrors errors;
	nRetVal = g_Context.InitFromXmlFile(SAMPLE_XML_PATH, &errors);
	
	if (nRetVal == XN_STATUS_NO_NODE_PRESENT)
	{
		XnChar strError[1024];
		errors.ToString(strError, 1024);
		printf("%s\n", strError);
		return (nRetVal);
	} else if (nRetVal != XN_STATUS_OK) {
		printf("Open failed: %s\n", xnGetStatusString(nRetVal));
		return (nRetVal);
	}

	nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
	CHECK_RC(nRetVal, "Find depth generator");
	nRetVal = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);
	if (nRetVal != XN_STATUS_OK)
	{
		nRetVal = g_UserGenerator.Create(g_Context);
		CHECK_RC(nRetVal, "Find user generator");
	}

	XnCallbackHandle hUserCallbacks, hCalibrationCallbacks, hPoseCallbacks;
	if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON))
	{
		printf("Supplied user generator doesn't support skeleton\n");
		return 1;
	}
	g_UserGenerator.RegisterUserCallbacks(User_NewUser, User_LostUser, NULL, hUserCallbacks);
	g_UserGenerator.GetSkeletonCap().RegisterCalibrationCallbacks(UserCalibration_CalibrationStart, UserCalibration_CalibrationEnd, NULL, hCalibrationCallbacks);

	if (g_UserGenerator.GetSkeletonCap().NeedPoseForCalibration())
	{
		g_bNeedPose = TRUE;
		if (!g_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION))
		{
			printf("Pose required, but not supported\n");
			return 1;
		}
		g_UserGenerator.GetPoseDetectionCap().RegisterToPoseCallbacks(UserPose_PoseDetected, NULL, NULL, hPoseCallbacks);
		g_UserGenerator.GetSkeletonCap().GetCalibrationPose(g_strPose);
	}

	g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);

	nRetVal = g_Context.StartGeneratingAll();
	CHECK_RC(nRetVal, "StartGenerating");
    ROS_INFO("Ready To Go!\n");

	while (ros::ok()) {
		// Update OpenNI
		g_Context.WaitAndUpdateAll();
		xn::SceneMetaData sceneMD;
		xn::DepthMetaData depthMD;
		g_DepthGenerator.GetMetaData(depthMD);
		g_UserGenerator.GetUserPixels(0, sceneMD);
		// Print positions
		XnUserID aUsers[15];
		XnUInt16 nUsers = 15;
		g_UserGenerator.GetUsers(aUsers, nUsers);
		for (int i = 0; i < nUsers; ++i) {
			if(g_UserGenerator.GetSkeletonCap().IsTracking(aUsers[i])) {
				// Read joint positions for person (No WRISTs)
				XnSkeletonJointPosition torsoPosition, lShoulderPosition, rShoulderPosition, neckPosition, headPosition, lElbowPosition, rElbowPosition;
                XnSkeletonJointPosition rWristPosition, lWristPosition, rHipPosition, lHipPosition, lKneePosition, rKneePosition;
                XnSkeletonJointPosition lFootPosition, rFootPosition;
				g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_TORSO, torsoPosition);
                g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_NECK, neckPosition);
                g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_HEAD, headPosition);
				g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_LEFT_SHOULDER, lShoulderPosition);
				g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_RIGHT_SHOULDER, rShoulderPosition);
				g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_LEFT_ELBOW, lElbowPosition);
				g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_RIGHT_ELBOW, rElbowPosition);
				g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_LEFT_HAND, lWristPosition);
				g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_RIGHT_HAND, rWristPosition);
                g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_LEFT_HIP, lHipPosition);
                g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_RIGHT_HIP, rHipPosition);
                g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_LEFT_KNEE, lKneePosition);
                g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_RIGHT_KNEE, rKneePosition);
                g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_LEFT_FOOT, lFootPosition);
                g_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_RIGHT_FOOT, rFootPosition);

                // Read Joint Orientations
                XnSkeletonJointOrientation torsoOrientation, lShoulderOrientation, rShoulderOrientation, lHipOrientation, rHipOrientation;
                XnSkeletonJointOrientation lWristOrientation, rWristOrientation, lElbowOrientation, rElbowOrientation;
                XnSkeletonJointOrientation headOrientation, neckOrientation;
                XnSkeletonJointOrientation lKneeOrientation, rKneeOrientation, lFootOrientation, rFootOrientation;
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_TORSO, torsoOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_HEAD, headOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_NECK, neckOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_LEFT_SHOULDER, lShoulderOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_RIGHT_SHOULDER, rShoulderOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_LEFT_HIP, lHipOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_RIGHT_HIP, rHipOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_LEFT_ELBOW, lElbowOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_RIGHT_ELBOW, rElbowOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_LEFT_HAND, lWristOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_RIGHT_HAND, rWristOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_LEFT_KNEE, lKneeOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_RIGHT_KNEE, rKneeOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_LEFT_FOOT, lFootOrientation);
	            g_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_RIGHT_FOOT, rFootOrientation);

	            XnFloat* m = torsoOrientation.orientation.elements;
	            KDL::Rotation torsoO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = lShoulderOrientation.orientation.elements;
                KDL::Rotation lShouldO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = rShoulderOrientation.orientation.elements;
                KDL::Rotation rShouldO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = lHipOrientation.orientation.elements;
                KDL::Rotation lHipO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = rHipOrientation.orientation.elements;
                KDL::Rotation rHipO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = headOrientation.orientation.elements;
                KDL::Rotation headO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = neckOrientation.orientation.elements;
                KDL::Rotation neckO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = lElbowOrientation.orientation.elements;
                KDL::Rotation lElbowO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = rElbowOrientation.orientation.elements;
                KDL::Rotation rElbowO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = lWristOrientation.orientation.elements;
                KDL::Rotation lWristO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = rWristOrientation.orientation.elements;
                KDL::Rotation rWristO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = lKneeOrientation.orientation.elements;
                KDL::Rotation lKneeO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = rKneeOrientation.orientation.elements;
                KDL::Rotation rKneeO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = lFootOrientation.orientation.elements;
                KDL::Rotation lFootO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);
                m = rFootOrientation.orientation.elements;
                KDL::Rotation rFootO(m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);

	            double qx = 0.0, qy = 0.0, qz = 0.0, qw = 0.0;

				// Get Points in 3D space
				XnPoint3D torso = torsoPosition.position;
				XnPoint3D lShould = lShoulderPosition.position;
				XnPoint3D rShould = rShoulderPosition.position;
                XnPoint3D lElbow = lElbowPosition.position;
                XnPoint3D rElbow = rElbowPosition.position;
                XnPoint3D lWrist = lWristPosition.position;
                XnPoint3D rWrist = rWristPosition.position;
                XnPoint3D neck = neckPosition.position;
                XnPoint3D head = headPosition.position;
                XnPoint3D lHip = lHipPosition.position;
                XnPoint3D rHip = rHipPosition.position;
                XnPoint3D lKnee = lKneePosition.position;
                XnPoint3D rKnee = rKneePosition.position;
                XnPoint3D lFoot = lFootPosition.position;
                XnPoint3D rFoot = rFootPosition.position;

                // ---------- ARM CONTROLLER HACK ------------------

                // Calculate arm length of user
                double lenL = calc3DDist( lShould, lElbow ) + calc3DDist( lElbow, lWrist );
                double lenR = calc3DDist( rShould, rElbow ) + calc3DDist( rElbow, rWrist );
                double distL = calc3DDist(lShould, lWrist);
                double distR = calc3DDist(rShould, rWrist);

                // Calculate positions
                prlite_kinematics::SphereCoordinate lCoord;
                prlite_kinematics::SphereCoordinate rCoord;

                lCoord.radius = 35 * (distL / lenL);
                rCoord.radius = 35 * (distR / lenR);

                lCoord.theta = -atan2(lShould.X - lWrist.X, lShould.Z - lWrist.Z);
                rCoord.theta = -atan2(rShould.X - rWrist.X, rShould.Z - rWrist.Z);
                if(lCoord.theta > 1.0) lCoord.theta = 1.0;
                if(lCoord.theta < -1.0) lCoord.theta = -1.0;
                if(rCoord.theta > 1.0) rCoord.theta = 1.0;
                if(rCoord.theta < -1.0) rCoord.theta = -1.0;

                lCoord.phi = -atan2(lShould.Y - lWrist.Y, lShould.X - lWrist.X);
                rCoord.phi = -atan2(rShould.Y - rWrist.Y, rShould.X - rWrist.X);
                if(lCoord.phi > 1.25) lCoord.phi = 1.25;
                if(lCoord.phi < -0.33) lCoord.phi = -0.33;
                if(rCoord.phi > 1.2) rCoord.phi = 1.25;
                if(rCoord.phi < -0.33) rCoord.phi = -0.33;

                ROS_INFO("User %d: Left (%lf,%lf,%lf), Right (%lf,%lf,%lf)", i, lCoord.radius, lCoord.theta, lCoord.phi, rCoord.radius, rCoord.theta, rCoord.phi);

                // Publish to arms
                leftArmPublisher.publish(rCoord);
                rightArmPublisher.publish(lCoord);

                // ---------- END HACK -----------------

                // Publish Transform
                static tf::TransformBroadcaster br;
                tf::Transform transform;
                std::stringstream body_name, neck_name, lshould_name, rshould_name, head_name, relbow_name, lelbow_name, lwrist_name, rwrist_name;
                std::stringstream lhip_name, rhip_name, lknee_name, rknee_name, lfoot_name, rfoot_name;
                body_name << "Torso (" << i << ")" << std::ends;
                neck_name << "Neck (" << i << ")" << std::ends;
                head_name << "Head (" << i << ")" << std::ends;
                lshould_name << "Shoulder L (" << i << ")" << std::ends;
                rshould_name << "Shoulder R (" << i << ")" << std::ends;
                lelbow_name << "Elbow L (" << i << ")" << std::ends;
                relbow_name << "Elbow R (" << i << ")" << std::ends;
                lwrist_name << "Wrist L (" << i << ")" << std::ends;
                rwrist_name << "Wrist R (" << i << ")" << std::ends;
                lhip_name << "Hip L (" << i << ")" << std::ends;
                rhip_name << "Hip R (" << i << ")" << std::ends;
                lknee_name << "Knee L (" << i << ")" << std::ends;
                rknee_name << "Knee R (" << i << ")" << std::ends;
                lfoot_name << "Foot L (" << i << ")" << std::ends;
                rfoot_name << "Foot R (" << i << ")" << std::ends;

                // Publish Torso
                torsoO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(torso.X / ADJUST_VALUE, torso.Y / ADJUST_VALUE, torso.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", body_name.str().c_str()));  
                // Publish Left Shoulder
                lShouldO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(lShould.X / ADJUST_VALUE, lShould.Y / ADJUST_VALUE, lShould.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", lshould_name.str().c_str()));
                // Publish Right Shoulder
                rShouldO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(rShould.X / ADJUST_VALUE, rShould.Y / ADJUST_VALUE, rShould.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", rshould_name.str().c_str())); 
                // Publish Left Elbow
                lElbowO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(lElbow.X / ADJUST_VALUE, lElbow.Y / ADJUST_VALUE, lElbow.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", lelbow_name.str().c_str()));
                // Publish Right Elbow
                rElbowO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(rElbow.X / ADJUST_VALUE, rElbow.Y / ADJUST_VALUE, rElbow.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", relbow_name.str().c_str()));
                // Publish Left Wrist
                lWristO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(lWrist.X / ADJUST_VALUE, lWrist.Y / ADJUST_VALUE, lWrist.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", lwrist_name.str().c_str()));
                // Publish Right Wrist
                rWristO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(rWrist.X / ADJUST_VALUE, rWrist.Y / ADJUST_VALUE, rWrist.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", rwrist_name.str().c_str()));
                // Publish Neck
                neckO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(neck.X / ADJUST_VALUE, neck.Y / ADJUST_VALUE, neck.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", neck_name.str().c_str())); 
                // Publish Head
                headO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(head.X / ADJUST_VALUE, head.Y / ADJUST_VALUE, head.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", head_name.str().c_str()));
                // Publish Left Hip
                lHipO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(lHip.X / ADJUST_VALUE, lHip.Y / ADJUST_VALUE, lHip.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", lhip_name.str().c_str()));
                // Publish Right Hip
                rHipO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(rHip.X / ADJUST_VALUE, rHip.Y / ADJUST_VALUE, rHip.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", rhip_name.str().c_str())); 
                // Publish Left Knee
                lKneeO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(lKnee.X / ADJUST_VALUE, lKnee.Y / ADJUST_VALUE, lKnee.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", lknee_name.str().c_str()));
                // Publish Right Knee
                rKneeO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(rKnee.X / ADJUST_VALUE, rKnee.Y / ADJUST_VALUE, rKnee.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", rknee_name.str().c_str())); 
                // Publish Left Foot
                lFootO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(lFoot.X / ADJUST_VALUE, lFoot.Y / ADJUST_VALUE, lFoot.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", lfoot_name.str().c_str()));
                // Publish Right Foot
                rFootO.GetQuaternion(qx, qy, qz, qw);
                transform.setOrigin(tf::Vector3(rFoot.X / ADJUST_VALUE, rFoot.Y / ADJUST_VALUE, rFoot.Z / ADJUST_VALUE));
                transform.setRotation(tf::Quaternion(qx, qy, qz, qw));
                br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", rfoot_name.str().c_str()));
			}
		}
		ros::spinOnce();
		//loop_rate.sleep();
	}
	g_Context.Shutdown();
	return 0;
}