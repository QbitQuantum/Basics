bool LightLx::GenerateProjectionMatrix()
{
	XMMATRIX projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1.0f, 0.1f, 1000.0f);
	XMStoreFloat4x4(&m_projectionMatrix, projection);

	return true;
}