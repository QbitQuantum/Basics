char *getVersion(char *fileName)
{
    DWORD vSize;
    DWORD vLen,langD;
    BOOL retVal;

    LPVOID version=NULL;
    LPVOID versionInfo=NULL;
    static char fileVersion[256];
    bool success = true;
    vSize = GetFileVersionInfoSize(fileName,&vLen);
    if (vSize)
    {
        versionInfo = malloc(vSize+1);
        if (GetFileVersionInfo(fileName,vLen,vSize,versionInfo))
        {
            sprintf(fileVersion,"\\VarFileInfo\\Translation");
            retVal = VerQueryValue(versionInfo,fileVersion,&version,(UINT *)&vLen);
            if (retVal && vLen==4)
            {
                memcpy(&langD,version,4);
                sprintf(fileVersion, "\\StringFileInfo\\%02X%02X%02X%02X\\FileVersion",
                        (langD & 0xff00)>>8,langD & 0xff,(langD & 0xff000000)>>24,
                        (langD & 0xff0000)>>16);
            }
            else
                sprintf(fileVersion, "\\StringFileInfo\\%04X04B0\\FileVersion",
                        GetUserDefaultLangID());
            retVal = VerQueryValue(versionInfo,fileVersion,&version,(UINT *)&vLen);
            if (!retVal) success = false;
        }