void OvrSceneView::UpdateViewMatrix(const VrFrame vrFrame )
{
	// Experiments with position tracking
	const bool	useHeadModel = !AllowPositionTracking ||
			( ( vrFrame.Input.buttonState & ( BUTTON_A | BUTTON_X ) ) == 0 );

	// Delta time in seconds since last frame.
	const float dt = vrFrame.DeltaSeconds;
	const float yawSpeed = 1.5f;

    Vector3f GamepadMove;

	// Allow up / down movement if there is no floor collision model
	if ( vrFrame.Input.buttonState & BUTTON_RIGHT_TRIGGER )
	{
		FootPos.y -= vrFrame.Input.sticks[0][1] * dt * MoveSpeed;
	}
	else
	{
		GamepadMove.z = vrFrame.Input.sticks[0][1];
	}
	GamepadMove.x = vrFrame.Input.sticks[0][0];

	// Turn based on the look stick
	// Because this can be predicted ahead by async TimeWarp, we apply
	// the yaw from the previous frame's controls, trading a frame of
	// latency on stick controls to avoid a bounce-back.
	YawOffset -= YawVelocity * dt;

	if ( !( vrFrame.OvrStatus & ovrStatus_OrientationTracked ) )
	{
		PitchOffset -= yawSpeed * vrFrame.Input.sticks[1][1] * dt;
		YawVelocity = yawSpeed * vrFrame.Input.sticks[1][0];
	}
	else
	{
		YawVelocity = 0.0f;
	}

	// We extract Yaw, Pitch, Roll instead of directly using the orientation
	// to allow "additional" yaw manipulation with mouse/controller.
	const Quatf quat = vrFrame.PoseState.Pose.Orientation;

	quat.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>( &EyeYaw, &EyePitch, &EyeRoll );

	EyeYaw += YawOffset;

	// If the sensor isn't plugged in, allow right stick up/down
	// to adjust pitch, which can be useful for debugging.  Never
	// do this when head tracking
	if ( !( vrFrame.OvrStatus & ovrStatus_OrientationTracked ) )
	{
		EyePitch += PitchOffset;
	}

	// Perform player movement.
	if ( GamepadMove.LengthSq() > 0.0f )
	{
		const Matrix4f yawRotate = Matrix4f::RotationY( EyeYaw );
		const Vector3f orientationVector = yawRotate.Transform( GamepadMove );

		// Don't let move get too crazy fast
		const float moveDistance = OVR::Alg::Min<float>( MoveSpeed * (float)dt, 1.0f );
		if ( WorldModel.Definition )
		{
			FootPos = SlideMove( FootPos, ViewParms.EyeHeight, orientationVector, moveDistance,
						WorldModel.Definition->Collisions, WorldModel.Definition->GroundCollisions );
		}
		else
		{	// no scene loaded, walk without any collisions
			CollisionModel collisionModel;
			CollisionModel groundCollisionModel;
			FootPos = SlideMove( FootPos, ViewParms.EyeHeight, orientationVector, moveDistance,
						collisionModel, groundCollisionModel );
		}
	}

	// Rotate and position View Camera, using YawPitchRoll in BodyFrame coordinates.
	Matrix4f rollPitchYaw = Matrix4f::RotationY( EyeYaw )
			* Matrix4f::RotationX( EyePitch )
			* Matrix4f::RotationZ( EyeRoll );
	const Vector3f up = rollPitchYaw.Transform( UpVector );
	const Vector3f forward = rollPitchYaw.Transform( ForwardVector );
	const Vector3f right = rollPitchYaw.Transform( RightVector );

	// Have sensorFusion zero the integration when not using it, so the
	// first frame is correct.
	if ( vrFrame.Input.buttonPressed & (BUTTON_A | BUTTON_X) )
	{
		LatchedHeadModelOffset = LastHeadModelOffset;
	}

	// Calculate the shiftedEyePos
	ShiftedEyePos = CenterEyePos();

	Vector3f headModelOffset = HeadModelOffset( EyeRoll, EyePitch, EyeYaw,
			ViewParms.HeadModelDepth, ViewParms.HeadModelHeight );
	if ( useHeadModel )
	{
		ShiftedEyePos += headModelOffset;
	}

	headModelOffset += forward * ImuToEyeCenter.z;
	headModelOffset += right * ImuToEyeCenter.x;

	LastHeadModelOffset = headModelOffset;

	if ( !useHeadModel )
	{
		// Use position tracking from the sensor system, which is in absolute
		// coordinates without the YawOffset
		ShiftedEyePos += Matrix4f::RotationY( YawOffset ).Transform( vrFrame.PoseState.Pose.Position );

		ShiftedEyePos -= forward * ImuToEyeCenter.z;
		ShiftedEyePos -= right * ImuToEyeCenter.x;

		ShiftedEyePos += LatchedHeadModelOffset;
	}

	ViewMatrix = Matrix4f::LookAtRH( ShiftedEyePos, ShiftedEyePos + forward, up );
}