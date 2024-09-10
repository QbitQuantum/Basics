BOOL CALLBACK EnumerateCallback(HWND window, LPARAM lParam)
{
   HICON hIcon;

   UNREFERENCED_PARAMETER(lParam);

   if (!IsWindowVisible(window))
            return TRUE;

   GetClassNameW(window,windowText,4095);
   if ((wcscmp(L"Shell_TrayWnd",windowText)==0) ||
       (wcscmp(L"Progman",windowText)==0) )
            return TRUE;
      
   // First try to get the big icon assigned to the window
   hIcon = (HICON)SendMessageW(window, WM_GETICON, ICON_BIG, 0);
   if (!hIcon)
   {
      // If no icon is assigned, try to get the icon assigned to the windows' class
      hIcon = (HICON)GetClassLongPtrW(window, GCL_HICON);
      if (!hIcon)
      {
         // If we still don't have an icon, see if we can do with the small icon,
         // or a default application icon
         hIcon = (HICON)SendMessageW(window, WM_GETICON, ICON_SMALL2, 0);
         if (!hIcon)
         {
            // If all fails, give up and continue with the next window
            return TRUE;
         }
      }
   }

   windowList[windowCount] = window;
   iconList[windowCount] = CopyIcon(hIcon);

   windowCount++;

   // If we got to the max number of windows,
   // we won't be able to add any more
   if(windowCount == MAX_WINDOWS)
      return FALSE;

   return TRUE;
}