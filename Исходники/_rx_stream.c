__inline HRESULT __WaitNewSignals(
    IN PRX_BLOCK       pScanPoint,
    IN USHORT          uRetries,
    IN ULONG           VStreamMask,
    OUT FLAG           *fReachEnd
)
{
    ULONG   uSpinCount  = uRetries * 2;
    *fReachEnd = 0;
    while(uSpinCount != 0)
    {
        if (SORA_C_RXBUF_IS_VALID_EX(pScanPoint, VStreamMask))
        {
            return S_OK;
        }
        else
        {
            _mm_clflush(pScanPoint);
            _mm_mfence();
            *fReachEnd = 1;
        }
        uSpinCount--;
    }

    return E_FETCH_SIGNAL_HW_TIMEOUT;
}