//+---------------------------------------------------------------------------
//
// Function:  HrShowNetAdapters
//
// Purpose:   Display all installed net class devices using Setup API
//
// Arguments: None
//
// Returns:   S_OK on success, otherwise an error code
//
// Notes:
//
HRESULT HrShowNetAdapters()
{
#define MAX_COMP_INSTID 4096
#define MAX_COMP_DESC   4096

    HRESULT hr=S_OK;
    HDEVINFO hdi;
    DWORD dwIndex=0;
    SP_DEVINFO_DATA deid;
    BOOL fSuccess=FALSE;
//    DWORD   cchRequiredSize;
    WCHAR szCompInstanceId[MAX_COMP_INSTID];
    WCHAR szCompDescription[MAX_COMP_DESC];
    DWORD dwRegType;
    BOOL fFound=FALSE;

    // get a list of all devices of class 'GUID_DEVCLASS_NET'
    hdi = SetupDiGetClassDevs((struct _GUID *)&GUID_DEVCLASS_NET, NULL, NULL, DIGCF_PRESENT);

    if (INVALID_HANDLE_VALUE != hdi)
    {
        // enumerate over each device
        while (deid.cbSize = sizeof(SP_DEVINFO_DATA),
               SetupDiEnumDeviceInfo(hdi, dwIndex, &deid))
        {
            dwIndex++;

            // the right thing to do here would be to call this function
            // to get the size required to hold the instance ID and then
            // to call it second time with a buffer large enough for that size.
            // However, that would tend to obscure the control flow in
            // the sample code. Lets keep things simple by keeping the
            // buffer large enough.

            // get the device instance ID
            fSuccess = SetupDiGetDeviceInstanceIdW(hdi, &deid,
                                                  szCompInstanceId,
                                                  MAX_COMP_INSTID, NULL);
            if (fSuccess)
            {
                // get the description for this instance
                fSuccess =
                    SetupDiGetDeviceRegistryProperty(hdi, &deid,
                                                     SPDRP_DEVICEDESC,
                                                     &dwRegType,
                                                     (BYTE*) szCompDescription,
                                                     MAX_COMP_DESC,
                                                     NULL);
                if (fSuccess)
                {
                    if (!fFound)
                    {
                        fFound = TRUE;
                    }
                }
            }
        }

        // release the device info list
        SetupDiDestroyDeviceInfoList(hdi);
    }

    if (!fSuccess)
    {
        DWORD dwError = GetLastError();
        hr = HRESULT_FROM_WIN32(dwError);
    }

    return hr;
}