void OcculusCameraComponent::update( float dt )
{
	//Occulus warning
	// Health and Safety Warning display state.
	ovrHSWDisplayState hswDisplayState;
	ovrHmd_GetHSWDisplayState(hmd, &hswDisplayState);
	if (hswDisplayState.Displayed) 
	{ 
		// Dismiss the warning if the user pressed the appropriate key or if the user 
		// is tapping the side of the HMD. 
		// If the user has requested to dismiss the warning via keyboard or controller input... 
		//if (Util_GetAndResetHSWDismissedState()) 
		//	ovrHmd_DismissHSWDisplay(hmd); 
		//else 
		{ 
			// Detect a moderate tap on the side of the HMD. 
			ovrTrackingState ts = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());
			if (ts.StatusFlags & ovrStatus_OrientationTracked) 
			{ 
				const OVR::Vector3f v(ts.RawSensorData.Accelerometer.x, ts.RawSensorData.Accelerometer.y, ts.RawSensorData.Accelerometer.z);

				// Arbitrary value and representing moderate tap on the side of the DK2 Rift.
				if (v.LengthSq() > 250.f) ovrHmd_DismissHSWDisplay(hmd);
			}
		}
	}


	dt;
	// Query the HMD for the current tracking state.
	
	ovrTrackingState ts = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());
	if (ts.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked))
	{
		ovrPosef pose = ts.HeadPose.ThePose;

		//convert to mat4 if desired
		glm::mat4 transformMatrix = glm::mat4_cast( fromOVR( pose.Orientation ) );

		//parent->gc<TransformComponent>()->setRotation( glm::mat3(transformMatrix) );
	}
	parent->getStage()->subscribeRender( this );
}