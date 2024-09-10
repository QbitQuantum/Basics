void CheckNddeShare()
{
    DWORD           dwAvail;
    WORD            wItems=0;
    BYTE            buffer[200];
    //LPBYTE            buffer;
    CHAR            szres[255];
    DWORD           err=0;
    char            szerror[16];
    char            *sztopiclist = {"bugboard|bugboard\0bugboard|bugboard\0bugboard|bugboard\0\0"};

    //FARPROC         fpNDdeShareGetInfo;

    PSID pworldsid;

    PACL pacl;

    SID_IDENTIFIER_AUTHORITY IdentifierAuthority = SECURITY_WORLD_SID_AUTHORITY;

    SECURITY_DESCRIPTOR sd;

    //HINSTANCE hinstNDDEAPI=NULL;

    SetErrorMode(SEM_FAILCRITICALERRORS);  //_NOOPENFILEERRORBOX);

    HINSTANCE hinstNDDEAPI = LoadLibrary("NDDEAPI.DLL");

    if (NULL == hinstNDDEAPI) // <= HINSTANCE_ERROR)
    {
        MessageBox(NULL, "NDDEAPI.DLL not found in path",  "bugboard.exe", MB_OK | MB_ICONSTOP);
        return;
    }

    SGIPROC fpNDdeShareGetInfo = (SGIPROC) GetProcAddress(hinstNDDEAPI, "NDdeShareGetInfoA");

    if (fpNDdeShareGetInfo == NULL)
    {
        FreeLibrary(hinstNDDEAPI);
        return;
    }

    UINT ret = (*fpNDdeShareGetInfo)(NULL, "bugboard$", 2,
                    buffer, sizeof(buffer), &dwAvail, &wItems);


    if (ret != NDDE_SHARE_NOT_EXIST) {
       return;

    }

    NDDESHAREINFO *pnddeInfo = (NDDESHAREINFO *)buffer;

    SAPROC lpfnNDdeShareAdd =
        (SAPROC) GetProcAddress(hinstNDDEAPI, "NDdeShareAddA");

    if (lpfnNDdeShareAdd == NULL)
    {
        FreeLibrary(hinstNDDEAPI);
        return;
    }


    /* this is all different for win32 (NT)
    lstrcpy(pnddeInfo->szShareName, "bugboard$");
    pnddeInfo->lpszTargetApp    = "bugboard";
    pnddeInfo->lpszTargetTopic  = "bugboard";
    pnddeInfo->lpbPassword1     = (LPBYTE) "";
    pnddeInfo->cbPassword1      = 0;
    pnddeInfo->dwPermissions1   = 15;
    pnddeInfo->lpbPassword2     = (LPBYTE) "";
    pnddeInfo->cbPassword2      = 0;
    pnddeInfo->dwPermissions2   = 0;
    pnddeInfo->lpszItem         = "";
    pnddeInfo->cAddItems        = 0;
    pnddeInfo->lpNDdeShareItemInfo = NULL;
    */


    // current structure
    pnddeInfo->lRevision        = 1L;
    pnddeInfo->lpszShareName    = _strdup("bugboard$");
    pnddeInfo->lShareType       = SHARE_TYPE_NEW | SHARE_TYPE_OLD | SHARE_TYPE_STATIC;
    pnddeInfo->lpszAppTopicList = (LPTSTR)sztopiclist;
    pnddeInfo->fSharedFlag      = 1;
    pnddeInfo->fService         = 0;
    pnddeInfo->fStartAppFlag    = 0;
    pnddeInfo->nCmdShow         = SW_SHOWMAXIMIZED;
    pnddeInfo->qModifyId[0]     = 0;
    pnddeInfo->qModifyId[1]     = 0;
    pnddeInfo->cNumItems        = 0;
    pnddeInfo->lpszItemList     = "\0";


    if (!AllocateAndInitializeSid( &IdentifierAuthority,
                                   1,
                                   SECURITY_WORLD_RID,
                                   0,0,0,0,0,0,0,
                                   &pworldsid))
    {
        FreeLibrary(hinstNDDEAPI);
        return;
    }


    pacl = (ACL*)malloc(sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) + GetLengthSid(pworldsid) - sizeof(DWORD) ) ;

    InitializeAcl(pacl,
                  sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) + GetLengthSid(pworldsid) - sizeof(DWORD),
                  ACL_REVISION);

    if (!IsValidAcl) {

       MessageBox(NULL, "ACL not valid",  "bugboard.exe", MB_OK | MB_ICONSTOP);
       FreeLibrary(hinstNDDEAPI);
       return;
    }

    if (!AddAccessAllowedAce(pacl,
                        ACL_REVISION,
                        STANDARD_RIGHTS_ALL | MAXIMUM_ALLOWED | GENERIC_ALL | ACCESS_SYSTEM_SECURITY,
                        pworldsid)) {
       MessageBox(NULL, "Add ACE failed",  "bugboard.exe", MB_OK | MB_ICONSTOP);
       FreeLibrary(hinstNDDEAPI);
       return;

    }

    if (!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION))
    {
       MessageBox(NULL, "Init sd failed",  "bugboard.exe", MB_OK | MB_ICONSTOP);
       FreeLibrary(hinstNDDEAPI);
       return;
    }

    if (!SetSecurityDescriptorOwner(&sd, NULL, FALSE))
    {
        FreeLibrary(hinstNDDEAPI);
        return;
    }

    if (!SetSecurityDescriptorGroup(&sd, NULL, FALSE))
    {
        FreeLibrary(hinstNDDEAPI);
        return;
    }


    if (!SetSecurityDescriptorDacl(&sd, TRUE, pacl, FALSE))
    {
        FreeLibrary(hinstNDDEAPI);
        return;
    }


    if (!IsValidSecurityDescriptor(&sd))
    {
       MessageBox(NULL, "Invalid sd",  "bugboard.exe", MB_OK | MB_ICONSTOP);
       FreeLibrary(hinstNDDEAPI);
       return;
    }

    ret = (*lpfnNDdeShareAdd)(NULL, 2, &sd, buffer, sizeof(buffer));

    if (ret != NDDE_NO_ERROR && ret != NDDE_SHARE_ALREADY_EXIST) {

       SGSPROC lpfnNDdeGetErrorString =
        (SGSPROC) GetProcAddress(hinstNDDEAPI, "NDdeGetErrorStringA");

       if (lpfnNDdeGetErrorString == NULL)
       {
        FreeLibrary(hinstNDDEAPI);
        return;
       }

       (*lpfnNDdeGetErrorString)(ret, (LPSTR)szres, 255);

       MessageBox(NULL, (LPSTR)szres,  "ERROR bugboard.exe", MB_OK | MB_ICONSTOP);

       FreeLibrary(hinstNDDEAPI);
       return;
    }

    SSTPROC lpfnNDdeSetTrustedShare =
        (SSTPROC) GetProcAddress(hinstNDDEAPI, "NDdeSetTrustedShareA");


    if (NDDE_NO_ERROR != ((*lpfnNDdeSetTrustedShare)(NULL, pnddeInfo->lpszShareName, NDDE_TRUST_SHARE_INIT)))
    {
       MessageBox(NULL, "Unable to set trusted share",  "ERROR bugboard.exe", MB_OK | MB_ICONSTOP);
    }

    FreeLibrary(hinstNDDEAPI);
}