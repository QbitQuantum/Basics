LONG WINAPI FaderWndProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
/////////////////////////////////////////////////////////////////////////////
{
	PAINTSTRUCT	ps;
	PFADERINFO	pFI			= (PFADERINFO)GetWindowLong( hWnd, GWL_USERDATA );
	HWND		hParentWnd	= GetParent( hWnd );
	
	switch( iMessage ) 
	{
	case WM_GETDLGCODE:
		return( DLGC_WANTARROWS );

	case WM_SETFOCUS:
		if( pFI )
		{
			CreateCaret( hWnd, (HBITMAP)1, pFI->bmFader.bmWidth - 5, pFI->bmFader.bmHeight - CARET_OFFSET );
			SetCaretPos( pFI->nBitmapX + 2, pFI->nBitmapPos + (CARET_OFFSET/2) );
			ShowCaret( hWnd );
			pFI->bHasFocus = TRUE;
		}
		break;
		
	case WM_KILLFOCUS:
		if( pFI )
			pFI->bHasFocus = FALSE;
		HideCaret( hWnd );
		DestroyCaret();
		break;
		
	case WM_APPCOMMAND:
		switch( GET_APPCOMMAND_LPARAM(lParam) )
		{
		case APPCOMMAND_VOLUME_MUTE:
			PostMessage( hParentWnd, WM_VSCROLL, (WPARAM)SB_BOTTOM, (LPARAM)hWnd );
			return( TRUE );
		case APPCOMMAND_VOLUME_UP:
			PostMessage( hParentWnd, WM_VSCROLL, (WPARAM)SB_LINEUP, (LPARAM)hWnd );
			return( TRUE );
		case APPCOMMAND_VOLUME_DOWN:
			PostMessage( hParentWnd, WM_VSCROLL, (WPARAM)SB_LINEDOWN, (LPARAM)hWnd );
			return( TRUE );
		default:
			return( DefWindowProc( hWnd, iMessage, wParam, lParam ) );
		}
		break;

	case WM_KEYDOWN:		/* Keyboard Interface for Fader */
		switch( wParam ) 
		{
		case VK_TAB:
			// pass this on to the parent
			//PostMessage( hParentWnd, iMessage, wParam, lParam );
			break;

		case VK_RIGHT:
		case VK_DOWN:
			PostMessage( hParentWnd, WM_VSCROLL, (WPARAM)SB_LINEDOWN, (LPARAM)hWnd );
			break;
			
		case VK_LEFT:
		case VK_UP:
			PostMessage( hParentWnd, WM_VSCROLL, (WPARAM)SB_LINEUP, (LPARAM)hWnd );
			break;
			
		case VK_PRIOR:
			PostMessage( hParentWnd, WM_VSCROLL, (WPARAM)SB_PAGEUP, (LPARAM)hWnd );
			break;
			
		case VK_NEXT:
			PostMessage( hParentWnd, WM_VSCROLL, (WPARAM)SB_PAGEDOWN, (LPARAM)hWnd );
			break;
			
		case VK_HOME:
			PostMessage( hParentWnd, WM_VSCROLL, (WPARAM)SB_TOP, (LPARAM)hWnd );
			break;
			
		case VK_END:
			PostMessage( hParentWnd, WM_VSCROLL, (WPARAM)SB_BOTTOM, (LPARAM)hWnd );
			break;
			
		}
		break;
		
	case WM_LBUTTONUP:
		ReleaseCapture();
		if( pFI )
		{
			// we know this control has the focus
			SetCaretPos( pFI->nBitmapX + 2, pFI->nBitmapPos + (CARET_OFFSET/2) );
			ShowCaret( hWnd );
			pFI->bMouseDown = FALSE;
		}
		break;
		
	case WM_LBUTTONDOWN:
		SetFocus( hWnd );
		SetCapture( hWnd );
		HideCaret( hWnd );
		if( pFI )
		{
			pFI->bMouseDown = TRUE;		/* Fall Through */
		}
		
	case WM_MOUSEMOVE:
		//fwKeys = wParam;        // key flags 
		//xPos = LOWORD(lParam);  // horizontal position of cursor 
		//yPos = HIWORD(lParam);  // vertical position of cursor (zero at the top)

		if( pFI )
		{
			if( pFI->bMouseDown )
			{
				short	X = LOWORD( lParam );
				short	Y = HIWORD( lParam );
				WORD	wPos;
				int		nScale = pFI->nWindowY - pFI->bmFader.bmHeight;

				// make sure we don't go out of bounds
				if( Y > (pFI->nWindowY - (pFI->bmFader.bmHeight/2)) )
					Y = (pFI->nWindowY - (pFI->bmFader.bmHeight/2));
				
				if( Y < (pFI->bmFader.bmHeight/2) )
					Y = (pFI->bmFader.bmHeight/2);

				Y	-= (pFI->bmFader.bmHeight/2);

				if( Y > nScale )
					Y = nScale;

				wPos = pFI->nMax - (((int)Y * pFI->nMax) / nScale);

				PostMessage( hParentWnd, WM_VSCROLL, MAKELONG( SB_THUMBTRACK, wPos ), (LPARAM)hWnd );
			}
		}
		break;

	case WM_MOUSEWHEEL:
		{
		short	fwKeys = LOWORD( wParam );
		short	nZDelta = HIWORD( wParam );
		short	nX = LOWORD( lParam );
		short	nY = HIWORD( lParam );
		POINT	Point;
		HWND	hParent;
//		long	CntlID;

		// what window is the mouse currently above?

		Point.x = nX;
		Point.y = nY;

		hWnd = WindowFromPoint( Point );

		hParent = GetParent( hWnd );

		// if the parent of this window is not our parent, we are done
		if( hParent != hParentWnd )
			return( 0L );
		
		// is this one of our fader windows?
/***********
		CntlID = GetWindowLong( hWnd, GWL_ID );
		switch( CntlID )
		{
		case IDC_OUT1_VOLUME:
		case IDC_OUT2_VOLUME:
		case IDC_OUT3_VOLUME:
		case IDC_OUT4_VOLUME:
			break;
		default:
			return( 0L );
		}
***********/

		SetFocus( hWnd );
		HideCaret( hWnd );

		//sprintf( szBuffer, "fwKeys [%d] nZ [%d] nX [%d] nY [%d]", fwKeys, nZDelta, nX, nY );
		//SetDlgItemText( GetParent( hWnd ), IDC_STATUS, szBuffer );

		if( nZDelta > 0 )
			PostMessage( hParentWnd, WM_VSCROLL, (WPARAM)SB_LINEUP, (LPARAM)hWnd );
		else
			PostMessage( hParentWnd, WM_VSCROLL, (WPARAM)SB_LINEDOWN, (LPARAM)hWnd );
		}
		break;
		
	case WM_SIZE:
		if( pFI )
		{
			pFI->nWindowX = LOWORD( lParam );
			pFI->nWindowY = HIWORD( lParam );
			// Place the Knob at the top of the control
			pFI->nBitmapPos = pFI->nWindowY - pFI->bmFader.bmHeight - 2;
			pFI->nBitmapX = (pFI->nWindowX / 2) - (pFI->bmFader.bmWidth / 2);
		}
		break;
		
	case WM_CREATE:
		pFI = (PFADERINFO)malloc( sizeof( FADERINFO ) );
		SetWindowLong( hWnd, GWL_USERDATA, (DWORD)pFI );
		if( !pFI )
		{
			MessageBox( NULL, TEXT("Fader: malloc failed!"), TEXT("LynxONE Mixer"), MB_OK | MB_ICONSTOP | MB_TASKMODAL );
			break;
		}
		ZeroMemory( pFI, sizeof( FADERINFO ) );
		pFI->hFader = LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDB_FADER ) );
		pFI->hGradient = LoadBitmap( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDB_GRADIENT ) );
		GetObject( pFI->hFader, sizeof( BITMAP ), (LPSTR)&pFI->bmFader );
		GetObject( pFI->hGradient, sizeof( BITMAP ), (LPSTR)&pFI->bmGradient );
		break;
		
	case WM_DESTROY:
		if( pFI )
		{
			DeleteObject( pFI->hFader );
			DeleteObject( pFI->hGradient );
			free( pFI );
		}
		SetWindowLong( hWnd, GWL_USERDATA, (DWORD)0 );
		break;
		
	case WM_PAINT:
		BeginPaint( hWnd, (LPPAINTSTRUCT)&ps );
		if( pFI )
			PaintControl( ps.hdc, pFI );
		EndPaint( hWnd, (LPPAINTSTRUCT)&ps );
		break;
		
	default:
		return( DefWindowProc( hWnd, iMessage, wParam, lParam ) );
	}
	return( 0L );
}