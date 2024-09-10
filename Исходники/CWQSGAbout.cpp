static inline INT_PTR CALLBACK AboutFunc(HWND a_hDlg, UINT a_message, WPARAM a_wParam, LPARAM a_lParam)
{
	switch (a_message)
	{
	case WM_INITDIALOG:
		SendMessage( a_hDlg , WM_SETICON , TRUE , (LPARAM)g_hIcon );
		SendMessage( a_hDlg , WM_SETICON , FALSE , (LPARAM)g_hIcon );

		SetWindowText( a_hDlg , g_pTitle );

		SendMessage( GetDlgItem( a_hDlg , s_ids.m_nIcon ) , STM_SETICON, (WPARAM)g_hIcon , 0L);
		SetDlgItemText( a_hDlg , s_ids.m_nAppName , g_pAppName );

		SetDlgItemText( a_hDlg , s_ids.m_nLink , g_pUrl );

		SetDlgItemText( a_hDlg , s_ids.m_nEdit , g_pProgrammed );

		{
			RECT rcTmp = {};

			GetWindowRect( a_hDlg , &rcTmp );
			RECT rcMain1 = rcTmp;

			GetClientRect( a_hDlg , &rcTmp );

			SIZE szClientSize = { rcTmp.right , rcTmp.bottom };

			const SIZE szMainB = {
				(rcMain1.right - rcMain1.left) - rcTmp.right,
				(rcMain1.bottom - rcMain1.top) - rcTmp.bottom
			};
			//-----------------------------------------
			CWndSize wIcon( GetDlgItem( a_hDlg , s_ids.m_nIcon ) );
			CWndSize wAppName( GetDlgItem( a_hDlg , s_ids.m_nAppName ) );
			CWndSize wLink( GetDlgItem( a_hDlg , s_ids.m_nLink ) );
			CWndSize wP2( GetDlgItem( a_hDlg , s_ids.m_nText0 ) );
			CWndSize wProgrammed( GetDlgItem( a_hDlg , s_ids.m_nEdit ) );
			//--------------------------------------------------
			int nMaxHeight_Link = 0;
			int nMaxWidth_Link = 0;

			if( wLink.GetHWND() )
			{
				nMaxHeight_Link = (int)::SendMessage( wLink.GetHWND() , LM_GETIDEALHEIGHT , 0 , 0 );

				nMaxWidth_Link = 0;
				int nHeight1;
				int nHeight2;

				SIZE size = {};
				do
				{
					nMaxWidth_Link++;
					nHeight1 = (int)::SendMessage( wLink.GetHWND() , LM_GETIDEALSIZE , (WPARAM)nMaxWidth_Link     , (LPARAM)&size );
					nHeight2 = (int)::SendMessage( wLink.GetHWND() , LM_GETIDEALSIZE , (WPARAM)nMaxWidth_Link + 2 , (LPARAM)&size );
				}
				while ( nMaxHeight_Link != nHeight1 || nMaxHeight_Link != nHeight2 );
			}

			if( nMaxWidth_Link < (szClientSize.cx - 8*2) )
			{
				//nMaxWidth_Link = (szClientSize.cx - 8*2);
			}
			else
				szClientSize.cx = nMaxWidth_Link + 8*2;

			szClientSize.cy =
				8 + wIcon.GetSize().cy +
				2 + wAppName.GetSize().cy +
				16 + nMaxHeight_Link +
				16 + wP2.GetSize().cy +
				2 + wProgrammed.GetSize().cy +
				8;

			MoveWindow( a_hDlg , rcMain1.left , rcMain1.top , szClientSize.cx + szMainB.cx , szClientSize.cy + szMainB.cy , TRUE );
			//
			int posY = 8;

			wIcon.SetC_X( szClientSize.cx , posY , wIcon.GetSize().cx , wIcon.GetSize().cy );
			posY += (2 + wIcon.GetSize().cy);

			//SetWindowLong( wAppName.GetHWND() , GWL_STYLE ,  GetWindowLong( wAppName.GetHWND() , GWL_STYLE ) | SS_CENTER );
			wAppName.SetC_X( szClientSize.cx , posY , szClientSize.cx , wAppName.GetSize().cy );
			posY += (16 + wAppName.GetSize().cy);

			wLink.SetC_X( szClientSize.cx , posY , nMaxWidth_Link , nMaxHeight_Link );
			posY += (16 + wLink.GetSize().cy);

			//SetWindowLong( wP2.GetHWND() , GWL_STYLE ,  GetWindowLong( wP2.GetHWND() , GWL_STYLE ) | SS_CENTER );
			wP2.SetC_X( szClientSize.cx , posY , szClientSize.cx , wP2.GetSize().cy );
			posY += (2 + wP2.GetSize().cy);

			wProgrammed.SetC_X( szClientSize.cx , posY , szClientSize.cx , wProgrammed.GetSize().cy );
			posY += (2 + wProgrammed.GetSize().cy);
		}

		return (INT_PTR)TRUE;
	case WM_NOTIFY:
		{
			const LPNMHDR pNMHdr = (LPNMHDR)a_lParam;
			switch (pNMHdr->code)
			{
				//case NM_RETURN:
			case NM_CLICK:
				{
					const PNMLINK pNMLink = (PNMLINK)a_lParam;

					if( *pNMLink->item.szUrl )
						ShellExecute( NULL , L"open" , pNMLink->item.szUrl , NULL , NULL , SW_SHOW );
				}
				break;
			};
		}
	case WM_COMMAND:
		if (LOWORD(a_wParam) == IDOK || LOWORD(a_wParam) == IDCANCEL)
		{
			EndDialog( a_hDlg , LOWORD(a_wParam) );
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}