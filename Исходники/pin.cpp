/*****************************************************************************
 * CKsPin::Instantiate()
 *****************************************************************************
 *//*!
 * @brief
 */
HRESULT 
CKsPin::
Instantiate
(
    IN		BOOL	Looped
)
{
    HRESULT hr = S_OK;

    if (m_KsPinConnect)
	{
		if (m_LinkPin)
		{
			ASSERT((KSPIN_COMMUNICATION_SINK == m_LinkPin->m_PinDescriptor.Communication) ||
				   (KSPIN_COMMUNICATION_BOTH == m_LinkPin->m_PinDescriptor.Communication));

			m_KsPinConnect->PinToHandle = m_LinkPin->m_Handle;
		}

		m_Looped = Looped;

		m_KsPinConnect->Interface.Id = m_Looped ? KSINTERFACE_STANDARD_LOOPED_STREAMING : KSINTERFACE_STANDARD_STREAMING;

		DWORD w32Error = KsCreatePin(m_KsFilter->m_Handle, m_KsPinConnect, GENERIC_WRITE | GENERIC_READ, &m_Handle);

		if (ERROR_SUCCESS != w32Error)
		{
			 hr = HRESULT_FROM_WIN32(w32Error);

			 if (SUCCEEDED(hr))
			 {
				// Sometimes the error codes don't map to error HRESULTs.
				hr = E_FAIL;
			 }
		}

		if (FAILED(hr))
		{
			_DbgPrintF(DEBUGLVL_ERROR,("[CKsPin::Instantiate] - Failed to instantiate pin. hr=0x%08x", hr));
		}
	}

    return hr;
}