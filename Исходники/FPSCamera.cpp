	void FPSCamera::Update()
	{
		vec2 windowSize = Application::GetApplication().GetWindowSize();
		vec2 windowCenter = vec2((float)(int32)(windowSize.x / 2.0f), (float)(int32)(windowSize.y / 2.0f));

		if (Input::IsMouseButtonPressed(SP_MOUSE_RIGHT))
		{
			if (!Input::GetInputManager()->IsMouseGrabbed())
			{
				Input::GetInputManager()->SetMouseGrabbed(true);
				Input::GetInputManager()->SetMouseCursor(SP_NO_CURSOR);
			}
		}

		if (Input::GetInputManager()->IsMouseGrabbed())
		{
			vec2 mouse = Input::GetInputManager()->GetMousePosition();
			mouse.x -= windowCenter.x;
			mouse.y -= windowCenter.y;
			if (m_MouseWasGrabbed)
			{
				m_Yaw += mouse.x * m_MouseSensitivity;
				m_Pitch += mouse.y * m_MouseSensitivity;
			}
			m_MouseWasGrabbed = true;
			Input::GetInputManager()->SetMousePosition(windowCenter);

			Quaternion orientation = GetOrientation();
			m_Rotation = orientation.ToEulerAngles() * (180.0f / SP_PI);

			vec3 forward = GetForwardDirection(orientation);
			vec3 right = GetRightDirection(orientation);
			vec3 up = vec3::YAxis();
			float speed = Input::IsKeyPressed(SP_KEY_SHIFT) ? m_SprintSpeed : m_Speed;
			if (Input::IsKeyPressed(SP_KEY_W))
				m_Position += forward * speed;
			else if (Input::IsKeyPressed(SP_KEY_S))
				m_Position -= forward * speed;

			if (Input::IsKeyPressed(SP_KEY_A))
				m_Position -= right * speed;
			else if (Input::IsKeyPressed(SP_KEY_D))
				m_Position += right * speed;

			if (Input::IsKeyPressed(SP_KEY_SPACE))
				m_Position += up * speed;
			if (Input::IsKeyPressed(SP_KEY_CONTROL))
				m_Position -= up * speed;

			mat4 rotation = mat4::Rotate(orientation.Conjugate());
			mat4 translation = mat4::Translate(-m_Position);
			m_ViewMatrix = rotation * translation;
		}

		if (Input::IsKeyPressed(SP_KEY_ESCAPE))
		{
			Input::GetInputManager()->SetMouseGrabbed(false);
			Input::GetInputManager()->SetMouseCursor(1);
			m_MouseWasGrabbed = false;
		}
	}