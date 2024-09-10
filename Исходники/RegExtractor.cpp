BOOL CRegExtractorGUI::ExtractRealRegistryValues(BOOL bRegistryView32,EmulatedRegistry::CHostKey* pHostKey,OUT BOOL* pErrorDetectedDuringExtraction)
{
    BOOL bSuccess = TRUE;
    HKEY hBaseKey = NULL;
    HKEY hRemoteBaseKey = NULL;
    HKEY hKey = NULL;
    TCHAR* RelatvePathFromBaseKey = NULL;
    *pErrorDetectedDuringExtraction = FALSE;
    
    ////////////////////////////////////////////////////
    // for pHostKey->KeysFilteringType == KeysFilteringType_ONLY_SPECIFIED; only
    ////////////////////////////////////////////////////
#ifdef _DEBUG
    if (pHostKey->KeysFilteringType != EmulatedRegistry::CHostKey::KeysFilteringType_ONLY_SPECIFIED)
        DebugBreak();
#endif    
    
    REGSAM RegSam = KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE | KEY_READ;
    this->GetRegistryView(bRegistryView32,&RegSam);

    // for each specified key   
    std::vector<std::tstring*>::iterator iSpecifiedKeys;
    for (iSpecifiedKeys = pHostKey->SpecifiedKeys.begin();iSpecifiedKeys!=pHostKey->SpecifiedKeys.end();iSpecifiedKeys++)
    {
        std::tstring* pString = *iSpecifiedKeys;

        // get base key name and relative key from base key
        if (!this->GetBaseKeyFromFullPath((TCHAR*)pString->c_str(),&hBaseKey,&RelatvePathFromBaseKey))
        {
            free(RelatvePathFromBaseKey);
            return FALSE;
        }    
        
        // get base key
        if (pHostKey->IsLocalHost())
        {
            bSuccess = (::RegOpenKeyEx(hBaseKey,RelatvePathFromBaseKey,0,RegSam,&hKey) == ERROR_SUCCESS);
        }
        else // remote host
        {
            // remote registry must be enabled : see MSDN RegConnectRegistry for informations
            bSuccess = (::RegConnectRegistry((TCHAR*)pHostKey->KeyName.c_str(),hBaseKey,&hRemoteBaseKey) == ERROR_SUCCESS);
            if (bSuccess)
                bSuccess = (::RegOpenKeyEx(hRemoteBaseKey,RelatvePathFromBaseKey,0,RegSam,&hKey) == ERROR_SUCCESS);
        }
        
        // in case of success 
        if (bSuccess)
        {
            // create tree to subkey inside emulated registry
            TCHAR* pSplitter;
            TCHAR* LocalBuffer;
            TCHAR* KeyName;
            LocalBuffer = _tcsdup((TCHAR*)pString->c_str());
            KeyName = LocalBuffer;
            
            EmulatedRegistry::CKeyReplace* pUpperKey = (EmulatedRegistry::CKeyReplace*)pHostKey;
            EmulatedRegistry::CKeyReplace* pKey;

            pSplitter = KeyName; // provide a not empty value for splitter
            while(pSplitter)
            {
                pSplitter = _tcschr(KeyName,'\\');
                if (pSplitter)
                {
                    *pSplitter = 0;
                }
                if (!*KeyName)
                    break;
                pKey = pUpperKey->GetOrAddSubKey(KeyName);
                pUpperKey = pKey;
                KeyName = pSplitter+1;
            }
            free(LocalBuffer);
            
            // extract key values
            *pErrorDetectedDuringExtraction = *pErrorDetectedDuringExtraction || (!this->ExtractRealRegistryValues(bRegistryView32,pKey,hKey));
        }
        else
        {
            TCHAR Msg[2048];
            _sntprintf(Msg,2048, _T("Error opening key %s"),pString->c_str());
            this->ReportError(Msg);
            *pErrorDetectedDuringExtraction = TRUE;
        }
        
        // free memory
        free(RelatvePathFromBaseKey);
        if (hKey)
            ::RegCloseKey(hKey);
        if (hRemoteBaseKey)
            ::RegCloseKey(hRemoteBaseKey);
    
    }
    
    // return success status
    return bSuccess;
}