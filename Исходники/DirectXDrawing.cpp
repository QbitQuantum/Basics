//Needs to be called befor all other drawcalls, and ended with "EndDraw()"
void DirectXGraphicEngine::BeginDraw()
{
	if (m_IsDrawing)
	{
		Logger::Log( "Rendering call Begin was called before end was called", "DirectXRenderSystem", LoggerType::MSG_ERROR );
		return;
	}

	//clear the backbuffer, and depthstencil buffer
	float t_Black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, t_Black);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	//clear gbuffers
	for (int i = 0; i < 3; i++)
	{
		m_DeviceContext->ClearRenderTargetView(m_GBufferRTV[i], t_Black);
	}

	m_IsDrawing = true;

	UINT t_Strides = sizeof(XMFLOAT4X4);
	UINT t_Offsets = 0;

	m_DeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_DeviceContext->IASetVertexBuffers(1, 1, &m_InstanceBuffer, &t_Strides, &t_Offsets);



	//update viewmatrix
	DirectXMatrixLibrary* t_MatrixLib = (DirectXMatrixLibrary*)t_MatrixLib->GetInstance();

	UINT t_Size = m_View.size();
	for (size_t i = 0; i < t_Size; i++)
	{
		PerFrameCBuffer t_PFB;
		t_PFB.View = *t_MatrixLib->GetMatrix(m_View.at(i).camera.transformMatrixHandle);
		t_PFB.Proj = *t_MatrixLib->GetMatrix(m_View.at(i).camera.projectionMatrixHandle);
		XMMATRIX t_View = XMLoadFloat4x4(&t_PFB.View);
		XMMATRIX t_Proj = XMLoadFloat4x4(&t_PFB.Proj);
		XMMATRIX t_ViewProj = XMMatrixMultiply(t_View, t_Proj);
		XMStoreFloat4x4(&t_PFB.ViewProj, t_ViewProj);
		
		m_DeviceContext->UpdateSubresource(m_PerFrameCBuffer, 0, nullptr, &t_PFB, 0, 0);
	}
	
}