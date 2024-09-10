static
ULONG
WINAPI
INetConnectionPropertyUi2_fnRelease(
    INetConnectionPropertyUi2 * iface)
{
    INetConnectionPropertyUiImpl * This =  (INetConnectionPropertyUiImpl*)iface;
    ULONG refCount = InterlockedDecrement(&This->ref);

    if (!refCount) 
    {
        if (This->pNCfg)
        {
            INetCfg_Uninitialize(This->pNCfg);
            INetCfg_Release(This->pNCfg);
        }
        if (This->NCfgLock)
        {
            INetCfgLock_Release(This->NCfgLock);
        }
        if (This->pProperties)
        {
            NcFreeNetconProperties(This->pProperties);
        }
        CoTaskMemFree (This);
    }
    return refCount;
}