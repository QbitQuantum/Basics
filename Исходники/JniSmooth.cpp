JNIEXPORT jboolean JNICALL jnm_exitWindows(JNIEnv *env, jobject obj, jint s)
{

  DWORD dwVersion = GetVersion();
  if ( dwVersion < 0x80000000)
    {
      // Windows NT4/2000/XP
      HANDLE hToken;
      LUID tmpLuid;
      
      HANDLE handleProcess=GetCurrentProcess();
      
      if (!OpenProcessToken(handleProcess,TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken))
	return JNI_FALSE;

      if (!LookupPrivilegeValue(0, SE_SHUTDOWN_NAME, &tmpLuid))
	return JNI_FALSE;

      TOKEN_PRIVILEGES NewState;
      LUID_AND_ATTRIBUTES luidattr;

      NewState.PrivilegeCount = 1;
      luidattr.Luid=tmpLuid;
      luidattr.Attributes=SE_PRIVILEGE_ENABLED;
      NewState.Privileges[0]=luidattr;

      if (!AdjustTokenPrivileges(hToken, false, &NewState, sizeof(TOKEN_PRIVILEGES), 0, 0))
	return JNI_FALSE;
    }

  if (ExitWindowsEx(s, 0))
    return JNI_TRUE;

  return JNI_FALSE;
}