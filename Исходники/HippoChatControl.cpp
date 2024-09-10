STDMETHODIMP
HippoChatControl::Invoke (DISPID        member,
                          const IID    &iid,
                          LCID          lcid,              
                          WORD          flags,
                          DISPPARAMS   *dispParams,
                          VARIANT      *result,
                          EXCEPINFO    *excepInfo,  
                          unsigned int *argErr)
{
    // Forward chat room events on to our connected listeners
    if (member == HIPPO_DISPID_ONUSERJOIN ||
        member == HIPPO_DISPID_ONUSERLEAVE ||
        member == HIPPO_DISPID_ONMESSAGE ||
        member == HIPPO_DISPID_ONRECONNECT ||
        member == HIPPO_DISPID_ONUSERMUSICCHANGE) 
    {
        HRESULT hr;

        HippoPtr<IConnectionPoint> point;
        hr = connectionPointContainer_.FindConnectionPoint(IID_IHippoChatRoomEvents, &point);
        if (FAILED(hr))
            return hr;

        HippoPtr<IEnumConnections> e;
        hr = point->EnumConnections(&e);
        if (FAILED(hr))
            return hr;

        CONNECTDATA data;
        ULONG fetched;
        while (e->Next(1, &data, &fetched) == S_OK) {
            HippoQIPtr<IDispatch> dispatch(data.pUnk);
            if (dispatch) {
                // If we passed the result return value, then we'd have to worry about freeing 
                // it to avoid leaks when it was overwritten. Just pass in null for the
                // return value since these events don't have return values
                hr = dispatch->Invoke(member, IID_NULL, 0 /* LCID */,
                                      DISPATCH_METHOD, dispParams, 
                                      NULL /* result */, NULL /* exception */, NULL /* argError */);

                // we debug log failure but otherwise ignore it
                if (FAILED(hr))
                    hippoDebugLogW(L"Invoke of notification %d failed: %x", member, hr);
            }
        }

        return S_OK;
    }

    if (!ifaceTypeInfo_) 
         return E_OUTOFMEMORY;

    HippoQIPtr<IHippoChatRoom> hippoChatControl(static_cast<IHippoChatRoom *>(this));
    HRESULT hr = DispInvoke(hippoChatControl, ifaceTypeInfo_, member, flags, 
                             dispParams, result, excepInfo, argErr);

#if 0
    hippoDebugDialog(L"Invoke: %#x - result %#x\n", member, hr);
#endif
    
    return hr;
}