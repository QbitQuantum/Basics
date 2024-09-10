// OpenConnection is called by clients to initiate work with the resource manager under a specified transaction
// The transaction is passed in as a transaction token, to show how transactions objects can be serialized across
// processes
bool DTCResourceManager::OpenConnection(byte* transactionToken, ULONG tokenSize)
{
    std::cout << "The resource manager received an OpenConnection request. Enlisting in the transaction..." << std::endl;
    ITransactionReceiverFactory* pTxReceiverFactory = NULL;
    HRESULT hr = DtcGetTransactionManager(
    NULL,              // [in] char * pszHost,
    NULL,              // [in] char * pszTmName,
    IID_ITransactionReceiverFactory,    // [in] REFIID riid,
    0,                // [in] DWORD dwReserved1,
    0,                // [in] WORD wcbVarLenReserved2,
    (void *)NULL,          // [in] void * pvVarDataReserved2,
    (void **)&pTxReceiverFactory // [out] void ** ppv
    );
    if (FAILED (hr))
    {        
        std::cout << "DtcGetTransactionManager for ITransactionReceiverFactory failed: Error # " << std::hex << hr << std::endl;
        goto cleanup;
    }

    ITransactionReceiver* pTxReceiver = NULL;
    hr = pTxReceiverFactory->Create(&pTxReceiver);
    if (FAILED(hr))
    {        
        std::cout << "pTxReceiverFactory->Create failed: Error # " << std::hex << hr << std::endl;
        goto cleanup;
    }

    ITransaction* pTx = NULL;
    hr = pTxReceiver->UnmarshalPropagationToken(tokenSize, transactionToken, &pTx);
    if (FAILED(hr))
    {        
        std::cout << "pTxReceiver->UnmarshalPropagationToken failed: Error # " << std::hex << hr << std::endl;
        goto cleanup;
    }

    XACTUOW uow;
    LONG isoLevel;

    hr = _pRMManager->Enlist(pTx, this, &uow, &isoLevel, &_pEnlist);
    if (FAILED(hr))
    {        
        std::cout << "pRMManager->Enlist failed: Error # " << std::hex << hr << std::endl;
        goto cleanup;
    }

cleanup:
    if( pTx )
    {
        pTx->Release();
        pTx = NULL;
    }
    if( pTxReceiver )
    {
        pTxReceiver->Release();
        pTxReceiver = NULL;
    }

    if( pTxReceiverFactory )
    {
        pTxReceiverFactory->Release();
        pTxReceiverFactory = NULL;
    }

    if( FAILED(hr) )
    {
        std::cout << "OpenConnection failed" << std::endl;
        return false;
    }
    return true;
}