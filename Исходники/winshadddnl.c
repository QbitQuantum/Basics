void
winShadowUpdateDDNL (ScreenPtr pScreen, 
		     shadowBufPtr pBuf)
{
  winScreenPriv(pScreen);
  winScreenInfo		*pScreenInfo = pScreenPriv->pScreenInfo;
  RegionPtr		damage = &pBuf->damage;
  HRESULT		ddrval = DD_OK;
  RECT			rcDest, rcSrc;
  POINT			ptOrigin;
  DWORD			dwBox = REGION_NUM_RECTS (damage);
  BoxPtr		pBox = REGION_RECTS (damage);
  HRGN			hrgnTemp = NULL, hrgnCombined = NULL;

  /*
   * Return immediately if the app is not active
   * and we are fullscreen, or if we have a bad display depth
   */
  if ((!pScreenPriv->fActive && pScreenInfo->fFullScreen)
      || pScreenPriv->fBadDepth) return;

  /* Get the origin of the window in the screen coords */
  ptOrigin.x = pScreenInfo->dwXOffset;
  ptOrigin.y = pScreenInfo->dwYOffset;
  MapWindowPoints (pScreenPriv->hwndScreen,
		   HWND_DESKTOP,
		   (LPPOINT)&ptOrigin, 1);

  /*
   * Handle small regions with multiple blits,
   * handle large regions by creating a clipping region and 
   * doing a single blit constrained to that clipping region.
   */
  if (pScreenInfo->dwClipUpdatesNBoxes == 0
      || dwBox < pScreenInfo->dwClipUpdatesNBoxes)
    {
      /* Loop through all boxes in the damaged region */
      while (dwBox--)
	{
	  /* Assign damage box to source rectangle */
	  rcSrc.left = pBox->x1;
	  rcSrc.top = pBox->y1;
	  rcSrc.right = pBox->x2;
	  rcSrc.bottom = pBox->y2;
	  
	  /* Calculate destination rectangle */
	  rcDest.left = ptOrigin.x + rcSrc.left;
	  rcDest.top = ptOrigin.y + rcSrc.top;
	  rcDest.right = ptOrigin.x + rcSrc.right;
	  rcDest.bottom = ptOrigin.y + rcSrc.bottom;
	  
	  /* Blit the damaged areas */
	  ddrval = IDirectDrawSurface4_Blt (pScreenPriv->pddsPrimary4,
					    &rcDest,
					    pScreenPriv->pddsShadow4,
					    &rcSrc,
					    DDBLT_WAIT,
					    NULL);
	  if (FAILED (ddrval))
	    {
	      ErrorF ("winShadowUpdateDDNL - IDirectDrawSurface4_Blt () "
		      "failed: %08x\n",
		      ddrval);
	    }
	  
	  /* Get a pointer to the next box */
	  ++pBox;
	}
    }
  else
    {
      BoxPtr		pBoxExtents = REGION_EXTENTS (pScreen, damage);

      /* Compute a GDI region from the damaged region */
      hrgnCombined = CreateRectRgn (pBox->x1, pBox->y1, pBox->x2, pBox->y2);
      dwBox--;
      pBox++;
      while (dwBox--)
	{
	  hrgnTemp = CreateRectRgn (pBox->x1, pBox->y1, pBox->x2, pBox->y2);
	  CombineRgn (hrgnCombined, hrgnCombined, hrgnTemp, RGN_OR);
	  DeleteObject (hrgnTemp);
	  pBox++;
	}

      /* Install the GDI region as a clipping region */
      SelectClipRgn (pScreenPriv->hdcScreen, hrgnCombined);
      DeleteObject (hrgnCombined);
      hrgnCombined = NULL;

#if CYGDEBUG
      ErrorF ("winShadowUpdateDDNL - be x1 %d y1 %d x2 %d y2 %d\n",
	      pBoxExtents->x1, pBoxExtents->y1,
	      pBoxExtents->x2, pBoxExtents->y2);
#endif

      /* Calculating a bounding box for the source is easy */
      rcSrc.left = pBoxExtents->x1;
      rcSrc.top = pBoxExtents->y1;
      rcSrc.right = pBoxExtents->x2;
      rcSrc.bottom = pBoxExtents->y2;

      /* Calculating a bounding box for the destination is trickier */
      rcDest.left = ptOrigin.x + rcSrc.left;
      rcDest.top = ptOrigin.y + rcSrc.top;
      rcDest.right = ptOrigin.x + rcSrc.right;
      rcDest.bottom = ptOrigin.y + rcSrc.bottom;

      /* Our Blt should be clipped to the invalidated region */
      ddrval = IDirectDrawSurface4_Blt (pScreenPriv->pddsPrimary4,
					&rcDest,
					pScreenPriv->pddsShadow4,
					&rcSrc,
					DDBLT_WAIT,
					NULL);

      /* Reset the clip region */
      SelectClipRgn (pScreenPriv->hdcScreen, NULL);
    }
}