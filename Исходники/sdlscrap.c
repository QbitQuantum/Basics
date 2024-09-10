PUBLIC void
put_scrap(int type, int srclen, char *src)
{
  scrap_type format;
  int dstlen;
  char *dst;

  format = convert_format(type);
  dstlen = convert_data(type, NULL, src, srclen);

#if defined(X11_SCRAP)
/* * */
  dst = (char *)alloca(dstlen);
  if ( dst != NULL )
    {
      convert_data(type, dst, src, srclen);
      XChangeProperty(SDL_Display, DefaultRootWindow(SDL_Display),
		      XA_CUT_BUFFER0, format, 8, PropModeReplace,
		      (unsigned char *) dst, dstlen);
      if ( we_lost_clipboard() )
        XSetSelectionOwner(SDL_Display, XA_PRIMARY, SDL_Window, CurrentTime);
    }

#elif defined(WIN_SCRAP)
/* * */
  if ( OpenClipboard(SDL_Window) )
    {
      HANDLE hMem;

      hMem = GlobalAlloc((GMEM_MOVEABLE|GMEM_DDESHARE), dstlen);
      if ( hMem != NULL )
        {
          dst = (char *)GlobalLock(hMem);
          convert_data(type, dst, src, srclen);
          GlobalUnlock(hMem);
          EmptyClipboard();
          SetClipboardData(format, hMem);
        }
      CloseClipboard();
    }

#endif /* scrap type */
}