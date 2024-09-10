DWORD setDCOMPermission(
    HKEY RootKey, 
    LPTSTR KeyName, 
    PSID sid,
    LPTSTR ValueName,
    DWORD dwPermissionMask,
    BOOL bLimits)
{
    DWORD returnValue;
    SECURITY_DESCRIPTOR *sd = NULL;
    SECURITY_DESCRIPTOR *sdSelfRelative = NULL;
    SECURITY_DESCRIPTOR *sdAbsolute = NULL;
    DWORD secDescSize;
    BOOL present;
    BOOL defaultDACL;
    PACL dacl;
    BOOL newSD = FALSE;

    returnValue = GetNamedValueSD (RootKey, KeyName, ValueName, &sd, &newSD);

    //
    // Get security descriptor from registry or create a new one
    //

    if (returnValue != ERROR_SUCCESS)
    {
        return returnValue;
    }

    if (!GetSecurityDescriptorDacl (sd, &present, &dacl, &defaultDACL))
    {
        return GetLastError();
    }

    if ((newSD) && (!bLimits))
    {
        AddAccessAllowedACEToACL(
            &dacl, 
            COM_RIGHTS_EXECUTE,
            TEXT("SYSTEM"));
            
        AddAccessAllowedACEToACL(
            &dacl,
            COM_RIGHTS_EXECUTE,
            TEXT("INTERACTIVE"));
    }

    //get account according to the SID
    TCHAR userName[256];
    TCHAR acctName[256];
    TCHAR domainName[256];
    DWORD dwAcctName = 256;
    DWORD dwDomainName = 256;
    SID_NAME_USE eUse = SidTypeUnknown;

    if (LookupAccountSid(
        NULL,
        sid,
        acctName,
        (LPDWORD)&dwAcctName,
        domainName,
        &dwDomainName,
        &eUse)) 
    {
        sprintf(userName, "%s\\%s", domainName, acctName);
    }
    else
    {
        return GetLastError();
    }

    returnValue = AddAccessAllowedACEToACL (
        &dacl, 
        dwPermissionMask, 
        userName); 
    

    if (returnValue != ERROR_SUCCESS)
    {
        free (sd);
        return returnValue;
    }

    //
    // Make the security descriptor absolute if it isn't new
    //

    if (!newSD)
    {
        MakeSDAbsolute (
            (PSECURITY_DESCRIPTOR) sd, 
            (PSECURITY_DESCRIPTOR *) &sdAbsolute);
    } 
    else 
    {
        sdAbsolute = sd;
    }

    //
    // Set the discretionary ACL on the security descriptor
    //

    if (!SetSecurityDescriptorDacl (sdAbsolute, TRUE, dacl, FALSE))
        return GetLastError();

    //
    // Make the security descriptor self-relative so that we can
    // store it in the registry
    //

    secDescSize = 0;
    MakeSelfRelativeSD (sdAbsolute, sdSelfRelative, &secDescSize);
    sdSelfRelative = (SECURITY_DESCRIPTOR *) malloc (secDescSize);
    
    if (!MakeSelfRelativeSD (sdAbsolute, sdSelfRelative, &secDescSize))
    {
        return GetLastError();
    }

    //
    // Store the security descriptor in the registry
    //

    SetNamedValueSD (RootKey, KeyName, ValueName, sdSelfRelative);

    free (sd);
    free (sdSelfRelative);
    
    if (sd != sdAbsolute) 
    {
        free (sdAbsolute);
    }

    return ERROR_SUCCESS;
}