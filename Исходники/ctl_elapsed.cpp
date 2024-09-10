HRESULT CALLBACK ElapsedProc (HWND hElapsed, UINT msg, WPARAM wp, LPARAM lp)
{
   ElapsedInfo *pei = NULL;

   EnterCriticalSection (&csElapsed);

   if (msg == WM_CREATE)
      {
      size_t iElapsed;
      for (iElapsed = 0; iElapsed < cElapsed; ++iElapsed)
         {
         if (aElapsed[ iElapsed ].hElapsed == NULL)
            break;
         }
      if (iElapsed >= cElapsed)
         {
         if (!REALLOC (aElapsed, cElapsed, 1+iElapsed, 4))
            return FALSE;
         }

      memset (&aElapsed[ iElapsed ], 0x00, sizeof(ElapsedInfo));
      aElapsed[ iElapsed ].hElapsed = hElapsed;

      pei = &aElapsed[ iElapsed ];
      }
   else
      {
      for (size_t iElapsed = 0; !pei && iElapsed < cElapsed; ++iElapsed)
         {
         if (aElapsed[ iElapsed ].hElapsed == hElapsed)
            pei = &aElapsed[ iElapsed ];
         }
      }

   LeaveCriticalSection (&csElapsed);

   if (pei != NULL)
      {
      switch (msg)
         {
         case WM_CREATE:
            Elapsed_OnCreate (pei);
            break;

         case WM_DESTROY:
            Elapsed_OnDestroy (pei);
            break;

         case WM_RBUTTONDOWN:
         case WM_LBUTTONDOWN:
            Elapsed_OnButtonDown (pei, msg, wp, lp);
            break;

         case WM_SETFOCUS:
            PostMessage (GetParent(hElapsed), WM_NEXTDLGCTL, (WPARAM)pei->hHours, TRUE);
            break;

         case WM_ENABLE:
            EnableWindow (pei->hHours,   IsWindowEnabled (hElapsed));
            EnableWindow (pei->hSep1,    IsWindowEnabled (hElapsed));
            EnableWindow (pei->hMinutes, IsWindowEnabled (hElapsed));
            EnableWindow (pei->hSep2,    IsWindowEnabled (hElapsed));
            EnableWindow (pei->hSeconds, IsWindowEnabled (hElapsed));
            EnableWindow (pei->hSpinner, IsWindowEnabled (hElapsed));

            RECT rElapsed;
            GetRectInParent (hElapsed, &rElapsed);
            InvalidateRect (GetParent(hElapsed), &rElapsed, TRUE);
            UpdateWindow (GetParent(hElapsed));
            break;

         case WM_SYSCHAR:
         case WM_CHAR:
            switch (wp)
               {
               case VK_UP:
                  PostMessage (GetParent(pei->hSpinner), WM_VSCROLL, SB_LINEUP, (LPARAM)pei->hSpinner);
                  break;

               case VK_DOWN:
                  PostMessage (GetParent(pei->hSpinner), WM_VSCROLL, SB_LINEDOWN, (LPARAM)pei->hSpinner);
                  break;

               case VK_PRIOR:
                  PostMessage (GetParent(pei->hSpinner), WM_VSCROLL, SB_PAGEUP, (LPARAM)pei->hSpinner);
                  break;

               case VK_NEXT:
                  PostMessage (GetParent(pei->hSpinner), WM_VSCROLL, SB_PAGEDOWN, (LPARAM)pei->hSpinner);
                  break;

               case VK_HOME:
                  PostMessage (GetParent(pei->hSpinner), WM_VSCROLL, SB_TOP, (LPARAM)pei->hSpinner);
                  break;

               case VK_END:
                  PostMessage (GetParent(pei->hSpinner), WM_VSCROLL, SB_BOTTOM, (LPARAM)pei->hSpinner);
                  break;
               }
            break;

         case ELM_GETRANGE:
            return Elapsed_OnGetRange (pei, wp, lp);

         case ELM_SETRANGE:
            return Elapsed_OnSetRange (pei, wp, lp);

         case ELM_GETTIME:
            return Elapsed_OnGetTime (pei, wp, lp);

         case ELM_SETTIME:
            return Elapsed_OnSetTime (pei, wp, lp);
         }
      }

   return DefWindowProc (hElapsed, msg, wp, lp);
}