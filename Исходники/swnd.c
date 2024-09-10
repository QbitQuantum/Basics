LRESULT CALLBACK searchInputProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
const char *txt;

  if (msg == WM_GETDLGCODE) return DLGC_WANTALLKEYS;
  switch (msg)  {
    case WM_KEYDOWN:
      switch (wParam)  {
        case VK_RETURN:
          //Do your stuff
          on_search_click ();
          return 0;
          break;  //or return 0; if you don't want to pass it further to def proc
                  //If not your key, skip to default:
        case VK_DOWN:
          txt = recent_current_decrement ();
          Edit_SetText (wnd, txt);
          Edit_SetSel (wnd, 0, -1);
          return 0;
          break;
        case VK_UP:
          txt = recent_current_increment ();
          Edit_SetText (wnd, txt);
          Edit_SetSel (wnd, 0, -1);
          return 0;
          break;
        case VK_TAB:
          SetFocus (GetNextDlgTabItem(hMainWindow, wnd, GetAsyncKeyState(VK_SHIFT) & 0x8000 ? TRUE : FALSE));
          return 0;
        default:
          return CallWindowProc(oldsearchInputProc, wnd, msg, wParam, lParam);
      }
    default:
      //printf ("msg = 0x%X %X %X\n", msg, wParam, lParam);
      return CallWindowProc(oldsearchInputProc, wnd, msg, wParam, lParam);
   }
   return 0;
}