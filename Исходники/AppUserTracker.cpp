int main() {
	printf("main() START\n");
	signal(SIGINT, onSignalReceived); // hit CTRL-C keys in terminal (2)
	signal(SIGTERM, onSignalReceived); // hit stop button in eclipse CDT (15)

	mapMode.nXRes = XN_VGA_X_RES;
	mapMode.nYRes = XN_VGA_Y_RES;
	mapMode.nFPS = 30;

	CHECK_RC(ctx.Init(), "init");
	CHECK_RC(depthGenerator.Create(ctx), "create depth");
	depthGenerator.SetMapOutputMode(mapMode);

	XnStatus userAvailable = ctx.FindExistingNode(XN_NODE_TYPE_USER, userGenerator);
	if(userAvailable != XN_STATUS_OK) {
		CHECK_RC(userGenerator.Create(ctx), "create user");
	}

	XnCallbackHandle hUserCallbacks, hCalibrationCallbacks, hPoseCallbacks;
	xn::SkeletonCapability skel = userGenerator.GetSkeletonCap();
	CHECK_RC(userGenerator.RegisterUserCallbacks(onUserNew, onUserLost, NULL, hUserCallbacks), "register user");
	CHECK_RC(skel.RegisterCalibrationCallbacks(onCalibrationStart, onCalibrationEnd, NULL, hCalibrationCallbacks), "register calib");
	CHECK_RC(userGenerator.GetPoseDetectionCap().RegisterToPoseCallbacks(onPoseDetected, NULL, NULL, hPoseCallbacks), "register pose");

	XnChar poseName[20] = "";
	CHECK_RC(skel.GetCalibrationPose(poseName), "get posename");
	printf("poseName: %s\n", poseName);
	CHECK_RC(skel.SetSkeletonProfile(XN_SKEL_PROFILE_ALL), "set skel profile");
	CHECK_RC(skel.SetSmoothing(0.8), "set smoothing");
//	xnSetMirror(depth, !mirrorMode);

	CHECK_RC(ctx.StartGeneratingAll(), "start generating");

	printf("waitAnyUpdateAll ...\n");
	while(!shouldTerminate) {
		ctx.WaitAnyUpdateAll();
//		depthGenerator.GetMetaData(tempDepthMetaData);

		const XnUInt16 userCount = userGenerator.GetNumberOfUsers();
//		printf("userCount: %i\n", userCount);
		XnUserID aUsers[userCount];
		XnUInt16 nUsers = userCount;
		userGenerator.GetUsers(aUsers, nUsers);
		for (int i = 0; i < nUsers; ++i) {
			XnUserID currentUserId = aUsers[i];
			if (skel.IsTracking(aUsers[i])) {
				XnSkeletonJointPosition joint;
				skel.GetSkeletonJointPosition(currentUserId, XN_SKEL_HEAD, joint);
				XnFloat x = joint.position.X;
				XnFloat y = joint.position.Y;
				XnFloat z = joint.position.Z;
				printf("joint position: %.2f x %.2f x %.2f\n", x, y, z);
				printf("joint.fConfidence: %.2f\n", joint.fConfidence);
			}
		}
	}
	printf("STOP\n");
	CHECK_RC(ctx.StopGeneratingAll(), "stop generating");
	ctx.Shutdown();

	printf("main() END\n");
}