void EPropWnd::SetScrollPage()
{
	CSize PageSize = GetScrollPageSize();

	if( PageSize.cx==0 && PageSize.cy==0 )
	{
		SetScrollPos ( SB_HORZ , 0     );
		SetScrollPos ( SB_VERT , 0     );
		ShowScrollBar( SB_BOTH , FALSE );
	}
	else
	{
		CRect wr;
		GetWindowRect(&wr);
		CSize ClientSize = wr.Size();

		bool bEnableH = false;
		bool bEnableV = false;

		if( PageSize.cx > ClientSize.cx )
		{
			ClientSize.cy -= GetSystemMetrics(SM_CYHSCROLL);
			bEnableH = true;
		}

		if( PageSize.cy > ClientSize.cy )
		{
			ClientSize.cx -= GetSystemMetrics(SM_CXVSCROLL);
			bEnableV = true;

			if( bEnableH == false )
			{
				if( PageSize.cx > ClientSize.cx )
				{
					ClientSize.cy -= GetSystemMetrics(SM_CYHSCROLL);
					bEnableH = true;
				}
			}
		}

		SCROLLINFO si;
		si.cbSize = sizeof(si);
		si.fMask  = SIF_PAGE | SIF_POS | SIF_RANGE;

		if( bEnableH )
		{
			si.nPage  = ClientSize.cx;			//size of scrolltab
			si.nMin   = 0;
			si.nMax   = PageSize.cx-1;
			si.nPos   = GetScrollPos(SB_HORZ);
			ShowScrollBar( SB_HORZ , TRUE );
			SetScrollInfo( SB_HORZ , &si );
		}
		else
		{
			ShowScrollBar( SB_HORZ , FALSE );
			SetScrollPos( SB_HORZ , 0 );
		}

		if( bEnableV )
		{
			si.nPage  = ClientSize.cy;			//size of scrolltab
			si.nMin   = 0;
			si.nMax   = PageSize.cy-1;
			si.nPos   = GetScrollPos(SB_VERT);
			ShowScrollBar( SB_VERT , TRUE );
			SetScrollInfo( SB_VERT , &si );
		}
		else
		{
			ShowScrollBar( SB_VERT , FALSE );
			SetScrollPos( SB_VERT , 0 );
		}

	}
}