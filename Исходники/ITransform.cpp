XMFLOAT4X4& ITransform::GetTransformMatrix()
{
	XMMATRIX scl, rot, tsl;
	scl = XMMatrixScalingFromVector(XMLoadFloat3(&m_vScale));
	rot = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_vRotation));
	tsl = XMMatrixTranslationFromVector(XMLoadFloat3(&m_vPosition));

	// worldMat = S*R*T
	XMStoreFloat4x4(&m_mTransform, (scl*rot*tsl));

	return m_mTransform;
}