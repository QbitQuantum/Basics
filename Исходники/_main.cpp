LRESULT CALLBACK WndProcViewLog(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam )
{
	//LPNMHDR hdr;
	//TVITEM tvit;
	NMLVDISPINFO *lvdi;
	wchar_t buff[2048];
	int buff_r;
	int buff_g;
	int buff_b;
	wchar_t* pos=0;
	DWORD dwStyle;
	UINT idButton;
	SCROLLBARINFO sbi;
	TBBUTTON tbButton={LOWORD(lParam)-70, 0,  TBSTATE_ENABLED, BTNS_SEP, 0L, 0};
	sbi.cbSize=sizeof(SCROLLBARINFO);
	switch(Msg)
	{
		case WM_DESTROY:
			mLogWnd[hWnd].exit = true;
			PostQuitMessage(0);
		break;
			break;
		case WM_COMMAND:
			if ((HWND)lParam==mLogWnd[hWnd].hToolBar)
			{
				switch (wParam)
				{
				case 123: //find button
					SendMessage(mLogWnd[hWnd].hFindText,WM_GETTEXT,2048,(LPARAM)buff);
					mLogWnd[hWnd].Find(buff);
					break;
				case 125:
					if (SendMessage(mLogWnd[hWnd].hToolBar,TB_ISBUTTONCHECKED,125,0))
					{	SetWindowPos(hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE | SWP_NOMOVE);	}
					else
					{	SetWindowPos(hWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOSIZE | SWP_NOMOVE);	}
					break;
				}

			}
			break;
		case WM_SIZE:
			MoveWindow(mLogWnd[hWnd].hListView,0,28,LOWORD(lParam),HIWORD(lParam)-28,TRUE);
			SetWindowPos(mLogWnd[hWnd].hFindText,0,LOWORD(lParam)-225,2,0,0,SWP_NOZORDER | SWP_NOSIZE);
			SetWindowPos(mLogWnd[hWnd].hProgressBar,0,LOWORD(lParam)-225,2,0,0,SWP_NOZORDER | SWP_NOSIZE);
			SendMessage(mLogWnd[hWnd].hToolBar,TB_DELETEBUTTON,0,0);
			SendMessage(mLogWnd[hWnd].hToolBar,TB_INSERTBUTTON,0,(LPARAM)&tbButton);
			SendMessage(mLogWnd[hWnd].hToolBar,TB_AUTOSIZE,0,0);
			
			LVCOLUMN lcol;
			lcol.mask = LVCF_WIDTH;
			dwStyle = (DWORD)GetWindowLong(mLogWnd[hWnd].hListView, GWL_STYLE);
			if (dwStyle & WS_VSCROLL)
			{ GetScrollBarInfo(mLogWnd[hWnd].hListView,OBJID_VSCROLL,&sbi);
			lcol.cx = LOWORD(lParam)-sbi.dxyLineButton;	}
			else
			{lcol.cx = LOWORD(lParam);}
			ListView_SetColumn(mLogWnd[hWnd].hListView,0,&lcol);
		break;
		case WM_NOTIFY:
			LPNMLISTVIEW pnm;
            pnm = (LPNMLISTVIEW)lParam;
			switch (pnm->hdr.code)
			{
			case NM_CUSTOMDRAW:
				NMLVCUSTOMDRAW *nmlvcd;
				nmlvcd = (NMLVCUSTOMDRAW *)lParam;
				switch (nmlvcd -> nmcd.dwDrawStage)
				{
				case CDDS_PREPAINT:
					return CDRF_NOTIFYITEMDRAW;
				break;
				case CDDS_ITEMPREPAINT:
					// Determine colors
					
					if (mLogWnd[hWnd].vList.size()==0 ||
						nmlvcd -> nmcd.dwItemSpec>mLogWnd[hWnd].vList.size())
					{  
						return CDRF_NEWFONT;	
					}
					if (swscanf_s (mLogWnd[hWnd].vList[nmlvcd -> nmcd.dwItemSpec].c_str(),
						L"%[a-zA-Z?ÿ??_.]%*[:|]%d,%d,%d",buff,1024,&buff_r,&buff_g,&buff_b
						)==4)
					{
						nmlvcd -> clrTextBk = RGB(buff_r,buff_g,buff_b);
					}
					
					/*if ( nmlvcd -> nmcd.dwItemSpec & 1 )
					{
						nmlvcd -> clrTextBk = RGB(200,200,200);
						//nmlvcd -> 
						//nmlvcd -> clrText = 0xF0F0F0;
						SelectObject ( nmlvcd -> nmcd.hdc, GetStockObject (SYSTEM_FONT) );
						//return CDRF_NEWFONT;
					}
					else
					{
						nmlvcd -> clrTextBk = RGB(230,230,230);
					}*/
					return CDRF_NEWFONT;
				break;
				}
			break;
			
			case TTN_GETDISPINFO:
					LPTOOLTIPTEXT lpttt; 
					lpttt = (LPTOOLTIPTEXT) lParam; 
					lpttt->hinst = App.hIns; 
					// Specify the resource identifier of the descriptive 
					// text for the given button. 
					idButton = lpttt->hdr.idFrom; 
					switch (idButton) 
					{ 
					    case 123: 
							lpttt->lpszText = MAKEINTRESOURCE(IDS_STRING_UFINDBUTTON); 
					        break; 
					    case 124: 
							lpttt->lpszText = MAKEINTRESOURCE(IDS_STRING_UASCROLL); 
					        break; 
					    case 125: 
					        lpttt->lpszText = MAKEINTRESOURCE(IDS_STRING_UTOP); 
					        break; 
					} 
					break; 
				
			case NM_DBLCLK:
				DialogBox(App.hIns,MAKEINTRESOURCE(IDD_DIALOGVIEWMSG),mLogWnd[hWnd].hWnd,(DLGPROC)DlgMsgProc);
				break;
			
			case LVN_GETDISPINFO:
				lvdi = (NMLVDISPINFO*) lParam;
				if (lvdi->item.mask & LVIF_TEXT)
				{	
					//while (lvdi->item.pszText=wcscspn(mLogWnd[hWnd].vList[lvdi->item.iItem].c_str(),L":|:"))
					//wcscpy( buff,const_cast<LPWSTR>(mLogWnd[hWnd].vList[lvdi->item.iItem].c_str()));
					lvdi->item.pszText = const_cast<LPWSTR>(mLogWnd[hWnd].vList[lvdi->item.iItem].c_str());

					// remove "Debug"...
					//while ((pos=wcsstr(lvdi->item.pszText,L":|:"))!=NULL)
					//{
					//	lvdi->item.pszText=pos+3;
					//}
					lvdi->item.cchTextMax = 1024;
				}	
			break;
         }// switch
         
         break; // WM_NOTIFY

		default:
		return DefWindowProc(hWnd,Msg,wParam,lParam);
	}
	return(0);
}