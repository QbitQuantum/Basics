HRESULT CDelay::InternalProcessInput(DWORD dwInputStreamIndex, IMediaBuffer *pBuffer,
                                          DWORD dwFlags, REFERENCE_TIME rtTimestamp,
                                          REFERENCE_TIME rtTimelength)
{
    _ASSERTE(m_pBuffer == NULL);

    HRESULT hr = pBuffer->GetBufferAndLength(&m_pbInputData, &m_cbInputLength);
    if (FAILED(hr))
    {
        return hr;
    }


	ATLTRACE2(atlTraceGeneral, 3, "Process Input: %d bytes. Time stamp: %f/%f\n", 
		m_cbInputLength, RefTime2Double(rtTimestamp), RefTime2Double(rtTimelength));

    if (m_cbInputLength <= 0) 
        return E_FAIL;
    
    m_pBuffer = pBuffer;
    
    if (dwFlags & DMO_INPUT_DATA_BUFFERF_TIME)
    {
        m_bValidTime = true;
        m_rtTimestamp = rtTimestamp;
    }
    else
    {
        m_bValidTime = false;
    }
    
    return S_OK;
}