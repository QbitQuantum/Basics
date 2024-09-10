HRESULT WIACamera::CDataCallback::StoreBuffer()
{
    // Increase the successfully transferred buffers array size
    IStream **ppStream = (IStream **) CoTaskMemRealloc(
		*m_pppStream, (*m_plCount + 1) * sizeof(IStream *)
	);
    if (ppStream == NULL) {
        return E_OUTOFMEMORY;
    }
    *m_pppStream = ppStream;

	// Rewind the current buffer
    LARGE_INTEGER liZero = { 0 };
    m_pStream->Seek(liZero, STREAM_SEEK_SET, 0);

    // Store the current buffer as the last successfully transferred buffer
	(*m_pppStream)[*m_plCount] = m_pStream;
    (*m_pppStream)[*m_plCount]->AddRef();
    *m_plCount += 1;

    // Reset the current buffer
    m_pStream->Release();

    m_nDataSize = 0;

    return S_OK;
}