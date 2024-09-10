/** Checks states via InputManager. Regular key-bindings should probably still be defined in the main game state 
	and then passed on as messages to the character with inputFocus turned on.
*/
void FirstPersonPlayerProperty::ProcessInput()
{
	// Skip if CTLR is pressed, should be some other binding then.
	if (InputMan.KeyPressed(KEY::CTRL) || InputMan.KeyPressed(KEY::ALT))
		return;
	forward = 0.f;
	// Should probably check some lexicon of key-bindings here too. or?
	if (InputMan.KeyPressed(KEY::W))
		forward -= 1.f;
	if (InputMan.KeyPressed(KEY::S))
		forward += 1.f;
	right = 0.f;
	if (InputMan.KeyPressed(KEY::A))
		right -= 1.f;
	if (InputMan.KeyPressed(KEY::D))
		right += 1.f;

	/// o.o
	if (InputMan.KeyPressedThisFrame(KEY::R))
	{
		ToggleAutorun();
	}

	if (InputMan.KeyPressed(KEY::SPACE))
	{
		if (!jumping)
		{
			// Jump!
			PhysicsQueue.Add(new PMApplyImpulse(owner, Vector3f(0,jumpSpeed,0), Vector3f()));
			lastJump = Time::Now();
			jumping = true;
			PhysicsQueue.Add(new PMSetEntity(owner, PT_ACCELERATION, Vector3f()));
			/// Cancel auto run as well.
			PhysicsQueue.Add(new PMSetEntity(owner, PT_RELATIVE_ACCELERATION, Vector3f()));
		}
	}

	forward *= movementSpeed;

	float rotationSpeed = 1.2f;
	right *= rotationSpeed;

	Vector3f acc;
	acc[2] = forward;

//	Vector3f rot;
//	rot[1] = right;

	// 
	// Auto-running,.
	if (autorun)
	{
		if (lastAcc != acc)
		{
		}
		if (right != lastRight)
		{
			// Rotate int Y..
			Quaternion q = Quaternion(Vector3f(0,1,0), right);
			PhysicsQueue.Add(new PMSetEntity(owner, PT_ROTATIONAL_VELOCITY, q));
			lastRight = right;
		}
	}
			
	/// o-o cameraaaa focsuuuuuu!
	if (owner->cameraFocus)
	{
		
		// Check mouse position.
		if (raycast)
			UpdateTargetsByCursorPosition();


		// Free-form running (relative to camera)
		if (!autorun)
		{
			/// Get camera transform.
			Camera * camera = owner->cameraFocus;
			if (!camera)
				return;
			Vector3f camLookAt = camera->LookingAt();
			Vector3f forwardVector = -forward * camLookAt;
			forwardVector.Normalize();
			Vector3f rightwardVector = -right * camera->LeftVector();
			rightwardVector.Normalize();
			Vector3f newVelocity = forwardVector + rightwardVector;
			// Remove Y-component.
			newVelocity[1] = 0;
			Vector3f normalizedVelocity = newVelocity.NormalizedCopy();
			// Multiply movement speed.
			newVelocity = normalizedVelocity * movementSpeed;
			UpdateVelocity(newVelocity);
		}


		/// Make sure the camera is rotating around the center of the entity. <- wat.
		float height = 1.7f;
		if (owner->cameraFocus->relativePosition[1] != height)
		{
			GraphicsQueue.Add(new GMSetCamera(owner->cameraFocus, CT_RELATIVE_POSITION_Y, height));
			GraphicsQueue.Add(new GMSetCamera(owner->cameraFocus, CT_TRACKING_POSITION_OFFSET, Vector3f(0,height,0)));
		}
		/// Camera Control, Booyakasha!
		float cameraRight = 0.f;
		if (InputMan.KeyPressed(KEY::LEFT))
			cameraRight += 1.f;
		if (InputMan.KeyPressed(KEY::RIGHT))
			cameraRight -= 1.f;

		// Set it! :D
		static float pastCameraRight = 0.f;
		if (cameraRight != pastCameraRight)
		{
			GraphicsQueue.Add(new GMSetCamera(owner->cameraFocus, CT_ROTATION_SPEED_YAW, -cameraRight));
			pastCameraRight = cameraRight;
		}

		/// Camera updown
		float cameraUp = 0.f;
		if (InputMan.KeyPressed(KEY::UP))
			cameraUp += 1.f;
		if (InputMan.KeyPressed(KEY::DOWN))
			cameraUp -= 1.f;
		static float pastCameraUp = 0.f;
		if (cameraUp != pastCameraUp)
		{
			GraphicsQueue.Add(new GMSetCamera(owner->cameraFocus, CT_ROTATION_SPEED_PITCH, -cameraUp)); 
			pastCameraUp = cameraUp;
		}


		float cameraZoom = 0.f;
		float cameraZoomMultiplier = 1.00f;
#define CONSTANT_ZOOM_SPEED 2.2f
#define ZOOM_MULTIPLIER_SPEED 1.5f
		if (InputMan.KeyPressed(KEY::PG_DOWN))
		{
			cameraZoomMultiplier *= ZOOM_MULTIPLIER_SPEED;
			cameraZoom = CONSTANT_ZOOM_SPEED;
		}
		if (InputMan.KeyPressed(KEY::PG_UP))
		{
			cameraZoomMultiplier /= ZOOM_MULTIPLIER_SPEED;
			cameraZoom = - CONSTANT_ZOOM_SPEED;
		}
		static float pastCameraZoom = 1.f;
		if (cameraZoom != pastCameraZoom)
		{
			GraphicsQueue.Add(new GMSetCamera(owner->cameraFocus, CT_DISTANCE_FROM_CENTER_OF_MOVEMENT_SPEED, cameraZoom));
			GraphicsQueue.Add(new GMSetCamera(owner->cameraFocus, CT_DISTANCE_FROM_CENTER_OF_MOVEMENT_SPEED_MULTIPLIER, cameraZoomMultiplier));
			pastCameraZoom = cameraZoom;
		}
		float cameraTurn = 0.f;
		if (InputMan.KeyPressed(KEY::LEFT))
			cameraTurn += 1.f;
		if (InputMan.KeyPressed(KEY::RIGHT))
			cameraTurn += -1;
		static float pastCameraTurn = 0.f;
		if (cameraTurn != pastCameraTurn)
		{
			cameraTurn *= 2.f;
			pastCameraTurn = cameraTurn;
			GraphicsQueue.Add(new GMSetCamera(owner->cameraFocus, CT_ROTATION_SPEED_YAW, cameraTurn));
		}
	}
}