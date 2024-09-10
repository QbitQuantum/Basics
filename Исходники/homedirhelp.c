wchar_t *gethomedir_w(char *pUserName, char *pDomainName)
{
  HANDLE token;

  PROFILEINFOW profileInfo;
  
  wchar_t szPathW[MAX_PATH] = {0};
  
  wchar_t pUserName_w[UNLEN + 1] = {0};
  
  static wchar_t username_w[UNLEN + 1] = {0}; 
  
  DWORD usernamelen = UNLEN + 1;
  
  wchar_t pDomainName_w[UNLEN + 1] = {0};
  
  wchar_t *userprofile_w;
  
  /*
   * If there is home dir from lsa return it.
   */
  
  if (HomeDirLsaW[0] != L'\0')
  {
    debug("Using LSA HomeDirW.");
    
    return _wcsdup(HomeDirLsaW);
  }

  szPathW[0] = '\0';
  
  if (MultiByteToWideChar(CP_UTF8, 0, pUserName, -1, pUserName_w, UNLEN) == 0)
  {
    return NULL;
  }  
  
  if (pDomainName && 
          MultiByteToWideChar(CP_UTF8, 0, pDomainName,
                                  -1, pDomainName_w, UNLEN) == 0)
  {
    return NULL;
  }  

  debug3("gethomedir: pUserName [%s]", pUserName);

  GetUserNameW(username_w, &usernamelen);

  debug3("gethomedir: username [%ls]", username_w);

  if (wcscmp(pUserName_w, username_w) == 0)
  {
    /*
     * User query his own home dir, we can take it from env.
     */
    
    debug3("gethomedir: getenv");
  
    userprofile_w = _wgetenv(L"USERPROFILE");
    
    if (userprofile_w)
    {
      debug3("gethomedir: userprofile [%ls]", userprofile_w);
      
      /*
       * We have a %USERPROFILE% and we can return it
       */
      
      return _wcsdup(userprofile_w);
    }
    
    /*
     * Env not set, let's try to take it from token
     */
  }

  /*
   * If all above fail try to create user token manually
   * and get homedir using this token.
   */
  
  #ifdef USE_NTCREATETOKEN
  
  token = CreateUserTokenW(pUserName_w, pDomainName_w, L"sshd");
  
  if (token == NULL)
  {
    debug("gethomedir: create token failed");

    return NULL;
  }

  debug2("setting up profile info...");
  
  /*
   * Become the user
   */
  
  memset(&profileInfo, 0, sizeof(profileInfo));

  profileInfo.dwSize = sizeof(profileInfo);
  profileInfo.lpUserName = pUserName_w;
  profileInfo.lpServerName = pDomainName_w;

  debug2("LoadUserProfile()...");
  
  if (!LoadUserProfile(token, &profileInfo))
  {
    DWORD dwLast = GetLastError();
  
    debug("gethomedir: load profile failed [%d]", dwLast);
    
    return NULL;
  }

  /*
   * Get user's home directory
   */
  
  //if (!SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, token, 0, szPath)))
  
  debug2("SGGetFolderPath()...");
  
  if (!SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, token, 0, szPathW)))
  {
    debug("gethomedir: get folder failed");

    /*
     * Become self again.
     */

    UnloadUserProfile(token, profileInfo.hProfile);

    RevertToSelf();

    CloseHandle(token);

    return NULL;
  }

  debug3("gethomedir: szPathW [%ls]", szPathW);

  /*
   * Become self again.
   */
  
  UnloadUserProfile(token, profileInfo.hProfile);

  RevertToSelf();
  
  CloseHandle(token);

  debug2("<- gethomedir()...");
  
  return _wcsdup(szPathW);
  
  #else
  
  return NULL;
  
  #endif
}