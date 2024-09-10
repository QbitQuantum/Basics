/* --- PRIVATE FUNCTIONS ---------------------------------------------------- */
static void CallbackSdOwner(
    _In_ HANDLE hOutfile,
    _Inout_ PLDAP_RETRIEVED_DATA pLdapRetreivedData
    ) {
    BOOL bResult = FALSE;
    BOOL bDaclPresent = FALSE;
    BOOL bDaclDefaulted = FALSE;
    PACL pDacl = { 0 };
    PSECURITY_DESCRIPTOR pSd = (PSECURITY_DESCRIPTOR)pLdapRetreivedData->ppbData[0];

    if (!IsValidSecurityDescriptor(pSd)) {
        LOG(Err, _T("Invalid security descriptor"));
        return;
    }

    bResult = ControlWriteOwnerOutline(hOutfile, pSd, pLdapRetreivedData->tDN, CONTROL_AD_OWNER_KEYWORD);
    if (!bResult) {
        LOG(Err, _T("Cannot write owner control relation for <%s>"), pLdapRetreivedData->tDN);
    }

    bResult = GetSecurityDescriptorDacl(pSd, &bDaclPresent, &pDacl, &bDaclDefaulted);
    if (bResult == FALSE) {
        LOG(Err, _T("Failed to get DACL <%u>"), GetLastError());
        return;
    }

    if (bDaclPresent == FALSE || pDacl == NULL) {
        LOG(Info, "Null or no DACL for element <%s>", pLdapRetreivedData->tDN);
        bResult = ControlWriteOutline(hOutfile, gs_ptSidEveryone, pLdapRetreivedData->tDN, CONTROL_AD_NULL_DACL_KEYWORD);
        if (bResult == FALSE) {
            LOG(Err, _T("Cannot write null-dacl control relation for <%s>"), pLdapRetreivedData->tDN);
            return;
        }
    }
}