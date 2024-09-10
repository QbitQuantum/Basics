void InitDirect3DApp::OnResize()
{
	D3DApp::OnResize();

	XMMATRIX newProjMtx = XMMatrixPerspectiveFovLH(0.25f * PI, AspectRatio(), 1.0f, 1000.0f);
	projMtx = newProjMtx;
}