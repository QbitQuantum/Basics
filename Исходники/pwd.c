char *GetHomeDirFromToken(char *userName, HANDLE token)
{
  UCHAR domain[200];
  wchar_t pw_buf[MAX_PATH] = { L'\0' };
  
  debug("-> GetHomeDirFromToken()...");
  
  PROFILEINFO profileInfo;

  // find the server name of the domain controller which created this token
  GetDomainFromToken ( &token, domain, sizeof(domain));
  //if (MultiByteToWideChar(CP_UTF8, 0, domain, -1, domainW, sizeof(domainW)) == 0)
  //{
    //debug("DomainServerName encoding conversion failure");
    //return NULL;
  //}

  profileInfo.dwFlags = PI_NOUI;
  profileInfo.lpProfilePath = NULL;
  profileInfo.lpUserName = userName;
  profileInfo.lpDefaultPath = NULL;
  profileInfo.lpServerName = domain;
  profileInfo.lpPolicyPath = NULL;
  profileInfo.hProfile = NULL;
  profileInfo.dwSize = sizeof(profileInfo);


  
  if (LoadUserProfile(token, &profileInfo) == FALSE)
  {
    debug("<- GetHomeDirFromToken()...");
    debug("LoadUserProfile failure: %d", GetLastError());
    
    return NULL;
  }

  /*
   * And retrieve homedir from profile.
   */
        
  if (!SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, token, 0, pw_homedir)))
  {
    debug("<- GetHomeDirFromToken()...");
    debug("SHGetFolderPath failed");
    
    return NULL;
  }

  // update APPDATA user's env variable
  if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_APPDATA, token, 0, pw_buf)))
  {
	  SetEnvironmentVariableW(L"APPDATA", pw_buf);
  }

  // update LOCALAPPDATA user's env variable
  if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, token, 0, pw_buf)))
  {
	  SetEnvironmentVariableW(L"LOCALAPPDATA", pw_buf);
  }

  /*
   * Unload user profile.
   */
       
  if (UnloadUserProfile(token, profileInfo.hProfile) == FALSE)
  {
    debug("WARNING. Cannot unload user profile (%u).", GetLastError());
  }
  
  debug("<- GetHomeDirFromToken()...");
  
  return pw_homedir;
}