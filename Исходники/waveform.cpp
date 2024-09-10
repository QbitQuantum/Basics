HRESULT CDirectxWaveform::preDrawFrame()
{
	// ASSUMES m_refLock IS HELD BY CALLER
	if(!m_dataTex || !m_dataTexData || !m_pPSGlobals)
	{
		return E_POINTER;
	}

	// push the radio input to the video buffers
	D3D10_MAPPED_TEXTURE2D mappedDataTex;
	memset(&mappedDataTex, 0, sizeof(mappedDataTex));
	UINT subr = D3D10CalcSubresource(0, 0, 0);
	HRESULT hR = m_dataTex->Map(subr, D3D10_MAP_WRITE_DISCARD, 0, &mappedDataTex);
	if(FAILED(hR)) return hR;
	if(m_bIsComplexInput)
	{
		UINT halfWidth = m_dataTexWidth / 2;
		memcpy(((char*)mappedDataTex.pData) + halfWidth*m_dataTexElemSize, m_dataTexData, m_dataTexElemSize*halfWidth);
		memcpy(mappedDataTex.pData, ((char*)m_dataTexData) + halfWidth*m_dataTexElemSize, m_dataTexElemSize*halfWidth);
	} else {
		memcpy(mappedDataTex.pData, m_dataTexData, m_dataTexElemSize*m_dataTexWidth);
	}
	m_dataTex->Unmap(subr);

	return S_OK;
}