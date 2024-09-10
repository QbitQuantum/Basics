static bool win_set_clipboard_text(ALLEGRO_DISPLAY *display, const char *text)
{
   HWND handle = get_window_handle(display);
   HANDLE hMem = NULL;
   wchar_t *tstr = NULL;
   size_t size;
   size_t len;
   LPTSTR dst;

   if (!OpenClipboard(handle)) {
      ALLEGRO_DEBUG("Could not open clipboard for handle %p", handle);
      return false;
   }

   /* Convert the text from UTF-8 to Windows Unicode */
   tstr = _al_win_utf16(text);
   len  = wcslen(tstr);
   size = (len+1) * sizeof(wchar_t);
   /* Save the data to the clipboard */
   hMem = GlobalAlloc(GMEM_MOVEABLE, size);

   if (!hMem) {
      al_free(tstr);
      ALLEGRO_DEBUG("GlobalAlloc failed to allocate memory for the clipboard data");
      return false;
   }

   dst = (LPTSTR)GlobalLock(hMem);
   /* Copy the text over. Unlike SDL, do NOT convert newlines, that's for the
    * use to decide. */
   memmove(dst, tstr, size);
   dst[len] = 0;
   GlobalUnlock(hMem);
   EmptyClipboard();
   if (!SetClipboardData(TEXT_FORMAT, hMem)) {
      al_free(tstr);
      ALLEGRO_DEBUG("Couldn't set clipboard data");
      return false;
   }
   al_free(tstr);
   CloseClipboard();
   return true;
}