/*****************************************************************
   LoggedSetLockPagesPrivilege: a function to obtain or
   release the privilege of locking physical pages.

   Inputs:

       HANDLE hProcess: Handle for the process for which the
       privilege is needed

       BOOL bEnable: Enable (TRUE) or disable?

   Return value: TRUE indicates success, FALSE failure.

*****************************************************************/
BOOL
LoggedSetLockPagesPrivilege ( HANDLE hProcess,
                              BOOL bEnable)
{
  struct {
    DWORD Count;
    LUID_AND_ATTRIBUTES Privilege [1];
  } Info;

  HANDLE Token;
  BOOL Result;

  // Open the token.

  Result = OpenProcessToken ( hProcess,
                              TOKEN_ADJUST_PRIVILEGES,
                              & Token);

  if( Result != TRUE )
  {
    printf( "Cannot open process token.\n" );
    return FALSE;
  }

  // Enable or disable?

  Info.Count = 1;
  if( bEnable )
  {
    Info.Privilege[0].Attributes = SE_PRIVILEGE_ENABLED;
  }
  else
  {
    Info.Privilege[0].Attributes = 0;
  }

  // Get the LUID.

  Result = LookupPrivilegeValue ( NULL,
                                  SE_LOCK_MEMORY_NAME,
                                  &(Info.Privilege[0].Luid));

  if( Result != TRUE )
  {
    printf( "Cannot get privilege for %s.\n", SE_LOCK_MEMORY_NAME );
    return FALSE;
  }

  // Adjust the privilege.

  Result = AdjustTokenPrivileges ( Token, FALSE,
                                   (PTOKEN_PRIVILEGES) &Info,
                                   0, NULL, NULL);

  // Check the result.

  if( Result != TRUE )
  {
    printf ("Cannot adjust token privileges (%u)\n", GetLastError() );
    return FALSE;
  }
  else
  {
    if( GetLastError() != ERROR_SUCCESS )
    {
      printf ("Cannot enable the SE_LOCK_MEMORY_NAME privilege; ");
      printf ("please check the local policy.\n");
      return FALSE;
    }
  }

  CloseHandle( Token );

  return TRUE;
}