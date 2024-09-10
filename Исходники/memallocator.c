static HRESULT WINAPI BaseMemAllocator_Commit(IMemAllocator * iface)
{
    BaseMemAllocator *This = (BaseMemAllocator *)iface;
    HRESULT hr;

    TRACE("(%p)->()\n", This);

    EnterCriticalSection(&This->csState);
    {
        if (!This->pProps)
            hr = VFW_E_SIZENOTSET;
        else if (This->bCommitted)
            hr = S_OK;
        else if (This->bDecommitQueued)
        {
            This->bDecommitQueued = FALSE;
            hr = S_OK;
        }
        else
        {
            if (!(This->hSemWaiting = CreateSemaphoreW(NULL, This->pProps->cBuffers, This->pProps->cBuffers, NULL)))
            {
                ERR("Couldn't create semaphore (error was %ld)\n", GetLastError());
                hr = HRESULT_FROM_WIN32(GetLastError());
            }
            else
            {
                hr = This->fnAlloc(iface);
                if (SUCCEEDED(hr))
                    This->bCommitted = TRUE;
                else
                    ERR("fnAlloc failed with error 0x%lx\n", hr);
            }
        }
    }
    LeaveCriticalSection(&This->csState);

    return hr;
}