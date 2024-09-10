BOOL WINAPI SSPLogonUser(LPTSTR szDomain, LPTSTR szUser, LPTSTR szPassword, loginfo_t* logger) {

   AUTH_SEQ    asServer   = {0};
   AUTH_SEQ    asClient   = {0};
   BOOL        fDone      = FALSE;
   BOOL        fResult    = FALSE;
   DWORD       cbOut      = 0;
   DWORD       cbIn       = 0;
   DWORD       cbMaxToken = 0;
   PVOID       pClientBuf = NULL;
   PVOID       pServerBuf = NULL;
   PSecPkgInfo pSPI       = NULL;
//   HMODULE     hModule    = NULL;

   SEC_WINNT_AUTH_IDENTITY ai;

   __try {

//      hModule = LoadSecurityDll();
//      if (!hModule)
//         __leave;

      // Get max token size
      _QuerySecurityPackageInfo(_T("NTLM"), &pSPI);
      cbMaxToken = pSPI->cbMaxToken;
      _FreeContextBuffer(pSPI);

      // Allocate buffers for client and server messages
      pClientBuf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbMaxToken);
      pServerBuf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbMaxToken);

      // Initialize auth identity structure
      ZeroMemory(&ai, sizeof(ai));
#if defined(UNICODE) || defined(_UNICODE)
      ai.Domain = szDomain;
      ai.DomainLength = lstrlen(szDomain);
      ai.User = szUser;
      ai.UserLength = lstrlen(szUser);
      ai.Password = szPassword;
      ai.PasswordLength = lstrlen(szPassword);
      ai.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;
#else
      ai.Domain = (unsigned char *)szDomain;
      ai.DomainLength = lstrlen(szDomain);
      ai.User = (unsigned char *)szUser;
      ai.UserLength = lstrlen(szUser);
      ai.Password = (unsigned char *)szPassword;
      ai.PasswordLength = lstrlen(szPassword);
      ai.Flags = SEC_WINNT_AUTH_IDENTITY_ANSI;
#endif

      // Prepare client message (negotiate) .
      cbOut = cbMaxToken;
      if (!GenClientContext(&asClient, &ai, NULL, 0, pClientBuf, &cbOut, &fDone, logger))
         __leave;

      // Prepare server message (challenge) .
      cbIn = cbOut;
      cbOut = cbMaxToken;
      if (!GenServerContext(&asServer, pClientBuf, cbIn, pServerBuf, &cbOut,
            &fDone, logger))
         __leave;
         // Most likely failure: AcceptServerContext fails with SEC_E_LOGON_DENIED
         // in the case of bad szUser or szPassword.
         // Unexpected Result: Logon will succeed if you pass in a bad szUser and
         // the guest account is enabled in the specified domain.

      // Prepare client message (authenticate) .
      cbIn = cbOut;
      cbOut = cbMaxToken;
      if (!GenClientContext(&asClient, &ai, pServerBuf, cbIn, pClientBuf, &cbOut,
            &fDone, logger))
         __leave;

      // Prepare server message (authentication) .
      cbIn = cbOut;
      cbOut = cbMaxToken;
      if (!GenServerContext(&asServer, pClientBuf, cbIn, pServerBuf, &cbOut,
            &fDone, logger))
         __leave;

      fResult = TRUE;

   } __finally {

      // Clean up resources
      if (asClient.fHaveCtxtHandle)
         _DeleteSecurityContext(&asClient.hctxt);

      if (asClient.fHaveCredHandle)
         _FreeCredentialsHandle(&asClient.hcred);

      if (asServer.fHaveCtxtHandle)
         _DeleteSecurityContext(&asServer.hctxt);

      if (asServer.fHaveCredHandle)
         _FreeCredentialsHandle(&asServer.hcred);

//      if (hModule)
//         UnloadSecurityDll(hModule);

      HeapFree(GetProcessHeap(), 0, pClientBuf);
      HeapFree(GetProcessHeap(), 0, pServerBuf);

   }

   return fResult;
}