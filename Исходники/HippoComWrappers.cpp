STDMETHODIMP
HippoChatRoomWrapper::Invoke (DISPID        member,
                    const IID    &iid,
                    LCID          lcid,              
                    WORD          flags,
                    DISPPARAMS   *dispParams,
                    VARIANT      *result,
                    EXCEPINFO    *excepInfo,  
                    unsigned int *argErr)
{
    if (!ifaceTypeInfo_) 
         return E_OUTOFMEMORY;

    HippoQIPtr<IHippoChatRoom> hippoEmbed(static_cast<IHippoChatRoom *>(this));
    HRESULT hr = DispInvoke(hippoEmbed, ifaceTypeInfo_, member, flags, 
                             dispParams, result, excepInfo, argErr);

#if 0
    hippoDebug(L"Invoke: %#x - result %#x\n", member, hr);
#endif
    
    return hr;
}