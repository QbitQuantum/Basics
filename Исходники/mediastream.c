static HRESULT WINAPI DirectDrawMediaStreamImpl_IDirectDrawMediaStream_GetDirectDraw(IDirectDrawMediaStream *iface,
        IDirectDraw **ddraw)
{
    DirectDrawMediaStreamImpl *This = impl_from_IDirectDrawMediaStream(iface);

    TRACE("(%p)->(%p)\n", iface, ddraw);

    *ddraw = NULL;
    if (!This->ddraw)
    {
        HRESULT hr = DirectDrawCreateEx(NULL, (void**)&This->ddraw, &IID_IDirectDraw7, NULL);
        if (FAILED(hr))
            return hr;
        IDirectDraw7_SetCooperativeLevel(This->ddraw, NULL, DDSCL_NORMAL);
    }

    return IDirectDraw7_QueryInterface(This->ddraw, &IID_IDirectDraw, (void**)ddraw);
}