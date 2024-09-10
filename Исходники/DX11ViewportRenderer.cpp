bool DX11ViewportRenderer::drawBounds( const MMatrix &matrix, const MBoundingBox &box, float color[3] )
{
	// Transform from object to world space
	//
	XMMATRIX mat = XMMATRIX
		(
		(float)matrix.matrix[0][0], (float)matrix.matrix[0][1], (float)matrix.matrix[0][2], (float)matrix.matrix[0][3],
		(float)matrix.matrix[1][0], (float)matrix.matrix[1][1], (float)matrix.matrix[1][2], (float)matrix.matrix[1][3],
		(float)matrix.matrix[2][0], (float)matrix.matrix[2][1], (float)matrix.matrix[2][2], (float)matrix.matrix[2][3],
		(float)matrix.matrix[3][0], (float)matrix.matrix[3][1], (float)matrix.matrix[3][2], (float)matrix.matrix[3][3]
		);

	// Adjust the unit cube to the bounds
	//
	MPoint	minPt = box.min();
	MPoint	maxPt = box.max();
	float minVal[3] = { (float)minPt.x, (float)minPt.y, (float)minPt.z };
	float maxVal[3] = { (float)maxPt.x, (float)maxPt.y, (float)maxPt.z };
	XMMATRIX bounds( 0.5f*(maxVal[0]-minVal[0]), 0.0f,						 0.0f,							0.0f,
					 0.0f,						 0.5f*(maxVal[1]-minVal[1]), 0.0f,							0.0f,
					 0.0f,						 0.0f,						 0.5f*(maxVal[2]-minVal[2]),	0.0f,
					 0.5f*(maxVal[0]+minVal[0]), 0.5f*(maxVal[1]+minVal[1]), 0.5f*(maxVal[2]+minVal[2]),	1.0f );

    // Set vertex buffer
    UINT stride = sizeof( BoundsVertex );
    UINT offset = 0;
    m_pD3DDeviceCtx->IASetVertexBuffers( 0, 1, &m_pBoundsVertexBuffer, &stride, &offset );

	// Set index buffer
    m_pD3DDeviceCtx->IASetIndexBuffer( m_pBoundsIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );

	// Set constant buffer
    BoundsConstants cb;
	cb.fWVP = XMMatrixTranspose( bounds * mat * m_currentViewMatrix * m_currentProjectionMatrix );
	cb.fDiffuseMaterial = XMFLOAT3( color[0], color[1], color[2] );
	m_pD3DDeviceCtx->UpdateSubresource( m_pBoundsConstantBuffer, 0, NULL, &cb, 0, 0 );

    // Set primitive topology
    m_pD3DDeviceCtx->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_LINELIST );

	// get shader
	SurfaceEffectItemList::const_iterator it = m_resourceManager.getSurfaceEffectItemList().find( "Maya_unlit" );
	if ( it == m_resourceManager.getSurfaceEffectItemList().end() )
		return false;
	const SurfaceEffectItem* sei = it->second;

	// bind shaders
    m_pD3DDeviceCtx->VSSetShader( sei->fVertexShader, NULL, 0 );
	m_pD3DDeviceCtx->VSSetConstantBuffers( 0, 1, &m_pBoundsConstantBuffer );
    m_pD3DDeviceCtx->IASetInputLayout( sei->fInputLayout );
    m_pD3DDeviceCtx->PSSetShader( sei->fPixelShader, NULL, 0 );
	m_pD3DDeviceCtx->PSSetConstantBuffers( 0, 1, &m_pBoundsConstantBuffer );

	// draw
    m_pD3DDeviceCtx->DrawIndexed( 24, 0, 0 );

	return true;
}