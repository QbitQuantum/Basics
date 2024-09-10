void cGridMesh::Draw()
{
	// Set Layout And Topology
	g_pD3DDC->IASetInputLayout(cInputLayouts::Simple);
	g_pD3DDC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set VertexBuffer And IndexBuffer
	UINT stride = sizeof(Vertex::Simple);
	UINT offset = 0;
	g_pD3DDC->IASetVertexBuffers(0, 1, &m_VB, &stride, &offset);
	g_pD3DDC->IASetIndexBuffer(m_IB, DXGI_FORMAT_R32_UINT, 0);

	// worldViewProj Çà·ÄÀ» ±¸ÇÑ´Ù.
	XMMATRIX world	= XMLoadFloat4x4(&GetTransformMatrix());
	XMMATRIX view	= g_pCameraManager->GetView();
	XMMATRIX proj	= g_pCameraManager->GetProj();
	XMMATRIX worldViewProj = world * view * proj;

	// ¼ÎÀÌ´õ¿¡ »ó¼ö°ª ¼³Á¤.
	cEffects::SimpleFX->SetWorldViewProj(worldViewProj);

	ID3DX11EffectTechnique* tech = cEffects::SimpleFX->ColorTech;
	D3DX11_TECHNIQUE_DESC techDesc;
	tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		tech->GetPassByIndex(p)->Apply(0, g_pD3DDC);

		// »öÀÎÀ» »ç¿ëÇØ¼­ ±×¸°´Ù.
		g_pD3DDC->DrawIndexed(m_GridIndexCount, 0, 0);
	}

	HR(g_pD3DSC->Present(0, 0));
}