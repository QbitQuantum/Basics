//-----------------------------------------------------------------------------
// Function:    EnumPeopleNearMe
//
// Purpose:     Simple wrapper function that calls PeerCollabEnumPeopleNearMe
//              and displays the results.  Setting fPrompt flag prompts user
//              to select an endpoint for further information.
//
// Returns:     HRESULT
//
HRESULT EnumPeopleNearMe()
{
    PEER_PEOPLE_NEAR_ME **   ppPeopleNearMe = NULL;
    PEER_PEOPLE_NEAR_ME *    pPersonNearMe = NULL;
    HRESULT                  hr = S_OK;
    HPEERENUM                hEnum = NULL;
    ULONG                    count = 0;
    ULONG                     index = 0;
 
    // Enumerate the people near me and setup the enumeration
    //
    hr = PeerCollabEnumPeopleNearMe(&hEnum);

    if (SUCCEEDED(hr))
    {
        hr = PeerGetItemCount(hEnum, &count);

        if (SUCCEEDED(hr))
        {
            if (count == 0)
            {
                PeerEndEnumeration(hEnum);
                return hr;
            }
            hr = PeerGetNextItem(hEnum, &count, (PVOID **) &ppPeopleNearMe);
        }

        if (SUCCEEDED(hr))
        {    
            // Add people to dialog
            //
            while (index < count)
            {
                if (SUCCEEDED(DuplicatePeerPeopleNearMe(&pPersonNearMe, ppPeopleNearMe[index])))
                {
                    //Add the person to the Listview
                    //
                    PostMessage(g_hModelDlgOwner, WM_ADDPERSON, 0, (LPARAM) pPersonNearMe);
                }
                index++;
            }
            // Free the used PEER resources
            //
            PeerFreeData(ppPeopleNearMe);
        }

        // End the PEER enumeration
        //
        PeerEndEnumeration(hEnum);     
    }
    return hr;
}