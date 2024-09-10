void Creds_OnUpdate (HWND hDlg)
{
   LPTSTR pszCell = (LPTSTR)GetWindowLongPtr (hDlg, DWLP_USER);
   if (!pszCell || !*pszCell)
      {
      BOOL fRunning = IsServiceRunning();
      ShowWindow (GetDlgItem (hDlg, IDC_RUNNING), fRunning);
      ShowWindow (GetDlgItem (hDlg, IDC_STOPPED), !fRunning);
      ShowWindow (GetDlgItem (hDlg, IDC_CREDS_OBTAIN), fRunning);
      return;
      }

   lock_ObtainMutex(&g.credsLock);
   size_t iCreds;
   for (iCreds = 0; iCreds < g.cCreds; ++iCreds)
      {
      if (!lstrcmpi (g.aCreds[ iCreds ].szCell, pszCell))
         break;
      }

   TCHAR szGateway[cchRESOURCE] = TEXT("");
   if (!g.fIsWinNT)
      GetGatewayName (szGateway);

   if (!szGateway[0])
      {
      SetDlgItemText (hDlg, IDC_CREDS_CELL, pszCell);
      }
   else
      {
      TCHAR szCell[ cchRESOURCE ];
      TCHAR szFormat[ cchRESOURCE ];
      GetString (szFormat, IDS_CELL_GATEWAY);
      wsprintf (szCell, szFormat, pszCell, szGateway);
      SetDlgItemText (hDlg, IDC_CREDS_CELL, szCell);
      }

   if (iCreds == g.cCreds)
      {
      TCHAR szText[cchRESOURCE];
      GetString (szText, IDS_NO_CREDS);
      SetDlgItemText (hDlg, IDC_CREDS_INFO, szText);
      }
   else
      {
      // FormatString(%t) expects a date in GMT, not the local time zone...
      //
      FILETIME ftLocal;
      SystemTimeToFileTime (&g.aCreds[ iCreds ].stExpires, &ftLocal);

      FILETIME ftGMT;
      LocalFileTimeToFileTime (&ftLocal, &ftGMT);

      SYSTEMTIME stGMT;
      FileTimeToSystemTime (&ftGMT, &stGMT);

      SYSTEMTIME stNow;
      GetLocalTime (&stNow);

      FILETIME ftNow;
      SystemTimeToFileTime (&stNow, &ftNow);

      LONGLONG llNow = (((LONGLONG)ftNow.dwHighDateTime) << 32) + (LONGLONG)(ftNow.dwLowDateTime);
      LONGLONG llExpires = (((LONGLONG)ftLocal.dwHighDateTime) << 32) + (LONGLONG)(ftLocal.dwLowDateTime);

      llNow /= c100ns1SECOND;
      llExpires /= c100ns1SECOND;

      LPTSTR pszCreds = NULL;
      if (llExpires <= (llNow + (LONGLONG)cminREMIND_WARN * csec1MINUTE))
          pszCreds = FormatString (IDS_CREDS_EXPIRED, TEXT("%s"), g.aCreds[ iCreds ].szUser);

      if (!pszCreds || !pszCreds[0])
          pszCreds = FormatString (IDS_CREDS, TEXT("%s%t"), g.aCreds[ iCreds ].szUser, &stGMT);
      SetDlgItemText (hDlg, IDC_CREDS_INFO, pszCreds);
      FreeString (pszCreds);
      }

   lock_ReleaseMutex(&g.credsLock);
   CheckDlgButton (hDlg, IDC_CREDS_REMIND, (iCreds == g.cCreds) ? FALSE : g.aCreds[iCreds].fRemind);

   EnableWindow (GetDlgItem (hDlg, IDC_CREDS_OBTAIN), IsServiceRunning());
   EnableWindow (GetDlgItem (hDlg, IDC_CREDS_REMIND), (iCreds != g.cCreds));
   EnableWindow (GetDlgItem (hDlg, IDC_CREDS_DESTROY), (iCreds != g.cCreds));
}