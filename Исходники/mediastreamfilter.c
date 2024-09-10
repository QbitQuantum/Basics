static HRESULT WINAPI MediaStreamFilterImpl_AddMediaStream(IMediaStreamFilter* iface, IAMMediaStream *pAMMediaStream)
{
    IMediaStreamFilterImpl *This = impl_from_IMediaStreamFilter(iface);
    IMediaStream** streams;
    IPin** pins;
    MediaStreamFilter_InputPin* pin;
    HRESULT hr;
    PIN_INFO info;
    MSPID purpose_id;

    TRACE("(%p)->(%p)\n", iface, pAMMediaStream);

    streams = CoTaskMemRealloc(This->streams, (This->nb_streams + 1) * sizeof(IMediaStream*));
    if (!streams)
        return E_OUTOFMEMORY;
    This->streams = streams;
    pins = CoTaskMemRealloc(This->pins, (This->nb_streams + 1) * sizeof(IPin*));
    if (!pins)
        return E_OUTOFMEMORY;
    This->pins = pins;
    info.pFilter = (IBaseFilter*)&This->filter;
    info.dir = PINDIR_INPUT;
    hr = IAMMediaStream_GetInformation(pAMMediaStream, &purpose_id, NULL);
    if (FAILED(hr))
        return hr;
    /* Pin name is "I{guid MSPID_PrimaryVideo or MSPID_PrimaryAudio}" */
    info.achName[0] = 'I';
    StringFromGUID2(&purpose_id, info.achName + 1, 40);
    hr = BaseInputPin_Construct(&MediaStreamFilter_InputPin_Vtbl, sizeof(BaseInputPin), &info, &input_BaseFuncTable,
            &input_BaseInputFuncTable, &This->filter.csFilter, NULL, &This->pins[This->nb_streams]);
    if (FAILED(hr))
        return hr;

    pin = (MediaStreamFilter_InputPin*)This->pins[This->nb_streams];
    pin->pin.pin.pinInfo.pFilter = (LPVOID)This;
    This->streams[This->nb_streams] = (IMediaStream*)pAMMediaStream;
    This->nb_streams++;

    IMediaStream_AddRef((IMediaStream*)pAMMediaStream);

    return S_OK;
}