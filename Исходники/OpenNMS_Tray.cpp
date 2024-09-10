//---------------------------------------------------------------------------------------
int DisplayMenu(HWND hWnd)
{
   int nID = 0;
   HMENU hMenu = CreatePopupMenu();

   if(hMenu)
   {
      HMODULE hMod = GetResourceHandle();

      if(hMod)
      {
         TCHAR szBuf[MAX_PATH] = _T("");
         LoadString(hMod, IDS_MNU_LAUNCH, szBuf, MAX_PATH);
         AppendMenu(hMenu, MF_STRING, 1, szBuf);

         if(IsServiceRunning())
         {
            LoadString(hMod, IDS_MNU_STOP, szBuf, MAX_PATH);
            AppendMenu(hMenu, MF_STRING, 2, szBuf);
         }
         else
         {
            LoadString(hMod, IDS_MNU_START, szBuf, MAX_PATH);
            AppendMenu(hMenu, MF_STRING, 2, szBuf);
         }

         LoadString(hMod, IDS_MNU_ABOUT, szBuf, MAX_PATH);
         AppendMenu(hMenu, MF_STRING, 3, szBuf);

         AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);

         LoadString(hMod, IDS_MNU_EXIT, szBuf, MAX_PATH);
         AppendMenu(hMenu, MF_STRING, 4, szBuf);

         FreeResourceHandle(hMod);
      }

      POINT pt = {0};
      GetCursorPos (&pt);

      SetMenuDefaultItem(hMenu, 0, TRUE);
      nID = TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, NULL);
      DestroyMenu(hMenu);
   }

   return nID;
}