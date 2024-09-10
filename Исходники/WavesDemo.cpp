void WavesApp::OnResize()
{
	D3DApp::OnResize();
	// The window resized, so update the aspect ratio and recompute the projection matrix.
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f*MathHelper::PI/* 90度视角 */, GetAspectRatio(), 1.0f, 1000.0f);
	XMStoreFloat4x4(&m_projMaxtrix, P);
}