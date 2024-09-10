void SwapChain::SetMatrixPerspective()
{
	float Aspect = (float)m_nWidth / (float)m_nHeight;
	m_projectMat = XMMatrixPerspectiveFovLH(XM_PI / 4.0f, Aspect, 1.0f, 20000.f);
	XMVECTOR v0 = XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f);
	XMVECTOR v1 = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR v2 = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	m_viewMat = XMMatrixLookAtLH(v0, v1, v2);
	m_WorldMat = XMMatrixIdentity();
}