VOID
GetVersionInfo(
    BOOL Verbose
    )
{
    WCHAR          NameBuffer[MAXVERSIONBUFFER];
    WCHAR          Title1[128];
    WCHAR          Title2[128];
    WCHAR          wszPID[MAXVERSIONSTRING];
    WCHAR          wszPro[MAXVERSIONSTRING];
    WCHAR          wszSrv[MAXVERSIONSTRING];
    WCHAR          wszPBuild[MAXVERSIONSTRING];
    WCHAR          wszEvaluation[MAXVERSIONSTRING];
    UNICODE_STRING UserBuildString;
    UNICODE_STRING UserTypeString;
    UNICODE_STRING UserCSDString;
    NTSTATUS       Status;


    RTL_QUERY_REGISTRY_TABLE BaseServerRegistryConfigurationTable[] = {

        {NULL,
         RTL_QUERY_REGISTRY_DIRECT,
         L"CurrentBuildNumber",
         &UserBuildString,
         REG_NONE,
         NULL,
         0},

        {NULL,
         RTL_QUERY_REGISTRY_DIRECT,
         L"CurrentType",
         &UserTypeString,
         REG_NONE,
         NULL,
         0},

        {NULL,
         RTL_QUERY_REGISTRY_DIRECT,
         L"CSDVersion",
         &UserCSDString,
         REG_NONE,
         NULL,
         0},

        {NULL,
         0,
         NULL,
         NULL,
         REG_NONE,
         NULL,
         0}
    };

    UserBuildString.Buffer          = &NameBuffer[OFFSET_BLDSTRING];
    UserBuildString.Length          = 0;
    UserBuildString.MaximumLength   = MAXVERSIONSTRING * sizeof(WCHAR);

    UserTypeString.Buffer           = &NameBuffer[OFFSET_TYPSTRING];
    UserTypeString.Length           = 0;
    UserTypeString.MaximumLength    = MAXVERSIONSTRING * sizeof(WCHAR);

    UserCSDString.Buffer            = &NameBuffer[OFFSET_CSDSTRING];
    UserCSDString.Length            = 0;
    UserCSDString.MaximumLength     = MAXVERSIONSTRING * sizeof(WCHAR);

    Status = RtlQueryRegistryValues(RTL_REGISTRY_WINDOWS_NT,
                                    L"",
                                    BaseServerRegistryConfigurationTable,
                                    NULL,
                                    NULL);

    if (!NT_SUCCESS(Status)) {
        RIPMSG1(RIP_WARNING, "GetVersionInfo failed with status %x", Status);
        return;
    }

    ServerLoadString( hModuleWin, STR_DTBS_PRODUCTID, wszPID, ARRAY_SIZE(wszPID) );
    ServerLoadString( hModuleWin, STR_DTBS_PRODUCTPRO, wszPro, ARRAY_SIZE(wszPro) );
    ServerLoadString( hModuleWin, STR_DTBS_PRODUCTSRV, wszSrv, ARRAY_SIZE(wszSrv) );
    ServerLoadString( hModuleWin, STR_DTBS_PRODUCTBUILD, wszPBuild, ARRAY_SIZE(wszPBuild) );

    /*
     * Write out Debugging Version message.
     */

    /*
     * Bug 280256 - joejo
     * Create new desktop build information strings
     */
    swprintf(
        wszProductName,
        wszPID,
        ((USER_SHARED_DATA->NtProductType == NtProductWinNt) ? wszPro : wszSrv)
        );

    
    if (gfUnsignedDrivers) {
        /* This takes precedence */
        ServerLoadString( hModuleWin, STR_TESTINGONLY, wszEvaluation, ARRAY_SIZE(wszEvaluation) );
    } else if (USER_SHARED_DATA->SystemExpirationDate.QuadPart) {
        ServerLoadString(hModuleWin, STR_DTBS_EVALUATION, wszEvaluation,
                ARRAY_SIZE(wszEvaluation));
    } else {
        wszEvaluation[0] = '\0';
    }

    swprintf(
        wszProductBuild,
        wszPBuild,
        wszEvaluation,
        UserBuildString.Buffer
        );

    if (Verbose) {

        ServerLoadString( hModuleWin, STR_SAFEMODE_TITLE1, Title1, ARRAY_SIZE(Title1) );
        ServerLoadString( hModuleWin, STR_SAFEMODE_TITLE2, Title2, ARRAY_SIZE(Title2) );

        swprintf(
            wszT,
            UserCSDString.Length == 0 ? Title1 : Title2,
            UserBuildString.Buffer,
            UserCSDString.Buffer,
            USER_SHARED_DATA->NtSystemRoot
            );

    } else {
        PWSTR s = wcsrchr( UserTypeString.Buffer, L' ' );
        if (s) {
            s += 1;
        } else {
            s = UserTypeString.Buffer;
        }

        ServerLoadString( hModuleWin, STR_SAFEMODE_TITLE3, Title1, ARRAY_SIZE(Title1) );
        ServerLoadString( hModuleWin, STR_SAFEMODE_TITLE4, Title2, ARRAY_SIZE(Title2) );

        swprintf(
            wszT,
            UserCSDString.Length == 0 ? Title1 : Title2,
            UserBuildString.Buffer,
            UserCSDString.Buffer,
            s
            );
    }
}