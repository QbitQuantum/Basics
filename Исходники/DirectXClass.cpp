//
// Update the program's state
//
void DirectXClass::Update(float deltaTime)
{
	XMVECTOR eyePosition = XMVectorSet(0, 30, -50, 1);
	XMVECTOR focusPoint = XMVectorSet(0, 0, 0, 1);
	XMVECTOR upDirection = XMVectorSet(0, 1, 0, 0);
	m_ViewMatrix = XMMatrixLookAtLH(eyePosition, focusPoint, upDirection);
	m_3dDeviceContext->UpdateSubresource(g_d3dConstantBuffers[CB_Frame], 0, nullptr, &m_ViewMatrix, 0, 0);

	static float angle = 0.0f;
	angle += 90.0f * deltaTime/5;
	XMVECTOR rotationAxis = XMVectorSet(0, 1, 0, 0);

	m_WorldMatrix = XMMatrixRotationAxis(rotationAxis, XMConvertToRadians(angle));
	m_3dDeviceContext->UpdateSubresource(g_d3dConstantBuffers[CB_Object], 0, nullptr, &m_WorldMatrix, 0, 0);
}