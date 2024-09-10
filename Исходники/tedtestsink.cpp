HRESULT CTedTestSink::InitVideoStream()
{
    HRESULT hr = S_OK;

    InternalAddRef();
    /*IMFMediaSink* pMediaSink;
    InternalQueryInterface(this, CTedTestSink::_GetEntries(), IID_IMFMediaSink, (void**) &pMediaSink);*/
    
    CComPtr<IMFMediaType> spVideoType;
    IFC( MFCreateMediaType(&spVideoType) );
    IFC( spVideoType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video) );
    IFC( spVideoType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_RGB24) );

    CComObject<CTedTestMediaTypeHandler>* pVideoTypeHandler = NULL;
    IFC( CComObject<CTedTestMediaTypeHandler>::CreateInstance(&pVideoTypeHandler) );
    pVideoTypeHandler->AddRef();
    pVideoTypeHandler->SetMajorType(MFMediaType_Video);
    pVideoTypeHandler->AddAvailableType(spVideoType);

    CComObject<CTedTestStreamSink>* pVideoStreamSink = NULL;
    IFC( CComObject<CTedTestStreamSink>::CreateInstance(&pVideoStreamSink) );
    pVideoStreamSink->AddRef();
    m_spVideoStreamSink = pVideoStreamSink;
    //IFC( pVideoStreamSink->Init(pMediaSink, pVideoTypeHandler, 1) );
    IFC( pVideoStreamSink->Init(this, pVideoTypeHandler, 1) );
    pVideoTypeHandler->Release();
    pVideoStreamSink->Release();

    //pMediaSink->Release();
Cleanup:
    return hr;
}