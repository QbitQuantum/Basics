DynamicConstantBuffer::DynamicConstantBuffer(UINT constantSize, UINT maxDrawsPerFrame, UINT frameCount) :
	m_alignedPerDrawConstantBufferSize(Align(constantSize)),	// Constant buffers must be aligned for hardware requirements.
	m_maxDrawsPerFrame(maxDrawsPerFrame),
	m_frameCount(frameCount),
	m_constantBuffer(nullptr)
{
	m_perFrameConstantBufferSize = m_alignedPerDrawConstantBufferSize * m_maxDrawsPerFrame;
}