HRESULT CMediaStream::CreateInstance(StspStreamDescription *pStreamDescription, IBufferPacket *pAttributesBuffer, CMediaSource *pSource, CMediaStream **ppStream)
{
    if (pStreamDescription == nullptr || pSource == nullptr || ppStream == nullptr)
    {
        return E_INVALIDARG;
    }

    HRESULT hr = S_OK;
    try
    {
        ComPtr<CMediaStream> spStream;
        spStream.Attach(new (std::nothrow) CMediaStream(pSource));
        if (!spStream)
        {
            Throw(E_OUTOFMEMORY);
        }

        spStream->Initialize(pStreamDescription, pAttributesBuffer);


        (*ppStream) = spStream.Detach();
    }
    catch(Exception ^exc)
    {
        hr = exc->HResult;
    }

    TRACEHR_RET(hr);
}