int SetupTokenPrivileges(PTOKEN_PRIVILEGES *pPrivToken, PSID userSid)
{
  DWORD ntStat = 0;
  
  int exitCode = 1;
  
  LSA_OBJECT_ATTRIBUTES lsaOA = {0};

  PLSA_UNICODE_STRING userRights = NULL;
  
  ULONG nRights = 0;
  
  DWORD size;
  
  int i, j;
  
  /*
   * Open local policy.
   */

  LSA_HANDLE hPolicy;
  
  lsaOA.Length = sizeof(lsaOA);
  
  ACCESS_MASK mask = POLICY_VIEW_LOCAL_INFORMATION | POLICY_LOOKUP_NAMES;
  
  debug("Opening local policy...");
  
  ntStat = LsaOpenPolicy(NULL, &lsaOA, mask, &hPolicy);
  
  FAIL(ntStat);
  
  /*
   * Retrieve user's privileges.
   */
  
  debug("Retrieving user's privileges list...");
  
  ntStat = LsaEnumerateAccountRights(hPolicy, userSid, &userRights, &nRights);

  /*
   * This error code means there is no any rights.
   * In this case, we should create empty list.
   */
  
  if (ntStat == STATUS_OBJECT_NAME_NOT_FOUND)
  {
    nRights = 0;
    ntStat  = 0;
  }
  
  FAIL(ntStat);
  
  /*
   * FIXME. Now if some privilege name is not recognized by
   * LookupPrivilegeName() part of pPrivToken buffer will be
   * unused.
   */
   
  /*
   * Allocate buffer for TOKEN_PRIVILEGES.
   */
  
  debug("Allocating buffer for TOKEN_PRIVILEGES [%u]...", nRights);
  
  size = sizeof(DWORD) + nRights * sizeof(LUID_AND_ATTRIBUTES);
  
  (*pPrivToken) = LocalAlloc(LPTR, size);
  
  FAIL(pPrivToken == NULL);
  
  /*
   * Fill TOKEN_PRIVILEGES with LUIDs of retrieved privileges.
   */
  
  j = 0;
  
  for (i = 0; i < nRights; i++)
  {
    /*
     * Retrieve unicode name of privilege.
     * Make sure there is a zero word at the end.
     */
    
    wchar_t privName[128];
    
    int len = userRights[i].Length;
    
    memcpy(privName, userRights[i].Buffer, len * sizeof(wchar_t));
    
    privName[len] = 0;
    
    debug("Adding %ls... ", privName);

    /*
     * Retrieve LUID for given privilege name.
     */
    
    if(LookupPrivilegeValueW(NULL, privName,
                                   &(*pPrivToken) -> Privileges[i].Luid) == FALSE)
    {
      debug("WARNING. Cannot add privilege to token (%u).", GetLastError());
    }
    else
    {
      (*pPrivToken) -> Privileges[j].Attributes = SE_PRIVILEGE_ENABLED;

      j++;
    }  
  }
  
  /*
   * j = number of privileges, which were recognized by
   * LookupPrivilegesValue().
   */
  
  (*pPrivToken) -> PrivilegeCount = j;
  
  exitCode = 0;

fail:

  /*
   * Clenup.
   */
  
  if (userRights)
  {
    LsaFreeMemory(userRights);
  }
  
  if (hPolicy)
  {
    CloseHandle(hPolicy);
  }  
  
  if (exitCode)
  {
    debug("ERROR. Cannot setup TOKEN_PRIVILEGES (err=%u, ntStat=%x).",
              GetLastError(), ntStat);
  }
}