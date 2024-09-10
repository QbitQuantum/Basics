/////////////////////////////////////////////////////////////////////////////////
// DisplayPropertySheet
/////////////////////////////////////////////////////////////////////////////////
// This function displays the property dialog.
// It is called by CPlApplet when the ac97cpl icon gets a double click.
//
// Arguments:
//    hWnd      parent window handle
//
// Return Value:
//    None.
//
void DisplayPropertySheet (HWND hWnd)
{
    SP_PROPSHEETPAGE_REQUEST    pspRequest;         // structure passed to ac97prop
    SP_DEVINFO_DATA             DeviceInfoData;     // pspRequest points to it.
    HMODULE                     hDLL;               // Module handle of library
    LPFNADDPROPSHEETPAGES       AC97PropPageProvider; // function to be called.
    PROPSHEETHEADER             psh;
    WCHAR                       wszFormat[128];
    size_t                      iRes;

    // You could move this to CPL_INIT, then it would be called
    // before the control panel window appears.
    // In case of an failure the icon would not be displayed. In our sample
    // however, the icon will be displayed and when the user clicks on it he
    // gets the error message.
    if (!FindAC97Device(&pspRequest, &DeviceInfoData))
    {
        iRes = LoadString(ghInstance, IDS_AC97_WARNING_MUST_INSTALL_DRIVER, wszFormat, ARRAYSIZE(wszFormat));
        if (iRes >0)
        {
            MessageBox (hWnd, wszFormat, AppletName, MB_ICONSTOP | MB_OK);
        }
        return;
    }

    // Load the library and get the function pointer.
    if (!GetDLLInfo (&hDLL, &AC97PropPageProvider))
    {
        iRes = LoadString(ghInstance, IDS_AC97_WARNING_PROPERTYPAGE_DLL_COULD_NOT_LOAD, wszFormat, ARRAYSIZE(wszFormat));
        if (iRes >0)
        {
            MessageBox (hWnd, wszFormat, AppletName, MB_ICONSTOP | MB_OK);
        }

        SetupDiDestroyDeviceInfoList (pspRequest.DeviceInfoSet);
        return;
    }

    //
    // Prepare the header for the property sheet.
    //
    psh.nStartPage = 0;
    psh.dwSize = sizeof(psh);
    psh.dwFlags = PSH_PROPTITLE | PSH_NOAPPLYNOW;
    psh.hwndParent = hWnd;
    psh.hInstance = ghInstance;
    psh.pszIcon = NULL;
    psh.pszCaption = MAKEINTRESOURCE(IDS_AC97CPL);
    psh.nPages = 1;

    // Call the function to request the property sheet page.
    if (!(*AC97PropPageProvider) ((LPVOID)&pspRequest, AddPropSheet, (LPARAM)&psh.phpage))
    {
        iRes = LoadString(ghInstance, IDS_AC97_WARNING_PROPERTYPAGEPROVIDER_FAILURE, wszFormat, ARRAYSIZE(wszFormat));
        if (iRes >0)
        {
            MessageBox (hWnd, wszFormat, AppletName, MB_ICONSTOP | MB_OK);
        }
        FreeLibrary (hDLL);
        SetupDiDestroyDeviceInfoList (pspRequest.DeviceInfoSet);
        return;
    }

    // Create the dialog. The function returns when the dialog is closed.
    if (PropertySheet (&psh) < 0)
    {
        //
        // Dialog closed abnormally. This might be a system failure.
        //
        iRes = LoadString(ghInstance, IDS_AC97_WARNING_REINSTALL_DRIVER, wszFormat, ARRAYSIZE(wszFormat));
        if (iRes >0)
        {
            MessageBox (hWnd, wszFormat, AppletName, MB_ICONSTOP | MB_OK);
        }
    }

    // Clean up.
    FreeLibrary (hDLL);
    LocalFree (psh.phpage);
    SetupDiDestroyDeviceInfoList (pspRequest.DeviceInfoSet);
}