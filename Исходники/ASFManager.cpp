HRESULT CASFManager::CreateASFSplitter (IMFByteStream *pContentByteStream,
                                        IMFASFSplitter **ppSplitter)
{
    if (!pContentByteStream || !ppSplitter)
    {
        return E_INVALIDARG;
    }

    if (!m_pContentInfo)
    {
        return MF_E_NOT_INITIALIZED;
    }

    HRESULT hr = S_OK;
    
    IMFASFSplitter *pSplitter = NULL;
    IMFPresentationDescriptor* pPD = NULL;

    UINT64 cbDataOffset = 0, cbDataLength = 0;

    CHECK_HR(hr = MFCreateASFSplitter(&pSplitter));
    
    CHECK_HR(hr = pSplitter->Initialize(m_pContentInfo));

    //Generate the presentation descriptor
    CHECK_HR(hr =  m_pContentInfo->GeneratePresentationDescriptor(&pPD));

    //Get the offset to the start of the Data Object
    CHECK_HR(hr = pPD->GetUINT64(MF_PD_ASF_DATA_START_OFFSET, &cbDataOffset));

    //Get the length of the Data Object
    CHECK_HR(hr = pPD->GetUINT64(MF_PD_ASF_DATA_LENGTH, &cbDataLength));

    m_pByteStream = pContentByteStream;
    m_pByteStream->AddRef();

    m_cbDataOffset = cbDataOffset;
    m_cbDataLength = cbDataLength;

    // Return the pointer to the caller.
    *ppSplitter = pSplitter;
    (*ppSplitter)->AddRef();

    TRACE((L"Created Splitter object.\n"));


done:

    LOG_MSG_IF_FAILED(L"CASFManager::CreateASFSplitter failed.\n", hr);

    SAFE_RELEASE(pSplitter);
    SAFE_RELEASE(pPD);

    return hr;
}