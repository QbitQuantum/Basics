int __cdecl wmain(int argc, WCHAR* argv[])
{
    HRESULT hr = E_FAIL;
    
    ITransaction* pITransaction = NULL;
    HANDLE hTransactionHandle = INVALID_HANDLE_VALUE;

    // Parse the command line to see if -abort switch is used or not.
    // If the abort switch is used the transaction will be aborted at the end,
    // otherwise it will be committed.
    ParseCommandLine(argc, argv);

    // Get a pointer to a new transaction
    hr = CreateTransaction(&pITransaction);
    if (FAILED(hr)) 
        goto cleanup;

    // Get a transaction handle to use with the transacted file operation
    hr = GetKernelTransactionHandle(pITransaction, &hTransactionHandle);
    if (FAILED(hr)) 
        goto cleanup;

    // Do a transacted file operation
    hr = TransactedFileOperation(hTransactionHandle);
    if (FAILED(hr)) 
        goto cleanup;


    //-------------------------------------------------------------------------
    // Here you can do other operations to various Resource Managers as part 
    // of this transaction using the same ITransaction.
    //-------------------------------------------------------------------------


    // Commit or abort the transaction depending on the g_fAbort boolean variable
    // which was set by using the -abort command line parameter
    hr = CommitOrAbortTransaction(pITransaction);
    if (FAILED(hr)) 
        goto cleanup;

cleanup:
    
    if(INVALID_HANDLE_VALUE != hTransactionHandle)
    {
        CloseHandle(hTransactionHandle);
        hTransactionHandle = INVALID_HANDLE_VALUE;
    }
    
    if(NULL != pITransaction)
    {
        pITransaction->Release();
        pITransaction = NULL;
    }

    return 0;
}