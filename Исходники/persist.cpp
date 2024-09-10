/*****************************Private*Routine******************************\
* GetRecentFiles
*
* Reads at most MAX_RECENT_FILES from the app's registry entry. 
* Returns the number of files actually read.  
* Updates the File menu to show the "recent" files.
*
\**************************************************************************/
int
GetRecentFiles(
    int iLastCount,
    int iMenuPosition   // Menu position of start of MRU list
    )
{
    int     i;
    TCHAR   FileName[MAX_PATH];
    TCHAR   szKey[32];
    HMENU   hSubMenu;

    //
    // Delete the files from the menu
    //
    hSubMenu = GetSubMenu(GetMenu(hwndApp), 0);

    // Delete the separator at the requested position and all the other 
    // recent file entries
    if(iLastCount != 0)
    {
        DeleteMenu(hSubMenu, iMenuPosition, MF_BYPOSITION);

        for(i = 1; i <= iLastCount; i++)
        {
            DeleteMenu(hSubMenu, ID_RECENT_FILE_BASE + i, MF_BYCOMMAND);
        }
    }

    for(i = 1; i <= MAX_RECENT_FILES; i++)
    {
        DWORD   len;
        TCHAR   szMenuName[MAX_PATH + 3];

        (void)StringCchPrintf(szKey, NUMELMS(szKey), TEXT("File %d\0"), i);

        len = ProfileStringIn(szKey, TEXT(""), FileName, MAX_PATH * sizeof(TCHAR));
        if(len == 0)
        {
            i = i - 1;
            break;
        }

        StringCchCopy(aRecentFiles[i - 1], NUMELMS(aRecentFiles[i-1]), FileName);
        (void)StringCchPrintf(szMenuName, NUMELMS(szMenuName), TEXT("&%d %s\0"), i, FileName);

        if(i == 1)
        {
            InsertMenu(hSubMenu, iMenuPosition, MF_SEPARATOR | MF_BYPOSITION, (UINT)-1, NULL);
        }

        InsertMenu(hSubMenu, iMenuPosition + i, MF_STRING | MF_BYPOSITION,
            ID_RECENT_FILE_BASE + i, szMenuName);
    }

    //
    // i is the number of recent files in the array.
    //
    return i;
}