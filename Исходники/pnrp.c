//-----------------------------------------------------------------------------
// Function:    AsyncPeerNameResolve
// Purpose:     Wrapper function for PeerPnrpResolve that perform the
//              resolution asynchronously
// Parameters:
//   pwzPeerName [in]    : Peer Name to resolve
//   pwzCloudName [in]   : Cloud name in which to resolve
//
HRESULT AsyncPeerNameResolve(PCWSTR pwzPeerName, PCWSTR pwzCloudName)
{
    HRESULT                  hr = S_OK;
    PPEER_PNRP_ENDPOINT_INFO pEndpointInfo = NULL;
    ULONG                    cEndpoints = MAX_ENDPOINTS_TO_RESOLVE;
    HANDLE                   hEvent;
    HANDLE                   hResolve;

    wprintf(L"Resolving (this may take a few seconds)...\n");

    hEvent = CreateEvent(0, FALSE, FALSE, 0);
    if (hEvent == NULL)
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        return hr;
    }
    if (wcslen(pwzCloudName) != 0)
    {
        // Start an asynchronous resolve
        hr = PeerPnrpStartResolve(pwzPeerName, pwzCloudName, cEndpoints,
                                            hEvent, &hResolve);
    }
    else
    {
        // If no cloud name is given, search in all clouds (NULL argument)
        hr = PeerPnrpStartResolve(pwzPeerName, NULL, cEndpoints,
                                            hEvent, &hResolve);
    }

    cEndpoints = 0;
    if (SUCCEEDED(hr))
    {
        // Waits for up to 10 seconds for an endpoint to return
        while (WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0)
        {
            hr = PeerPnrpGetEndpoint(hResolve, &pEndpointInfo);
            if (hr == PEER_E_NO_MORE)
            {
                // Exit if all endpoints have been retrieved
                break;
            }
            else if (SUCCEEDED(hr))
            {
                // Display results as they are received
                hr = DisplayPNRPEndpoint(pEndpointInfo);
                if (FAILED(hr))
                {
                    wprintf(L"Error in DisplayEndpointInfo\n");
                }
                cEndpoints++;

                if (pEndpointInfo != NULL)
                {
                    PeerFreeData(pEndpointInfo);
                }
            }    
            else
            {
                break;
            }
        }
        if (cEndpoints == 0)
        {
            wprintf(L"No endpoints found for peer name %s\n", pwzPeerName);
        }

        // End Asynchronous Resolve
        hr = PeerPnrpEndResolve(hResolve);
        wprintf(L"Asynchronous resolve complete.\n");
    }

    CloseHandle(hEvent);
    return hr;
}