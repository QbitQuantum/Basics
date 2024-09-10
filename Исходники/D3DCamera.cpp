void D3DCamera::Render(XMVECTOR translate, XMVECTOR rotate, bool move, bool playback)
{
	XMVECTOR upVector, lookAtVector, rightVector;
	XMMATRIX rotationMatrix;

	rightVector = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	upVector = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	lookAtVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	if (move)
	{
		XMVECTOR quaternion = XMQuaternionRotationRollPitchYawFromVector(rotate);
		quaternion = XMQuaternionNormalize(quaternion);
		m_rotation = XMQuaternionMultiply(quaternion, m_rotation);
	}
	if (playback) m_rotation = rotate;
	rotationMatrix = XMMatrixRotationQuaternion(m_rotation);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);
	rightVector = XMVector3TransformCoord(upVector, rotationMatrix);
	if (move)
	{
		translate = XMVector3TransformCoord(translate, rotationMatrix);
		translate = XMVectorSetW(translate, 0);
		m_position += translate;
	}
	if (playback) m_position = translate;

	// Translate the rotated camera position to the location of the viewer.
	lookAtVector = XMVectorAdd(m_position, lookAtVector);

	m_lookAtVector.x = lookAtVector.m128_f32[0];
	m_lookAtVector.y = lookAtVector.m128_f32[1];
	m_lookAtVector.z = lookAtVector.m128_f32[2];

	
	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(m_position, lookAtVector, upVector);
	return;
}