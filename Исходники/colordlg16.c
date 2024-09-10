/***********************************************************************
 *                              CC_WMCommand16                  [internal]
 */
static LRESULT CC_WMCommand16( HWND hDlg, WPARAM wParam, LPARAM lParam, WORD notifyCode, HWND hwndCtl )
{
    int  r, g, b, i, xx;
    UINT cokmsg;
    HDC hdc;
    COLORREF *cr;
    LCCPRIV lpp = (LCCPRIV)GetWindowLongPtrW(hDlg, DWLP_USER);
    TRACE("CC_WMCommand wParam=%lx lParam=%lx\n", wParam, lParam);
    switch (wParam)
    {
          case 0x2c2:  /* edit notify RGB */
	  case 0x2c3:
	  case 0x2c4:
	       if (notifyCode == EN_UPDATE && !lpp->updating)
			 {
			   i = CC_CheckDigitsInEdit(hwndCtl, 255);
			   r = GetRValue(lpp->lpcc->rgbResult);
			   g = GetGValue(lpp->lpcc->rgbResult);
			   b= GetBValue(lpp->lpcc->rgbResult);
			   xx = 0;
			   switch (wParam)
			   {
			    case 0x2c2: if ((xx = (i != r))) r = i; break;
			    case 0x2c3: if ((xx = (i != g))) g = i; break;
			    case 0x2c4: if ((xx = (i != b))) b = i; break;
			   }
			   if (xx) /* something has changed */
			   {
			    lpp->lpcc->rgbResult = RGB(r, g, b);
			    CC_PaintSelectedColor(hDlg, lpp->lpcc->rgbResult);
			    lpp->h = CC_RGBtoHSL('H', r, g, b);
			    lpp->s = CC_RGBtoHSL('S', r, g, b);
			    lpp->l = CC_RGBtoHSL('L', r, g, b);
			    CC_EditSetHSL(hDlg, lpp->h, lpp->s, lpp->l);
			    CC_PaintCross(hDlg, lpp->h, lpp->s);
			    CC_PaintTriangle(hDlg, lpp->l);
			   }
			 }
		 break;

	  case 0x2bf:  /* edit notify HSL */
	  case 0x2c0:
	  case 0x2c1:
	       if (notifyCode == EN_UPDATE && !lpp->updating)
			 {
			   i = CC_CheckDigitsInEdit(hwndCtl , wParam == 0x2bf ? 239:240);
			   xx = 0;
			   switch (wParam)
			   {
			    case 0x2bf: if ((xx = ( i != lpp->h))) lpp->h = i; break;
			    case 0x2c0: if ((xx = ( i != lpp->s))) lpp->s = i; break;
			    case 0x2c1: if ((xx = ( i != lpp->l))) lpp->l = i; break;
			   }
			   if (xx) /* something has changed */
			   {
			    r = CC_HSLtoRGB('R', lpp->h, lpp->s, lpp->l);
			    g = CC_HSLtoRGB('G', lpp->h, lpp->s, lpp->l);
			    b = CC_HSLtoRGB('B', lpp->h, lpp->s, lpp->l);
			    lpp->lpcc->rgbResult = RGB(r, g, b);
			    CC_PaintSelectedColor(hDlg, lpp->lpcc->rgbResult);
			    CC_EditSetRGB(hDlg, lpp->lpcc->rgbResult);
			    CC_PaintCross(hDlg, lpp->h, lpp->s);
			    CC_PaintTriangle(hDlg, lpp->l);
			   }
			 }
	       break;

          case 0x2cf:
               CC_SwitchToFullSize(hDlg, lpp->lpcc->rgbResult, &lpp->fullsize);
	       SetFocus( GetDlgItem(hDlg, 0x2bf));
	       break;

          case 0x2c8:    /* add colors ... column by column */
               cr = lpp->lpcc->lpCustColors;
               cr[(lpp->nextuserdef % 2) * 8 + lpp->nextuserdef / 2] = lpp->lpcc->rgbResult;
               if (++lpp->nextuserdef == 16)
		   lpp->nextuserdef = 0;
	       CC_PaintUserColorArray(hDlg, 2, 8, lpp->lpcc->lpCustColors);
	       break;

          case 0x2c9:              /* resulting color */
	       hdc = GetDC(hDlg);
	       lpp->lpcc->rgbResult = GetNearestColor(hdc, lpp->lpcc->rgbResult);
	       ReleaseDC(hDlg, hdc);
	       CC_EditSetRGB(hDlg, lpp->lpcc->rgbResult);
	       CC_PaintSelectedColor(hDlg, lpp->lpcc->rgbResult);
	       r = GetRValue(lpp->lpcc->rgbResult);
	       g = GetGValue(lpp->lpcc->rgbResult);
	       b = GetBValue(lpp->lpcc->rgbResult);
	       lpp->h = CC_RGBtoHSL('H', r, g, b);
	       lpp->s = CC_RGBtoHSL('S', r, g, b);
	       lpp->l = CC_RGBtoHSL('L', r, g, b);
	       CC_EditSetHSL(hDlg, lpp->h, lpp->s, lpp->l);
	       CC_PaintCross(hDlg, lpp->h, lpp->s);
	       CC_PaintTriangle(hDlg, lpp->l);
	       break;

	  case 0x40e:           /* Help! */ /* The Beatles, 1965  ;-) */
	       i = RegisterWindowMessageA(HELPMSGSTRINGA);
               if (lpp->lpcc16)
               {
                   if (lpp->lpcc->hwndOwner)
		       SendMessageA(lpp->lpcc->hwndOwner, i, 0, (LPARAM)lpp->lpcc16);
                   if ( CC_HookCallChk(lpp->lpcc))
		       CallWindowProc16( (WNDPROC16) lpp->lpcc16->lpfnHook,
					 HWND_16(hDlg), WM_COMMAND, psh15,
					 (LPARAM)lpp->lpcc16);
               }
	       break;

          case IDOK :
		cokmsg = RegisterWindowMessageA(COLOROKSTRINGA);
                if (lpp->lpcc16)
                {
		    if (lpp->lpcc->hwndOwner)
			if (SendMessageA(lpp->lpcc->hwndOwner, cokmsg, 0, (LPARAM)lpp->lpcc16))
			   break;    /* do NOT close */
                }
                if (lpp->lpcc16)
                {
                    BYTE *ptr = MapSL(lpp->lpcc16->lpCustColors);
                    memcpy(ptr, lpp->lpcc->lpCustColors, sizeof(COLORREF)*16);
                    lpp->lpcc16->rgbResult = lpp->lpcc->rgbResult;
                }
		EndDialog(hDlg, 1) ;
		return TRUE ;

	  case IDCANCEL :
		EndDialog(hDlg, 0) ;
		return TRUE ;

       }
       return FALSE;
}