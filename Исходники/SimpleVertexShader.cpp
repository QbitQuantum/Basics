SimpleVertexShader::SimpleVertexShader(void)
{
	// Initialise constant buffer data
	XMStoreFloat4x4( &m_cbPerObjectData.m_worldViewProjection, XMMatrixIdentity() );
	m_cbPerObjectData.m_colour = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
}