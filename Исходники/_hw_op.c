HRESULT __SoraHwWaitTransferDone (PTX_DESC pTxDesc )
{
    HRESULT hr = S_OK;
    ULONG   uTemp  = 10000000;	// for MAX data transfer (24bit, 2^24 = 16M) it takes more time than previous value 100000

    // wait until hw owns the buffer
    while(pTxDesc->__FrameCtrlOwn == 1) 
    //hw will set it if TXDone. Tx Desc is in MmWriteCombined mem, so not cached.
    {
        uTemp--;
        if(uTemp < 1) {
            hr = E_TX_TRANSFER_FAIL;
            break;
        }
        _mm_pause();
    }
    return hr;
}