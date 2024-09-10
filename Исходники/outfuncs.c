//+---------------------------------------------------------------------------
//
//  Function:   OpenDebugSinks()
//
//  Synopsis:
//
//  Arguments:
//
//  Returns:
//
//  History:    26-Jan-96   murthys   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
void OpenDebugSinks()
{
        // Get LogFile name
        char tmpstr[MAX_PATH];
        DWORD cbtmpstr = sizeof(tmpstr);
        LPTSTR lptstr;

        InitializeCriticalSection(&g_LogFileCS);
        GetProfileStringA("CairOLE InfoLevels", // section
                          "LogFile",               // key
                          "",             // default value
                          tmpstr,              // return buffer
                          cbtmpstr);
        if (tmpstr[0] != '\0')
        {
#ifdef _CHICAGO_
            lptstr = tmpstr;

            WriteToLogFile(lptstr);
#else
            // convert ansi to unicode
            WCHAR wtmpstr[MAX_PATH];

            lptstr = wtmpstr;
            if (MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, tmpstr, -1, wtmpstr, MAX_PATH))
            {
                WriteToLogFile(lptstr);
            }
            else
            {
                OutputDebugStringA("OLE32: MultiByteToWideChar failed for logfile!\n");
            }
#endif
        }

        // See if Debug Screen should be turned off
        GetProfileStringA("CairOLE InfoLevels", // section
                          "DebugScreen",               // key
                          "Yes",             // default value
                          tmpstr,              // return buffer
                          cbtmpstr);
        if ((tmpstr[0] == 'n') || (tmpstr[0] == 'N'))
        {
            WriteToDebugScreen(FALSE);  // turn off output to debugger screen
        }
}