int InitUserSid(BOOL fDiagnostic, BPRINT_BUFFER *pbp)
{
   int err = 0;
   if ( ! ls.UserSid)
      {
      LPVOID pvInfo = NULL;
      DWORD cbSize = 0;
      if ( ! GetTokenInformation(ls.hToken, TokenUser,  NULL, 0, &cbSize))
         {
         err = GetLastError();
         if (ERROR_INSUFFICIENT_BUFFER == err)
            {
            err = 0;
            pvInfo = LocalAlloc(LPTR, cbSize);
            if ( ! pvInfo)
               {
               err = ERROR_OUTOFMEMORY;
               }
            else if ( ! GetTokenInformation(ls.hToken, TokenUser,  pvInfo, cbSize, &cbSize))
               {
               err = GetLastError();
               ReportError(err, "GetTokenInformation(TokenUser)");
               }
            else
               {
               err = 0;
               const TOKEN_USER * pUser = (const TOKEN_USER *)pvInfo;
               ls.UserSid = pUser->User.Sid;
               if (fDiagnostic)
                  {
                  bprintf(*pbp, TEXT("Got User Sid "));
                  PrintSidName(ls.UserSid, *pbp);
                  bprint_Sep(*pbp, ' ');
                  PrintSidText(ls.UserSid, *pbp);
                  bprint_EndLine(*pbp);
                  }
               }
            }
         }
      }

   return err;
}