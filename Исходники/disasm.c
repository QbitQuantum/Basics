LRESULT DisasmCtl_OnPaint(DisasmCtl_struct *cc, WPARAM wParam, LPARAM lParam)
{
   HDC hdc=(HDC)wParam;
   PAINTSTRUCT ps;
   RECT rect;
   HANDLE oldfont;
   int x=0, y=0;
   char text[MAX_PATH];
   u32 addr;
   SIZE size;
   RECT clip;
   int curaddr=-1;
   BOOL ispc;

   addr = cc->addr;

   // Setup everything for rendering
   if (hdc == NULL)
      hdc = BeginPaint(cc->hwnd, &ps);
   oldfont = SelectObject(hdc, cc->font);

   GetClientRect(cc->hwnd, &rect);

   for(;;)
   {
      ispc = (addr == cc->pc) ? TRUE : FALSE;
      x = 0;
      addr += cc->disinst(addr, text);
      GetTextExtentPoint32A(hdc, text, (int)strlen(text), &size);
      if (size.cy+y >= rect.bottom)
         break;

      // adjust clipping values
      if (y+(size.cy*2) >= rect.bottom)
         clip.bottom = rect.bottom;
      else
         clip.bottom = y+size.cy;

      // Draw the address text
      clip.left = x;
      clip.top = y;
      clip.right = rect.right;
      if (ispc)
      {
         SetTextColor(hdc, GetSysColor(COLOR_HIGHLIGHTTEXT));
         SetBkColor(hdc, GetSysColor(COLOR_HIGHLIGHT));
      }
      else
      {
         SetTextColor(hdc, cc->text_color);
         SetBkColor(hdc, cc->bg_color);
      }
      ExtTextOutA(hdc, x, y, ETO_OPAQUE | ETO_CLIPPED, &clip, text, strlen(text), 0);
      y += size.cy;
   }

   // Let's clean up, and we're done
   SelectObject(hdc, oldfont);

   if ((HDC)wParam == NULL)
      EndPaint(cc->hwnd, &ps);

   return FALSE;
}