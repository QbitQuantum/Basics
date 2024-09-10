/**************************************************************************
 * SmoothScrollWindow [COMCTL32.382]
 *
 * Lots of magic for smooth scrolling windows.
 *
 * RETURNS
 *     Success: TRUE
 *     Failure: FALSE
 *
 * BUGS
 *     Currently only scrolls ONCE. The comctl32 implementation uses GetTickCount
 *     and what else to do smooth scrolling.
 */
BOOL WINAPI SmoothScrollWindow( const SMOOTHSCROLLSTRUCT *smooth ) {
   LPRECT	lpupdaterect = smooth->lpupdaterect;
   HRGN		hrgnupdate = smooth->hrgnupdate;
   RECT		tmprect;
   DWORD	flags = smooth->flags;

   if (smooth->dwSize!=sizeof(SMOOTHSCROLLSTRUCT))
       return FALSE;

   if (!lpupdaterect)
       lpupdaterect = &tmprect;
   SetRectEmpty(lpupdaterect);

   if (!(flags & 0x40000)) { /* no override, use system wide defaults */
       if (smoothscroll == 2) {
	   HKEY	hkey;

	   smoothscroll = 0;
	   if (!RegOpenKeyA(HKEY_CURRENT_USER,"Control Panel\\Desktop",&hkey)) {
	       DWORD	len = 4;

	       RegQueryValueExA(hkey,"SmoothScroll",0,0,(LPBYTE)&smoothscroll,&len);
	       RegCloseKey(hkey);
	   }
       }
       if (!smoothscroll)
	   flags |= 0x20000;
   }

   if (flags & 0x20000) { /* are we doing jump scrolling? */
       if ((smooth->x2 & 1) && smooth->scrollfun)
	   return smooth->scrollfun(
	       smooth->hwnd,smooth->dx,smooth->dy,smooth->lpscrollrect,
	       smooth->lpcliprect,hrgnupdate,lpupdaterect,
	       flags & 0xffff
	   );
       else
	   return ScrollWindowEx(
	       smooth->hwnd,smooth->dx,smooth->dy,smooth->lpscrollrect,
	       smooth->lpcliprect,hrgnupdate,lpupdaterect,
	       flags & 0xffff
	   );
   }

   FIXME("(hwnd=%p,flags=%x,x2=%x): should smooth scroll here.\n",
	   smooth->hwnd,flags,smooth->x2
   );
   /* FIXME: do timer based smooth scrolling */
   if ((smooth->x2 & 1) && smooth->scrollfun)
       return smooth->scrollfun(
	   smooth->hwnd,smooth->dx,smooth->dy,smooth->lpscrollrect,
	   smooth->lpcliprect,hrgnupdate,lpupdaterect,
	   flags & 0xffff
       );
   else
       return ScrollWindowEx(
	   smooth->hwnd,smooth->dx,smooth->dy,smooth->lpscrollrect,
	   smooth->lpcliprect,hrgnupdate,lpupdaterect,
	   flags & 0xffff
       );
}