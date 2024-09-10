isc_result_t
isc_fsaccess_changeowner(const char *filename, const char *user) {
    SECURITY_DESCRIPTOR psd;
    BYTE sidBuffer[500];
    BYTE groupBuffer[500];
    PSID psid=(PSID) &sidBuffer;
    DWORD sidBufferSize = sizeof(sidBuffer);
    char domainBuffer[100];
    DWORD domainBufferSize = sizeof(domainBuffer);
    SID_NAME_USE snu;
    PSID pSidGroup = (PSID) &groupBuffer;
    DWORD groupBufferSize = sizeof(groupBuffer);


    /*
     * Determine if this is a FAT or NTFS disk and
     * call the appropriate function to set the ownership
     * FAT disks do not have ownership attributes so it's
     * a noop.
     */
    if (is_ntfs(filename) == FALSE)
        return (ISC_R_SUCCESS);

    if (!InitializeSecurityDescriptor(&psd, SECURITY_DESCRIPTOR_REVISION))
        return (ISC_R_NOPERM);

    if (!LookupAccountName(0, user, psid, &sidBufferSize, domainBuffer,
                           &domainBufferSize, &snu))
        return (ISC_R_NOPERM);

    /* Make sure administrators can get to it */
    domainBufferSize = sizeof(domainBuffer);
    if (!LookupAccountName(0, "Administrators", pSidGroup,
                           &groupBufferSize, domainBuffer, &domainBufferSize, &snu))
        return (ISC_R_NOPERM);

    if (!SetSecurityDescriptorOwner(&psd, psid, FALSE))
        return (ISC_R_NOPERM);

    if (!SetSecurityDescriptorGroup(&psd, pSidGroup, FALSE))
        return (ISC_R_NOPERM);

    if (!SetFileSecurity(filename,
                         OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION,
                         &psd))
        return (ISC_R_NOPERM);

    return (ISC_R_SUCCESS);
}