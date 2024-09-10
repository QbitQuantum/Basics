//-----------------------------------------------------------------------------
// Function:    EnumeratePeopleNearMe
// Purpose:     Simple wrapper function that calls PeerCollabEnumPeopleNearMe
//              and displays the results.
// Parameters:  (none)
//
void EnumeratePeopleNearMe()
{
    PEER_PEOPLE_NEAR_ME**    ppPeopleNearMe = NULL;
    HRESULT                  hr = S_OK;
    HPEERENUM                hEnum = NULL;
    ULONG                    count = 0;

    //Open an enumeration of all PNM endpoints
    //
    hr = PeerCollabEnumPeopleNearMe(&hEnum);

    if (FAILED(hr))
    {
        wprintf(L"PeerCollabEnumPeopleNearMe failed.\nHRESULT=0x%x\n", hr);
        PrintError(hr);
    }

    hr = PeerGetItemCount(hEnum, &count);

    if (FAILED(hr))
    {
        wprintf(L"Error retrieving item count. HRESULT=0x%x\n", hr);
        PrintError(hr);
        goto exit;
    }

    if (count == 0)
    {
        wprintf(L"No PNM endpoints found.  PNM is not started by default.  On another Vista machine on your IPv6 subnet start PNM via this sample app or the PNM control panel icon.\n");
        hr = E_FAIL;
        goto exit;
    }

    //Obtain all endpoints in the enumeration
    //
    hr = PeerGetNextItem(hEnum, &count, (PVOID **) &ppPeopleNearMe);

    //Display a list of all the endpoints
    //
    if (SUCCEEDED(hr))
    {
        PrintPeopleNearMeInfo(ppPeopleNearMe, count);
    } 
    else
    {
        wprintf(L"Error retrieving endpoints, HRESULT=0x%x", hr);
        PrintError(hr);
    }


exit:
    SAFE_PEER_FREE_DATA(ppPeopleNearMe);

    //Close the enumeratration
    //
    SAFE_PEER_END_ENUMERATION(hEnum);
}