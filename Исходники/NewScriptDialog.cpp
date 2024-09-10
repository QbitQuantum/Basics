void CNewScriptDialog::_PrepareDialog()
{
    int iSuggestedRoom = 0;

    // Look through game.ini for a vacant room number.
    DWORD nSize = 5000;
    TCHAR *pszNameValues = new TCHAR[nSize];
    if (pszNameValues)
    {
        std::string iniFileName = theApp.GetResourceMap().GetGameIniFileName();
        if (!iniFileName.empty())
        {
            DWORD nLength =  GetPrivateProfileSection(TEXT("Script"), pszNameValues, nSize, iniFileName.c_str());
            if (nLength > 0 && ((nSize - 2) != nLength)) // returns (nSize - 2) in case of insufficient buffer 
            {
                // Keep track of which script numbers have been used.
                ZeroMemory(_rgUsed, sizeof(_rgUsed));

                TCHAR *psz = pszNameValues;
                while(*psz)
                {
                    // The format is
                    // n000=ScriptName
                    size_t cch = strlen(psz);
                    TCHAR *pszEq = StrChr(psz, TEXT('='));
                    if (pszEq)
                    {
                        _DiscoveredScriptName(pszEq + 1);
                    }

                    // Take note of the script number.
                    int iScript = StrToInt(psz + 1);
                    if ((iScript >= 0) && (iScript < ARRAYSIZE(_rgUsed)))
                    {
                        _rgUsed[iScript] = 0xff;
                    }

                    // Advance to next string.
                    psz += (cch + 1);
                }

                iSuggestedRoom = _GetSuggestedScriptNumber();
            }
        }
        delete [] pszNameValues;
    }

    // Suggest a room:
    TCHAR szNumber[5];
    StringCchPrintf(szNumber, ARRAYSIZE(szNumber), TEXT("%d"), iSuggestedRoom);
    m_wndEditScriptNumber.SetWindowText(szNumber);

}