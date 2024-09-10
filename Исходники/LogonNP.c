/****************************************************************************
   FUNCTION: NPLogonNotify

   PURPOSE:  This entry point is called when a user logs on.  If the user
             authentication fails here, the user will still be logged on
             to the local machine.

*******************************************************************************/
DWORD
WINAPI
NPLogonNotify (
              PLUID               lpLogonId,
              LPCWSTR             lpAuthentInfoType,
              LPVOID              lpAuthentInfo,
              LPCWSTR             lpPreviousAuthentInfoType,
              LPVOID              lpPreviousAuthentInfo,
              LPWSTR              lpStationName,
              LPVOID              StationHandle,
              LPWSTR              *lpLogonScript
              )
{
   PMSV1_0_INTERACTIVE_LOGON pAuthInfo;

   #ifdef DEBUG
   TCHAR szBuf[1024];

   // For debugging purposes only
   MessageBeep(0xFFFFFFFF);

   //
   // Write out some information about the logon attempt
   //
   wsprintf(szBuf, L"lpAuthentInfoType=%s lpStationName=%s\r\n",
            lpAuthentInfoType, lpStationName);

   WriteLogFile(szBuf);
   #endif


   //
   // If the primary authenticator is not MSV1_0, return success.
   // Why? Because this is the only auth info structure that we
   // understand and we don't want to interact with other types.
   //
   if ( lstrcmpiW (MSV1_0_AUTH_TYPE, lpAuthentInfoType) )
   {

      #ifdef DEBUG
      wsprintf(szBuf, L"Authenticator is not MSV1_0 - Returning.\n");

      WriteLogFile(szBuf);
      #endif

      SetLastError(NO_ERROR);
      return NO_ERROR;
   }

   //
   // Do something with the authentication information
   //
   pAuthInfo = (PMSV1_0_INTERACTIVE_LOGON) lpAuthentInfo;

   #ifdef DEBUG
   wsprintf(szBuf, L"LogonDomain=%s User=%s\r\n",
            pAuthInfo->LogonDomainName.Buffer,
            pAuthInfo->UserName.Buffer);

   WriteLogFile(szBuf);
   #endif

   //
   // Let's utilize the logon script capability to display
   // our logon information
   //

   // The Caller MUST free this memory
   *lpLogonScript = LocalAlloc(LPTR,1024);

   #ifdef DEBUG
   wsprintf(*lpLogonScript,L"notepad %s",LOGFILE);
   #endif

   return NO_ERROR;
}