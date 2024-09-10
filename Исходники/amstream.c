static HRESULT WINAPI IAMMultiMediaStreamImpl_AddMediaStream(IAMMultiMediaStream* iface, IUnknown* pStreamObject, const MSPID* PurposeId,
                                          DWORD dwFlags, IMediaStream** ppNewStream)
{
    IAMMultiMediaStreamImpl *This = impl_from_IAMMultiMediaStream(iface);
    HRESULT hr;
    IMediaStream* pStream;
    IMediaStream** pNewStreams;

    TRACE("(%p/%p)->(%p,%s,%x,%p)\n", This, iface, pStreamObject, debugstr_guid(PurposeId), dwFlags, ppNewStream);

    if (!IsEqualGUID(PurposeId, &MSPID_PrimaryVideo) && !IsEqualGUID(PurposeId, &MSPID_PrimaryAudio))
        return MS_E_PURPOSEID;

    if (dwFlags & AMMSF_ADDDEFAULTRENDERER)
    {
        if (IsEqualGUID(PurposeId, &MSPID_PrimaryVideo))
        {
            /* Default renderer not supported by video stream */
            return MS_E_PURPOSEID;
        }
        else
        {
            IBaseFilter* dsoundrender_filter;

            /* Create the default renderer for audio */
            hr = CoCreateInstance(&CLSID_DSoundRender, NULL, CLSCTX_INPROC_SERVER, &IID_IBaseFilter, (LPVOID*)&dsoundrender_filter);
            if (SUCCEEDED(hr))
            {
                 hr = IGraphBuilder_AddFilter(This->pFilterGraph, dsoundrender_filter, NULL);
                 IBaseFilter_Release(dsoundrender_filter);
            }

            /* No media stream created when the default renderer is used */
            return hr;
        }
    }

    if (IsEqualGUID(PurposeId, &MSPID_PrimaryVideo))
        hr = ddrawmediastream_create((IMultiMediaStream*)iface, PurposeId, This->StreamType, &pStream);
    else
        hr = audiomediastream_create((IMultiMediaStream*)iface, PurposeId, This->StreamType, &pStream);
    if (SUCCEEDED(hr))
    {
        pNewStreams = CoTaskMemRealloc(This->pStreams, (This->nbStreams+1) * sizeof(IMediaStream*));
        if (!pNewStreams)
        {
            IMediaStream_Release(pStream);
            return E_OUTOFMEMORY;
        }
        This->pStreams = pNewStreams;
        This->pStreams[This->nbStreams] = pStream;
        This->nbStreams++;

        if (ppNewStream)
            *ppNewStream = pStream;
    }

    if (SUCCEEDED(hr))
    {
        /* Add stream to the media stream filter */
        IMediaStreamFilter_AddMediaStream((IMediaStreamFilter*)This->media_stream_filter, (IAMMediaStream*)pStream);
    }

    return hr;
}