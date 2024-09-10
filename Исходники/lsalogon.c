int LsaLogon(HANDLE *hToken, char homeDir[MAX_PATH], char *user, 
                 char *pkBlob, int pkBlobSize, char *sign, int signSize, 
                     char *data, int dataSize, int dataFellow)
{
  int exitCode = 1;
  
  NTSTATUS ntStat = 0;
  
  LSA_STRING logonProcName;
  LSA_STRING originName;
  LSA_STRING authPckgName;
  
  HANDLE hLsa = NULL;
  
  LSA_OPERATIONAL_MODE securityMode;
  
  /*
   * Impersonation, "weak" token returned from network logon.
   * We can't create process as other user via this token.
   */
  
  HANDLE hWeakToken = NULL;
  
  /*
   * Login data.
   */
  
  LsaAuth *lsaAuth = NULL;

  ULONG lsaAuthSize = 0;

  ULONG authPckgId  = 0;
  
  TOKEN_SOURCE srcToken;
  
  PVOID profile = NULL;

  ULONG profileSize;
  
  LUID  logonId;
  
  QUOTA_LIMITS quotas;
  
  NTSTATUS loginStat;
  

  debug("-> LsaLogon()...");

  /*
   * We check only hToken arg, becouse other args are tested in AllocLsaAuth().
   */
  
  debug("Checking args...");
  
  FAIL(hToken == NULL);
  
  /*
   * Setup lsa strings.
   */

  debug("Setting up LSA Strings...");
  
  FAIL(InitLsaString(&logonProcName, "sshd-logon"));
  FAIL(InitLsaString(&originName, "NTLM"));
  FAIL(InitLsaString(&authPckgName, "SSH-LSA"));

  /*
   * Enable needed privilege to current running process.
   */

  EnablePrivilege("SeTcbPrivilege", 1);
  
  /*
   * Register new logon process.
   */
  
  debug("LsaRegisterLogonProcess()...");

  NTFAIL(LsaRegisterLogonProcess(&logonProcName, &hLsa, &securityMode));
  
  /*
   * Retrieve Authenticated Package ID.
   */
  
  debug("Retrieving Authentification Package ID...");
  
  NTFAIL(LsaLookupAuthenticationPackage(hLsa, &authPckgName, &authPckgId));
  
  /*
   * Allocate LsaAuth struct.
   */

  debug("Allocating LsaAuth struct...");
  
  FAIL(AllocLsaAuth(&lsaAuth, user, pkBlob, pkBlobSize,
                       sign, signSize, data, dataSize, dataFellow));
                       
  lsaAuthSize = lsaAuth -> totalSize_;                       

  /*
   * Create TOKEN_SOURCE part
   */
  
  debug("Setting up TOKEN_SOURCE...");
  
  FAIL(AllocateLocallyUniqueId(&srcToken.SourceIdentifier) == FALSE);
  
  memcpy(srcToken.SourceName, "**sshd**", 8);

  /*
   * Try to login using LsaAuth struct.
   */

  debug("Login attemp...");
  
  NTFAIL(LsaLogonUser(hLsa, &originName, Network,
                          authPckgId, lsaAuth, lsaAuthSize, NULL,
                              &srcToken, &profile, &profileSize,
                                  &logonId, &hWeakToken, &quotas, &loginStat));

  debug("login status: %x...", loginStat);
  
  
  //FAIL(WideCharToMultiByte( CP_UTF8, 0, profile, -1, homeDir, MAX_PATH, NULL, NULL)==0);
  //memcpy(homeDir, profile, MAX_PATH*sizeof(wchar_t));

  lstrcpyW(homeDir, profile);
  
  debug("homedir = [%ls]", (char *) homeDir);

  //strcpy(homeDir, profile);
  
  //PrintToken(hToken);
  
  /*
   * Duplicate 'weak' impersonation token into Primary Key token.
   * We can create process using duplicated token.
   */
  
  debug("Duplicating token...");
  
  FAIL(DuplicateTokenEx(hWeakToken, MAXIMUM_ALLOWED,
                            NULL, SecurityImpersonation,
                                TokenPrimary, hToken) == 0);
  
  exitCode = 0;
  
fail:

  if (exitCode)
  {
    switch(ntStat)
    {
      case STATUS_LOGON_FAILURE:
      {
        debug("SSH-LSA authorization failed. " 
                  "(err = %u, ntStat = %x).", GetLastError(), ntStat);

        exitCode = 0;

        break;
      }
      
      case STATUS_NO_SUCH_PACKAGE:
      {
        debug("SSH-LSA package not found. "
                  "(err = %u, ntStat = %x).", GetLastError(), ntStat);
                  
        break;          
      }
      
      default:
      {
        debug("Cannot logon using LSA package (err = %u, ntStat = %x).",
                  GetLastError(), ntStat);
      }
    }        
            
    hToken = NULL;
  }
  else
  {
    debug("LsaLogon : OK.");
  }

  /*
   * Clean up.
   */
  
  CloseHandle(hWeakToken);
  
  LsaFreeReturnBuffer(profile);
   
  EnablePrivilege("SeTcbPrivilege", 0);
  
  LsaDeregisterLogonProcess(hLsa);
  
  ClearLsaString(&logonProcName);
  ClearLsaString(&originName);
  ClearLsaString(&authPckgName);
         
  debug("<- LsaLogon()...");
  
  return exitCode;
}