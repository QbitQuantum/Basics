// Debugger Actions
HRESULT ThreadController::Connect()
{
    ATLENSURE_RETURN_HR(ThreadHelpers::IsOnDispatchThread(m_dispatchThreadId), E_UNEXPECTED);

    HRESULT hr = S_OK;

    if (this->IsConnected())
    {
        // Already connected so do nothing
        // We can get here if the front end and the BHOSite both try to cause a connection, so just ignore the double call.
    }
    else
    {
        // Get the IRemoteDebugApplication using our helper function that keeps it thread safe
        CComPtr<IRemoteDebugApplication> spDebugAppKeepAlive;
        hr = this->GetRemoteDebugApplication(spDebugAppKeepAlive);
        BPT_FAIL_IF_NOT_S_OK(hr);

        // Create thread event listener for listening to PDM debugger events
        CComObject<ThreadEventListener>* pThreadEventListener;
        hr = CComObject<ThreadEventListener>::CreateInstance(&pThreadEventListener);
        BPT_FAIL_IF_NOT_S_OK(hr);

        hr = pThreadEventListener->Initialize(this);
        BPT_FAIL_IF_NOT_S_OK(hr);

        m_spThreadEventListener = pThreadEventListener;

        // Populate sources before connecting
        // We need to call the enumeration on the debugger thread so that we act as if the PDM is firing the events normally
        // Calling Enumerate from the dispatch thread would cause locks to get obtained in the wrong order
        hr = this->CallDebuggerThread(PDMThreadCallbackMethod::Rundown, (DWORD_PTR)m_spSourceController.p, (DWORD_PTR)nullptr);
        BPT_FAIL_IF_NOT_S_OK(hr);

        // Connect up the IApplicationDebugger
        hr = spDebugAppKeepAlive->ConnectDebugger(pThreadEventListener);
        if (hr != S_OK)
        {
            // A debugger is already attached
            m_spThreadEventListener.Release();

            // We can still display and listen to source events due to the source rundown feature,
            // so we don't need to release our m_spDebugApp
            hr = E_ALREADY_ATTACHED;
        }
        else
        {
            // Enable support for user unhandled exceptions now that the debugger is attached
            CComQIPtr<IRemoteDebugApplication110> spDebugApp110 = spDebugAppKeepAlive;
            ATLENSURE_RETURN_HR(spDebugApp110.p != nullptr, E_NOINTERFACE);
            SCRIPT_DEBUGGER_OPTIONS options = SDO_ENABLE_NONUSER_CODE_SUPPORT;
            HRESULT hrOptions = spDebugApp110->SetDebuggerOptions(options, options);
            BPT_FAIL_IF_NOT_S_OK(hrOptions);
        }

        // Signal that we have attached the debugger (do this regardless of failure to unblock IE thread during JIT debugging)
        ::SendMessageW(m_hwndDebugPipeHandler, WM_WAITFORATTACH, NULL, /*startWaiting=*/ FALSE);

        m_isConnected = (hr == S_OK);
    }

    return hr;
}