static Bool
winBltExposedRegionsShadowGDI (ScreenPtr pScreen)
{
  winScreenPriv(pScreen);
  winScreenInfo		*pScreenInfo = pScreenPriv->pScreenInfo;
  winPrivCmapPtr	pCmapPriv = NULL;
  HDC			hdcUpdate;
  PAINTSTRUCT		ps;

  /* BeginPaint gives us an hdc that clips to the invalidated region */
  hdcUpdate = BeginPaint (pScreenPriv->hwndScreen, &ps);

  /* Realize the palette, if we have one */
  if (pScreenPriv->pcmapInstalled != NULL)
    {
      pCmapPriv = winGetCmapPriv (pScreenPriv->pcmapInstalled);
      
      SelectPalette (hdcUpdate, pCmapPriv->hPalette, FALSE);
      RealizePalette (hdcUpdate);
    }

  /* Our BitBlt will be clipped to the invalidated region */
  BitBlt (hdcUpdate,
	  0, 0,
	  pScreenInfo->dwWidth, pScreenInfo->dwHeight,
	  pScreenPriv->hdcShadow,
	  0, 0,
	  SRCCOPY);

  /* EndPaint frees the DC */
  EndPaint (pScreenPriv->hwndScreen, &ps);

#ifdef XWIN_MULTIWINDOW
  /* Redraw all windows */
  if (pScreenInfo->fMultiWindow)
    EnumThreadWindows(g_dwCurrentThreadID, winRedrawAllProcShadowGDI, 
            (LPARAM)pScreenPriv->hwndScreen);
#endif

  return TRUE;
}