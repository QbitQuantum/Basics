void OvrSceneView::Frame( const VrFrame & vrFrame,
							const ovrHeadModelParms & headModelParms_,
							const long long supressModelsWithClientId_ )
{
	HeadModelParms = headModelParms_;
	SupressModelsWithClientId = supressModelsWithClientId_;

	CurrentTracking = vrFrame.Tracking;

	// Delta time in seconds since last frame.
	const float dt = vrFrame.DeltaSeconds;
	const float angleSpeed = 1.5f;

	//
	// Player view angles
	//

	// Turn based on the look stick
	// Because this can be predicted ahead by async TimeWarp, we apply
	// the yaw from the previous frame's controls, trading a frame of
	// latency on stick controls to avoid a bounce-back.
	StickYaw -= YawVelocity * dt;
	YawVelocity = angleSpeed * vrFrame.Input.sticks[1][0];

	// Only if there is no head tracking, allow right stick up/down to adjust pitch,
	// which can be useful for debugging without having to dock the device.
	if ( ( vrFrame.Tracking.Status & VRAPI_TRACKING_STATUS_ORIENTATION_TRACKED ) == 0 )
	{
		StickPitch -= angleSpeed * vrFrame.Input.sticks[1][1] * dt;
	}
	else
	{
		StickPitch = 0.0f;
	}

	// We extract Yaw, Pitch, Roll instead of directly using the orientation
	// to allow "additional" yaw manipulation with mouse/controller and scene offsets.
	const Quatf quat = vrFrame.Tracking.HeadPose.Pose.Orientation;

	quat.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>( &EyeYaw, &EyePitch, &EyeRoll );

	// Yaw is modified by both joystick and application-set scene yaw.
	// Pitch is only modified by joystick when no head tracking sensor is active.
	EyeYaw += StickYaw + SceneYaw;
	EyePitch += StickPitch;

	//
	// Player movement
	//

	// Allow up / down movement if there is no floor collision model or in 'free move' mode.
	const bool upDown = ( WorldModel.Definition == NULL || FreeMove ) && ( ( vrFrame.Input.buttonState & BUTTON_RIGHT_TRIGGER ) != 0 );
	const Vector3f gamepadMove(
			vrFrame.Input.sticks[0][0],
			upDown ? -vrFrame.Input.sticks[0][1] : 0.0f,
			upDown ? 0.0f : vrFrame.Input.sticks[0][1] );

	// Perform player movement if there is input.
	if ( gamepadMove.LengthSq() > 0.0f )
	{
		const Matrix4f yawRotate = Matrix4f::RotationY( EyeYaw );
		const Vector3f orientationVector = yawRotate.Transform( gamepadMove );

		// Don't let move get too crazy fast
		const float moveDistance = OVR::Alg::Min<float>( MoveSpeed * (float)dt, 1.0f );
		if ( WorldModel.Definition != NULL && !FreeMove )
		{
			FootPos = SlideMove( FootPos, HeadModelParms.EyeHeight, orientationVector, moveDistance,
						WorldModel.Definition->Collisions, WorldModel.Definition->GroundCollisions );
		}
		else
		{	// no scene loaded, walk without any collisions
			ModelCollision collisionModel;
			ModelCollision groundCollisionModel;
			FootPos = SlideMove( FootPos, HeadModelParms.EyeHeight, orientationVector, moveDistance,
						collisionModel, groundCollisionModel );
		}
	}

	//
	// Center eye transform
	//
	UpdateCenterEye();

	//
	// Model animations
	//

	if ( !Paused )
	{
		for ( int i = 0; i < Models.GetSizeI(); i++ )
		{
			if ( Models[i] != NULL )
			{
				Models[i]->AnimateJoints( static_cast<float>( vrFrame.PredictedDisplayTimeInSeconds ) );
			}
		}
	}

	// External systems can add surfaces to this list before drawing.
	EmitSurfaces.Resize( 0 );
}