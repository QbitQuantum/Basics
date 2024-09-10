void MayaCamera::OnUpdate(TimeStep timeStep)
{

	const Application& app = Application::GetApplication();

	if (app.IsKeyPressed(GLFW_KEY_LEFT_ALT))
	{
		const vec2& mouse = app.GetMousePos();
		vec2 delta = mouse - m_InitialMousePosition;
		m_InitialMousePosition = mouse;
		
		if (app.GetMouseButton() == GLFW_MOUSE_BUTTON_MIDDLE)
			MousePan(delta);
		else if (app.GetMouseButton() == GLFW_MOUSE_BUTTON_LEFT)
			MouseRotate(delta);
		else if (app.GetMouseButton() == GLFW_MOUSE_BUTTON_RIGHT)
			MouseZoom(delta.y);
	}

	// MouseZoom(window->GetMouseScrollPosition().y);

	m_Position = CalculatePosition();

	Quaternion orientation = GetOrientation();
	m_Rotation = orientation.ToEulerAngles() * (180.0f / 3.14f);

	m_View = mat4::Translate(vec3(0, 0, 1)) * mat4::Rotate(orientation.Conjugate()) * mat4::Translate(-m_Position);
}