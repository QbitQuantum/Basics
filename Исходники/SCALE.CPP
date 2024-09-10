void SCALE::DoVscroll (HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	int nVscrollInc ;

	switch (wParam)
 		{
		case SB_TOP:
    		nVscrollInc = -nVscrollPos ;
        break ;

    case SB_BOTTOM:
        nVscrollInc = nVscrollMax - nVscrollPos ;
        break ;

    case SB_LINEUP:
				nVscrollInc = -5 ;
        break ;

    case SB_LINEDOWN:
				nVscrollInc = 5 ;
        break ;

    case SB_PAGEUP:
				nVscrollInc = min (-5, -nVscrollMax ) ;
				break ;

    case SB_PAGEDOWN:
				nVscrollInc = max (5, nVscrollMax ) ; 
        break ;

    case SB_THUMBTRACK:
        nVscrollInc = LOWORD (lParam) - nVscrollPos ;
        break ;

    default:
        nVscrollInc = 0 ;
		}
	nVscrollInc = max (-nVscrollPos,
								min (nVscrollInc, nVscrollMax - nVscrollPos)) ;
	if (nVscrollInc)
  	{
		nVscrollPos += nVscrollInc ;
		nVfirstPixel +=nVscrollInc ;
		ScrollWindow (hwnd, 0, -nVscrollInc, NULL, NULL) ;
    SetScrollPos (hwnd, SB_VERT, nVscrollPos, TRUE) ;
		UpdateWindow (hwnd) ;
		}
}