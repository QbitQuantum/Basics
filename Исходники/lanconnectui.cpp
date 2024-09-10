ULONG
WINAPI
CNetConnectionPropertyUi::Release()
{
    ULONG refCount = InterlockedDecrement(&ref);

    if (!refCount)
    {
        if (pNCfg)
        {
            pNCfg->Uninitialize();
            pNCfg->Release();
        }
        if (NCfgLock)
        {
            NCfgLock->Release();
        }
        if (pProperties)
        {
            NcFreeNetconProperties(pProperties);
        }
        delete this;
    }

    return refCount;
}