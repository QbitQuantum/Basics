BOOL SetOwner(LPCTSTR filename, LPCTSTR newOwner)
{
  PSID sid = nullptr;
  BOOL res = TRUE;
  PACL pacl = nullptr;

  // get the SID for the new owner
  TCHAR domainUnused[4096];
  DWORD sidSize = 0;
  DWORD domainBufSize = 4096;
  SID_NAME_USE sidUse;
  // pre-flight to determine required size of the sid
  LookupAccountName(nullptr, newOwner, nullptr, &sidSize, domainUnused, &domainBufSize, &sidUse);
  sid = (PSID)malloc(sidSize);
  // determine sid for account name
  if (!LookupAccountName(nullptr, newOwner, sid, &sidSize, domainUnused, &domainBufSize, &sidUse)) {
    qCritical("failed to look up account name: %ls", newOwner);
    res = FALSE;
  } else {
    EXPLICIT_ACCESS access;
    ZeroMemory(&access, sizeof(EXPLICIT_ACCESS));

    wchar_t ownerTemp[UNLEN + 1];
    wcsncpy(ownerTemp, newOwner, UNLEN + 1);

    // Set full control for Administrators.
    access.grfAccessPermissions = GENERIC_ALL;
    access.grfAccessMode = SET_ACCESS;
    access.grfInheritance = SUB_CONTAINERS_AND_OBJECTS_INHERIT;
    access.Trustee.TrusteeForm = TRUSTEE_IS_SID;
    access.Trustee.TrusteeType = TRUSTEE_IS_GROUP;
    access.Trustee.ptstrName = (LPTSTR)sid;

    DWORD secRes = SetEntriesInAcl(1, &access, nullptr, &pacl);
    if (secRes != ERROR_SUCCESS) {
      qCritical("failed to set up acls: %lu", secRes);
      return FALSE;
    }


    // filename parameter for SetNamedSecurityInfo isn't const
    // which is odd since it is documented to be a input parameter...
    TCHAR *fileNameBuf = new TCHAR[32768];
    wcsncpy_s(fileNameBuf, 32768, filename, 32768);
    // Set the owner on the file and give him full access
    secRes = SetNamedSecurityInfo(
        fileNameBuf, SE_FILE_OBJECT,
        OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION,
        sid, nullptr, pacl, nullptr);

    delete [] fileNameBuf;
    if (secRes != NOERROR) {
      qCritical("failed to set file owner: %d", secRes);
      res = false;
    }
  }

  if (sid != nullptr) {
    free(sid);
  }

  return res;
}