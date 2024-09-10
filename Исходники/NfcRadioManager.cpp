VOID WINAPI CNfcRadioManager::NFCInterfaceEnumCallback(
    _In_ HDEVQUERY hDevQuery,
    _In_opt_ PVOID pContext,
    _In_ const DEV_QUERY_RESULT_ACTION_DATA *pActionData
    )
{
    UNREFERENCED_PARAMETER(hDevQuery);

    TRACE_FUNCTION_ENTRY(LEVEL_VERBOSE);

    HRESULT hr = S_OK;
    CNfcRadioManager* pNfcRM = (CNfcRadioManager*) pContext;
    LPWSTR friendlyName = NULL;
    DEVPROPCOMPKEY propKeyFriendlyName[] = {{DEVPKEY_Device_FriendlyName, DEVPROP_STORE_SYSTEM, NULL}};
    ULONG devPropCount = 0;
    DEVPROPERTY* pDevProp = NULL;
    size_t cchFriendlyName = 0;
    
    switch (pActionData->Action)
    {
    case DevQueryResultStateChange:
        TRACE_LINE(LEVEL_INFO, "State change. New state=%d", pActionData->Data.State);
        if (DevQueryStateAborted == pActionData->Data.State)
        {
            //
            // If we hit an error, then we cannot tell if a new device comes or an old device goes. We will destroy the existing list of radios and then restart the query
            //
            hr = pNfcRM->CreateDevQuery();
        }
        else if (DevQueryStateEnumCompleted == pActionData->Data.State)
        {
            TRACE_LINE(LEVEL_INFO, "Initial enumeration complete.");
        }
        break;

    case DevQueryResultUpdate:
    case DevQueryResultAdd:

        // Though we do not expect any Updates to the fields that we are looking into, they will be funneled through Add where they will fail instance creation due to existing instance
        TRACE_LINE(LEVEL_INFO, "Action=%d received for %S", pActionData->Action, pActionData->Data.DeviceObject.pszObjectId);

        //
        // Retrieve the DEVPKEY_Device_FriendlyName property and use it to add a new device
        //
        hr = DevGetObjectProperties(DevObjectTypeDevice,
                                    pActionData->Data.DeviceObject.pszObjectId,
                                    DevQueryFlagNone,
                                    1, propKeyFriendlyName,
                                    &devPropCount, (const DEVPROPERTY**) &pDevProp);
        if (SUCCEEDED(hr))
        {
            cchFriendlyName = pDevProp->BufferSize + 1;
            friendlyName = (LPWSTR) malloc(sizeof(WCHAR) * cchFriendlyName);
            if (NULL != friendlyName)
            {
                CopyMemory(friendlyName, pDevProp->Buffer, pDevProp->BufferSize);
                friendlyName[cchFriendlyName - 1] = L'\0';

                TRACE_LINE(LEVEL_INFO, "DEVPKEY_Device_FriendlyName=%S for %S", friendlyName, pActionData->Data.DeviceObject.pszObjectId);
            }
            else
            {
                hr = E_OUTOFMEMORY;
            }
        }
        else // The driver doesn't report a friendly name so load the localized friendlyname
        {
            WCHAR szLocalFriendlyName[MAX_CCH_LOCAL_FRIENDLYNAME];
            ZeroMemory(szLocalFriendlyName, sizeof(szLocalFriendlyName));

            hr = S_OK;
            
            TRACE_LINE(LEVEL_INFO, "AEP query for %S did not return DEVPKEY_Device_FriendlyName property", pActionData->Data.DeviceObject.pszObjectId);
            
            DWORD cchCopied = LoadString(g_hInstance, IDS_NFC_RADIO_FRIENDLYNAME, szLocalFriendlyName, ARRAYSIZE(szLocalFriendlyName));

            if (cchCopied > 0)
            {
                TRACE_LINE(LEVEL_INFO, "Localized Name is %S", szLocalFriendlyName);
                cchFriendlyName = cchCopied;
            }
            else
            {
                TRACE_LINE(LEVEL_INFO, "Nothing found in Resource module");
                StringCchCopy(szLocalFriendlyName, ARRAYSIZE(szLocalFriendlyName), L"NFC");
                hr = StringCchLength(szLocalFriendlyName, STRSAFE_MAX_CCH, &cchFriendlyName);
            }

            if (SUCCEEDED(hr))
            {
                cchFriendlyName = cchFriendlyName + 1; // Additional space for the NULL character
                friendlyName = (LPWSTR) malloc(sizeof(WCHAR) * cchFriendlyName);
                
                if (NULL != friendlyName)
                {
                    CopyMemory(friendlyName, szLocalFriendlyName, cchCopied * sizeof(WCHAR));
                    friendlyName[cchFriendlyName - 1] = L'\0';
                }
                else
                {
                    hr = E_OUTOFMEMORY;
                }
            }
        }

        if (SUCCEEDED(hr) && (NULL != friendlyName))
        {
            //
            // Adding new radio with properties. NameLength should not matter here because the string should be a null terminated PWSTR.
            // RadioInstance takes ownership of friendlyName
            hr = pNfcRM->AddRadio(pActionData->Data.DeviceObject.pszObjectId, friendlyName);

            // AddRadio has successfully taken ownership of the friendly name
            friendlyName = NULL;
        }
        break;

    case DevQueryResultRemove :
        TRACE_LINE(LEVEL_INFO, "Action=%d received for %S", pActionData->Action, pActionData->Data.DeviceObject.pszObjectId);
        hr = pNfcRM->RemoveRadio(pActionData->Data.DeviceObject.pszObjectId);
        break;

    default:
        TRACE_LINE(LEVEL_INFO, "Action=%d received for %S", pActionData->Action, pActionData->Data.DeviceObject.pszObjectId);
        break;
    }

    if (friendlyName)
    {
        free(friendlyName);
    }

    if (pDevProp)
    {
        DevFreeObjectProperties(devPropCount, pDevProp);
        pDevProp = NULL;
        devPropCount = 0;
    }

    TRACE_FUNCTION_EXIT_HR(LEVEL_VERBOSE, hr);
    return;
}