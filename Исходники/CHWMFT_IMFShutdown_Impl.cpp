HRESULT CHWMFT::Shutdown(void)
{
    HRESULT hr = S_OK;

    do
    {
        CAutoLock lock(&m_csLock);

        hr = ShutdownEventQueue();
        if(FAILED(hr))
        {
            break;
        }

        hr = MFUnlockWorkQueue(m_dwDecodeWorkQueueID);
        if(FAILED(hr))
        {
            break;
        }

        m_bShutdown = TRUE;
    }while(false);

    return hr;
}