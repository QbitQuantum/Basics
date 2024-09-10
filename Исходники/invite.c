//-----------------------------------------------------------------------------
// Function:    DisplayApplicationRegistrations
// Purpose:     Retrieves and displays locally registered applications
// Parameters:  None
//
void DisplayApplicationRegistrations()
{
    PPEER_APPLICATION_REGISTRATION_INFO*  ppApplications = NULL;
    HPEERENUM           hApplicationEnum = NULL;
    ULONG               cApplications = 0;
    ULONG               i = 0;
    HRESULT             hr = S_OK;
    PPEER_APPLICATION_REGISTRATION_INFO pRegInfo = NULL;


    // Get a list of locally registered applications for the current user
    //
    wprintf(L"Enumerating all locally registered applications for the current user:\n");

    hr = PeerCollabEnumApplicationRegistrationInfo(PEER_APPLICATION_CURRENT_USER, &hApplicationEnum);

    IF_FAILED_PRINT_ERROR_AND_EXIT(hr, L"Error retrieving application info.");

    hr = PeerGetItemCount(hApplicationEnum, &cApplications);

    IF_FAILED_PRINT_ERROR_AND_EXIT(hr, L"Error retrieving item count.");

    if (cApplications == 0)
    {
        wprintf(L"There are no locally registered applications for the current user.\n");
    }
    else
    {
        hr = PeerGetNextItem(hApplicationEnum, &cApplications, (PVOID **) &ppApplications);

        IF_FAILED_PRINT_ERROR_AND_EXIT(hr, L"Error retrieving application info.");

        for (i = 0; i < cApplications; i++)
        {
            DisplayLocalApplicationInfo(ppApplications[i]);
            printf("\n");
        }
    }
    SAFE_PEER_END_ENUMERATION(hApplicationEnum);

    // Get a list of locally registgered applications for all users
    //
    wprintf(L"\nEnumerating all locally registered applications for all users:\n");

    hr = PeerCollabEnumApplicationRegistrationInfo(PEER_APPLICATION_ALL_USERS, &hApplicationEnum);

    IF_FAILED_PRINT_ERROR_AND_EXIT(hr, L"Error retrieving application info.");

    hr = PeerGetItemCount(hApplicationEnum, &cApplications);

    IF_FAILED_PRINT_ERROR_AND_EXIT(hr, L"Error retrieving item count.");

    if (cApplications == 0)
    {
        wprintf(L"There are no locally registered applications for all users.\n");
    }
    else
    {
        hr = PeerGetNextItem(hApplicationEnum, &cApplications, (PVOID **) &ppApplications);

        IF_FAILED_PRINT_ERROR_AND_EXIT(hr, L"Error retrieving application info.");

        for (i = 0; i < cApplications; i++)
        {
            DisplayLocalApplicationInfo(ppApplications[i]);
            printf("\n");
        }
    }

    SAFE_PEER_END_ENUMERATION(hApplicationEnum);

    wprintf(L"\nDisplaying registration for Collaboration Application:\n");

    hr = PeerCollabGetApplicationRegistrationInfo(&SampleAppGuid, PEER_APPLICATION_CURRENT_USER, &pRegInfo);

    if (SUCCEEDED(hr))
    {
        DisplayLocalApplicationInfo(pRegInfo);
    }
    else if (hr == PEER_E_NOT_FOUND)
    {
        wprintf(L"  Collaboration SDK Sample application is not registered\n");
    }
    else
    {
        wprintf(L"  Failed to get Application Registration Info. HRESULT=0x%x\n", hr);
        PrintError(hr);
    }

exit:
    SAFE_PEER_END_ENUMERATION(hApplicationEnum);
    SAFE_PEER_FREE_DATA(pRegInfo);
}