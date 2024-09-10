void CallAddAsync(
    __in int a, 
    __in int b)
{
    HRESULT hr;
    WS_ERROR* error = NULL;
    HANDLE eventHandle = NULL;
    int* sumPointer = NULL;
    
    // Create an error object for storing rich error information
    hr = WsCreateError(
        NULL, 
        0, 
        &error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Create an event handle that will be signaled in callback
    eventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (eventHandle == NULL)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto Exit;
    }
    
    // Store information used by the callback when add completes
    AddCompletion addCompletion;
    addCompletion.eventHandle = eventHandle;
    
    // Allocate space to store return value
    sumPointer = (int*)HeapAlloc(GetProcessHeap(), 0, sizeof(int));
    if (sumPointer == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto Exit;
    }
    
    // Specify the callback to call if function completes synchronously
    // along with the state to pass to the callback (AddCompletion structure)
    WS_ASYNC_CONTEXT asyncContext;
    asyncContext.callback = OnAddComplete;
    asyncContext.callbackState = &addCompletion;
    
    // Call the function asynchronously
    hr = Add(a, b, sumPointer, &asyncContext, error);
    
    // Zero out asyncContext to illustrate that async function should have copied it
    ZeroMemory(&asyncContext, sizeof(asyncContext));
    
    if (hr == WS_S_ASYNC)
    {
        // Function completed asynchronously
    
        // Wait for callback to signal completion
        if (WaitForSingleObject(eventHandle, INFINITE) != WAIT_OBJECT_0)
        {
            hr = HRESULT_FROM_WIN32(GetLastError());
            goto Exit;
        }
    
        // Get error code that was stored by callback
        hr = addCompletion.errorCode;
    }
    
    wprintf(L"%d\n", *sumPointer);
    
Exit:
    if (FAILED(hr))
    {
        // Print out the error
        PrintError(hr, error);
    }
    
    if (eventHandle != NULL)
    {
        CloseHandle(eventHandle);
    }
    
    if (sumPointer != NULL)
    {
        // Free value
        HeapFree(GetProcessHeap(), 0, sumPointer);
    }
    
    if (error != NULL)
    {
        WsFreeError(error);
    }
}