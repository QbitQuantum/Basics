bool GetSizeForDevID(wxString &TargetDevID, int *WidthMm, int *HeightMm)
{
    HDEVINFO devInfo = SetupDiGetClassDevsEx(
        &GUID_CLASS_MONITOR, //class GUID
        NULL, //enumerator
        NULL, //HWND
        DIGCF_PRESENT, // Flags //DIGCF_ALLCLASSES|
        NULL, // device info, create a new one.
        NULL, // machine name, local machine
        NULL);// reserved
    
    if (NULL == devInfo)
        return false;
    
    bool bRes = false;
    
    for (ULONG i=0; ERROR_NO_MORE_ITEMS != GetLastError(); ++i)
    {
        SP_DEVINFO_DATA devInfoData;
        memset(&devInfoData,0,sizeof(devInfoData));
        devInfoData.cbSize = sizeof(devInfoData);
        
        if (SetupDiEnumDeviceInfo(devInfo,i,&devInfoData))
        {
            wchar_t    Instance[80];
            SetupDiGetDeviceInstanceId(devInfo, &devInfoData, Instance, MAX_PATH, NULL);
            wxString instance(Instance);
            if(instance.Upper().Find( TargetDevID.Upper() ) == wxNOT_FOUND )
                continue;
            
            HKEY hDevRegKey = SetupDiOpenDevRegKey(devInfo,&devInfoData,
                                                   DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
            
            if(!hDevRegKey || (hDevRegKey == INVALID_HANDLE_VALUE))
                continue;
            
            bRes = GetMonitorSizeFromEDID(hDevRegKey, WidthMm, HeightMm);
            
            RegCloseKey(hDevRegKey);
        }
    }
    SetupDiDestroyDeviceInfoList(devInfo);
    return bRes;
}