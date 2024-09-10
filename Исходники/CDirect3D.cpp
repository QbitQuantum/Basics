void CDirect3D::SetViewport()
{
	XMMATRIX matIdentity;
	XMMATRIX matProjection;

	matProjection = XMMatrixOrthographicOffCenterLH(0.0f,1.0f,0.0f,1.0f,0.0f,1.0f);
	matIdentity = XMMatrixIdentity();
	pDevice->SetTransform(D3DTS_WORLD,(D3DMATRIX*)&matIdentity);
	pDevice->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&matIdentity);
	pDevice->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&matProjection);

	RECT drawRect = CalculateDisplayRect(afterRenderWidth,afterRenderHeight,dPresentParams.BackBufferWidth,dPresentParams.BackBufferHeight);
	D3DVIEWPORT9 viewport;
	viewport.X = drawRect.left;
	viewport.Y = drawRect.top;
	viewport.Height = drawRect.bottom - drawRect.top;
	viewport.Width = drawRect.right - drawRect.left;
	viewport.MinZ = 0.0f;
	viewport.MaxZ = 1.0f;
	HRESULT hr = pDevice->SetViewport(&viewport);

	SetupVertices();
}