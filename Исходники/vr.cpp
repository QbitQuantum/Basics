void VR::nextTracking()
{
#if defined(_DEBUG)
	// make sure we are only caled once per frame:
	static vector<bool> called;
	if (xapp->getFramenum() < 50000) {
		size_t framenum = (size_t) xapp->getFramenum();
		assert(called.size() <= framenum);
		called.push_back(true);
		assert(called.size() == framenum+1);
	}
#endif

	// Get both eye poses simultaneously, with IPD offset already included. 
	ovrVector3f useHmdToEyeViewOffset[2] = { eyeRenderDesc[0].HmdToEyeOffset, eyeRenderDesc[1].HmdToEyeOffset };
	//ovrPosef temp_EyeRenderPose[2];
	double displayMidpointSeconds = ovr_GetPredictedDisplayTime(session, 0);
	ovrTrackingState ts = ovr_GetTrackingState(session, displayMidpointSeconds, false);
	ovr_CalcEyePoses(ts.HeadPose.ThePose, useHmdToEyeViewOffset, layer.RenderPose);
	ovrResult result;
	ovrBoundaryTestResult btest;
	ovrBool visible;
	result = ovr_GetBoundaryVisible(session, &visible);
	if (0) {
		Log("visible = " << (visible == ovrTrue) << endl);

		result = ovr_TestBoundary(session, ovrTrackedDevice_HMD, ovrBoundary_Outer, &btest);
		if (OVR_SUCCESS(result)) {
			//Log("boundary success");
			if (result == ovrSuccess) Log("success" << endl);
			if (result == ovrSuccess_BoundaryInvalid) Log("success boundary invalid" << endl);
			if (result == ovrSuccess_DeviceUnavailable) Log("success device unavailable" << endl);
		}
	}
	layer.Fov[0] = eyeRenderDesc[0].Fov;
	layer.Fov[1] = eyeRenderDesc[1].Fov;

	// Render the two undistorted eye views into their render buffers.  
	for (int eye = 0; eye < 2; eye++)
	{
		ovrPosef    * useEyePose = &EyeRenderPose[eye];
		float       * useYaw = &YawAtRender[eye];
		float Yaw = XM_PI;
		*useEyePose = layer.RenderPose[eye];
		*useYaw = Yaw;

		// Get view and projection matrices (note near Z to reduce eye strain)
		Matrix4f rollPitchYaw = Matrix4f::RotationY(Yaw);
		Matrix4f finalRollPitchYaw = rollPitchYaw * Matrix4f(useEyePose->Orientation);
		// fix finalRollPitchYaw for LH coordinate system:
		Matrix4f s = Matrix4f::Scaling(1.0f, -1.0f, -1.0f);  // 1 1 -1
		finalRollPitchYaw = s * finalRollPitchYaw * s;

		Vector3f finalUp = finalRollPitchYaw.Transform(Vector3f(0, 1, 0));
		Vector3f finalForward = finalRollPitchYaw.Transform(Vector3f(0, 0, -1));//0 0 1
		Vector3f Posf;
		Posf.x = xapp->camera.pos.x;
		Posf.y = xapp->camera.pos.y;
		Posf.z = xapp->camera.pos.z;
		Vector3f diff = rollPitchYaw.Transform(useEyePose->Position);
		//diff /= 10.0f;
		//diff.x = 0.0f;
		//diff.y = 0.0f;
		//diff.z = 0.0f;
		Vector3f shiftedEyePos;
		shiftedEyePos.x = Posf.x - diff.x;
		shiftedEyePos.y = Posf.y + diff.y;
		shiftedEyePos.z = Posf.z + diff.z;
		xapp->camera.look.x = finalForward.x;
		xapp->camera.look.y = finalForward.y;
		xapp->camera.look.z = finalForward.z;

		Matrix4f view = Matrix4f::LookAtLH(shiftedEyePos, shiftedEyePos + finalForward, finalUp);
		Matrix4f projO = ovrMatrix4f_Projection(eyeRenderDesc[eye].Fov, 0.2f, 2000.0f,  ovrProjection_LeftHanded);
		Matrix4fToXM(this->viewOVR[eye], view.Transposed());
		Matrix4fToXM(this->projOVR[eye], projO.Transposed());
	}
}