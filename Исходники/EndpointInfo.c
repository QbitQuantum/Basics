//-----------------------------------------------------------------------------
// Function:    SetEndpointName
// Purpose:     Routine to set the name of the current endpoint used by the peer application
// Parameters:  None.
//
void SetEndpointName()
{
    HRESULT hr = S_OK;
    WCHAR wzBuff[STRING_BUFSIZE];

    //Retrieve the desired endpoint name.
    //
    wprintf(L"Enter Endpoint name: ");
    GET_PROMPT_RESPONSE(hr, wzBuff);

    //Set the endpoint name
    //PeerCollabSetEndpointName imposes a limit of 255 Unicode characters
    //for the endpoint name.  For this sample we intentionally allow more than 255 characters to
    //demonstrate the error that is returned (E_INVALIDARG).
    //
    hr = PeerCollabSetEndpointName(wzBuff);

    if (SUCCEEDED(hr))
    {
        wprintf(L"Endpoint name successfully set\n");
    }
    else
    {
        wprintf(L"PeerCollabSetEndpointName failed. HRESULT=0x%x.\n", hr);
        PrintError(hr);
    }

exit:
    return;
}