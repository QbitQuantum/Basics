static
int
winAddRgn (WindowPtr pWin, pointer data)
{
  int		iX, iY, iWidth, iHeight, iBorder;
  HRGN		hRgn = *(HRGN*)data;
  HRGN		hRgnWin;
  winWindowPriv(pWin);
  
  /* If pWin is not Root */
  if (pWin->parent != NULL) 
    {
#if CYGDEBUG
      ErrorF ("winAddRgn ()\n");
#endif
      if (pWin->mapped)
	{
	  iBorder = wBorderWidth (pWin);
	  
	  iX = pWin->drawable.x - iBorder;
	  iY = pWin->drawable.y - iBorder;
	  
	  iWidth = pWin->drawable.width + iBorder * 2;
	  iHeight = pWin->drawable.height + iBorder * 2;
	  
	  hRgnWin = CreateRectRgn (0, 0, iWidth, iHeight);
	  
	  if (hRgnWin == NULL)
	    {
	      ErrorF ("winAddRgn - CreateRectRgn () failed\n");
	      ErrorF ("  Rect %d %d %d %d\n",
		      iX, iY, iX + iWidth, iY + iHeight);
	    }
	  
	  if (pWinPriv->hRgn)
	    {
	      if (CombineRgn (hRgnWin, hRgnWin, pWinPriv->hRgn, RGN_AND)
		  == ERROR)
		{
		  ErrorF ("winAddRgn - CombineRgn () failed\n");
		}
	    }
	  
	  OffsetRgn (hRgnWin, iX, iY);

	  if (CombineRgn (hRgn, hRgn, hRgnWin, RGN_OR) == ERROR)
	    {
	      ErrorF ("winAddRgn - CombineRgn () failed\n");
	    }
	  
	  DeleteObject (hRgnWin);
	}
      return WT_DONTWALKCHILDREN;
    }
  else
    {
      return WT_WALKCHILDREN;
    }
}