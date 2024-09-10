/***************************************************************************

   Function:   CheckFileVersion

   Purpose:    Check the version information of a given file

   Input:      File name
               File location (Windows dir, System dir, Current dir or none)
               Reference to Major number 
               Reference to Minor number 
               Reference to Build number 

   Output:     TRUE only if successful

   Remarks:    Trashes original file name

****************************************************************************/
BOOL CDLLVersion::CheckFileVersion (LPSTR szFileName, int FileLoc, 
                                    DWORD &dwMajor, DWORD &dwMinor, 
                                    DWORD &dwBuildNumber)
{
LPSTR   lpVersion;                        // String pointer to 'version' text
//UINT    uVersionLen;
DWORD   dwVerHnd=0;                        // An 'ignored' parameter, always '0'
//VS_FIXEDFILEINFO vsFileInfo;

    FixFilePath (szFileName, FileLoc);  // Add necessary path prefix to file name

    DWORD dwVerInfoSize = GetFileVersionInfoSize (szFileName, &dwVerHnd);
    if (!dwVerInfoSize)     // Cannot reach the DLL file
        return FALSE;

    LPSTR lpstrVffInfo = (LPSTR) malloc (dwVerInfoSize);  // Alloc memory for file info
    if (lpstrVffInfo == NULL)
        return FALSE;   // Allocation failed

        // Try to get the info
    if (!GetFileVersionInfo(szFileName, dwVerHnd, dwVerInfoSize, lpstrVffInfo)) 
    {
        free (lpstrVffInfo);
        return FALSE;   // Cannot read the file information - 
                        // wierd, since we could read the information size
    }

    /* The below 'hex' value looks a little confusing, but
       essentially what it is, is the hexidecimal representation
       of a couple different values that represent the language
       and character set that we are wanting string values for.
       040904E4 is a very common one, because it means:
       US English, Windows MultiLingual characterset
       Or to pull it all apart:
       04------        = SUBLANG_ENGLISH_USA
       --09----        = LANG_ENGLISH
       ----04E4 = 1252 = Codepage for Windows:Multilingual
    */
    /*static char fileVersion[256];
    LPVOID version=NULL;
    DWORD vLen,langD;
    BOOL retVal;

    sprintf(fileVersion,"\\VarFileInfo\\Translation");
    retVal = VerQueryValue ( lpstrVffInfo,  
                             fileVersion, &version, (UINT *)&uVersionLen);
    if (retVal && vLen==4)
    {
        memcpy(&langD,version,4);
        sprintf(fileVersion, "\\StringFileInfo\\%02X%02X%02X%02X\\FileVersion",
                (langD & 0xff00)>>8,langD & 0xff,(langD & 0xff000000)>>24, 
                (langD & 0xff0000)>>16);            
    }
    else 
        sprintf(fileVersion,"\\StringFileInfo\\%04X04B0\\FileVersion",GetUserDefaultLangID());

    if (!VerQueryValue (    lpstrVffInfo, fileVersion, 
                (LPVOID *)&lpVersion, (UINT *)&uVersionLen))
        {    
        free (lpstrVffInfo);
        return FALSE;     // Query was unsuccessful    
        }
    */
    // Now we have a string that looks like this :
    // "MajorVersion.MinorVersion.BuildNumber", so let's parse it
    lpVersion = getVersion(szFileName);
    m_stFullVersion = getVersion(szFileName);
    BOOL bRes = ParseVersionString (lpVersion, dwMajor, dwMinor, dwBuildNumber);
    if(!bRes)
        // Lets try for commas
        bRes = ParseVersionString1 (lpVersion, dwMajor, dwMinor, dwBuildNumber);
    free (lpstrVffInfo);
    return bRes;
}