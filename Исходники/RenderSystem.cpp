void RenderSystem::init_camera()
{
	//Viewport Infomation
	D3D11_VIEWPORT vp;
	ZeroMemory(&vp, sizeof(D3D11_VIEWPORT));
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.Width    = m_ScreenWidth;
	vp.Height   = m_ScreenHeight;
	m_pD3D11DeviceContext->RSSetViewports(1, &vp);

	//MVP Matrix
	XMVECTOR camPos    = XMVectorSet(0.0f,  5.0f, -8.0f, 0.0f);
	XMVECTOR camTarget = XMVectorSet( 0.0f, 0.0f, 0.0f, 0.0f );
	XMVECTOR camUp     = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	XMMATRIX View      = XMMatrixLookAtLH( camPos, camTarget, camUp );
	XMMATRIX Model     = XMMatrixIdentity();
	XMMATRIX Proj      = XMMatrixPerspectiveFovLH(0.4f*3.14f, GetAspect(), 1.0f, 1000.0f);

	XMStoreFloat4x4(&m_Proj, XMMatrixTranspose(Proj));
	XMStoreFloat4x4(&m_Model, XMMatrixTranspose(Model) );
	XMStoreFloat4x4(&m_View, XMMatrixTranspose(View) );

}