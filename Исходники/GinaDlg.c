BOOL 
CALLBACK 
MyWlxLoggedOutSASDlgProc (HWND   hwndDlg,  // handle to dialog box
                          UINT   uMsg,     // message  
                          WPARAM wParam,   // first message parameter
                          LPARAM lParam)   // second message parameter
{
   BOOL bResult;
   
   //
   // Sanity check.
   //
   assert(pfWlxLoggedOutSASDlgProc != NULL);
   
   //
   // Pass on to MSGINA first.
   //
   bResult = pfWlxLoggedOutSASDlgProc(hwndDlg, uMsg, wParam, lParam);

   //
   // We are only interested in WM_INITDIALOG message.
   //
   if (uMsg == WM_INITDIALOG)
   {
      DWORD dwIndex;
      HWND hwndDomain;
      NET_API_STATUS netstatus;
      LPWKSTA_INFO_100 lpWkstaInfo;

      //
      // Get local machine name.
      //
      netstatus = NetWkstaGetInfo(NULL, 100, (LPBYTE *) &lpWkstaInfo);
      if (netstatus != NERR_Success)
      {
         return bResult;
      }            

      //
      // Convert to ANSI.
      //
      wcstombs(g_szLocalMachineName, lpWkstaInfo->wki100_computername, 
               sizeof(g_szLocalMachineName));

      //
      // and free the buffer.
      //
      NetApiBufferFree((LPVOID) lpWkstaInfo);

      //
      // Manipulate the domain combo box so that only some predetermined
      // trusted domains are included in the list.
      //
      // In our case, we restrict logon to local machine only.
      //
      hwndDomain = GetDlgItem(hwndDlg, IDC_WLXLOGGEDOUTSAS_DOMAIN);
      if (hwndDomain == NULL)
      {
         return bResult;
      }

      dwIndex = (DWORD) SendMessage(hwndDomain, CB_FINDSTRING, 
                                    0, (LPARAM) g_szLocalMachineName);
      if (dwIndex != CB_ERR)
      {
         SendMessage(hwndDomain, CB_SETCURSEL, (WPARAM) dwIndex, 0);
         EnableWindow(hwndDomain, FALSE);
      }
   }

   return bResult;
}