void CameraClass::RenderBaseViewMatrix()
{
	XMFLOAT3 f3_lookAt;
	XMVECTOR up, position, lookAt;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;


	// Setup the vector that points upwards.
	up = XMLoadFloat3(&XMFLOAT3(0.0f, 1.0f, 0.0f));

	// Setup the position of the camera in the world.
	position = XMLoadFloat3(&XMFLOAT3(m_positionX, m_positionY, m_positionZ));

	// Setup where the camera is looking by default.
	lookAt = XMLoadFloat3(&XMFLOAT3(0.0f, 0.0f, 1.0f));

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw   = m_rotationY * 0.0174532925f;
	roll  = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the base view matrix from the three updated vectors.
	m_baseViewMatrix = XMMatrixLookAtLH(position, lookAt, up);
}