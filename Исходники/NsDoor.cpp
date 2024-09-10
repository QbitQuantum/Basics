//////////////////////////////////////////////////////////////////////////
//进程管理窗口过程
//////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK ProcDlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	HWND hList = NULL;
	LPNMHDR lPnmhdr = NULL;
	switch (uMsg)
	{
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case ID_POPUP_40007:
				{
					hList = GetDlgItem(hDlg,IDC_LIST1);
					int index = ListView_GetSelectionMark(hList);
					char temp[10] = {0};
					ListView_GetItemText(hList,index,0,temp,sizeof(temp));
					int pid = atoi(temp);
					ProcDelete(sockfd,pid);

				}
				break;
			case ID_POPUP_40009:
				{
					//PID==0为刷新
					int pid = 0;
					ProcDelete(sockfd,pid);
				}
				break;
			}
		}
		break;
	case WM_NOTIFY:
		{
			lPnmhdr = (LPNMHDR)lParam;
			hList = GetDlgItem(hDlg,IDC_LIST1);
			if (lPnmhdr->hwndFrom==hList)
			{
				switch (lPnmhdr->code)
				{
				case NM_RCLICK:
					{
						HMENU hMenu = LoadMenu(hInst,MAKEINTRESOURCE(IDR_MENU2));
						hMenu = GetSubMenu(hMenu,0);
						POINT stPos;
						GetCursorPos(&stPos);
						TrackPopupMenu(hMenu,TPM_LEFTALIGN,stPos.x,stPos.y,NULL,hDlg,NULL);
					}
					break;
				}
			}
		}
	case WM_INITMENUPOPUP:
		{
			BOOL flag = TRUE;
			hList = GetDlgItem(hDlg,IDC_LIST1);
			int index = ListView_GetSelectionMark(hList);
			int count = ListView_GetItemCount(hList);
			if (index >= count)
			{
				flag = FALSE;
			}
			switch(LOWORD(lParam))
			{
			case 0:
				{
					if (flag)
					{
						EnableMenuItem((HMENU)wParam,ID_POPUP_40007,MF_ENABLED);
					}
					else
					{
						EnableMenuItem((HMENU)wParam,ID_POPUP_40007,MF_GRAYED);
					}

				}
				break;
			}
		}
		break;
	case WM_SOCKET:
		{
			switch(LOWORD(lParam))
			{
			case FD_WRITE:
				{
					//继续发送
					SendCmd(sockfd,NULL,NULL);
				}
				break;
			case FD_READ:
				{
					RecvCmd(sockfd);
				}
				break;
			case FD_CLOSE:
				{
					//SOCKET出错处理,MainFunc.H里 清理缓冲区
					SocketError(sockfd);
				}
				break;
			}
		}
		break;
	case WM_INITDIALOG:
		{
			sockfd = (SOCKET)lParam;
			hList = GetDlgItem(hDlg,IDC_LIST1);
			hSysList = hList;
			//非拥塞模式
			WSAAsyncSelect(sockfd,hDlg,WM_SOCKET,FD_WRITE|FD_READ|FD_CLOSE);
			//发送命令请求
			RatProto ratPro;
			ratPro.RatId = PROC_VIEW;
			ratPro.RatLen = sizeof(RatProto);
			SendCmd(sockfd,(char*)&ratPro,ratPro.RatLen);
			//初始化列表
			InitProcList(hList);
		}
		break;
	case WM_CLOSE:
		{
			EndDialog(hDlg,NULL);
		}
		break;
	default:
		break;
	}

	return FALSE;
}