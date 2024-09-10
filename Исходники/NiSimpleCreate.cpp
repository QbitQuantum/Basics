int main()
{
	XnStatus nRetVal = XN_STATUS_OK;
	Context context;

	nRetVal = context.Init();
	CHECK_RC(nRetVal, "Initialize context");

	DepthGenerator depth;
	nRetVal = depth.Create(context);
	CHECK_RC(nRetVal, "Create depth generator");

	nRetVal = context.StartGeneratingAll();
	CHECK_RC(nRetVal, "StartGeneratingAll");

	DepthMetaData depthMD;
	while (!xnOSWasKeyboardHit())
	{
		nRetVal = context.WaitOneUpdateAll(depth);
		if (nRetVal != XN_STATUS_OK)
		{
			printf("UpdateData failed: %s\n", xnGetStatusString(nRetVal));
			continue;
		}

		depth.GetMetaData(depthMD);
		const XnDepthPixel* pDepthMap = depthMD.Data();

		printf("Frame %d Middle point is: %u.\n", depthMD.FrameID(), depthMD(depthMD.XRes() / 2, depthMD.YRes() / 2));
	}

	context.Shutdown();

	return 0;
}