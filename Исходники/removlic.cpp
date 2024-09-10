int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
    char pszPath[MAX_PATH];
    char pszOutput[10000];
    DWORD dwNumberOfBytesWritten;

    GetModuleFileName(NULL, pszPath, MAX_PATH);

    pszPath[strlen(pszPath)-3] = '\0';
    strcat(pszPath, "log");

    HANDLE file = NULL;

    file = CreateFile(pszPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if(!file) {
        MessageBox(NULL, "Failed to create log file!", "ATCMControl Remove Lic", MB_OK|MB_ICONERROR);
    }

    strcpy(pszOutput, "RemoveLic\r\n");
    WriteFile(file, pszOutput, strlen(pszOutput), &dwNumberOfBytesWritten, NULL);

    SYSTEMTIME sysTime;

    GetSystemTime(&sysTime);

    sprintf(pszOutput, "%i.%i.%i,%i:%i:%i\r\n", 
            sysTime.wDay, sysTime.wMonth, sysTime.wYear, 
            sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
    WriteFile(file, pszOutput, strlen(pszOutput), &dwNumberOfBytesWritten, NULL);

    // rever to the SoftingProd.h file for all products relatet to 4C!
    // remove the V2.0 ATCM Productkeys
    int i;
    for(i=1; i<=6; i++) {
        char strKey[10];
        _itoa(i, strKey, 10);
        RemoveLicKey(file, strKey);
    }
    RemoveLicKey(file, "20");
    RemoveLicKey(file, "21");
    RemoveLicKey(file, "23");
    RemoveLicKey(file, "52");

    // remove the V2.1 ATCM Productkey
    for(i=61; i<=75; i++) {
        char strKey[10];
        _itoa(i, strKey, 10);
        RemoveLicKey(file, strKey);
    }
    RemoveLicKey(file, "79");
    RemoveLicKey(file, "85");
    RemoveLicKey(file, "86");
    
    CloseHandle(file);

    if(gError>0) {
        MessageBox(NULL, "Not all license info could be deleted!", "ATCMControl Remove Lic", MB_OK|MB_ICONERROR);
    } else {
        sprintf(pszOutput, "ATCMControl license information removed successfully.\nLog information stored in %s", pszPath);
        MessageBox(NULL, pszOutput, "ATCMControl Remove Lic", MB_OK);

    }

	return 0;
}