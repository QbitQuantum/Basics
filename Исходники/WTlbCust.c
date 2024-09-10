static BOOL 
TlbCustom_OnDrawItem 
(   
    	HWND                hwDlg, 
    	UINT                idCtl, 
    	LPDRAWITEMSTRUCT    lpdi 
) 
{
    	HWND                hwToolbar   = ( HWND )NULL;
    	HGLOBAL             hBtnText    = ( HGLOBAL )NULL;
    	LPSTR               pBtnText    = ( HWND )NULL;

    	int                 ErrorCode   = 0;

	if ( ! ( hwToolbar = GETTLBHANDLE ( hwDlg ) ) )
		ErrorCode = WTLB_ERR_GETWINPROP;
	else
	if ( ! ( hBtnText = GETBTNINFO ( hwDlg ) ) )
		ErrorCode = WTLB_ERR_GETWINPROP;
	else
	if ( ! ( pBtnText = GlobalLock ( hBtnText ) ) )
		ErrorCode = WTLB_ERR_GETWINPROP;
	else
    	if ( SendMessage ( GetDlgItem ( hwDlg, idCtl ), LB_GETCOUNT, 0, 0L ) > 0 )
    	{
    	    Toolbr_DrawDragLBxItem ( hwDlg, hwToolbar, lpdi, pBtnText );
#if 0
	    InvalidateRect ( lpdi->hwndItem, &lpdi->rcItem, TRUE );
	    ValidateRect ( lpdi->hwndItem, &lpdi->rcItem );
#endif
    	    GlobalUnlock ( hBtnText );
    	    return TRUE;
    	}

    	return FALSE;
}