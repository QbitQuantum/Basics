void JF::Component::ColisionBox::Render()
{
	// Declear)
	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// Get)
	auto* pTransform = GetOwner()->GetComponent<JF::Component::Transform>();

	// Check)
	RETURN_IF(pTransform == nullptr, );

	// Set Layout And Topology
	gRENDERER->DeviceContext()->IASetInputLayout(InputLayouts::PosColor);
	gRENDERER->DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	// Set VertexBuffer And IndexBuffer
	UINT stride = sizeof(JF::Vertex::PosColor);
	UINT offset = 0;
	gRENDERER->DeviceContext()->IASetVertexBuffers(0, 1, &m_VertBuff, &stride, &offset);
	gRENDERER->DeviceContext()->IASetIndexBuffer(m_IndexBuff, DXGI_FORMAT_R32_UINT, 0);

	// worldViewProj 행렬을 구한다.
	XMFLOAT3 rPosition	= XMFLOAT3(pTransform->GetPosition().x + m_Center.x, pTransform->GetPosition().y + m_Center.y, pTransform->GetPosition().z + m_Center.z);
	XMFLOAT3 rScale		= XMFLOAT3(pTransform->GetScale().x * m_Size.x, pTransform->GetScale().y * m_Size.y, pTransform->GetScale().z * m_Size.z);
	XMFLOAT4 rRotation	= pTransform->GetRotation();

	XMMATRIX scl, rot, tsl;
	scl = XMMatrixScalingFromVector(XMLoadFloat3(&rScale));
	rot = XMMatrixRotationQuaternion(XMLoadFloat4(&rRotation));
	tsl = XMMatrixTranslationFromVector(XMLoadFloat3(&rPosition));

	XMMATRIX world = scl*rot*tsl;
	XMMATRIX view = Camera::g_pMainCamera->GetView();
	XMMATRIX proj = Camera::g_pMainCamera->GetProj();
	XMMATRIX worldViewProj = world * view * proj;

	Effects::SimpleFX->SetWorldViewProj(worldViewProj);

	// 노말맵이 있는지에따라 FX Tech 설정 변경.
	ID3DX11EffectTechnique* Tech;
	Tech = Effects::SimpleFX->ColorTech;

	D3DX11_TECHNIQUE_DESC techDesc;
	Tech->GetDesc(&techDesc);
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		Tech->GetPassByIndex(p)->Apply(0, gRENDERER->DeviceContext());
		gRENDERER->DeviceContext()->DrawIndexed(m_indexCnt, 0, 0);
	}

	// 기본 랜더상태로 복원한다.
	gRENDERER->DeviceContext()->RSSetState(0);
	gRENDERER->DeviceContext()->OMSetBlendState(0, blendFactors, 0xffffffff);
}