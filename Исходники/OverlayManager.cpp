void OverlayManager::TrackingUpdate(std::vector<std::shared_ptr<Overlay>>::iterator it, vr::VRControllerState_t controllerState, vr::TrackedDevicePose_t controllerPose, bool controllerInOverlay, vr::IVRSystem* vrSys, vr::IVRCompositor* vrComp)
{
	vr::TrackedDeviceIndex_t controller1 = -1;
	vr::TrackedDeviceIndex_t controller2 = -1;

	vr::VRControllerState_t hmdState;
	vr::VRControllerState_t controller1State;
	vr::VRControllerState_t controller2State;

	vr::TrackedDevicePose_t hmdPose;
	vr::TrackedDevicePose_t controller1Pose;
	vr::TrackedDevicePose_t controller2Pose;

	

	for (int i = 0; i < vr::k_unMaxTrackedDeviceCount; i++)
	{
		switch (vrSys->GetTrackedDeviceClass(i))
		{
		case vr::TrackedDeviceClass_Controller:
			if (controller1 == -1)
			{
				controller1 = i;
			}
			if (controller1 >= 0 && i != controller1)
			{
				controller2 = i;
			}
			if (controller2 >= 0)
			{
				break;
			}
		}
	}

	vrSys->GetControllerStateWithPose(vrComp->GetTrackingSpace(), controller1, &controller1State, sizeof(controller1State), &controller1Pose);
	vrSys->GetControllerStateWithPose(vrComp->GetTrackingSpace(), controller2, &controller2State, sizeof(controller2State), &controller2Pose);
	vrSys->GetControllerStateWithPose(vrComp->GetTrackingSpace(), vr::k_unTrackedDeviceIndex_Hmd,  &hmdState, sizeof(hmdState), &hmdPose);


	if (controllerInOverlay) //controller trigger squeezed, in overlay and not being tracked to controller1
	{
		if ((*it)->getTracking() == 0)
		{
			(*it)->setOverlayMatrix(controllerPose.mDeviceToAbsoluteTracking);
		}
		else
		{
			//Must be same sized for matrix inverse calculation
			Eigen::Transform<float, 3, Eigen::Affine> trackedSource;
			Eigen::Transform<float, 3, Eigen::Affine> invertedSource;
			Eigen::Transform<float, 3, Eigen::Affine> controllerTransform;
			//Eigen::Transform<float, 3, Eigen::Affine> newTransform;
			vr::HmdMatrix34_t newPosition;
			memset(&newPosition, 0, sizeof(vr::HmdMatrix34_t));

			//HMD Calculation


			//Populate boost matrices
			for (unsigned i = 0; i < 3; ++i)
			{
				for (unsigned j = 0; j < 4; ++j)
				{
					
						if ((*it)->getTracking() == 1)
						{
							trackedSource(i, j) = hmdPose.mDeviceToAbsoluteTracking.m[i][j];
						}
						if ((*it)->getTracking() == 2)
						{
							trackedSource(i, j) = controller1Pose.mDeviceToAbsoluteTracking.m[i][j];
						}
						if ((*it)->getTracking() == 3)
						{
							trackedSource(i, j) = controller2Pose.mDeviceToAbsoluteTracking.m[i][j];
						}
						controllerTransform(i, j) = controllerPose.mDeviceToAbsoluteTracking.m[i][j];
				
					
				} //End Column loop
			}  //End Row loop

			
			Eigen::Matrix<float, 4, 4> invMatrix = trackedSource.matrix().inverse();
			Eigen::Matrix<float, 4, 4> newTransform;
			newTransform = invMatrix * controllerTransform.matrix();



			//Copy values from the new matrix into the openVR matrix
			for (unsigned i = 0; i < 3; ++i)
			{
				for (unsigned j = 0; j < 4; ++j)
				{
					if (i < 3)
					{
						newPosition.m[i][j] = newTransform(i, j);
					}
				} // end column loop
			} //end row loop

			//Maintain previous rotation


			(*it)->setOverlayMatrix(newPosition);
		} // end else (tracking check for non-spacial tracking)

	} //end controller check
}