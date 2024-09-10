void XMCamera::UpdateView()
{
	// rotate
	m_rotationMatrix = XMMatrixRotationRollPitchYaw(m_pitch, m_yaw, m_roll);

	// transform
	const FVEC3 dv(0, 0, 1);
	const FVEC3 du(0, 1, 0);

	m_lookAt = TVectorTransform(dv, m_rotationMatrix);
	m_up = TVectorTransform(du, m_rotationMatrix);

	// forward & right
	m_forward	= Normalize(m_lookAt);
	m_right		= Cross(m_up, m_forward);
	m_right		= Normalize(m_right);


	// update lookAt
	m_lookAt = m_position + m_lookAt;

	// update viewMatrix
	XMFLOAT3 p(m_position.x, m_position.y, m_position.z);
	XMFLOAT3 l(m_lookAt.x, m_lookAt.y, m_lookAt.z);
	XMFLOAT3 u(m_up.x, m_up.y, m_up.z);

	m_viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&p), XMLoadFloat3(&l), XMLoadFloat3(&u));
	//m_viewMatrix = TMatrixTranspose(m_viewMatrix);

	// update inverse matrix
	m_inverseViewMatrix = XMMatrixInverse(&XMMatrixDeterminant(m_viewMatrix), m_viewMatrix);
	m_inverseProjectionMatrix = XMMatrixInverse(&XMMatrixDeterminant(m_projectionMatrix), m_projectionMatrix);
	/* (world) view projection */
	//m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
	m_viewProjectionMatrix	= m_projectionMatrix * m_viewMatrix;
	m_inverseWVP			= XMMatrixInverse(&XMMatrixDeterminant(m_viewProjectionMatrix), m_viewProjectionMatrix);

	
}